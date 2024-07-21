//-------------------------------------------------------------------------------
// File: Resources\VulkanReplay.cpp
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//-------------------------------------------------------------------------------

#include "Application.h"
#include "Arguments.h"

#include <vk_mem_alloc.h>

#include "Helpers.h"
#include "Timer.h"
#include "VulkanHelpers.h"
#if defined(NV_USE_OPENGL)
#include "OpenGLHelpers.h"
#endif

#include "VulkanReplay.h"
#include "VulkanStructHydrator.h"
#if !defined(__ANDROID__)
#include "WindowSystem.h"
#endif

#include "VulkanTools/ScopedVmaBuffer.h"
#include "VulkanTools/VulkanStructCopy.h"

#include "ThreadPool.h"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cstdint>
#include <ctime>
#include <functional>
#include <future>
#include <iomanip>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

using namespace NV::VulkanTools;

// WAR for lack of make_unique in C++11
#if !defined(_MSC_VER) && __cplusplus < 201402L
namespace std {
template <class T, class... Types>
unique_ptr<T> make_unique(Types&&... Args)
{
    return unique_ptr<T>(new T(std::forward<Types>(Args)...));
}
}
#endif

// Define TLS
#if defined(_MSC_VER) && _MSC_VER < 1900
#define TLS_STORAGE __declspec(thread)
#elif defined(__GNUC__)
#define TLS_STORAGE __thread
#else
#define TLS_STORAGE thread_local
#endif

//------------------------------------------------------------------------------
// SYSTEM_ALIGNED_MALLOC
//
// System specific aligned allocation code (much simpler if C++17 is supported)
//------------------------------------------------------------------------------
#if defined(_WIN32)
#define SYSTEM_ALIGNED_MALLOC(alignment, size) (_aligned_malloc((size), (alignment)))
#elif defined(__ANDROID_API__) && (__ANDROID_API__ < 16)
#define SYSTEM_ALIGNED_MALLOC(alignment, size) (memalign((alignment), (size)))
#elif defined(__APPLE__) || defined(__ANDROID__) || (defined(__linux__) && defined(__GLIBCXX__) && !defined(_GLIBCXX_HAVE_ALIGNED_ALLOC))
void* do_posix_memalign(size_t alignment, size_t size)
{
    void* ptr;
    if (posix_memalign(&ptr, alignment, size) != 0)
    {
        return nullptr;
    }
    return ptr;
}
#define SYSTEM_ALIGNED_MALLOC(alignment, size) (do_posix_memalign((alignment), (size)))
#else
#define SYSTEM_ALIGNED_MALLOC(alignment, size) (aligned_alloc((alignment), (size)))
#endif

//------------------------------------------------------------------------------
// ByteSize
//------------------------------------------------------------------------------
#ifndef BYTE_SIZE
#define BYTE_SIZE 8
#endif

//------------------------------------------------------------------------------
// Bootstrap functions
//------------------------------------------------------------------------------
extern void BootstrapICD();
extern void BootstrapInstance(VkInstance instance);
extern void BootstrapDevice(VkDevice device);
extern bool Has_vkEnumerateInstanceVersion();

//------------------------------------------------------------------------------
// Strings
//------------------------------------------------------------------------------
static const char* k_ReplayMemoryManagment = "vk-replay-memory-management";
static const char* k_UnsafeCompactedAccelerationStructures = "vk-unsafe-compacted-acceleration-structures";
static const char* k_PerfMarkerCleanupName = "[NSIGHT] Perf Marker Cleanup";

//------------------------------------------------------------------------------
// Vulkan-specific options
//------------------------------------------------------------------------------
static bool s_SyncAtEndOfFrame = false;
static bool s_PopulateAllResources = false;
static bool s_SkipMappedMemoryUpdates = false;
static bool s_UseReplayManagedMemoryAllocations = false;
static bool s_CacheCommandBuffer = false;
static bool s_ForceResetCommandBuffers = false;
static bool s_MinimizeValidationWarnings = false;
static bool s_DisableCopyQueryPoolResults = false;
static bool s_DisableDeviceDiagnosticCheckpoints = false;
static bool s_CloseAllPerfMarkersBeforePresent = false;
static int32_t s_ForcePresentMode = -1;
static std::vector<std::string> s_vecAdditionalLayers;
static bool s_ReportCallContext = false;
static VulkanHelper_CallingContext s_CurrentCallingContext = {};
static bool s_TrimDeviceMemory = false;
static bool s_UnsafeCompactedAccelerationStructuresKHR = false;
static bool s_IgnoreSemaphores = false;
static bool s_SyncAfterSumbit = false;
static bool s_DumpFrame = false;

#if defined(VK_USE_PLATFORM_WIN32_KHR) || defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
static bool s_DummyFullscreen = false;
#define NV_DUMMY_FULL_SCREEN 1
#endif

//------------------------------------------------------------------------------
// Global mutex
//------------------------------------------------------------------------------
static std::recursive_mutex s_VulkanMutex;

//------------------------------------------------------------------------------
// Global variables
//------------------------------------------------------------------------------
static bool s_NeedDumpFrame = false; // when dumped image once, this flag will be reset

#define VULKAN_REPLAY_WRITE_LOCK() \
    std::unique_lock<std::recursive_mutex> lock(s_VulkanMutex)

//------------------------------------------------------------------------------
// Vulkan-specific option parser
//------------------------------------------------------------------------------
static FnParseResults ParseVulkanArguments(args::ArgumentParser& parser)
{
    // Vulkan option group
    static args::Group optVulkanGroup(parser, "Vulkan-specific options");

#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
    // By default we replay multi-threaded applications only using a single
    // thread to avoid context switching overhead. Enabling multi-threading
    // will utilize a coarse grain synchronization pattern (e.g. one thread
    // at a time) to make sure each call is replayed on the thread it originally
    // happened in an exact atomic ordering. For Vulkan, this is only necessary
    // if there is a usage pattern where multi-threading is necessary to unblock
    // a thread waiting on a fence from another thread. Performance wise, enabling
    // this option will almost always result in a performance slow down.
    static args::Flag optMtReplay(optVulkanGroup, "optMtReplay", "Enable multi-threaded replay [default=false]", { "vk-multithreaded-replay", "vk-mt" });
#endif

    // Allows for additional explicit layers to be specified at the command line.
    // Multiple layers can be specified by adding this option multiple times.
    static args::ValueFlagList<std::string> optLayers(optVulkanGroup, "optLayers", "Force an explicit layer to be active", { "vk-layer" });

    // By default we rebuild command buffers in frame if they were recorded in
    // frame. This option will cache recording so that it only happens once.
    static args::Flag optCacheCommandBuffer(optVulkanGroup, "optCacheCommandBuffer", "Cache command buffer rebuilds [default=false]", { "vk-cache-commandbuffers" });

    // Provide option to force rebuilding command buffers that were recorded out-of-frame.
    // This might be necessary to remove flickering if the application pre-baked a bunch
    // of commands related to swap chain management. This is pretty rare as most applications
    // re-record depending on the current swapchain state rather than cache.
    static args::Flag optResetCommandBuffers(optVulkanGroup, "optResetCommandBuffers", "Force re-recording of all command buffers [default=false]", { "vk-force-rebuild-commandbuffers" });

    // Enable collection of file and line context for api entrypoints.
    static args::Flag optReportCallContext(optVulkanGroup, "optReportCallContext", "Enable reporting of file and line locations of api calls", { "vk-report-call-context" });

    // Looping a single frame in isolation creates some synchronization problems
    // that don't necessarily exist in the original application. Namely, we must
    // take extra care to ensure that all synchronization primitives are ready
    // when submitting work for the next frame within the running loop. For JIT
    // syncing we synchronization pending primitives just before the usage event.
    // For EOF syncing, we synchronize everything during frame reset. JIT will
    // typically result in higher FPS but the waiting will be distributed
    // throughout the frame. Whereas EOF synchronization will result in lower
    // FPS with a single known synchronization point.
    static args::Group optVulkanSynchronizationStrategy(optVulkanGroup, "Synchronization strategy", args::Group::Validators::AtMostOne);

    static args::Flag optSyncJit(optVulkanSynchronizationStrategy, "optSyncJit", "Just in time (default)", { "vk-sync-jit" });
    static args::Flag optSyncEndOfFrame(optVulkanSynchronizationStrategy, "optSyncEndOfFrame", "End of frame", { "vk-sync-eof" });

    // Troubleshooting options.
    static args::Group optVulkanTroubleshooting(optVulkanGroup, "Troubleshooting options");

    // By default we don't populate images that were flagged as initialized in
    // frame (e.g. cleared, full screen quad, blit, etc.). This may lead to
    // "false negatives" where the replay appears to be working correctly
    // even though a command call is failing.
    static args::Flag optPopulateAllResources(optVulkanTroubleshooting, "optPopulateAllResources", "Pre-populate resources that are initialized in frame [default=false]", { "vk-populate-all-resources" });

    // It's possible that replaying the frame in isolation might lead to
    // corruption issues related to mapped memory since the original application
    // might have a synchronization pattern that falls apart when looping
    // a single frame in isolation.
    static args::Flag optSkipMappedMemoryUpdates(optVulkanTroubleshooting, "optSkipMappedMemoryUpdates", "Skip mapped memory updates", { "vk-skip-mapped-memory-updates" });

    // Trim device memory allocations to reduce memory pressure.
    static args::Flag optTrimDeviceMemory(optVulkanTroubleshooting, "optTrimDeviceMemory", "Trim device memory allocations of unused space [default=false]", { "vk-trim-device-memory" });

    // When this mode is enabled, the replayer the attempt to manage the
    // device allocations rather than using what the original application
    // has provided. This might be necessary to allow for replay on a system
    // with less GPU memory than one where the capture occurred. This might allow
    // for replay on a system with different GPU arch than one where the capture
    // occurred as well.
    static args::Flag optReplayMemoryManagement(optVulkanTroubleshooting, "optReplayMemoryManagement", "Enable replay managed device memory allocations", { k_ReplayMemoryManagment });

    // By default we do not allow for query pool results to be copied
    // because there is no way we can control the contents of a query pool
    // in frame looping. Under most circumstances the query pool will either
    // be incomplete or invalid which results in a hang (or device lost)
    // when copying to a buffer.
    static args::Flag optDisableCopyQueryPoolResults(optVulkanTroubleshooting, "optDisableCopyQueryPoolResults", "Disable copying of unsafe query pools", { "vk-disable-copy-query-pool-results" });

    // Disable the VK_NV_device_diagnostic_checkpoints extension which
    // may introduce instability during replay.
    static args::Flag optDisableDeviceDiagnosticCheckpoints(optVulkanTroubleshooting, "optDisableDeviceDiagnosticCheckpoints", "Disable VK_NV_device_diagnostic_checkpoints", { "vk-disable-checkpoints" });

    // There is a chicken-or-the-egg problem when it comes to compacted acceleration structure
    // objects due to the compacted size only being known after an the initial uncompacted build
    // and query which happen at initialization time -- not creation time. This option will use
    // the capture time compacted size which will fail if the replay compacted size has changed.
    // By default, we take a safer option which over-allocates but still compacts.
    static args::Flag optUnsafeCompactedAccelerationStructuresKHR(optVulkanTroubleshooting, "optUnsafeCompactedAccelerationStructuresKHR", "Allow unsafe/non-portable compact VkAccelerationStructureKHR objects", { k_UnsafeCompactedAccelerationStructures });

    // Sync after every submit to catch device lost errors soon after they happen
    // Will also help correctness in some applications that are missing some kind of synchronization but
    // only look wrong in replay due to the lack of CPU overhead.
    static args::Flag optSyncAfterSubmit(optVulkanTroubleshooting, "optSyncSubmit", "Synchronize after every queue submit", { "vk-sync-after-sumbit" });

    // Add ability to force a present mode
    static args::Group optPresentMode(optVulkanGroup, "Force present mode", args::Group::Validators::AtMostOne);
    static args::Flag optPresentModeImmediate(optPresentMode, "optPresentModeImmediate", "VK_PRESENT_MODE_IMMEDIATE_KHR", { "vk-force-present-mode-immediate" });
    static args::Flag optPresentModeMailbox(optPresentMode, "optPresentModeMailbox", "VK_PRESENT_MODE_MAILBOX_KHR", { "vk-force-present-mode-mailbox" });
    static args::Flag optPresentModeFifo(optPresentMode, "optPresentModeFifo", "VK_PRESENT_MODE_FIFO_KHR", { "vk-force-present-mode-fifo" });
    static args::Flag optPresentModeFifoRelaxed(optPresentMode, "optPresentModeFifoRelaxed", "VK_PRESENT_MODE_FIFO_RELAXED_KHR", { "vk-force-present-mode-fifo-relaxed" });

    // Ignore semaphores for testing purposes. This may lead to instability and/or rendering
    // corruption and should only be used for targeted "what if" experiment testing. In the
    // future there might be more knobs to control semaphore exclusion with more specificity.
    static args::Flag optIgnoreAllSemaphores(optVulkanGroup, "optIgnoreSemaphores", "Ignore all semaphore signals and waits; may lead to instability or corruption", { "vk-skip-semaphore-wait-all" });

    // Experimental option group
    static args::Group optExperimentalVulkanGroup(optVulkanGroup, "Experimental options");

#if defined(NV_DUMMY_FULL_SCREEN)
    // Using dummy swapchain with a fullscreen surface. If enabled, create fullscreen window and dummy swapchain,
    // which means it draws to dummy images and present nothing. This is useful in case of performance measuring
    // since non-fullscreen may hurt the performance. The reason why we use dummy as a WAR instead of directly
    // support fullscreen is that the complexity due to the Linux specific OUT_OF_DATE issue.
    static args::Flag optDummyFullscreen(optExperimentalVulkanGroup, "optDummyFullscreen", "Set the window to fullscreen and use dummy swapchain instead, this could be useful in case of performance measuring.", { "vk-dummy-fullscreen" });
#endif

    // dump the first frame to file when replaying
    static args::Flag optDumpFrame(optExperimentalVulkanGroup, "optDumpFrame", "Dump the first frame to file", { "vk-dump-frame" });

    return [=]() {
    // Vulkan defaults multi-threaded replay off
#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
        if (optMtReplay)
        {
            Application::EnableMultiThreadedReplay(true);
        }
        else
        {
            Application::EnableMultiThreadedReplay(false);
        }
#endif

        if (optLayers)
        {
            s_vecAdditionalLayers = optLayers.Get();
        }

        if (optSyncEndOfFrame)
        {
            s_SyncAtEndOfFrame = true;
        }

        if (optCacheCommandBuffer)
        {
            s_CacheCommandBuffer = optCacheCommandBuffer.Get();
        }

        if (optResetCommandBuffers)
        {
            s_ForceResetCommandBuffers = optResetCommandBuffers.Get();
        }

        if (optReportCallContext)
        {
            s_ReportCallContext = optReportCallContext.Get();
        }

        if (optPopulateAllResources)
        {
            s_PopulateAllResources = true;
        }

        if (optSkipMappedMemoryUpdates)
        {
            s_SkipMappedMemoryUpdates = true;
        }

        if (optTrimDeviceMemory)
        {
            s_TrimDeviceMemory = true;
        }

        if (optReplayMemoryManagement)
        {
            s_UseReplayManagedMemoryAllocations = true;
        }

        if (optDisableCopyQueryPoolResults)
        {
            s_DisableCopyQueryPoolResults = true;
        }

        if (optSyncAfterSubmit)
        {
            s_SyncAfterSumbit = true;
        }

        if (optUnsafeCompactedAccelerationStructuresKHR)
        {
            s_UnsafeCompactedAccelerationStructuresKHR = true;
        }

        if (optIgnoreAllSemaphores)
        {
            s_IgnoreSemaphores = true;
        }

        if (optPresentModeImmediate)
        {
            s_ForcePresentMode = int32_t(VK_PRESENT_MODE_IMMEDIATE_KHR);
        }
        else if (optPresentModeMailbox)
        {
            s_ForcePresentMode = int32_t(VK_PRESENT_MODE_MAILBOX_KHR);
        }
        else if (optPresentModeFifo)
        {
            s_ForcePresentMode = int32_t(VK_PRESENT_MODE_FIFO_KHR);
        }
        else if (optPresentModeFifoRelaxed)
        {
            s_ForcePresentMode = int32_t(VK_PRESENT_MODE_FIFO_RELAXED_KHR);
        }
        else
        {
            s_ForcePresentMode = -1;
        }
#if defined(NV_DUMMY_FULL_SCREEN)
        if (optDummyFullscreen)
        {
            s_DummyFullscreen = true;
        }
#endif
        if (optDumpFrame)
        {
            s_DumpFrame = true;
            s_NeedDumpFrame = true;
        }

        // NOTE: Disabling by default to work around known issues
        s_DisableDeviceDiagnosticCheckpoints = true;

        if (Application::MinimizeCPUOverheadRequested())
        {
            // This is where we set any options that we know are safe to enable and minimize the CPU overhead
            s_CacheCommandBuffer = true;
        }
    };
}

REGISTER_ARGUMENTS(ParseVulkanArguments);

//------------------------------------------------------------------------------
// DebugReportCallback
//
// Debug callback function used if forceDebug is enabled
//------------------------------------------------------------------------------
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    static std::set<std::string> s_suppressedMessageIDs;
    VULKAN_REPLAY_WRITE_LOCK();

    if (s_suppressedMessageIDs.size())
    {
        if (s_suppressedMessageIDs.count(pCallbackData->pMessageIdName))
        {
            return VK_FALSE;
        }
    }

    NV_MESSAGE("%s", pCallbackData->pMessage);

    // Set this to false to allow duplicate VUID messages
    bool suppressThisVUID = true;
    if (suppressThisVUID)
    {
        s_suppressedMessageIDs.insert(pCallbackData->pMessageIdName);
    }

    return VK_FALSE;
}

//------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------

// Global state of the replay process
enum class VulkanReplayPhase
{
    Creation, // Resources are being created
    Initializaiton, // Resources are being populated with their initial data
    Frame, // Frame replay
    StateReset, // State is being reset to initial data
    ResourceReset, // Resources are being reset to initial data
};

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
static const uint32_t NV_DEFAULT_FENCE_WAIT_NS = 5000000;
static const uint32_t NV_MAX_RESOURCES_INFLIGHT = 16;

//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------

// Unique identify for object override state (e.g. swapchain index)
using OverrideKey = uint64_t;

// Map of objects valid valid under the current override set
struct ObjectOverrideMap
{
    std::map<VkImage, VkImage> images;
    std::map<VkImageView, VkImageView> imageViews;
    std::map<VkFramebuffer, VkFramebuffer> framebuffers;
};

// Unique identifier for an image data piece
using ImageSubResource = std::tuple<VkImage, VkImageAspectFlags, uint32_t, uint32_t>;

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

struct InstanceInfo
{
    uint32_t instanceVersion = VK_API_VERSION_1_0;
    uint32_t applicationInfoApiVersion = VK_API_VERSION_1_0;
    std::vector<std::string> vecExplicitlyEnabledLayers;
};

static std::map<VkInstance, InstanceInfo> s_InstanceInfo;

// Running frame counters
static uint32_t s_FrameIdx = 0;
static uint32_t s_SubmitIdx = 0;
static std::map<VkCommandBuffer, uint32_t> s_TraceRaysNVIdx;

// Round-robin buffering indices
static uint32_t s_BufferingSize = 0;
static uint32_t s_BufferingIdx = 0;

// Current replay phase
static VulkanReplayPhase s_ReplayPhase = VulkanReplayPhase::Creation;

// Per-device versions
static std::map<VkDevice, uint32_t> s_DeviceVersion;

// Per-device allocators
static std::map<VkDevice, VmaAllocator> s_Allocators;
static std::map<VkDevice, std::unique_ptr<NV::VulkanTools::HostAllocator>> s_HostAllocators;

// Per-device work streamer
class WorkStreamer;
static std::map<VkDevice, std::unique_ptr<WorkStreamer>> s_ResourceUpdateHelpers;

// Information about the current command buffer being recorded
struct CommandBufferRecordInfo
{
    VkDevice device;
    VkCommandBuffer commandBuffer;
    const VkCommandBufferAllocateInfo* pAllocateInfo;
    PFN_RecordCommandBuffer pFnRecordCommandBuffer;
};
static CommandBufferRecordInfo s_CurrentCommandBufferRecordInfo;

// List of command buffer flagged for one-time submit
static std::map<VkCommandBuffer, CommandBufferRecordInfo> s_OneTimeSubmitCommandBuffersRecordedBeforeFrame;

// Information about each bound buffer
static std::map<VkBuffer, VkBindBufferMemoryInfo> s_BoundBufferInfo;

// List of built structures
#if defined(VK_NV_ray_tracing) || defined(VK_KHR_acceleration_structure)
static std::set<VkAccelerationStructureKHR> s_BuiltAccelerationStructuresKHR;
#endif

// Mapping information about NVX image view handles/addresses, image view handle/address at capture -> image view handle/address at replay
#if defined(VK_NVX_image_view_handle)
struct ImageViewHandleMappingInfoNVX
{
    uint32_t handle = 0;
    std::map<OverrideKey, uint32_t> overrideHandles;
};
struct ImageViewAddressMappingInfoNVX
{
    VkDeviceAddress address = 0;
    std::map<OverrideKey, VkDeviceAddress> overrideAddresses;
};
static std::map<uint32_t, ImageViewHandleMappingInfoNVX> s_imageViewHandleMappingInfoNVX;
static std::map<VkDeviceAddress, ImageViewAddressMappingInfoNVX> s_imageViewAddressMappingInfoNVX;
#endif

// Flag to force all scratch buffers to be allocated by Nsight
bool s_ForceReplayManagedScratch = false;

extern const char* ProcessName;

#if defined(VKSC_VERSION_1_0)
static VkCommandPoolMemoryReservationCreateInfo GetDefaultCommandPoolMemoryReservationInfo()
{
    // Here we reserve a default command pool size and max command buffer size
    // since we don't actually know the allocation size.
    VkCommandPoolMemoryReservationCreateInfo info = { VK_STRUCTURE_TYPE_COMMAND_POOL_MEMORY_RESERVATION_CREATE_INFO };
    info.commandPoolReservedSize = 10 * 1024 * 1024;
    info.commandPoolMaxCommandBuffers = 50;
    return info;
}
#endif

//------------------------------------------------------------------------------
// WorkStreamer
//------------------------------------------------------------------------------
class WorkStreamer
{
public:
    using DeviceMask = uint32_t;
    using FnWork = std::function<void(VkCommandBuffer)>;

    WorkStreamer(VkDevice device, uint32_t transferFamilyIndex)
        : m_device(device)
        , m_transferFamilyIndex(transferFamilyIndex)
    {
        VkCommandPoolCreateInfo commandPoolCreateInfo = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
#if defined(VKSC_VERSION_1_0)
        VkCommandPoolMemoryReservationCreateInfo memoryReservationInfo = GetDefaultCommandPoolMemoryReservationInfo();
        commandPoolCreateInfo.pNext = &memoryReservationInfo;
#endif
        commandPoolCreateInfo.queueFamilyIndex = transferFamilyIndex;
        vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &m_pool);

        VkFenceCreateInfo fenceCreateInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
        fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        for (uint32_t i = 0; i < WORK_SLOT_COUNT; i++)
        {
            vkCreateFence(device, &fenceCreateInfo, nullptr, &m_fences[i]);
        }
    }

    void EnqueueWork(DeviceMask deviceMask, VkDeviceSize size, FnWork&& fnWork)
    {
        // Add to appropriate work vector
        std::vector<FnWork>& vecWorkForDevice = m_vecPendingWork[deviceMask];
        vecWorkForDevice.emplace_back(std::move(fnWork));

        // Update size threshold
        m_pendingWorkload += size;

        // See if we are at the flush limit
        if (m_pendingWorkload >= WORK_SIZE_LIMIT || vecWorkForDevice.size() >= WORK_ITEM_LIMIT)
        {

            // Acquire next slot and make sure work from that slot is complete
            Flush();

            // Submit next work vector
            RecordAndSubmitWork(deviceMask, std::move(vecWorkForDevice));

            // Clear size workload
            m_pendingWorkload = 0;
        }
    }

    bool FinishWork()
    {
        // Empty all enqueued work queues
        bool hasWork = false;
        for (auto& pair : m_vecPendingWork)
        {
            Flush();
            uint32_t deviceMask = pair.first;
            std::vector<FnWork>& vecWorkForDevice = pair.second;
            if (!vecWorkForDevice.empty())
            {
                hasWork = true;
            }
            RecordAndSubmitWork(deviceMask, std::move(vecWorkForDevice));
        }

        // Bail if no work to do
        if (!hasWork)
        {
            return true;
        }

        // Wait for *all* work to finish
        VkResult result = VK_TIMEOUT;
        NV_TIMED_EXEC("WorkStreamer::WaitForAvailableSlot", [&]() {
            do
            {
                result = vkWaitForFences(m_device, WORK_SLOT_COUNT, m_fences, VK_TRUE, NV_DEFAULT_FENCE_WAIT_NS);
            } while (result == VK_TIMEOUT);
        });
        NV_ASSERT(result == VK_SUCCESS);

        // Reset all resources
        for (uint32_t i = 0; i < WORK_SLOT_COUNT; i++)
        {
            m_vecInflightWork[i].clear();
        }

        // Done with command buffers & pool
        vkFreeCommandBuffers(m_device, m_pool, (uint32_t)m_vecCmdBuffers.size(), m_vecCmdBuffers.data());
        m_vecCmdBuffers.clear();
        result = vkResetCommandPool(m_device, m_pool, VkCommandPoolResetFlags(0));
        NV_ASSERT(result == VK_SUCCESS);
        return true;
    }

private:
    // Number of items before we flush
    static const uint32_t WORK_ITEM_LIMIT = 32;
    static const uint32_t WORK_SIZE_LIMIT = 0x4000000; // 64 MB
    static const uint32_t WORK_SLOT_COUNT = 4;
    static const int32_t INVALID_SLOT = ~0u;

    void RecordAndSubmitWork(uint32_t deviceMask, std::vector<FnWork>&& vecWork);

    bool Flush()
    {
        // Acquire next slot; this might block if all channels are full
        m_slot = WaitForNextAvailableSlot();
        NV_ASSERT(m_slot != INVALID_SLOT);

        // Reset slot-specific resources
        vkResetFences(m_device, 1, &m_fences[m_slot]);
        m_vecInflightWork[m_slot].clear();

        // Success
        return true;
    }

    int32_t WaitForNextAvailableSlot() const
    {
        // Search for a free fence
        const int32_t slot = GetForAvailableSlot();
        if (slot != INVALID_SLOT)
        {
            return slot;
        }

        // Wait for *any* work to finish
        VkResult result = VK_TIMEOUT;
        NV_TIMED_EXEC("WorkStreamer::WaitForAvailableSlot", [&]() {
            do
            {
                result = vkWaitForFences(m_device, WORK_SLOT_COUNT, m_fences, VK_FALSE, NV_DEFAULT_FENCE_WAIT_NS);
            } while (result == VK_TIMEOUT);
        });
        NV_ASSERT(result == VK_SUCCESS);

        // Get any slot available
        return GetForAvailableSlot();
    }

    int32_t GetForAvailableSlot() const
    {
        // Query for available
        for (uint32_t i = 0; i < WORK_SLOT_COUNT; i++)
        {
            VkResult result = vkGetFenceStatus(m_device, m_fences[i]);
            if (result == VK_SUCCESS)
            {
                return int32_t(i);
            }
        }

        // None ready
        return INVALID_SLOT;
    }

    const VkDevice m_device = VK_NULL_HANDLE;
    const uint32_t m_transferFamilyIndex = 0;
    VkCommandPool m_pool = { VK_NULL_HANDLE };
    VkFence m_fences[WORK_SLOT_COUNT] = { VK_NULL_HANDLE };

    // Multi-buffering index
    int32_t m_slot = INVALID_SLOT;

    // Size of pending working to be uploaded
    VkDeviceSize m_pendingWorkload = 0;

    // All allocated command buffers
    std::vector<VkCommandBuffer> m_vecCmdBuffers;

    // Has not been recorded yet
    std::map<DeviceMask, std::vector<FnWork>> m_vecPendingWork;

    // Has been submitted but not waited up
    std::vector<FnWork> m_vecInflightWork[WORK_SLOT_COUNT];
};

// Per-descriptor pool information to handle unexpected allocation failures
static std::map<VkDescriptorPool, const VkDescriptorPoolCreateInfo*> s_DescriptorPoolCreateInfo;
static std::map<VkDescriptorPool, std::vector<VkDescriptorPool>> s_OverflowDescriptorPools;

// Known object sets
static std::set<VkPhysicalDevice> s_SetPhysicalDevices;
static std::set<VkDevice> s_SetDevices;

// Available extensions
static std::map<VkInstance, std::set<std::string>> s_InstanceExtensions;
static std::map<VkDevice, std::set<std::string>> s_DeviceExtensions;

// Valid replay queues
static std::map<VkDevice, std::map<uint32_t, VkDeviceQueueCreateInfo>> s_DeviceQueues;

// Swapchain info
struct SwapChainInfo
{
    VkDevice device = VK_NULL_HANDLE;
    VkSwapchainKHR upToDateSwapchain = VK_NULL_HANDLE;
    const VkAllocationCallbacks* pAllocator = nullptr;
    VkSwapchainCreateInfoKHR createInfo, originalCreateInfo;
    std::vector<VkImage> images;
    std::vector<VkDeviceMemory> dummyImageMemories;
    std::queue<uint32_t> acquiredImages;
};
static std::map<VkSwapchainKHR, SwapChainInfo> s_SwapChainInfoMap;

// GetSwapchainInfo (helper)
static SwapChainInfo& GetSwapchainInfo(VkSwapchainKHR swapchain)
{
    NV_ASSERT(s_SwapChainInfoMap.find(swapchain) != s_SwapChainInfoMap.end());
    return s_SwapChainInfoMap[swapchain];
}

// Override that is active when no swapchain image is acquired (e.g. between present and next acqurie)
OverrideKey s_DefaultOverride = 0;

// Command pool management
// In multi-threaded mode, we will create a dedicated command pool (matching the original create info)
// for every command buffer. This is because pools do not allow concurrent thread access.
struct CommandPoolInfo
{
    VkCommandPoolCreateInfo createInfo = {};
    uint32_t commandBufferCount = 0;
    VkCommandPool real = VK_NULL_HANDLE;
};
static std::map<VkCommandPool, CommandPoolInfo> s_CommandPoolInfo;

VkCommandPool CreateDedicateCommandPoolForCommandBuffer(VkDevice device, VkCommandPool realPool)
{
    auto iter = s_CommandPoolInfo.find(realPool);
    NV_ASSERT(iter != s_CommandPoolInfo.end());
    CommandPoolInfo& info = iter->second;
    // This bit-flag should have been set in VulkanReplay_CreateCommandPool, it is required so we
    // can reset the command buffer later.
    NV_ASSERT(info.createInfo.flags & VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

    // When single-threading we can always use the real pool.
    VkCommandPool newPool = VK_NULL_HANDLE;
    VkResult result = vkCreateCommandPool(device, &info.createInfo, nullptr, &newPool);
    NV_ASSERT(result == VK_SUCCESS);
    return newPool;
}

// Each command buffer has a dedicate pool to make multi-threaded replay possible
static std::map<VkCommandBuffer, VkCommandPool> s_CommandBufferToDedicatedPool;
void ResetDedicatedPool(VkDevice device, VkCommandBuffer commandBuffer)
{
    auto itr = s_CommandBufferToDedicatedPool.find(commandBuffer);
    NV_ASSERT(itr != s_CommandBufferToDedicatedPool.end());
    VkCommandPool commandPool = itr->second;
    vkResetCommandBuffer(commandBuffer, VkCommandBufferResetFlags(0));
    vkResetCommandPool(device, commandPool, VkCommandPoolResetFlags(0));
}

// Object-to-parent mapping
static std::map<VkPhysicalDevice, VkInstance> s_PhsyicalDeviceToInstanceMap;
static std::map<VkDevice, VkPhysicalDevice> s_DeviceToPhysicalDeviceMap;
static std::map<VkQueue, VkDevice> s_QueueToDeviceMap;
static std::map<VkCommandBuffer, VkDevice> s_CommandBufferToDeviceMap;
static std::map<VkCommandBuffer, const VkCommandBufferAllocateInfo*> s_CommandBufferToAllocateInfo;

// Query pool management
static std::map<VkQueryPool, const VkQueryPoolCreateInfo*> s_QueryPoolToCreateInfo;
static std::map<VkCommandBuffer, VkQueryPool> s_CommandBufferToQueryPoolReset;
static std::set<VkQueryPool> s_QueryPoolResetInFrame;
static std::map<VkQueryPool, std::vector<VkBool32>> s_QueryPoolAvailableRanges;

// Property checking
static std::map<VkPhysicalDevice, VkPhysicalDeviceMemoryProperties> s_CaptureMemoryProperties;
static std::map<VkPhysicalDevice, std::map<uint32_t, uint32_t>> s_QueueFamilyMap;

// Replay memory properties
static std::map<VkPhysicalDevice, VkPhysicalDeviceMemoryProperties> s_MemoryProperties;

// Remap flags
static bool s_SawQueueFamilyMismatch = false;
static bool s_SawHeapSizeMismatch = false;
static bool s_SawMemoryTypeMismatch = false;
static bool s_SawPipelineCacheHeaderMismatch = false;

// Keep track of objects who have size or alignment issues and cannot be placed in
// their original memory
static std::set<uint64_t> s_SawMemorySizeOrAlignmentMismatch;

// Requirement flags
struct MemoryRequirements
{
    VkDevice device;
    VkMemoryRequirements capture;
    VkMemoryRequirements replay;
};
static std::map<VkImage, MemoryRequirements> s_ImageMemoryRequirements;
static std::map<VkBuffer, MemoryRequirements> s_BufferMemoryRequirements;
#if defined(VK_NV_ray_tracing)
static std::map<VkAccelerationStructureNV, MemoryRequirements> s_AccelerationStructureMemoryRequirementsNV;
#endif
#if defined(VK_KHR_video_queue)
using VideoSessionMemoryBindKey = std::pair<VkVideoSessionKHR, uint32_t>;
static std::map<VideoSessionMemoryBindKey, MemoryRequirements> s_VideoSessionRequirements;
#endif

// Vma managed buffer information
struct VmaInfo
{
    VmaAllocator allocator;
    VmaAllocation allocation;
    VmaAllocationInfo allocationInfo;
};
static std::map<VkBuffer, VmaInfo> s_VmaBufferInfo;

// Basic state tracking
static std::map<VkBuffer, VkBufferCreateInfo> s_BufferCreateInfo;
static std::map<VkImage, VkImageCreateInfo> s_ImageCreateInfo;
static std::map<VkImage, VkFormat> s_ImageFormat;
#if defined(VK_USE_PLATFORM_WIN32_KHR)
std::map<VkSurfaceKHR, VkWin32SurfaceCreateInfoKHR> s_Win32SurfaceCreateInfoMap;
#endif
#if defined(VK_USE_PLATFORM_XCB_KHR)
std::map<VkSurfaceKHR, VkXcbSurfaceCreateInfoKHR> s_XcbSurfaceCreateInfoMap;
#endif
#if defined(VK_USE_PLATFORM_XLIB_KHR)
std::map<VkSurfaceKHR, VkXlibSurfaceCreateInfoKHR> s_XlibSurfaceCreateInfoMap;
#endif

// Buffer binding information
struct BindBufferMemoryInfo
{
    uint32_t memoryTypeIdx;
    VkBindBufferMemoryInfo bindInfo;
};
static std::map<VkBuffer, BindBufferMemoryInfo> s_BufferBindInfo;

// Image binding information
struct BindImageMemoryInfo
{
    uint32_t memoryTypeIdx;
    VkBindImageMemoryInfo bindInfo;
};
static std::map<VkImage, BindImageMemoryInfo> s_ImageBindInfo;

// Semaphore tracking
struct SemaphoreStatus
{
    bool signaled = false;
    uint32_t lastSignaledFrame = 0;
};
static std::map<VkSemaphore, SemaphoreStatus> s_SemaphoreStatus;

SemaphoreStatus& GetSempahoreStatus(VkSemaphore semaphore)
{
    auto itr = s_SemaphoreStatus.find(semaphore);
    NV_ASSERT(itr != s_SemaphoreStatus.end());
    return itr->second;
}

// Fence tracking
struct FenceStatus
{
    bool signaled = false;
};
static std::map<VkFence, FenceStatus> s_FenceStatus;

FenceStatus& GetFenceStatus(VkFence fence)
{
    auto itr = s_FenceStatus.find(fence);
    NV_ASSERT(itr != s_FenceStatus.end());
    return itr->second;
}

// Event tracking
static bool s_SawWaitEvent = false;
static std::set<VkEvent> s_ActiveEvents;
static std::vector<VkEvent> s_RogueEvents;
static std::map<VkCommandBuffer, std::set<VkEvent>> s_CommandBufferSetEvents;
static std::map<VkCommandBuffer, std::set<VkEvent>> s_CommandBufferResetEvents;
static std::map<VkCommandBuffer, std::set<VkEvent>> s_CommandBufferWaitEvents;

// We need to track all submits even if the original application wasn't
static std::map<uint32_t, VkFence> s_InjectedSubmitFences;

// Command buffer-to-fence tracking
static std::map<VkCommandBuffer, VkFence> s_CommandBufferToFence;

// Device memory information
struct DeviceMemoryInfo
{
    bool isAllocated;
    VkMemoryAllocateInfo allocateInfo;
    VkMemoryPropertyFlags propertyFlags;
};
static std::map<VkDeviceMemory, DeviceMemoryInfo> s_DeviceMemoryInfo;

// Device memory information
struct MemoryMappingInfo
{
    VkDeviceSize offset;
    VkDeviceSize size;
    VkMemoryMapFlags flags;
    void* pData;
};
static std::map<VkDeviceMemory, MemoryMappingInfo> s_MemoryMappingInfo;

//------------------------------------------------------------------------------
// GetObjectName
//------------------------------------------------------------------------------
template <typename T>
static std::string GetObjectName(T object)
{
    // TODO: This could utilize debug names with some reordering
    uint64_t id = uint64_t(object);
    const uint32_t width = id < UINT32_MAX ? 8 : 16;
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(width) << std::hex << id;
    return ss.str();
}

//------------------------------------------------------------------------------
// RaytracingHandleKey
//------------------------------------------------------------------------------
class RaytracingHandleKey
{
public:
    RaytracingHandleKey(VkPipeline pipeline, uint32_t shaderGroupHandleSize, const uint8_t* pData)
        : m_pipeline(pipeline)
        , m_data(pData, pData + shaderGroupHandleSize)
    {
    }

    bool operator<(const RaytracingHandleKey& rhs) const
    {
        return std::make_tuple(m_pipeline, m_data) < std::make_tuple(rhs.m_pipeline, rhs.m_data);
    }

    bool operator==(const RaytracingHandleKey& rhs) const
    {
        return std::make_tuple(m_pipeline, m_data) == std::make_tuple(rhs.m_pipeline, rhs.m_data);
    }

private:
    VkPipeline m_pipeline;
    std::string m_data;
};

//------------------------------------------------------------------------------
// HasExtension
//------------------------------------------------------------------------------
static bool HasExtension(VkDevice device, const char* pName)
{
    return s_DeviceExtensions[device].count(std::string(pName)) > 0;
}

//------------------------------------------------------------------------------
// GetBufferAddress
//------------------------------------------------------------------------------
static bool SupportsBufferAddress(VkDevice device)
{
#if defined(VKSC_VERSION_1_0)
    return false;
#else
    if (s_DeviceVersion[device] >= VK_API_VERSION_1_2)
    {
        return true;
    }
    if (HasExtension(device, VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
    {
        return true;
    }
    if (HasExtension(device, VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
    {
        return true;
    }
    return false;
#endif
}

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
//------------------------------------------------------------------------------
// GetBufferAddress
//------------------------------------------------------------------------------
static VkDeviceAddress GetBufferAddress(VkDevice device, VkBuffer buffer)
{
    VkDeviceAddress address = [&]() -> VkDeviceAddress {
        if (s_DeviceVersion[device] >= VK_API_VERSION_1_2)
        {
            VkBufferDeviceAddressInfo info = { VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO };
            info.buffer = buffer;
            return vkGetBufferDeviceAddress(device, &info);
        }
        else if (HasExtension(device, VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
        {
            VkBufferDeviceAddressInfoKHR info = { VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO_KHR };
            info.buffer = buffer;
            return vkGetBufferDeviceAddressKHR(device, &info);
        }
        else if (HasExtension(device, VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
        {
            VkBufferDeviceAddressInfoEXT info = { VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO_EXT };
            info.buffer = buffer;
            return vkGetBufferDeviceAddressEXT(device, &info);
        }
        else
        {
            NV_ASSERT(false && "no buffer device extension avaialble");
            return 0;
        }
    }();

    if (address == 0)
    {
        NV_LOG("WARNING: Failed to get buffer address");
    }

    return address;
}
#endif

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// GetAccelerationStructureReferenceKHR
//------------------------------------------------------------------------------
static VkDeviceAddress GetAccelerationStructureReferenceKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure)
{
    if (accelerationStructure == VK_NULL_HANDLE)
    {
        return 0;
    }

    VkAccelerationStructureDeviceAddressInfoKHR info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR };
    info.accelerationStructure = accelerationStructure;
    VkDeviceAddress address = vkGetAccelerationStructureDeviceAddressKHR(device, &info);
    NV_ASSERT(address != 0);
    return address;
}
#endif

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
//------------------------------------------------------------------------------
// BufferAddressManager
//------------------------------------------------------------------------------
class BufferAddressManager
{
public:
    void RegisterCaptureBufferAddress(VkBuffer buffer, const VkBufferCreateInfo* pCreateInfo, VkDeviceAddress captureAddress)
    {
        m_mapCaptureAddress[buffer] = captureAddress;
        m_mapCaptureBufferEnd[captureAddress + pCreateInfo->size] = buffer;
        m_mapBufferSize[buffer] = pCreateInfo->size;
    }

    void RegisterReplayBufferAddress(VkBuffer buffer, VkDeviceAddress replayAddress, VkDeviceSize size)
    {
        m_mapReplayBufferEnd[replayAddress + size] = buffer;
        m_mapBufferSize[buffer] = size;
    }

    VkDeviceAddress LookupOpaqueCaptureAddress(VkBuffer buffer) const
    {
        auto itr = m_mapCaptureAddress.find(buffer);
        if (itr == m_mapCaptureAddress.end())
        {
            NV_LOG("WARNING: Failed to lookup capture address of buffer (%s)", GetObjectName(buffer).c_str());
            return 0;
        }
        return itr->second;
    }

    VkBuffer LookupBufferFromCaptureAddress(VkDeviceAddress address, VkDeviceSize& offset)
    {
        return DoLookupBufferFromReplayAddress(m_mapCaptureBufferEnd, address, offset);
    }

    VkBuffer LookupBufferFromReplayAddress(VkDeviceAddress address, VkDeviceSize& offset)
    {
        return DoLookupBufferFromReplayAddress(m_mapReplayBufferEnd, address, offset);
    }

    bool RemapCaptureAddressForReplay(VkDevice device, VkDeviceAddress& captureAddress)
    {
        if (captureAddress == 0)
        {
            return true;
        }

        VkDeviceSize offset = 0;
        VkBuffer buffer = LookupBufferFromCaptureAddress(captureAddress, offset);
        NV_ASSERT(buffer != VK_NULL_HANDLE);
        captureAddress = GetBufferAddress(device, buffer);
        NV_ASSERT(captureAddress != 0);
        captureAddress += offset;
        return true;
    }

private:
    using AddressToBufferMap = std::map<VkDeviceAddress, VkBuffer>;

    VkBuffer DoLookupBufferFromReplayAddress(const AddressToBufferMap& map, VkDeviceAddress address, VkDeviceSize& offset)
    {
        auto itr = map.upper_bound(address);
        if (itr == map.end())
        {
            return VK_NULL_HANDLE;
        }
        const VkBuffer buffer = itr->second;
        const VkDeviceSize size = m_mapBufferSize[buffer];
        const VkDeviceAddress endAddress = itr->first;
        const VkDeviceAddress startAddress = endAddress - size;
        offset = address - startAddress;
        return buffer;
    }

    std::map<VkDeviceAddress, VkBuffer> m_mapCaptureBufferEnd;
    std::map<VkDeviceAddress, VkBuffer> m_mapReplayBufferEnd;
    std::map<VkBuffer, VkDeviceSize> m_mapBufferSize;
    std::map<VkBuffer, VkDeviceAddress> m_mapCaptureAddress;
};

// Helper to lookup buffers by address
static BufferAddressManager s_BufferAddressManager;
#endif

//------------------------------------------------------------------------------
// ObjectMap
//
// Generic implementation to allow for handle-to-object lookup
//------------------------------------------------------------------------------
template <typename T_Handle, typename T_Object>
class ObjectMap
{
public:
    template <class... Types>
    T_Object& Register(T_Handle handle, Types&&... args)
    {
        auto spObject = std::make_unique<T_Object>(std::forward<Types>(args)..., handle);
        T_Object* pEntry = spObject.get();
        auto entry = std::make_pair(handle, std::move(spObject));
        m_map.emplace(std::move(entry));
        return *pEntry;
    }

    T_Object* Lookup(T_Handle handle) const
    {
        auto itr = m_map.find(handle);
        if (itr == m_map.end())
        {
            return nullptr;
        }
        return itr->second.get();
    }

private:
    using T_ObjectMap = std::map<T_Handle, std::unique_ptr<T_Object>>;
    T_ObjectMap m_map;
};

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// AccelerationStructureNV
//------------------------------------------------------------------------------
struct AccelerationStructureNV
{
public:
    AccelerationStructureNV(VkDevice device_, const VkAccelerationStructureCreateInfoNV* pCreateInfoNV_, VkAccelerationStructureNV accelerationStructure_)
        : device(device_)
        , pCreateInfoNV(pCreateInfoNV_)
        , accelerationStructureNV(accelerationStructure_)
    {
    }

    VkMemoryRequirements GetMemoryRequirements() const
    {
        VkMemoryRequirements2 memoryRequirements = { VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2 };

        VkAccelerationStructureMemoryRequirementsInfoNV info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV };
        info.accelerationStructure = accelerationStructureNV;
        info.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;
        vkGetAccelerationStructureMemoryRequirementsNV(device, &info, &memoryRequirements);
        return memoryRequirements.memoryRequirements;
    }

    const VkDevice device;
    const VkAccelerationStructureCreateInfoNV* pCreateInfoNV = nullptr;
    const VkAccelerationStructureNV accelerationStructureNV;
};

//------------------------------------------------------------------------------
// AccelerationStructureKHR
//------------------------------------------------------------------------------
struct AccelerationStructureKHR
{
public:
    AccelerationStructureKHR(VkDevice device_, const VkAccelerationStructureCreateInfoKHR* pCreateInfoKHR_, const VkAccelerationStructureBuildSizesInfoKHR& sizeInfo_, VkAccelerationStructureKHR accelerationStructure_)
        : device(device_)
        , pCreateInfoKHR(pCreateInfoKHR_)
        , sizeInfo(sizeInfo_)
        , accelerationStructureKHR(accelerationStructure_)
    {
    }

    const VkDevice device;
    const VkAccelerationStructureCreateInfoKHR* pCreateInfoKHR = nullptr;
    const VkAccelerationStructureBuildSizesInfoKHR sizeInfo;
    const VkAccelerationStructureKHR accelerationStructureKHR;

    bool replayManagedScratch = false;
};

// Global AccelerationStructureNV lookup table
ObjectMap<VkAccelerationStructureNV, AccelerationStructureNV> s_AccelerationStructuresNV;
ObjectMap<VkAccelerationStructureKHR, AccelerationStructureKHR> s_AccelerationStructuresKHR;

// Track buffers used for acceleration structures
std::set<VkBuffer> s_AccelerationStructureBuffers;

// NV_raytracing handle size
static uint32_t s_ShaderGroupHandleSize = 0;

// Type of shader binding tables
enum class RayTracingShaderBindingTableType
{
    RayGenShader,
    MissShader,
    HitShader,
    CallableShader,
};

// Vulkan feature
enum class Feature
{
    NV,
    EXT,
    KHR,
};

// Ray tracing group information (NV and KHR)
struct RaytracingHandleValue
{
    VkPipeline pipeline;
    uint32_t groupNumber;
};
static std::map<RaytracingHandleKey, RaytracingHandleValue> s_RayTracingHandleMap;

// Address-to-structure (NV or KHR)
static std::map<VkDeviceAddress, VkAccelerationStructureNV> s_AccelerationStructureAddressMapNV;
static std::map<VkDeviceAddress, VkAccelerationStructureKHR> s_AccelerationStructureAddressMapKHR;

// Ray Tracing group information (NV & KHR)
using RaytracingGroup = std::tuple<VkPipeline, uint32_t>;
static std::map<RaytracingGroup, VkRayTracingShaderGroupCreateInfoKHR> s_RayTracingGroupInfo;
#endif

#if defined(VK_EXT_opacity_micromap)
//------------------------------------------------------------------------------
// MicromapEXT
//------------------------------------------------------------------------------
struct MicromapEXT
{
public:
    MicromapEXT(VkDevice device_, const VkMicromapCreateInfoEXT* pCreateInfoKHR_, const VkMicromapBuildSizesInfoEXT& sizeInfo_, VkMicromapEXT micromapEXT_)
        : device(device_)
        , pCreateInfoKHR(pCreateInfoKHR_)
        , sizeInfo(sizeInfo_)
        , micromapEXT(micromapEXT_)
    {
    }

    const VkDevice device;
    const VkMicromapCreateInfoEXT* pCreateInfoKHR = nullptr;
    const VkMicromapBuildSizesInfoEXT sizeInfo;
    const VkMicromapEXT micromapEXT;

    bool replayManagedScratch = false;
};

// Global micromap lookup table
ObjectMap<VkMicromapEXT, MicromapEXT> s_Micromaps;

// Track buffers used for micromaps
std::set<VkBuffer> s_MicromapBuffers;

#endif

// Override tracking
struct VulkanThreadState
{
    // @activeOverride: The main thread is the primary writer in Acquire and Present.  The only time
    // when this is not true is when command buffers must generate all overrides at once (rare case).
    // To handle that, we start the record thread off with the spawning main thread state, and are
    // free to mutate the TLS from there as it will not pollute the main thread.
    OverrideKey activeOverride = 0;

    // SBT
    std::map<std::tuple<VkCommandBuffer, VkPipelineBindPoint>, VkPipeline> currentBoundPipeline;

    // VulkanReplay_CmdBindDescriptorSets
    std::vector<VkDescriptorSet> vecDescriptorSets;

    // VulkanReplay_UpdateDescriptorSets
    std::map<uint32_t, std::set<VkDescriptorSet>> eventToDescriptorsUsed;
    std::set<uint32_t> eventRequiresOverrides;
};

static TLS_STORAGE VulkanThreadState* s_pTLS;
VulkanThreadState& GetThreadState()
{
    VulkanThreadState* pTLS = s_pTLS;
    if (!pTLS)
    {
        pTLS = new VulkanThreadState();
        s_pTLS = pTLS;
    }
    return *pTLS;
}

// Each key must belong (e.g. swapchain image count)
static std::vector<OverrideKey> s_VecOverrideSet;
static std::map<VkImage, OverrideKey> s_ImageToOverrideKey;
static std::map<VkImageView, OverrideKey> s_ImageViewToOverrideKey;
static std::map<OverrideKey, std::unique_ptr<ObjectOverrideMap>> s_OverrideKeyToObjectOverrideMap;

// Synchronization double buffering overrides
static std::map<VkSemaphore, std::vector<VkSemaphore>> s_SemaphoreOverrides;
static std::map<VkFence, std::vector<VkFence>> s_FenceOverrides;
static std::map<VkCommandBuffer, std::vector<VkCommandBuffer>> s_CommandBufferOverrides;
static std::map<VkDescriptorSet, std::vector<VkDescriptorSet>> s_DescriptorSetOverrides;
static std::map<VkDescriptorPool, std::vector<VkDescriptorPool>> s_DescriptorPoolOverrides;

struct CommandBufferRecordDesc
{
    bool valid = false;
    std::future<void> optionalFuture = {};
};
static std::map<VkCommandBuffer, CommandBufferRecordDesc> s_CommandBufferRecordDescs; // The state of command buffers can be modified during multithreaded records.

// Command buffers recorded in frame; used to JIT re-record in some cases
static std::set<VkCommandBuffer> s_CommandBufferRecordedInFrame;
static std::map<VkCommandBuffer, PFN_RecordCommandBuffer> s_CommandBufferToRecordRev0;

static bool WasCommandBufferRecordedInFrame(VkCommandBuffer commandBuffer)
{
    return s_CommandBufferRecordedInFrame.find(commandBuffer) != s_CommandBufferRecordedInFrame.end();
}

static CommandBufferRecordDesc& GetCommandBufferRecordDesc(VkCommandBuffer commandBuffer)
{
    auto iter = s_CommandBufferRecordDescs.find(commandBuffer);
    NV_ASSERT(iter != s_CommandBufferRecordDescs.end());
    return iter->second;
}

struct DescriptorSetInfo
{
    VkDescriptorSetLayout layout = VK_NULL_HANDLE;
    VkDescriptorPool pool = VK_NULL_HANDLE;
    bool valid = false;
};

static std::map<VkDescriptorSet, DescriptorSetInfo> s_DescriptorSetToInfoMap;

class DescriptorManager
{
public:
    void EnqueueDescriptorUpdates(const NV::VulkanTools::UpdateDescriptorSets_Params& params)
    {
        std::future<void> f = NvExecuteOnThreadPool([=] {
            vkUpdateDescriptorSets(
                params.device,
                params.descriptorWriteCount,
                params.pDescriptorWrites,
                params.descriptorCopyCount,
                params.pDescriptorCopies);
        });

        s_BatchedDescriptorUpdates.emplace_back(std::move(f));
    }

    void FlushDescriptorUpdates()
    {
        for (const std::future<void>& f : s_BatchedDescriptorUpdates)
        {
            f.wait();
        }
        s_BatchedDescriptorUpdates.clear();
    }

private:
    std::vector<std::future<void>> s_BatchedDescriptorUpdates;
};

static DescriptorManager s_DescriptorManager;

DescriptorSetInfo& GetDescriptorSetInfo(VkDescriptorSet set)
{
    auto iter = s_DescriptorSetToInfoMap.find(set);
    NV_ASSERT(iter != s_DescriptorSetToInfoMap.end());
    return iter->second;
}

// Semaphore info
struct SemaphoreInfo
{
    VkDevice device;
    const VkSemaphoreCreateInfo* pCreateInfo;
#if defined(VK_KHR_timeline_semaphore)
    VkSemaphoreTypeKHR type;
#endif
    uint64_t startValue;
    uint64_t endValue;
    uint64_t value;

    // This delta is the total per-frame difference of this semaphore. In theory we
    // could violate maxTimelineSemaphoreValueDifference in an extreme corner case
    // which would need some special handling if that ever happened.
    uint64_t delta;

    // Minimal signaled value, currently used to identify invalid timeline wait
    mutable uint64_t minimalSignaledValue;
};
static std::map<VkSemaphore, SemaphoreInfo> s_SemaphoreToInfoMap;

// Fence info
struct FenceInfo
{
    VkDevice device;
    const VkFenceCreateInfo* pCreateInfo;
};
static std::map<VkFence, FenceInfo> s_FenceToInfoMap;

// Queue info
struct QueueInfo
{
    VkDevice device;
    uint32_t queueFamilyIndex;
    uint32_t queueIndex;
};
static std::map<VkQueue, QueueInfo> s_QueueInfo;

// Command pool info
static std::map<VkCommandPool, uint32_t> s_CommandPoolQueueFamilyIndex;

// External memory update management
static uint32_t s_ExternalMemoryUpdateIdx = 0;
static std::vector<ScopedVmaBuffer*> s_ExternalMemoryDataBuffers;
static std::vector<VkBuffer> s_ExternalMemorySpanningBuffers;

// Object record
struct ObjectRecord
{
    VkObjectType type;
    uint64_t object;
};
static std::map<uint64_t, ObjectRecord> s_ObjectMap;

// We only need to decode packed database structure once
static std::map<uint32_t, std::vector<uint8_t>> s_HydratedStructCache;

//------------------------------------------------------------------------------
// AlignUpP2
//------------------------------------------------------------------------------
template <typename TValue, typename TAlign>
inline TValue AlignUpP2(TValue value, TAlign align)
{
    return (value + align - 1) & ~TValue(align - 1);
}

#define ALIGN_WORD(X) AlignUpP2(X, sizeof(uint32_t))

//------------------------------------------------------------------------------
// ObjectTypeToString
//------------------------------------------------------------------------------
static const char* ObjectTypeToString(VkObjectType type)
{
    switch (type)
    {
    case VK_OBJECT_TYPE_UNKNOWN:
        return "UNKNOWN";
    case VK_OBJECT_TYPE_INSTANCE:
        return "INSTANCE";
    case VK_OBJECT_TYPE_PHYSICAL_DEVICE:
        return "PHYSICAL_DEVICE";
    case VK_OBJECT_TYPE_DEVICE:
        return "DEVICE";
    case VK_OBJECT_TYPE_QUEUE:
        return "QUEUE";
    case VK_OBJECT_TYPE_SEMAPHORE:
        return "SEMAPHORE";
    case VK_OBJECT_TYPE_COMMAND_BUFFER:
        return "COMMAND_BUFFER";
    case VK_OBJECT_TYPE_FENCE:
        return "FENCE";
    case VK_OBJECT_TYPE_DEVICE_MEMORY:
        return "DEVICE_MEMORY";
    case VK_OBJECT_TYPE_BUFFER:
        return "BUFFER";
    case VK_OBJECT_TYPE_IMAGE:
        return "IMAGE";
    case VK_OBJECT_TYPE_EVENT:
        return "EVENT";
    case VK_OBJECT_TYPE_QUERY_POOL:
        return "QUERY_POOL";
    case VK_OBJECT_TYPE_BUFFER_VIEW:
        return "BUFFER_VIEW";
    case VK_OBJECT_TYPE_IMAGE_VIEW:
        return "IMAGE_VIEW";
#if !defined(VKSC_VERSION_1_0)
    case VK_OBJECT_TYPE_SHADER_MODULE:
        return "SHADER_MODULE";
#endif
    case VK_OBJECT_TYPE_PIPELINE_CACHE:
        return "PIPELINE_CACHE";
    case VK_OBJECT_TYPE_PIPELINE_LAYOUT:
        return "PIPELINE_LAYOUT";
    case VK_OBJECT_TYPE_RENDER_PASS:
        return "RENDER_PASS";
    case VK_OBJECT_TYPE_PIPELINE:
        return "PIPELINE";
    case VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT:
        return "DESCRIPTOR_SET_LAYOUT";
    case VK_OBJECT_TYPE_SAMPLER:
        return "SAMPLER";
    case VK_OBJECT_TYPE_DESCRIPTOR_POOL:
        return "DESCRIPTOR_POOL";
    case VK_OBJECT_TYPE_DESCRIPTOR_SET:
        return "DESCRIPTOR_SET";
    case VK_OBJECT_TYPE_FRAMEBUFFER:
        return "FRAMEBUFFER";
    case VK_OBJECT_TYPE_COMMAND_POOL:
        return "COMMAND_POOL";
    case VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION:
        return "SAMPLER_YCBCR_CONVERSION";
#if !defined(VKSC_VERSION_1_0)
    case VK_OBJECT_TYPE_DESCRIPTOR_UPDATE_TEMPLATE:
        return "DESCRIPTOR_UPDATE_TEMPLATE";
#endif
    case VK_OBJECT_TYPE_SURFACE_KHR:
        return "SURFACE_KHR";
    case VK_OBJECT_TYPE_SWAPCHAIN_KHR:
        return "SWAPCHAIN_KHR";
    case VK_OBJECT_TYPE_DISPLAY_KHR:
        return "DISPLAY_KHR";
    case VK_OBJECT_TYPE_DISPLAY_MODE_KHR:
        return "DISPLAY_MODE_KHR";
#if defined(VK_EXT_debug_report)
    case VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT:
        return "DEBUG_REPORT_CALLBACK_EXT";
#endif
    case VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT:
        return "DEBUG_UTILS_MESSENGER_EXT";
#if defined(VK_EXT_validation_cache)
    case VK_OBJECT_TYPE_VALIDATION_CACHE_EXT:
        return "VALIDATION_CACHE_EXT";
#endif
#if defined(VK_NV_ray_tracing)
    case VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV:
        return "ACCELERATION_STRUCTURE_NV";
#endif
#if defined(VK_INTEL_performance_query)
    case VK_OBJECT_TYPE_PERFORMANCE_CONFIGURATION_INTEL:
        return "PERFORMANCE_CONFIGURATION_INTEL";
#endif
    default:
        break;
    }

    return "UNKNOWN";
}

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// RayTracingShaderBindingTableTypeToString
//------------------------------------------------------------------------------
static const char* RayTracingShaderBindingTableTypeToString(RayTracingShaderBindingTableType type)
{
    switch (type)
    {
    case RayTracingShaderBindingTableType::RayGenShader:
        return "rayGen";
    case RayTracingShaderBindingTableType::MissShader:
        return "miss";
    case RayTracingShaderBindingTableType::HitShader:
        return "hit";
    case RayTracingShaderBindingTableType::CallableShader:
        return "callable";
    default:
        return "<ERROR>";
    }
}
#endif

//------------------------------------------------------------------------------
// BitsToString
//------------------------------------------------------------------------------
static std::string BitsToString(uint32_t bits)
{
    std::bitset<32> b(bits);
    std::stringstream ss;
    ss << "0b" << b.to_string();
    return ss.str();
}

//------------------------------------------------------------------------------
// BufferCreateFlagsToString
//------------------------------------------------------------------------------
std::string BufferCreateFlagsToString(VkFlags bits)
{
    if (bits == 0)
    {
        return "--";
    }

    std::stringstream ss;

    if (bits & VK_BUFFER_CREATE_SPARSE_BINDING_BIT)
    {
        ss << "SPARSE_BINDING";
        bits &= ~VK_BUFFER_CREATE_SPARSE_BINDING_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT)
    {
        ss << "SPARSE_RESIDENCY";
        bits &= ~VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_CREATE_SPARSE_ALIASED_BIT)
    {
        ss << "SPARSE_ALIASED";
        bits &= ~VK_BUFFER_CREATE_SPARSE_ALIASED_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_CREATE_PROTECTED_BIT)
    {
        ss << "PROTECTED";
        bits &= ~VK_BUFFER_CREATE_PROTECTED_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT)
    {
        ss << "DEVICE_ADDRESS_CAPTURE_REPLAY";
        bits &= ~VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    return ss.str();
}

//------------------------------------------------------------------------------
// BufferUsageFlagsToString
//------------------------------------------------------------------------------
std::string BufferUsageFlagsToString(VkFlags bits)
{
    if (bits == 0)
    {
        return "--";
    }

    std::stringstream ss;

    if (bits & VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
    {
        ss << "TRANSFER_SRC";
        bits &= ~VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_TRANSFER_DST_BIT)
    {
        ss << "TRANSFER_DST";
        bits &= ~VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
    {
        ss << "UNIFORM_TEXEL_BUFFER";
        bits &= ~VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT)
    {
        ss << "STORAGE_TEXEL_BUFFER";
        bits &= ~VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
    {
        ss << "UNIFORM_BUFFER";
        bits &= ~VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
    {
        ss << "STORAGE_BUFFER";
        bits &= ~VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
    {
        ss << "INDEX_BUFFER";
        bits &= ~VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
    {
        ss << "VERTEX_BUFFER";
        bits &= ~VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT)
    {
        ss << "INDIRECT_BUFFER";
        bits &= ~VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
    {
        ss << "SHADER_DEVICE_ADDRESS";
        bits &= ~VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

#if defined(VK_EXT_transform_feedback)
    if (bits & VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT)
    {
        ss << "TRANSFORM_FEEDBACK_BUFFER";
        bits &= ~VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT)
    {
        ss << "TRANSFORM_FEEDBACK_COUNTER_BUFFER";
        bits &= ~VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }
#endif

#if defined(VK_EXT_conditional_rendering)
    if (bits & VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT)
    {
        ss << "CONDITIONAL_RENDERING";
        bits &= ~VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }
#endif

#if defined(VK_KHR_acceleration_structure)
    if (bits & VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR)
    {
        ss << "ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY";
        bits &= ~VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR)
    {
        ss << "ACCELERATION_STRUCTURE_STORAGE";
        bits &= ~VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR)
    {
        ss << "SHADER_BINDING_TABLE";
        bits &= ~VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR;
        if (bits != 0)
        {
            ss << " | ";
        }
    }
#endif

    return ss.str();
}

//------------------------------------------------------------------------------
// VersionToString
//------------------------------------------------------------------------------
static std::string VersionToString(uint32_t version)
{
    std::stringstream ss;
    ss << VK_API_VERSION_MAJOR(version) << ".";
    ss << VK_API_VERSION_MINOR(version) << ".";
    ss << VK_API_VERSION_PATCH(version);
    return ss.str();
}

//------------------------------------------------------------------------------
// DriverVersionToString
//------------------------------------------------------------------------------
static std::string DriverVersionToString(VkPhysicalDeviceProperties props)
{
    // NVIDIA
    if (props.vendorID == 4318)
    {
        const uint32_t major = (props.driverVersion >> 22) & 0x3ff;
        const uint32_t minor = (props.driverVersion >> 14) & 0x0ff;
        const uint32_t secondaryBranch = (props.driverVersion >> 6) & 0x0ff;
        const uint32_t tertiaryBranch = (props.driverVersion) & 0x003f;

        std::stringstream ss;
        ss << major << ".";
        ss << std::setw(2) << std::setfill('0') << minor;
        if (secondaryBranch)
        {
            ss << "-" << secondaryBranch;
        }
        if (tertiaryBranch)
        {
            ss << "." << tertiaryBranch;
        }
        return ss.str();
    }

    return VersionToString(props.driverVersion);
}

//------------------------------------------------------------------------------
// FindStructure
//------------------------------------------------------------------------------
static const VkBaseInStructure* FindStructure(VkStructureType type, const void* pNext)
{
    // End of the chain
    if (!pNext)
    {
        return nullptr;
    }

    // First extension element
    const VkBaseInStructure* pBaseInStructure = reinterpret_cast<const VkBaseInStructure*>(pNext);

    // Found our extension type
    if (pBaseInStructure->sType == type)
    {
        return reinterpret_cast<const VkBaseInStructure*>(pNext);
    }

    // Next in the chain
    return FindStructure(type, pBaseInStructure->pNext);
}

//------------------------------------------------------------------------------
// AppendStructure
//------------------------------------------------------------------------------
inline void AppendStructure(void* pStructure, const void* pNewStructure)
{
    VkBaseInStructure* pBaseInStructure = reinterpret_cast<VkBaseInStructure*>(pStructure);
    while (pBaseInStructure->pNext != nullptr)
    {
        pBaseInStructure = const_cast<VkBaseInStructure*>(pBaseInStructure->pNext);
    }
    pBaseInStructure->pNext = reinterpret_cast<const VkBaseInStructure*>(pNewStructure);
}

//------------------------------------------------------------------------------
// GetAllocationCreateInfoForMemory
//------------------------------------------------------------------------------
static VmaAllocationCreateInfo GetAllocationCreateInfoForMemory(VkDeviceMemory memory)
{
    // Lookup memory requirements for this buffer
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // Categorize flags
    // NOTE: VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT should be consider *strongly preferred*
    // but there are cases where host-visible vidmem might not be available on the replay
    // system and we can soldier on without the device local part. There is a possibility
    // we could instead remove the host visible/coherent bits and populate via copies but
    // that would be a significant effort.
    const VkMemoryPropertyFlags requiredFlagsMask = (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    const VkMemoryPropertyFlags preferredFlagsMask = (VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT | VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT);

    // Make a create info with appropriate flags
    VmaAllocationCreateInfo createInfo = {};
    createInfo.requiredFlags = VkMemoryPropertyFlags(memoryInfo.propertyFlags & requiredFlagsMask);
    createInfo.preferredFlags = VkMemoryPropertyFlags(memoryInfo.propertyFlags & preferredFlagsMask);

    // Create mapped if host visible; this simplifies some later update code
    if (createInfo.requiredFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        createInfo.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
    }

    return createInfo;
}

//------------------------------------------------------------------------------
// RuntimeChecks
//------------------------------------------------------------------------------
class RuntimeChecks
{
public:
    static void SetRecorded(VkCommandBuffer cmdBuf, bool recorded = true)
    {
        CommandBufferRecordDesc& desc = GetCommandBufferRecordDesc(cmdBuf);
        desc.valid = recorded;
    }

    static void AssertRecorded(VkCommandBuffer cmdBuf)
    {
        // If a command buffer is submitted while in an invalid state it is more likely-than-not
        // an Nsight error. It's also possible (but rare) the application made this mistake because
        // it doesn't seem to be fatal on most Vulkan implementation.
        CommandBufferRecordDesc& desc = GetCommandBufferRecordDesc(cmdBuf);
        if (!desc.valid)
        {
            NV_THROW_IF(true, "WARNING: Command buffer is not in a valid state");
        }
    }
};

//------------------------------------------------------------------------------
// CheckBindTimeMemoryRequirements
//------------------------------------------------------------------------------
static bool CheckBindTimeMemoryRequirements(const MemoryRequirements& memoryRequirements, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    // Replay size is larger than capture size
    if (memoryRequirements.capture.size < memoryRequirements.replay.size)
    {
        NV_LOG("INFO: Forcing JIT allocate & remap due to size change (%" PRIu64 " < %" PRIu64 ")", memoryRequirements.capture.size, memoryRequirements.replay.size);
        return false;
    }

    // Alignment mismatch
    if (memoryRequirements.capture.alignment % memoryRequirements.replay.alignment != 0)
    {
        NV_LOG("INFO: Forcing JIT allocate & remap due to alignment change (%" PRIu64 "% %" PRIu64 " != 0)", memoryRequirements.capture.alignment, memoryRequirements.replay.alignment);
        return false;
    }

    // Lookup memory requirements for this buffer
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // Helper to check for bits being set
    auto IsBitSet = [](uint32_t bit, uint32_t mask) -> bool {
        return ((1u << bit) & mask);
    };

    //
    if (!IsBitSet(memoryInfo.allocateInfo.memoryTypeIndex, memoryRequirements.replay.memoryTypeBits))
    {
        NV_LOG("INFO: Forcing JIT allocate & remap due to memoryTypeBits change (bit %u not set in %s)", memoryInfo.allocateInfo.memoryTypeIndex, BitsToString(memoryRequirements.replay.memoryTypeBits).c_str());
        return false;
    }

    // Memory is still safe to use; carry on with bind
    return true;
}

//------------------------------------------------------------------------------
// LookupSemaphoreInfo
//------------------------------------------------------------------------------
static SemaphoreInfo* LookupSemaphoreInfo(VkSemaphore semaphore)
{
    auto itr = s_SemaphoreToInfoMap.find(semaphore);
    NV_ASSERT(itr != s_SemaphoreToInfoMap.end());
    return &itr->second;
}

//------------------------------------------------------------------------------
// LookupObject
//------------------------------------------------------------------------------
template <typename T_Handle>
T_Handle LookupObject(VkObjectType type, T_Handle object)
{
    if (object == 0)
    {
        return (T_Handle)VK_NULL_HANDLE;
    }

    const uint64_t id = (uint64_t)object;
    auto itr = s_ObjectMap.find(id);
    if (itr == s_ObjectMap.end())
    {
        NV_LOG("WARNING: failed to lookup %s with id: 0x%" PRIx64 "", ObjectTypeToString(type), id);
        return (T_Handle)VK_NULL_HANDLE;
    }
    return (T_Handle)itr->second.object;
}

//------------------------------------------------------------------------------
// FindPNextStructure (const)
//------------------------------------------------------------------------------
static const void* FindPNextStructure(const void* pNext, VkStructureType sType)
{
    if (!pNext)
    {
        return nullptr;
    }
    const VkBaseInStructure* pBaseInStructure = reinterpret_cast<const VkBaseInStructure*>(pNext);
    if (pBaseInStructure->sType == sType)
    {
        return pNext;
    }
    return FindPNextStructure(pBaseInStructure->pNext, sType);
}

//------------------------------------------------------------------------------
// FindPNextStructure
//------------------------------------------------------------------------------
static void* FindPNextStructure(void* pNext, VkStructureType sType)
{
    if (!pNext)
    {
        return nullptr;
    }
    const VkBaseInStructure* pBaseInStructure = reinterpret_cast<const VkBaseInStructure*>(pNext);
    if (pBaseInStructure->sType == sType)
    {
        return pNext;
    }
    return FindPNextStructure((void*)pBaseInStructure->pNext, sType);
}

//------------------------------------------------------------------------------
// ReplacePNextStructure
//------------------------------------------------------------------------------
static void ReplacePNextStructure(void** ppNext, VkStructureType sType, void* pNewStructure)
{
    if (!ppNext || !*ppNext)
    {
        return;
    }
    VkBaseInStructure* pBaseInStructure = reinterpret_cast<VkBaseInStructure*>(*ppNext);
    if (pBaseInStructure->sType == sType)
    {
        *ppNext = pNewStructure;
        return;
    }
    return ReplacePNextStructure((void**)&pBaseInStructure->pNext, sType, pNewStructure);
}

//------------------------------------------------------------------------------
// RemovePNextStructure
//------------------------------------------------------------------------------
static bool RemovePNextStructure(void* pThis, VkStructureType sType)
{
    VkBaseOutStructure* pNext = reinterpret_cast<VkBaseOutStructure*>(pThis);
    while (pNext && pNext->pNext)
    {
        if (pNext->pNext->sType == sType)
        {
            pNext->pNext = pNext->pNext->pNext;
        }
        pNext = reinterpret_cast<VkBaseOutStructure*>(pNext->pNext);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// HasInstanceExtension
//------------------------------------------------------------------------------
static bool HasInstanceExtension(VkInstance instance, const char* pName)
{
    NV_ASSERT(instance != VK_NULL_HANDLE);
    const auto& map = s_InstanceExtensions[instance];
    return map.find(std::string(pName)) != map.end();
}

//------------------------------------------------------------------------------
// HasDeviceExtension
//------------------------------------------------------------------------------
static bool HasDeviceExtension(VkDevice device, const char* pName)
{
    NV_ASSERT(device != VK_NULL_HANDLE);
    const auto& map = s_DeviceExtensions[device];
    return map.find(std::string(pName)) != map.end();
}

//------------------------------------------------------------------------------
// GetOverrideKey
//------------------------------------------------------------------------------
static OverrideKey GetOverrideKey(VkSwapchainKHR swapchain, uint32_t index)
{
    uint64_t h1 = (uint64_t)swapchain << 32;
    uint64_t h2 = (uint64_t)index;
    return h1 | h2;
}

//------------------------------------------------------------------------------
// GetOverrideOrReal<T>
//------------------------------------------------------------------------------
template <typename T, typename FnGet>
T GetActive(OverrideKey key, T object, const FnGet& fn)
{
#if defined(VKSC_VERSION_1_0)
    // For VulkanSC we don't use overrides
    return object;
#else
    // There always need to be an override key set
    NV_ASSERT(key != 0);

    // Make sure an override is active
    auto itrOverrideObjects = s_OverrideKeyToObjectOverrideMap.find(key);
    if (itrOverrideObjects == s_OverrideKeyToObjectOverrideMap.end())
    {
        return object;
    }

    // Not an override
    const std::map<T, T>* pSetOverrides = fn(itrOverrideObjects->second);
    auto itrView = pSetOverrides->find(object);
    if (itrView == pSetOverrides->end())
    {
        return object;
    }

    // Return override
    return itrView->second;
#endif
}

//------------------------------------------------------------------------------
// GetActive_Image
//------------------------------------------------------------------------------
static VkImage GetActive_Image(OverrideKey key, VkImage image)
{
    return GetActive(key, image, [](const std::unique_ptr<ObjectOverrideMap>& spObjects) {
        return &spObjects->images;
    });
}

//------------------------------------------------------------------------------
// GetActive_ImageView
//------------------------------------------------------------------------------
static VkImageView GetActive_ImageView(OverrideKey key, VkImageView imageView)
{
    return GetActive(key, imageView, [](const std::unique_ptr<ObjectOverrideMap>& spObjects) {
        return &spObjects->imageViews;
    });
}

//------------------------------------------------------------------------------
// GetActive_Framebufer
//------------------------------------------------------------------------------
static VkFramebuffer GetActive_Framebuffer(OverrideKey key, VkFramebuffer framebuffer)
{
    return GetActive(key, framebuffer, [](const std::unique_ptr<ObjectOverrideMap>& spObjects) {
        return &spObjects->framebuffers;
    });
}

//------------------------------------------------------------------------------
// GetActive_Sempahore
//------------------------------------------------------------------------------
static VkSemaphore GetActive_Sempahore(uint32_t bufferIdx, VkSemaphore semaphore)
{
    if (semaphore == VK_NULL_HANDLE)
    {
        return VK_NULL_HANDLE;
    }

    if (bufferIdx == 0)
    {
        return semaphore;
    }
    else
    {
        auto itr = s_SemaphoreOverrides.find(semaphore);
        NV_ASSERT(itr != s_SemaphoreOverrides.end());
        return itr->second[bufferIdx - 1];
    }
}

//------------------------------------------------------------------------------
// GetActive_Fence
//------------------------------------------------------------------------------
static VkFence GetActive_Fence(uint32_t bufferIdx, VkFence fence)
{
    if (fence == VK_NULL_HANDLE)
    {
        return VK_NULL_HANDLE;
    }

    if (bufferIdx == 0)
    {
        return fence;
    }
    else
    {
        auto itr = s_FenceOverrides.find(fence);
        NV_ASSERT(itr != s_FenceOverrides.end());
        return itr->second[bufferIdx - 1];
    }
}

//------------------------------------------------------------------------------
// GetActive_CommandBuffer
//------------------------------------------------------------------------------
static VkCommandBuffer GetActive_CommandBuffer(uint32_t bufferIdx, VkCommandBuffer commandBuffer)
{
    if (commandBuffer == VK_NULL_HANDLE)
    {
        return VK_NULL_HANDLE;
    }

    if (bufferIdx == 0)
    {
        return commandBuffer;
    }
    else
    {
        auto itr = s_CommandBufferOverrides.find(commandBuffer);
        NV_ASSERT(itr != s_CommandBufferOverrides.end());
        return itr->second[bufferIdx - 1];
    }
}

//------------------------------------------------------------------------------
// GetActive_DescriptorSet
//------------------------------------------------------------------------------
static VkDescriptorSet GetActive_DescriptorSet(uint32_t bufferIdx, VkDescriptorSet set)
{
    if (set == VK_NULL_HANDLE)
    {
        return VK_NULL_HANDLE;
    }

    if (bufferIdx == 0)
    {
        return set;
    }
    else
    {
        auto itr = s_DescriptorSetOverrides.find(set);
        NV_ASSERT(itr != s_DescriptorSetOverrides.end());
        return itr->second[bufferIdx - 1];
    }
}

//------------------------------------------------------------------------------
// GetActive_DescriptorPool
//------------------------------------------------------------------------------
static VkDescriptorPool GetActive_DescriptorPool(uint32_t bufferIdx, VkDescriptorPool pool)
{
    if (pool == VK_NULL_HANDLE)
    {
        return VK_NULL_HANDLE;
    }

    if (bufferIdx == 0)
    {
        return pool;
    }
    else
    {
        auto itr = s_DescriptorPoolOverrides.find(pool);
        NV_ASSERT(itr != s_DescriptorPoolOverrides.end());
        return itr->second[bufferIdx - 1];
    }
}

//------------------------------------------------------------------------------
// GetCommandPool
//------------------------------------------------------------------------------
static VkCommandPool GetCommandPool(VkDevice device, uint32_t queueFamilyIndex)
{
    // Unique {Device, QueueFamilyIndex} set
    using PoolKey = std::tuple<VkDevice, uint32_t>;

    // Lazily created per-device command pool
    static std::map<PoolKey, VkCommandPool> s_commandPools;

    // Unique pool key
    PoolKey key = std::tie(device, queueFamilyIndex);

    // Check cache
    auto itr = s_commandPools.find(key);
    if (itr != s_commandPools.end())
    {
        return itr->second;
    }

    // Create pool
    VkCommandPool pool = VK_NULL_HANDLE;
    VkCommandPoolCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
#if defined(VKSC_VERSION_1_0)
    VkCommandPoolMemoryReservationCreateInfo memoryReservationInfo = GetDefaultCommandPoolMemoryReservationInfo();
    createInfo.pNext = &memoryReservationInfo;
#endif
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    createInfo.queueFamilyIndex = queueFamilyIndex;
    NV_VK_VALIDATE(vkCreateCommandPool(device, &createInfo, nullptr, &pool));

    // Insert into cache
    s_commandPools[key] = pool;

    // Return new pool
    return pool;
}

//------------------------------------------------------------------------------
// CountBits
//------------------------------------------------------------------------------
static uint32_t CountBits(VkFlags flags)
{
    uint32_t count = 0;
    while (flags)
    {
        count += flags & 1;
        flags >>= 1;
    }
    return count;
};

//------------------------------------------------------------------------------
// GetQueue
//------------------------------------------------------------------------------
static VkQueue GetQueue(VkDevice device, uint32_t queueFamilyIndex)
{
    VkQueue queue = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
    return queue;
}

//------------------------------------------------------------------------------
// GetQueueFamilyWithFlagBit
//------------------------------------------------------------------------------
static uint32_t GetQueueFamilyWithFlagBit(VkDevice device, VkQueueFlags flags)
{
    auto itr = s_DeviceQueues.find(device);
    NV_ASSERT(itr != s_DeviceQueues.end());
    const auto& queues = itr->second;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(s_DeviceToPhysicalDeviceMap[device], &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> vecQueueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(s_DeviceToPhysicalDeviceMap[device], &queueFamilyCount, vecQueueFamilyProperties.data());
    for (uint32_t queueFamilyIdx = 0; queueFamilyIdx < queueFamilyCount; queueFamilyIdx++)
    {
        // Skip this queue if not valid
        if (queues.find(queueFamilyIdx) == queues.end())
        {
            continue;
        }

        const VkQueueFamilyProperties& queueFamilyProperties = vecQueueFamilyProperties[queueFamilyIdx];
        const bool hasFlags = (queueFamilyProperties.queueFlags & flags) == flags;
        if (queueFamilyProperties.queueCount > 0 && hasFlags)
        {
            return queueFamilyIdx;
        }
    }
    return VK_QUEUE_FAMILY_IGNORED;
}

//------------------------------------------------------------------------------
// GetQueueWithFlagBit
//------------------------------------------------------------------------------
static VkQueue GetQueueWithFlagBit(VkDevice device, VkQueueFlags flags)
{
    uint32_t queueFamilyIdx = GetQueueFamilyWithFlagBit(device, flags);
    if (queueFamilyIdx == VK_QUEUE_FAMILY_IGNORED)
    {
        return VK_NULL_HANDLE;
    }

    VkQueue deviceQueue = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamilyIdx, 0, &deviceQueue);
    return deviceQueue;
}

//------------------------------------------------------------------------------
// FindMemoryIndices
//------------------------------------------------------------------------------
static std::vector<uint32_t> FindMemoryIndices(const VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t memoryTypeBits, VkMemoryPropertyFlags properties)
{
    std::vector<uint32_t> indices;

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {

        const bool hasProperty = ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties);
        if (!hasProperty)
        {
            continue;
        }

        if (memoryTypeBits & (1 << i))
        {
            indices.push_back(int32_t(i));
        }
    }

    return indices;
};

//------------------------------------------------------------------------------
// MemoryPropertyFlagsToString
//------------------------------------------------------------------------------
static std::string MemoryPropertyFlagsToString(VkMemoryPropertyFlags bits)
{
    if (bits == 0)
    {
        return "0";
    }

    std::stringstream ss;

    if (bits & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    {
        ss << "DEVICE_LOCAL";
        bits &= ~VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        ss << "HOST_VISIBLE";
        bits &= ~VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
    {
        ss << "HOST_COHERENT";
        bits &= ~VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
    {
        ss << "HOST_CACHED";
        bits &= ~VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
    {
        ss << "LAZILY_ALLOCATED";
        bits &= ~VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_PROPERTY_PROTECTED_BIT)
    {
        ss << "PROTECTED";
        bits &= ~VK_MEMORY_PROPERTY_PROTECTED_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits != 0)
    {
        ss << "0x" << std::hex << bits;
    }

    return ss.str();
}

//------------------------------------------------------------------------------
// MemoryHeapFlagBitsToString
//------------------------------------------------------------------------------
static std::string MemoryHeapFlagBitsToString(VkMemoryHeapFlags bits)
{
    if (bits == 0)
    {
        return "0";
    }

    std::stringstream ss;

    if (bits & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
    {
        ss << "VK_MEMORY_HEAP_DEVICE_LOCAL_BIT";
        bits &= ~VK_MEMORY_HEAP_DEVICE_LOCAL_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT)
    {
        ss << "VK_MEMORY_HEAP_MULTI_INSTANCE_BIT";
        bits &= ~VK_MEMORY_HEAP_MULTI_INSTANCE_BIT;
        if (bits != 0)
        {
            ss << " | ";
        }
    }

    if (bits != 0)
    {
        ss << "0x" << std::hex << bits;
    }

    return ss.str();
}

//------------------------------------------------------------------------------
// PatchBufferMemory
//------------------------------------------------------------------------------
static uint32_t PatchBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory& memory, VkDeviceSize& memoryOffset)
{
    // JIT allocation info if needed
    VmaAllocationCreateInfo createInfo = {};

    // Get memory requirements
    const MemoryRequirements& memoryRequirements = [&] {
        auto itr = s_BufferMemoryRequirements.find(buffer);
        NV_ASSERT(itr != s_BufferMemoryRequirements.end());
        return itr->second;
    }();

    // Get meta information about memory
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // If using this setting memory should always be null the memory coming in is a
    // just a lookup key.
    if (s_UseReplayManagedMemoryAllocations)
    {
        NV_ASSERT(!memoryInfo.isAllocated);
        createInfo = GetAllocationCreateInfoForMemory(memory);
        memory = VK_NULL_HANDLE;
    }
    else if (s_SawMemoryTypeMismatch)
    {
        if (!memoryInfo.isAllocated || !CheckBindTimeMemoryRequirements(memoryRequirements, memory, memoryOffset))
        {
            createInfo = GetAllocationCreateInfoForMemory(memory);
            memory = VK_NULL_HANDLE;
        }
    };

    // Memory used by this bind was incompatible; get our own
    if (memory == VK_NULL_HANDLE)
    {
        // Allocate memory for this image
        VmaAllocator allocator = s_Allocators[device];
        VmaAllocation allocation = VK_NULL_HANDLE;
        VmaAllocationInfo allocationInfo;
        VkResult result = vmaAllocateMemoryForBuffer(allocator, buffer, &createInfo, &allocation, &allocationInfo);
        NV_THROW_IF(result != VK_SUCCESS, "Failed to pool allocate buffer");

        // Log this special case
        NV_LOG("NOTE: Buffer (%s) allocated in replay managed memory not used by original capture", GetObjectName(buffer).c_str());

        // Log information
        s_VmaBufferInfo[buffer] = VmaInfo{ allocator, allocation, allocationInfo };

        // Patch up bind information and memory index
        memory = allocationInfo.deviceMemory;
        memoryOffset = allocationInfo.offset;
        return allocationInfo.memoryType;
    }

    // Get memoryTypeIndex from real memory used
    return memoryInfo.allocateInfo.memoryTypeIndex;
}

//------------------------------------------------------------------------------
// PatchImageMemory
//------------------------------------------------------------------------------
static uint32_t PatchImageMemory(VkDevice device, VkImage image, VkDeviceMemory& memory, VkDeviceSize& memoryOffset)
{
    // JIT allocation info if needed
    VmaAllocationCreateInfo createInfo = {};

    // Get memory requirements
    const MemoryRequirements& memoryRequirements = [&] {
        auto itr = s_ImageMemoryRequirements.find(image);
        NV_ASSERT(itr != s_ImageMemoryRequirements.end());
        return itr->second;
    }();

    // Get meta information about memory
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // If using this setting memory should always be null the memory coming in is a
    // just a lookup key.
    if (s_UseReplayManagedMemoryAllocations)
    {
        NV_ASSERT(!memoryInfo.isAllocated);
        createInfo = GetAllocationCreateInfoForMemory(memory);
        memory = VK_NULL_HANDLE;
    }
    else if (s_SawMemoryTypeMismatch)
    {
        if (!memoryInfo.isAllocated || !CheckBindTimeMemoryRequirements(memoryRequirements, memory, memoryOffset))
        {
            createInfo = GetAllocationCreateInfoForMemory(memory);
            memory = VK_NULL_HANDLE;
        }
    };

    // Memory used by this bind was incompatible; get our own
    if (memory == VK_NULL_HANDLE)
    {

        // Allocate memory for this image
        VmaAllocator allocator = s_Allocators[device];
        VmaAllocation allocation;
        VmaAllocationInfo allocationInfo;
        VkResult result = vmaAllocateMemoryForImage(allocator, image, &createInfo, &allocation, &allocationInfo);
        NV_THROW_IF(result != VK_SUCCESS, "Failed to pool allocate image");

        // Log this special case
        NV_LOG("NOTE: Image (%s) allocated in replay managed memory not used by original capture", GetObjectName(image).c_str());

        // Patch up bind information and memory index
        memory = allocationInfo.deviceMemory;
        memoryOffset = allocationInfo.offset;
        return allocationInfo.memoryType;
    }

    // Get memoryTypeIndex from real memory used
    return memoryInfo.allocateInfo.memoryTypeIndex;
}

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// PatchAccelerationStructureMemoryNV
//------------------------------------------------------------------------------
static uint32_t PatchAccelerationStructureMemoryNV(VkDevice device, VkBindAccelerationStructureMemoryInfoNV& info)
{
    // Get meta information about memory
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(info.memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // Memory used by this bind was incompatible; get our own
    if (!memoryInfo.isAllocated)
    {

        // JIT allocation info if needed
        VmaAllocationCreateInfo createInfo = GetAllocationCreateInfoForMemory(info.memory);

        // Lookup object
        const AccelerationStructureNV* pAccelerationStructureNV = s_AccelerationStructuresNV.Lookup(info.accelerationStructure);
        VkMemoryRequirements memoryRequirements = pAccelerationStructureNV->GetMemoryRequirements();

        // Allocate memory for this image
        VmaAllocator allocator = s_Allocators[device];
        VmaAllocation allocation = VK_NULL_HANDLE;
        VmaAllocationInfo allocationInfo;
        VkResult result = vmaAllocateMemory(allocator, &memoryRequirements, &createInfo, &allocation, &allocationInfo);
        NV_THROW_IF(result != VK_SUCCESS, "Failed to pool allocate image");

        // Log this special case
        NV_LOG("NOTE: Acceleration structure (%s) allocated in replay managed memory not used by original capture", GetObjectName(pAccelerationStructureNV->accelerationStructureNV).c_str());

        // Patch up bind information and memory index
        info.memory = allocationInfo.deviceMemory;
        info.memoryOffset = allocationInfo.offset;
        return allocationInfo.memoryType;
    }

    // Get memoryTypeIndex from real memory used
    return memoryInfo.allocateInfo.memoryTypeIndex;
}
#endif

//------------------------------------------------------------------------------
// AllowGetQueryPoolResult
//------------------------------------------------------------------------------
static bool AllowGetQueryPoolResult(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    // Disabled via option
    if (s_DisableCopyQueryPoolResults)
    {
        return false;
    }

#if defined(VK_KHR_video_encode_queue)
    // Video encoding always require Query commands, or it crashes
    auto itrCI = s_QueryPoolToCreateInfo.find(queryPool);
    if (itrCI != s_QueryPoolToCreateInfo.end() && itrCI->second->queryType == VK_QUERY_TYPE_VIDEO_ENCODE_BITSTREAM_BUFFER_RANGE_KHR)
    {
        return true;
    }
#endif

    // Pool was never reset; this will probably hang
    auto itr = s_QueryPoolResetInFrame.find(queryPool);
    if (itr == s_QueryPoolResetInFrame.end())
    {
        return false;
    }

    // Any of the range was not written, probably hang
    auto itrRange = s_QueryPoolAvailableRanges.find(queryPool);
    if (itrRange == s_QueryPoolAvailableRanges.end())
    {
        return false;
    }
    for (uint32_t i = 0; i != queryCount; i++)
    {
        if (!itrRange->second[firstQuery + i])
        {
            return false;
        }
    }

    // Should be safe to use
    return true;
}

//------------------------------------------------------------------------------
// AllowCmdResetQueryPool
//------------------------------------------------------------------------------
static bool AllowCmdResetQueryPool(VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    return AllowGetQueryPoolResult(queryPool, firstQuery, queryCount);
}

//------------------------------------------------------------------------------
// AllowCmdCopyQueryPoolResults
//------------------------------------------------------------------------------
static bool AllowCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    // Disabled via option
    if (s_DisableCopyQueryPoolResults)
    {
        return false;
    }

#if defined(VK_KHR_video_encode_queue)
    // Video encoding always require Query commands, or it crashes
    auto itrCI = s_QueryPoolToCreateInfo.find(queryPool);
    if (itrCI != s_QueryPoolToCreateInfo.end() && itrCI->second->queryType == VK_QUERY_TYPE_VIDEO_ENCODE_BITSTREAM_BUFFER_RANGE_KHR)
    {
        return true;
    }
#endif

    // If any of the range was not written, probably hang
    auto itrRange = s_QueryPoolAvailableRanges.find(queryPool);
    if (itrRange == s_QueryPoolAvailableRanges.end())
    {
        return false;
    }
    for (uint32_t i = 0; i != queryCount; i++)
    {
        if (!itrRange->second[firstQuery + i])
        {
            return false;
        }
    }

    // If the pool was reset in frame we are OK
    auto itrPool = s_QueryPoolResetInFrame.find(queryPool);
    if (itrPool != s_QueryPoolResetInFrame.end())
    {
        return true;
    }

    // If we have recorded (but not yet submitted) a clear we are OK as well
    auto itrCmdBuffer = s_CommandBufferToQueryPoolReset.find(commandBuffer);
    if (itrCmdBuffer != s_CommandBufferToQueryPoolReset.end())
    {
        return true;
    }

    // Not safe to do this copy; will hang!
    return false;
}

//------------------------------------------------------------------------------
// IsQueryAvailable
//------------------------------------------------------------------------------
static bool IsQueryAvailable(VkQueryPool queryPool, uint32_t query)
{
    // Find query pool
    auto itrRange = s_QueryPoolAvailableRanges.find(queryPool);
    if (itrRange == s_QueryPoolAvailableRanges.end())
    {
        return false;
    }

    // Check if it is valid query
    if (query >= s_QueryPoolAvailableRanges[queryPool].size())
    {
        return false;
    }

    return s_QueryPoolAvailableRanges[queryPool][query] == VK_TRUE;
}

//------------------------------------------------------------------------------
// GetTexelSizeInBitsForUncompressedColorFormat
//------------------------------------------------------------------------------
static uint32_t GetTexelSizeInBitsForUncompressedColorFormat(VkFormat format)
{
    switch (format)
    {
    case VK_FORMAT_R4G4_UNORM_PACK8:
    case VK_FORMAT_R8_SINT:
    case VK_FORMAT_R8_SNORM:
    case VK_FORMAT_R8_SRGB:
    case VK_FORMAT_R8_SSCALED:
    case VK_FORMAT_R8_UINT:
    case VK_FORMAT_R8_UNORM:
    case VK_FORMAT_R8_USCALED:
        return 8;
    case VK_FORMAT_A1R5G5B5_UNORM_PACK16:
    case VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT:
    case VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT:
    case VK_FORMAT_B4G4R4A4_UNORM_PACK16:
    case VK_FORMAT_B5G5R5A1_UNORM_PACK16:
    case VK_FORMAT_B5G6R5_UNORM_PACK16:
    case VK_FORMAT_R16_SFLOAT:
    case VK_FORMAT_R16_SINT:
    case VK_FORMAT_R16_SNORM:
    case VK_FORMAT_R16_SSCALED:
    case VK_FORMAT_R16_UINT:
    case VK_FORMAT_R16_UNORM:
    case VK_FORMAT_R16_USCALED:
    case VK_FORMAT_R4G4B4A4_UNORM_PACK16:
    case VK_FORMAT_R5G5B5A1_UNORM_PACK16:
    case VK_FORMAT_R5G6B5_UNORM_PACK16:
    case VK_FORMAT_R8G8_SINT:
    case VK_FORMAT_R8G8_SNORM:
    case VK_FORMAT_R8G8_SRGB:
    case VK_FORMAT_R8G8_SSCALED:
    case VK_FORMAT_R8G8_UINT:
    case VK_FORMAT_R8G8_UNORM:
    case VK_FORMAT_R8G8_USCALED:
        return 16;
    case VK_FORMAT_B8G8R8_SINT:
    case VK_FORMAT_B8G8R8_SNORM:
    case VK_FORMAT_B8G8R8_SRGB:
    case VK_FORMAT_B8G8R8_SSCALED:
    case VK_FORMAT_B8G8R8_UINT:
    case VK_FORMAT_B8G8R8_UNORM:
    case VK_FORMAT_B8G8R8_USCALED:
    case VK_FORMAT_R8G8B8_SINT:
    case VK_FORMAT_R8G8B8_SNORM:
    case VK_FORMAT_R8G8B8_SRGB:
    case VK_FORMAT_R8G8B8_SSCALED:
    case VK_FORMAT_R8G8B8_UINT:
    case VK_FORMAT_R8G8B8_UNORM:
    case VK_FORMAT_R8G8B8_USCALED:
        return 24;
    case VK_FORMAT_A2B10G10R10_SINT_PACK32:
    case VK_FORMAT_A2B10G10R10_SNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_SSCALED_PACK32:
    case VK_FORMAT_A2B10G10R10_UINT_PACK32:
    case VK_FORMAT_A2B10G10R10_UNORM_PACK32:
    case VK_FORMAT_A2B10G10R10_USCALED_PACK32:
    case VK_FORMAT_A2R10G10B10_SINT_PACK32:
    case VK_FORMAT_A2R10G10B10_SNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_SSCALED_PACK32:
    case VK_FORMAT_A2R10G10B10_UINT_PACK32:
    case VK_FORMAT_A2R10G10B10_UNORM_PACK32:
    case VK_FORMAT_A2R10G10B10_USCALED_PACK32:
    case VK_FORMAT_A8B8G8R8_SINT_PACK32:
    case VK_FORMAT_A8B8G8R8_SNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_SRGB_PACK32:
    case VK_FORMAT_A8B8G8R8_SSCALED_PACK32:
    case VK_FORMAT_A8B8G8R8_UINT_PACK32:
    case VK_FORMAT_A8B8G8R8_UNORM_PACK32:
    case VK_FORMAT_A8B8G8R8_USCALED_PACK32:
    case VK_FORMAT_B10G11R11_UFLOAT_PACK32:
    case VK_FORMAT_B8G8R8A8_SINT:
    case VK_FORMAT_B8G8R8A8_SNORM:
    case VK_FORMAT_B8G8R8A8_SRGB:
    case VK_FORMAT_B8G8R8A8_SSCALED:
    case VK_FORMAT_B8G8R8A8_UINT:
    case VK_FORMAT_B8G8R8A8_UNORM:
    case VK_FORMAT_B8G8R8A8_USCALED:
    case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32:
    case VK_FORMAT_R16G16_SFLOAT:
    case VK_FORMAT_R16G16_SINT:
    case VK_FORMAT_R16G16_SNORM:
    case VK_FORMAT_R16G16_SSCALED:
    case VK_FORMAT_R16G16_UINT:
    case VK_FORMAT_R16G16_UNORM:
    case VK_FORMAT_R16G16_USCALED:
    case VK_FORMAT_R32_SFLOAT:
    case VK_FORMAT_R32_SINT:
    case VK_FORMAT_R32_UINT:
    case VK_FORMAT_R8G8B8A8_SINT:
    case VK_FORMAT_R8G8B8A8_SNORM:
    case VK_FORMAT_R8G8B8A8_SRGB:
    case VK_FORMAT_R8G8B8A8_SSCALED:
    case VK_FORMAT_R8G8B8A8_UINT:
    case VK_FORMAT_R8G8B8A8_UNORM:
    case VK_FORMAT_R8G8B8A8_USCALED:
        return 32;
    case VK_FORMAT_R16G16B16_SFLOAT:
    case VK_FORMAT_R16G16B16_SINT:
    case VK_FORMAT_R16G16B16_SNORM:
    case VK_FORMAT_R16G16B16_SSCALED:
    case VK_FORMAT_R16G16B16_UINT:
    case VK_FORMAT_R16G16B16_UNORM:
    case VK_FORMAT_R16G16B16_USCALED:
        return 48;
    case VK_FORMAT_R16G16B16A16_SFLOAT:
    case VK_FORMAT_R16G16B16A16_SINT:
    case VK_FORMAT_R16G16B16A16_SNORM:
    case VK_FORMAT_R16G16B16A16_SSCALED:
    case VK_FORMAT_R16G16B16A16_UINT:
    case VK_FORMAT_R16G16B16A16_UNORM:
    case VK_FORMAT_R16G16B16A16_USCALED:
    case VK_FORMAT_R32G32_SFLOAT:
    case VK_FORMAT_R32G32_SINT:
    case VK_FORMAT_R32G32_UINT:
    case VK_FORMAT_R64_SFLOAT:
    case VK_FORMAT_R64_SINT:
    case VK_FORMAT_R64_UINT:
        return 64;
    case VK_FORMAT_R32G32B32_SFLOAT:
    case VK_FORMAT_R32G32B32_SINT:
    case VK_FORMAT_R32G32B32_UINT:
        return 96;
    case VK_FORMAT_R32G32B32A32_SFLOAT:
    case VK_FORMAT_R32G32B32A32_SINT:
    case VK_FORMAT_R32G32B32A32_UINT:
    case VK_FORMAT_R64G64_SFLOAT:
    case VK_FORMAT_R64G64_SINT:
    case VK_FORMAT_R64G64_UINT:
        return 128;
    case VK_FORMAT_R64G64B64_SFLOAT:
    case VK_FORMAT_R64G64B64_SINT:
    case VK_FORMAT_R64G64B64_UINT:
        return 192;
    case VK_FORMAT_R64G64B64A64_SFLOAT:
    case VK_FORMAT_R64G64B64A64_SINT:
    case VK_FORMAT_R64G64B64A64_UINT:
        return 256;
    default:
        break;
    }

    // Depth/Stencil formats, compressed formats and multi-planar formats are not handled here
    return 0;
}

//------------------------------------------------------------------------------
// VulkanHelper_ExecuteCommands
//------------------------------------------------------------------------------
VkResult VulkanHelper_ExecuteCommands(VkDevice device, VkQueueFlags queueFlags, std::function<void(VkCommandBuffer)>&& fnWork)
{
    const uint32_t deviceMask = 0;
    return VulkanHelper_ExecuteCommands(device, deviceMask, queueFlags, std::move(fnWork));
}

//------------------------------------------------------------------------------
// VulkanHelper_ExecuteCommands (with device mask)
//------------------------------------------------------------------------------
VkResult VulkanHelper_ExecuteCommands(VkDevice device, uint32_t deviceMask, VkQueueFlags queueFlags, std::function<void(VkCommandBuffer)>&& fnWork)
{
    // Create command buffer
    VkCommandBuffer cmdBuffer = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = GetCommandPool(device, 0);
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = 1;
    NV_VK_VALIDATE(vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &cmdBuffer));

    // Begin command buffer
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    NV_VK_VALIDATE(vkBeginCommandBuffer(cmdBuffer, &beginInfo));

    // Call into user function
    fnWork(cmdBuffer);

    // End command buffer
    NV_VK_VALIDATE(vkEndCommandBuffer(cmdBuffer));

    // Submit info
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuffer;

    // Multi-GPU support
    VkDeviceGroupSubmitInfo deviceGroupSubmitInfo = {};
    if (deviceMask != 0)
    {
        deviceGroupSubmitInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
        deviceGroupSubmitInfo.commandBufferCount = 1;
        deviceGroupSubmitInfo.pCommandBufferDeviceMasks = &deviceMask;
        submitInfo.pNext = &deviceGroupSubmitInfo;
    }

    // Submit on queue
    const VkQueue queue = GetQueueWithFlagBit(device, queueFlags);
    NV_ASSERT(queue != VK_NULL_HANDLE);
    NV_VK_VALIDATE(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE));

    // Wait for command to finish
    NV_VK_VALIDATE(vkQueueWaitIdle(queue));

    // Done with command
    NV_VK_VALIDATE(vkResetCommandBuffer(cmdBuffer, 0));

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// ResourceUpdateHelper::RecordAndSubmitWork
//------------------------------------------------------------------------------
void WorkStreamer::RecordAndSubmitWork(uint32_t deviceMask, std::vector<WorkStreamer::FnWork>&& vecWork)
{
    // Create command buffer
    VkCommandBuffer cmdBuffer = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = m_pool;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandBufferCount = 1;
    NV_VK_VALIDATE(vkAllocateCommandBuffers(m_device, &commandBufferAllocateInfo, &cmdBuffer));
    m_vecCmdBuffers.push_back(cmdBuffer);

    // Begin command buffer
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    NV_VK_VALIDATE(vkBeginCommandBuffer(cmdBuffer, &beginInfo));

    // Call into user function
    for (const WorkStreamer::FnWork& fnWork : vecWork)
    {
        fnWork(cmdBuffer);
    }

    // End command buffer
    NV_VK_VALIDATE(vkEndCommandBuffer(cmdBuffer));

    // Submit info
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuffer;

    // Multi-GPU support
    VkDeviceGroupSubmitInfo deviceGroupSubmitInfo = {};
    if (deviceMask != 0)
    {
        deviceGroupSubmitInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO;
        deviceGroupSubmitInfo.commandBufferCount = 1;
        deviceGroupSubmitInfo.pCommandBufferDeviceMasks = &deviceMask;
        submitInfo.pNext = &deviceGroupSubmitInfo;
    }

    // Hold onto work
    m_vecInflightWork[m_slot] = std::move(vecWork);

    // Submit on queue
    const VkQueue queue = GetQueueWithFlagBit(m_device, m_transferFamilyIndex);
    NV_VK_VALIDATE(vkQueueSubmit(queue, 1, &submitInfo, m_fences[m_slot]));
}

//------------------------------------------------------------------------------
// ForceWaitForSignaledSemaphore
//------------------------------------------------------------------------------
static bool ForceWaitForSignaledSemaphore(VkDevice device, VkSemaphore semaphore, const char* pFunction)
{
    if (semaphore != VK_NULL_HANDLE)
    {
        SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(semaphore);
        if (semaphoreStatus.signaled)
        {
            VkSubmitInfo submitInfo = {};
            VkPipelineStageFlags pPipelineStageFlags[] = { VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT };
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.waitSemaphoreCount = 1;
            submitInfo.pWaitSemaphores = &semaphore;
            submitInfo.pWaitDstStageMask = pPipelineStageFlags;
            submitInfo.commandBufferCount = 0;
            submitInfo.pCommandBuffers = nullptr;
            submitInfo.signalSemaphoreCount = 0;
            submitInfo.pSignalSemaphores = nullptr;
            NV_VK_VALIDATE(vkQueueSubmit(GetQueue(device, 0), 1, &submitInfo, VK_NULL_HANDLE));
            semaphoreStatus.signaled = false;
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
// WaitForPendingFence
//------------------------------------------------------------------------------
static bool WaitForPendingFence(VkDevice device, VkFence fence, const char* pFunction)
{
    // NOTE: This fence is already an overridden fence

    if (fence != VK_NULL_HANDLE)
    {
        VULKAN_REPLAY_WRITE_LOCK();
        FenceStatus& fenceStatus = GetFenceStatus(fence);
        if (fenceStatus.signaled)
        {
            VkResult status = vkGetFenceStatus(device, fence);
            if (status != VK_SUCCESS)
            {
                auto waitFunc = [&]() {
                    while (vkWaitForFences(device, 1, &fence, VK_TRUE, NV_DEFAULT_FENCE_WAIT_NS) != VK_SUCCESS)
                    {
                        NV_LOG("[%s] Waiting on fence...", pFunction);
                    }
                };
                NV_TIMED_EXEC(pFunction, waitFunc);
            }
            vkResetFences(device, 1, &fence);
            fenceStatus.signaled = false;
            return true;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// FlushRogueEvents
//------------------------------------------------------------------------------
static bool FlushRogueEvents(VkDevice device)
{
    // Bail if no rogue events have been collected.
    if (s_RogueEvents.empty())
    {
        return true;
    }

    // If we get to this point it means we are seeing the application trying
    // to reset an event we never saw set while having set events that are
    // never waited upon. This is dangerous because it potentially means there
    // is a cross-frame dependency related to event handling. As such, we need
    // to wait on all of these "rogue events" as we must assume there is a
    // dependency we didn't obverse within the scope of the captured frame.
    NV_TIMED_EXEC("Rogue Events", [=]() {
        vkDeviceWaitIdle(device);
    });
    s_RogueEvents.clear();
    return true;
}

//------------------------------------------------------------------------------
// HandleEvents
//------------------------------------------------------------------------------
static bool HandleEvents(VkDevice device, std::vector<VkCommandBuffer> vecCommandBuffers)
{
    // Nothing to do if we never saw a wait
    if (!s_SawWaitEvent)
    {
        return true;
    }

    // Collect events associated with these command buffers
    std::set<VkEvent> setSetEvents;
    std::set<VkEvent> setResetEvents;
    std::set<VkEvent> setWaitEvents;
    bool hasEvents = false;
    for (VkCommandBuffer commandBuffer : vecCommandBuffers)
    {
        for (VkEvent event : s_CommandBufferSetEvents[commandBuffer])
        {
            setSetEvents.insert(event);
            hasEvents = true;
        }
        for (VkEvent event : s_CommandBufferResetEvents[commandBuffer])
        {
            setResetEvents.insert(event);
            hasEvents = true;
        }
        for (VkEvent event : s_CommandBufferWaitEvents[commandBuffer])
        {
            setWaitEvents.insert(event);
            hasEvents = true;
        }
    }

    // Bail if no events being used
    if (!hasEvents)
    {
        return true;
    }

    // Handle rogue events
    FlushRogueEvents(device);

    // Track active events that are in a "set" state following the execution
    // of this command buffer
    for (VkEvent setEvent : setSetEvents)
    {
        s_ActiveEvents.insert(setEvent);
    }

    // If an event is waited up either and we know it has been set, remove it
    // from the active list. If this event has not been set, we can force set
    // it to prevent a potential dead lock scenario.
    for (VkEvent waitEvent : setWaitEvents)
    {
        auto itr = s_ActiveEvents.find(waitEvent);
        if (itr != s_ActiveEvents.end())
        {
            s_ActiveEvents.erase(itr);
        }
        else
        {
            NV_LOG("WARNING: avoiding potential deadlock scenario waiting on event that is never set");
            vkSetEvent(device, waitEvent);
        }
    }

    // We can remove rogue events that have been waited upon
    if (!s_RogueEvents.empty())
    {
        for (VkEvent waitEvent : setWaitEvents)
        {
            auto itr = std::find(s_RogueEvents.begin(), s_RogueEvents.end(), waitEvent);
            if (itr != s_RogueEvents.end())
            {
                s_RogueEvents.erase(itr);
            }
        }
    }

    // If we are reseting an active event, remove it from the active list. If
    // we are reseting an event we don't think is active we have observed a
    // potential cross-frame synchronization issue and need to flush.
    for (VkEvent resetEvent : setResetEvents)
    {
        auto itr = s_ActiveEvents.find(resetEvent);
        if (itr != s_ActiveEvents.end())
        {
            s_ActiveEvents.erase(itr);
        }
    }

    return false;
}

//------------------------------------------------------------------------------
// HandleEvents
//------------------------------------------------------------------------------
static bool HandleEvents(VkDevice device, uint32_t submitCount, const VkSubmitInfo* pSubmits)
{
    // Collect command buffers
    std::vector<VkCommandBuffer> vecCommandBuffers;
    for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
    {
        for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferCount; commandBufferIdx++)
        {
            const VkCommandBuffer commandBuffer = pSubmits[submitIdx].pCommandBuffers[commandBufferIdx];
            vecCommandBuffers.push_back(commandBuffer);
        }
    }

    // Pass to common implementation
    return HandleEvents(device, vecCommandBuffers);
}

//------------------------------------------------------------------------------
// HandleEvents
//------------------------------------------------------------------------------
static bool HandleEvents(VkDevice device, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits)
{
    // Collect command buffers
    std::vector<VkCommandBuffer> vecCommandBuffers;
    for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
    {
        for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferInfoCount; commandBufferIdx++)
        {
            const VkCommandBuffer commandBuffer = pSubmits[submitIdx].pCommandBufferInfos[commandBufferIdx].commandBuffer;
            vecCommandBuffers.push_back(commandBuffer);
        }
    }

    // Pass to common implementation
    return HandleEvents(device, vecCommandBuffers);
}

//------------------------------------------------------------------------------
// WaitForCommandBuffer
//------------------------------------------------------------------------------
static bool WaitForCommandBuffer(VkCommandBuffer commandBuffer, const char* pFunction)
{
    auto itr = s_CommandBufferToFence.find(commandBuffer);
    if (itr != s_CommandBufferToFence.end())
    {
        VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];
        VkFence fence = itr->second;
        return WaitForPendingFence(device, fence, pFunction);
    }

    return false;
}

//------------------------------------------------------------------------------
// WaitForPendingResourceUpdates
//------------------------------------------------------------------------------
static bool WaitForPendingResourceUpdates(VkDevice device)
{
    return s_ResourceUpdateHelpers[device]->FinishWork();
}

//------------------------------------------------------------------------------
// CopyBuffer
//------------------------------------------------------------------------------
static VkResult CopyBuffer(VkDevice device, VkBuffer srcBuffer, VkDeviceSize srcOffset, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size)
{
    return VulkanHelper_ExecuteCommands(device, VK_QUEUE_TRANSFER_BIT, [=](VkCommandBuffer cmdBuffer) {
        VkBufferCopy region = {};
        region.srcOffset = srcOffset;
        region.dstOffset = dstOffset;
        region.size = size;
        vkCmdCopyBuffer(cmdBuffer, srcBuffer, dstBuffer, 1, &region);
    });
}

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// CreateAccelerationScratchBufferNV
//------------------------------------------------------------------------------
static ScopedVmaBuffer CreateAccelerationScratchBufferNV(VkDevice device, VkAccelerationStructureNV accelerationStructure)
{
    // Get size requirements for buffer
    const VkMemoryRequirements requirements = [&]() {
        VkAccelerationStructureMemoryRequirementsInfoNV memoryRequirementsInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV };
        memoryRequirementsInfo.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV;
        memoryRequirementsInfo.accelerationStructure = accelerationStructure;
        VkMemoryRequirements2 memoryRequirements2 = { VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 };
        vkGetAccelerationStructureMemoryRequirementsNV(device, &memoryRequirementsInfo, &memoryRequirements2);
        return memoryRequirements2.memoryRequirements;
    }();

    return ScopedVmaBuffer(s_Allocators[device], requirements.size, requirements.memoryTypeBits, VK_BUFFER_USAGE_RAY_TRACING_BIT_NV, VMA_MEMORY_USAGE_GPU_ONLY);
}

//------------------------------------------------------------------------------
// PatchGeometryInstanceNV
//------------------------------------------------------------------------------
bool PatchGeometryInstanceNV(VkDevice device, VkAccelerationStructureInstanceNV& instance)
{
    // Empty BLAS are OK
    if (instance.accelerationStructureReference == 0)
    {
        return true;
    }

    // See which acceleration structure this buffer originally referred to
    auto itr = s_AccelerationStructureAddressMapNV.find(instance.accelerationStructureReference);
    if (itr == s_AccelerationStructureAddressMapNV.end())
    {
        NV_MESSAGE("WARNING: Failed to remap BLAS handle 0x%016" PRIx64 ". Inserting null.", instance.accelerationStructureReference);
        instance.accelerationStructureReference = 0;
        return false;
    }
    const VkAccelerationStructureNV acclerationStructure = itr->second;
    NV_ASSERT(acclerationStructure != 0);

    // Get handle of that acceleration structure
    VkDeviceAddress address = 0;
    vkGetAccelerationStructureHandleNV(device, acclerationStructure, sizeof(VkDeviceAddress), &address);
    instance.accelerationStructureReference = uint64_t(address);
    return true;
}

//------------------------------------------------------------------------------
// PatchGeometryInstanceKHR
//------------------------------------------------------------------------------
bool PatchGeometryInstanceKHR(VkDevice device, VkAccelerationStructureInstanceKHR& instance)
{
    // Empty BLAS are OK
    if (instance.accelerationStructureReference == 0)
    {
        return true;
    }

    // See which acceleration structure this buffer originally referred to
    auto itr = s_AccelerationStructureAddressMapKHR.find(instance.accelerationStructureReference);
    if (itr == s_AccelerationStructureAddressMapKHR.end())
    {
        NV_MESSAGE("WARNING: Failed to remap BLAS reference: 0x%016" PRIx64 ".", instance.accelerationStructureReference);
        instance.accelerationStructureReference = 0;
        return false;
    }
    const VkAccelerationStructureKHR acclerationStructure = itr->second;
    NV_ASSERT(acclerationStructure != 0);

    // Make sure this BLAS was built
    auto itr2 = s_BuiltAccelerationStructuresKHR.find(acclerationStructure);
    if (itr2 == s_BuiltAccelerationStructuresKHR.end())
    {
        NV_MESSAGE("WARNING: BLAS wasn't built: %s", GetObjectName(acclerationStructure).c_str());
        instance.accelerationStructureReference = 0;
        return false;
    }

    // Get handle of that acceleration structure
    VkAccelerationStructureDeviceAddressInfoKHR info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR };
    info.accelerationStructure = acclerationStructure;
    VkDeviceAddress address = vkGetAccelerationStructureDeviceAddressKHR(device, &info);
    NV_ASSERT(address);
    instance.accelerationStructureReference = uint64_t(address);
    return true;
}

//------------------------------------------------------------------------------
// PatchInstanceBuffer
//------------------------------------------------------------------------------
template <Feature T_Feature>
VkResult PatchInstanceBuffer(VkCommandBuffer commandBuffer, uint32_t instanceCount, VkBuffer instanceBuffer, VkDeviceSize instanceOffset)
{
    // Buffer size
    const VkDeviceSize size = sizeof(VkAccelerationStructureInstanceKHR) * instanceCount;

    // We can cache patched allocations
    auto key = std::make_tuple(commandBuffer, instanceCount, instanceBuffer, instanceOffset);
    using InstanceBufferKey = decltype(key);

    // Get allocator
    VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];
    VmaAllocator allocator = s_Allocators[device];
    NV_ASSERT(allocator);

    // Get entry
    static std::map<InstanceBufferKey, ScopedVmaBuffer*> s_cache;

    VULKAN_REPLAY_WRITE_LOCK();
    auto itr = s_cache.find(key);
    if (itr == s_cache.end())
    {

        // Get patch buffer
        ScopedVmaBuffer* pPatchBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_RAY_TRACING_BIT_NV | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT), VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(pPatchBuffer);

        // Copy into scratch buffer
        NV_VK_VALIDATE(CopyBuffer(device, instanceBuffer, instanceOffset, pPatchBuffer->GetBuffer(), 0, size));

        // Map scratch data
        VkAccelerationStructureInstanceKHR* pDstInstanceData = reinterpret_cast<VkAccelerationStructureInstanceKHR*>(pPatchBuffer->Map());
        NV_ASSERT(pDstInstanceData);

        // Loop accelerations structures to patch up handles
        for (uint32_t i = 0; i < instanceCount; i++)
        {
            if (!PatchGeometryInstanceNV(device, pDstInstanceData[i]))
            {
                pPatchBuffer->Unmap();
                return VK_ERROR_INVALID_DEVICE_ADDRESS_EXT;
            }
        }

        // Unmap data
        pPatchBuffer->Unmap();

        // Add to cache
        itr = s_cache.insert(std::make_pair(key, pPatchBuffer)).first;
    }

    // Get patch buffer
    const VkBuffer patchedBuffer = itr->second->GetBuffer();
    NV_ASSERT(patchedBuffer != VK_NULL_HANDLE);

    // Write into command buffer
    VkBufferCopy region;
    region.srcOffset = 0;
    region.dstOffset = instanceOffset;
    region.size = size;
    vkCmdCopyBuffer(commandBuffer, patchedBuffer, instanceBuffer, 1, &region);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// GetRayTracingShaderGroupHandle
//------------------------------------------------------------------------------
template <Feature T_Feature>
std::vector<uint8_t> GetRayTracingShaderGroupHandle(VkDevice device, VkPipeline pipeline, uint32_t groupNumber)
{
    std::vector<uint8_t> handle(s_ShaderGroupHandleSize);

    VkResult result = VK_ERROR_UNKNOWN;

    switch (T_Feature)
    {
    case Feature::NV:
        result = vkGetRayTracingShaderGroupHandlesNV(device, pipeline, groupNumber, 1, s_ShaderGroupHandleSize, handle.data());
        break;
    case Feature::KHR:
        result = vkGetRayTracingShaderGroupHandlesKHR(device, pipeline, groupNumber, 1, s_ShaderGroupHandleSize, handle.data());
        break;
    default:
        break;
    }

    if (result != VK_SUCCESS)
    {
        return {};
    }

    return handle;
}

//------------------------------------------------------------------------------
// RemapShaderBindingTableNV
//------------------------------------------------------------------------------
template <Feature T_Feature>
bool RemapShaderBindingTable(VkDevice device, uint32_t traceRaysIdx, VkPipeline pipeline, RayTracingShaderBindingTableType type, VkDeviceSize size, uint8_t* pSBT, VkDeviceSize stride)
{
    // Category of invalid handles
    enum class InvalidHandleReason
    {
        Null,
        Invalid,
        BadType_General,
        BadType_Hit,
        FailedGet,
    };

    // Invalid range entry
    struct InvalidIdx
    {
        InvalidIdx(VkDeviceSize _idx, InvalidHandleReason _type)
            : idx(_idx)
            , type(_type)
        {
        }

        VkDeviceSize idx;
        InvalidHandleReason type;
    };

    // Keep track of invalid indices
    std::vector<InvalidIdx> vecInvalidIndices;

    // ToString helper
    auto InvalidHandleTypeToString = [](InvalidHandleReason reason) {
        switch (reason)
        {
        case InvalidHandleReason::Null:
            return "null handle";
        case InvalidHandleReason::Invalid:
            return "invalid handle";
        case InvalidHandleReason::BadType_General:
            return "missing expected general handle";
        case InvalidHandleReason::BadType_Hit:
            return "missing expected hit handle";
        case InvalidHandleReason::FailedGet:
            return "missing expected hit handle";
        default:
            break;
        }
        return "unknown reason";
    };

    // Print helper
    auto PrintInvalidRanges = [&](size_t start, size_t end) {
        const InvalidIdx& startIdx = vecInvalidIndices[start];
        const InvalidIdx& endIdx = vecInvalidIndices[end];
        if (startIdx.idx == endIdx.idx)
        {
            NV_LOG("WARNING: Invalid %s shader binding table entry @ %u (%s). Only a problem if accessed.", RayTracingShaderBindingTableTypeToString(type), uint32_t(startIdx.idx), InvalidHandleTypeToString(startIdx.type));
        }
        else
        {
            NV_LOG("WARNING: Invalid %s shader binding table entries @ %u-%u (%s). Only a problem if accessed.", RayTracingShaderBindingTableTypeToString(type), uint32_t(startIdx.idx), uint32_t(endIdx.idx), InvalidHandleTypeToString(startIdx.type));
        }
    };

    // Loop table entries to patch up handles
    for (VkDeviceSize offset = 0, idx = 0; offset < size; offset += stride, idx++)
    {

        // Lookup previously registered entry
        uint8_t* pOldHandle = pSBT + offset;

        // Helper to check for empty data
        auto IsEmpty = [&](const uint8_t* pHandle) -> bool {
            for (uint32_t i = 0; i < s_ShaderGroupHandleSize; i++)
            {
                if (pHandle[i] != 0)
                {
                    return false;
                }
            }
            return true;
        };

        // Ignore null handles
        if (IsEmpty(pOldHandle))
        {
            // NOTE: Don't bother logging; these are very common especially in NV_ray_tracing
            // vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::Null));
            continue;
        }

        // Create key
        RaytracingHandleKey key = RaytracingHandleKey(pipeline, s_ShaderGroupHandleSize, pOldHandle);

        // Make sure this handle exists
        auto itr = s_RayTracingHandleMap.find(key);
        if (itr == s_RayTracingHandleMap.end())
        {
            vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::Invalid));
            continue;
        }

        // Lookup pipeline and group associate with this old handle
        const VkPipeline currentPipeline = itr->second.pipeline;
        const uint32_t groupNumber = itr->second.groupNumber;

        // Validate
        auto itr2 = s_RayTracingGroupInfo.find(std::make_tuple(currentPipeline, groupNumber));
        if (itr2 != s_RayTracingGroupInfo.end())
        {
            const VkRayTracingShaderGroupCreateInfoKHR& groupInfo = itr2->second;
            switch (type)
            {
            case RayTracingShaderBindingTableType::RayGenShader:
            case RayTracingShaderBindingTableType::MissShader:
            case RayTracingShaderBindingTableType::CallableShader:
                if (groupInfo.generalShader == VK_SHADER_UNUSED_KHR)
                {
                    vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::BadType_General));
                }
                break;
            case RayTracingShaderBindingTableType::HitShader:
                if (groupInfo.anyHitShader == VK_SHADER_UNUSED_KHR && groupInfo.closestHitShader == VK_SHADER_UNUSED_KHR)
                {
                    vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::BadType_Hit));
                }
                break;
            default:
                break;
            }
        }
        else
        {
            vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::Invalid));
        }

        // Get new handle
        std::vector<uint8_t> newHandle = GetRayTracingShaderGroupHandle<T_Feature>(device, currentPipeline, groupNumber);
        if (newHandle.empty())
        {
            vecInvalidIndices.push_back(InvalidIdx(idx, InvalidHandleReason::FailedGet));
            continue;
        }

        // Patch up old handle
        memcpy(pOldHandle, newHandle.data(), s_ShaderGroupHandleSize);
    }

    // Print bad ranges
    size_t rangeStart = 0;
    for (size_t i = 0; i < vecInvalidIndices.size(); i++)
    {
        const InvalidIdx& thisIdx = vecInvalidIndices[i];
        if (i + 1 != vecInvalidIndices.size())
        {
            const InvalidIdx& nextIdx = vecInvalidIndices[i + 1];
            if (nextIdx.idx + 1 != thisIdx.idx || nextIdx.type != thisIdx.type)
            {
                PrintInvalidRanges(rangeStart, i);
                rangeStart = i;
            }
        }
        else
        {
            PrintInvalidRanges(rangeStart, i);
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// DoPatchShaderBindingTable
//------------------------------------------------------------------------------
template <Feature T_Feature>
VkBuffer DoPatchShaderBindingTable(uint32_t traceRaysIdx, RayTracingShaderBindingTableType type, VkCommandBuffer commandBuffer, VkDeviceSize stride, VkDeviceSize size, std::function<void(VkDevice device, VkBuffer dstBuffer, uint8_t* pDstData)> fnGetData)
{
    // No need to patch a buffer multiple times
    auto key = std::make_tuple(commandBuffer, traceRaysIdx, type);
    using ShaderBindTableKey = decltype(key);
    static std::map<ShaderBindTableKey, ScopedVmaBuffer*> s_cache;

    // Get allocator
    VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];
    VmaAllocator allocator = s_Allocators[device];
    NV_ASSERT(allocator);

    auto& tls = GetThreadState();
    VULKAN_REPLAY_WRITE_LOCK();

    // Get entry
    auto itr = s_cache.find(key);
    if (itr == s_cache.end())
    {

        // Current pipeline object
        std::tuple<VkCommandBuffer, VkPipelineBindPoint> pipelineKey = std::make_tuple(commandBuffer, VK_PIPELINE_BIND_POINT_RAY_TRACING_NV);
        VkPipeline pipeline = tls.currentBoundPipeline[pipelineKey];

        // Create patch buffer
        ScopedVmaBuffer* pPatchBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_RAY_TRACING_BIT_NV | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT), VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(pPatchBuffer);

        // Map scratch data
        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pPatchBuffer->Map());
        NV_ASSERT(pDstData);

        // Copy into scratch buffer
        fnGetData(device, pPatchBuffer->GetBuffer(), pDstData);

        // Remap the shader
        RemapShaderBindingTable<T_Feature>(device, traceRaysIdx, pipeline, type, size, pDstData, stride);

        // Unmap data
        pPatchBuffer->Unmap();

        // Add to cache
        itr = s_cache.insert(std::make_pair(key, pPatchBuffer)).first;
    }

    // Get patch buffer
    const VkBuffer patchedBuffer = itr->second->GetBuffer();
    NV_ASSERT(patchedBuffer != VK_NULL_HANDLE);
    return patchedBuffer;
}

//------------------------------------------------------------------------------
// PatchShaderBindTableNV
//------------------------------------------------------------------------------
VkBuffer PatchShaderBindingTableNV(uint32_t traceRaysIdx, RayTracingShaderBindingTableType type, VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkDeviceSize srcBufferOffset, VkDeviceSize stride)
{
    // Possible size of shader bind table
    VkDeviceSize size = s_BufferCreateInfo[srcBuffer].size - srcBufferOffset;

    // Handle zero stride which is just one entry
    if (stride == 0)
    {
        size = s_ShaderGroupHandleSize;
        stride = size;
    }

    // Patch shader binding table
    return DoPatchShaderBindingTable<Feature::NV>(traceRaysIdx, type, commandBuffer, stride, size, [=](VkDevice device, VkBuffer dstBuffer, uint8_t* pDstData) {
        NV_VK_VALIDATE(CopyBuffer(device, srcBuffer, srcBufferOffset, dstBuffer, 0, size));
    });
}

//------------------------------------------------------------------------------
// PatchShaderBindingTableKHR
//------------------------------------------------------------------------------
VkStridedDeviceAddressRegionKHR PatchShaderBindingTableKHR(uint32_t traceRaysIdx, RayTracingShaderBindingTableType type, VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR& region)
{
    if (region.deviceAddress == 0 || region.size == 0)
    {
        return region;
    }

    VkStridedDeviceAddressRegionKHR patchedRegion = region;

    VkDeviceSize offset = 0;
    VkBuffer buffer = s_BufferAddressManager.LookupBufferFromReplayAddress(region.deviceAddress, offset);

    // Patch shader binding table
    DoPatchShaderBindingTable<Feature::KHR>(traceRaysIdx, type, commandBuffer, region.stride, region.size, [=](VkDevice device, VkBuffer dstBuffer, uint8_t* pDstData) {
        NV_VK_VALIDATE(CopyBuffer(device, buffer, offset, dstBuffer, 0, region.size));
    });

    return patchedRegion;
}

//------------------------------------------------------------------------------
// PatchShaderBindingTableNV_FromDatabase
//------------------------------------------------------------------------------
static VkBuffer PatchShaderBindingTableNV_FromDatabase(uint32_t traceRaysIdx, RayTracingShaderBindingTableType type, VkCommandBuffer commandBuffer, Serialization::DATABASE_HANDLE handle, VkDeviceSize srcBufferOffset, VkDeviceSize stride)
{
    // Possible size of shader binding table
    VkDeviceSize size = VkDeviceSize(GetDatabase().GetSize(handle));
    size -= srcBufferOffset;

    // Handle zero stride which is just one entry
    if (stride == 0)
    {
        size = s_ShaderGroupHandleSize;
        stride = size;
    }

    // Patch shader binding table
    return DoPatchShaderBindingTable<Feature::NV>(traceRaysIdx, type, commandBuffer, stride, size, [=](VkDevice device, VkBuffer dstBuffer, uint8_t* pDstData) {
        // Load input from database
        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
        pSrcData += srcBufferOffset;

        // Copy in data
        memcpy(pDstData, pSrcData, size);
    });
}

//------------------------------------------------------------------------------
// ExtractShaderBindingTableKHR_FromDatabase
//------------------------------------------------------------------------------
static VkStridedDeviceAddressRegionKHR ExtractShaderBindingTableKHR_FromDatabase(VkDevice device, RayTracingShaderBindingTableType type, const VulkanHelper_ShaderBindTable* pShaderBindTable)
{
    // Empty data
    if (!pShaderBindTable || pShaderBindTable->entryCount == 0)
    {
        return {};
    }

    // Cache
    VULKAN_REPLAY_WRITE_LOCK();
    static std::map<const VulkanHelper_ShaderBindTable*, VkStridedDeviceAddressRegionKHR> s_sbtCache;
    auto itr = s_sbtCache.find(pShaderBindTable);
    if (itr == s_sbtCache.end())
    {

        // Stride
        const VkDeviceSize handleSize = s_ShaderGroupHandleSize;
        const VkDeviceSize inlineDataSize = pShaderBindTable->pEntries[0].inlineDataSize;
        const VkDeviceSize stride = handleSize + inlineDataSize;
        const VkDeviceSize bufferSize = stride * (type == RayTracingShaderBindingTableType::RayGenShader ? 1u : pShaderBindTable->entryCount);

        // Populate table
        ScopedVmaBuffer* pBuffer = new ScopedVmaBuffer(s_Allocators[device], bufferSize, VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR), VMA_MEMORY_USAGE_CPU_TO_GPU);
        uint8_t* pSbt = (uint8_t*)pBuffer->Map();
        for (uint32_t i = 0; i < pShaderBindTable->entryCount; i++)
        {
            const VulkanHelper_ShaderBindTableEntry& entry = pShaderBindTable->pEntries[i];
            if (entry.pipeline != VK_NULL_HANDLE)
            {
                VulkanReplay_GetRayTracingShaderGroupHandlesKHR(device, entry.pipeline, entry.group, 1, handleSize, pSbt);
            }
            else
            {
                NV_LOG("WARNING: Shader binding table entry %d references null pipeline; OK if unused", i);
            }
            pSbt += handleSize;
            memcpy(pSbt, entry.pInlineData, entry.inlineDataSize);
            pSbt += inlineDataSize;
        }
        pBuffer->Unmap();

        // Get address
        VkStridedDeviceAddressRegionKHR region = {};
        region.deviceAddress = GetBufferAddress(device, pBuffer->GetBuffer());
        region.size = bufferSize;
        region.stride = stride;

        // Add to cache
        itr = s_sbtCache.insert(std::make_pair(pShaderBindTable, region)).first;
    }

    return itr->second;
}

//------------------------------------------------------------------------------
// ExtractShaderBindingTableKHR_FromDatabase2
//------------------------------------------------------------------------------
static VkStridedDeviceAddressRegionKHR ExtractShaderBindingTableKHR_FromDatabase2(VkDevice device, RayTracingShaderBindingTableType type, const VkStridedDeviceAddressRegionKHR* pShaderBindTable)
{
    // Special struct the data is encoded as
    struct EncodedHandle
    {
        uint64_t pipelineId;
        uint64_t groupId;
        uint64_t __padding0;
        uint64_t __padding1;
    };

    // Empty data
    if (!pShaderBindTable || pShaderBindTable->size == 0)
    {
        return {};
    }

    // The device address has been hijacked as a database handle
    Serialization::DATABASE_HANDLE databaseHandle(static_cast<uint32_t>(pShaderBindTable->deviceAddress));
    if (databaseHandle == Serialization::DATABASE_HANDLE_INVALID)
    {
        return {};
    }

    bool hasLogged = false;

    // Cache
    VULKAN_REPLAY_WRITE_LOCK();
    static std::map<const VkStridedDeviceAddressRegionKHR*, VkStridedDeviceAddressRegionKHR> s_sbtCache;
    auto itr = s_sbtCache.find(pShaderBindTable);
    if (itr == s_sbtCache.end())
    {

        // Load data
        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, databaseHandle);
        NV_ASSERT(pSrcData);

        // Create buffer
        ScopedVmaBuffer* pDstBuffer = new ScopedVmaBuffer(s_Allocators[device], pShaderBindTable->size, VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR), VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(pDstBuffer);

        // Map for write
        uint8_t* pDstData = (uint8_t*)pDstBuffer->Map();
        NV_ASSERT(pDstData);

        // Copy in data
        memcpy(pDstData, pSrcData, pShaderBindTable->size);

        // Loop entries
        uint8_t* pDstDataEnd = pDstData + pShaderBindTable->size;
        uint32_t i = 0;
        while (pDstData + pShaderBindTable->stride <= pDstDataEnd)
        {

            // If we can't find the group then we'll have an unpopulated table entry, which is ok.
            EncodedHandle* pEncoded = reinterpret_cast<EncodedHandle*>(pDstData);
            if (pEncoded->pipelineId != 0)
            {
                VkPipeline pipeline = LookupObject(VK_OBJECT_TYPE_PIPELINE, VkPipeline(pEncoded->pipelineId));
                if (pipeline != VK_NULL_HANDLE)
                {
                    VkResult ret = VulkanReplay_GetRayTracingShaderGroupHandlesKHR(device, pipeline, uint32_t(pEncoded->groupId), 1, s_ShaderGroupHandleSize, pDstData);
                    if (ret != VK_SUCCESS)
                    {
                        NV_LOG("ERROR: Failed to get group handle", i);
                    }
                }
                else
                {
                    NV_LOG("ERROR: Shader binding table entry %d references unknown pipeline; OK if unused", i);
                }
            }
            else
            {

                if (!hasLogged)
                {
                    NV_LOG("WARNING: Shader binding table entry %d references null pipeline; OK if unused", i);
                    hasLogged = true;
                }
            }

            // Next entry
            pDstData += pShaderBindTable->stride;
            i++;

            // Raygen only has one entry; ignore rest
            if (type == RayTracingShaderBindingTableType::RayGenShader)
            {
                break;
            }
        }
        pDstBuffer->Unmap();

        // Get address
        VkStridedDeviceAddressRegionKHR region = {};
        region.deviceAddress = GetBufferAddress(device, pDstBuffer->GetBuffer());
        region.size = pShaderBindTable->size;
        region.stride = pShaderBindTable->stride;

        // Add to cache
        itr = s_sbtCache.insert(std::make_pair(pShaderBindTable, region)).first;
    }

    return itr->second;
}
#endif

//----------------------------------------------------------------------------------
// CheckLimit<T>
//----------------------------------------------------------------------------------
template <typename T, uint32_t N>
void CheckLimit(const T (&lhs)[N], const T (&rhs)[N], const char* pName)
{
    if (memcmp(lhs, rhs, sizeof(T) * N) != 0)
    {
        std::stringstream ss;
        ss << "NOTE: Device limit " << pName << "[" << N << "]"
           << " mismatch" << std::endl;
        ss << " > Capture: {";
        for (uint32_t i = 0; i < N; i++)
        {
            ss << lhs[i];
            if (i + 1 != N)
            {
                ss << ", ";
            }
        }
        ss << "}" << std::endl;
        ss << " > Replay:  {";
        for (uint32_t i = 0; i < N; i++)
        {
            ss << rhs[i];
            if (i + 1 != N)
            {
                ss << ", ";
            }
        }
        ss << "}";
        NV_MESSAGE(ss.str().c_str());
    }
}

template <typename T>
void CheckLimit(const T& lhs, const T& rhs, const char* pName)
{
    if (lhs != rhs)
    {
        std::stringstream ss;
        ss << "NOTE: Device limit " << pName << " mismatch" << std::endl;
        ss << " > Capture: " << lhs << std::endl;
        ss << " > Replay:  " << rhs;
        NV_MESSAGE(ss.str().c_str());
    }
}

#define NV_VK_CHECK_LIMIT(LHS, RHS, LIMIT) CheckLimit(LHS.LIMIT, RHS.LIMIT, #LIMIT);

//----------------------------------------------------------------------------------
// QueueFlagsToString
//----------------------------------------------------------------------------------
static std::string QueueFlagsToString(VkQueueFlags flags)
{
    std::string str;

    auto AppendBit = [](std::string& str, const std::string& append) {
        if (!str.empty())
        {
            str += " | ";
        }
        str += append;
    };

    if (flags & VK_QUEUE_GRAPHICS_BIT)
    {
        AppendBit(str, "GRAPHICS");
    }
    if (flags & VK_QUEUE_COMPUTE_BIT)
    {
        AppendBit(str, "COMPUTE");
    }
    if (flags & VK_QUEUE_TRANSFER_BIT)
    {
        AppendBit(str, "TRANSFER");
    }
#if !defined(VKSC_VERSION_1_0)
    if (flags & VK_QUEUE_SPARSE_BINDING_BIT)
    {
        AppendBit(str, "SPARSE_BINDING");
    }
#endif
    if (flags & VK_QUEUE_PROTECTED_BIT)
    {
        AppendBit(str, "PROTECTED");
    }
    return str;
}

//----------------------------------------------------------------------------------
// Extent3DToString
//----------------------------------------------------------------------------------
static std::string Extent3DToString(VkExtent3D x)
{
    std::stringstream ss;
    ss << "<";
    ss << x.width << ", ";
    ss << x.height << ", ";
    ss << x.depth;
    ss << ">";
    return ss.str();
}

//----------------------------------------------------------------------------------
// DeviceAddressToString
//----------------------------------------------------------------------------------
std::string DeviceAddressToString(VkDeviceAddress address)
{
    std::stringstream ss;
    ss << "0x" << std::hex << address;
    return ss.str();
}

//----------------------------------------------------------------------------------
// IncreaseVulkanFrameCounters
//----------------------------------------------------------------------------------
void IncreaseVulkanFrameCounters()
{
    // Increase frame counter
    s_FrameIdx++;

    // Flip buffering index
    s_BufferingIdx = s_FrameIdx % s_BufferingSize;

    // Reset per-frame counters
    s_SubmitIdx = 0;
    s_TraceRaysNVIdx.clear();
    s_ExternalMemoryUpdateIdx = 0;
    s_QueryPoolResetInFrame.clear();
}

//----------------------------------------------------------------------------------
// VulkanHelper_InitBegin
//----------------------------------------------------------------------------------
VkResult VulkanHelper_InitBegin(VkInstance instance)
{
    s_ReplayPhase = VulkanReplayPhase::Initializaiton;

    // GL-VK interop may not have any Vulkan swapchain. Register a dummy override to meet our assumptions.
    // This is required by object's initialization like descriptor-sets
#if defined(NV_USE_OPENGL)
    if (s_BufferingSize == 0)
    {
        OverrideKey dummyKey = GetOverrideKey((VkSwapchainKHR)0xBAD, 0);
        VulkanHelper_RegisterOverrideSet(instance, 1, &dummyKey);
        s_BufferingSize = 1;
        s_BufferingIdx = 0;
        VulkanHelper_ActivateOverride(instance, dummyKey);
        s_DefaultOverride = dummyKey;
    }
    RegisterGLSwapBuffersCallbacks(IncreaseVulkanFrameCounters);
#endif

    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_InitEnd
//----------------------------------------------------------------------------------
VkResult VulkanHelper_InitEnd(VkInstance instace)
{
    for (VkDevice device : s_SetDevices)
    {
        WaitForPendingResourceUpdates(device);
    }

    s_ReplayPhase = VulkanReplayPhase::Frame;
    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_ResetBegin
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ResetBegin(VkInstance instance)
{
    // Deprecated path that does state and resource reset in a single pass
    VulkanHelper_ResetInstanceState(instance);
    return VulkanHelper_ResetInstanceResourcesBegin(instance);
}

//----------------------------------------------------------------------------------
// VulkanHelper_ResetEnd
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ResetEnd(VkInstance instance)
{
    // Deprecated path that does state and resource reset in a single pass
    return VulkanHelper_ResetInstanceResourcesEnd(instance);
}

//----------------------------------------------------------------------------------
// BeginFrameResetPerfMarkers
//----------------------------------------------------------------------------------
static void BeginFrameResetPerfMarkers(VkInstance instance)
{
#if defined(VK_EXT_debug_marker)
    for (VkDevice device : s_SetDevices)
    {
        const auto& setExtensions = s_DeviceExtensions[device];
        auto itr = setExtensions.find(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
        if (itr != setExtensions.end())
        {
            static VkCommandBuffer s_ResetBeginCmd = [&]() -> VkCommandBuffer {
                VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
                VkCommandBufferAllocateInfo allocateInfo = {};
                allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocateInfo.commandPool = GetCommandPool(device, 0);
                allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocateInfo.commandBufferCount = 1;
                vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer);
                VkCommandBufferBeginInfo beginInfo = {};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                vkBeginCommandBuffer(commandBuffer, &beginInfo);
                VkDebugMarkerMarkerInfoEXT markerInfo = {};
                markerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
                markerInfo.pMarkerName = NV_FRAME_RESET_MARKER_NAME;
                vkCmdDebugMarkerBeginEXT(commandBuffer, &markerInfo);
                vkEndCommandBuffer(commandBuffer);
                return commandBuffer;
            }();
            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &s_ResetBeginCmd;
            vkQueueSubmit(GetQueue(device, 0), 1, &submitInfo, VK_NULL_HANDLE);
        }
    }
#endif
}

//----------------------------------------------------------------------------------
// EndFrameResetPerfMarkers
//----------------------------------------------------------------------------------
static void EndFrameResetPerfMarkers(VkInstance instance)
{
#if defined(VK_EXT_debug_marker)
    for (VkDevice device : s_SetDevices)
    {
        const auto& setExtensions = s_DeviceExtensions[device];
        auto itr = setExtensions.find(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
        if (itr != setExtensions.end())
        {
            static VkCommandBuffer s_ResetBeginCmd = [&]() -> VkCommandBuffer {
                VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
                VkCommandBufferAllocateInfo allocateInfo = {};
                allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocateInfo.commandPool = GetCommandPool(device, 0);
                allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocateInfo.commandBufferCount = 1;
                vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer);
                VkCommandBufferBeginInfo beginInfo = {};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                vkBeginCommandBuffer(commandBuffer, &beginInfo);
                vkCmdDebugMarkerEndEXT(commandBuffer);
                vkEndCommandBuffer(commandBuffer);
                return commandBuffer;
            }();
            VkSubmitInfo submitInfo = {};
            submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            submitInfo.commandBufferCount = 1;
            submitInfo.pCommandBuffers = &s_ResetBeginCmd;
            vkQueueSubmit(GetQueue(device, 0), 1, &submitInfo, VK_NULL_HANDLE);
        }
    }
#endif
}

//----------------------------------------------------------------------------------
// VulkanHelper_ResetInstanceResourcesBegin
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ResetInstanceResourcesBegin(VkInstance instance)
{
    s_ReplayPhase = VulkanReplayPhase::ResourceReset;

    for (VkDevice device : s_SetDevices)
    {
        // Make sure all work is complete before reset potentially
        // overwrites resources that are in use
        vkDeviceWaitIdle(device);
    }

    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_ResetInstanceResourcesEnd
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ResetInstanceResourcesEnd(VkInstance instance)
{
    for (VkDevice device : s_SetDevices)
    {
        WaitForPendingResourceUpdates(device);
    }

    if (s_SyncAtEndOfFrame)
    {
        for (VkDevice device : s_SetDevices)
        {

            std::vector<VkSemaphore> vecSemaphores;
            for (const auto& pair : s_SemaphoreStatus)
            {
                if (pair.second.signaled)
                {
                    VkSemaphore semaphore = pair.first;
                    vecSemaphores.push_back(semaphore);
                }
            }

            for (VkSemaphore semaphore : vecSemaphores)
            {
                ForceWaitForSignaledSemaphore(device, semaphore, "ResetEnd");
            }
            for (auto& pair : s_FenceStatus)
            {
                if (pair.second.signaled)
                {
                    WaitForPendingFence(device, pair.first, "ResetEnd");
                }
            }
        }
    }

    if (hasFrameReset)
    {
        EndFrameResetPerfMarkers(instance);
    }

    s_ReplayPhase = VulkanReplayPhase::Frame;
    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_ResetInstanceState
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ResetInstanceState(VkInstance instance)
{
    // The frame-index must not be zero at this point. Prevent such bugs that
    // may occure in cases like interop
    // Note: for VulkanSC we render to offscreen memory and use NvSci+OpenWFD
    // to render, so we don't use swapchain and we don't use frame-index.
#if !defined(VKSC_VERSION_1_0)
    NV_THROW_IF(s_FrameIdx == 0, "Per-frame counters failed to be increased");
#endif

    // Change to state reset phase
    VulkanReplayPhase lastPhase = s_ReplayPhase;
    s_ReplayPhase = VulkanReplayPhase::StateReset;

    // Inject markers
    if (hasFrameReset)
    {
        BeginFrameResetPerfMarkers(instance);
    }

    // Record each command buffer that was recorded prior to the frame
    // with the VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT flag.
    for (const auto& pair : s_OneTimeSubmitCommandBuffersRecordedBeforeFrame)
    {
        VkCommandBuffer commandBuffer = GetActive_CommandBuffer(s_BufferingIdx, pair.first);
        const CommandBufferRecordInfo& info = pair.second;
        info.pFnRecordCommandBuffer(commandBuffer);
    }

    // Restore phase
    s_ReplayPhase = lastPhase;
    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_ValidateImageMemoryRequirements
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateImageMemoryRequirements(VkDevice device, VkImage image, const VkMemoryRequirements* pCaptureMemoryRequirements)
{
    // Make sure the memory requirements
    // NOTE: We can attempt to support mismatches in a later version
    VkMemoryRequirements replayMemoryRequirements;
    vkGetImageMemoryRequirements(device, image, &replayMemoryRequirements);

    // Look for size or alignment changes
    if (pCaptureMemoryRequirements->size < replayMemoryRequirements.size)
    {
        NV_LOG("Image (%s) has changed size requirement (%" PRIu64 " to %" PRIu64 ")", GetObjectName(image).c_str(), pCaptureMemoryRequirements->size, replayMemoryRequirements.size);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(image));
    }
    if (pCaptureMemoryRequirements->alignment % replayMemoryRequirements.alignment != 0)
    {
        NV_LOG("Image (%s) has changed alignment (%u to %u)", GetObjectName(image).c_str(), pCaptureMemoryRequirements->alignment, replayMemoryRequirements.alignment);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(image));
    }

    // If we haven't see a memory type mismatch yet, see if the image requirements have changed
    if (!s_SawMemoryTypeMismatch)
    {
        if (pCaptureMemoryRequirements->memoryTypeBits != replayMemoryRequirements.memoryTypeBits)
        {
            NV_LOG("Image (%s) has changed memoryTypeBits (%s to %s)", GetObjectName(image).c_str(), BitsToString(pCaptureMemoryRequirements->memoryTypeBits).c_str(), BitsToString(replayMemoryRequirements.memoryTypeBits).c_str());
            s_SawMemoryTypeMismatch = true;
        }
    }

    // Store image requirements; this is only a problem if the requirements are
    // violated at bind time.
    s_ImageMemoryRequirements[image] = MemoryRequirements{ device, *pCaptureMemoryRequirements, replayMemoryRequirements };

    return VK_SUCCESS;
}

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//----------------------------------------------------------------------------------
// VulkanHelper_ValidateSparseImageMemoryRequirements
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateSparseImageMemoryRequirements(VkDevice device, VkImage image, uint32_t sparseImageMemoryRequirementCount, const VkSparseImageMemoryRequirements* pSparseImageMemoryRequirement)
{
    // Early return if count is zero
    if (sparseImageMemoryRequirementCount == 0)
    {
        return VK_SUCCESS;
    }

    // Get sparse image memory requirements
    uint32_t replaySparseImageMemoryReqsCount;
    std::vector<VkSparseImageMemoryRequirements> replaySparseImageMemoryReqs;
    vkGetImageSparseMemoryRequirements(device, image, &replaySparseImageMemoryReqsCount, nullptr);
    replaySparseImageMemoryReqs.resize(replaySparseImageMemoryReqsCount);
    vkGetImageSparseMemoryRequirements(device, image, &replaySparseImageMemoryReqsCount, replaySparseImageMemoryReqs.data());

    // Validate replay sparse image memory reqs
    if (replaySparseImageMemoryReqsCount != sparseImageMemoryRequirementCount)
    {
        NV_MESSAGE("NOTE: Sparse image memory requirements count different than the original capture");
        NV_MESSAGE(" > Capture: %u", sparseImageMemoryRequirementCount);
        NV_MESSAGE(" > Replay:  %u", replaySparseImageMemoryReqsCount);
    }
    else
    {
        if (memcmp(pSparseImageMemoryRequirement, replaySparseImageMemoryReqs.data(), sparseImageMemoryRequirementCount * sizeof(VkSparseImageMemoryRequirements)) != 0)
        {
            NV_MESSAGE("NOTE: Sparse image memory requirements mismatch");
        }
    }

    return VK_SUCCESS;
}
#endif

//----------------------------------------------------------------------------------
// VulkanHelper_ValidateBufferMemoryRequirements
//----------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateBufferMemoryRequirements(VkDevice device, VkBuffer buffer, const VkMemoryRequirements* pCaptureMemoryRequirements)
{
    // Make sure the memory requirements
    VkMemoryRequirements replayMemoryRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &replayMemoryRequirements);

    // Look for size or alignment changes
    if (pCaptureMemoryRequirements->size < replayMemoryRequirements.size)
    {
        NV_LOG("Buffer (%s) has changed size requirement (%" PRIu64 " to %" PRIu64 ")", GetObjectName(buffer).c_str(), pCaptureMemoryRequirements->size, replayMemoryRequirements.size);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(buffer));
    }
    if (pCaptureMemoryRequirements->alignment % replayMemoryRequirements.alignment != 0)
    {
        NV_LOG("Buffer (%s) has changed alignment (%u to %u)", GetObjectName(buffer).c_str(), pCaptureMemoryRequirements->alignment, replayMemoryRequirements.alignment);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(buffer));
    }

    // If we haven't see a memory tyGetAllocationCreateInfoForMemorype mismatch yet, see if the buffer requirements have changed
    if (!s_SawMemoryTypeMismatch)
    {
        if (pCaptureMemoryRequirements->memoryTypeBits != replayMemoryRequirements.memoryTypeBits)
        {
            NV_LOG("Buffer (%s) has changed memoryTypeBits (%s to %s)", GetObjectName(buffer).c_str(), BitsToString(pCaptureMemoryRequirements->memoryTypeBits).c_str(), BitsToString(replayMemoryRequirements.memoryTypeBits).c_str());
            s_SawMemoryTypeMismatch = true;
        }
    }

    // Store buffer requirements; this is only a problem if the requirements are
    // violated at bind time.
    s_BufferMemoryRequirements[buffer] = MemoryRequirements{ device, *pCaptureMemoryRequirements, replayMemoryRequirements };

    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// VulkanHelper_GetCompatiblePhysicalDevice
//----------------------------------------------------------------------------------
VkResult VulkanHelper_GetCompatiblePhysicalDevice(VkInstance instance, uint32_t deviceIdx, const VkPhysicalDeviceProperties& captureProperties, uint32_t captureQueueFamilyCount, const VkQueueFamilyProperties* pCaptureQueueFamilyProperties, const VkPhysicalDeviceMemoryProperties& captureMemoryProperties, VkPhysicalDevice* pPhysicalDevice)
{
    // Initialize return value
    *pPhysicalDevice = VK_NULL_HANDLE;

    // Enumerate physical devices
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    std::vector<VkPhysicalDevice> vecPhysicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, vecPhysicalDevices.data());

    // Register physical devices
    for (VkPhysicalDevice physicalDevice : vecPhysicalDevices)
    {
        s_PhsyicalDeviceToInstanceMap[physicalDevice] = instance;
    }

    // The higher the score the better match
    std::vector<uint32_t> vecDeviceMatchScore(physicalDeviceCount);

    // Loop these physical devices looking for a match
    // NOTE: This code has limited smarts in trying to find a "best match"
    for (uint32_t i = 0; i < physicalDeviceCount; i++)
    {

        // Candidate device
        const VkPhysicalDevice& physicalDevice = vecPhysicalDevices[i];

        // Skip physical devices we already enumerated
        if (s_SetPhysicalDevices.count(physicalDevice) > 0)
        {
            vecDeviceMatchScore[i] = 0;
            continue;
        }

        // One point for not being taken
        vecDeviceMatchScore[i]++;

        // General properties
        VkPhysicalDeviceProperties rhsProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &rhsProperties);

        // Same device name is very high probability it'll work
        if (strcmp(captureProperties.deviceName, rhsProperties.deviceName) == 0)
        {
            vecDeviceMatchScore[i] += 10;
        }

        // Otherwise same vendor ID has a better likelihood
        if (captureProperties.vendorID == rhsProperties.vendorID)
        {
            vecDeviceMatchScore[i] += 5;
        }

        // Prefer same device index for multi-GPU systems
        if (deviceIdx == i)
        {
            vecDeviceMatchScore[i] += 2;
        }
    }

    // Get device with highest score
    uint32_t maxScore = 0;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    for (uint32_t i = 0; i < physicalDeviceCount; i++)
    {
        const uint32_t score = vecDeviceMatchScore[i];
        if (score != 0 && score > maxScore)
        {
            maxScore = vecDeviceMatchScore[i];
            physicalDevice = vecPhysicalDevices[i];
        }
    }

    // Failed to find a compatible device
    if (physicalDevice == VK_NULL_HANDLE)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Use this device
    *pPhysicalDevice = physicalDevice;
    s_SetPhysicalDevices.insert(*pPhysicalDevice);

    // Map the memory properties of this device so we can attempt to patch them up
    s_CaptureMemoryProperties[physicalDevice] = captureMemoryProperties;

    // General properties
    VkPhysicalDeviceProperties replayProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &replayProperties);

    // Log some information about this device
    uint32_t apiVersion = 0;
    VulkanReplay_EnumerateInstanceVersion(&apiVersion);

    NV_MESSAGE("Replay Environment");
    NV_MESSAGE("> Vulkan Instance: %s", VersionToString(apiVersion).c_str());
    NV_MESSAGE("> Physical Device: %s", replayProperties.deviceName);
    NV_MESSAGE("> Driver Version: %s", DriverVersionToString(replayProperties).c_str());

    // Notify if some non-fatal values are different
    if (strcmp(captureProperties.deviceName, replayProperties.deviceName) != 0)
    {
        NV_MESSAGE("NOTE: Device name mismatch");
        NV_MESSAGE(" > Capture: %s", captureProperties.deviceName);
        NV_MESSAGE(" > Replay:  %s", replayProperties.deviceName);
    }
    if (captureProperties.driverVersion != replayProperties.driverVersion)
    {
        NV_MESSAGE("NOTE: Driver version mismatch");
        NV_MESSAGE(" > Capture: %s", DriverVersionToString(captureProperties).c_str());
        NV_MESSAGE(" > Replay:  %s", DriverVersionToString(replayProperties).c_str());
    }
    if (captureProperties.vendorID != replayProperties.vendorID)
    {
        s_SawPipelineCacheHeaderMismatch = true;
        NV_MESSAGE("NOTE: Vendor ID mismatch");
        NV_MESSAGE(" > Capture: %u", captureProperties.vendorID);
        NV_MESSAGE(" > Replay:  %u", replayProperties.vendorID);
    }
    if (captureProperties.deviceID != replayProperties.deviceID)
    {
        s_SawPipelineCacheHeaderMismatch = true;
        NV_MESSAGE("NOTE: Device ID mismatch");
        NV_MESSAGE(" > Capture: %u", captureProperties.deviceID);
        NV_MESSAGE(" > Replay:  %u", replayProperties.deviceID);
    }
    if (memcmp(captureProperties.pipelineCacheUUID, replayProperties.pipelineCacheUUID, sizeof(uint8_t) * VK_UUID_SIZE) != 0)
    {
        s_SawPipelineCacheHeaderMismatch = true;
        NV_MESSAGE("NOTE: Pipeline cache UUID mismatch");
    }

    // These *might* be trouble if they are different and there is very little we
    // could do at this point if something here is causing issues
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxImageDimension1D);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxImageDimension2D);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxImageDimension3D);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxImageDimensionCube);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxImageArrayLayers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTexelBufferElements);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxUniformBufferRange);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxStorageBufferRange);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPushConstantsSize);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxMemoryAllocationCount);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxSamplerAllocationCount);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, bufferImageGranularity);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, sparseAddressSpaceSize);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxBoundDescriptorSets);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorSamplers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorUniformBuffers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorStorageBuffers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorSampledImages);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorStorageImages);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageDescriptorInputAttachments);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxPerStageResources);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetSamplers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetUniformBuffers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetUniformBuffersDynamic);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetStorageBuffers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetStorageBuffersDynamic);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetSampledImages);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetStorageImages);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDescriptorSetInputAttachments);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxVertexInputAttributes);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxVertexInputBindings);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxVertexInputAttributeOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxVertexInputBindingStride);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxVertexOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationGenerationLevel);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationPatchSize);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationControlPerVertexInputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationControlPerVertexOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationControlPerPatchOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationControlTotalOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationEvaluationInputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTessellationEvaluationOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxGeometryShaderInvocations);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxGeometryInputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxGeometryOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxGeometryOutputVertices);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxGeometryTotalOutputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFragmentInputComponents);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFragmentOutputAttachments);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFragmentDualSrcAttachments);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFragmentCombinedOutputResources);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxComputeSharedMemorySize);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxComputeWorkGroupCount);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxComputeWorkGroupInvocations);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxComputeWorkGroupSize);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, subPixelPrecisionBits);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, subTexelPrecisionBits);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, mipmapPrecisionBits);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDrawIndexedIndexValue);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxDrawIndirectCount);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxSamplerLodBias);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxSamplerAnisotropy);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxViewports);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxViewportDimensions);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, viewportBoundsRange);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, viewportSubPixelBits);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minMemoryMapAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minTexelBufferOffsetAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minUniformBufferOffsetAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minStorageBufferOffsetAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minTexelOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTexelOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minTexelGatherOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxTexelGatherOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, minInterpolationOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxInterpolationOffset);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, subPixelInterpolationOffsetBits);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFramebufferWidth);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFramebufferHeight);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxFramebufferLayers);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, framebufferColorSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, framebufferDepthSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, framebufferStencilSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, framebufferNoAttachmentsSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxColorAttachments);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, sampledImageColorSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, sampledImageIntegerSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, sampledImageDepthSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, sampledImageStencilSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, storageImageSampleCounts);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxSampleMaskWords);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, timestampComputeAndGraphics);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, timestampPeriod);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxClipDistances);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxCullDistances);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, maxCombinedClipAndCullDistances);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, discreteQueuePriorities);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, pointSizeRange);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, lineWidthRange);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, pointSizeGranularity);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, lineWidthGranularity);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, strictLines);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, standardSampleLocations);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, optimalBufferCopyOffsetAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, optimalBufferCopyRowPitchAlignment);
    NV_VK_CHECK_LIMIT(captureProperties.limits, replayProperties.limits, nonCoherentAtomSize);

    // Check spare properties
    if (memcmp(&captureProperties.sparseProperties, &replayProperties.sparseProperties, sizeof(VkPhysicalDeviceSparseProperties)) != 0)
    {
        NV_MESSAGE("NOTE: Sparse properties mismatch");
    }

    // Get queue families properties
    uint32_t replayQueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &replayQueueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> vecReplayQueueFamilyProperties(replayQueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &replayQueueFamilyCount, vecReplayQueueFamilyProperties.data());

    // Report queue family mismatches; we only consider queue families incompatible if features
    // were removed
    s_SawQueueFamilyMismatch = [&]() -> bool {
        // More replay queues are OK if all the capture queues are the same
        if (captureQueueFamilyCount > replayQueueFamilyCount)
        {
            return true;
        }

        // See if all capture queues match
        for (uint32_t i = 0; i < captureQueueFamilyCount; i++)
        {
            const VkQueueFamilyProperties& capture = pCaptureQueueFamilyProperties[i];
            const VkQueueFamilyProperties& replay = vecReplayQueueFamilyProperties[i];
            if (memcmp(&capture, &replay, sizeof(VkQueueFamilyProperties)) != 0)
            {
                return true;
            }
        }

        // Otherwise compatible up to
        return false;
    }();

    // Build up queue family map
    std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[*pPhysicalDevice];
    if (!s_SawQueueFamilyMismatch)
    {

        // Use passthrough; all old queue families are compatible with new ones
        for (uint32_t queueFamilyIdx = 0; queueFamilyIdx < captureQueueFamilyCount; queueFamilyIdx++)
        {
            queueFamilyMap[queueFamilyIdx] = queueFamilyIdx;
        }
    }
    else
    {

        // Log difference
        NV_MESSAGE("NOTE: Queue families incompatible");
        auto LogQueue = [&](const char* pType, uint32_t idx, const VkQueueFamilyProperties* pProperties) {
            const VkQueueFamilyProperties& properties = pProperties[idx];
            NV_MESSAGE(" > %s [%u]", pType, idx);
            NV_MESSAGE("   > queueFlags: %s", QueueFlagsToString(properties.queueFlags).c_str());
            NV_MESSAGE("   > queueCount: %u", properties.queueCount);
            NV_MESSAGE("   > timestampValidBits: %u", properties.timestampValidBits);
            NV_MESSAGE("   > minImageTransferGranularity: %s", Extent3DToString(properties.minImageTransferGranularity).c_str());
        };
        for (uint32_t idx = 0; idx < captureQueueFamilyCount; idx++)
        {
            LogQueue("Capture", idx, pCaptureQueueFamilyProperties);
        }
        for (uint32_t idx = 0; idx < replayQueueFamilyCount; idx++)
        {
            LogQueue("Replay", idx, vecReplayQueueFamilyProperties.data());
        }

        // Attempt to patch queue family compatibility
        NV_MESSAGE("Attempting to find compatible queue families via remapping");
        s_SawQueueFamilyMismatch = true;
        for (uint32_t oldIdx = 0; oldIdx < captureQueueFamilyCount; oldIdx++)
        {

            // Helper to log match
            auto LogMatch = [&](uint32_t oldIdx) {
                const uint32_t newIdx = queueFamilyMap[oldIdx];
                const std::string captureFlags = QueueFlagsToString(pCaptureQueueFamilyProperties[oldIdx].queueFlags);
                const std::string replayFlags = QueueFlagsToString(vecReplayQueueFamilyProperties[newIdx].queueFlags);
                NV_MESSAGE("> Queue family %u (%s) --> %u (%s)", oldIdx, captureFlags.c_str(), newIdx, replayFlags.c_str());
            };

            auto TryToFindBestMatch = [&](int oldIdx) -> bool {
                // Match item
                struct Match
                {
                    uint32_t idx;
                    uint32_t count;
                };
                std::vector<Match> vecCompatibleFamilies;

                const VkQueueFamilyProperties& oldProperties = pCaptureQueueFamilyProperties[oldIdx];

                // Do a pass to find compatible families
                for (uint32_t newIdx = 0; newIdx < replayQueueFamilyCount; newIdx++)
                {
                    const VkQueueFamilyProperties& newProperties = vecReplayQueueFamilyProperties[newIdx];
                    if ((oldProperties.queueFlags & newProperties.queueFlags) == oldProperties.queueFlags)
                    {
                        Match match;
                        match.idx = newIdx;
                        match.count = CountBits(newProperties.queueFlags);
                        vecCompatibleFamilies.push_back(match);
                    }
                }

                // No match found!
                if (vecCompatibleFamilies.empty())
                {
                    return false;
                }

                // Best match has the least number of bits set of all the compatible matches
                auto itr = std::min_element(vecCompatibleFamilies.begin(), vecCompatibleFamilies.end(), [](const Match& lhs, const Match& rhs) {
                    return lhs.count < rhs.count;
                });
                queueFamilyMap[oldIdx] = itr->idx;
                return true;
            };

            // Try to best exact match
            if (TryToFindBestMatch(oldIdx))
            {
                LogMatch(oldIdx);
                continue;
            }

            // This *might* work if a family lost an unused queue family property like PROTECTED.
            NV_MESSAGE("> Queue family %u --> 0 (No match found)", oldIdx);
            queueFamilyMap[oldIdx] = 0;
        }
    }

    // Memory properties of this device
    VkPhysicalDeviceMemoryProperties replayMemoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &replayMemoryProperties);
    s_MemoryProperties[physicalDevice] = replayMemoryProperties;

    // Check for heap size mismatches
    s_SawHeapSizeMismatch = [&]() {
        // More replay heaps are OK if all the capture heaps are the same
        if (captureMemoryProperties.memoryHeapCount > replayMemoryProperties.memoryHeapCount)
        {
            return true;
        }

        // See if all capture queues match
        for (uint32_t i = 0; i < captureMemoryProperties.memoryHeapCount; i++)
        {

            const VkMemoryHeap& capture = captureMemoryProperties.memoryHeaps[i];
            const VkMemoryHeap& replay = replayMemoryProperties.memoryHeaps[i];

            // We don't care about system memory as there is nothing we can do about that
            const bool isDeviceLocal = ((capture.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) == VK_MEMORY_HEAP_DEVICE_LOCAL_BIT);
            if (capture.flags == replay.flags && !isDeviceLocal)
            {
                continue;
            }

            // More memory is OK
            if (replay.size < capture.size)
            {
                return true;
            }
        }

        // Otherwise compatible up to
        return false;
    }();

    // Log difference
    if (s_SawHeapSizeMismatch)
    {
        NV_MESSAGE("NOTE: Heap size mismatch");
        NV_MESSAGE("NOTE: -vk-trim-device-memory may help if VK_ERROR_OUT_OF_DEVICE_MEMORY is encountered");
        NV_MESSAGE(" > Capture");
        for (uint32_t i = 0; i < captureMemoryProperties.memoryHeapCount; i++)
        {
            const VkMemoryHeap& heap = captureMemoryProperties.memoryHeaps[i];
            NV_MESSAGE("   > Heap[%u] = { size = %" PRIu64 ", flags = %s }", i, heap.size, MemoryHeapFlagBitsToString(heap.flags).c_str());
        }
        NV_MESSAGE(" > Replay");
        for (uint32_t i = 0; i < replayMemoryProperties.memoryHeapCount; i++)
        {
            const VkMemoryHeap& heap = replayMemoryProperties.memoryHeaps[i];
            NV_MESSAGE("   > Heap[%u] = { size = %" PRIu64 ", flags = %s }", i, heap.size, MemoryHeapFlagBitsToString(heap.flags).c_str());
        }
    }

    // Check if number of memory types is different
    if (captureMemoryProperties.memoryTypeCount != replayMemoryProperties.memoryTypeCount)
    {
        s_SawMemoryTypeMismatch = true;
    }

    // Same count; check for type flag mismatches
    if (!s_SawMemoryTypeMismatch)
    {
        for (uint32_t memoryTypeIdx = 0; memoryTypeIdx < replayMemoryProperties.memoryTypeCount; memoryTypeIdx++)
        {
            if (captureMemoryProperties.memoryTypes[memoryTypeIdx].propertyFlags != replayMemoryProperties.memoryTypes[memoryTypeIdx].propertyFlags)
            {
                s_SawMemoryTypeMismatch = true;
            }
        }
    }

    // Log differences
    if (s_SawMemoryTypeMismatch)
    {
        NV_MESSAGE("NOTE: Memory type mismatch");
        NV_MESSAGE(" > Capture");
        for (uint32_t i = 0; i < captureMemoryProperties.memoryTypeCount; i++)
        {
            const VkMemoryType& memoryType = captureMemoryProperties.memoryTypes[i];
            NV_MESSAGE("   > MemoryType[%u] = { heapIdx = %u, properties = %s }", i, memoryType.heapIndex, MemoryPropertyFlagsToString(memoryType.propertyFlags).c_str());
        }
        NV_MESSAGE(" > Replay");
        for (uint32_t i = 0; i < replayMemoryProperties.memoryTypeCount; i++)
        {
            const VkMemoryType& memoryType = replayMemoryProperties.memoryTypes[i];
            NV_MESSAGE("   > MemoryType[%u] = { heapIdx = %u, properties = %s }", i, memoryType.heapIndex, MemoryPropertyFlagsToString(memoryType.propertyFlags).c_str());
        }
    }

    // Successfully found a valid device
    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// GetCompatibleDisplay
//----------------------------------------------------------------------------------
VkResult VulkanHelper_GetCompatibleDisplay(VkPhysicalDevice physicalDevice, const VkDisplayPropertiesKHR& matchProperty, VkDisplayKHR* pDisplay)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping calls to get compatible display as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    // Enumerate display
    uint32_t propertyCount;
    vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &propertyCount, nullptr);
    std::vector<VkDisplayPropertiesKHR> vecProperties(propertyCount);
    vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, &propertyCount, vecProperties.data());

    // Fail to find display property
    if (propertyCount == 0)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Find display if displayName matches
    for (const auto& property : vecProperties)
    {
        if (!matchProperty.displayName || !property.displayName)
        {
            continue;
        }
        if (strcmp(matchProperty.displayName, property.displayName) == 0)
        {
            NV_MESSAGE("> Display: %s", property.displayName);
            *pDisplay = property.display;
            return VK_SUCCESS;
        }
    }

    // Find display if transform capability matches
    for (const auto& property : vecProperties)
    {
        if ((property.supportedTransforms & matchProperty.supportedTransforms) != 0)
        {
            NV_MESSAGE("> Display: %s", property.displayName);
            *pDisplay = property.display;
            return VK_SUCCESS;
        }
    }

    // Cannot find matched display, use the first one
    NV_MESSAGE("NOTE: Failed to find matching display");
    NV_MESSAGE(" > Display: %s", vecProperties[0].displayName);
    *pDisplay = vecProperties[0].display;
    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// GetCompatibleDisplayMode
//----------------------------------------------------------------------------------
VkResult VulkanHelper_GetCompatibleDisplayMode(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModePropertiesKHR& matchProperty, VkDisplayModeKHR* pDisplayMode)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping calls to get compatible display mode as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    // Enumerate display mode
    uint32_t propertyCount;
    vkGetDisplayModePropertiesKHR(physicalDevice, display, &propertyCount, nullptr);
    std::vector<VkDisplayModePropertiesKHR> vecProperties(propertyCount);
    vkGetDisplayModePropertiesKHR(physicalDevice, display, &propertyCount, vecProperties.data());

    // Fail to find display mode property
    if (propertyCount == 0)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Find display mode if rate and visible region matches
    for (const auto& property : vecProperties)
    {
        if (memcmp(&matchProperty.parameters, &property.parameters, sizeof(property.parameters)) == 0)
        {
            NV_MESSAGE("> Display Mode: visible region (%u, %u), refresh rate %u", property.parameters.visibleRegion.width, property.parameters.visibleRegion.height, property.parameters.refreshRate);
            *pDisplayMode = property.displayMode;
            return VK_SUCCESS;
        }
    }

    // Find display mode if rate matches
    for (const auto& property : vecProperties)
    {
        if (matchProperty.parameters.refreshRate == property.parameters.refreshRate)
        {
            NV_MESSAGE("> Display Mode: visible region (%u, %u), refresh rate %u", property.parameters.visibleRegion.width, property.parameters.visibleRegion.height, property.parameters.refreshRate);
            *pDisplayMode = property.displayMode;
            return VK_SUCCESS;
        }
    }

    // Cannot find matched display mode, use the first one
    NV_MESSAGE("NOTE: Failed to find matching display");
    NV_MESSAGE(" > Display Mode: visible region (%u, %u), refresh rate %u", vecProperties[0].parameters.visibleRegion.width, vecProperties[0].parameters.visibleRegion.height, vecProperties[0].parameters.refreshRate);
    *pDisplayMode = vecProperties[0].displayMode;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelpers_RegisterOverrideSet
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterOverrideSet(VkInstance instance, uint32_t count, const uint64_t* pOverrides)
{
    NV_ASSERT(count != 0);
    NV_ASSERT(pOverrides != nullptr);

    // Only the main presenting swapchain should call this
    NV_ASSERT(s_VecOverrideSet.empty());

    // Create set object; must be empty
    s_VecOverrideSet = std::vector<OverrideKey>(pOverrides, pOverrides + count);

    // Loop each override
    for (uint32_t i = 0; i < count; i++)
    {
        // Create object override map for this specific override
        s_OverrideKeyToObjectOverrideMap.insert(std::make_pair(pOverrides[i], std::unique_ptr<ObjectOverrideMap>(new ObjectOverrideMap)));
    }

    // Store key
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelpers_AssociateImageOverrideKey
//------------------------------------------------------------------------------
VkResult VulkanHelper_AssociateImageWithOverrideKey(VkInstance instance, VkImage image, uint64_t key)
{
    // Make sure we know about this key
    auto itrKey = std::find(s_VecOverrideSet.begin(), s_VecOverrideSet.end(), key);
    if (itrKey == s_VecOverrideSet.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // This image must not already be associated with an image
    auto itrImage = s_ImageToOverrideKey.find(image);
    if (itrImage != s_ImageToOverrideKey.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Register LUT for image to key
    s_ImageToOverrideKey.insert(std::make_pair(image, key));
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelpers_RegisterOverrideSet
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterImageOverride(VkInstance instance, uint64_t key, VkImage srcImage, VkImage dstImg)
{
    // Make sure we know about this key
    auto itrKey = std::find(s_VecOverrideSet.begin(), s_VecOverrideSet.end(), key);
    if (itrKey == s_VecOverrideSet.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Register override object
    s_OverrideKeyToObjectOverrideMap[key]->images[srcImage] = dstImg;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterSemaphoreOverride
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterSemaphoreOverride(VkInstance instance, uint64_t key, VkSemaphore srcSemaphore, VkSemaphore dstSemaphore)
{
    // This legacy interface is no longer necessary
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterFenceOverride
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterFenceOverride(VkInstance instance, uint64_t key, VkFence srcFence, VkFence dstFence)
{
    // This legacy interface is no longer necessary
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelpers_ActivateOverride
//------------------------------------------------------------------------------
VkResult VulkanHelper_ActivateOverride(VkInstance instance, uint64_t override)
{
    auto& tls = GetThreadState();
    tls.activeOverride = override;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelpers_DeactivateOverride
//------------------------------------------------------------------------------
VkResult VulkanHelper_DeactivateOverride(VkInstance instance, uint64_t override)
{
    auto& tls = GetThreadState();
    tls.activeOverride = s_DefaultOverride;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_SignalSemaphore
//------------------------------------------------------------------------------
VkResult VulkanHelper_SignalSemaphore(VkSemaphore semaphore)
{
    SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(semaphore);
    semaphoreStatus.signaled = true;
    semaphoreStatus.lastSignaledFrame = s_FrameIdx;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_WaitSemaphore
//------------------------------------------------------------------------------
VkResult VulkanHelper_WaitSemaphore(VkSemaphore semaphore)
{
    // Call this function if the semaphore has been signaled outside of VulkanReplay,
    // so it will be removed from pending list and never be waited on
    GetSempahoreStatus(semaphore).signaled = false;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_IsCallingContextEnabled
//------------------------------------------------------------------------------
bool VulkanHelper_IsCallingContextEnabled()
{
    return s_ReportCallContext;
}

//------------------------------------------------------------------------------
// VulkanHelper_SetCallingContext
//------------------------------------------------------------------------------
VkResult VulkanHelper_SetCallingContext(const VulkanHelper_CallingContext* pContext)
{
    if (!s_ReportCallContext || !pContext)
    {
        return VK_ERROR_UNKNOWN;
    }

    s_CurrentCallingContext = *pContext;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_GetCallingContext
//------------------------------------------------------------------------------
VkResult VulkanHelper_GetCallingContext(VulkanHelper_CallingContext* pContext)
{
    if (!s_ReportCallContext || !pContext)
    {
        return VK_ERROR_UNKNOWN;
    }

    *pContext = s_CurrentCallingContext;
    pContext->structSize = sizeof(s_CurrentCallingContext);
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_SignalFence
//------------------------------------------------------------------------------
VkResult VulkanHelper_SignalFence(VkFence fence)
{
    VULKAN_REPLAY_WRITE_LOCK();

    fence = GetActive_Fence(s_BufferingIdx, fence);
    GetFenceStatus(fence).signaled = true;
    return VK_SUCCESS;
}

#if defined(VK_NVX_image_view_handle)
//------------------------------------------------------------------------------
// VulkanHelper_RegisterImageViewHandleOverrideNVX
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterImageViewHandleOverrideNVX(VkDevice device, VkImageView imageView, VkDescriptorType descriptorType, VkSampler sampler, uint32_t srcViewHandleNVX)
{
    if (srcViewHandleNVX == 0)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Make sure this image view handle hasn't yet been registered
    if (s_imageViewHandleMappingInfoNVX.find(srcViewHandleNVX) != s_imageViewHandleMappingInfoNVX.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Helper to get the active image view handle
    auto GetHandleNVX = [&](VkImageView view) {
        const VkImageViewHandleInfoNVX handleInfoNVX = {
            VK_STRUCTURE_TYPE_IMAGE_VIEW_HANDLE_INFO_NVX,
            nullptr,
            view,
            descriptorType,
            sampler
        };
        const uint32_t handle = VulkanReplay_GetImageViewHandleNVX(device, &handleInfoNVX);
        NV_ASSERT(handle != 0);
        return handle;
    };

    // Get the active handle for this image view
    const uint32_t thisHandle = GetHandleNVX(imageView);

    // Get the active handles for image view override (if needed)
    std::map<OverrideKey, uint32_t> overrideHandles;
    const auto itr = s_ImageViewToOverrideKey.find(imageView);
    if (itr != s_ImageViewToOverrideKey.end())
    {
        // Loop overrides
        const OverrideKey thisKey = itr->second;
        for (const OverrideKey& otherKey : s_VecOverrideSet)
        {
            // Fill up for this image view for easily searching
            if (otherKey == thisKey)
            {
                overrideHandles.emplace(thisKey, thisHandle);
                continue;
            }

            // Lookup image view associated with the other key
            const VkImageView otherImageView = s_OverrideKeyToObjectOverrideMap[otherKey]->imageViews[imageView];
            NV_ASSERT(otherImageView != VK_NULL_HANDLE);

            // Get the active handle for the other image view
            const uint32_t otherHandle = GetHandleNVX(otherImageView);
            overrideHandles.emplace(otherKey, otherHandle);
        }
    }

    // Register overrides
    s_imageViewHandleMappingInfoNVX.emplace(srcViewHandleNVX, ImageViewHandleMappingInfoNVX{ thisHandle, std::move(overrideHandles) });

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterImageViewAddressOverrideNVX
//------------------------------------------------------------------------------
NV_REPLAY_EXPORT VkResult VulkanHelper_RegisterImageViewAddressOverrideNVX(VkDevice device, VkImageView imageView, VkDeviceAddress srcDeviceAddressNVX, VkDeviceSize srcSizeNVX)
{
    if ((srcDeviceAddressNVX == 0) || (srcSizeNVX == 0))
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Make sure this image view address hasn't yet been registered
    if (s_imageViewAddressMappingInfoNVX.find(srcDeviceAddressNVX) != s_imageViewAddressMappingInfoNVX.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    // Helper to get the active image view address
    auto GetAddressNVX = [&](VkImageView view) {
        VkImageViewAddressPropertiesNVX addrPropsNVX = {
            VK_STRUCTURE_TYPE_IMAGE_VIEW_ADDRESS_PROPERTIES_NVX,
            nullptr,
            0,
            0
        };
        const VkResult getAddrResult = VulkanReplay_GetImageViewAddressNVX(device, imageView, &addrPropsNVX);
        NV_ASSERT(getAddrResult == VK_SUCCESS);
        NV_ASSERT(srcSizeNVX == addrPropsNVX.size);
        return addrPropsNVX.deviceAddress;
    };

    // Get the active image view address for this image view
    const VkDeviceAddress thisAddr = GetAddressNVX(imageView);

    // Get the active addresses for image view override (if needed)
    std::map<OverrideKey, VkDeviceAddress> overrideAddrs;
    const auto itr = s_ImageViewToOverrideKey.find(imageView);
    if (itr != s_ImageViewToOverrideKey.end())
    {
        // Loop overrides
        const OverrideKey thisKey = itr->second;
        for (const OverrideKey& otherKey : s_VecOverrideSet)
        {
            // Fill up for this image view for easily searching
            if (otherKey == thisKey)
            {
                overrideAddrs.emplace(thisKey, thisAddr);
                continue;
            }

            // Lookup image view associated with the other key
            const VkImageView otherImageView = s_OverrideKeyToObjectOverrideMap[otherKey]->imageViews[imageView];
            NV_ASSERT(otherImageView != VK_NULL_HANDLE);

            // Get the active address for the other image view
            const VkDeviceAddress otherAddr = GetAddressNVX(otherImageView);
            overrideAddrs.emplace(otherKey, otherAddr);
        }
    }

    // Register overrides
    s_imageViewAddressMappingInfoNVX.emplace(srcDeviceAddressNVX, ImageViewAddressMappingInfoNVX{ thisAddr, std::move(overrideAddrs) });

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_ActivateImageViewHandleOverrideNVX
//------------------------------------------------------------------------------
VkResult VulkanHelper_ActivateImageViewHandleOverrideNVX(void* pData, size_t dataSize)
{
    if (s_imageViewHandleMappingInfoNVX.empty())
    {
        return VK_SUCCESS;
    }

    // Patch up overrides
    const OverrideKey activeKey = GetThreadState().activeOverride;

    uint32_t* pHandleData = reinterpret_cast<uint32_t*>(pData);
    const size_t handleCount = (dataSize / sizeof(uint32_t));

    for (size_t handleIdx = 0; handleIdx < handleCount; ++handleIdx)
    {
        const uint32_t srcHandle = pHandleData[handleIdx];
        const auto itr = s_imageViewHandleMappingInfoNVX.find(srcHandle);
        if (itr != s_imageViewHandleMappingInfoNVX.end())
        {
            const ImageViewHandleMappingInfoNVX& handleMappingInfo = itr->second;
            const uint32_t dstHandle = (handleMappingInfo.overrideHandles.empty() ? handleMappingInfo.handle : handleMappingInfo.overrideHandles.at(activeKey));
            if (srcHandle == dstHandle)
            {
                NV_MESSAGE("INFO: NVX image view handle '%u' unchanged", srcHandle);
            }
            else
            {
                pHandleData[handleIdx] = dstHandle;
                NV_MESSAGE("NOTE: Overriding NVX image view handle '%u' -> '%u'", srcHandle, dstHandle);
            }
        }
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_ActivateImageViewAddressOverrideNVX
//------------------------------------------------------------------------------
VkResult VulkanHelper_ActivateImageViewAddressOverrideNVX(void* pData, size_t dataSize)
{
    if (s_imageViewAddressMappingInfoNVX.empty())
    {
        return VK_SUCCESS;
    }

    // Patch up overrides
    const OverrideKey activeKey = GetThreadState().activeOverride;

    VkDeviceAddress* pAddressData = reinterpret_cast<VkDeviceAddress*>(pData);
    const size_t addressCount = (dataSize / sizeof(VkDeviceAddress));

    for (size_t addressIdx = 0; addressIdx < addressCount; ++addressIdx)
    {
        const VkDeviceAddress srcAddress = pAddressData[addressIdx];
        const auto itr = s_imageViewAddressMappingInfoNVX.find(srcAddress);
        if (itr != s_imageViewAddressMappingInfoNVX.end())
        {
            const ImageViewAddressMappingInfoNVX& addrMappingInfo = itr->second;
            const VkDeviceAddress dstAddress = (addrMappingInfo.overrideAddresses.empty() ? addrMappingInfo.address : addrMappingInfo.overrideAddresses.at(activeKey));
            if (srcAddress == dstAddress)
            {
                NV_MESSAGE("INFO: NVX image view address '%" PRIu64 "' unchanged", srcAddress);
            }
            else
            {
                pAddressData[addressIdx] = dstAddress;
                NV_MESSAGE("NOTE: Overriding NVX image view address '%" PRIu64 "' -> '%" PRIu64 "'", srcAddress, dstAddress);
            }
        }
    }

    return VK_SUCCESS;
}
#endif

//------------------------------------------------------------------------------
// VulkanHelper_InitializeDescriptorSet
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeDescriptorSet(VkDevice device, VkDescriptorSet set, VkDescriptorPool pool, VkDescriptorSetLayout layout, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites)
{
    // Update original command buffer
    VulkanReplay_UpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, 0, nullptr);
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeCommandBuffer
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeCommandBuffer(VkDevice device, VkCommandBuffer commandBuffer, const VkCommandBufferAllocateInfo* pAllocateInfo, PFN_RecordCommandBuffer pFnRecordCommandBuffer)
{
    // We shouldn't be in a current override
    auto& tls = GetThreadState();
    NV_ASSERT(tls.activeOverride == s_DefaultOverride);

    // Make all descriptors are initialized
    s_DescriptorManager.FlushDescriptorUpdates();

    // Cache current recording information
    s_CurrentCommandBufferRecordInfo.device = device;
    s_CurrentCommandBufferRecordInfo.commandBuffer = commandBuffer;
    s_CurrentCommandBufferRecordInfo.pAllocateInfo = pAllocateInfo;
    s_CurrentCommandBufferRecordInfo.pFnRecordCommandBuffer = pFnRecordCommandBuffer;

    // Store first record function
    s_CommandBufferToRecordRev0[commandBuffer] = pFnRecordCommandBuffer;

#if defined(VKSC_VERSION_1_0)
    // For VulkanSC, we don't have overrides we just record command buffer.
    pFnRecordCommandBuffer(commandBuffer);
    RuntimeChecks::SetRecorded(commandBuffer);
#else
    // Initialize all possible overrides using a different swapchain override
    // for any command buffer that is cached before the frame. This isn't bullet
    // proof but will address some flickering issues.

    // Initialize all possible overrides
    NV_ASSERT(s_BufferingSize == s_VecOverrideSet.size());
    for (uint32_t i = 0; i < s_BufferingSize; i++)
    {
        // Record this
        OverrideKey tempKey = s_VecOverrideSet[i];
        tls.activeOverride = tempKey;
        s_BufferingIdx = i;

        VkCommandBuffer overrideCommandBuffer = GetActive_CommandBuffer(i, commandBuffer);
        pFnRecordCommandBuffer(overrideCommandBuffer);
        RuntimeChecks::SetRecorded(overrideCommandBuffer);
    }
#endif

    // Restore overrides
    tls.activeOverride = s_DefaultOverride;
    s_BufferingIdx = 0;

    // Reset
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// DoRecordCommandBuffer_Work
//------------------------------------------------------------------------------
static void DoRecordCommandBuffer_Work(VkDevice device, VkCommandBuffer commandBuffer, PFN_RecordCommandBuffer pFnRecordCommandBuffer)
{
    ResetDedicatedPool(device, commandBuffer);
    pFnRecordCommandBuffer(commandBuffer);
    RuntimeChecks::SetRecorded(commandBuffer);
}

//------------------------------------------------------------------------------
// DoRecordCommandBuffer_Dispatch
//------------------------------------------------------------------------------
static void DoRecordCommandBuffer_Dispatch(OverrideKey thisOverride, VkDevice device, VkCommandBuffer commandBuffer, PFN_RecordCommandBuffer pFnRecordCommandBuffer)
{
    // Do the 1st frame without multi-threading to allow our static data structures to resize correctly
    const bool useThreads = g_threadPoolThreadCount > 0 && s_FrameIdx != 0;

    CommandBufferRecordDesc& desc = GetCommandBufferRecordDesc(commandBuffer);
    desc.valid = false;

    if (!useThreads)
    {
        VulkanThreadState& mainThreadTls = GetThreadState();
        OverrideKey temp = mainThreadTls.activeOverride;
        mainThreadTls.activeOverride = thisOverride;
        DoRecordCommandBuffer_Work(device, commandBuffer, pFnRecordCommandBuffer);
        mainThreadTls.activeOverride = temp;
        return;
    }

    desc.optionalFuture = NvExecuteOnThreadPool([=] {
        VulkanThreadState& helperThreadTls = GetThreadState();
        helperThreadTls.activeOverride = thisOverride;
        DoRecordCommandBuffer_Work(device, commandBuffer, pFnRecordCommandBuffer);
    });
};

//------------------------------------------------------------------------------
// WaitForCommandBufferRecord
//------------------------------------------------------------------------------
static void WaitForCommandBufferRecord(VkCommandBuffer commandBuffer)
{
    CommandBufferRecordDesc& commandBufferDesc = GetCommandBufferRecordDesc(commandBuffer);
    std::future<void>& future = commandBufferDesc.optionalFuture;
    if (future.valid())
    {
        auto waitResult = future.wait_for(std::chrono::seconds(10));
        NV_THROW_IF(waitResult != std::future_status::ready, "Timeout waiting for async command buffer recording to finish");
    }

    NV_THROW_IF(!commandBufferDesc.valid, "Command buffer was never recorded");
}

//------------------------------------------------------------------------------
// VulkanHelper_RecordCommandBuffer
//------------------------------------------------------------------------------
VkResult VulkanHelper_RecordCommandBuffer(VkDevice device, VkCommandBuffer commandBuffer, uint32_t revision, PFN_RecordCommandBuffer pFnRecordCommandBuffer)
{
    // We only create the overrides for the first frame when when the cache is enabled
    if (s_CacheCommandBuffer && s_FrameIdx != 0)
    {
        return VK_SUCCESS;
    }

    // Flag command buffers recorded in frame
    if (s_FrameIdx == 0 && s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        s_CommandBufferRecordedInFrame.insert(commandBuffer);
    }

    // Make sure all async descriptors are updated before doing any recording
    // With a little more management we could wait inside the multi-threaded
    // recording functions but this avoids any deadlock scenario as all waiting
    // happens in the main thread.
    s_DescriptorManager.FlushDescriptorUpdates();

    // Record this command buffer for the multi-buffering index and overrides
    VkCommandBuffer activeCommandBuffer = GetActive_CommandBuffer(s_BufferingIdx, commandBuffer);
    DoRecordCommandBuffer_Dispatch(GetThreadState().activeOverride, device, activeCommandBuffer, pFnRecordCommandBuffer);

    // Initialize all version of this command buffer if we are pre-frame
    if (s_CacheCommandBuffer || s_ReplayPhase != VulkanReplayPhase::Frame || s_FrameIdx == 0)
    {
        // We save/restore the bufferingIdx so that target commandbuffers for CmdExecuteCommands get the correct buffering idx.
        const uint32_t saveBufferingIdx = s_BufferingIdx;
        for (s_BufferingIdx = 0; s_BufferingIdx < s_BufferingSize; s_BufferingIdx++)
        {
            if (s_BufferingIdx == saveBufferingIdx)
            {
                continue;
            }
            VkCommandBuffer activeCommandBuffer = GetActive_CommandBuffer(s_BufferingIdx, commandBuffer);
            DoRecordCommandBuffer_Dispatch(s_VecOverrideSet[s_BufferingIdx], device, activeCommandBuffer, pFnRecordCommandBuffer);
        }
        s_BufferingIdx = saveBufferingIdx;
    }

    // Restore main thread TLS
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeSwapchain
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeSwapchain(VkDevice device, VkSwapchainKHR swapchain, uint32_t acquiredImageCount)
{
    if (s_ReplayPhase != VulkanReplayPhase::Initializaiton)
    {
        return VK_SUCCESS;
    }

    // It is not required to present images in the same order that they were acquired,
    // the application may do like this in a frame:
    //
    //     1. Record to image N-1 (acquired in previous frames)
    //     2. Render to image N-1
    //     3. Acquire image N
    //     4. Present image N-1
    //
    // In order to take care of this case, we need in advance to acquire some images before
    // replaying the saved frame.

    for (uint32_t i = 0; i < acquiredImageCount; ++i)
    {
        uint32_t imageIndex = 0;
        const auto result = vkAcquireNextImageKHR(device, swapchain, NV_DEFAULT_FENCE_WAIT_NS, VK_NULL_HANDLE, VK_NULL_HANDLE, &imageIndex);
        NV_THROW_IF(result != VK_SUCCESS, "Failed to acquire pre-frame swapchain image.");

        auto& swapchainInfo = GetSwapchainInfo(swapchain);
        swapchainInfo.acquiredImages.push(imageIndex);
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeQueryPool
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeQueryPool(VkDevice device, VkQueryPool queryPool)
{
    // Lookup query count
    auto itr = s_QueryPoolToCreateInfo.find(queryPool);
    if (itr == s_QueryPoolToCreateInfo.end())
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }
    const uint32_t queryCount = itr->second->queryCount;
    s_QueryPoolAvailableRanges[queryPool].resize(queryCount, VK_FALSE);

    // Reset whole pool
    return VulkanHelper_ExecuteCommands(device, VkQueueFlags(VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT), [=](VkCommandBuffer cmdBuffer) {
        vkCmdResetQueryPool(cmdBuffer, queryPool, 0, queryCount);
    });
}

//------------------------------------------------------------------------------
// VulkanHelper_ResetQueryPool
//------------------------------------------------------------------------------
VkResult VulkanHelper_ResetQueryPool(VkDevice device, VkQueryPool queryPool)
{
    return VulkanHelper_InitializeQueryPool(device, queryPool);
}

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanHelper_ValidateAccelerationStructureMemoryRequirementsNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateAccelerationStructureMemoryRequirementsNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pCaptureMemoryRequirements2)
{
    // Query replay memory requirements
    VkAccelerationStructureMemoryRequirementsInfoNV replayMemoryRequirementsInfo;
    replayMemoryRequirementsInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV;
    replayMemoryRequirementsInfo.pNext = nullptr;
    replayMemoryRequirementsInfo.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;
    replayMemoryRequirementsInfo.accelerationStructure = accelerationStructure;
    VkMemoryRequirements2 replayRemoryRequirements2 = { VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 };
    vkGetAccelerationStructureMemoryRequirementsNV(device, &replayMemoryRequirementsInfo, &replayRemoryRequirements2);

    // Look for size or alignment changes
    if (pCaptureMemoryRequirements2->memoryRequirements.size < replayRemoryRequirements2.memoryRequirements.size)
    {
        NV_LOG("Acceleration structure (%s) has changed size requirement (%" PRIu64 " to %" PRIu64 ")", GetObjectName(accelerationStructure), pCaptureMemoryRequirements2->memoryRequirements.size, replayRemoryRequirements2.memoryRequirements.size);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(accelerationStructure));
    }
    if (pCaptureMemoryRequirements2->memoryRequirements.alignment % replayRemoryRequirements2.memoryRequirements.alignment != 0)
    {
        NV_LOG("Acceleration structure (%s) has changed alignment (%u to %u)", GetObjectName(accelerationStructure), pCaptureMemoryRequirements2->memoryRequirements.alignment, replayRemoryRequirements2.memoryRequirements.alignment);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(accelerationStructure));
    }

    // Store in map to validate at bind time
    s_AccelerationStructureMemoryRequirementsNV[accelerationStructure] = { device, pCaptureMemoryRequirements2->memoryRequirements, replayRemoryRequirements2.memoryRequirements };
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_ValidateAccelerationStructureMemoryRequirementsKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateAccelerationStructureMemoryRequirementsKHR(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pCaptureMemoryRequirements2)
{
    return VulkanHelper_ValidateAccelerationStructureMemoryRequirementsNV(device, accelerationStructure, pCaptureMemoryRequirements2);
}

//------------------------------------------------------------------------------
// VulkanHelper_ValidateAccelerationStructureScratchMemoryRequirementsNVX
//------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateAccelerationStructureScratchMemoryRequirementsNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkMemoryRequirements2* pCaptureMemoryRequirements2)
{
    // We manage all scratch space locally; no need for this to match
    return VK_SUCCESS;
}
#endif

#if defined(VK_KHR_video_queue)
//------------------------------------------------------------------------------
// VulkanHelper_ValidateVideoSessionMemoryRequirements
//------------------------------------------------------------------------------
VkResult VulkanHelper_ValidateVideoSessionMemoryRequirements(VkDevice device, VkVideoSessionKHR videoSession, uint32_t captureMemoryRequirementsCount, const VkVideoSessionMemoryRequirementsKHR* pCaptureMemoryProperties)
{
    // Early return if count is zero
    if (captureMemoryRequirementsCount == 0)
    {
        return VK_SUCCESS;
    }

    // Get video session memory requirements
    uint32_t replayVideoSessionMemoryRequirementsCount = 0;
    vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, &replayVideoSessionMemoryRequirementsCount, nullptr);
    std::vector<VkVideoSessionMemoryRequirementsKHR> replayVecVideoSessionMemoryProperties(replayVideoSessionMemoryRequirementsCount);
    for (uint32_t i = 0; i < replayVideoSessionMemoryRequirementsCount; i++)
    {
        replayVecVideoSessionMemoryProperties[i].sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
    }
    vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, &replayVideoSessionMemoryRequirementsCount, replayVecVideoSessionMemoryProperties.data());

    // Validate replay video session memory reqs
    if (captureMemoryRequirementsCount != replayVideoSessionMemoryRequirementsCount)
    {
        NV_MESSAGE("NOTE: Video session memory requirements count different than the original capture");
        NV_MESSAGE(" > Capture: %u", captureMemoryRequirementsCount);
        NV_MESSAGE(" > Replay:  %u", replayVideoSessionMemoryRequirementsCount);
        s_SawMemorySizeOrAlignmentMismatch.insert(uint64_t(videoSession));
    }
    else
    {
        auto Equals = [](const VkVideoSessionMemoryRequirementsKHR& lhs, const VkVideoSessionMemoryRequirementsKHR& rhs) -> bool {
            if (lhs.memoryBindIndex != rhs.memoryBindIndex)
            {
                return false;
            }
            const VkMemoryRequirements& lhsMemReq = lhs.memoryRequirements;
            const VkMemoryRequirements& rhsMemReq = rhs.memoryRequirements;
            return lhsMemReq.size == rhsMemReq.size && lhsMemReq.alignment == rhsMemReq.alignment && lhsMemReq.memoryTypeBits == rhsMemReq.memoryTypeBits;
        };
        for (uint32_t i = 0; i < captureMemoryRequirementsCount; i++)
        {
            if (!Equals(replayVecVideoSessionMemoryProperties[i], pCaptureMemoryProperties[i]))
            {
                NV_MESSAGE("NOTE: Video session memory requirements mismatch");
                break;
            }
        }
    }

    return VK_SUCCESS;
}
#endif

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanHelper_InitializeAccelerationStructureNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeAccelerationStructureNV(VkDevice device, const VkAccelerationStructureInfoNV* pInfo, const void* pInstanceData, const VulkanHelper_GeometryDataNV* pGeometryDataNV, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src)
{
    return VulkanHelper_InitializeAccelerationStructureNV2(device, pInfo, pInstanceData, pGeometryDataNV, update, dst, src, VK_FALSE);
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VulkanHelper_InitializeAccelerationStructureInfoKHR* pInitializationInfo, uint32_t geometryCount, const VkAccelerationStructureGeometryKHR* pGeometry, const VkAccelerationStructureBuildRangeInfoKHR* pRangeInfo)
{
    return VulkanHelper_InitializeAccelerationStructureKHR2(device, accelerationStructure, pInitializationInfo, geometryCount, pGeometry, pRangeInfo, VK_FALSE);
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeAccelerationStructureNV2
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeAccelerationStructureNV2(VkDevice device, const VkAccelerationStructureInfoNV* pInfo, const void* pInstanceData, const VulkanHelper_GeometryDataNV* pGeometryDataNV, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBool32 supportUpdates)
{
    // See if this is a compacted acceleration structure
    AccelerationStructureNV* pAccelerationStructureNV = s_AccelerationStructuresNV.Lookup(dst);
    NV_ASSERT(pAccelerationStructureNV);
    const VkDeviceSize compactedSize = (pAccelerationStructureNV->pCreateInfoNV->compactedSize);

    // Make sure all input buffers are fully populated before building this
    // acceleration structure.
    WaitForPendingResourceUpdates(device);

    // Get allocator for this device
    VmaAllocator allocator = s_Allocators[device];
    NV_ASSERT(allocator != VK_NULL_HANDLE);

    // If geometry data is directly included we need to rebuild geometry buffers
    if (pGeometryDataNV)
    {

        // Local copy of info
        VkAccelerationStructureInfoNV info = *pInfo;

        // Local copy where we will place geometry data
        std::vector<VkGeometryNV> vecGeometryNVX(pInfo->pGeometries, pInfo->pGeometries + pInfo->geometryCount);
        info.pGeometries = vecGeometryNVX.data();

        // Local buffer storage to keep scoped buffers valid
        std::list<ScopedVmaBuffer> vecGeometryBuffers;

        // Update geometry
        for (uint32_t i = 0; i < pInfo->geometryCount; i++)
        {

            // Helper to populate buffer data
            auto MakeBuffer = [&](VkDeviceSize size, const uint8_t* pSrcData, VkDeviceSize srcStride = 0, VkDeviceSize dstStride = 0) -> VkBuffer {
                if (!pSrcData)
                {
                    return VK_NULL_HANDLE;
                }

                // Resize to destination stride
                uint32_t elementCount = 0;
                if (srcStride && dstStride && srcStride != dstStride)
                {
                    elementCount = static_cast<uint32_t>(size / srcStride);
                    size = elementCount * dstStride;
                }

                // Allocate memory
                ScopedVmaBuffer allocation = ScopedVmaBuffer(allocator, size, VK_BUFFER_USAGE_RAY_TRACING_BIT_NV, VMA_MEMORY_USAGE_CPU_TO_GPU);
                NV_ASSERT(allocation);

                uint8_t* pDstData = static_cast<uint8_t*>(allocation.Map());
                NV_ASSERT(pDstData);

                // Perform copy
                if (srcStride && dstStride && srcStride != dstStride)
                {
                    for (uint32_t i = 0; i < elementCount; i++)
                    {
                        memcpy(pDstData + (i * dstStride), pSrcData + (i * srcStride), srcStride);
                    }
                }
                else
                {
                    memcpy(pDstData, pSrcData, size);
                }

                allocation.Unmap();
                vecGeometryBuffers.push_back(std::move(allocation));
                return vecGeometryBuffers.back().GetBuffer();
            };

            // CPU geometry
            const VulkanHelper_GeometryDataNV& hostGeometryData = pGeometryDataNV[i];

            // Has deep copied vertex buffer
            if (hostGeometryData.pVertexBufferData)
            {
                vecGeometryNVX[i].geometry.triangles.vertexData = MakeBuffer(hostGeometryData.vertexBufferSize, hostGeometryData.pVertexBufferData, hostGeometryData.packedVertexStride, hostGeometryData.unpackedVertexStride);
                vecGeometryNVX[i].geometry.triangles.vertexStride = hostGeometryData.unpackedVertexStride;
            }

            // Has deep copied index buffer
            // NOTE: This path is deprecated; all index buffers are fetched into vertex buffers
            if (hostGeometryData.pIndexBufferData)
            {
                vecGeometryNVX[i].geometry.triangles.indexData = MakeBuffer(hostGeometryData.indexBufferSize, hostGeometryData.pIndexBufferData);
            }

            // Has deep copied transform buffer
            if (hostGeometryData.pTransformBufferData)
            {
                vecGeometryNVX[i].geometry.triangles.transformData = MakeBuffer(hostGeometryData.transformBufferSize, hostGeometryData.pTransformBufferData);
            }
        }

        // Call again with valid data
        return VulkanHelper_InitializeAccelerationStructureNV2(device, &info, pInstanceData, nullptr, update, dst, src, supportUpdates);
    }

    // Handle compaction initialization case
    if (compactedSize != 0)
    {

        // We should have consumed the geometry data by now
        NV_ASSERT(!pGeometryDataNV && "Deep copy geometry should have been consumed");
        NV_ASSERT(pInfo->instanceCount == 0 && "Unexpected compacted instance case");

        // Append ALLOW_COMPACTION_BIT to as info since the src as should be created and built with this bit
        VkAccelerationStructureInfoNV tempAsInfo = *pInfo;
        tempAsInfo.flags |= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV;

        // Create the pre-compacted acceleration structure
        VkAccelerationStructureNV tempAs = VK_NULL_HANDLE;
        VkAccelerationStructureCreateInfoNV tempAsCreateInfo = *pAccelerationStructureNV->pCreateInfoNV;
        tempAsCreateInfo.compactedSize = 0;
        tempAsCreateInfo.info = tempAsInfo;
        NV_VK_VALIDATE(vkCreateAccelerationStructureNV(device, &tempAsCreateInfo, nullptr, &tempAs));

        // Get size requirements for acceleration structure
        const VkMemoryRequirements asRequirements = [&]() {
            VkAccelerationStructureMemoryRequirementsInfoNV asMemoryRequirementsInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_INFO_NV };
            asMemoryRequirementsInfo.type = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV;
            asMemoryRequirementsInfo.accelerationStructure = tempAs;
            VkMemoryRequirements2 memoryRequirements2 = { VK_STRUCTURE_TYPE_MEMORY_REQUIREMENTS_2 };
            vkGetAccelerationStructureMemoryRequirementsNV(device, &asMemoryRequirementsInfo, &memoryRequirements2);
            return memoryRequirements2.memoryRequirements;
        }();

        // Allocate build memory
        ScopedVmaBuffer buildBuffer = ScopedVmaBuffer(allocator, asRequirements.size, asRequirements.memoryTypeBits, VK_BUFFER_USAGE_RAY_TRACING_BIT_NV, VMA_MEMORY_USAGE_GPU_ONLY);

        // Create and bind build buffer
        VkBindAccelerationStructureMemoryInfoNV bindInfo = { VK_STRUCTURE_TYPE_BIND_ACCELERATION_STRUCTURE_MEMORY_INFO_NV };
        bindInfo.accelerationStructure = tempAs;
        bindInfo.memory = buildBuffer.GetInfo().deviceMemory;
        bindInfo.memoryOffset = buildBuffer.GetInfo().offset;
        NV_VK_VALIDATE(vkBindAccelerationStructureMemoryNV(device, 1, &bindInfo));

        // Create scratch buffer
        ScopedVmaBuffer scratch = CreateAccelerationScratchBufferNV(device, tempAs);

        // Build the original and perform the query
        NV_VK_VALIDATE(VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
            if (supportUpdates)
            {
                vkCmdBuildAccelerationStructureNV(cmdBuffer, &tempAsInfo, VK_NULL_HANDLE, 0, update, tempAs, src ? tempAs : VK_NULL_HANDLE, scratch, 0);
            }
            else
            {
                vkCmdBuildAccelerationStructureNV(cmdBuffer, &tempAsInfo, VK_NULL_HANDLE, 0, VK_FALSE, tempAs, VK_NULL_HANDLE, scratch, 0);
            }
        }));

        // Query the size now (we could use a barrier instead of two command lists)
        VkQueryPool queryPool = VK_NULL_HANDLE;
        VkQueryPoolCreateInfo tempPoolCreateInfo = { VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO };
        tempPoolCreateInfo.queryType = VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV;
        tempPoolCreateInfo.queryCount = 1;
        NV_VK_VALIDATE(vkCreateQueryPool(device, &tempPoolCreateInfo, nullptr, &queryPool));
        NV_VK_VALIDATE(VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
            vkCmdWriteAccelerationStructuresPropertiesNV(cmdBuffer, 1, &tempAs, VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_NV, queryPool, 0);
        }));
        VkDeviceSize compactedSizeOut = 0;
        NV_VK_VALIDATE(vkGetQueryPoolResults(device, queryPool, 0, 1, sizeof(VkDeviceSize), &compactedSizeOut, sizeof(VkDeviceSize), VK_QUERY_RESULT_WAIT_BIT));
        vkDestroyQueryPool(device, queryPool, nullptr);

        // XXX: Unsupported case if the compacted size changed
        NV_THROW_IF(compactedSizeOut != compactedSize, "FATAL: Unsupported change in compacted acceleration structure size.");

        // Now perform the compacting copy
        NV_VK_VALIDATE(VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
            vkCmdCopyAccelerationStructureNV(cmdBuffer, dst, tempAs, VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV);
        }));

        // Done with temporary AS
        vkDestroyAccelerationStructureNV(device, tempAs, nullptr);

        // Compacted AS should be built now
        return VK_SUCCESS;
    }

    // Create scratch buffer
    ScopedVmaBuffer scratchBuffer = CreateAccelerationScratchBufferNV(device, dst);

    // Override instance acceleration structure handles
    if (pInstanceData)
    {

        // Cast to geometry data
        const VkAccelerationStructureInstanceKHR* pSrcInstanceData = reinterpret_cast<const VkAccelerationStructureInstanceKHR*>(pInstanceData);

        // Allocate buffer
        ScopedVmaBuffer geometryBuffer = ScopedVmaBuffer(allocator, sizeof(VkAccelerationStructureInstanceKHR) * pInfo->instanceCount, VK_BUFFER_USAGE_RAY_TRACING_BIT_NV, VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(geometryBuffer);

        // Map our data
        VkAccelerationStructureInstanceKHR* pDstInstanceData = reinterpret_cast<VkAccelerationStructureInstanceKHR*>(geometryBuffer.Map());
        NV_ASSERT(pDstInstanceData);

        // Loop accelerations structures
        for (uint32_t i = 0; i < pInfo->instanceCount; i++)
        {

            // Copy instance data
            pDstInstanceData[i] = pSrcInstanceData[i];

            // Patch up instance handles
            if (!PatchGeometryInstanceNV(device, pDstInstanceData[i]))
            {
                return VK_ERROR_INVALID_DEVICE_ADDRESS_EXT;
            }
        }

        // Unmap data
        geometryBuffer.Unmap();

        // Execute build
        VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
            vkCmdBuildAccelerationStructureNV(cmdBuffer, pInfo, geometryBuffer, 0, VK_FALSE, dst, VK_NULL_HANDLE, scratchBuffer, 0);
        });
    }
    else
    {

        // Execute build
        VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
            if (supportUpdates)
            {
                vkCmdBuildAccelerationStructureNV(cmdBuffer, pInfo, VK_NULL_HANDLE, 0, update, dst, src ? dst : VK_NULL_HANDLE, scratchBuffer, 0);
            }
            else
            {
                vkCmdBuildAccelerationStructureNV(cmdBuffer, pInfo, VK_NULL_HANDLE, 0, VK_FALSE, dst, VK_NULL_HANDLE, scratchBuffer, 0);
            }
        });
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeAccelerationStructureKHR2
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VulkanHelper_InitializeAccelerationStructureInfoKHR* pInitializationInfo, uint32_t geometryCount, const VkAccelerationStructureGeometryKHR* pGeometry, const VkAccelerationStructureBuildRangeInfoKHR* pRangeInfo, VkBool32 supportUpdates)
{
    // Make sure all input buffers are fully populated before building this
    // acceleration structure.
    WaitForPendingResourceUpdates(device);

    // Get allocator
    VmaAllocator allocator = s_Allocators[device];
    NV_ASSERT(allocator);

    // Patching buffers
    std::vector<ScopedVmaBuffer*> vecTempBuffers;

    // Copy geometry
    std::vector<VkAccelerationStructureGeometryKHR> vecAccelerationStructureGeometryKHR(pGeometry, pGeometry + geometryCount);
    pGeometry = vecAccelerationStructureGeometryKHR.data();

    // Was this acceleration structure compacted as part of a previous copy?
    const VkBool32 isCompacted = [=]() -> VkBool32 {
        // This option was missing from the first version
        if (pInitializationInfo->version < 2)
        {
            return VK_FALSE;
        }

        return pInitializationInfo->isCompacted;
    }();

    // Patch instance buffer
    for (uint32_t i = 0; i < geometryCount; i++)
    {

        // Local copies
        VkAccelerationStructureGeometryKHR& geometry = vecAccelerationStructureGeometryKHR[i];
        VkAccelerationStructureGeometryInstancesDataKHR& instancesData = geometry.geometry.instances;

        // Handle geometry
        switch (geometry.geometryType)
        {
        case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
        {
            VkAccelerationStructureGeometryTrianglesDataKHR& triangles = geometry.geometry.triangles;

            // Patch vertex data
            if (triangles.vertexData.deviceAddress != 0)
            {
                if (pInitializationInfo->hasHostGeometryData)
                {
                    // Host data is always without indices
                    NV_ASSERT(triangles.indexType == VK_INDEX_TYPE_NONE_KHR);

                    // Handle is encoded in device address
                    Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(triangles.vertexData.deviceAddress));
                    if (handle != Serialization::DATABASE_HANDLE_INVALID)
                    {
                        // Read from database an copy into target
                        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
                        NV_ASSERT(pSrcData);

                        // Allocate destination buffer
                        const VkDeviceSize size = 3 * pRangeInfo[i].primitiveCount * triangles.vertexStride;
                        ScopedVmaBuffer* pVertexBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_ONLY);
                        vecTempBuffers.push_back(pVertexBuffer);

                        // Map destination data
                        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pVertexBuffer->Map());
                        NV_ASSERT(pDstData);

                        memcpy(pDstData, pSrcData, size);

                        // Get address
                        triangles.vertexData.deviceAddress = GetBufferAddress(device, pVertexBuffer->GetBuffer());
                    }
                    else
                    {
                        triangles.vertexData.deviceAddress = 0;
                    }
                }
                else
                {

                    // These are capture addresses we need to remap for replay
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, triangles.vertexData.deviceAddress);
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, triangles.indexData.deviceAddress);
                }
            }

            // Patch motion vertices
            VkAccelerationStructureGeometryMotionTrianglesDataNV* pAccelerationStructureGeometryMotionTrianglesDataNV = (VkAccelerationStructureGeometryMotionTrianglesDataNV*)FindStructure(VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_MOTION_TRIANGLES_DATA_NV, triangles.pNext);
            if (pAccelerationStructureGeometryMotionTrianglesDataNV && pAccelerationStructureGeometryMotionTrianglesDataNV->vertexData.deviceAddress != 0)
            {
                if (pInitializationInfo->hasHostGeometryData)
                {
                    // Host data is always without indices
                    NV_ASSERT(triangles.indexType == VK_INDEX_TYPE_NONE_KHR);

                    // Handle is encoded in device address
                    Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(pAccelerationStructureGeometryMotionTrianglesDataNV->vertexData.deviceAddress));
                    if (handle != Serialization::DATABASE_HANDLE_INVALID)
                    {
                        // Read from database an copy into target
                        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
                        NV_ASSERT(pSrcData);

                        // Allocate destination buffer
                        const VkDeviceSize size = 3 * pRangeInfo[i].primitiveCount * triangles.vertexStride;
                        ScopedVmaBuffer* pVertexMotionBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_ONLY);
                        vecTempBuffers.push_back(pVertexMotionBuffer);

                        // Map destination data
                        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pVertexMotionBuffer->Map());
                        NV_ASSERT(pDstData);

                        memcpy(pDstData, pSrcData, size);

                        // Get address
                        pAccelerationStructureGeometryMotionTrianglesDataNV->vertexData.deviceAddress = GetBufferAddress(device, pVertexMotionBuffer->GetBuffer());
                    }
                    else
                    {
                        pAccelerationStructureGeometryMotionTrianglesDataNV->vertexData.deviceAddress = 0;
                    }
                }
                else
                {

                    // These are capture addresses we need to remap for replay
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, pAccelerationStructureGeometryMotionTrianglesDataNV->vertexData.deviceAddress);
                }
            }

            // Patch opacity micromaps
            VkAccelerationStructureTrianglesOpacityMicromapEXT* pAccelerationStructureTrianglesOpacityMicromapEXT = (VkAccelerationStructureTrianglesOpacityMicromapEXT*)FindStructure(VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_EXT, triangles.pNext);
            if (pAccelerationStructureTrianglesOpacityMicromapEXT && pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress != 0)
            {
                if (pInitializationInfo->hasHostGeometryData)
                {
                    // Handle is encoded in device address
                    Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress));
                    if (handle != Serialization::DATABASE_HANDLE_INVALID)
                    {
                        // Read from database an copy into target
                        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
                        NV_ASSERT(pSrcData);

                        // Allocate index buffer
                        const VkDeviceSize size = pAccelerationStructureTrianglesOpacityMicromapEXT->indexStride * pRangeInfo[i].primitiveCount;
                        ScopedVmaBuffer* pMicromapIndexBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT), VMA_MEMORY_USAGE_CPU_TO_GPU);
                        vecTempBuffers.push_back(pMicromapIndexBuffer);

                        // Map destination data
                        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pMicromapIndexBuffer->Map());
                        NV_ASSERT(pDstData);

                        memcpy(pDstData, pSrcData, size);

                        // Get address
                        pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress = GetBufferAddress(device, pMicromapIndexBuffer->GetBuffer());
                    }
                    else
                    {
                        pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress = 0;
                    }
                }
                else
                {
                    // These are capture addresses we need to remap for replay
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress);
                }
            }

            // Patch transform data
            if (triangles.transformData.deviceAddress != 0)
            {
                if (pInitializationInfo->hasHostTransformData)
                {
                    // Handle is encoded in device address
                    Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(triangles.transformData.deviceAddress));
                    if (handle != Serialization::DATABASE_HANDLE_INVALID)
                    {
                        // Allocate destination buffer
                        const VkDeviceSize size = sizeof(VkTransformMatrixNV);
                        ScopedVmaBuffer* pTransformBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_ONLY);
                        vecTempBuffers.push_back(pTransformBuffer);

                        // Map destination data
                        VkTransformMatrixNV* pDstData = reinterpret_cast<VkTransformMatrixNV*>(pTransformBuffer->Map());
                        NV_ASSERT(pDstData);

                        // Read from database an copy into target
                        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
                        NV_ASSERT(pSrcData);
                        memcpy(pDstData, pSrcData, size);

                        // Get address
                        triangles.transformData.deviceAddress = GetBufferAddress(device, pTransformBuffer->GetBuffer());
                    }
                    else
                    {
                        triangles.transformData.deviceAddress = 0;
                    }
                }
                else
                {

                    // These are capture addresses we need to remap for replay
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, triangles.transformData.deviceAddress);
                }
            }
        }
        break;
        case VK_GEOMETRY_TYPE_AABBS_KHR:
        {

            VkAccelerationStructureGeometryAabbsDataKHR& aabbs = geometry.geometry.aabbs;

            if (pInitializationInfo->hasHostGeometryData)
            {
                // Handle is encoded in device address
                Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(aabbs.data.deviceAddress));
                if (handle != Serialization::DATABASE_HANDLE_INVALID)
                {
                    // Allocate destination buffer
                    const VkDeviceSize size = pRangeInfo[i].primitiveCount * aabbs.stride;
                    ScopedVmaBuffer* pAabbBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_ONLY);
                    vecTempBuffers.push_back(pAabbBuffer);

                    // Map destination data
                    VkAccelerationStructureInstanceKHR* pDstData = reinterpret_cast<VkAccelerationStructureInstanceKHR*>(pAabbBuffer->Map());
                    NV_ASSERT(pDstData);

                    // Read from database an copy into target
                    const VkAabbPositionsKHR* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const VkAabbPositionsKHR*, handle);
                    NV_ASSERT(pSrcData);
                    memcpy(pDstData, pSrcData, size);

                    // Get address
                    aabbs.data.deviceAddress = GetBufferAddress(device, pAabbBuffer->GetBuffer());
                }
                else
                {
                    aabbs.data.deviceAddress = 0;
                }
            }
            else
            {

                // These are capture addresses we need to remap for replay
                s_BufferAddressManager.RemapCaptureAddressForReplay(device, aabbs.data.deviceAddress);
            }
        }
        break;
        case VK_GEOMETRY_TYPE_INSTANCES_KHR:
        {
            // Data should be saved !arrayOfPointers
            NV_ASSERT(instancesData.arrayOfPointers == VK_FALSE);

            // Allocate destination buffer
            const VkDeviceSize size = pRangeInfo[i].primitiveCount * sizeof(VkAccelerationStructureInstanceKHR);
            ScopedVmaBuffer* pInstanceBuffer = new ScopedVmaBuffer(allocator, size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_ONLY);
            vecTempBuffers.push_back(pInstanceBuffer);

            // Map destination data
            VkAccelerationStructureInstanceKHR* pDstData = reinterpret_cast<VkAccelerationStructureInstanceKHR*>(pInstanceBuffer->Map());
            NV_ASSERT(pDstData);

            // Copy into scratch buffer
            if (pInitializationInfo->hasHostInstanceData)
            {
                // Decode handle from device address
                Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(instancesData.data.deviceAddress));
                if (handle == Serialization::DATABASE_HANDLE_INVALID)
                {
                    instancesData.data.deviceAddress = 0;
                    break;
                }

                // Read from database
                const VkAccelerationStructureInstanceKHR* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const VkAccelerationStructureInstanceKHR*, handle);
                NV_ASSERT(pSrcData);
                memcpy(pDstData, pSrcData, size);
            }
            else
            {
                // Lookup input buffer
                VkDeviceSize srcOffset = 0;
                VkBuffer srcBuffer = s_BufferAddressManager.LookupBufferFromReplayAddress(instancesData.data.deviceAddress, srcOffset);
                NV_ASSERT(srcBuffer != VK_NULL_HANDLE);
                NV_VK_VALIDATE(CopyBuffer(device, srcBuffer, srcOffset, pInstanceBuffer->GetBuffer(), 0, size));
            }

            // Loop instances to patch them
            for (uint32_t p = 0; p < pRangeInfo[i].primitiveCount; p++)
            {
                PatchGeometryInstanceKHR(device, pDstData[p]);
            }

            // Get address
            instancesData.data.deviceAddress = GetBufferAddress(device, pInstanceBuffer->GetBuffer());
        }
        break;
        default:
            break;
        }
    }

    // Lookup creation information
    const AccelerationStructureKHR* pAccelerationStructureKHR = s_AccelerationStructuresKHR.Lookup(accelerationStructure);
    NV_ASSERT(pAccelerationStructureKHR);

    const bool isUpdate = pInitializationInfo->mode == VK_BUILD_ACCELERATION_STRUCTURE_MODE_UPDATE_KHR;

    // Construct build information
    VkAccelerationStructureBuildGeometryInfoKHR buildGeometryInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
    buildGeometryInfo.type = pInitializationInfo->type;
    buildGeometryInfo.flags = pInitializationInfo->flags;
    buildGeometryInfo.mode = supportUpdates ? pInitializationInfo->mode : VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    buildGeometryInfo.srcAccelerationStructure = supportUpdates && isUpdate ? accelerationStructure : VK_NULL_HANDLE;
    buildGeometryInfo.dstAccelerationStructure = accelerationStructure;
    buildGeometryInfo.geometryCount = geometryCount;
    buildGeometryInfo.pGeometries = pGeometry;
    buildGeometryInfo.ppGeometries = nullptr;

    // Get max primitive count
    std::vector<uint32_t> vecMaxPrimitiveCounts(geometryCount);
    for (uint32_t i = 0; i < geometryCount; i++)
    {
        vecMaxPrimitiveCounts[i] = pRangeInfo[i].primitiveCount;
    }

    // Query build sizes
    const VkAccelerationStructureBuildSizesInfoKHR& buildSizesInfo = pAccelerationStructureKHR->sizeInfo;

    // If compacted, we need to first build a temporary un-compacted src AS that'll
    // be copied into the final target acceleration structure.
    VkAccelerationStructureKHR tempAs = VK_NULL_HANDLE;
    if (isCompacted)
    {
        // Create backing buffer for the temp src
        ScopedVmaBuffer* pScopedVmaBuffer = new ScopedVmaBuffer(s_Allocators[device], buildSizesInfo.accelerationStructureSize, VkBufferUsageFlagBits(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR), VMA_MEMORY_USAGE_GPU_ONLY);
        vecTempBuffers.push_back(pScopedVmaBuffer);

        // Create temp src
        VkAccelerationStructureCreateInfoKHR tempCreateInfo = *pAccelerationStructureKHR->pCreateInfoKHR;
        tempCreateInfo.size = pScopedVmaBuffer->Size();
        tempCreateInfo.buffer = pScopedVmaBuffer->GetBuffer();
        tempCreateInfo.offset = 0;
        vkCreateAccelerationStructureKHR(device, &tempCreateInfo, nullptr, &tempAs);
        NV_ASSERT(tempAs != VK_NULL_HANDLE);

        // Modify the build information to use this buffer
        buildGeometryInfo.flags |= VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR;
        buildGeometryInfo.dstAccelerationStructure = tempAs;
    }

    // Create scratch buffer (spec says this needs VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
    ScopedVmaBuffer* pScratchBuffer = new ScopedVmaBuffer(s_Allocators[device], buildSizesInfo.buildScratchSize, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, VMA_MEMORY_USAGE_GPU_ONLY);
    vecTempBuffers.push_back(pScratchBuffer);
    buildGeometryInfo.scratchData.deviceAddress = GetBufferAddress(device, pScratchBuffer->GetBuffer());

    // Execute build
    VkResult ret = VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [=](VkCommandBuffer cmdBuffer) {
        vkCmdBuildAccelerationStructuresKHR(cmdBuffer, 1, &buildGeometryInfo, &pRangeInfo);
    });
    NV_VK_VALIDATE(ret);

    // If compacted, perform a compacting copy to from the temporary src to the real object
    if (isCompacted)
    {
        // If we didn't resize the original compacted acceleration structure, we need to
        // make sure the post-build size is actually big enough.
        if (s_UnsafeCompactedAccelerationStructuresKHR)
        {
            // Query the size now (we could use a barrier instead of two command lists)
            VkQueryPool queryPool = VK_NULL_HANDLE;
            VkQueryPoolCreateInfo tempPoolCreateInfo = { VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO };
            tempPoolCreateInfo.queryType = VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR;
            tempPoolCreateInfo.queryCount = 1;
            NV_VK_VALIDATE(vkCreateQueryPool(device, &tempPoolCreateInfo, nullptr, &queryPool));
            NV_VK_VALIDATE(VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
                vkCmdResetQueryPool(cmdBuffer, queryPool, 0, 1);
                vkCmdWriteAccelerationStructuresPropertiesKHR(cmdBuffer, 1, &tempAs, VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR, queryPool, 0);
            }));
            VkDeviceSize compactedSizeOut = 0;
            NV_VK_VALIDATE(vkGetQueryPoolResults(device, queryPool, 0, 1, sizeof(VkDeviceSize), &compactedSizeOut, sizeof(VkDeviceSize), VK_QUERY_RESULT_WAIT_BIT));
            vkDestroyQueryPool(device, queryPool, nullptr);

            // If our destination isn't big enough, we have trouble
            if (compactedSizeOut > pAccelerationStructureKHR->pCreateInfoKHR->size)
            {
                NV_MESSAGE("Compacted acceleration structure size has change between capture and replay. This trace can only run without -%s", k_UnsafeCompactedAccelerationStructures);
                return NV_VK_VALIDATE(VK_ERROR_INCOMPATIBLE_DRIVER);
            }
        }

        // NOTE: Performance of this could be improved with a single command list and barriers
        ret = VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [=](VkCommandBuffer cmdBuffer) {
            VkCopyAccelerationStructureInfoKHR info = { VK_STRUCTURE_TYPE_COPY_ACCELERATION_STRUCTURE_INFO_KHR };
            info.src = tempAs;
            info.dst = accelerationStructure;
            info.mode = VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_KHR;
            vkCmdCopyAccelerationStructureKHR(cmdBuffer, &info);
        });
        NV_VK_VALIDATE(ret);

        // Clean up temp src
        vkDestroyAccelerationStructureKHR(device, tempAs, nullptr);
    }

    // VulkanHelper_ExecuteCommands is blocking so we can delete now
    for (ScopedVmaBuffer* pTempBuffer : vecTempBuffers)
    {
        delete pTempBuffer;
    }

    // Keep track of completed builds
    s_BuiltAccelerationStructuresKHR.insert(accelerationStructure);

    return ret;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeSerializedAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeSerializedAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, VkDeviceSize size, const void* pData)
{
    // The defined header structure for the serialized data consists of:
    //
    // VK_UUID_SIZE bytes of data matching VkPhysicalDeviceIDProperties::driverUUID
    //
    // VK_UUID_SIZE bytes of data identifying the compatibility for comparison using vkGetDeviceAccelerationStructureCompatibilityKHR
    //
    // A 64-bit integer of the total size matching the value queried using VK_QUERY_TYPE_ACCELERATION_STRUCTURE_SERIALIZATION_SIZE_KHR
    //
    // A 64-bit integer of the deserialized size to be passed in to VkAccelerationStructureCreateInfoKHR::size
    //
    // A 64-bit integer of the count of the number of acceleration structure handles following. This will be zero for a bottom-level
    // acceleration structure. For top-level acceleration structures this number is implementation-dependent; the number of and ordering
    // of the handles may not match the instance descriptions which were used to build the acceleration structure.

    struct Header
    {
        uint8_t driverUUID[VK_UUID_SIZE];
        uint8_t asUUID[VK_UUID_SIZE];
        uint64_t inSize;
        uint64_t outSize;
        uint64_t numHandles;
    };

    ScopedVmaBuffer srcBuffer = ScopedVmaBuffer(s_Allocators[device], size, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR), VMA_MEMORY_USAGE_CPU_TO_GPU);
    uint8_t* pBuffer = (uint8_t*)srcBuffer.Map();
    VkDeviceAddress* pAddresses = reinterpret_cast<VkDeviceAddress*>(pBuffer + sizeof(Header));
    Header* pHeader = reinterpret_cast<Header*>(pBuffer);
    memcpy(pHeader, pData, size);

    // This can happen if a gibberish acceleration structure was serialized
    if (pHeader->inSize == 0 || pHeader->outSize == 0)
    {
        NV_MESSAGE("FATAL: Unable to deserialize acceleration structure due to invalid header");
        return NV_VK_VALIDATE(VK_ERROR_UNKNOWN);
    }

    // Validate output size; we must have enough room to deserialize this
    const AccelerationStructureKHR* pAccelerationStructureKHR = s_AccelerationStructuresKHR.Lookup(accelerationStructure);
    NV_ASSERT(pAccelerationStructureKHR);
    if (pHeader->outSize > pAccelerationStructureKHR->pCreateInfoKHR->size)
    {
        NV_MESSAGE("FATAL: Unable to deserialize acceleration structure due to size mismatch");
        return NV_VK_VALIDATE(VK_ERROR_INCOMPATIBLE_DRIVER);
    }

    // Check API for compatibility
    VkAccelerationStructureVersionInfoKHR versionInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_VERSION_INFO_KHR };
    versionInfo.pVersionData = reinterpret_cast<uint8_t*>(pHeader);
    VkAccelerationStructureCompatibilityKHR compatibility;
    vkGetDeviceAccelerationStructureCompatibilityKHR(device, &versionInfo, &compatibility);
    if (compatibility == VK_ACCELERATION_STRUCTURE_COMPATIBILITY_INCOMPATIBLE_KHR)
    {
        NV_MESSAGE("FATAL: Unable to deserialize acceleration structure due to compatibility check failure");
        return NV_VK_VALIDATE(VK_ERROR_INCOMPATIBLE_DRIVER);
    }

    // Remap handles
    for (uint32_t i = 0; i < pHeader->numHandles; i++)
    {
        VkDeviceAddress srcAddress = pAddresses[i];
        auto itr = s_AccelerationStructureAddressMapKHR.find(srcAddress);
        NV_ASSERT(itr != s_AccelerationStructureAddressMapKHR.end());
        VkAccelerationStructureKHR srcAS = itr->second;
        VkAccelerationStructureDeviceAddressInfoKHR info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR };
        info.accelerationStructure = srcAS;
        VkDeviceAddress dstAddress = vkGetAccelerationStructureDeviceAddressKHR(device, &info);
        NV_ASSERT(dstAddress);
        pAddresses[i] = dstAddress;
    }
    srcBuffer.Flush();

    VkBufferDeviceAddressInfo deviceInfo = { VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO_KHR };
    deviceInfo.buffer = srcBuffer.GetBuffer();
    VkDeviceAddress deviceAddress = vkGetBufferDeviceAddressKHR(device, &deviceInfo);

    return VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
        VkCopyMemoryToAccelerationStructureInfoKHR info = { VK_STRUCTURE_TYPE_COPY_MEMORY_TO_ACCELERATION_STRUCTURE_INFO_KHR };
        info.src.deviceAddress = deviceAddress;
        info.dst = accelerationStructure;
        info.mode = VK_COPY_ACCELERATION_STRUCTURE_MODE_DESERIALIZE_KHR;
        vkCmdCopyMemoryToAccelerationStructureKHR(cmdBuffer, &info);
    });
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterAccelerationStructureHandleNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructureNV, uint64_t handle)
{
    s_AccelerationStructureAddressMapNV[handle] = accelerationStructureNV;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterAccelerationStructureAddressKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterAccelerationStructureAddressKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructureKHR, VkDeviceAddress address)
{
    s_AccelerationStructureAddressMapKHR[address] = accelerationStructureKHR;
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterRaytracingShaderGroupHandleNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleNV(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, const uint64_t* pHandle)
{
    // Old interface that assumed handle size of 16
    return VulkanHelper_RegisterRaytracingShaderGroupHandleNV(device, pipeline, groupNumber, 16, reinterpret_cast<const uint8_t*>(pHandle));
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterRaytracingShaderGroupHandleNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleNV(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, uint32_t shaderGroupHandleSize, const uint8_t* pHandle)
{
    // Cache shaderGroupHandleSize for the application
    static bool s_once = false;
    if (!s_once)
    {
        s_ShaderGroupHandleSize = shaderGroupHandleSize;
        s_once = true;
    }

    RaytracingHandleKey key = RaytracingHandleKey(pipeline, shaderGroupHandleSize, pHandle);
    s_RayTracingHandleMap[key] = RaytracingHandleValue{ pipeline, groupNumber };
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_RegisterRaytracingShaderGroupHandleKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterRaytracingShaderGroupHandleKHR(VkDevice device, VkPipeline pipeline, uint32_t groupNumber, uint32_t shaderGroupHandleSize, const uint8_t* pHandle)
{
    return VulkanHelper_RegisterRaytracingShaderGroupHandleNV(device, pipeline, groupNumber, shaderGroupHandleSize, pHandle);
}
#endif

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanHelper_InitializeSparseBindings
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeSparseBindings(VkDevice device, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo)
{
    // Get sparse queue
    const VkQueue queue = GetQueueWithFlagBit(device, VK_QUEUE_SPARSE_BINDING_BIT);

    // Fence used for all sparse bindings
    static VkFence s_fence = [=]() {
        VkFence fence = VK_NULL_HANDLE;
        VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
        vkCreateFence(device, &createInfo, nullptr, &fence);
        return fence;
    }();

    // Bind sparse
    NV_VK_VALIDATE(vkQueueBindSparse(queue, bindInfoCount, pBindInfo, s_fence));

    // Wait for completion
    while (vkWaitForFences(device, 1, &s_fence, VK_TRUE, 1000000000) != VK_SUCCESS)
    {
        NV_LOG("Waiting for sparse...");
    }
    vkResetFences(device, 1, &s_fence);

    return VK_SUCCESS;
}
#endif

#if defined(VK_KHR_timeline_semaphore)
//------------------------------------------------------------------------------
// VulkanHelper_InitializeTimelineSemaphore
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeTimelineSemaphore(VkDevice device, VkSemaphore semaphore, uint64_t startValue, uint64_t endValue)
{
    VkSemaphoreSignalInfoKHR signalInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO_KHR };
    signalInfo.semaphore = semaphore;
    signalInfo.value = startValue;
    if (s_DeviceVersion[device] < VK_API_VERSION_1_2)
    {
        NV_VK_VALIDATE(vkSignalSemaphoreKHR(device, &signalInfo));
    }
    else
    {
        NV_VK_VALIDATE(vkSignalSemaphore(device, &signalInfo));
    }

    auto itr = s_SemaphoreToInfoMap.find(semaphore);
    if (itr == s_SemaphoreToInfoMap.end())
    {
        return VK_ERROR_UNKNOWN;
    }

    itr->second.startValue = startValue;
    itr->second.endValue = endValue;
    itr->second.delta = (endValue - startValue) + 1;
    itr->second.minimalSignaledValue = endValue + 1;
    return VK_SUCCESS;
}
#endif

//------------------------------------------------------------------------------
// RecordTimelineSignal (helper)
//------------------------------------------------------------------------------
static void RecordTimelineSignal(SemaphoreInfo* pInfo, uint64_t signalValue)
{
    if (s_FrameIdx == 0)
    {
        pInfo->minimalSignaledValue = std::min(signalValue, pInfo->minimalSignaledValue);
    }
}

//------------------------------------------------------------------------------
// IsAvailableForTimelineWait (helper)
//------------------------------------------------------------------------------
static bool IsAvailableForTimelineWait(const SemaphoreInfo* pInfo, uint64_t waitValue)
{
    // Drop the semaphore values not confirmed to be signaled, part of the synchronization work
    // may not captured in our frame.
    return waitValue >= pInfo->minimalSignaledValue;
}

#if NV_USE_MANAGED_WINSYS
//------------------------------------------------------------------------------
// VulkanHelper_CreateWindowSystemSurface
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateWindowSystemSurface(VkInstance instance, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
#if defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.connection = *reinterpret_cast<xcb_connection_t**>(WindowSystemInstance().GetDisplayAddr());
    createInfo.window = *reinterpret_cast<xcb_window_t*>(WindowSystemInstance().GetWindowAddr());
    return vkCreateXcbSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    VkXlibSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.dpy = *reinterpret_cast<Display**>(WindowSystemInstance().GetDisplayAddr());
    createInfo.window = *reinterpret_cast<Window*>(WindowSystemInstance().GetWindowAddr());
    return vkCreateXlibSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.flags = 0;
    createInfo.hinstance = *reinterpret_cast<HINSTANCE*>(WindowSystemInstance().GetDisplayAddr());
    createInfo.hwnd = *reinterpret_cast<HWND*>(WindowSystemInstance().GetWindowAddr());
    return vkCreateWin32SurfaceKHR(instance, &createInfo, pAllocator, pSurface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.display = *reinterpret_cast<wl_display**>(WindowSystemInstance().GetDisplayAddr());
    createInfo.surface = *reinterpret_cast<wl_surface**>(WindowSystemInstance().GetWindowAddr());
    return vkCreateWaylandSurfaceKHR(instance, &createInfo, pAllocator, pSurface);
#elif defined(VK_USE_PLATFORM_D2D_KHR)

    // First physical device
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    for (const auto& physicalDevicePair : s_PhsyicalDeviceToInstanceMap)
    {
        if (physicalDevicePair.second == instance)
        {
            physicalDevice = physicalDevicePair.first;
            break;
        }
    }
    NV_ASSERT(physicalDevice != VK_NULL_HANDLE);

    // Default display properties
    VkDisplayPropertiesKHR displayProps = {};
    displayProps.display = VK_NULL_HANDLE;
    displayProps.displayName = nullptr;
    displayProps.physicalDimensions = VkExtent2D{ 0, 0 };
    displayProps.physicalResolution = VkExtent2D{ 0, 0 };
    displayProps.supportedTransforms = VkSurfaceTransformFlagsKHR(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR);
    displayProps.planeReorderPossible = VK_FALSE;
    displayProps.persistentContent = VK_FALSE;

    // Try to get a compatible display
    VkDisplayKHR display = VK_NULL_HANDLE;
    const VkResult getDisplayResult = VulkanHelper_GetCompatibleDisplay(physicalDevice, displayProps, &display);
    NV_ASSERT(getDisplayResult == VK_SUCCESS);

    // Window size
    const uint32_t width = uint32_t(WindowSystemInstance().GetNativeWindowWidth());
    const uint32_t height = uint32_t(WindowSystemInstance().GetNativeWindowHeight());

    // Default display mode properties
    VkDisplayModePropertiesKHR displayModeProps = {};
    displayModeProps.displayMode = VK_NULL_HANDLE;
    displayModeProps.parameters = {};
    displayModeProps.parameters.visibleRegion = VkExtent2D{ width, height };
    displayModeProps.parameters.refreshRate = 60000u;

    // Try to get a compatible display mode
    VkDisplayModeKHR displayMode = VK_NULL_HANDLE;
    const VkResult getDisplayModeResult = VulkanHelper_GetCompatibleDisplayMode(physicalDevice, display, displayModeProps, &displayMode);
    NV_ASSERT(getDisplayModeResult == VK_SUCCESS);

    // Try to create a display plane surface
    VkDisplaySurfaceCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.flags = VkDisplaySurfaceCreateFlagsKHR(0);
    createInfo.displayMode = displayMode;
    createInfo.planeIndex = 0u;
    createInfo.planeStackIndex = 0u;
    createInfo.transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.globalAlpha = 1.0f;
    createInfo.alphaMode = VK_DISPLAY_PLANE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.imageExtent = VkExtent2D{ width, height };
    return vkCreateDisplayPlaneSurfaceKHR(instance, &createInfo, pAllocator, pSurface);

#else
    // Shall not enter this code.
    return VK_SUCCESS;
#endif
}
#endif // NV_USE_MANAGED_WINSYS

//------------------------------------------------------------------------------
// VulkanHelper_RegisterObject
//------------------------------------------------------------------------------
VkResult VulkanHelper_RegisterObject(VkObjectType objectType, uint64_t object, uint64_t id)
{
    s_ObjectMap[id] = ObjectRecord{ objectType, object };
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_UpdateDescriptorSetsFromPackedWrites
//------------------------------------------------------------------------------
VkResult VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice device, uint32_t descriptorWriteCount, Serialization::DATABASE_HANDLE handle, VkDeviceSize dataSize, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
    // Get writes
    const VkWriteDescriptorSet* pDescriptorWritesOut = [&]() -> const VkWriteDescriptorSet* {
        // No pDescriptorWritesOut to on invalid (or empty) handle
        if (handle == Serialization::DATABASE_HANDLE_INVALID)
        {
            NV_ASSERT(descriptorWriteCount == 0);
            return nullptr;
        }

        auto itr = s_HydratedStructCache.find(handle.value);
        if (itr == s_HydratedStructCache.end())
        {
            // Load input from database
            const VkWriteDescriptorSet* pDescriptorWritesIn = NV_GET_RESOURCE_NOSCOPETRACKER(const VkWriteDescriptorSet*, handle);

            // Decode structure
            std::vector<uint8_t> blob(dataSize);
            NV::Vulkan::StructHydrator hydrator(blob, [](VkObjectType type, uint64_t object) {
                return LookupObject(type, object);
            });
            const VkWriteDescriptorSet* pOut = hydrator.Rehydrate(0, descriptorWriteCount, pDescriptorWritesIn);

            // Cache and return
            auto entry = std::make_pair(handle.value, std::move(blob));
            s_HydratedStructCache.emplace(std::move(entry));
            return pOut;
        }
        else
        {
            return reinterpret_cast<const VkWriteDescriptorSet*>(itr->second.data());
        }
    }();

    // Perform update
    VulkanReplay_UpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWritesOut, descriptorCopyCount, pDescriptorCopies);
    return VK_SUCCESS;
}

#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanHelper_CmdTraceRaysNV_FromDatabase
//------------------------------------------------------------------------------
VkResult VulkanHelper_CmdTraceRaysNV_FromDatabase(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, Serialization::DATABASE_HANDLE raygenShaderBindingTableHandle, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, Serialization::DATABASE_HANDLE missShaderBindingTableHandle, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, Serialization::DATABASE_HANDLE hitShaderBindingTableHandle, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, Serialization::DATABASE_HANDLE callableShaderBindingTableHandle, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth)
{
    // Get index for this trace call dependent on the override because it can be recorded multiple times
    uint32_t& traceRaysIdx = s_TraceRaysNVIdx[commandBuffer];

    // First time through we need to patch the SBT shader handles
    if (raygenShaderBindingTableHandle != Serialization::DATABASE_HANDLE_INVALID)
    {
        raygenShaderBindingTableBuffer = PatchShaderBindingTableNV_FromDatabase(traceRaysIdx, RayTracingShaderBindingTableType::RayGenShader, commandBuffer, raygenShaderBindingTableHandle, raygenShaderBindingOffset, 0);
    }
    if (missShaderBindingTableHandle != Serialization::DATABASE_HANDLE_INVALID)
    {
        missShaderBindingTableBuffer = PatchShaderBindingTableNV_FromDatabase(traceRaysIdx, RayTracingShaderBindingTableType::MissShader, commandBuffer, missShaderBindingTableHandle, missShaderBindingOffset, missShaderBindingStride);
    }
    if (hitShaderBindingTableHandle != Serialization::DATABASE_HANDLE_INVALID)
    {
        hitShaderBindingTableBuffer = PatchShaderBindingTableNV_FromDatabase(traceRaysIdx, RayTracingShaderBindingTableType::HitShader, commandBuffer, hitShaderBindingTableHandle, hitShaderBindingOffset, hitShaderBindingStride);
    }
    if (callableShaderBindingTableHandle != Serialization::DATABASE_HANDLE_INVALID)
    {
        callableShaderBindingTableBuffer = PatchShaderBindingTableNV_FromDatabase(traceRaysIdx, RayTracingShaderBindingTableType::CallableShader, commandBuffer, callableShaderBindingTableHandle, callableShaderBindingOffset, callableShaderBindingStride);
    }

    // Increase trace counter
    traceRaysIdx++;

    vkCmdTraceRaysNV(commandBuffer,
        raygenShaderBindingTableBuffer, 0,
        missShaderBindingTableBuffer, 0, missShaderBindingStride,
        hitShaderBindingTableBuffer, 0, hitShaderBindingStride,
        callableShaderBindingTableBuffer, 0, callableShaderBindingStride,
        width, height, depth);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_CmdTraceRaysKHR_FromDatabase
//------------------------------------------------------------------------------
VkResult VulkanHelper_CmdTraceRaysKHR_FromDatabase(VkCommandBuffer commandBuffer, const VulkanHelper_ShaderBindTable* pRaygen, const VulkanHelper_ShaderBindTable* pMiss, const VulkanHelper_ShaderBindTable* pHit, const VulkanHelper_ShaderBindTable* pCallable, uint32_t width, uint32_t height, uint32_t depth)
{
    // Get device
    VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

    // Create SBTs
    VkStridedDeviceAddressRegionKHR raygenRegion = ExtractShaderBindingTableKHR_FromDatabase(device, RayTracingShaderBindingTableType::RayGenShader, pRaygen);
    VkStridedDeviceAddressRegionKHR missRegion = ExtractShaderBindingTableKHR_FromDatabase(device, RayTracingShaderBindingTableType::MissShader, pMiss);
    VkStridedDeviceAddressRegionKHR hitRegion = ExtractShaderBindingTableKHR_FromDatabase(device, RayTracingShaderBindingTableType::HitShader, pHit);
    VkStridedDeviceAddressRegionKHR callableRegion = ExtractShaderBindingTableKHR_FromDatabase(device, RayTracingShaderBindingTableType::CallableShader, pCallable);

    vkCmdTraceRaysKHR(commandBuffer,
        pRaygen ? &raygenRegion : nullptr,
        pMiss ? &missRegion : nullptr,
        pHit ? &hitRegion : nullptr,
        pCallable ? &callableRegion : nullptr,
        width, height, depth);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_CmdTraceRaysKHR_FromDatabase2
//------------------------------------------------------------------------------
VkResult VulkanHelper_CmdTraceRaysKHR_FromDatabase2(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth)
{
    // Get device
    VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

    // Create SBTs
    VkStridedDeviceAddressRegionKHR raygenRegion = ExtractShaderBindingTableKHR_FromDatabase2(device, RayTracingShaderBindingTableType::RayGenShader, pRaygenShaderBindingTable);
    VkStridedDeviceAddressRegionKHR missRegion = ExtractShaderBindingTableKHR_FromDatabase2(device, RayTracingShaderBindingTableType::MissShader, pMissShaderBindingTable);
    VkStridedDeviceAddressRegionKHR hitRegion = ExtractShaderBindingTableKHR_FromDatabase2(device, RayTracingShaderBindingTableType::HitShader, pHitShaderBindingTable);
    VkStridedDeviceAddressRegionKHR callableRegion = ExtractShaderBindingTableKHR_FromDatabase2(device, RayTracingShaderBindingTableType::CallableShader, pCallableShaderBindingTable);

    vkCmdTraceRaysKHR(commandBuffer, &raygenRegion, &missRegion, &hitRegion, &callableRegion, width, height, depth);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_CmdBuildAccelerationStructuresInstanceKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CmdBuildAccelerationStructuresInstanceKHR(VkCommandBuffer commandBuffer, VkAccelerationStructureTypeKHR type, VkBuildAccelerationStructureFlagsKHR flags, VkBuildAccelerationStructureModeKHR mode, VkAccelerationStructureKHR srcAccelerationStructure, VkAccelerationStructureKHR dstAccelerationStructure, VkGeometryFlagsKHR geometryFlags, uint32_t instanceCount, const VulkanHelper_AccelerationStructureInstance* pSrc)
{
    // This might be a data collection error but we cannot replay it
    if (!pSrc)
    {
        NV_MESSAGE_ONCE("INFO: Seen empty TLAS build. Possible data collection error.");
        return VK_SUCCESS;
    }

    static std::map<const VulkanHelper_AccelerationStructureInstance*, std::function<void(VkCommandBuffer)>> k_cache;

    VULKAN_REPLAY_WRITE_LOCK();
    auto itr = k_cache.find(pSrc);

    if (itr == k_cache.end())
    {
        // Get device
        VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

        // Create instance buffer
        VkDeviceSize bufferSize = instanceCount * sizeof(VkAccelerationStructureInstanceKHR);
        ScopedVmaBuffer* pInstanceBuffer = new ScopedVmaBuffer(s_Allocators[device], bufferSize, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_TO_GPU);
        VkAccelerationStructureInstanceKHR* pDst = (VkAccelerationStructureInstanceKHR*)pInstanceBuffer->Map();

        // Populate instance buffer
        for (uint32_t i = 0; i < instanceCount; i++)
        {

            // Populate VkAccelerationStructureInstanceKHR
            memcpy(pDst[i].transform.matrix, pSrc[i].pTransform, sizeof(float) * 12);
            pDst[i].instanceCustomIndex = pSrc[i].instanceCustomIndex;
            pDst[i].mask = pSrc[i].mask;
            pDst[i].instanceShaderBindingTableRecordOffset = pSrc[i].instanceShaderBindingTableRecordOffset;
            pDst[i].flags = pSrc[i].flags;
            pDst[i].accelerationStructureReference = GetAccelerationStructureReferenceKHR(device, pSrc[i].accelerationStructure);
        }

        pInstanceBuffer->Unmap();

        // Create geometry (leaked for indirect lambda capture)
        VkAccelerationStructureGeometryKHR* pGeometry = new VkAccelerationStructureGeometryKHR;
        memset(pGeometry, 0, sizeof(VkAccelerationStructureGeometryKHR));
        pGeometry->sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
        pGeometry->geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
        pGeometry->geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
        pGeometry->geometry.instances.data.deviceAddress = GetBufferAddress(device, pInstanceBuffer->GetBuffer());
        pGeometry->flags = geometryFlags;

        // Create info
        VkAccelerationStructureBuildGeometryInfoKHR info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
        info.type = type;
        info.flags = flags;
        info.mode = mode;
        info.srcAccelerationStructure = srcAccelerationStructure;
        info.dstAccelerationStructure = dstAccelerationStructure;
        info.geometryCount = 1;
        info.pGeometries = pGeometry;

        // Get scratch buffer
        VkAccelerationStructureBuildSizesInfoKHR sizeInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
        vkGetAccelerationStructureBuildSizesKHR(device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &info, &instanceCount, &sizeInfo);
        ScopedVmaBuffer* pScratchBuffer = new ScopedVmaBuffer(s_Allocators[device], mode == VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ? sizeInfo.buildScratchSize : sizeInfo.updateScratchSize, VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT), VMA_MEMORY_USAGE_GPU_ONLY);
        info.scratchData.deviceAddress = GetBufferAddress(device, pScratchBuffer->GetBuffer());

        // Cache call to avoid allocations and parsing, etc.
        std::function<void(VkCommandBuffer cmdBuf)> fnDoCmd = [=](VkCommandBuffer cmdBuf) {
            // Execute call
            VkAccelerationStructureBuildRangeInfoKHR buildRangeInfo = {};
            buildRangeInfo.primitiveCount = instanceCount;
            const VkAccelerationStructureBuildRangeInfoKHR* pBuildRangeInfo = &buildRangeInfo;
            vkCmdBuildAccelerationStructuresKHR(cmdBuf, 1, &info, &pBuildRangeInfo);
        };
        itr = k_cache.insert(std::make_pair(pSrc, fnDoCmd)).first;
    }

    std::function<void(VkCommandBuffer cmdBuf)> fnDoCmd = itr->second;
    fnDoCmd(commandBuffer);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_CmdBuildAccelerationStructuresMotionInstanceKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CmdBuildAccelerationStructuresMotionInstanceKHR(VkCommandBuffer commandBuffer, VkAccelerationStructureTypeKHR type, VkBuildAccelerationStructureFlagsKHR flags, VkBuildAccelerationStructureModeKHR mode, VkAccelerationStructureKHR srcAccelerationStructure, VkAccelerationStructureKHR dstAccelerationStructure, VkGeometryFlagsKHR geometryFlags, uint32_t instanceCount, const VulkanHelper_AccelerationStructureMotionInstance* pSrc)
{
    static std::map<const VulkanHelper_AccelerationStructureMotionInstance*, std::function<void(VkCommandBuffer)>> k_cache;

    VULKAN_REPLAY_WRITE_LOCK();
    auto itr = k_cache.find(pSrc);

    if (itr == k_cache.end())
    {
        // Get device
        VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

        // Special version of VkAccelerationStructureMotionInstanceNV where the size is 160 as per the spec
        struct AccelerationStructureMotionInstance
        {
            VkAccelerationStructureMotionInstanceTypeNV type;
            VkFlags flags;
            VkAccelerationStructureMotionInstanceDataNV data;
            uint32_t padding;
        };
        static_assert(sizeof(AccelerationStructureMotionInstance) == 160, "size mismatch");

        // Create instance buffer
        VkDeviceSize bufferSize = instanceCount * sizeof(AccelerationStructureMotionInstance);
        ScopedVmaBuffer* pInstanceBuffer = new ScopedVmaBuffer(s_Allocators[device], bufferSize, VkBufferUsageFlags(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR), VMA_MEMORY_USAGE_CPU_TO_GPU);
        AccelerationStructureMotionInstance* pDst = (AccelerationStructureMotionInstance*)pInstanceBuffer->Map();

        // Populate instance buffer
        for (uint32_t i = 0; i < instanceCount; i++)
        {

            //
            const VulkanHelper_AccelerationStructureMotionInstance& src = pSrc[i];
            AccelerationStructureMotionInstance& dst = pDst[i];

            // Copy data
            dst.type = src.type;
            dst.flags = 0;
            switch (dst.type)
            {
            case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_STATIC_NV:
            {
                VkAccelerationStructureInstanceKHR& staticInstance = dst.data.staticInstance;
                memcpy(reinterpret_cast<float*>(&staticInstance.transform), src.pTransformT0, sizeof(VkTransformMatrixKHR));
                staticInstance.instanceCustomIndex = src.instanceCustomIndex;
                staticInstance.mask = src.mask;
                staticInstance.instanceShaderBindingTableRecordOffset = src.instanceShaderBindingTableRecordOffset;
                staticInstance.flags = src.flags;
                staticInstance.accelerationStructureReference = GetAccelerationStructureReferenceKHR(device, src.accelerationStructure);
                break;
            }
            case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_MATRIX_MOTION_NV:
            {
                VkAccelerationStructureMatrixMotionInstanceNV& matrixMotionInstance = dst.data.matrixMotionInstance;
                memcpy(reinterpret_cast<float*>(&matrixMotionInstance.transformT0), src.pTransformT0, sizeof(VkTransformMatrixKHR));
                memcpy(reinterpret_cast<float*>(&matrixMotionInstance.transformT1), src.pTransformT1, sizeof(VkTransformMatrixKHR));
                matrixMotionInstance.instanceCustomIndex = src.instanceCustomIndex;
                matrixMotionInstance.mask = src.mask;
                matrixMotionInstance.instanceShaderBindingTableRecordOffset = src.instanceShaderBindingTableRecordOffset;
                matrixMotionInstance.flags = src.flags;
                matrixMotionInstance.accelerationStructureReference = GetAccelerationStructureReferenceKHR(device, src.accelerationStructure);
                break;
            }
            case VK_ACCELERATION_STRUCTURE_MOTION_INSTANCE_TYPE_SRT_MOTION_NV:
            {
                VkAccelerationStructureSRTMotionInstanceNV& srtMotionInstance = dst.data.srtMotionInstance;
                memcpy(reinterpret_cast<float*>(&srtMotionInstance.transformT0), src.pTransformT0, sizeof(VkSRTDataNV));
                memcpy(reinterpret_cast<float*>(&srtMotionInstance.transformT1), src.pTransformT1, sizeof(VkSRTDataNV));
                srtMotionInstance.instanceCustomIndex = src.instanceCustomIndex;
                srtMotionInstance.mask = src.mask;
                srtMotionInstance.instanceShaderBindingTableRecordOffset = src.instanceShaderBindingTableRecordOffset;
                srtMotionInstance.flags = src.flags;
                srtMotionInstance.accelerationStructureReference = GetAccelerationStructureReferenceKHR(device, src.accelerationStructure);
                break;
            }
            default:
                break;
            }
        }

        pInstanceBuffer->Unmap();

        // Create geometry (leaked for indirect lambda capture)
        VkAccelerationStructureGeometryKHR* pGeometry = new VkAccelerationStructureGeometryKHR;
        memset(pGeometry, 0, sizeof(VkAccelerationStructureGeometryKHR));
        pGeometry->sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
        pGeometry->geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
        pGeometry->geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
        pGeometry->geometry.instances.data.deviceAddress = GetBufferAddress(device, pInstanceBuffer->GetBuffer());
        pGeometry->flags = geometryFlags;

        // Create info
        VkAccelerationStructureBuildGeometryInfoKHR info = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR };
        info.type = type;
        info.flags = flags;
        info.mode = mode;
        info.srcAccelerationStructure = srcAccelerationStructure;
        info.dstAccelerationStructure = dstAccelerationStructure;
        info.geometryCount = 1;
        info.pGeometries = pGeometry;

        // Get scratch buffer
        VkAccelerationStructureBuildSizesInfoKHR sizeInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };
        vkGetAccelerationStructureBuildSizesKHR(device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &info, &instanceCount, &sizeInfo);
        ScopedVmaBuffer* pScratchBuffer = new ScopedVmaBuffer(s_Allocators[device], mode == VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ? sizeInfo.buildScratchSize : sizeInfo.updateScratchSize, VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT), VMA_MEMORY_USAGE_GPU_ONLY);
        info.scratchData.deviceAddress = GetBufferAddress(device, pScratchBuffer->GetBuffer());

        // Cache call to avoid allocations and parsing, etc.
        std::function<void(VkCommandBuffer cmdBuf)> fnDoCmd = [=](VkCommandBuffer cmdBuf) {
            // Execute call
            VkAccelerationStructureBuildRangeInfoKHR buildRangeInfo = {};
            buildRangeInfo.primitiveCount = instanceCount;
            const VkAccelerationStructureBuildRangeInfoKHR* pBuildRangeInfo = &buildRangeInfo;
            vkCmdBuildAccelerationStructuresKHR(cmdBuf, 1, &info, &pBuildRangeInfo);
        };
        itr = k_cache.insert(std::make_pair(pSrc, fnDoCmd)).first;
    }

    std::function<void(VkCommandBuffer cmdBuf)> fnDoCmd = itr->second;
    fnDoCmd(commandBuffer);

    return VK_SUCCESS;
}
#endif

#if defined(VK_EXT_descriptor_buffer)
VkResult VulkanHelper_RegisterDescriptor_Sampler(VkDevice device, VkDescriptorType type, VkSampler sampler, size_t size, const void* pData)
{
    VkDescriptorGetInfoEXT info = { VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT };
    info.type = type;
    info.data.pSampler = &sampler;
    std::vector<uint8_t> data(size);
    VulkanReplay_GetDescriptorEXT(device, &info, size, data.data());
    if (memcpy(data.data(), pData, size) != 0)
    {
        NV_LOG("ERROR: Sampler descriptor data capture/replay mismatch");
        return VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR;
    }
    return VK_SUCCESS;
}
#endif

#if defined(VK_EXT_descriptor_buffer)
VkResult VulkanHelper_RegisterDescriptor_Image(VkDevice device, VkDescriptorType type, const VkDescriptorImageInfo* pInfo, size_t size, const void* pData)
{
    VkDescriptorGetInfoEXT info = { VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT };
    info.type = type;
    info.data.pSampledImage = pInfo;
    std::vector<uint8_t> data(size);
    VulkanReplay_GetDescriptorEXT(device, &info, size, data.data());
    if (memcpy(data.data(), pData, size) != 0)
    {
        NV_LOG("ERROR: Image descriptor data capture/replay mismatch");
        return VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR;
    }
    return VK_SUCCESS;
}
#endif

#if defined(VK_EXT_descriptor_buffer)
VkResult VulkanHelper_RegisterDescriptor_Buffer(VkDevice device, VkDescriptorType type, const VkDescriptorAddressInfoEXT* pAddressInfo, size_t size, const void* pData)
{
    VkDescriptorGetInfoEXT info = { VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT };
    info.type = type;
    info.data.pUniformBuffer = pAddressInfo;
    std::vector<uint8_t> data(size);
    VulkanReplay_GetDescriptorEXT(device, &info, size, data.data());
    if (memcpy(data.data(), pData, size) != 0)
    {
        NV_LOG("ERROR: Buffer descriptor data capture/replay mismatch");
        return VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR;
    }
    return VK_SUCCESS;
}
#endif

#if defined(VK_EXT_descriptor_buffer)
VkResult VulkanHelper_RegisterDescriptor_AccelerationStructure(VkDevice device, VkDescriptorType type, VkDeviceAddress accelerationStructure, size_t size, const void* pData)
{
    VkDescriptorGetInfoEXT info = { VK_STRUCTURE_TYPE_DESCRIPTOR_GET_INFO_EXT };
    info.type = type;
    info.data.accelerationStructure = accelerationStructure;
    std::vector<uint8_t> data(size);
    VulkanReplay_GetDescriptorEXT(device, &info, size, data.data());
    if (memcpy(data.data(), pData, size) != 0)
    {
        NV_LOG("ERROR: Acceleration structure descriptor data capture/replay mismatch");
        return VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR;
    }
    return VK_SUCCESS;
}
#endif

//------------------------------------------------------------------------------
// VulkanHelper_ReleaseDevice
//------------------------------------------------------------------------------
VkResult VulkanHelper_ReleaseDevice(VkDevice device)
{
    // We don't actually clean anything up
    return VulkanReplay_DeviceWaitIdle(device);
}

//------------------------------------------------------------------------------
// VulkanHelper_ReleaseInstance
//------------------------------------------------------------------------------
VkResult VulkanHelper_ReleaseInstance(VkInstance instance)
{
    // We don't actually clean anything up
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// GetMemoryRequirementsForBuffers
//------------------------------------------------------------------------------
static std::vector<VkMemoryRequirements> GetMemoryRequirementsForBuffers(VkDevice device, uint32_t bindCount, const VkBindBufferMemoryInfo* pBindBufferMemoryInfo)
{
    std::vector<VkMemoryRequirements> vecMemoryRequirements;
    for (uint32_t i = 0; i < bindCount; i++)
    {
        VkMemoryRequirements memoryRequirements;
        vkGetBufferMemoryRequirements(device, pBindBufferMemoryInfo[i].buffer, &memoryRequirements);
        vecMemoryRequirements.push_back(memoryRequirements);
    }
    return vecMemoryRequirements;
}

//------------------------------------------------------------------------------
// GetMemoryTypeBitsForImages
//------------------------------------------------------------------------------
static std::vector<VkMemoryRequirements> GetMemoryRequimentsForImages(VkDevice device, uint32_t bindCount, const VkBindImageMemoryInfo* pBindImageMemoryInfo)
{
    std::vector<VkMemoryRequirements> vecMemoryRequirements;
    for (uint32_t i = 0; i < bindCount; i++)
    {
        VkMemoryRequirements memoryRequirements;
        vkGetImageMemoryRequirements(device, pBindImageMemoryInfo[i].image, &memoryRequirements);
        vecMemoryRequirements.push_back(memoryRequirements);
    }
    return vecMemoryRequirements;
}

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// GetMemoryRequirementsForAccelerationStructuresNV
//------------------------------------------------------------------------------
static std::vector<VkMemoryRequirements> GetMemoryRequirementsForAccelerationStructuresNV(VkDevice device, uint32_t bindCount, const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV)
{
    std::vector<VkMemoryRequirements> vecMemoryRequirements;
    for (uint32_t i = 0; i < bindCount; i++)
    {
        const AccelerationStructureNV* pAccelerationStructure = s_AccelerationStructuresNV.Lookup(pBindAccelerationStructureMemoryInfoNV[i].accelerationStructure);
        vecMemoryRequirements.push_back(pAccelerationStructure->GetMemoryRequirements());
    }

    return vecMemoryRequirements;
}
#endif

#if defined(VK_KHR_video_queue)
//------------------------------------------------------------------------------
// GetMemoryTypeBitsForImages
//------------------------------------------------------------------------------
static std::vector<VkMemoryRequirements> GetMemoryRequimentsForVideoSessions(VkDevice device, uint32_t bindCount, const VkVideoSessionKHR* pVideoSession)
{
    // Ingore duplicates
    std::set<VkVideoSessionKHR> videoSessions;
    for (uint32_t i = 0; i < bindCount; i++)
    {
        videoSessions.insert(pVideoSession[i]);
    }

    std::vector<VkMemoryRequirements> vecMemoryRequirements;
    std::vector<VkVideoSessionMemoryRequirementsKHR> vecVideoSessionMemoryRequirements;
    for (auto videoSession : videoSessions)
    {
        uint32_t videoSessionMemoryRequirementsCount = 0;
        vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, &videoSessionMemoryRequirementsCount, nullptr);
        vecVideoSessionMemoryRequirements.resize(videoSessionMemoryRequirementsCount);
        for (uint32_t i = 0; i < videoSessionMemoryRequirementsCount; i++)
        {
            vecVideoSessionMemoryRequirements[i].sType = VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR;
        }
        vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, &videoSessionMemoryRequirementsCount, vecVideoSessionMemoryRequirements.data());
        for (const auto& requirements : vecVideoSessionMemoryRequirements)
        {
            vecMemoryRequirements.push_back(requirements.memoryRequirements);
        }
    }

    return vecMemoryRequirements;
}
#endif

//------------------------------------------------------------------------------
// BindBufferMemory
//------------------------------------------------------------------------------
static void BindBufferMemory(VkDevice device, uint32_t bindCount, const VkBindBufferMemoryInfo* pBinds)
{
    for (uint32_t i = 0; i < bindCount; i++)
    {
        const VkBindBufferMemoryInfo& bind = pBinds[i];
        if (s_DeviceVersion[device] >= VK_API_VERSION_1_1)
        {
            VulkanReplay_BindBufferMemory2(device, 1, &bind);
        }
#if defined(VK_KHR_bind_memory2)
        else if (HasExtension(device, VK_KHR_BIND_MEMORY_2_EXTENSION_NAME))
        {
            VulkanReplay_BindBufferMemory2KHR(device, 1, &bind);
        }
#endif
        else
        {
            VulkanReplay_BindBufferMemory(device, bind.buffer, bind.memory, bind.memoryOffset);
        }
        s_BoundBufferInfo[bind.buffer] = *pBinds;
    }
}

//------------------------------------------------------------------------------
// BindImageMemory
//------------------------------------------------------------------------------
static void BindImageMemory(VkDevice device, uint32_t bindCount, const VkBindImageMemoryInfo* pBinds)
{
    for (uint32_t i = 0; i < bindCount; i++)
    {
        const VkBindImageMemoryInfo& bind = pBinds[i];
        if (s_DeviceVersion[device] >= VK_API_VERSION_1_1)
        {
            VulkanReplay_BindImageMemory2(device, 1, &bind);
        }
#if defined(VK_KHR_bind_memory2)
        else if (HasExtension(device, VK_KHR_BIND_MEMORY_2_EXTENSION_NAME))
        {
            VulkanReplay_BindImageMemory2KHR(device, 1, &bind);
        }
#endif
        else
        {
            VulkanReplay_BindImageMemory(device, bind.image, bind.memory, bind.memoryOffset);
        }
    }
}

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// BindAccelerationStructureMemoryNV
//------------------------------------------------------------------------------
static void BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindCount, const VkBindAccelerationStructureMemoryInfoNV* pBinds)
{
    for (uint32_t i = 0; i < bindCount; i++)
    {
        const VkBindAccelerationStructureMemoryInfoNV& bind = pBinds[i];
        if (HasExtension(device, VK_NV_RAY_TRACING_EXTENSION_NAME))
        {
            VulkanReplay_BindAccelerationStructureMemoryNV(device, 1, &bind);
        }
    }
}
#endif

#if defined(VK_KHR_video_queue)
//------------------------------------------------------------------------------
// BindVideoSessionMemory
//------------------------------------------------------------------------------
static void BindVideoSessionMemory(VkDevice device, uint32_t bindCount, const VkVideoSessionKHR* pVideoSessions, const VkBindVideoSessionMemoryInfoKHR* pBinds)
{
    for (uint32_t i = 0; i < bindCount; i++)
    {
        const VkBindVideoSessionMemoryInfoKHR& bind = pBinds[i];
        if (HasExtension(device, VK_KHR_VIDEO_QUEUE_EXTENSION_NAME))
        {
            VulkanReplay_BindVideoSessionMemoryKHR(device, pVideoSessions[i], 1, &bind);
        }
    }
}
#endif

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanHelper_CreateAccelerationStructureNV
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateAccelerationStructureNV(VkDevice device, VkAccelerationStructureCreateInfoNV* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkAccelerationStructureNV* pAccelerationStructure)
{
#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->info.flags |= VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    return VulkanReplay_CreateAccelerationStructureNV(device, pCreateInfo, nullptr, pAccelerationStructure);
}
#endif

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanHelper_AllocateAndInitializeMemory
//------------------------------------------------------------------------------
VkResult VulkanHelper_AllocateAndInitializeMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, VkDeviceAddress address, uint32_t bufferBindCount, const VkBindBufferMemoryInfo* pBindBufferMemoryInfo, uint32_t imageBindCount, const VkBindImageMemoryInfo* pBindImageMemoryInfo, uint32_t accelerationStructureBindCount, const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV, VkDeviceMemory* pDeviceMemory)
{
    return VulkanHelper_AllocateAndInitializeMemory2(device, pAllocateInfo, address, bufferBindCount, pBindBufferMemoryInfo, imageBindCount, pBindImageMemoryInfo, accelerationStructureBindCount, pBindAccelerationStructureMemoryInfoNV, pDeviceMemory, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_AllocateAndInitializeMemory2
//------------------------------------------------------------------------------
VkResult VulkanHelper_AllocateAndInitializeMemory2(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, VkDeviceAddress address, uint32_t bufferBindCount, const VkBindBufferMemoryInfo* pBindBufferMemoryInfo, uint32_t imageBindCount, const VkBindImageMemoryInfo* pBindImageMemoryInfo, uint32_t accelerationStructureBindCount, const VkBindAccelerationStructureMemoryInfoNV* pBindAccelerationStructureMemoryInfoNV, VkDeviceMemory* pDeviceMemory, const uint8_t* pData)
{
    VulkanHelper_InitializeDeviceMemoryInfo initializeInfo = {};
    initializeInfo.address = address;
    initializeInfo.bufferBindCount = bufferBindCount;
    initializeInfo.pBindImageMemoryInfo = pBindImageMemoryInfo;
    initializeInfo.accelerationStructureBindCount = accelerationStructureBindCount;
    initializeInfo.pBindAccelerationStructureMemoryInfoNV = pBindAccelerationStructureMemoryInfoNV;
    return VulkanHelper_AllocateAndInitializeMemory3(device, pAllocateInfo, &initializeInfo, pDeviceMemory, pData);
}
#endif

//------------------------------------------------------------------------------
// VulkanHelper_AllocateAndInitializeMemory3
//------------------------------------------------------------------------------
VkResult VulkanHelper_AllocateAndInitializeMemory3(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VulkanHelper_InitializeDeviceMemoryInfo* pInitializeInfo, VkDeviceMemory* pMemory, const uint8_t* pData)
{
    VkDeviceAddress opaqueCaptureAddress = pInitializeInfo->address;
    uint32_t bufferBindCount = pInitializeInfo->bufferBindCount;
    auto pBindBufferMemoryInfo = pInitializeInfo->pBindBufferMemoryInfo;
    uint32_t imageBindCount = pInitializeInfo->imageBindCount;
    auto pBindImageMemoryInfo = pInitializeInfo->pBindImageMemoryInfo;
#if defined(VK_NV_ray_tracing)
    uint32_t accelerationStructureBindCountNV = pInitializeInfo->accelerationStructureBindCount;
    auto pBindAccelerationStructureMemoryInfoNV = pInitializeInfo->pBindAccelerationStructureMemoryInfoNV;
#endif
#if defined(VK_KHR_video_queue)
    uint32_t videoBindMemoryCount = pInitializeInfo->videoBindMemoryCount;
    auto pVideoSessions = pInitializeInfo->pVideoSessions;
    auto pVideoBindMemory = pInitializeInfo->pVideoBindMemory;
#endif

    // Local copy of allocation info
    VkMemoryAllocateInfo allocateInfo = *pAllocateInfo;

    // Get physical device
    const VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];

    // Get physical device memory properties
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

    // Get original memory property information
    const VkMemoryPropertyFlags capturePropertyFlags = s_CaptureMemoryProperties[physicalDevice].memoryTypes[pAllocateInfo->memoryTypeIndex].propertyFlags;
    const bool isHostVisible = !!(capturePropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

    // In some cases we do not actually allocate this memory object and instead JIT
    // allocate memory each individual resource at bind time.
    bool shouldAllocate = true;

    // If we know we have less memory than the capture system; we can try and trim
    // the allocation so that every bound item fits in the memory. A lot of applications
    // simply over-allocate and don't use the entire memory heap so we might be able to
    // save some space here.
    //
    // NOTE: We don't compress host memory because it's possible it'll be mapped later
    // and the bounds will go-past the mapped range.
    if (s_TrimDeviceMemory && !isHostVisible)
    {

        // See if we can pack this allocation
        VkDeviceSize trimSize = 0;

        for (uint32_t i = 0; i < bufferBindCount; i++)
        {
            VkBuffer buffer = pBindBufferMemoryInfo[i].buffer;
            auto itr = s_BufferMemoryRequirements.find(buffer);
            if (itr == s_BufferMemoryRequirements.end())
            {
                NV_MESSAGE("ERROR: Skipping unknown resource in trim operation");
                continue;
            }
            const VkMemoryRequirements& requirements = itr->second.replay;
            const VkDeviceSize size = requirements.size;
            const VkDeviceSize offset = pBindBufferMemoryInfo[i].memoryOffset;
            const VkDeviceSize end = offset + size;
            if (end > trimSize)
            {
                trimSize = end;
            }
        }

        for (uint32_t i = 0; i < imageBindCount; i++)
        {
            VkImage image = pBindImageMemoryInfo[i].image;
            auto itr = s_ImageMemoryRequirements.find(image);
            if (itr == s_ImageMemoryRequirements.end())
            {
                NV_MESSAGE("ERROR: Skipping unknown resource in trim operation");
                continue;
            }

            const VkMemoryRequirements& requirements = itr->second.replay;
            const VkDeviceSize size = requirements.size;
            const VkDeviceSize offset = pBindImageMemoryInfo[i].memoryOffset;
            const VkDeviceSize end = offset + size;
            if (end > trimSize)
            {
                trimSize = end;
            }
        }

#if defined(VK_NV_ray_tracing)
        for (uint32_t i = 0; i < accelerationStructureBindCountNV; i++)
        {
            VkAccelerationStructureNV accelerationStructure = pBindAccelerationStructureMemoryInfoNV[i].accelerationStructure;
            auto itr = s_AccelerationStructureMemoryRequirementsNV.find(accelerationStructure);
            if (itr == s_AccelerationStructureMemoryRequirementsNV.end())
            {
                NV_MESSAGE("ERROR: Skipping unknown resource in trim operation");
                continue;
            }
            const VkMemoryRequirements& requirements = itr->second.replay;
            const VkDeviceSize size = requirements.size;
            const VkDeviceSize offset = pBindAccelerationStructureMemoryInfoNV[i].memoryOffset;
            const VkDeviceSize end = offset + size;
            if (end > trimSize)
            {
                trimSize = end;
            }
        }
#endif

#if defined(VK_KHR_video_queue)
        for (uint32_t i = 0; i < videoBindMemoryCount; i++)
        {
            VkVideoSessionKHR videoSession = pVideoSessions[i];
            const VkBindVideoSessionMemoryInfoKHR& bindMemory = pVideoBindMemory[i];
            VideoSessionMemoryBindKey bindKey = std::make_pair(videoSession, bindMemory.memoryBindIndex);
            auto itr = s_VideoSessionRequirements.find(bindKey);
            if (itr == s_VideoSessionRequirements.end())
            {
                NV_MESSAGE("ERROR: Skipping unknown resource in trim operation");
                continue;
            }
            const VkMemoryRequirements& requirements = itr->second.replay;
            const VkDeviceSize size = requirements.size;
            const VkDeviceSize offset = bindMemory.memoryOffset;
            const VkDeviceSize end = offset + size;
            if (end > trimSize)
            {
                trimSize = end;
            }
        }
#endif

        // Try packing
        if (trimSize == 0)
        {
            NV_MESSAGE("WARNING: Skipping shrinking of allocation with no contents", allocateInfo.allocationSize);
        }
        else if (trimSize < allocateInfo.allocationSize)
        {
            NV_MESSAGE("NOTE: Shrinking allocation %u -> %u due to unused space (memoryTypeIndex: %u)", allocateInfo.allocationSize, trimSize, allocateInfo.memoryTypeIndex);
            allocateInfo.allocationSize = trimSize;
        }
    }

    // Helper to get a memory type index
    auto SuggestMemoryTypeIndex = [&](uint32_t ignore = -1) -> uint32_t {
        // Get memory requirements for all resources
        // NOTE: Not available for legacy interfaces. These will be null results in a fully populated flag to match
        // existing behavior.
        uint32_t memoryTypeBits = UINT32_MAX;
        for (const VkMemoryRequirements& memoryRequirements : GetMemoryRequirementsForBuffers(device, bufferBindCount, pBindBufferMemoryInfo))
        {
            memoryTypeBits = memoryTypeBits & memoryRequirements.memoryTypeBits;
        }
        for (const VkMemoryRequirements& memoryRequirements : GetMemoryRequimentsForImages(device, imageBindCount, pBindImageMemoryInfo))
        {
            memoryTypeBits = memoryTypeBits & memoryRequirements.memoryTypeBits;
        }
#if defined(VK_NV_ray_tracing)
        for (const VkMemoryRequirements& memoryRequirements : GetMemoryRequirementsForAccelerationStructuresNV(device, accelerationStructureBindCountNV, pBindAccelerationStructureMemoryInfoNV))
        {
            memoryTypeBits = memoryTypeBits & memoryRequirements.memoryTypeBits;
        }
#endif
#if defined(VK_KHR_video_queue)
        for (const VkMemoryRequirements& memoryRequirements : GetMemoryRequimentsForVideoSessions(device, videoBindMemoryCount, pVideoSessions))
        {
            memoryTypeBits = memoryTypeBits & memoryRequirements.memoryTypeBits;
        }
#endif

        // First try to find exactly matched memory type index
        for (uint32_t index : FindMemoryIndices(memoryProperties, memoryTypeBits, capturePropertyFlags))
        {
            if (index != ignore)
            {
                return index;
            }
        }

        // Try again masking out non-critical flags
        const VkMemoryPropertyFlags preferredFlags = capturePropertyFlags & VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        for (uint32_t index : FindMemoryIndices(memoryProperties, memoryTypeBits, preferredFlags))
        {
            if (index != ignore)
            {
                return index;
            }
        }

        // Try once more only keep required flags
        const VkMemoryPropertyFlags requiredFlags = capturePropertyFlags & VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        for (uint32_t index : FindMemoryIndices(memoryProperties, memoryTypeBits, requiredFlags))
        {
            if (index != ignore)
            {
                return index;
            }
        }

        // Failed to remap
        return uint32_t(-1);
    };

    // Check for memory type remapping
    if (s_UseReplayManagedMemoryAllocations)
    {

        // Never allocate with this flag
        shouldAllocate = false;
    }
    else if (s_SawMemoryTypeMismatch)
    {

        // Try and find new memory type index
        allocateInfo.memoryTypeIndex = SuggestMemoryTypeIndex();
    }

    // Don't allocate if we failed to find a suitable memory type
    if (allocateInfo.memoryTypeIndex == uint32_t(-1))
    {
        NV_MESSAGE("NOTE: Failed to find memory type compatible with memory property flags (%s) that is valid for all contained resources. Resources will be pool allocated", MemoryPropertyFlagsToString(capturePropertyFlags).c_str());
        shouldAllocate = false;
    }

    // If using imported host memory we need to create the initial allocation
    VkImportMemoryHostPointerInfoEXT* pImportMemoryHostPointerInfoEXT = reinterpret_cast<VkImportMemoryHostPointerInfoEXT*>(FindPNextStructure(&allocateInfo, VK_STRUCTURE_TYPE_IMPORT_MEMORY_HOST_POINTER_INFO_EXT));
    if (pImportMemoryHostPointerInfoEXT && !pImportMemoryHostPointerInfoEXT->pHostPointer)
    {
        VkPhysicalDeviceExternalMemoryHostPropertiesEXT physicalDeviceExternalMemoryHostPropertiesEXT = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_MEMORY_HOST_PROPERTIES_EXT };
        VkPhysicalDeviceProperties2 physicalDeviceProperties2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
        physicalDeviceProperties2.pNext = &physicalDeviceExternalMemoryHostPropertiesEXT;
        VulkanReplay_GetPhysicalDeviceProperties2(physicalDevice, &physicalDeviceProperties2);
        const VkDeviceSize alignment = physicalDeviceExternalMemoryHostPropertiesEXT.minImportedHostPointerAlignment;
        pImportMemoryHostPointerInfoEXT->pHostPointer = SYSTEM_ALIGNED_MALLOC(alignment, allocateInfo.allocationSize);
        NV_ASSERT(pImportMemoryHostPointerInfoEXT->pHostPointer);
    }

    // See if this was capture replay memory that already has VkMemoryAllocateFlagsInfo
    bool isCaptureReplay = false;
    VkMemoryAllocateFlagsInfo* pMemoryAllocateFlagsInfo = reinterpret_cast<VkMemoryAllocateFlagsInfo*>(FindPNextStructure(&allocateInfo, VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO));
    if (pMemoryAllocateFlagsInfo)
    {
        // In newer version of captures we use the user's original allocation info; not one we have modified.
        // As such, we need to inject some flags.
        if (pInitializeInfo->injectedCaptureReplay)
        {
            pMemoryAllocateFlagsInfo->flags |= VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT;
        }
        isCaptureReplay = !!(pMemoryAllocateFlagsInfo->flags & VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT);
    }

    // If we injected capture replay and this doesn't have VkMemoryAllocateFlagsInfo we need to add it
    if (pInitializeInfo->injectedCaptureReplay && !pMemoryAllocateFlagsInfo)
    {
        VkMemoryAllocateFlagsInfo* pMemoryAllocateFlagsInfo = new VkMemoryAllocateFlagsInfo;
        pMemoryAllocateFlagsInfo->sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
        pMemoryAllocateFlagsInfo->pNext = nullptr;
        pMemoryAllocateFlagsInfo->flags = VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT | VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT);
        pMemoryAllocateFlagsInfo->deviceMask = 0;
        AppendStructure(&allocateInfo, pMemoryAllocateFlagsInfo);
        isCaptureReplay = true;
    }

    // Inject a VkMemoryOpaqueCaptureAddressAllocateInfo structure to force a GPU address for replay.
    VkMemoryOpaqueCaptureAddressAllocateInfo* pMemoryOpaqueCaptureAddressAllocateInfo = nullptr;
    if (opaqueCaptureAddress != 0)
    {
        NV_THROW_IF(!isCaptureReplay, "Expected capture/replay bit set if opaque address is provided");
        const VkMemoryOpaqueCaptureAddressAllocateInfo* pExistingMemoryOpaqueCaptureAddressAllocateInfo = reinterpret_cast<const VkMemoryOpaqueCaptureAddressAllocateInfo*>(FindPNextStructure(&allocateInfo, VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO));
        if (pExistingMemoryOpaqueCaptureAddressAllocateInfo)
        {
            NV_THROW_IF(pExistingMemoryOpaqueCaptureAddressAllocateInfo->opaqueCaptureAddress != opaqueCaptureAddress, "Mismatched opaque address");
        }
        else
        {
            pMemoryOpaqueCaptureAddressAllocateInfo = new VkMemoryOpaqueCaptureAddressAllocateInfo;
            pMemoryOpaqueCaptureAddressAllocateInfo->sType = VK_STRUCTURE_TYPE_MEMORY_OPAQUE_CAPTURE_ADDRESS_ALLOCATE_INFO;
            pMemoryOpaqueCaptureAddressAllocateInfo->pNext = nullptr;
            pMemoryOpaqueCaptureAddressAllocateInfo->opaqueCaptureAddress = opaqueCaptureAddress;
            AppendStructure(&allocateInfo, pMemoryOpaqueCaptureAddressAllocateInfo);
        }
    }

    // We need associate this memory information with some kind non-null key
    // so we can later lookup memory meta information.
    static std::atomic<uint64_t> s_NullMemoryIdx(0);
    VkDeviceMemory nullMemoryKey = VkDeviceMemory(++s_NullMemoryIdx);
    s_DeviceMemoryInfo[nullMemoryKey] = DeviceMemoryInfo{ false, allocateInfo, capturePropertyFlags };

    // Perform allocation or assign a fake index to the handle to we can later lookup meta information
    VkResult result = VK_SUCCESS;
    if (shouldAllocate)
    {

        // Try allocation
        result = vkAllocateMemory(device, &allocateInfo, nullptr, pMemory);

        // If we can't get the same opaque address we probably in trouble
        if (result == VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS)
        {
            // This is probably bad if they are using memory in a SBT record
            NV_MESSAGE("ERROR: Failed to acquire capture/replay address for device memory allocation.");

            // Try again without capture/replay support.
            NV_MESSAGE("WARNING: Trying allocation without capture/replay suppport. This might be fatal depending on memory usage patterns.");
            pMemoryAllocateFlagsInfo->flags &= ~VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT;
            pMemoryOpaqueCaptureAddressAllocateInfo->opaqueCaptureAddress = 0;
            result = vkAllocateMemory(device, &allocateInfo, nullptr, pMemory);
        }

        // It's possible that we ran out of memory due to a heap size change; try and find a replacement
        if (result == VK_ERROR_OUT_OF_DEVICE_MEMORY)
        {
            // Log to user
            NV_MESSAGE("WARNING: Device memory allocation failed with VK_ERROR_OUT_OF_DEVICE_MEMORY (memoryTypeIndex: %u, size: %u)", allocateInfo.memoryTypeIndex, allocateInfo.allocationSize);

            // Advertise the vk-replay-memory-management option
            static bool s_once = false;
            if (!s_once)
            {
                NV_MESSAGE(" > INFO: Re-running with %s might help", k_ReplayMemoryManagment);
                s_once = true;
            }

            // Try get and get a new index; throw if not
            allocateInfo.memoryTypeIndex = SuggestMemoryTypeIndex(allocateInfo.memoryTypeIndex);
            if (allocateInfo.memoryTypeIndex == uint32_t(-1))
            {
                NV_MESSAGE(" > FATAL: Failed to find suiteable replacement memoryTypeIndex");
                NV_VK_VALIDATE(result);
            }

            // Try again
            NV_MESSAGE(" > INFO: Trying replacement (memoryTypeIndex: %u)", allocateInfo.memoryTypeIndex);
            result = vkAllocateMemory(device, &allocateInfo, nullptr, pMemory);

            // Fatal if this fails
            // NOTE: There might be a case where we can try even more memory types
            if (result != VK_SUCCESS)
            {
                NV_MESSAGE(" > FATAL: Failed to find suiteable replacement memoryTypeIndex");
                NV_VK_VALIDATE(result);
            }
        }

        // Make sure we got the same
        if (opaqueCaptureAddress)
        {
            // Get address
            const VkDeviceAddress opaqueReplayAddress = [&]() {
                VkDeviceMemoryOpaqueCaptureAddressInfo info = { VK_STRUCTURE_TYPE_DEVICE_MEMORY_OPAQUE_CAPTURE_ADDRESS_INFO };
                info.memory = *pMemory;
#if defined(VK_KHR_buffer_device_address)
                if (HasDeviceExtension(device, VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
                {
                    return vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, &info);
                }
#endif
                return vkGetDeviceMemoryOpaqueCaptureAddress(device, &info);
            }();

            // Log results; this is trouble if it doesn't match
            if (opaqueReplayAddress != opaqueCaptureAddress)
            {
                NV_MESSAGE("WARNING: Device memory (%s) failed to acquired replay address that matches opaque capture address.", GetObjectName(*pMemory).c_str());
                NV_MESSAGE(" > Capture: %s", DeviceAddressToString(opaqueCaptureAddress).c_str());
                NV_MESSAGE(" > Replay:  %s", DeviceAddressToString(opaqueReplayAddress).c_str());
            }
            else
            {
                NV_LOG("NOTE: Device memory (%s) acquired same opaque capture address: %s", GetObjectName(*pMemory).c_str(), DeviceAddressToString(opaqueCaptureAddress).c_str());
            }
        }

        s_DeviceMemoryInfo[*pMemory] = DeviceMemoryInfo{ true, allocateInfo, capturePropertyFlags };
    }
    else
    {
        *pMemory = nullMemoryKey;
    }

    // Log remap
    if (shouldAllocate && pAllocateInfo->memoryTypeIndex != allocateInfo.memoryTypeIndex)
    {
        NV_MESSAGE("NOTE: Device memory (%s) memoryTypeIndex remapped from %u to %u", GetObjectName(*pMemory).c_str(), pAllocateInfo->memoryTypeIndex, allocateInfo.memoryTypeIndex);
    }

    // Patch up buffer bind information
    std::vector<VkBindBufferMemoryInfo> vecBindBufferMemoryInfo(pBindBufferMemoryInfo, pBindBufferMemoryInfo + bufferBindCount);
    for (VkBindBufferMemoryInfo& info : vecBindBufferMemoryInfo)
    {
        if (s_SawMemorySizeOrAlignmentMismatch.find(uint64_t(info.buffer)) == s_SawMemorySizeOrAlignmentMismatch.end())
        {
            info.memory = *pMemory;
        }
        else
        {
            info.memory = nullMemoryKey;
        }
    }

    // Patch up image bind information
    std::vector<VkBindImageMemoryInfo> vecBindImageMemoryInfo(pBindImageMemoryInfo, pBindImageMemoryInfo + imageBindCount);
    for (VkBindImageMemoryInfo& info : vecBindImageMemoryInfo)
    {
        if (s_SawMemorySizeOrAlignmentMismatch.find(uint64_t(info.image)) == s_SawMemorySizeOrAlignmentMismatch.end())
        {
            info.memory = *pMemory;
        }
        else
        {
            info.memory = nullMemoryKey;
        }
    }

#if defined(VK_NV_ray_tracing)
    // Patch up acceleration structure bind information
    std::vector<VkBindAccelerationStructureMemoryInfoNV> vecBindAccelerationStructureMemoryInfo(pBindAccelerationStructureMemoryInfoNV, pBindAccelerationStructureMemoryInfoNV + accelerationStructureBindCountNV);
    for (VkBindAccelerationStructureMemoryInfoNV& info : vecBindAccelerationStructureMemoryInfo)
    {
        if (s_SawMemorySizeOrAlignmentMismatch.find(uint64_t(info.accelerationStructure)) == s_SawMemorySizeOrAlignmentMismatch.end())
        {
            info.memory = *pMemory;
        }
        else
        {
            info.memory = nullMemoryKey;
        }
    }
#endif

#if defined(VK_KHR_video_queue)
    // Patch up video bind information
    std::vector<VkBindVideoSessionMemoryInfoKHR> vecVideoBindMemories(pVideoBindMemory, pVideoBindMemory + videoBindMemoryCount);
    for (uint32_t i = 0; i < videoBindMemoryCount; i++)
    {
        VkVideoSessionKHR videoSession = pVideoSessions[i];
        VkBindVideoSessionMemoryInfoKHR& bind = vecVideoBindMemories[i];
        if (s_SawMemorySizeOrAlignmentMismatch.find(uint64_t(videoSession)) == s_SawMemorySizeOrAlignmentMismatch.end())
        {
            bind.memory = *pMemory;
        }
        else
        {
            bind.memory = nullMemoryKey;
        }
    }
#endif

    // Perform binds
    if (result == VK_SUCCESS)
    {
        BindBufferMemory(device, bufferBindCount, vecBindBufferMemoryInfo.data());
        BindImageMemory(device, imageBindCount, vecBindImageMemoryInfo.data());
#if defined(VK_NV_ray_tracing)
        BindAccelerationStructureMemoryNV(device, accelerationStructureBindCountNV, vecBindAccelerationStructureMemoryInfo.data());
#endif
#if defined(VK_KHR_video_queue)
        BindVideoSessionMemory(device, videoBindMemoryCount, pVideoSessions, vecVideoBindMemories.data());
#endif
    }

    // Lookup buffer addresses now that everything is bound
#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    if (SupportsBufferAddress(device))
    {
        for (const VkBindBufferMemoryInfo& info : vecBindBufferMemoryInfo)
        {
            VkBuffer buffer = info.buffer;
            auto itr = s_BufferCreateInfo.find(buffer);
            NV_ASSERT(itr != s_BufferCreateInfo.end());
            const VkBufferCreateInfo& bufferCreateInfo = itr->second;
            const bool canGetAddress = !!(bufferCreateInfo.usage & VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT);
            const bool isCaptureReplay = !!(bufferCreateInfo.flags & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT);
            if (canGetAddress || isCaptureReplay)
            {
                VkDeviceAddress bufferCaptureAddress = s_BufferAddressManager.LookupOpaqueCaptureAddress(buffer);
                VkDeviceAddress bufferReplayAddress = GetBufferAddress(device, buffer);
                NV_ASSERT(bufferReplayAddress != 0);
                if (bufferCaptureAddress != bufferReplayAddress)
                {
                    NV_MESSAGE("WARNING: Buffer (%s) failed to acquired matching opaque capture address", GetObjectName(buffer).c_str());
                    NV_MESSAGE(" > MemoryIdx: %u", allocateInfo.memoryTypeIndex);
                    NV_MESSAGE(" > Size:      %u", (uint32_t)bufferCreateInfo.size);
                    NV_MESSAGE(" > Flags:     %s", BufferCreateFlagsToString(bufferCreateInfo.flags).c_str());
                    NV_MESSAGE(" > Usage:     %s", BufferUsageFlagsToString(bufferCreateInfo.usage).c_str());
                    NV_MESSAGE(" > Capture:   %s", DeviceAddressToString(bufferCaptureAddress).c_str());
                    NV_MESSAGE(" > Replay:    %s", DeviceAddressToString(bufferReplayAddress).c_str());
                }

                s_BufferAddressManager.RegisterReplayBufferAddress(buffer, bufferReplayAddress, bufferCreateInfo.size);
            }
        }
    }
#endif

    // Populate initial data if provided
    if (pData)
    {

        // Populate initial data
        if (isHostVisible)
        {

            // Copy directly to host-visible memory
            void* pDstData = nullptr;
            vkMapMemory(device, *pMemory, 0, allocateInfo.allocationSize, 0, &pDstData);
            NV_ASSERT(pDstData);
            memcpy(pDstData, pData, allocateInfo.allocationSize);
            vkUnmapMemory(device, *pMemory);
        }
        else
        {

            // Populate host visible staging buffer
            ScopedVmaBuffer srcBuffer = ScopedVmaBuffer(s_Allocators[device], allocateInfo.allocationSize, VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT), VMA_MEMORY_USAGE_CPU_TO_GPU);
            NV_ASSERT(srcBuffer.IsValid());
            void* pStagingBufferData = srcBuffer.Map();
            memcpy(pStagingBufferData, pData, allocateInfo.allocationSize);
            srcBuffer.Unmap();

            // Create a temporary buffer bound to the whole allocation
            VkBuffer dstBuffer = VK_NULL_HANDLE;
            VkBufferCreateInfo dstBufferCreateInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
            dstBufferCreateInfo.size = allocateInfo.allocationSize;
            dstBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
            vkCreateBuffer(device, &dstBufferCreateInfo, nullptr, &dstBuffer);
            NV_ASSERT(dstBuffer != VK_NULL_HANDLE);
            vkBindBufferMemory(device, dstBuffer, *pMemory, 0);

            // Perform copy
            VkResult copyResult = VulkanHelper_ExecuteCommands(device, 0, VkQueueFlags(VK_QUEUE_TRANSFER_BIT), [&](VkCommandBuffer cmdBuf) {
                VkBufferCopy region = {};
                region.size = allocateInfo.allocationSize;
                vkCmdCopyBuffer(cmdBuf, srcBuffer.GetBuffer(), dstBuffer, 1, &region);
            });
            NV_VK_VALIDATE(copyResult);

            // Cleanup temporary
            vkDestroyBuffer(device, dstBuffer, nullptr);
        }
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanHelper_ResetDeviceMemory
//------------------------------------------------------------------------------
VkResult VulkanHelper_ResetDeviceMemory(VkDevice device, VkDeviceMemory deviceMemory, VkDeviceSize offset, VkDeviceSize size, const void* pData)
{
    // Populate host visible staging buffer
    ScopedVmaBuffer srcBuffer = ScopedVmaBuffer(s_Allocators[device], size, VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT), VMA_MEMORY_USAGE_CPU_TO_GPU);
    NV_ASSERT(srcBuffer.IsValid());
    void* pStagingBufferData = srcBuffer.Map();
    memcpy(pStagingBufferData, pData, size);
    srcBuffer.Unmap();

    // Create a temporary buffer bound to the whole allocation
    VkBuffer dstBuffer = VK_NULL_HANDLE;
    VkBufferCreateInfo dstBufferCreateInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
    dstBufferCreateInfo.size = size;
    dstBufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    vkCreateBuffer(device, &dstBufferCreateInfo, nullptr, &dstBuffer);
    NV_ASSERT(dstBuffer != VK_NULL_HANDLE);
    vkBindBufferMemory(device, dstBuffer, deviceMemory, 0);

    // Perform copy
    VkResult copyResult = VulkanHelper_ExecuteCommands(device, 0, VkQueueFlags(VK_QUEUE_TRANSFER_BIT), [&](VkCommandBuffer cmdBuf) {
        VkBufferCopy region = {};
        region.srcOffset = 0;
        region.dstOffset = offset;
        region.size = size;
        vkCmdCopyBuffer(cmdBuf, srcBuffer.GetBuffer(), dstBuffer, 1, &region);
    });
    NV_VK_VALIDATE(copyResult);

    // Cleanup temporary
    vkDestroyBuffer(device, dstBuffer, nullptr);

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateBuffer
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateBuffer(VkDevice device, VkBufferCreateInfo* pCreateInfo, VkDeviceAddress opaqueCaptureAddress, VkBuffer* pBuffer)
{
    // Forward to old API where opaque and device addresses were the same
    return VulkanHelper_CreateBuffer2(device, pCreateInfo, nullptr, opaqueCaptureAddress, opaqueCaptureAddress, pBuffer);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateBuffer2
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateBuffer2(VkDevice device, VkBufferCreateInfo* pCreateInfo, const VkMemoryRequirements* pRequirements, const VkDeviceAddress captureDeviceAddress, VkDeviceAddress opaqueCaptureAddress, VkBuffer* pBuffer)
{
    return VulkanHelper_CreateBuffer3(device, pCreateInfo, pRequirements, captureDeviceAddress, opaqueCaptureAddress, 0, nullptr, pBuffer);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateBuffer3(VkDevice device, VkBufferCreateInfo* pCreateInfo, const VkMemoryRequirements* pRequirements, const VkDeviceAddress captureDeviceAddress, VkDeviceAddress opaqueCaptureAddress, size_t opaqueHandleSize, const void* pOpaqueHandle, VkBuffer* pBuffer)
{
    // If this was created for capture/replay it'll either have a flag or an address provided
    const bool isCaptureReplay = (pCreateInfo->flags & VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT);

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    if (isCaptureReplay || captureDeviceAddress || opaqueCaptureAddress)
    {

        // Make sure we have the capture replay address
        pCreateInfo->flags |= VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT;

        // Should always have a device address for any capture/replay buffer
        //
        // The opaque address can be zero, though if the implementation didn't request opaque memory
        // for this specific buffer. On NVIDIA hardware, this is only non-zero for sparse buffers.
        NV_ASSERT(captureDeviceAddress != 0);

        if (s_DeviceVersion[device] >= VK_API_VERSION_1_2 || HasExtension(device, VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
        {

            // For the KHR version add VkBufferOpaqueCaptureAddressCreateInfo if not already there
            VkBufferOpaqueCaptureAddressCreateInfo* pBufferOpaqueCaptureAddressCreateInfo = (VkBufferOpaqueCaptureAddressCreateInfo*)FindStructure(VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO_KHR, pCreateInfo->pNext);
            if (!pBufferOpaqueCaptureAddressCreateInfo)
            {
                pBufferOpaqueCaptureAddressCreateInfo = new VkBufferOpaqueCaptureAddressCreateInfo;
                memset(pBufferOpaqueCaptureAddressCreateInfo, 0, sizeof(VkBufferOpaqueCaptureAddressCreateInfo));
                pBufferOpaqueCaptureAddressCreateInfo->sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO_KHR;
                pBufferOpaqueCaptureAddressCreateInfo->opaqueCaptureAddress = opaqueCaptureAddress;
                AppendStructure(pCreateInfo, pBufferOpaqueCaptureAddressCreateInfo);
            }
            else
            {
                NV_ASSERT(pBufferOpaqueCaptureAddressCreateInfo->opaqueCaptureAddress == opaqueCaptureAddress);
            }
        }
        else if (HasExtension(device, VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME))
        {

            // For the deprecated EXT version add VkBufferOpaqueCaptureAddressCreateInfo if not already there
            VkBufferDeviceAddressCreateInfoEXT* pBufferDeviceAddressCreateInfoEXT = (VkBufferDeviceAddressCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT, pCreateInfo->pNext);
            if (!pBufferDeviceAddressCreateInfoEXT)
            {
                pBufferDeviceAddressCreateInfoEXT = new VkBufferDeviceAddressCreateInfoEXT;
                memset(pBufferDeviceAddressCreateInfoEXT, 0, sizeof(VkBufferDeviceAddressCreateInfoEXT));
                pBufferDeviceAddressCreateInfoEXT->sType = VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO_KHR;
                pBufferDeviceAddressCreateInfoEXT->deviceAddress = captureDeviceAddress;
                AppendStructure(pCreateInfo, pBufferDeviceAddressCreateInfoEXT);
            }
            else
            {
                NV_ASSERT(pBufferDeviceAddressCreateInfoEXT->deviceAddress == opaqueCaptureAddress);
            }
        }
    }
#endif

    // Patch up invalid queue families
    std::vector<uint32_t> vecQueueFamilies;
    if (s_SawQueueFamilyMismatch && pCreateInfo->sharingMode == VK_SHARING_MODE_CONCURRENT && pCreateInfo->queueFamilyIndexCount > 0)
    {

        // Allocate locate storage
        vecQueueFamilies.reserve(pCreateInfo->queueFamilyIndexCount);

        // Add re-mapped values
        VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];
        std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[physicalDevice];
        for (uint32_t i = 0; i < pCreateInfo->queueFamilyIndexCount; i++)
        {
            uint32_t familyIndex = queueFamilyMap[pCreateInfo->pQueueFamilyIndices[i]];
            auto itr = std::find(vecQueueFamilies.begin(), vecQueueFamilies.end(), familyIndex);
            if (itr == vecQueueFamilies.end())
            {
                vecQueueFamilies.push_back(familyIndex);
            }
        }

        // Update create info
        pCreateInfo->queueFamilyIndexCount = static_cast<uint32_t>(vecQueueFamilies.size());
        pCreateInfo->pQueueFamilyIndices = vecQueueFamilies.data();
    }

    //  Add SRC/DST transfer flags necessary for population
    if (s_MinimizeValidationWarnings)
    {
        pCreateInfo->usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        pCreateInfo->usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    }

#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->flags |= VK_BUFFER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    // Real call
    const VkResult result = vkCreateBuffer(device, pCreateInfo, nullptr, pBuffer);

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    // If we fail with VK_ERROR_INVALID_DEVICE_ADDRESS_EXT try again without an opaque address. This is OK in some
    // cases for KHR ray tracing where buffer device addresses are used but not indirectly in shaders.
    if (isCaptureReplay && result == VK_ERROR_INVALID_DEVICE_ADDRESS_EXT)
    {
        NV_LOG("WARNING: Buffer failed to acquire opaque capture replay address (%s). This may result in issues if this address is indirectly accessed inside a shader", DeviceAddressToString(opaqueCaptureAddress).c_str());
        pCreateInfo->flags &= ~VK_BUFFER_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT;
        RemovePNextStructure(pCreateInfo, VK_STRUCTURE_TYPE_BUFFER_OPAQUE_CAPTURE_ADDRESS_CREATE_INFO_KHR);
        RemovePNextStructure(pCreateInfo, VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_CREATE_INFO_EXT);
        return VulkanHelper_CreateBuffer(device, pCreateInfo, opaqueCaptureAddress, pBuffer);
    }
#endif

    // Failures at this point are fatal
    NV_VK_VALIDATE(result);

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    // Make sure we got the same buffer address
    //
    // This only needs to be done by buffers with a valid opaqueCaptureAddress which
    // means the allocation was done at the buffer level (opposed to memory).
    if (isCaptureReplay && opaqueCaptureAddress)
    {
        VkDeviceAddress replayDeviceAddress = GetBufferAddress(device, *pBuffer);
        NV_ASSERT(replayDeviceAddress != 0);
        if (captureDeviceAddress != replayDeviceAddress)
        {
            NV_MESSAGE("WARNING: Buffer (%s) failed to acquired matching device address", GetObjectName(*pBuffer).c_str());
            NV_MESSAGE(" > Size:      %u", (uint32_t)pCreateInfo->size);
            NV_MESSAGE(" > Flags:     %s", BufferCreateFlagsToString(pCreateInfo->flags).c_str());
            NV_MESSAGE(" > Usage:     %s", BufferUsageFlagsToString(pCreateInfo->usage).c_str());
            NV_MESSAGE(" > Capture:   %s", DeviceAddressToString(captureDeviceAddress).c_str());
            NV_MESSAGE(" > Replay:    %s", DeviceAddressToString(replayDeviceAddress).c_str());
        }
        else
        {
            NV_LOG("NOTE: Buffer (%s) acquired same device address: %s", GetObjectName(*pBuffer).c_str(), DeviceAddressToString(opaqueCaptureAddress).c_str());
        }
    }
#endif

    // Store create information
    s_BufferCreateInfo[*pBuffer] = *pCreateInfo;

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    // Store device address
    if (result == VK_SUCCESS && captureDeviceAddress != 0)
    {
        s_BufferAddressManager.RegisterCaptureBufferAddress(*pBuffer, pCreateInfo, captureDeviceAddress);
    }
#endif

    // Validate memory requirements for this buffer
    if (result == VK_SUCCESS && pRequirements)
    {
        VulkanHelper_ValidateBufferMemoryRequirements(device, *pBuffer, pRequirements);
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateSampler
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateSampler(VkDevice device, VkSamplerCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkSampler* pSampler)
{
#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->flags |= VK_SAMPLER_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    return VulkanReplay_CreateSampler(device, pCreateInfo, nullptr, pSampler);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateImage
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateImage(VkDevice device, VkImageCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkImage* pImage)
{
#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->flags |= VK_IMAGE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    return VulkanReplay_CreateImage(device, pCreateInfo, nullptr, pImage);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateImageView
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateImageView(VkDevice device, VkImageViewCreateInfo* pCreateInfo, size_t opaqueHandleSize, const void* pOpaqueHandle, VkImageView* pImageView)
{
    // It's possible this image view is part of a swapchain not actively used in the capture
    if (pCreateInfo->image == VK_NULL_HANDLE)
    {
        return VK_SUCCESS;
    }

#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->flags |= VK_IMAGE_VIEW_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    return VulkanReplay_CreateImageView(device, pCreateInfo, nullptr, pImageView);
}

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanHelper_CreateAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateAccelerationStructureKHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure)
{
    // The first version didn't support compaction
    return VulkanHelper_CreateAccelerationStructure2KHR(device, pCreateInfo, captureAddress, pBuildInfo, pMaxPrimitiveCount, pAccelerationStructure, VK_FALSE);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateAccelerationStructure2KHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateAccelerationStructure2KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted)
{
    return VulkanHelper_CreateAccelerationStructure3KHR(device, pCreateInfo, captureAddress, pBuildInfo, pMaxPrimitiveCount, pAccelerationStructure, isCompacted, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateAccelerationStructure3KHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateAccelerationStructure3KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted, const VkAccelerationStructureBuildSizesInfoKHR* pCaptureSizeInfo)
{
    return VulkanHelper_CreateAccelerationStructure4KHR(device, pCreateInfo, captureAddress, pBuildInfo, pMaxPrimitiveCount, pAccelerationStructure, isCompacted, nullptr, 0, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_CreateAccelerationStructure4KHR
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateAccelerationStructure4KHR(VkDevice device, VkAccelerationStructureCreateInfoKHR* pCreateInfo, VkDeviceAddress captureAddress, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCount, VkAccelerationStructureKHR* pAccelerationStructure, VkBool32 isCompacted, const VkAccelerationStructureBuildSizesInfoKHR* pCaptureSizeInfo, size_t opaqueHandleSize, const void* pOpaqueHandle)
{
    if (captureAddress == 0)
    {
        NV_LOG("WARNING: Acceleration structure has no capture address; this is unexpected and potential fatal if used.");
    }

    // Get size info
    //
    // Note the sizes at CREATE time must be respected at BUILD time. You cannot
    // query the scratch size using the the build time information as they might
    // actually be different.
    VkAccelerationStructureBuildSizesInfoKHR replaySizeInfo = { VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR };

    // Only query size if used
    if (pBuildInfo->geometryCount > 0)
    {
        vkGetAccelerationStructureBuildSizesKHR(device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, pBuildInfo, pMaxPrimitiveCount, &replaySizeInfo);
    }

    // Make sure capture buffer is large enough for this acceleration structure
    //
    // Acceleration structures have a chicken/egg problem in that we only know the
    // size of the compacted acceleration structure after a un-compacted src acceleration
    // structure is created, built, and queried. Since the flow of C++ captures is
    // create/initialize we cannot easily handle this pattern without introducing a totally
    // new pattern. As such, we need to be conservative and over-allocate the compacted
    // acceleration structure. We may revisit this later.
    if (pBuildInfo->geometryCount > 0 && replaySizeInfo.accelerationStructureSize > pCreateInfo->size)
    {

        if (isCompacted)
        {
            if (s_UnsafeCompactedAccelerationStructuresKHR)
            {
                goto do_build;
            }
            NV_MESSAGE("INFO: Overallocating compacted acceleration structure (%d > %d)", replaySizeInfo.accelerationStructureSize, pCreateInfo->size);
            NV_MESSAGE_ONCE("> NOTE: This behavior can be changed with (%s) but may lead to instability if the compact size changes between capture & replay", k_UnsafeCompactedAccelerationStructures);
        }
        else
        {
            NV_MESSAGE("INFO: Acceleration structure size mismatch (%d > %d). Allocating new managed buffer", replaySizeInfo.accelerationStructureSize, pCreateInfo->size);
        }

        ScopedVmaBuffer* pBuffer = new ScopedVmaBuffer(s_Allocators[device], replaySizeInfo.accelerationStructureSize, VkBufferUsageFlagBits(VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR), VMA_MEMORY_USAGE_GPU_ONLY);
        pCreateInfo->size = replaySizeInfo.accelerationStructureSize;
        pCreateInfo->buffer = pBuffer->GetBuffer();
        pCreateInfo->offset = 0;
    }

do_build:

#if defined(VK_EXT_descriptor_buffer)
    VkOpaqueCaptureDescriptorDataCreateInfoEXT opaqueInfo = { VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT };
    if (pOpaqueHandle)
    {
        pCreateInfo->createFlags |= VK_ACCELERATION_STRUCTURE_CREATE_DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT;
        VkOpaqueCaptureDescriptorDataCreateInfoEXT* pOpaqueCaptureDescriptorDataCreateInfoEXT = (VkOpaqueCaptureDescriptorDataCreateInfoEXT*)FindStructure(VK_STRUCTURE_TYPE_OPAQUE_CAPTURE_DESCRIPTOR_DATA_CREATE_INFO_EXT, pCreateInfo->pNext);
        if (!pOpaqueCaptureDescriptorDataCreateInfoEXT)
        {
            pOpaqueCaptureDescriptorDataCreateInfoEXT = &opaqueInfo;
        }
        pOpaqueCaptureDescriptorDataCreateInfoEXT->opaqueCaptureDescriptorData = pOpaqueHandle;
        AppendStructure(pCreateInfo, pOpaqueCaptureDescriptorDataCreateInfoEXT);
    }
#endif

    const VkResult result = NV_VK_VALIDATE(vkCreateAccelerationStructureKHR(device, pCreateInfo, nullptr, pAccelerationStructure));

    if (result == VK_SUCCESS)
    {
        AccelerationStructureKHR& myAccelerationStructureKHR = s_AccelerationStructuresKHR.Register(*pAccelerationStructure, device, pCreateInfo, replaySizeInfo);
        if (captureAddress != 0)
        {
            s_AccelerationStructureAddressMapKHR[captureAddress] = *pAccelerationStructure;
        }
        s_AccelerationStructureBuffers.insert(pCreateInfo->buffer);

        // See if the replay should manage all the scart
        myAccelerationStructureKHR.replayManagedScratch = [&]() -> bool {
            // If this an old capture without this information assume we need to rebuild
            if (!pCaptureSizeInfo)
            {
                return true;
            }

            // See if scratch sizes changed
            if (replaySizeInfo.buildScratchSize > pCaptureSizeInfo->buildScratchSize)
            {
                NV_LOG("INFO: Acceleration structure build scratch size mismatch (%d > %d). Will allocating managed buffer at build time.", replaySizeInfo.buildScratchSize, pCaptureSizeInfo->buildScratchSize);
                return true;
            }
            if (replaySizeInfo.updateScratchSize > pCaptureSizeInfo->updateScratchSize)
            {
                NV_LOG("INFO: Acceleration structure update scratch size mismatch (%d > %d). Will allocating managed buffer at update time.", replaySizeInfo.updateScratchSize, pCaptureSizeInfo->updateScratchSize);
                return true;
            }

            // Sizes are OK
            return false;
        }();
    }

    return result;
}
#endif

#if defined(VK_EXT_opacity_micromap)
//------------------------------------------------------------------------------
// VulkanHelper_CreateMicromapEXT
//------------------------------------------------------------------------------
VkResult VulkanHelper_CreateMicromapEXT(VkDevice device, VkMicromapCreateInfoEXT* pCreateInfo, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapEXT* pMicromapEXT, VkBool32 isCompacted, const VkMicromapBuildSizesInfoEXT* pCaptureSizeInfo)
{
    // Get size info
    //
    // Note the sizes at CREATE time must be respected at BUILD time. You cannot
    // query the scratch size using the the build time information as they might
    // actually be different.
    VkMicromapBuildSizesInfoEXT replaySizeInfo = { VK_STRUCTURE_TYPE_MICROMAP_BUILD_SIZES_INFO_EXT };

    // Only query size if used
    if (pBuildInfo->usageCountsCount > 0)
    {
        vkGetMicromapBuildSizesEXT(device, VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, pBuildInfo, &replaySizeInfo);
    }

    // Make sure capture buffer is large enough for this micromap
    //
    // Micromaps have a chicken/egg problem in that we only know the size of the
    // compacted micromap after a un-compacted src micromap is created, built,
    // and queried. Since the flow of C++ captures is create/initialize we cannot
    // easily handle this pattern without introducing a totally new pattern. As such,
    // we need to be conservative and over-allocate the compacted micromap.
    if (pBuildInfo->usageCountsCount > 0 && replaySizeInfo.micromapSize > pCreateInfo->size)
    {
        if (isCompacted)
        {
            if (s_UnsafeCompactedAccelerationStructuresKHR)
            {
                goto do_build;
            }
            NV_MESSAGE("INFO: Overallocating compacted micromap (%d > %d)", replaySizeInfo.micromapSize, pCreateInfo->size);
            NV_MESSAGE_ONCE("> NOTE: This behavior can be changed with (%s) but may lead to instability if the compact size changes between capture & replay", k_UnsafeCompactedAccelerationStructures);
        }
        else
        {
            NV_MESSAGE("INFO: Micromap size mismatch (%d > %d). Allocating new managed buffer", replaySizeInfo.micromapSize, pCreateInfo->size);
        }

        ScopedVmaBuffer* pBuffer = new ScopedVmaBuffer(s_Allocators[device], replaySizeInfo.micromapSize, VkBufferUsageFlagBits(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT), VMA_MEMORY_USAGE_GPU_ONLY);
        pCreateInfo->size = replaySizeInfo.micromapSize;
        pCreateInfo->buffer = pBuffer->GetBuffer();
        pCreateInfo->offset = 0;
    }

do_build:

    const VkResult result = NV_VK_VALIDATE(vkCreateMicromapEXT(device, pCreateInfo, nullptr, pMicromapEXT));

    if (result == VK_SUCCESS)
    {
        MicromapEXT& myMicromapEXT = s_Micromaps.Register(*pMicromapEXT, device, pCreateInfo, replaySizeInfo);
        s_MicromapBuffers.insert(pCreateInfo->buffer);

        // See if the replay should manage all the scratch data
        myMicromapEXT.replayManagedScratch = [&]() -> bool {
            // If this an old capture without this information assume we need to rebuild
            if (!pCaptureSizeInfo)
            {
                return true;
            }

            // See if scratch sizes changed
            if (replaySizeInfo.buildScratchSize > pCaptureSizeInfo->buildScratchSize)
            {
                NV_LOG("INFO: Micromap build scratch size mismatch (%d > %d). Will allocating managed buffer at build time.", replaySizeInfo.buildScratchSize, pCaptureSizeInfo->buildScratchSize);
                return true;
            }

            // Sizes are OK
            return false;
        }();
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanHelper_InitializeMicromapEXT
//------------------------------------------------------------------------------
VkResult VulkanHelper_InitializeMicromapEXT(VkDevice device, VkMicromapEXT micromapEXT, const VkMicromapBuildInfoEXT* pBuildInfo, VkDeviceSize dataSize, VkDeviceSize triangleArraySize, VkBool32 isCompacted)
{
    // Make sure all input buffers are fully populated before building this micromap
    WaitForPendingResourceUpdates(device);

    // Get allocator
    VmaAllocator allocator = s_Allocators[device];
    NV_ASSERT(allocator);

    // Copy build info
    VkMicromapBuildInfoEXT buildInfo = *pBuildInfo;

    // Patching buffers
    std::vector<ScopedVmaBuffer*> vecTempBuffers;

    // Patch data buffer
    {
        // Allocate destination buffer
        ScopedVmaBuffer* pDataBuffer = new ScopedVmaBuffer(allocator, dataSize, VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT), VMA_MEMORY_USAGE_CPU_TO_GPU);
        vecTempBuffers.push_back(pDataBuffer);

        // Read from database an copy into target
        Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(buildInfo.data.deviceAddress));
        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
        NV_ASSERT(pSrcData);

        // Map destination data
        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pDataBuffer->Map());
        NV_ASSERT(pDstData);

        memcpy(pDstData, pSrcData, dataSize);

        // Get address
        buildInfo.data.deviceAddress = GetBufferAddress(device, pDataBuffer->GetBuffer());
    }

    // Patch triangle array buffer
    {
        // Allocate destination buffer
        ScopedVmaBuffer* pTriangleArrayBuffer = new ScopedVmaBuffer(allocator, triangleArraySize, VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT), VMA_MEMORY_USAGE_CPU_TO_GPU);
        vecTempBuffers.push_back(pTriangleArrayBuffer);

        // Read from database an copy into target
        Serialization::DATABASE_HANDLE handle(static_cast<uint32_t>(buildInfo.triangleArray.deviceAddress));
        const uint8_t* pSrcData = NV_GET_RESOURCE_NOSCOPETRACKER(const uint8_t*, handle);
        NV_ASSERT(pSrcData);

        // Map destination data
        uint8_t* pDstData = reinterpret_cast<uint8_t*>(pTriangleArrayBuffer->Map());
        NV_ASSERT(pDstData);

        memcpy(pDstData, pSrcData, triangleArraySize);

        // Get address
        buildInfo.triangleArray.deviceAddress = GetBufferAddress(device, pTriangleArrayBuffer->GetBuffer());
    }

    // Set the destination
    buildInfo.dstMicromap = micromapEXT;

    // Lookup creation information
    const MicromapEXT* pMicromapEXT = s_Micromaps.Lookup(micromapEXT);
    NV_ASSERT(pMicromapEXT);

    // Query build sizes
    const VkMicromapBuildSizesInfoEXT& buildSizesInfo = pMicromapEXT->sizeInfo;

    // If compacted, we need to first build a temporary un-compacted src micromap that'll
    // be copied into the final target micromap.
    VkMicromapEXT tempMicromap = VK_NULL_HANDLE;
    if (isCompacted)
    {
        // Create backing buffer for the temp src
        ScopedVmaBuffer* pScopedVmaBuffer = new ScopedVmaBuffer(allocator, buildSizesInfo.micromapSize, VkBufferUsageFlagBits(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT), VMA_MEMORY_USAGE_GPU_ONLY);
        vecTempBuffers.push_back(pScopedVmaBuffer);

        // Create temp src
        VkMicromapCreateInfoEXT tempCreateInfo = *pMicromapEXT->pCreateInfoKHR;
        tempCreateInfo.size = pScopedVmaBuffer->Size();
        tempCreateInfo.buffer = pScopedVmaBuffer->GetBuffer();
        tempCreateInfo.offset = 0;
        vkCreateMicromapEXT(device, &tempCreateInfo, nullptr, &tempMicromap);
        NV_ASSERT(tempMicromap != VK_NULL_HANDLE);

        // Modify the build information to use this buffer
        buildInfo.flags |= VK_BUILD_MICROMAP_ALLOW_COMPACTION_BIT_EXT;
        buildInfo.dstMicromap = tempMicromap;
    }

    // Create scratch buffer
    ScopedVmaBuffer* pScratchBuffer = new ScopedVmaBuffer(allocator, buildSizesInfo.buildScratchSize, VkBufferUsageFlagBits(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT), VMA_MEMORY_USAGE_GPU_ONLY);
    vecTempBuffers.push_back(pScratchBuffer);
    buildInfo.scratchData.deviceAddress = GetBufferAddress(device, pScratchBuffer->GetBuffer());

    // Execute build
    VkResult ret = VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [=](VkCommandBuffer cmdBuffer) {
        vkCmdBuildMicromapsEXT(cmdBuffer, 1, &buildInfo);
    });
    NV_VK_VALIDATE(ret);

    // If compacted, perform a compacting copy to from the temporary src to the real object
    if (isCompacted)
    {
        // If we didn't resize the original compacted micromap, we need to
        // make sure the post-build size is actually big enough.
        if (s_UnsafeCompactedAccelerationStructuresKHR)
        {
            // Query the size now (we could use a barrier instead of two command lists)
            VkQueryPool queryPool = VK_NULL_HANDLE;
            VkQueryPoolCreateInfo tempPoolCreateInfo = { VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO };
            tempPoolCreateInfo.queryType = VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT;
            tempPoolCreateInfo.queryCount = 1;
            NV_VK_VALIDATE(vkCreateQueryPool(device, &tempPoolCreateInfo, nullptr, &queryPool));
            NV_VK_VALIDATE(VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [&](VkCommandBuffer cmdBuffer) {
                vkCmdResetQueryPool(cmdBuffer, queryPool, 0, 1);
                vkCmdWriteMicromapsPropertiesEXT(cmdBuffer, 1, &tempMicromap, VK_QUERY_TYPE_MICROMAP_COMPACTED_SIZE_EXT, queryPool, 0);
            }));
            VkDeviceSize compactedSizeOut = 0;
            NV_VK_VALIDATE(vkGetQueryPoolResults(device, queryPool, 0, 1, sizeof(VkDeviceSize), &compactedSizeOut, sizeof(VkDeviceSize), VK_QUERY_RESULT_WAIT_BIT));
            vkDestroyQueryPool(device, queryPool, nullptr);

            // If our destination isn't big enough, we have trouble
            if (compactedSizeOut > pMicromapEXT->pCreateInfoKHR->size)
            {
                NV_MESSAGE("Compacted micromap size has change between capture and replay. This trace can only run without -%s", k_UnsafeCompactedAccelerationStructures);
                return NV_VK_VALIDATE(VK_ERROR_INCOMPATIBLE_DRIVER);
            }
        }

        // NOTE: Performance of this could be improved with a single command list and barriers
        ret = VulkanHelper_ExecuteCommands(device, VK_QUEUE_COMPUTE_BIT, [=](VkCommandBuffer cmdBuffer) {
            VkCopyMicromapInfoEXT info = { VK_STRUCTURE_TYPE_COPY_MICROMAP_INFO_EXT };
            info.src = tempMicromap;
            info.dst = micromapEXT;
            info.mode = VK_COPY_MICROMAP_MODE_COMPACT_EXT;
            vkCmdCopyMicromapEXT(cmdBuffer, &info);
        });
        NV_VK_VALIDATE(ret);

        // Clean up temp src
        vkDestroyMicromapEXT(device, tempMicromap, nullptr);
    }

    // VulkanHelper_ExecuteCommands is blocking so we can delete now
    for (ScopedVmaBuffer* pTempBuffer : vecTempBuffers)
    {
        delete pTempBuffer;
    }

    return ret;
}
#endif

#if defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanSCHelper_CreateGraphicsPipeline
//------------------------------------------------------------------------------
VkResult VulkanSCHelper_CreateGraphicsPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo* pCreateInfo, size_t size, const void* pData, VkPipeline* pPipeline)
{
    VkPipelineCacheCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    info.flags = VK_PIPELINE_CACHE_CREATE_READ_ONLY_BIT | VK_PIPELINE_CACHE_CREATE_USE_APPLICATION_STORAGE_BIT;
    info.initialDataSize = size;
    info.pInitialData = pData;

    VkPipelineCache pipelineCache = VK_NULL_HANDLE;
    NV_VK_VALIDATE(vkCreatePipelineCache(device, &info, nullptr, &pipelineCache));
    NV_VK_VALIDATE(vkCreateGraphicsPipelines(device, pipelineCache, 1, pCreateInfo, nullptr, pPipeline));

    vkDestroyPipelineCache(device, pipelineCache, nullptr);
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanSCHelper_CreateComputePipeline
//------------------------------------------------------------------------------
VkResult VulkanSCHelper_CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, size_t size, const void* pData, VkPipeline* pPipeline)
{
    VkPipelineCacheCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    info.flags = VK_PIPELINE_CACHE_CREATE_READ_ONLY_BIT | VK_PIPELINE_CACHE_CREATE_USE_APPLICATION_STORAGE_BIT;
    info.initialDataSize = size;
    info.pInitialData = pData;

    VkPipelineCache pipelineCache = VK_NULL_HANDLE;
    NV_VK_VALIDATE(vkCreatePipelineCache(device, &info, nullptr, &pipelineCache));
    NV_VK_VALIDATE(vkCreateComputePipelines(device, pipelineCache, 1, pCreateInfo, nullptr, pPipeline));

    vkDestroyPipelineCache(device, pipelineCache, nullptr);
    return VK_SUCCESS;
}
#endif

//------------------------------------------------------------------------------
// VulkanHelper_PopulateBuffer (legacy interface)
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateBuffer(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceMemory /*do_no_use*/, VkMemoryPropertyFlags /*do_no_use*/, VkDeviceSize /*do_no_use*/, VkDeviceSize size, const uint32_t* pBufferData)
{
    return VulkanHelper_PopulateBuffer3(device, deviceMask, buffer, 0, size, pBufferData);
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateBuffer2
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateBuffer2(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceSize size, const uint32_t* pBufferData)
{
    return VulkanHelper_PopulateBuffer3(device, deviceMask, buffer, 0, size, pBufferData);
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateBuffer3
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateBuffer3(VkDevice device, uint32_t deviceMask, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, const uint32_t* pBufferData)
{
#if defined(VK_NV_ray_tracing) || defined(VK_KHR_ray_tracing_pipeline)
    // We cannot treat acceleration structures as "just memory" as it'll corrupt internal data
    // structures if we simply overwrite the raw data.
    if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
    {
        auto itr = s_AccelerationStructureBuffers.find(buffer);
        if (itr != s_AccelerationStructureBuffers.end())
        {
            return VK_SUCCESS;
        }
    }
#endif

#if defined(VK_EXT_opacity_micromap)
    // We cannot treat micromaps as "just memory" as it'll corrupt internal data
    if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
    {
        auto itr = s_MicromapBuffers.find(buffer);
        if (itr != s_MicromapBuffers.end())
        {
            return VK_SUCCESS;
        }
    }
#endif

    // Get staging buffer
    std::shared_ptr<ScopedVmaBuffer> spStagingBuffer = [&]() -> std::shared_ptr<ScopedVmaBuffer> {
        // Cache buffers used in reset
        auto key = std::make_tuple(device, buffer, offset, size);
        static std::map<decltype(key), std::shared_ptr<ScopedVmaBuffer>> k_cache;
        if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
        {
            auto itr = k_cache.find(key);
            if (itr != k_cache.end())
            {
                return itr->second;
            }
        }

        // Get bind memory information; will be null for sparse cases
        const BindBufferMemoryInfo* pMemoryInfo = [&]() -> const BindBufferMemoryInfo* {
            auto itr = s_BufferBindInfo.find(buffer);
            if (itr == s_BufferBindInfo.end())
            {
                return nullptr;
            }
            return &itr->second;
        }();

        // If we have backing bind information
        if (pMemoryInfo && offset == 0)
        {

            // Get physical device
            const VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];

            // Get memory flags used by this buffer
            const VkMemoryPropertyFlags memoryPropertyFlags = s_MemoryProperties[physicalDevice].memoryTypes[pMemoryInfo->memoryTypeIdx].propertyFlags;

            // Check if mapped
            if (memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
            {
                if (s_UseReplayManagedMemoryAllocations)
                {
                    // Get VMA information about buffer
                    const VmaInfo& vmaInfo = [&] {
                        auto itr = s_VmaBufferInfo.find(pMemoryInfo->bindInfo.buffer);
                        NV_ASSERT(itr != s_VmaBufferInfo.end());
                        return itr->second;
                    }();

                    NV_ASSERT(vmaInfo.allocationInfo.pMappedData);
                    memcpy(vmaInfo.allocationInfo.pMappedData, pBufferData, size_t(size));
                    return {};
                }

                // See if this memory already mapped; this can happen during repopulation
                auto itr = s_MemoryMappingInfo.find(pMemoryInfo->bindInfo.memory);

                // Memory is already mapped; copy directly
                if (itr == s_MemoryMappingInfo.end())
                {
                    void* pDstData = nullptr;
                    NV_VK_VALIDATE(vkMapMemory(device, pMemoryInfo->bindInfo.memory, pMemoryInfo->bindInfo.memoryOffset, size, VkMemoryMapFlags(0), &pDstData));
                    memcpy(pDstData, pBufferData, size_t(size));
                    vkUnmapMemory(device, pMemoryInfo->bindInfo.memory);
                    return {};
                }

                // See if the population region is mapped
                const MemoryMappingInfo& info = itr->second;
                if (info.offset <= pMemoryInfo->bindInfo.memoryOffset)
                {
                    if (info.offset + info.size >= pMemoryInfo->bindInfo.memoryOffset + size)
                    {
                        const VkDeviceSize mappingOffset = pMemoryInfo->bindInfo.memoryOffset - info.offset;
                        memcpy(reinterpret_cast<uint8_t*>(info.pData) + mappingOffset, pBufferData, size_t(size));
                        return {};
                    }
                }

                // Fall through to other case if this actually mapped
            }
        }

        // Create & populate staging buffer
        std::shared_ptr<ScopedVmaBuffer> spStagingBuffer = std::make_shared<ScopedVmaBuffer>(s_Allocators[device], size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(spStagingBuffer->GetBuffer() != VK_NULL_HANDLE);
        void* pStagingData = spStagingBuffer->Map();
        NV_ASSERT(pStagingData);
        memcpy(pStagingData, pBufferData, size);
        spStagingBuffer->Unmap();

        // Insert into cache if doing resets
        if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
        {
            k_cache.insert(k_cache.end(), std::make_pair(key, spStagingBuffer));
        }

        return spStagingBuffer;
    }();

    // No buffer mean no copy is needed
    if (!spStagingBuffer)
    {
        return VK_SUCCESS;
    }

    // Upload to GPU
    s_ResourceUpdateHelpers[device]->EnqueueWork(deviceMask, spStagingBuffer->Size(), [=](VkCommandBuffer cmdBuffer) {
        VkBufferCopy region = {};
        region.srcOffset = 0;
        region.dstOffset = offset;
        region.size = size;
        vkCmdCopyBuffer(cmdBuffer, spStagingBuffer->GetBuffer(), buffer, 1, &region);
    });

    // Success
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateImage
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateImage(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData)
{
    return VulkanHelper_PopulateImage2(device, deviceMask, image, flags, layout, subresource, offset, extent, dataSize, pImageData, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateImage2
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateImage2(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize size, const uint32_t* pImageData, const VkClearValue* pClearValue)
{
    return VulkanHelper_PopulateImage3(device, deviceMask, image, flags, 1, &layout, subresource, offset, extent, size, pImageData, pClearValue);
}

//------------------------------------------------------------------------------
// UnpackPackedDepthStencilBuffer
//------------------------------------------------------------------------------
template <typename T_SrcPacked, typename T_Depth, typename T_Stencil>
std::tuple<const uint32_t*, VkDeviceSize, VkDeviceSize, VkDeviceSize> UnpackPackedDepthStencilBuffer(VkImage image, const VkExtent3D& extent, VkDeviceSize size, const uint32_t* pImageData)
{
    // Local data cache to avoid
    VULKAN_REPLAY_WRITE_LOCK();
    static std::map<VkImage, std::vector<uint8_t>> s_CachedUnpackedBuffers;

    // Texel count in this region
    const uint32_t texelCount = extent.width * extent.height * extent.depth;

    // Data is expected to be interleaved coming from the database
    const VkDeviceSize expectedInputSize = (texelCount * sizeof(T_SrcPacked));
    NV_ASSERT(size >= expectedInputSize);
    const T_SrcPacked* pSrcData = reinterpret_cast<const T_SrcPacked*>(pImageData);

    // Calculate unpacked sizes & offsets
    const size_t depthSize = ALIGN_WORD(texelCount * sizeof(T_Depth));
    const size_t stenciSize = ALIGN_WORD(texelCount * sizeof(T_Stencil));
    size = VkDeviceSize(depthSize + stenciSize);
    const size_t depthOffset = 0;
    const size_t stencilOffset = VkDeviceSize(depthSize);

    // Get cached unpacked buffer (or create)
    auto itr = s_CachedUnpackedBuffers.find(image);
    if (itr == s_CachedUnpackedBuffers.end())
    {

        // Create buffer big enough for split aspects
        std::vector<uint8_t> temp(size);
        T_Depth* pDstDepth = reinterpret_cast<T_Depth*>(&temp[depthOffset]);
        T_Stencil* pDstStencil = reinterpret_cast<T_Stencil*>(&temp[stencilOffset]);

        // Unpack buffers
        for (uint32_t i = 0; i < texelCount; i++)
        {
            const T_Depth depth = pSrcData[i].d;
            const T_Stencil stencil = pSrcData[i].s;
            pDstDepth[i] = depth;
            pDstStencil[i] = stencil;
        }

        // Add to cache
        auto entry = std::make_pair(image, std::move(temp));
        itr = s_CachedUnpackedBuffers.emplace(std::move(entry)).first;
    }

    // Use new buffer
    NV_ASSERT(itr != s_CachedUnpackedBuffers.end());
    pImageData = reinterpret_cast<const uint32_t*>(itr->second.data());
    return std::make_tuple(pImageData, size, depthOffset, stencilOffset);
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateImage3
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateImage3(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, uint32_t layoutCount, const VkImageLayout* pLayout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize size, const uint32_t* pImageData, const VkClearValue* pClearValue)
{
    std::vector<VkImageLayout> oldLayouts(layoutCount, VK_IMAGE_LAYOUT_UNDEFINED);

    return VulkanHelper_PopulateImage4(device, deviceMask, image, flags, layoutCount, oldLayouts.data(), pLayout, subresource, offset, extent, size, pImageData, pClearValue);
}

//------------------------------------------------------------------------------
// RecordTransitionImageLayout (static helper)
//------------------------------------------------------------------------------
static void RecordTransitionImageLayout(VkCommandBuffer cmdBuffer, VkImage image, uint32_t layoutCount, const VkImageLayout* pOldLayouts, const VkImageLayout* pNewLayouts, VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    // For depth/stencil image which has different layouts for aspects, we pass in two different layouts (depth and stencil)
    // otherwise, for depth/stencil image which has same layouts for aspects, or other images we pass in one layout for all aspects
    NV_ASSERT(layoutCount == 1 || layoutCount == 2);
    NV_ASSERT(pOldLayouts && pNewLayouts);

    std::vector<VkImageMemoryBarrier> vecImageMemoryBarriers = {};

    for (uint32_t i = 0; i < layoutCount; i++)
    {
        if (pOldLayouts[i] == pNewLayouts[i])
        {
            continue;
        }

        if (pNewLayouts[i] == VK_IMAGE_LAYOUT_UNDEFINED)
        {
            NV_MESSAGE_ONCE("Can't transition to image layout to VK_IMAGE_LAYOUT_UNDEFINED.");
            continue;
        }

        for (uint32_t j = 0; j < rangeCount; j++)
        {
            if (layoutCount == 2)
            {
                NV_ASSERT(pRanges[j].aspectMask == VkImageAspectFlags(VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT));
            }
            VkImageMemoryBarrier barrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
            barrier.oldLayout = pOldLayouts[i];
            barrier.newLayout = pNewLayouts[i];
            barrier.image = image;
            barrier.subresourceRange = pRanges[j];

            // Special handle for depth stencil separate layout
            if (layoutCount == 2)
            {
                if (i == 0)
                {
                    // Depth aspect
                    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
                }
                else
                {
                    // Stencil aspect
                    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT;
                }
            }

            vecImageMemoryBarriers.push_back(barrier);
        }
    }

    vkCmdPipelineBarrier(cmdBuffer, srcStage, dstStage, 0, 0, nullptr, 0, nullptr, (uint32_t)vecImageMemoryBarriers.size(), vecImageMemoryBarriers.data());
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateImage4
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateImage4(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, uint32_t layoutCount, const VkImageLayout* pOldLayouts, const VkImageLayout* pNewLayouts, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize size, const uint32_t* pImageData, const VkClearValue* pClearValue)
{
    // It's possible this image is part of a swapchain not actively used in the capture
    if (image == VK_NULL_HANDLE)
    {
        return VK_SUCCESS;
    }

    // TODO: This needs better support for images layouts and usage flags.
    // This'll trigger some API warnings but they are non-fatal to the
    // current NVIDIA driver. To get these correct we need additional state
    // tracking on the target.

    // By default do not initialize resources that are populated in frame
    const bool initializedInFrame = flags & NV_VK_IMAGE_INITIALIZED_IN_FRAME;
    const bool shouldPopulate = s_PopulateAllResources || !initializedInFrame;
    if (!shouldPopulate)
    {
        return VK_SUCCESS;
    }

    // Lookup create info
    const VkImageCreateInfo* pImageCreateInfo = [=]() {
        auto itr = s_ImageCreateInfo.find(image);
        return itr != s_ImageCreateInfo.end() ? &itr->second : nullptr;
    }();

    // Multi-sample images cannot be initialized from raw data
    if (pImageCreateInfo && pImageCreateInfo->samples != VK_SAMPLE_COUNT_1_BIT)
    {
        return VK_SUCCESS;
    }

    // Get image format
    const VkFormat format = [=]() -> VkFormat {
        if (pImageCreateInfo)
        {
            return pImageCreateInfo->format;
        }
        auto itr = s_ImageFormat.find(image);
        NV_ASSERT(itr != s_ImageFormat.end());
        return itr->second;
    }();

    // Aspect offsets
    VkDeviceSize depthOffset = 0;
    VkDeviceSize stencilOffset = 0;

    // Get staging buffer
    std::shared_ptr<ScopedVmaBuffer> spStagingBuffer = [&]() {
        // Cache key
        auto key = std::make_tuple(device, image, subresource.arrayLayer, subresource.aspectMask, subresource.mipLevel);
        static std::map<decltype(key), std::shared_ptr<ScopedVmaBuffer>> k_cache;
        if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
        {
            auto itr = k_cache.find(key);
            if (itr != k_cache.end())
            {
                return itr->second;
            }
        }

        // Special case multi-plane depth stencil formats as the Vulkan spec doesn't allow them to
        // populated in a single interleaved call unlike other APIs.
        //
        // From the spec...
        //
        //  data copied to or from the stencil aspect of any depth / stencil format is tightly packed
        //  with one VK_FORMAT_S8_UINT value per texel.
        //
        //  data copied to or from the depth aspect of a VK_FORMAT_D16_UNORM or VK_FORMAT_D16_UNORM_S8_UINT
        //  format is tightly packed with one VK_FORMAT_D16_UNORM value per texel.
        //
        //  data copied to or from the depth aspect of a VK_FORMAT_D32_SFLOAT or VK_FORMAT_D32_SFLOAT_S8_UINT
        //  format is tightly packed with one VK_FORMAT_D32_SFLOAT value per texel.
        //
        //  data copied to or from the depth aspect of a VK_FORMAT_X8_D24_UNORM_PACK32 or VK_FORMAT_D24_UNORM_S8_UINT
        //  format is packed with one 32 - bit word per texel with the D24 value in the LSBs of the word, and
        //  undefined values in the eight MSBs.
        if (format == VK_FORMAT_D16_UNORM_S8_UINT)
        {

            struct SrcData
            {
                uint16_t d;
                uint8_t s;
            };

            auto result = UnpackPackedDepthStencilBuffer<SrcData, uint16_t, uint8_t>(image, extent, size, pImageData);
            pImageData = std::get<0>(result);
            size = std::get<1>(result);
            depthOffset = std::get<2>(result);
            stencilOffset = std::get<3>(result);
        }
        else if (format == VK_FORMAT_D32_SFLOAT_S8_UINT)
        {

            struct SrcData
            {
                float d;
                uint8_t s;
                uint8_t _pad[3];
            };

            auto result = UnpackPackedDepthStencilBuffer<SrcData, float, uint8_t>(image, extent, size, pImageData);
            pImageData = std::get<0>(result);
            size = std::get<1>(result);
            depthOffset = std::get<2>(result);
            stencilOffset = std::get<3>(result);
        }
        else if (format == VK_FORMAT_D24_UNORM_S8_UINT || format == VK_FORMAT_X8_D24_UNORM_PACK32)
        {

            struct SrcData
            {
                uint32_t s : 8;
                uint32_t d : 24;
            };
            static_assert(sizeof(SrcData) == sizeof(uint32_t), "invalid bitfield");

            auto result = UnpackPackedDepthStencilBuffer<SrcData, uint32_t, uint8_t>(image, extent, size, pImageData);
            pImageData = std::get<0>(result);
            size = std::get<1>(result);
            depthOffset = std::get<2>(result);
            stencilOffset = std::get<3>(result);
        }

        // Create and populate staging buffer
        std::shared_ptr<ScopedVmaBuffer> spStagingBuffer = std::make_shared<ScopedVmaBuffer>(s_Allocators[device], size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(spStagingBuffer->GetBuffer() != VK_NULL_HANDLE);
        void* pStagingData = spStagingBuffer->Map();
        NV_ASSERT(pStagingData);
        memcpy(pStagingData, pImageData, size_t(size));
        spStagingBuffer->Unmap();

        // Insert into cache if doing resets
        if (s_ReplayPhase == VulkanReplayPhase::ResourceReset)
        {
            k_cache.insert(k_cache.end(), std::make_pair(key, spStagingBuffer));
        }

        return spStagingBuffer;
    }();

    // Record old layouts and new layouts
    std::vector<VkImageLayout> oldLayouts(pOldLayouts, pOldLayouts + layoutCount);
    std::vector<VkImageLayout> newLayouts(pNewLayouts, pNewLayouts + layoutCount);

    // Execute population of image
    s_ResourceUpdateHelpers[device]->EnqueueWork(deviceMask, spStagingBuffer->Size(), [=](VkCommandBuffer cmdBuffer) {
        VkImageSubresourceRange subresourceRange = {};
        subresourceRange.baseMipLevel = subresource.mipLevel;
        subresourceRange.levelCount = 1;
        subresourceRange.baseArrayLayer = subresource.arrayLayer;
        subresourceRange.layerCount = 1;
        subresourceRange.aspectMask = subresource.aspectMask;

        std::vector<VkImageLayout> transferDstLayouts(layoutCount, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
        RecordTransitionImageLayout(cmdBuffer, image, layoutCount, oldLayouts.data(), transferDstLayouts.data(), VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 1, &subresourceRange);

        // We must populate the image one aspect at a time
        VkImageSubresourceLayers subresourceForAspect = {};
        subresourceForAspect.aspectMask = subresource.aspectMask;
        subresourceForAspect.mipLevel = subresource.mipLevel;
        subresourceForAspect.baseArrayLayer = subresource.arrayLayer;
        subresourceForAspect.layerCount = 1;

        const VkImageAspectFlags depthStencil = VkImageAspectFlags(VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT);

        if (subresourceForAspect.aspectMask & depthStencil)
        {

            if (pClearValue)
            {
                std::vector<VkImageSubresourceRange> vecSubresourceRanges;
                // Depth range
                if (subresourceForAspect.aspectMask & VK_IMAGE_ASPECT_DEPTH_BIT)
                {
                    VkImageSubresourceRange range = subresourceRange;
                    range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
                    vecSubresourceRanges.push_back(range);
                }

                // Stencil range
                if (subresourceForAspect.aspectMask & VK_IMAGE_ASPECT_STENCIL_BIT)
                {
                    VkImageSubresourceRange range = subresourceRange;
                    range.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT;
                    vecSubresourceRanges.push_back(range);
                }

                vkCmdClearDepthStencilImage(cmdBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &pClearValue->depthStencil, uint32_t(vecSubresourceRanges.size()), vecSubresourceRanges.data());
            }

            std::vector<VkBufferImageCopy> vecRegions;

            // Depth region
            if (subresourceForAspect.aspectMask & VK_IMAGE_ASPECT_DEPTH_BIT)
            {
                VkBufferImageCopy depthRegion = {};
                depthRegion.bufferOffset = depthOffset;
                depthRegion.imageSubresource = subresourceForAspect;
                depthRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
                depthRegion.imageOffset = offset;
                depthRegion.imageExtent = extent;
                vecRegions.push_back(depthRegion);
            }

            // Stencil region
            if (subresourceForAspect.aspectMask & VK_IMAGE_ASPECT_STENCIL_BIT)
            {
                VkBufferImageCopy stencilRegion = {};
                stencilRegion.bufferOffset = stencilOffset;
                stencilRegion.imageSubresource = subresourceForAspect;
                stencilRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT;
                stencilRegion.imageOffset = offset;
                stencilRegion.imageExtent = extent;
                vecRegions.push_back(stencilRegion);
            }

            vkCmdCopyBufferToImage(cmdBuffer, spStagingBuffer->GetBuffer(), image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, uint32_t(vecRegions.size()), vecRegions.data());
        }
        else
        {

            if (pClearValue)
            {
                vkCmdClearColorImage(cmdBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &pClearValue->color, 1, &subresourceRange);
            }

            // Record update to buffer
            VkBufferImageCopy region = {};
            region.imageSubresource = subresourceForAspect;
            region.imageOffset = offset;
            region.imageExtent = extent;
            vkCmdCopyBufferToImage(cmdBuffer, spStagingBuffer->GetBuffer(), image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
        }

        // Transition to application layout after population
        RecordTransitionImageLayout(cmdBuffer, image, layoutCount, transferDstLayouts.data(), newLayouts.data(), VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 1, &subresourceRange);
    });

    // Success
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_PopulateSwapchainImage
//------------------------------------------------------------------------------
VkResult VulkanHelper_PopulateSwapchainImage(VkDevice device, uint32_t deviceMask, VkImage image, VulkanHelper_PopulateImageFlags flags, VkImageLayout layout, VkImageSubresource subresource, VkOffset3D offset, VkExtent3D extent, VkDeviceSize dataSize, const uint32_t* pImageData)
{
    auto& tls = GetThreadState();

    // Reset the active override swapchain image
    VkImage overrideImage = GetActive_Image(tls.activeOverride, image);

    return VulkanHelper_PopulateImage2(device, deviceMask, overrideImage, VulkanHelper_PopulateImageFlags(flags | NV_VK_IMAGE_SWAPCHAIN), layout, subresource, offset, extent, dataSize, pImageData, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_TransitionImageLayout
//------------------------------------------------------------------------------
VkResult VulkanHelper_TransitionImageLayout(VkDevice device, VkImage image, uint32_t layoutCount, const VkImageLayout* pOldLayouts, const VkImageLayout* pNewLayouts, VkPipelineStageFlags srcStage, VkPipelineStageFlags dstStage, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    return VulkanHelper_ExecuteCommands(device, VK_QUEUE_TRANSFER_BIT, [=](VkCommandBuffer cmdBuffer) {
        RecordTransitionImageLayout(cmdBuffer, image, layoutCount, pOldLayouts, pNewLayouts, srcStage, dstStage, rangeCount, pRanges);
    });
}

//------------------------------------------------------------------------------
// UpdateMappedMemory
//------------------------------------------------------------------------------
VkResult VulkanHelper_UpdateMappedMemory(VkDevice device, VkDeviceMemory memory, void* pMappedPtr, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData)
{
    return VulkanHelper_UpdateMappedMemory2(device, memory, pMappedPtr, offset, size, pData, 0, nullptr);
}

//------------------------------------------------------------------------------
// VulkanHelper_UpdateMappedMemory2
//------------------------------------------------------------------------------
VkResult VulkanHelper_UpdateMappedMemory2(VkDevice device, VkDeviceMemory memory, void* pMappedPtr, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData, uint32_t bufferInfoCount, const VkDescriptorBufferInfo* pBufferInfo)
{
    // Get meta information about memory
    const DeviceMemoryInfo& memoryInfo = [&] {
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        return itr->second;
    }();

    // If this memory was never allocated it means the buffer is being managed
    // by the replayer and we should updated it directly.
    if (!memoryInfo.isAllocated)
    {
        for (uint32_t i = 0; i < bufferInfoCount; i++)
        {
            const VkDescriptorBufferInfo& bufferInfo = pBufferInfo[i];

            // Get VMA information about buffer
            const VmaInfo& vmaInfo = [&] {
                auto itr = s_VmaBufferInfo.find(bufferInfo.buffer);
                NV_ASSERT(itr != s_VmaBufferInfo.end());
                return itr->second;
            }();

            // Map buffer
            void* pBufferData = vmaInfo.allocationInfo.pMappedData;
            NV_ASSERT(pBufferData);

            // Offset is actually a sigend value but we reused VkDescriptorBufferInfo
            // which is un-signed.
            int64_t offset = (int64_t)bufferInfo.offset;
            uint8_t* pDst = reinterpret_cast<uint8_t*>(pBufferData) + offset;

            // Copy in data
            //
            // If the offset is negative it means that the mapped region spans
            // multiple buffers and the mapped region starts before this buffer.
            if (offset >= 0)
            {
                memcpy(pDst, pData, std::min(bufferInfo.range, size));
            }
            else
            {
                offset = 0 - offset;
                memcpy(pDst, pData + offset, std::min(bufferInfo.range, size - offset));
            }
        }

        return VK_SUCCESS;
    }

    // Make sure map was successful
    if (!pMappedPtr)
    {
        return VK_ERROR_MEMORY_MAP_FAILED;
    }

    // Skip if opting out of multiple mapped memory updates
    if (s_SkipMappedMemoryUpdates && s_FrameIdx != 0)
    {
        return VK_SUCCESS;
    }

    // Copy data
    memcpy(reinterpret_cast<uint8_t*>(pMappedPtr) + offset, pData, size_t(size));

    // Success
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanHelper_UpdateExternalMemory
//------------------------------------------------------------------------------
VkResult VulkanHelper_UpdateExternalMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, const uint8_t* pData)
{
    // First frame through we'll create a buffer for the data
    if (s_FrameIdx == 0)
    {

        // Get allocation
        ScopedVmaBuffer* pBuffer = new ScopedVmaBuffer(s_Allocators[device], size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
        NV_ASSERT(pBuffer != VK_NULL_HANDLE);

        // Populate buffer data
        void* pStagingData = pBuffer->Map();
        memcpy(pStagingData, pData, size_t(size));
        pBuffer->Unmap();

        // Add to map
        s_ExternalMemoryDataBuffers.emplace_back(pBuffer);
    }

    // Also create a buffer that spans the whole device memory object
    if (s_FrameIdx == 0)
    {

        // Get memory
        auto itr = s_DeviceMemoryInfo.find(memory);
        NV_ASSERT(itr != s_DeviceMemoryInfo.end());
        VkDeviceSize allocationSize = itr->second.allocateInfo.allocationSize;

        // Create buffer
        VkBuffer buffer = VK_NULL_HANDLE;
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = allocationSize;
        bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);

        // Bind buffer
        vkBindBufferMemory(device, buffer, memory, 0);

        // Add to map
        s_ExternalMemorySpanningBuffers.push_back(buffer);
    }

    // Perform copy
    VkBuffer srcBuffer = s_ExternalMemoryDataBuffers[s_ExternalMemoryUpdateIdx]->GetBuffer();
    VkBuffer dstBuffer = s_ExternalMemorySpanningBuffers[s_ExternalMemoryUpdateIdx];
    VulkanHelper_ExecuteCommands(device, VK_QUEUE_TRANSFER_BIT, [=](VkCommandBuffer commandBuffer) {
        VkBufferCopy region = {};
        region.size = size;
        region.srcOffset = 0;
        region.dstOffset = offset;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &region);
    });

    s_ExternalMemoryUpdateIdx++;
    return VK_SUCCESS;
}

static bool memory_type_from_properties(VkPhysicalDeviceMemoryProperties* memory_properties, uint32_t typeBits,
    VkFlags requirements_mask, uint32_t* typeIndex)
{
    // Search memtypes to find first index with those properties
    for (uint32_t i = 0; i < 32; i++)
    {
        if ((typeBits & 1) == 1)
        {
            // Type is available, does it match user properties?
            if ((memory_properties->memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask)
            {
                *typeIndex = i;
                return true;
            }
        }
        typeBits >>= 1;
    }
    // No memory types matched, return failure
    return false;
}

enum class YAxisOrientation
{
    BottomToTop,
    TopToBottom
};

#ifdef _WIN32
#include <windows.h>
#else
#pragma pack(push, 2)
struct BITMAPFILEHEADER
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
#pragma pack(pop)

struct BITMAPINFOHEADER
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#endif
//---------------------------------------------------------------------------
// WriteBmpRGB8
//---------------------------------------------------------------------------
bool WriteBmpRGB8(const char* pFilename, int width, int height, int memWidth, YAxisOrientation yAxis, const uint8_t* pPixels)
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    // Bitmap data must be written out in 32-bit aligned rows of pixels.
    // We write 24-bit data, so we need to add padBytes at the end of each row.
    int padSize = (4 - (3 * width) % 4) % 4;
    uint32_t dataSize = static_cast<uint32_t>((width * height * 3 * sizeof(uint8_t) + padSize * height));

    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = width;
    // The negative Y for BMP means "line zero is top"
    infoHeader.biHeight = yAxis == YAxisOrientation::TopToBottom ? -height : height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biCompression = 0L; // BI_RGB
    infoHeader.biSizeImage = 0;
    infoHeader.biXPelsPerMeter = 300;
    infoHeader.biYPelsPerMeter = 300;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    // Open the file
    FILE* pFile = fopen(pFilename, "wb");
    if (!pFile)
    {
        return false;
    }

    // Write the header, then the info header
    fwrite(&fileHeader, sizeof(fileHeader), 1, pFile);
    fwrite(&infoHeader, sizeof(infoHeader), 1, pFile);

    // Now, write the image data
    int rowOffset = 0;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // Write the bits in bgr order
            fputc(pPixels[(rowOffset + j) * 4 + 0], pFile);
            fputc(pPixels[(rowOffset + j) * 4 + 1], pFile);
            fputc(pPixels[(rowOffset + j) * 4 + 2], pFile);
        }
        // Move to the next row
        rowOffset += memWidth;

        // Finally, add pad bytes to the end of the row, if necessary
        for (int k = 0; k < padSize; ++k)
        {
            fputc(0, pFile);
        }
    }

    // Close the file
    fclose(pFile);

    return true;
}

//------------------------------------------------------------------------------
// DumpFrame
//------------------------------------------------------------------------------
VkResult DumpFrame(uint32_t swapChainIndex, uint32_t imageIndex,
    const VkQueue& queue, const SwapChainInfo& swapChainInfo)
{
    // get image
    if (imageIndex > swapChainInfo.images.size())
    {
        return VK_ERROR_UNKNOWN;
    }
    VkImage image1 = swapChainInfo.images[imageIndex];

    // get device
    VkDevice device = swapChainInfo.device;
    VkPhysicalDevice physicalDevice = nullptr;
    if (s_DeviceToPhysicalDeviceMap.find(device) != s_DeviceToPhysicalDeviceMap.end())
    {
        physicalDevice = s_DeviceToPhysicalDeviceMap[device];
    }
    else
    {
        return VK_ERROR_UNKNOWN;
    }

    // get command pool
    uint32_t queueFamilyIndex = 0;
    if (s_QueueInfo.find(queue) != s_QueueInfo.end())
    {
        queueFamilyIndex = s_QueueInfo[queue].queueFamilyIndex;
    }
    else
    {
        return VK_ERROR_UNKNOWN;
    }
    VkCommandPool cmdPool = GetCommandPool(device, queueFamilyIndex);

    // get image size and format
    uint32_t width = swapChainInfo.originalCreateInfo.imageExtent.width; // "GetDummySwapchainImages" used originalCreateInfo, so here also use the original
    uint32_t height = swapChainInfo.originalCreateInfo.imageExtent.height; // "GetDummySwapchainImages" used originalCreateInfo
    VkFormat format = swapChainInfo.createInfo.imageFormat;

    // create resources
    const VkImageCreateInfo imgCreateInfo = {
        VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        NULL,
        0,
        VK_IMAGE_TYPE_2D,
        VK_FORMAT_R8G8B8A8_UNORM, // because to bmp file, we only support R8G8B8A8
        { width, height, 1 },
        1,
        1,
        VK_SAMPLE_COUNT_1_BIT,
        VK_IMAGE_TILING_LINEAR,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        VK_SHARING_MODE_EXCLUSIVE,
        swapChainInfo.createInfo.queueFamilyIndexCount,
        swapChainInfo.createInfo.pQueueFamilyIndices,
        VK_IMAGE_LAYOUT_UNDEFINED
    };
    VkMemoryAllocateInfo memAllocInfo = {
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, NULL,
        0, // allocationSize, queried later
        0 // memoryTypeIndex, queried later
    };
    const VkCommandBufferAllocateInfo allocCommandBufferInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        NULL,
        cmdPool,
        VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        1
    };
    const VkCommandBufferBeginInfo commandBufferBeginInfo = {
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        NULL,
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    const VkImageCopy imageCopyRegion = {
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 },
        { 0, 0, 0 },
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 },
        { 0, 0, 0 },
        { width, height, 1 }
    };
    VkMemoryRequirements memRequirements = { 0 };
    VkPhysicalDeviceMemoryProperties memory_properties = { 0 };

    // The VkImage image1 we are going to dump may not be mappable,
    // and/or it may have a tiling mode of optimal rather than linear.
    // To make sure we have an image that we can map and read linearly, we:
    //     create image2 that is mappable and linear
    //     copy image1 to image2
    //     map image2
    //     read from image2's mapped memory.
    VkImage image2 = 0;
    VkResult err = vkCreateImage(device, &imgCreateInfo, NULL, &image2);
    NV_ASSERT(err == VK_SUCCESS);
    vkGetImageMemoryRequirements(device, image2, &memRequirements);

    memAllocInfo.allocationSize = memRequirements.size;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memory_properties);

    bool pass = memory_type_from_properties(&memory_properties, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
        &memAllocInfo.memoryTypeIndex);
    NV_ASSERT(pass);

    VkDeviceMemory mem2 = 0;
    err = vkAllocateMemory(device, &memAllocInfo, NULL, &mem2);
    NV_ASSERT(err == VK_SUCCESS);

    err = vkBindImageMemory(device, image2, mem2, 0);
    NV_ASSERT(err == VK_SUCCESS);

    VkCommandBuffer commandBuffer = 0;
    err = vkAllocateCommandBuffers(device, &allocCommandBufferInfo, &commandBuffer);
    NV_ASSERT(err == VK_SUCCESS);

    err = vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);
    NV_ASSERT(err == VK_SUCCESS);

    VkImageMemoryBarrier image1_memory_barrier = {
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        NULL,
        VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_ACCESS_TRANSFER_READ_BIT,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        0,
        0,
        image1,
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
    };

    VkImageMemoryBarrier image2_memory_barrier = {
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
        NULL,
        0,
        VK_ACCESS_TRANSFER_WRITE_BIT,
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        0,
        0,
        image2,
        { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 }
    };

    VkPipelineStageFlags src_stages = VK_PIPELINE_STAGE_TRANSFER_BIT;
    VkPipelineStageFlags dst_stages = VK_PIPELINE_STAGE_TRANSFER_BIT;

    // The source image needs to be transitioned from the potentially optimized swapchain format to optimum format for the copy.
    vkCmdPipelineBarrier(commandBuffer, src_stages, dst_stages, 0, 0, NULL, 0, NULL, 1, &image1_memory_barrier);

    // The destination image needs to be transitioned from unknown to the optimum format for the copy.
    vkCmdPipelineBarrier(commandBuffer, src_stages, dst_stages, 0, 0, NULL, 0, NULL, 1, &image2_memory_barrier);

    vkCmdCopyImage(commandBuffer, image1, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image2,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageCopyRegion);

    // The destination needs to be transitioned from the optimum copy format to the format we can read with the CPU.
    image2_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    image2_memory_barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
    image2_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    image2_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    vkCmdPipelineBarrier(commandBuffer, src_stages, dst_stages, 0, 0, NULL, 0, NULL, 1, &image2_memory_barrier);

    // Restore the swap chain image layout to what it was before.
    // This may not be strictly needed, but it is generally good to restore things to original state.
    image1_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    image1_memory_barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    image1_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    image1_memory_barrier.dstAccessMask = 0;

    vkCmdPipelineBarrier(commandBuffer, src_stages, dst_stages, 0, 0, NULL, 0, NULL, 1, &image1_memory_barrier);

    err = vkEndCommandBuffer(commandBuffer);
    NV_ASSERT(err == VK_SUCCESS);

    VkFence nullFence = { VK_NULL_HANDLE };

    VkSubmitInfo submit_info = {
        VK_STRUCTURE_TYPE_SUBMIT_INFO,
        NULL,
        0,
        NULL,
        NULL,
        1,
        &commandBuffer,
        0,
        NULL
    };

    err = vkQueueWaitIdle(queue);
    NV_ASSERT(err == VK_SUCCESS);

    //TODO: without vkDeviceWaitIdle(), it may dump an empty image
    err = vkDeviceWaitIdle(device);
    NV_ASSERT(err == VK_SUCCESS);

    err = vkQueueSubmit(queue, 1, &submit_info, nullFence);
    NV_ASSERT(err == VK_SUCCESS);

    err = vkQueueWaitIdle(queue);
    NV_ASSERT(err == VK_SUCCESS);

    err = vkDeviceWaitIdle(device);
    NV_ASSERT(err == VK_SUCCESS);

    const VkImageSubresource sr = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0 };
    VkSubresourceLayout sr_layout;
    vkGetImageSubresourceLayout(device, image2, &sr, &sr_layout);

    const char* ptr = nullptr;
    err = vkMapMemory(device, mem2, 0, VK_WHOLE_SIZE, 0, (void**)&ptr);
    NV_ASSERT(err == VK_SUCCESS);

    ptr += sr_layout.offset;
    // Copy to host
    std::string data(sr_layout.size, 0);
    memcpy(&data[0], ptr, sr_layout.size);

    // Clean up
    vkUnmapMemory(device, mem2);
#if !defined(VKSC_VERSION_1_0)
    vkFreeMemory(device, mem2, NULL);
#endif
    vkDestroyImage(device, image2, NULL);
    vkFreeCommandBuffers(device, cmdPool, 1, &commandBuffer);

    // The allocated memory is aligned by 64bit or 128bit, so image2 maybe large than image1 in width.
    // And the redundant column will be filled with black, so we have to cut these column.
    // write to file
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::string fileName = "snapshot_" + std::string(ProcessName) + "_" + std::to_string(localTime->tm_year + 1900) + "_" + std::to_string(localTime->tm_mon + 1) + "_" + std::to_string(localTime->tm_mday) + "_" + std::to_string(localTime->tm_hour) + "_" + std::to_string(localTime->tm_min) + "_" + std::to_string(localTime->tm_sec) + "_" + std::to_string(swapChainIndex) + ".bmp";
    bool ret = WriteBmpRGB8(fileName.c_str(), width, height, int(sr_layout.rowPitch / (GetTexelSizeInBitsForUncompressedColorFormat(format) / BYTE_SIZE)),
        YAxisOrientation::TopToBottom, reinterpret_cast<const uint8_t*>(data.c_str()));
    if (!ret)
    {
        NV_LOG("ERROR: Cannot write the image to bmp file");
        return VK_ERROR_UNKNOWN;
    }

    return VK_SUCCESS;
}

//----------------------------------------------------------------------------------
// Vulkan API
//----------------------------------------------------------------------------------

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateInstance
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Force single threaded mode when using cached command buffers
    if (s_CacheCommandBuffer)
    {
        g_threadPoolThreadCount = 0;
    }

    if (s_InstanceInfo.size() > 0)
    {
        NV_MESSAGE("WARNING: Create more than 1 instance and may cause unexpected behavior");
    }

    // Get ICD addresses
    BootstrapICD();

    // Get instance extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> vecExtensionProperties(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, vecExtensionProperties.data());

    // Get instance layers
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> vecLayerProperties(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, vecLayerProperties.data());

    // Helper to check for instance layers
    auto HasLayer = [&](const char* pHasLayer) -> bool {
        for (VkLayerProperties& layerProperty : vecLayerProperties)
        {
            if (strcmp(pHasLayer, layerProperty.layerName) == 0)
            {
                return true;
            }
        }
        return false;
    };

    std::vector<std::string> vecExplicitlyEnabledLayers;

    // Helper to add only present layers
    auto AddLayerIfPresent = [&](const char* pLayer) {
        if (HasLayer(pLayer))
        {
            vecExplicitlyEnabledLayers.push_back(pLayer);
            return true;
        }
        else
        {
            return false;
        }
    };

    // Copy the instance create info so that we can override some parameters so
    // that the original serialized instance is still valid in this runtime
    // environment.
    VkInstanceCreateInfo instanceCreateInfo = *pCreateInfo;

    // Remove VkDebugReportCallbackCreateInfoEX or VkDebugUtilsMessengerCreateInfoEXT from
    // the instance creation structure. We cannot use the same callbacks the original
    // application was using. Instead a user can opt in via -forcedebug for a fully
    // managed validation experience.
    VkBaseOutStructure* pThis = reinterpret_cast<VkBaseOutStructure*>(&instanceCreateInfo);
    while (pThis && pThis->pNext)
    {
        switch (pThis->pNext->sType)
        {
#if defined(VK_EXT_debug_report)
        case VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT:
#endif
        case VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT:
            pThis->pNext = pThis->pNext->pNext;
            break;
        default:
            break;
        };
        pThis = pThis->pNext;
    }

    std::vector<const char*> vecOriginExtensions(pCreateInfo->ppEnabledExtensionNames, pCreateInfo->ppEnabledExtensionNames + pCreateInfo->enabledExtensionCount);

#if NV_USE_MANAGED_WINSYS

    // Delete VK_KHR_win32_surface / VK_KHR_xlib_surface / VK_KHR_xcb_surface / VK_KHR_display extension
    // Add correct extension based on what window system it is using.
    auto determineWindowSystemExtension = [&](const char* extensionName) {
        return !strcmp(extensionName, "VK_KHR_win32_surface") || !strcmp(extensionName, "VK_KHR_xlib_surface") || !strcmp(extensionName, "VK_KHR_xcb_surface") || !strcmp(extensionName, "VK_KHR_display");
    };
    vecOriginExtensions.erase(std::remove_if(vecOriginExtensions.begin(), vecOriginExtensions.end(), determineWindowSystemExtension), vecOriginExtensions.end());

#if defined(VK_USE_PLATFORM_XCB_KHR)
    vecOriginExtensions.push_back("VK_KHR_xcb_surface");
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    vecOriginExtensions.push_back("VK_KHR_xlib_surface");
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
    vecOriginExtensions.push_back("VK_KHR_win32_surface");
#elif defined(VK_USE_PLATFORM_D2D_KHR)
    vecOriginExtensions.push_back("VK_KHR_display");
#endif

#endif // NV_USE_MANAGED_WINSYS

    // Find intersection of enabled and serialized extensions
    std::vector<const char*> vecEnabledExtensions;
    for (const char* enabledExtensionName : vecOriginExtensions)
    {
        bool found = false;
        for (VkExtensionProperties& extensionProperty : vecExtensionProperties)
        {
            if (strcmp(enabledExtensionName, extensionProperty.extensionName) == 0)
            {
                vecEnabledExtensions.push_back(enabledExtensionName);
                found = true;
                break;
            }
        }
        if (!found)
        {
            NV_MESSAGE("Serialized instance extension not available: %s", enabledExtensionName);
        }
    }

    // Add debug extensions
    if (forceDebug)
    {
        vecEnabledExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    // Override create info with valid requested extensions
    instanceCreateInfo.enabledExtensionCount = uint32_t(vecEnabledExtensions.size());
    instanceCreateInfo.ppEnabledExtensionNames = vecEnabledExtensions.data();

    // Find intersection of enabled and serialized layers
    for (uint32_t i = 0; i < pCreateInfo->enabledLayerCount; i++)
    {
        const char* pEnabledLayerName = pCreateInfo->ppEnabledLayerNames[i];
        if (HasLayer(pEnabledLayerName))
        {
            vecExplicitlyEnabledLayers.push_back(pEnabledLayerName);
        }
        else
        {
            NV_MESSAGE("Serialized instance layer not available: %s", pEnabledLayerName);
        }
    }

    // Add debug layers
    if (forceDebug)
    {
        const bool addedDebugLayer = [&] {
            // SDK >= 1.1.121
            if (AddLayerIfPresent("VK_LAYER_KHRONOS_validation"))
            {
                return true;
            }

            // SDK 1.1.0 - 1.1.121
            if (AddLayerIfPresent("VK_LAYER_LUNARG_standard_validation"))
            {
                return true;
            }

            // Earlier
            bool added = false;
            added |= AddLayerIfPresent("VK_LAYER_LUNARG_core_validation");
            added |= AddLayerIfPresent("VK_LAYER_LUNARG_object_tracker");
            added |= AddLayerIfPresent("VK_LAYER_LUNARG_parameter_validation");
            return added;
        }();

        if (!addedDebugLayer)
        {
            NV_MESSAGE("Could not find any debug layer to install");
        }
    }

    // Inject command line specified layers
    for (const std::string& explicitLayer : s_vecAdditionalLayers)
    {
        const char* pExplicitLayer = explicitLayer.c_str();
        const bool added = AddLayerIfPresent(pExplicitLayer);
        if (!added)
        {
            NV_MESSAGE("Command line specified layer not available: %s", pExplicitLayer);
        }
    }

    // Override create info with valid requested layers
    std::vector<const char*> enabledLayers;
    for (auto& layerName : vecExplicitlyEnabledLayers)
    {
        enabledLayers.push_back(layerName.c_str());
    }
    instanceCreateInfo.enabledLayerCount = uint32_t(enabledLayers.size());
    instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();

    // Create object
    const VkResult result = vkCreateInstance(&instanceCreateInfo, pAllocator, pInstance);
    NV_THROW_IF(result != VK_SUCCESS, "Failed to create VkInstance");

    VkInstance instance = *pInstance;

    // Record enabled layers
    s_InstanceInfo[instance].vecExplicitlyEnabledLayers = std::move(vecExplicitlyEnabledLayers);

    // Record available extensions
    for (uint32_t i = 0; i < instanceCreateInfo.enabledExtensionCount; i++)
    {
        s_InstanceExtensions[instance].insert(instanceCreateInfo.ppEnabledExtensionNames[i]);
    }

    // Get instance addresses
    BootstrapInstance(instance);

    // Get instance version according to vulkan-1
    VulkanReplay_EnumerateInstanceVersion(&s_InstanceInfo[instance].instanceVersion);

    // If this information is provided it can restrict which entry points
    // are available when running with the debug layers.
    if (pCreateInfo->pApplicationInfo)
    {
        s_InstanceInfo[instance].applicationInfoApiVersion = pCreateInfo->pApplicationInfo->apiVersion;
    }
    else
    {
#if defined(VKSC_VERSION_1_0)
        s_InstanceInfo[instance].applicationInfoApiVersion = VKSC_VERSION_1_0;
#else
        s_InstanceInfo[instance].applicationInfoApiVersion = VK_API_VERSION_1_0;
#endif
    }

    // Install debug callbacks
    if (forceDebug)
    {

        // Configure
        static VkDebugUtilsMessengerCreateInfoEXT debugReportCallbackCreateInfo = {};
        debugReportCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugReportCallbackCreateInfo.messageSeverity = VkDebugUtilsMessageSeverityFlagsEXT(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT);
        debugReportCallbackCreateInfo.messageType = VkDebugUtilsMessageTypeFlagsEXT(VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT);
        debugReportCallbackCreateInfo.pfnUserCallback = &DebugReportCallback;

        static VkDebugUtilsMessengerEXT s_DebugUtilsMessengerEXT = VK_NULL_HANDLE;
        VulkanReplay_CreateDebugUtilsMessengerEXT(*pInstance, &debugReportCallbackCreateInfo, nullptr, &s_DebugUtilsMessengerEXT);
    }

    // Return results
    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyInstance
//------------------------------------------------------------------------------
void VulkanReplay_DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyInstance(instance, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_EnumeratePhysicalDevices
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices)
{
    return NV_VK_VALIDATE(vkEnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceProcAddr
//------------------------------------------------------------------------------
PFN_vkVoidFunction VulkanReplay_GetDeviceProcAddr(VkDevice device, const char* pName)
{
    return vkGetDeviceProcAddr(device, pName);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetInstanceProcAddr
//------------------------------------------------------------------------------
PFN_vkVoidFunction VulkanReplay_GetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return vkGetInstanceProcAddr(instance, pName);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties)
{
    vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceQueueFamilyProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties)
{
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceMemoryProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties)
{
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFeatures
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures)
{
    vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFormatProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties)
{
    vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceImageFormatProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDevice
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Get device extensions
    //
    // NOTE: When "pLayerName" parameter is NULL, only extensions provided by the Vulkan implementation or
    // by implicitly enabled layers are returned.  When "pLayerName" is the name of a layer,
    // the extensions provided by that layer are returned.
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    // Enumerate extensions provided by ICD or implicitly enabled layers.
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> vecExtensionProperties(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, vecExtensionProperties.data());

    // Helper to see if an extension is available
    auto IsExtenionAvailable = [&](const char* pExtensionName) -> bool {
        for (VkExtensionProperties& extensionProperty : vecExtensionProperties)
        {
            if (strcmp(pExtensionName, extensionProperty.extensionName) == 0)
            {
                return true;
            }
        }
        return false;
    };

    // Get the instance that the physical device belongs to
    VkInstance instance = s_PhsyicalDeviceToInstanceMap[physicalDevice];

    // Enumerate extensions provided by explicitly enabled layers.
    for (const auto& explicitLayer : s_InstanceInfo[instance].vecExplicitlyEnabledLayers)
    {
        uint32_t count = 0;
        vkEnumerateDeviceExtensionProperties(physicalDevice, explicitLayer.c_str(), &count, nullptr);

        if (count)
        {
            std::vector<VkExtensionProperties> vecExt(count);
            vkEnumerateDeviceExtensionProperties(physicalDevice, explicitLayer.c_str(), &count, vecExt.data());

            // Record the extensions provided by this layer (may result in duplicated elements).
            std::move(vecExt.begin(), vecExt.end(), std::back_inserter(vecExtensionProperties));
        }
    }

    // Get instance layers
    uint32_t layerCount = 0;
    vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, nullptr);
    std::vector<VkLayerProperties> vecLayerProperties(layerCount);
    vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, vecLayerProperties.data());

    // Copy the device create info so that we can override some parameters so
    // that the original serialized instance is still valid in this runtime
    // environment.
    VkDeviceCreateInfo createInfo = *pCreateInfo;

    // Find intersection of enabled and serialized extensions
    std::vector<const char*> vecEnabledExtensions;
    for (uint32_t i = 0; i < pCreateInfo->enabledExtensionCount; i++)
    {
        const char* enabledExtensionName = pCreateInfo->ppEnabledExtensionNames[i];

#if defined(VK_NV_device_diagnostic_checkpoints)
        // Skip VK_NV_device_diagnostic_checkpoints if it is disabled
        if (s_DisableDeviceDiagnosticCheckpoints && strcmp(enabledExtensionName, VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME) == 0)
        {
            continue;
        }
#endif

        bool found = false;
        for (VkExtensionProperties& extensionProperty : vecExtensionProperties)
        {
            if (strcmp(enabledExtensionName, extensionProperty.extensionName) == 0)
            {
                vecEnabledExtensions.push_back(enabledExtensionName);
                found = true;
                break;
            }
        }
        if (!found)
        {
            NV_MESSAGE("Serialized device extension not available: %s", enabledExtensionName);
        }
    }

    auto IsExtensionEnabled = [&](const char* pExtensionName) -> bool {
        for (const char* pEnabled : vecEnabledExtensions)
        {
            if (strcmp(pEnabled, pExtensionName) == 0)
            {
                return true;
            }
        }
        return false;
    };

    auto TryEnableExtension = [&](const char* pExtension) -> bool {
        if (!IsExtenionAvailable(pExtension))
        {
            return false;
        }

        if (!IsExtensionEnabled(pExtension))
        {
            vecEnabledExtensions.push_back(pExtension);
        }

        return true;
    };

    // Always enable timeline semaphores if available. There are some
    // cases where the reflex API can create them even if the extension
    // isn't available.
#if defined(VK_KHR_timeline_semaphore)
    TryEnableExtension(VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME);
#endif

    // Always enable the debug markers if available as we inject the
    // them to denote the start/end of reset even if the real application
    // wasn't using them.
#if defined(VK_EXT_debug_marker)
    TryEnableExtension(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
#endif

    // Override create info with valid requested extensions
    createInfo.enabledExtensionCount = uint32_t(vecEnabledExtensions.size());
    createInfo.ppEnabledExtensionNames = vecEnabledExtensions.data();

    // Override queue create info with valid queue family indices
    std::vector<VkDeviceQueueCreateInfo> vecQueueCreateInfo;
    if (s_SawQueueFamilyMismatch)
    {

        // Queue family index map
        std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[physicalDevice];

        // Remapped queue family index <-> Override queue create info
        std::map<uint32_t, VkDeviceQueueCreateInfo> mapOverrideInfo;

        for (uint32_t queueCreateInfoIdx = 0; queueCreateInfoIdx < createInfo.queueCreateInfoCount; ++queueCreateInfoIdx)
        {

            // Queue family index remapping
            const VkDeviceQueueCreateInfo& origInfo = createInfo.pQueueCreateInfos[queueCreateInfoIdx];
            const uint32_t origIdx = origInfo.queueFamilyIndex;
            const uint32_t remappedIdx = queueFamilyMap[origIdx];

            // Add an override queue create info for the remapped queue family index if there hasn't been one
            const auto itr = mapOverrideInfo.find(origIdx);
            if (itr == mapOverrideInfo.end())
            {
                VkDeviceQueueCreateInfo newInfo = origInfo;
                newInfo.queueFamilyIndex = remappedIdx;
                mapOverrideInfo.insert(std::make_pair(remappedIdx, std::move(newInfo)));
                continue;
            }

            // There's an override queue create info for the remapped queue family index already,
            // simply update the queue count/priorities if needed
            VkDeviceQueueCreateInfo& overrideInfo = itr->second;
            if (overrideInfo.queueCount < origInfo.queueCount)
            {
                overrideInfo.queueCount = origInfo.queueCount;
                overrideInfo.pQueuePriorities = origInfo.pQueuePriorities;
            }
        }

        // Update queue create info
        vecQueueCreateInfo.reserve(mapOverrideInfo.size());
        for (auto& overrideInfoPair : mapOverrideInfo)
        {
            vecQueueCreateInfo.emplace_back(std::move(overrideInfoPair.second));
        }
        createInfo.queueCreateInfoCount = uint32_t(vecQueueCreateInfo.size());
        createInfo.pQueueCreateInfos = vecQueueCreateInfo.data();
    }

    // Find intersection of enabled and serialized layers
    std::vector<const char*> vecEnabledLayers;
    for (uint32_t i = 0; i < pCreateInfo->enabledLayerCount; i++)
    {
        const char* enabledLayerName = pCreateInfo->ppEnabledLayerNames[i];
        bool found = false;
        for (VkLayerProperties& layerProperty : vecLayerProperties)
        {
            if (strcmp(enabledLayerName, layerProperty.layerName) == 0)
            {
                vecEnabledLayers.push_back(enabledLayerName);
                found = true;
                break;
            }
        }
        if (!found)
        {
            NV_MESSAGE("Serialized device extension not available: %s", enabledLayerName);
        }
    }

    // Override create info with valid requested layers
    createInfo.enabledLayerCount = uint32_t(vecEnabledLayers.size());
    createInfo.ppEnabledLayerNames = vecEnabledLayers.data();

#if defined(VK_EXT_buffer_device_address) || defined(VK_KHR_buffer_device_address)
    // bufferDeviceAddressCaptureReplay might be enabled in capture but unavailable in replay
    bool bufferDeviceAddressCaptureReplayUnsupported = false;
    const auto pBufferAddressFeaturesEXT = reinterpret_cast<const VkPhysicalDeviceBufferAddressFeaturesEXT*>(FindPNextStructure(createInfo.pNext, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_ADDRESS_FEATURES_EXT));
    if (pBufferAddressFeaturesEXT && pBufferAddressFeaturesEXT->bufferDeviceAddressCaptureReplay)
    {
        VkPhysicalDeviceBufferAddressFeaturesEXT bufferAddressFeaturesEXT = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_ADDRESS_FEATURES_EXT };
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        physicalDeviceFeatures2.pNext = &bufferAddressFeaturesEXT;
        if (HasInstanceExtension(instance, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
        {
            vkGetPhysicalDeviceFeatures2KHR(physicalDevice, &physicalDeviceFeatures2);
        }
        else
        {
            vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);
        }
        if (!bufferAddressFeaturesEXT.bufferDeviceAddressCaptureReplay)
        {
            const_cast<VkPhysicalDeviceBufferAddressFeaturesEXT*>(pBufferAddressFeaturesEXT)->bufferDeviceAddressCaptureReplay = VK_FALSE;
            bufferDeviceAddressCaptureReplayUnsupported = true;
        }
    }
    const auto pBufferAddressFeatures = reinterpret_cast<const VkPhysicalDeviceBufferDeviceAddressFeatures*>(FindPNextStructure(createInfo.pNext, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES));
    if (pBufferAddressFeatures && pBufferAddressFeatures->bufferDeviceAddressCaptureReplay)
    {
        VkPhysicalDeviceBufferDeviceAddressFeatures bufferDeviceAddressFeatures = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES };
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        physicalDeviceFeatures2.pNext = &bufferDeviceAddressFeatures;
        if (HasInstanceExtension(instance, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
        {
            vkGetPhysicalDeviceFeatures2KHR(physicalDevice, &physicalDeviceFeatures2);
        }
        else
        {
            vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);
        }
        if (!bufferDeviceAddressFeatures.bufferDeviceAddressCaptureReplay)
        {
            const_cast<VkPhysicalDeviceBufferDeviceAddressFeatures*>(pBufferAddressFeatures)->bufferDeviceAddressCaptureReplay = VK_FALSE;
            bufferDeviceAddressCaptureReplayUnsupported = true;
        }
    }
    const auto pVulkan12Features = reinterpret_cast<const VkPhysicalDeviceVulkan12Features*>(FindPNextStructure(createInfo.pNext, VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES));
    if (pVulkan12Features && pVulkan12Features->bufferDeviceAddressCaptureReplay)
    {
        VkPhysicalDeviceVulkan12Features physicalDeviceVulkan12Features = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
        physicalDeviceFeatures2.pNext = &physicalDeviceVulkan12Features;
        if (HasInstanceExtension(instance, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
        {
            vkGetPhysicalDeviceFeatures2KHR(physicalDevice, &physicalDeviceFeatures2);
        }
        else
        {
            vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceFeatures2);
        }
        if (!physicalDeviceVulkan12Features.bufferDeviceAddressCaptureReplay)
        {
            const_cast<VkPhysicalDeviceVulkan12Features*>(pVulkan12Features)->bufferDeviceAddressCaptureReplay = VK_FALSE;
            bufferDeviceAddressCaptureReplayUnsupported = true;
        }
    }
    if (bufferDeviceAddressCaptureReplayUnsupported)
    {
        NV_MESSAGE("WARNING: Buffer device address capture/replay is not supported");
    }
#endif

    // Override VulkanSC VkDeviceObjectReservationCreateInfo
#if defined(VKSC_VERSION_1_0)
    {
        const VkDeviceObjectReservationCreateInfo* pDeviceObjectReservationInfo = reinterpret_cast<const VkDeviceObjectReservationCreateInfo*>(FindPNextStructure(pCreateInfo->pNext, VK_STRUCTURE_TYPE_DEVICE_OBJECT_RESERVATION_CREATE_INFO));
        NV_ASSERT(pDeviceObjectReservationInfo != nullptr);

        VkDeviceObjectReservationCreateInfo deviceObjectReservationInfo = *pDeviceObjectReservationInfo;

        // We need additional command pools in WorkStreamer, etc.
        deviceObjectReservationInfo.commandPoolRequestCount += 5;

        // We need additional command buffers to execute additional commands.
        // Given the additional command buffer count is hard to estimate, just give a default size
        // which currently can meet the requirement.
        deviceObjectReservationInfo.commandBufferRequestCount += 200;

        // Other additional object we may request in replayer.
        deviceObjectReservationInfo.fenceRequestCount += 10;
        deviceObjectReservationInfo.bufferRequestCount += 20;
        deviceObjectReservationInfo.imageRequestCount += 20;
        deviceObjectReservationInfo.deviceMemoryRequestCount += 20;

        ReplacePNextStructure((void**)&createInfo.pNext, VK_STRUCTURE_TYPE_DEVICE_OBJECT_RESERVATION_CREATE_INFO, &deviceObjectReservationInfo);
    }
#endif

    // Create object
    const VkResult result = vkCreateDevice(physicalDevice, &createInfo, nullptr, pDevice);
    NV_THROW_IF(result != VK_SUCCESS, "Failed to create VkDevice");

    // Get device addresses
    BootstrapDevice(*pDevice);

    // Enumerate queues to build mapping
    for (uint32_t queueCreateInfoIdx = 0; queueCreateInfoIdx < pCreateInfo->queueCreateInfoCount; queueCreateInfoIdx++)
    {
        const VkDeviceQueueCreateInfo& queueCreateInfo = pCreateInfo->pQueueCreateInfos[queueCreateInfoIdx];
        for (uint32_t queueIdx = 0; queueIdx < queueCreateInfo.queueCount; queueIdx++)
        {
            VkQueue queue = VK_NULL_HANDLE;
            std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[physicalDevice];
            vkGetDeviceQueue(*pDevice, queueFamilyMap[queueCreateInfo.queueFamilyIndex], queueIdx, &queue);
            s_QueueToDeviceMap[queue] = *pDevice;
        }

        s_DeviceQueues[*pDevice][queueCreateInfo.queueFamilyIndex] = queueCreateInfo;
    }

    // Add to map
    s_DeviceToPhysicalDeviceMap[*pDevice] = physicalDevice;
    s_SetDevices.insert(*pDevice);

    // Record available extensions
    for (uint32_t i = 0; i < createInfo.enabledExtensionCount; i++)
    {
        s_DeviceExtensions[*pDevice].insert(createInfo.ppEnabledExtensionNames[i]);
    }

    // Create allocator
    {
        VmaAllocator allocator = VK_NULL_HANDLE;

        VmaVulkanFunctions vulkanFunctions = {};
        vulkanFunctions.vkGetPhysicalDeviceProperties = &vkGetPhysicalDeviceProperties;
        vulkanFunctions.vkGetPhysicalDeviceMemoryProperties = &vkGetPhysicalDeviceMemoryProperties;
        vulkanFunctions.vkAllocateMemory = &vkAllocateMemory;
#if !defined(VKSC_VERSION_1_0)
        vulkanFunctions.vkFreeMemory = &vkFreeMemory;
#endif
        vulkanFunctions.vkMapMemory = &vkMapMemory;
        vulkanFunctions.vkUnmapMemory = &vkUnmapMemory;
        vulkanFunctions.vkFlushMappedMemoryRanges = &vkFlushMappedMemoryRanges;
        vulkanFunctions.vkInvalidateMappedMemoryRanges = &vkInvalidateMappedMemoryRanges;
        vulkanFunctions.vkBindBufferMemory = &vkBindBufferMemory;
        vulkanFunctions.vkBindImageMemory = &vkBindImageMemory;
        vulkanFunctions.vkGetBufferMemoryRequirements = &vkGetBufferMemoryRequirements;
        vulkanFunctions.vkGetImageMemoryRequirements = &vkGetImageMemoryRequirements;
        vulkanFunctions.vkCreateBuffer = &vkCreateBuffer;
        vulkanFunctions.vkDestroyBuffer = &vkDestroyBuffer;
        vulkanFunctions.vkCreateImage = &vkCreateImage;
        vulkanFunctions.vkDestroyImage = &vkDestroyImage;
        vulkanFunctions.vkCmdCopyBuffer = &vkCmdCopyBuffer;
#if !defined(VKSC_VERSION_1_0)
        if (s_InstanceInfo[instance].applicationInfoApiVersion >= VK_API_VERSION_1_1)
        {
            vulkanFunctions.vkGetBufferMemoryRequirements2KHR = &vkGetBufferMemoryRequirements2;
            vulkanFunctions.vkGetImageMemoryRequirements2KHR = &vkGetImageMemoryRequirements2;
            vulkanFunctions.vkBindBufferMemory2KHR = &vkBindBufferMemory2;
            vulkanFunctions.vkBindImageMemory2KHR = &vkBindImageMemory2;
            vulkanFunctions.vkGetPhysicalDeviceMemoryProperties2KHR = &vkGetPhysicalDeviceMemoryProperties2;
        }
        else
        {
            vulkanFunctions.vkGetBufferMemoryRequirements2KHR = &vkGetBufferMemoryRequirements2KHR;
            vulkanFunctions.vkGetImageMemoryRequirements2KHR = &vkGetImageMemoryRequirements2KHR;
            vulkanFunctions.vkBindBufferMemory2KHR = &vkBindBufferMemory2KHR;
            vulkanFunctions.vkBindImageMemory2KHR = &vkBindImageMemory2KHR;
            vulkanFunctions.vkGetPhysicalDeviceMemoryProperties2KHR = &vkGetPhysicalDeviceMemoryProperties2KHR;
        }
#endif

#if !defined(VKSC_VERSION_1_0)
        if (s_InstanceInfo[instance].applicationInfoApiVersion >= VK_API_VERSION_1_3)
        {
            vulkanFunctions.vkGetDeviceBufferMemoryRequirements = &vkGetDeviceBufferMemoryRequirements;
            vulkanFunctions.vkGetDeviceImageMemoryRequirements = &vkGetDeviceImageMemoryRequirements;
        }
#endif

        VmaAllocatorCreateInfo allocatorCreateInfo = {};
        allocatorCreateInfo.device = *pDevice;
        allocatorCreateInfo.physicalDevice = physicalDevice;
        allocatorCreateInfo.instance = instance;
        allocatorCreateInfo.vulkanApiVersion = s_InstanceInfo[instance].applicationInfoApiVersion;
        allocatorCreateInfo.pVulkanFunctions = &vulkanFunctions;
#if !defined(VKSC_VERSION_1_0)
        allocatorCreateInfo.flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
#endif

        // VMA only supports Vulkan versions below than or equal to 1.3 or VulkanSC version 1.0
        uint32_t applicationApiVersion = s_InstanceInfo[instance].applicationInfoApiVersion;
        uint32_t apiVersionVariant = VK_API_VERSION_VARIANT(applicationApiVersion);
        uint32_t apiVersionMajor = VK_API_VERSION_MAJOR(applicationApiVersion);
        uint32_t apiVersionMinor = VK_API_VERSION_MINOR(applicationApiVersion);
#if defined(VKSC_VERSION_1_0)
        if (apiVersionVariant != VKSC_API_VARIANT || apiVersionMajor != 1 || apiVersionMinor > 0)
        {
            allocatorCreateInfo.vulkanApiVersion = VKSC_API_VERSION_1_0;
        }
#else
        if (apiVersionMajor != 1 || apiVersionMinor > 3)
        {
            allocatorCreateInfo.vulkanApiVersion = VK_API_VERSION_1_3;
        }
#endif
        else
        {
            allocatorCreateInfo.vulkanApiVersion = applicationApiVersion;
        }

        vmaCreateAllocator(&allocatorCreateInfo, &allocator);
        s_Allocators[*pDevice] = allocator;
    }

    // Create resource helper
    {
        const uint32_t transferFamily = GetQueueFamilyWithFlagBit(*pDevice, VK_QUEUE_TRANSFER_BIT);
        s_ResourceUpdateHelpers[*pDevice] = std::make_unique<WorkStreamer>(*pDevice, transferFamily);
    }

    // Create host allocator
    {
        s_HostAllocators[*pDevice] = std::make_unique<HostAllocator>();
    }

#if defined(NV_DUMMY_FULL_SCREEN)
    // Set to fullscreen window if the option enabled
    if (s_DummyFullscreen)
    {
        WindowSystemInstance().SetCreatingFullscreen(true);
    }
#endif

    // Store device version
    s_DeviceVersion[*pDevice] = std::min(physicalDeviceProperties.apiVersion, s_InstanceInfo[instance].applicationInfoApiVersion);

    // Return results
    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyDevice
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDevice(device, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_EnumerateInstanceVersion
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumerateInstanceVersion(uint32_t* pApiVersion)
{
    // Get ICD addresses
    BootstrapICD();

    // This API came in 1.1, some old loader doesn't have it
    if (Has_vkEnumerateInstanceVersion())
    {
        return NV_VK_VALIDATE(vkEnumerateInstanceVersion(pApiVersion));
    }
    else
    {
#if defined(VKSC_VERSION_1_0)
        *pApiVersion = VKSC_API_VERSION_1_0;
#else
        *pApiVersion = VK_API_VERSION_1_0;
#endif
        return VK_SUCCESS;
    }
}

#endif // VK_VERSION_1_1

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_EnumerateInstanceLayerProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    return NV_VK_VALIDATE(vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_EnumerateInstanceExtensionProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    return NV_VK_VALIDATE(vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_EnumerateDeviceLayerProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties)
{
    return NV_VK_VALIDATE(vkEnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_EnumerateDeviceExtensionProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties)
{
    return NV_VK_VALIDATE(vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceQueue
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue)
{
    if (s_SawQueueFamilyMismatch)
    {
        // Using remapped queue family index
        const VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];
        std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[physicalDevice];
        vkGetDeviceQueue(device, queueFamilyMap[queueFamilyIndex], queueIndex, pQueue);
    }
    else
    {
        vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
    }
    s_QueueInfo[*pQueue] = QueueInfo{ device, queueFamilyIndex, queueIndex };
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueSubmit
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
    // Count the number of command buffers
    size_t commandBufferCount = 0;
    for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
    {
        commandBufferCount += pSubmits[submitIdx].commandBufferCount;
    }

    // Get associated device
    const VkDevice device = s_QueueToDeviceMap[queue];

    // We need to inject a fence for submit calls without one. This is a side effect of replaying
    // a single frame where we do not reallocate command buffers that were originally created in
    // frame using a "fired and forgot" pattern.
    if (fence == VK_NULL_HANDLE)
    {
        auto itr = s_InjectedSubmitFences.find(s_SubmitIdx);
        if (itr == s_InjectedSubmitFences.end())
        {
            VULKAN_REPLAY_WRITE_LOCK();
            VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
            vkCreateFence(device, &createInfo, nullptr, &fence);
            s_InjectedSubmitFences[s_SubmitIdx] = fence;
            s_FenceStatus[fence] = FenceStatus{};

            // Create multi-buffering clones
            for (uint32_t i = 1; i < s_BufferingSize; i++)
            {
                VkFence clone;
                vkCreateFence(device, &createInfo, nullptr, &clone);
                s_FenceOverrides[fence].push_back(clone);
                s_FenceStatus[clone] = FenceStatus{};
            }
        }
        else
        {
            fence = itr->second;
        }
    }

    // Update fence
    VkFence originalFence = fence;
    fence = GetActive_Fence(s_BufferingIdx, fence);

    // The fence must be unsignaled; this should only be possible in multi-frame
    // synchronization cases
    WaitForPendingFence(device, fence, "QueueSubmit");

    // Track the state of events within these command buffers
    HandleEvents(device, submitCount, pSubmits);

    auto& tls = GetThreadState();

    // Helper generate patched queue submission parameters
    auto GenerateQueueSubmitParams = [&](uint32_t bufferingIdx, const OverrideKey& overrideKey) -> QueueSubmit_Params {
        // Local storage of submit information we are going to override
        std::vector<VkSubmitInfo> vecSubmits(submitCount);
#if defined(VK_KHR_timeline_semaphore)
        std::vector<VkTimelineSemaphoreSubmitInfoKHR> vecTimelineSemaphoreSubmitInfo(submitCount);
#endif
        std::vector<std::vector<VkSemaphore>> vecWaitSemaphores(submitCount);
        std::vector<std::vector<VkSemaphore>> vecSignalSemaphores(submitCount);
        std::vector<std::vector<VkCommandBuffer>> vecCommandBuffers(submitCount);
        std::vector<std::vector<uint64_t>> vecWaitValues(submitCount);
        std::vector<std::vector<uint64_t>> vecSignalValues(submitCount);

        // Get fence for this buffering index
        VkFence fence = GetActive_Fence(bufferingIdx, originalFence);

        // Patch up each submit
        for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
        {

#if defined(VK_KHR_timeline_semaphore)
            // Get optional timeline submit info
            const VkTimelineSemaphoreSubmitInfoKHR* pTimelineSemaphoreSubmitInfo = reinterpret_cast<const VkTimelineSemaphoreSubmitInfoKHR*>(FindStructure(VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO, pSubmits[submitIdx].pNext));
            if (pTimelineSemaphoreSubmitInfo)
            {
                vecTimelineSemaphoreSubmitInfo[submitIdx] = *pTimelineSemaphoreSubmitInfo;
            }
#endif

            // Override command buffer based on swapchain usage
            vecSubmits[submitIdx] = pSubmits[submitIdx];
            vecCommandBuffers[submitIdx].resize(pSubmits[submitIdx].commandBufferCount);
            vecSubmits[submitIdx].pCommandBuffers = vecCommandBuffers[submitIdx].data();
            for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferCount; commandBufferIdx++)
            {
                const VkCommandBuffer commandBuffer = pSubmits[submitIdx].pCommandBuffers[commandBufferIdx];

                VkCommandBuffer activeCommandBuffer = GetActive_CommandBuffer(s_BufferingIdx, commandBuffer);

                // Make sure this command buffer was re-recorded in frame if the option
                // is enabled.
                if (s_ForceResetCommandBuffers && !WasCommandBufferRecordedInFrame(commandBuffer))
                {
                    auto itr = s_CommandBufferToRecordRev0.find(commandBuffer);
                    NV_ASSERT(itr != s_CommandBufferToRecordRev0.end());
                    DoRecordCommandBuffer_Dispatch(GetThreadState().activeOverride, device, activeCommandBuffer, itr->second);
                }

                vecCommandBuffers[submitIdx][commandBufferIdx] = activeCommandBuffer;
            }

            // Clear signaled semaphores and trigger a hard wait on all pending semaphores
            // if we are being asked to wait on a semaphore we don't know about. This
            // indicates a dependent multi-frame synchronization event.
            if (!s_IgnoreSemaphores)
            {
                for (uint32_t waitSemaphoreIdx = 0; waitSemaphoreIdx < pSubmits[submitIdx].waitSemaphoreCount; waitSemaphoreIdx++)
                {
                    VkSemaphore waitSemaphore = pSubmits[submitIdx].pWaitSemaphores[waitSemaphoreIdx];
                    const SemaphoreInfo* pInfo = LookupSemaphoreInfo(waitSemaphore);
                    waitSemaphore = GetActive_Sempahore(bufferingIdx, waitSemaphore);
#if defined(VK_KHR_timeline_semaphore)
                    if (pInfo->type == VK_SEMAPHORE_TYPE_BINARY_KHR)
                    {
                        SemaphoreStatus& waitSemaphoreStatus = GetSempahoreStatus(waitSemaphore);
                        if (!waitSemaphoreStatus.signaled)
                        {
                            // TODO: (DG-11075) Add paranoia mode to sync here
                        }
                        else
                        {
                            vecWaitSemaphores[submitIdx].push_back(waitSemaphore);
                            waitSemaphoreStatus.signaled = false;
                            if (pTimelineSemaphoreSubmitInfo && (waitSemaphoreIdx < pTimelineSemaphoreSubmitInfo->waitSemaphoreValueCount))
                            {
                                vecWaitValues[submitIdx].push_back(0);
                            }
                        }
                    }
                    else if (pInfo->type == VK_SEMAPHORE_TYPE_TIMELINE_KHR)
                    {
                        NV_ASSERT(pTimelineSemaphoreSubmitInfo && pTimelineSemaphoreSubmitInfo->pWaitSemaphoreValues);
                        uint64_t waitValue = pTimelineSemaphoreSubmitInfo->pWaitSemaphoreValues[waitSemaphoreIdx];
                        if (waitValue > pInfo->endValue)
                        {
                            NV_MESSAGE("WARNING: Timeline sempahore is waiting on value (%u) outside of frame (%u); work will never be submitted", waitValue, pInfo->endValue);
                        }
                        if (IsAvailableForTimelineWait(pInfo, waitValue))
                        {
                            waitValue += (s_FrameIdx * pInfo->delta);
                            vecWaitSemaphores[submitIdx].push_back(waitSemaphore);
                            vecWaitValues[submitIdx].push_back(waitValue);
                        }
                    }
#else
                    SemaphoreStatus& waitSemaphoreStatus = GetSempahoreStatus(waitSemaphore);
                    if (waitSemaphoreStatus.signaled)
                    {
                        vecWaitSemaphores[submitIdx].push_back(waitSemaphore);
                        waitSemaphoreStatus.signaled = false;
                    }
#endif
                }
            }
            vecSubmits[submitIdx].waitSemaphoreCount = static_cast<uint32_t>(vecWaitSemaphores[submitIdx].size());
            vecSubmits[submitIdx].pWaitSemaphores = vecWaitSemaphores[submitIdx].data();

            // Patch up signal semaphores to remove ones that are already signaled
            if (!s_IgnoreSemaphores)
            {
                for (uint32_t signalSemaphoreIdx = 0; signalSemaphoreIdx < pSubmits[submitIdx].signalSemaphoreCount; signalSemaphoreIdx++)
                {
                    VkSemaphore signalSemaphore = pSubmits[submitIdx].pSignalSemaphores[signalSemaphoreIdx];
                    SemaphoreInfo* pInfo = LookupSemaphoreInfo(signalSemaphore);
                    signalSemaphore = GetActive_Sempahore(bufferingIdx, signalSemaphore);
#if defined(VK_KHR_timeline_semaphore)
                    if (pInfo->type == VK_SEMAPHORE_TYPE_BINARY_KHR)
                    {
                        SemaphoreStatus& signalSemaphoreStatus = GetSempahoreStatus(signalSemaphore);
                        if (signalSemaphoreStatus.signaled)
                        {
                            // TODO: (DG-11075) Add paranoia mode to sync here
                        }
                        else
                        {
                            vecSignalSemaphores[submitIdx].push_back(signalSemaphore);
                            signalSemaphoreStatus.signaled = true;
                            signalSemaphoreStatus.lastSignaledFrame = s_FrameIdx;
                            if (pTimelineSemaphoreSubmitInfo && (signalSemaphoreIdx < pTimelineSemaphoreSubmitInfo->signalSemaphoreValueCount))
                            {
                                vecSignalValues[submitIdx].push_back(0);
                            }
                        }
                    }
                    else if (pInfo->type == VK_SEMAPHORE_TYPE_TIMELINE_KHR)
                    {
                        NV_ASSERT(pTimelineSemaphoreSubmitInfo && pTimelineSemaphoreSubmitInfo->pSignalSemaphoreValues);
                        uint64_t signalValue = pTimelineSemaphoreSubmitInfo->pSignalSemaphoreValues[signalSemaphoreIdx];
                        RecordTimelineSignal(pInfo, signalValue);
                        signalValue += (s_FrameIdx * pInfo->delta);
                        vecSignalSemaphores[submitIdx].push_back(signalSemaphore);
                        vecSignalValues[submitIdx].push_back(signalValue);
                        pInfo->value = signalValue;
                    }
#else
                    SemaphoreStatus& signalSemaphoreStatus = GetSempahoreStatus(signalSemaphore);
                    if (!signalSemaphoreStatus.signaled)
                    {
                        vecSignalSemaphores[submitIdx].push_back(signalSemaphore);
                        signalSemaphoreStatus.signaled = true;
                        signalSemaphoreStatus.lastSignaledFrame = s_FrameIdx;
                    }
#endif
                }
            }
            vecSubmits[submitIdx].signalSemaphoreCount = static_cast<uint32_t>(vecSignalSemaphores[submitIdx].size());
            vecSubmits[submitIdx].pSignalSemaphores = vecSignalSemaphores[submitIdx].data();

#if defined(VK_KHR_timeline_semaphore)
            // Inject our timeline submit information if applicable
            if (pTimelineSemaphoreSubmitInfo)
            {
                vecTimelineSemaphoreSubmitInfo[submitIdx].waitSemaphoreValueCount = static_cast<uint32_t>(vecWaitValues[submitIdx].size());
                vecTimelineSemaphoreSubmitInfo[submitIdx].pWaitSemaphoreValues = vecWaitValues[submitIdx].data();
                vecTimelineSemaphoreSubmitInfo[submitIdx].signalSemaphoreValueCount = static_cast<uint32_t>(vecSignalValues[submitIdx].size());
                vecTimelineSemaphoreSubmitInfo[submitIdx].pSignalSemaphoreValues = vecSignalValues[submitIdx].data();
                VkBaseOutStructure* pThis = reinterpret_cast<VkBaseOutStructure*>(&vecSubmits[submitIdx]);
                while (pThis && pThis->pNext)
                {
                    if (pThis->pNext->sType == VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO)
                    {
                        pThis->pNext = reinterpret_cast<VkBaseOutStructure*>(&vecTimelineSemaphoreSubmitInfo[submitIdx]);
                        break;
                    }
                    pThis = pThis->pNext;
                }
            }
#endif
        }

        // Fences associated with this command buffer to so that we don't resubmit during capture
        if (fence != VK_NULL_HANDLE)
        {
            for (const auto& vecCommandBuffers_PerSubmit : vecCommandBuffers)
            {
                for (VkCommandBuffer cmdBuffer : vecCommandBuffers_PerSubmit)
                {
                    s_CommandBufferToFence[cmdBuffer] = fence;
                }
            }
        }

        // Patch up each submit
        for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
        {
            for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferCount; commandBufferIdx++)
            {
                const VkCommandBuffer commandBuffer = pSubmits[submitIdx].pCommandBuffers[commandBufferIdx];
                auto itr = s_CommandBufferToQueryPoolReset.find(commandBuffer);
                if (itr != s_CommandBufferToQueryPoolReset.end())
                {
                    s_QueryPoolResetInFrame.insert(itr->second);
                }
            }
        }

        // Deep copy
        return QueueSubmit_Params(*s_HostAllocators[device], queue, submitCount, vecSubmits.data(), fence);
    };

    // Get baked parameters
    // TODO: (DG-11075) - Cache this
    const QueueSubmit_Params params = GenerateQueueSubmitParams(s_BufferingIdx, tls.activeOverride);

    // Wait for all async command buffer recording to finish
    for (uint32_t submitIdx = 0; submitIdx < params.submitCount; ++submitIdx)
    {
        const VkSubmitInfo& submitInfo = params.pSubmits[submitIdx];
        for (uint32_t cmdBufferIdx = 0; cmdBufferIdx < submitInfo.commandBufferCount; ++cmdBufferIdx)
        {
            VkCommandBuffer cmdBuffer = submitInfo.pCommandBuffers[cmdBufferIdx];
            WaitForCommandBufferRecord(cmdBuffer);
        }
    }

    VkResult result = vkQueueSubmit(params.queue, params.submitCount, params.pSubmits, params.fence);

    // Increment counter
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        s_SubmitIdx++;
    }

    // In flight fence
    if (params.fence != VK_NULL_HANDLE)
    {
        VULKAN_REPLAY_WRITE_LOCK();
        GetFenceStatus(params.fence).signaled = true;
    }

    // Optionally wait immediately after every submit
    if (s_SyncAfterSumbit)
    {
        VkResult syncResult = vkQueueWaitIdle(params.queue);
        NV_VK_VALIDATE(syncResult)
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueWaitIdle
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueueWaitIdle(VkQueue queue)
{
    return NV_VK_VALIDATE(vkQueueWaitIdle(queue));
}

//------------------------------------------------------------------------------
// VulkanReplay_DeviceWaitIdle
//------------------------------------------------------------------------------
VkResult VulkanReplay_DeviceWaitIdle(VkDevice device)
{
    return NV_VK_VALIDATE(vkDeviceWaitIdle(device));
}

//------------------------------------------------------------------------------
// VulkanReplay_AllocateMemory
//------------------------------------------------------------------------------
VkResult VulkanReplay_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // We are in a legacy path;
    // Call into managed helper now
    VulkanHelper_InitializeDeviceMemoryInfo initializeInfo = {};
    return VulkanHelper_AllocateAndInitializeMemory3(device, pAllocateInfo, &initializeInfo, pMemory, nullptr);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_FreeMemory
//------------------------------------------------------------------------------
void VulkanReplay_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    // This memory wasn't actually allocate so just bail
    if (!s_DeviceMemoryInfo[memory].isAllocated)
    {
        return;
    }

    vkFreeMemory(device, memory, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_MapMemory
//------------------------------------------------------------------------------
VkResult VulkanReplay_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
    // This memory wasn't actually allocate so just bail
    if (!s_DeviceMemoryInfo[memory].isAllocated)
    {
        return VK_SUCCESS;
    }

    // Ignore if memory is already mapped from previous frame
    auto itr = s_MemoryMappingInfo.find(memory);
    if (itr != s_MemoryMappingInfo.end())
    {
        return VK_SUCCESS;
    }

    const VkResult result = vkMapMemory(device, memory, offset, size, flags, ppData);

    if (result == VK_SUCCESS)
    {
        s_MemoryMappingInfo[memory] = MemoryMappingInfo{ offset, size, flags, *ppData };
    }
    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_UnmapMemory
//------------------------------------------------------------------------------
void VulkanReplay_UnmapMemory(VkDevice device, VkDeviceMemory memory)
{
    // This memory wasn't actually allocate so just bail
    if (!s_DeviceMemoryInfo[memory].isAllocated)
    {
        return;
    }

    s_MemoryMappingInfo.erase(memory);
    vkUnmapMemory(device, memory);
}

//------------------------------------------------------------------------------
// VulkanReplay_FlushMappedMemoryRanges
//------------------------------------------------------------------------------
VkResult VulkanReplay_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    // Only flush memory ranges that have been allocated
    std::vector<VkMappedMemoryRange> vecMemoryRanges;
    for (uint32_t i = 0; i < memoryRangeCount; i++)
    {
        VkDeviceMemory memory = pMemoryRanges[i].memory;
        if (s_DeviceMemoryInfo[memory].isAllocated)
        {
            vecMemoryRanges.push_back(pMemoryRanges[i]);
        }
    }

    return NV_VK_VALIDATE(vkFlushMappedMemoryRanges(device, uint32_t(vecMemoryRanges.size()), vecMemoryRanges.data()));
}

//------------------------------------------------------------------------------
// VulkanReplay_InvalidateMappedMemoryRanges
//------------------------------------------------------------------------------
VkResult VulkanReplay_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
    // Only flush memory ranges that have been allocated
    std::vector<VkMappedMemoryRange> vecMemoryRanges;
    for (uint32_t i = 0; i < memoryRangeCount; i++)
    {
        VkDeviceMemory memory = pMemoryRanges[i].memory;
        if (s_DeviceMemoryInfo[memory].isAllocated)
        {
            vecMemoryRanges.push_back(pMemoryRanges[i]);
        }
    }

    return NV_VK_VALIDATE(vkInvalidateMappedMemoryRanges(device, uint32_t(vecMemoryRanges.size()), vecMemoryRanges.data()));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceMemoryCommitment
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes)
{
    vkGetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetBufferMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
    vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

//------------------------------------------------------------------------------
// VulkanReplay_BindBufferMemory
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // JIT patch up image memory if changes are needed
    uint32_t memoryTypeIdx = PatchBufferMemory(device, buffer, memory, memoryOffset);

    // Real call
    const VkResult result = NV_VK_VALIDATE(vkBindBufferMemory(device, buffer, memory, memoryOffset));

    // Store information about this bind
    if (result == VK_SUCCESS)
    {
        VkBindBufferMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO };
        info.buffer = buffer;
        info.memory = memory;
        info.memoryOffset = memoryOffset;
        s_BufferBindInfo[buffer] = BindBufferMemoryInfo{ memoryTypeIdx, info };
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanReplay_GetImageMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements)
{
    vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
}

//------------------------------------------------------------------------------
// VulkanReplay_BindImageMemory
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // JIT patch up image memory if changes are needed
    uint32_t memoryTypeIdx = PatchImageMemory(device, image, memory, memoryOffset);

    // Real call
    VkResult result = NV_VK_VALIDATE(vkBindImageMemory(device, image, memory, memoryOffset));

    // Store information about this bind
    if (result == VK_SUCCESS)
    {
        VkBindImageMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO };
        info.image = image;
        info.memory = memory;
        info.memoryOffset = memoryOffset;
        s_ImageBindInfo[image] = BindImageMemoryInfo{ memoryTypeIdx, info };
    }

    return result;
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageSparseMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)
{
    vkGetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties)
{
    vkGetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties);
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueBindSparse
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
    // The fence must be unsignaled; this should only be possible in multi-frame
    // synchronization cases
    const VkDevice device = s_QueueToDeviceMap[queue];
    WaitForPendingFence(device, fence, "QueueBindSparse");

    const VkResult result = NV_VK_VALIDATE(vkQueueBindSparse(queue, bindInfoCount, pBindInfo, fence));

    return result;
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateFence
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    const VkResult ret = NV_VK_VALIDATE(vkCreateFence(device, pCreateInfo, pAllocator, pFence));

    if (ret == VK_SUCCESS)
    {

        const bool isSignaled = !!(pCreateInfo->flags & VK_FENCE_CREATE_SIGNALED_BIT);

        s_FenceToInfoMap[*pFence] = FenceInfo{ device, pCreateInfo };
        FenceStatus status = FenceStatus{ isSignaled };
        s_FenceStatus[*pFence] = status;

        // Build multi-buffering
        for (uint32_t i = 1; i < s_BufferingSize; i++)
        {
            VkFence clone = VK_NULL_HANDLE;
            vkCreateFence(device, pCreateInfo, pAllocator, &clone);
            NV_ASSERT(clone != VK_NULL_HANDLE);
            s_FenceOverrides[*pFence].push_back(clone);
            s_FenceStatus[clone] = status;
        }
    }

    return ret;
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyFence
//------------------------------------------------------------------------------
void VulkanReplay_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyFence(device, fence, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_ResetFences
//------------------------------------------------------------------------------
VkResult VulkanReplay_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
    // If we have outstanding fences and we are attempting to reset a fence
    // we don't think needs reset this indicates we are in a multi-frame
    // synchronization problem as the fence is probably from a previous frame.
    // To handle this case we need to wait on all fences that are outstanding.
    for (uint32_t i = 0; i < fenceCount; i++)
    {

        VkFence fence = GetActive_Fence(s_BufferingIdx, pFences[i]);
        WaitForPendingFence(device, fence, "ResetFences");
    }

    std::vector<VkFence> vecFences(fenceCount);
    for (uint32_t i = 0; i < fenceCount; i++)
    {
        vecFences[i] = GetActive_Fence(s_BufferingIdx, pFences[i]);
    }

    const VkResult result = vkResetFences(device, fenceCount, vecFences.data());
    if (result != VK_SUCCESS)
    {
        return result;
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetFenceStatus
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetFenceStatus(VkDevice device, VkFence fence)
{
    fence = GetActive_Fence(s_BufferingIdx, fence);

    VkResult result = vkGetFenceStatus(device, fence);

    // If the application is querying the status of fence that is in flight and
    // the query didn't return success we must assume the original application
    // was intending to wait on this fence. For example, this'll catch an application
    // that is using a spin-loop of vkGetFenceStatus calls instead of a singular
    // vkWaitForFences call.
    if (result != VK_SUCCESS)
    {
        if (WaitForPendingFence(device, fence, "GetFenceStatus"))
        {
            return VK_SUCCESS;
        }
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_WaitForFences
//------------------------------------------------------------------------------
VkResult VulkanReplay_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
    // Due to multithreaded recording, the fence we are trying to wait for might be just resetting in a recording thread
    // calling WaitForPendingFence simultaneously (if a command buffer being recorded is assoicated with the same fence).
    // Guard the fence status checking and the fence waiting to avoid the simultaneous use and the status mismatch.
    VULKAN_REPLAY_WRITE_LOCK();

    // Only wait on fences we know are signaled; this will might hang indefinitely
    // otherwise.
    std::vector<VkFence> vecFences;
    for (uint32_t i = 0; i < fenceCount; i++)
    {
        VkFence fence = GetActive_Fence(s_BufferingIdx, pFences[i]);
        if (GetFenceStatus(fence).signaled)
        {
            vecFences.push_back(fence);
        }
    }

    // Bail if empty
    if (vecFences.empty())
    {
        return VK_SUCCESS;
    }

    // Real call
    VkResult result = vkWaitForFences(device, static_cast<uint32_t>(vecFences.size()), vecFences.data(), waitAll, timeout);
    if (result != VK_TIMEOUT)
    {
        return NV_VK_VALIDATE(result);
    }

    // Keep trying for 2500 ms. We can run into VK_TIMEOUT results if we are
    // running much faster than the original application.
    using clock = std::chrono::system_clock;
    using milliseconds = std::chrono::milliseconds;
    auto start = clock::now();
    while (true)
    {
        result = vkWaitForFences(device, static_cast<uint32_t>(vecFences.size()), vecFences.data(), waitAll, timeout);
        if (result == VK_TIMEOUT)
        {
            auto delta = clock::now() - start;
            if (delta > milliseconds(2500))
            {
                NV_LOG("ERROR: Bailing on stuck fence!?");
                break;
            }
        }
        else
        {
            break;
        }
    }

    // These fences are no longer outstanding since we know they have completed
    for (VkFence fence : vecFences)
    {
        GetFenceStatus(fence).signaled = false;
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateSemaphore
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // We treat Reflex semaphores as normal type so remove this internal data
#if defined(VK_NV_low_latency)
    RemovePNextStructure((void*)pCreateInfo, VK_STRUCTURE_TYPE_QUERY_LOW_LATENCY_SUPPORT_NV);
#endif

    VkResult result = vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);

    if (result == VK_SUCCESS)
    {
#if defined(VK_KHR_timeline_semaphore)
        auto GetType = [](const VkSemaphoreCreateInfo* pCreateInfo) -> VkSemaphoreTypeKHR {
            const VkSemaphoreTypeCreateInfoKHR* pTypeCreateInfo = reinterpret_cast<const VkSemaphoreTypeCreateInfoKHR*>(FindStructure(VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO_KHR, pCreateInfo));
            return pTypeCreateInfo ? pTypeCreateInfo->semaphoreType : VK_SEMAPHORE_TYPE_BINARY_KHR;
        };
#endif

        SemaphoreInfo info = {};
        info.device = device;
        info.pCreateInfo = pCreateInfo;
#if defined(VK_KHR_timeline_semaphore)
        info.type = GetType(pCreateInfo);
#endif
        s_SemaphoreToInfoMap.insert(std::make_pair(*pSemaphore, info));

        // Initialize status
        s_SemaphoreStatus[*pSemaphore] = SemaphoreStatus{};

        // Build multi-buffer clones
        for (uint32_t i = 1; i < s_BufferingSize; i++)
        {
            VkSemaphore clone = VK_NULL_HANDLE;
            vkCreateSemaphore(device, pCreateInfo, pAllocator, &clone);
            NV_ASSERT(clone != VK_NULL_HANDLE);
            s_SemaphoreOverrides[*pSemaphore].push_back(clone);
            s_SemaphoreStatus[clone] = SemaphoreStatus{};
        }
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroySemaphore
//------------------------------------------------------------------------------
void VulkanReplay_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroySemaphore(device, semaphore, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateEvent
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateEvent(device, pCreateInfo, pAllocator, pEvent));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyEvent
//------------------------------------------------------------------------------
void VulkanReplay_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyEvent(device, event, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetEventStatus
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetEventStatus(VkDevice device, VkEvent event)
{
    return NV_VK_VALIDATE(vkGetEventStatus(device, event));
}

//------------------------------------------------------------------------------
// VulkanReplay_SetEvent
//------------------------------------------------------------------------------
VkResult VulkanReplay_SetEvent(VkDevice device, VkEvent event)
{
    s_ActiveEvents.insert(event);

    return NV_VK_VALIDATE(vkSetEvent(device, event));
}

//------------------------------------------------------------------------------
// VulkanReplay_ResetEvent
//------------------------------------------------------------------------------
VkResult VulkanReplay_ResetEvent(VkDevice device, VkEvent event)
{
    // If we are reseting an active event, remove it from the active list. If
    // we are reseting an event we don't think is active we have observed a
    // potential cross-frame synchronization issue and need to flush.
    auto itr = s_ActiveEvents.find(event);
    if (itr != s_ActiveEvents.end())
    {
        s_ActiveEvents.erase(itr);
    }

    return NV_VK_VALIDATE(vkResetEvent(device, event));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateQueryPool
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Associate create info
    const VkResult status = vkCreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    if (status == VK_SUCCESS)
    {
        s_QueryPoolToCreateInfo[*pQueryPool] = pCreateInfo;
    }
    return NV_VK_VALIDATE(status);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyQueryPool
//------------------------------------------------------------------------------
void VulkanReplay_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyQueryPool(device, queryPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetQueryPoolResults
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags)
{
    // By default vkCmdCopyQueryPoolResults commands are ignored but we can
    // potentially allow them if the query pool was reset in frame. If the pool
    // never reset it will almost certainly be a hang (or fatal error) attempting
    // to copy the query results.
    if (!AllowGetQueryPoolResult(queryPool, firstQuery, queryCount))
    {
        return VK_SUCCESS;
    }

    // This call should pass as we only serialize vkGetQueryPoolResults that succeed
    VkResult result = vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    if (result != VK_NOT_READY)
    {
        return NV_VK_VALIDATE(result);
    }

    // Keep trying for 2500 ms. We can run into VK_NOT_READY results if we are
    // running much faster than the original application.
    using clock = std::chrono::system_clock;
    using milliseconds = std::chrono::milliseconds;
    auto start = clock::now();
    while (true)
    {
        result = vkGetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
        if (result == VK_NOT_READY)
        {
            auto delta = clock::now() - start;
            if (delta > milliseconds(2500))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return NV_VK_VALIDATE(result);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_ResetQueryPool
//------------------------------------------------------------------------------
void VulkanReplay_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    // Flag as reset
    if (!s_DisableCopyQueryPoolResults)
    {
        s_QueryPoolResetInFrame.insert(queryPool);
        std::fill_n(s_QueryPoolAvailableRanges[queryPool].begin() + firstQuery, queryCount, VK_FALSE);
    }

    vkResetQueryPool(device, queryPool, firstQuery, queryCount);
}

#endif // VK_VERSION_1_2

#if defined(VK_EXT_host_query_reset)
//------------------------------------------------------------------------------
// VulkanReplay_ResetQueryPoolEXT
//------------------------------------------------------------------------------
void VulkanReplay_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    // Flag as reset
    if (!s_DisableCopyQueryPoolResults)
    {
        s_QueryPoolResetInFrame.insert(queryPool);
        std::fill_n(s_QueryPoolAvailableRanges[queryPool].begin() + firstQuery, queryCount, VK_FALSE);
    }

    vkResetQueryPoolEXT(device, queryPool, firstQuery, queryCount);
}

#endif // VK_EXT_host_query_reset

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateBuffer
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Create buffer
    return NV_VK_VALIDATE(vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyBuffer
//------------------------------------------------------------------------------
void VulkanReplay_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyBuffer(device, buffer, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateBufferView
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateBufferView(device, pCreateInfo, pAllocator, pView));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyBufferView
//------------------------------------------------------------------------------
void VulkanReplay_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyBufferView(device, bufferView, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateImage
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // We populate every image via a transfer so this usage bit must
    // be set to avoid warnings.
    VkImageCreateInfo createInfo = *pCreateInfo;
    createInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

    // Patch up invalid queue families
    std::vector<uint32_t> vecQueueFamilies;
    if (s_SawQueueFamilyMismatch && pCreateInfo->sharingMode == VK_SHARING_MODE_CONCURRENT && pCreateInfo->queueFamilyIndexCount > 0)
    {

        // Allocate locate storage
        vecQueueFamilies.reserve(pCreateInfo->queueFamilyIndexCount);

        // Add re-mapped values
        VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];
        std::map<uint32_t, uint32_t>& queueFamilyMap = s_QueueFamilyMap[physicalDevice];
        for (uint32_t i = 0; i < pCreateInfo->queueFamilyIndexCount; i++)
        {
            uint32_t familyIndex = queueFamilyMap[pCreateInfo->pQueueFamilyIndices[i]];
            auto itr = std::find(vecQueueFamilies.begin(), vecQueueFamilies.end(), familyIndex);
            if (itr == vecQueueFamilies.end())
            {
                vecQueueFamilies.push_back(familyIndex);
            }
        }

        // Update create info
        createInfo.queueFamilyIndexCount = static_cast<uint32_t>(vecQueueFamilies.size());
        createInfo.pQueueFamilyIndices = vecQueueFamilies.data();
    }

    // Create image
    VkResult ret = NV_VK_VALIDATE(vkCreateImage(device, &createInfo, pAllocator, pImage));
    if (ret != VK_SUCCESS)
    {
        return ret;
    }

    // Store create info & image formats
    s_ImageCreateInfo[*pImage] = createInfo;
    s_ImageFormat[*pImage] = createInfo.format;
    return ret;
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyImage
//------------------------------------------------------------------------------
void VulkanReplay_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyImage(device, image, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetImageSubresourceLayout
//------------------------------------------------------------------------------
void VulkanReplay_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
    vkGetImageSubresourceLayout(device, image, pSubresource, pLayout);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateImageView
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    const VkResult result = vkCreateImageView(device, pCreateInfo, pAllocator, pView);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    // See if this is an image with an override
    auto itrKey = s_ImageToOverrideKey.find(pCreateInfo->image);
    if (itrKey != s_ImageToOverrideKey.end())
    {

        // Get key associated with parent image
        const VkImage myImage = itrKey->first;
        const OverrideKey myKey = itrKey->second;

        // Install into LUT
        s_ImageViewToOverrideKey[*pView] = myKey;

        // This view
        s_OverrideKeyToObjectOverrideMap[myKey]->imageViews[*pView] = *pView;

        // Loop overrides, skipping the current
        for (const OverrideKey& otherKey : s_VecOverrideSet)
        {
            if (myKey == otherKey)
            {
                continue;
            }

            // Lookup image associated with the otherKey
            const VkImage otherImage = s_OverrideKeyToObjectOverrideMap[otherKey]->images[myImage];
            NV_ASSERT(otherImage != VK_NULL_HANDLE);

            // Create override image view
            VkImageView overrideView = VK_NULL_HANDLE;
            VkImageViewCreateInfo createInfo = *pCreateInfo;
            createInfo.image = otherImage;
            const VkResult ret = vkCreateImageView(device, &createInfo, pAllocator, &overrideView);
            NV_ASSERT(ret == VK_SUCCESS);

            // Install into set
            s_OverrideKeyToObjectOverrideMap[otherKey]->imageViews[*pView] = overrideView;
        }
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyImageView
//------------------------------------------------------------------------------
void VulkanReplay_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyImageView(device, imageView, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateShaderModule
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyShaderModule
//------------------------------------------------------------------------------
void VulkanReplay_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyShaderModule(device, shaderModule, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreatePipelineCache
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    if (s_SawPipelineCacheHeaderMismatch)
    {
        NV_MESSAGE_ONCE("The pipeline cache could be imcompatible in the replay environment due to pipeline cache header mismatch.");
    }

    return NV_VK_VALIDATE(vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyPipelineCache
//------------------------------------------------------------------------------
void VulkanReplay_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyPipelineCache(device, pipelineCache, pAllocator);
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetPipelineCacheData
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetPipelineCacheData(device, pipelineCache, pDataSize, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_MergePipelineCaches
//------------------------------------------------------------------------------
VkResult VulkanReplay_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches)
{
    return NV_VK_VALIDATE(vkMergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches));
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateGraphicsPipelines
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

#if defined(VK_EXT_pipeline_creation_cache_control)
    // Remove the flags that specifies that pipeline creation will fail if a compile is required
    // We currently don't serialize pipeline cache (not portable)
    if (pCreateInfos->flags & VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT)
    {
        const_cast<VkGraphicsPipelineCreateInfo*>(pCreateInfos)->flags &= (~VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT);
    }
#endif

    return NV_VK_VALIDATE(vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateComputePipelines
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

#if defined(VK_EXT_pipeline_creation_cache_control)
    // Remove the flags that specifies that pipeline creation will fail if a compile is required
    // We currently don't serialize pipeline cache (not portable)
    if (pCreateInfos->flags & VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT)
    {
        const_cast<VkComputePipelineCreateInfo*>(pCreateInfos)->flags &= (~VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT);
    }
#endif

    return NV_VK_VALIDATE(vkCreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyPipeline
//------------------------------------------------------------------------------
void VulkanReplay_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyPipeline(device, pipeline, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreatePipelineLayout
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyPipelineLayout
//------------------------------------------------------------------------------
void VulkanReplay_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateSampler
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateSampler(device, pCreateInfo, pAllocator, pSampler));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroySampler
//------------------------------------------------------------------------------
void VulkanReplay_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroySampler(device, sampler, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDescriptorSetLayout
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Cannot cache command buffers if descriptor sets allow updates after bind
    NV_THROW_IF(s_CacheCommandBuffer && (pCreateInfo->flags & VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT), "Cannot cache command buffers if descriptor sets allow updates after bind");

    // Real call
    const VkResult result = vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyDescriptorSetLayout
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDescriptorPool
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    const VkResult result = vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    // Remember pool creation information
    // NOTE: This is safe because pCreateInfo is lives in static memory
    s_DescriptorPoolCreateInfo[*pDescriptorPool] = pCreateInfo;

    // Create override pools
    for (uint32_t i = 1; i < s_BufferingSize; i++)
    {
        VkDescriptorPool overridePool;
        vkCreateDescriptorPool(device, pCreateInfo, pAllocator, &overridePool);
        s_DescriptorPoolOverrides[*pDescriptorPool].push_back(overridePool);
        s_DescriptorPoolCreateInfo[overridePool] = pCreateInfo;
    }

    return VK_SUCCESS;
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyDescriptorPool
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_ResetDescriptorPool
//------------------------------------------------------------------------------
VkResult VulkanReplay_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkResetDescriptorPool(device, descriptorPool, flags));
}

//------------------------------------------------------------------------------
// DoAllocateDescriptorSets
//------------------------------------------------------------------------------
static VkResult DoAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
    // Record the relationship between descriptorSet descriptorSetLayout & descriptorPool,
    // we will delay the override descriptorSet's creation till UpdateDescriptorSet(), since
    // we can't get the complete info of VkWriteDescriptorSet for the descriptorSet at this time.
    auto RecordDescriptorSetToLayout = [&](const VkDescriptorSetAllocateInfo& allocationInfo) {
        for (uint32_t i = 0; i < allocationInfo.descriptorSetCount; ++i)
        {
            s_DescriptorSetToInfoMap[pDescriptorSets[i]] = { allocationInfo.pSetLayouts[i], allocationInfo.descriptorPool };
        }
    };

    // It's possible this might fail due to pool fragmentation
    VkResult result = vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
    if (result == VK_SUCCESS)
    {
        RecordDescriptorSetToLayout(*pAllocateInfo);
        return result;
    }

    // Helper to create and register an overflow pool
    auto AllocateOverflowPool = [=]() -> VkDescriptorPool {
        NV_LOG("Creating overflow pool");
        VkDescriptorPool pool = VK_NULL_HANDLE;
        const VkDescriptorPoolCreateInfo* pCreateInfo = s_DescriptorPoolCreateInfo[pAllocateInfo->descriptorPool];
        NV_ASSERT(pCreateInfo);
        vkCreateDescriptorPool(device, pCreateInfo, nullptr, &pool);
        s_OverflowDescriptorPools[pAllocateInfo->descriptorPool].push_back(pool);
        return pool;
    };

    // Create (or get) an overflow pool that matches the original allocation pool
    VkDescriptorPool overflowPool = VK_NULL_HANDLE;
    if (s_OverflowDescriptorPools[pAllocateInfo->descriptorPool].empty())
    {
        overflowPool = AllocateOverflowPool();
    }
    else
    {
        overflowPool = s_OverflowDescriptorPools[pAllocateInfo->descriptorPool].back();
    }
    NV_ASSERT(overflowPool != VK_NULL_HANDLE);

    // Try again with current overflow pool
    VkDescriptorSetAllocateInfo allocateInfo = *pAllocateInfo;
    allocateInfo.descriptorPool = overflowPool;
    result = vkAllocateDescriptorSets(device, &allocateInfo, pDescriptorSets);
    if (result == VK_SUCCESS)
    {
        RecordDescriptorSetToLayout(allocateInfo);
        return VK_SUCCESS;
    }

    // Try once more with a fresh overflow pool. If this fails we are out-of-luck
    overflowPool = AllocateOverflowPool();
    allocateInfo.descriptorPool = overflowPool;
    result = vkAllocateDescriptorSets(device, &allocateInfo, pDescriptorSets);
    if (result == VK_SUCCESS)
    {
        RecordDescriptorSetToLayout(allocateInfo);
    }
    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_AllocateDescriptorSets
//------------------------------------------------------------------------------
VkResult VulkanReplay_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Allocate without overrides
    DoAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);

    // We shouldn't be in a current override
    NV_ASSERT(GetThreadState().activeOverride == s_DefaultOverride);

    // Loop sets
    for (uint32_t i = 0; i < pAllocateInfo->descriptorSetCount; i++)
    {

        // Install self as passthrough override for the default
        VkDescriptorSet set = pDescriptorSets[i];

        // Loop all possible overrides
        for (uint32_t j = 1; j < s_BufferingSize; j++)
        {

            // Get override pool
            VkDescriptorPool overridePool = GetActive_DescriptorPool(j, pAllocateInfo->descriptorPool);
            NV_ASSERT(overridePool != VK_NULL_HANDLE);

            // Setup allocation with override pool
            VkDescriptorSetAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };
            allocateInfo.pNext = pAllocateInfo->pNext;
            allocateInfo.descriptorPool = overridePool;
            allocateInfo.descriptorSetCount = 1;
            allocateInfo.pSetLayouts = pAllocateInfo->pSetLayouts + i;

            // Perform allocation
            VkDescriptorSet overrideSet = VK_NULL_HANDLE;
            DoAllocateDescriptorSets(device, &allocateInfo, &overrideSet);

            // Install override
            s_DescriptorSetOverrides[set].push_back(overrideSet);
        }
    }

    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_FreeDescriptorSets
//------------------------------------------------------------------------------
VkResult VulkanReplay_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets));
}

//------------------------------------------------------------------------------
// VulkanReplay_UpdateDescriptorSets
//------------------------------------------------------------------------------
void VulkanReplay_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
    // We only create the overrides for the first frame when when the cache is enabled
    if (s_CacheCommandBuffer && s_FrameIdx != 0)
    {
        return;
    }

    // Helper to generate a deep copy of the descriptor set parameters used to populate this descriptor
    // for a specific override scenario.
    auto GenerateUpdateDescriptorSetsParams = [&](uint32_t bufferingIndex, OverrideKey overrideKey) -> NV::VulkanTools::UpdateDescriptorSets_Params {
        // Deep copy
        NV::VulkanTools::UpdateDescriptorSets_Params copy(*s_HostAllocators[device], device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);

        // Patch up overrides for writes
        for (uint32_t writeIdx = 0; writeIdx < descriptorWriteCount; writeIdx++)
        {

            VkWriteDescriptorSet& write = copy.pDescriptorWrites[writeIdx];
            write.dstSet = GetActive_DescriptorSet(bufferingIndex, write.dstSet);
            GetDescriptorSetInfo(write.dstSet).valid = true;

            switch (write.descriptorType)
            {
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            {
                for (uint32_t descriptorIdx = 0; descriptorIdx < write.descriptorCount; descriptorIdx++)
                {
                    VkImageView imageView = GetActive_ImageView(overrideKey, write.pImageInfo[descriptorIdx].imageView);
                    const_cast<VkDescriptorImageInfo&>(write.pImageInfo[descriptorIdx]).imageView = imageView;
                }
            }
            break;
            default:
                break;
            }
        }

        // Patch up overrides for copies
        for (uint32_t copyIdx = 0; copyIdx < descriptorCopyCount; copyIdx++)
        {
            VkCopyDescriptorSet& copySet = copy.pDescriptorCopies[copyIdx];
            VkDescriptorSet set = GetActive_DescriptorSet(s_BufferingIdx, pDescriptorCopies[copyIdx].dstSet);
            GetDescriptorSetInfo(set).valid = true;
            copySet.dstSet = set;
        }

        return copy;
    };

    auto DoUpdateDescriptorSets = [&](uint32_t bufferIndex, OverrideKey key) {
        // Get cache key
        auto cacheKey = std::make_tuple(pDescriptorWrites, pDescriptorCopies, bufferIndex, key);
        using CacheKey = decltype(cacheKey);
        static std::map<CacheKey, NV::VulkanTools::UpdateDescriptorSets_Params> k_CachedDescriptorSetsParams;
        auto itr = k_CachedDescriptorSetsParams.find(cacheKey);
        if (itr == k_CachedDescriptorSetsParams.end())
        {
            NV::VulkanTools::UpdateDescriptorSets_Params params = GenerateUpdateDescriptorSetsParams(bufferIndex, key);
            itr = k_CachedDescriptorSetsParams.insert(std::make_pair(cacheKey, params)).first;
        }
        const NV::VulkanTools::UpdateDescriptorSets_Params& params = itr->second;

        // Multi-threaded descriptors are not guaranteed to work depending on the application so they are disabled by default
// #define NV_VK_MULTI_THREAD_DESCRIPTORS 1
#if NV_VK_MULTI_THREAD_DESCRIPTORS
        // Do the 1st frame without multi-threading to allow our static data structures to resize correctly
        const bool useThreads = g_threadPoolThreadCount > 0 && s_FrameIdx != 0;
#else
        const bool useThreads = false;
#endif
        if (useThreads)
        {
            s_DescriptorManager.EnqueueDescriptorUpdates(params);
        }
        else
        {
            vkUpdateDescriptorSets(
                params.device,
                params.descriptorWriteCount,
                params.pDescriptorWrites,
                params.descriptorCopyCount,
                params.pDescriptorCopies);
        }
    };

    // Record for current override
    const OverrideKey activeKey = GetThreadState().activeOverride;
    const bool isDefault = (activeKey == s_DefaultOverride);
    if (!isDefault)
    {
        DoUpdateDescriptorSets(s_BufferingIdx, activeKey);
    }

    // Initialize all versions of this descriptor if we are pre-frame (or pre-acquire)
    if (isDefault || s_CacheCommandBuffer || s_ReplayPhase != VulkanReplayPhase::Frame || s_FrameIdx == 0)
    {
        // Initialize all possible overrides using a different swapchain override
        // for any descriptor that is cached before the frame
        NV_ASSERT(s_BufferingSize == s_VecOverrideSet.size());
        for (uint32_t i = 0; i < s_BufferingSize; i++)
        {
            OverrideKey tempKey = s_VecOverrideSet[i];
            DoUpdateDescriptorSets(i, tempKey);
        }
    }
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateFramebuffer
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Call real
    VkResult result = vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    // No overrides possible for image less framebuffers
    if (pCreateInfo->flags & VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT)
    {
        return result;
    }

    // See if any of the attachments are overrides
    //
    // NOTE: If multiple attachments are associated with *different* overrides we
    // are in trouble
    auto itrKey = s_ImageViewToOverrideKey.begin();
    for (uint32_t i = 0; i < pCreateInfo->attachmentCount; i++)
    {
        const VkImageView imageView = pCreateInfo->pAttachments[i];
        itrKey = s_ImageViewToOverrideKey.find(imageView);
        if (itrKey != s_ImageViewToOverrideKey.end())
        {
            break;
        }
    }

    // Bail if we don't need to create an override
    if (itrKey == s_ImageViewToOverrideKey.end())
    {
        return result;
    }

    // Install self
    const OverrideKey myKey = itrKey->second;
    s_OverrideKeyToObjectOverrideMap[myKey]->framebuffers[*pFramebuffer] = *pFramebuffer;

    // Loop override set
    for (const OverrideKey& otherKey : s_VecOverrideSet)
    {
        if (myKey == otherKey)
        {
            continue;
        }

        // Duplicate framebuffer create info
        VkFramebuffer overrideFramebuffer = VK_NULL_HANDLE;
        VkFramebufferCreateInfo createInfo = *pCreateInfo;
        std::vector<VkImageView> vecAttachments(pCreateInfo->pAttachments, pCreateInfo->pAttachments + pCreateInfo->attachmentCount);
        createInfo.pAttachments = vecAttachments.data();

        // Lookup override for each view
        for (VkImageView& view : vecAttachments)
        {
            view = GetActive_ImageView(otherKey, view);
        }

        // Create override framebuffer
        VkResult ret = vkCreateFramebuffer(device, &createInfo, pAllocator, &overrideFramebuffer);
        NV_ASSERT(ret == VK_SUCCESS);
        (void)ret;

        // Install into set
        s_OverrideKeyToObjectOverrideMap[otherKey]->framebuffers[*pFramebuffer] = overrideFramebuffer;
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyFramebuffer
//------------------------------------------------------------------------------
void VulkanReplay_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyFramebuffer(device, framebuffer, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateRenderPass
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyRenderPass
//------------------------------------------------------------------------------
void VulkanReplay_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyRenderPass(device, renderPass, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetRenderAreaGranularity
//------------------------------------------------------------------------------
void VulkanReplay_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity)
{
    vkGetRenderAreaGranularity(device, renderPass, pGranularity);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateCommandPool
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool)
{
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // TODO: (DG-1338) This is a work around until we can fully support mid-frame
    // command buffer reset.
    VkCommandPoolCreateInfo createInfo = *pCreateInfo;
    createInfo.flags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    VkResult result = vkCreateCommandPool(device, &createInfo, pAllocator, pCommandPool);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    CommandPoolInfo info;
    info.createInfo = createInfo;
    info.real = *pCommandPool;
    s_CommandPoolInfo[*pCommandPool] = info;

    return result;
}

#endif // VK_VERSION_1_0

#if defined(VK_VERSION_1_0) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyCommandPool
//------------------------------------------------------------------------------
void VulkanReplay_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyCommandPool(device, commandPool, pAllocator);
}

#endif // VK_VERSION_1_0 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_ResetCommandPool
//------------------------------------------------------------------------------
VkResult VulkanReplay_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkResetCommandPool(device, commandPool, flags));
}

//------------------------------------------------------------------------------
// VulkanReplay_AllocateCommandBuffers
//------------------------------------------------------------------------------
VkResult VulkanReplay_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {

        // Since we do not re-allocate in frame we need to make sure this command
        // buffer is ready to be reused.
        for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++)
        {
            WaitForCommandBuffer(pCommandBuffers[i], "AllocateCommandBuffers");

            auto& recordDesc = GetCommandBufferRecordDesc(pCommandBuffers[i]);
            recordDesc.optionalFuture = {};
            recordDesc.valid = false;
        }

        return VK_SUCCESS;
    }

    // We shouldn't be in a current override
    NV_ASSERT(GetThreadState().activeOverride == s_DefaultOverride);

    VkCommandBufferAllocateInfo overrideAllocateInfo = *pAllocateInfo;
    overrideAllocateInfo.commandPool = CreateDedicateCommandPoolForCommandBuffer(device, overrideAllocateInfo.commandPool);

    const VkResult result = vkAllocateCommandBuffers(device, &overrideAllocateInfo, pCommandBuffers);
    if (result != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(result);
    }

    for (uint32_t i = 0; i < pAllocateInfo->commandBufferCount; i++)
    {

        const VkCommandBuffer commandBuffer = pCommandBuffers[i];

        // Store information about each command buffer
        s_CommandBufferToDeviceMap[commandBuffer] = device;
        s_CommandBufferToAllocateInfo[commandBuffer] = pAllocateInfo;
        s_CommandBufferToDedicatedPool[commandBuffer] = overrideAllocateInfo.commandPool;
        s_CommandBufferRecordDescs[commandBuffer] = CommandBufferRecordDesc{};

        // Allocate overrides
        for (uint32_t i = 1; i < s_BufferingSize; i++)
        {

            VkCommandBufferAllocateInfo overrideAllocateInfo = *pAllocateInfo;
            overrideAllocateInfo.commandPool = CreateDedicateCommandPoolForCommandBuffer(device, overrideAllocateInfo.commandPool);

            // Re-record with this override
            VkCommandBuffer overrideCommandBuffer;
            NV_VK_VALIDATE(vkAllocateCommandBuffers(device, &overrideAllocateInfo, &overrideCommandBuffer));

            // Store information about each command buffer override
            s_CommandBufferToDeviceMap[overrideCommandBuffer] = device;
            s_CommandBufferToAllocateInfo[overrideCommandBuffer] = pAllocateInfo;
            s_CommandBufferToDedicatedPool[overrideCommandBuffer] = overrideAllocateInfo.commandPool;
            s_CommandBufferRecordDescs[overrideCommandBuffer] = CommandBufferRecordDesc{};

            // Install override
            s_CommandBufferOverrides[commandBuffer].push_back(overrideCommandBuffer);
        }
    }

    return result;
}

//------------------------------------------------------------------------------
// VulkanReplay_FreeCommandBuffers
//------------------------------------------------------------------------------
void VulkanReplay_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}

//------------------------------------------------------------------------------
// VulkanReplay_BeginCommandBuffer
//------------------------------------------------------------------------------
VkResult VulkanReplay_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
    // Local mutable copy
    VkCommandBufferBeginInfo beginInfo = *pBeginInfo;

    // One-time submit command buffers might need special handling
    const bool isOneTimeSubmit = (beginInfo.flags & VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    if (isOneTimeSubmit)
    {

        if (s_CacheCommandBuffer)
        {

            // Remove ONE_TIME_SUBMIT_BIT flag since in cache command buffer mode
            // all command buffers are used on every frame.
            NV_MESSAGE_ONCE("NOTE: VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT ignored due to vk-cache-commandbuffers");
            beginInfo.flags &= ~VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        }
        else if (s_ReplayPhase != VulkanReplayPhase::Frame)
        {

            // If the command buffer was record prior to the frame we need to re-record to honor the
            // the VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT flag.
            NV_MESSAGE_ONCE("NOTE: Command buffers with VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT recorded prior to frame will be re-recorded at the start of each frame.");
            if (s_BufferingIdx == 0)
            {
                s_OneTimeSubmitCommandBuffersRecordedBeforeFrame[commandBuffer] = s_CurrentCommandBufferRecordInfo;
            }
        }
    }

    // Make sure this command buffer isn't in flight
    WaitForCommandBuffer(commandBuffer, "BeginCommandBuffer");

    // Secondary commandbuffers need metadata matching the primary
    VkCommandBufferInheritanceInfo inheritanceInfo;
    if (pBeginInfo->pInheritanceInfo)
    {
        auto& tls = GetThreadState();

        inheritanceInfo = *pBeginInfo->pInheritanceInfo;
        inheritanceInfo.framebuffer = GetActive_Framebuffer(tls.activeOverride, inheritanceInfo.framebuffer);

        beginInfo.pInheritanceInfo = &inheritanceInfo;
    }

    return NV_VK_VALIDATE(vkBeginCommandBuffer(commandBuffer, &beginInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_EndCommandBuffer
//------------------------------------------------------------------------------
VkResult VulkanReplay_EndCommandBuffer(VkCommandBuffer commandBuffer)
{
    return NV_VK_VALIDATE(vkEndCommandBuffer(commandBuffer));
}

//------------------------------------------------------------------------------
// VulkanReplay_ResetCommandBuffer
//------------------------------------------------------------------------------
VkResult VulkanReplay_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags)
{
    // Make sure this command buffer isn't in flight
    WaitForCommandBuffer(commandBuffer, "ResetCommandBuffer");

    auto& commandBufferRecord = GetCommandBufferRecordDesc(commandBuffer);
    commandBufferRecord.optionalFuture = {};
    commandBufferRecord.valid = false;

    return NV_VK_VALIDATE(vkResetCommandBuffer(commandBuffer, flags));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindPipeline
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
    auto& tls = GetThreadState();

    vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);

    // Store active pipeline
    tls.currentBoundPipeline[std::make_tuple(commandBuffer, pipelineBindPoint)] = pipeline;
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_attachment_feedback_loop_dynamic_state)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetAttachmentFeedbackLoopEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask)
{
    vkCmdSetAttachmentFeedbackLoopEnableEXT(commandBuffer, aspectMask);
}

#endif // VK_EXT_attachment_feedback_loop_dynamic_state

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewport
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports)
{
    vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetScissor
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors)
{
    vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLineWidth
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth)
{
    vkCmdSetLineWidth(commandBuffer, lineWidth);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBias
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor)
{
    vkCmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetBlendConstants
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4])
{
    vkCmdSetBlendConstants(commandBuffer, blendConstants);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBounds
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds)
{
    vkCmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilCompareMask
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask)
{
    vkCmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilWriteMask
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask)
{
    vkCmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilReference
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference)
{
    vkCmdSetStencilReference(commandBuffer, faceMask, reference);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindDescriptorSets
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
    // Local copy
    auto& tls = GetThreadState();
    auto& vecDescriptorSets = tls.vecDescriptorSets;

    if (descriptorSetCount > vecDescriptorSets.size())
    {
        vecDescriptorSets.resize(descriptorSetCount);
    }

    // Patch up overrides
    for (uint32_t i = 0; i < descriptorSetCount; i++)
    {
        // NULL handle becomes valid usage in the 1.3 spec
        if (!pDescriptorSets[i])
        {
            vecDescriptorSets[i] = VK_NULL_HANDLE;
            continue;
        }

        VkDescriptorSet set = GetActive_DescriptorSet(s_BufferingIdx, pDescriptorSets[i]);
        // Error check first full pass
        if (s_FrameIdx <= s_BufferingSize)
        {
            static bool s_once = false;
            if (!s_once && !GetDescriptorSetInfo(set).valid)
            {
                NV_LOG("WARNING: Binding descriptor set that was never updated");
                s_once = true;
            }
        }
        vecDescriptorSets[i] = set;
    }

    vkCmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, vecDescriptorSets.data(), dynamicOffsetCount, pDynamicOffsets);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindIndexBuffer
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
    vkCmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindVertexBuffers
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
    vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDraw
//------------------------------------------------------------------------------
void VulkanReplay_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
{
    vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndexed
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance)
{
    vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_multi_draw)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMultiEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride)
{
    vkCmdDrawMultiEXT(commandBuffer, drawCount, pVertexInfo, instanceCount, firstInstance, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMultiIndexedEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset)
{
    vkCmdDrawMultiIndexedEXT(commandBuffer, drawCount, pIndexInfo, instanceCount, firstInstance, stride, pVertexOffset);
}

#endif // VK_EXT_multi_draw

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndirect
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    vkCmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndexedIndirect
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    vkCmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDispatch
//------------------------------------------------------------------------------
void VulkanReplay_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    vkCmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDispatchIndirect
//------------------------------------------------------------------------------
void VulkanReplay_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
    vkCmdDispatchIndirect(commandBuffer, buffer, offset);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBuffer
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    srcImage = GetActive_Image(tls.activeOverride, srcImage);
    dstImage = GetActive_Image(tls.activeOverride, dstImage);
    vkCmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBlitImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    srcImage = GetActive_Image(tls.activeOverride, srcImage);
    dstImage = GetActive_Image(tls.activeOverride, dstImage);
    vkCmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBufferToImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    dstImage = GetActive_Image(tls.activeOverride, dstImage);
    vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImageToBuffer
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    srcImage = GetActive_Image(tls.activeOverride, srcImage);
    vkCmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}

#endif // VK_VERSION_1_0

#if defined(VK_NV_copy_memory_indirect)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMemoryIndirectNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride)
{
    vkCmdCopyMemoryIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMemoryToImageIndirectNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources)
{
    vkCmdCopyMemoryToImageIndirectNV(commandBuffer, copyBufferAddress, copyCount, stride, dstImage, dstImageLayout, pImageSubresources);
}

#endif // VK_NV_copy_memory_indirect

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CmdUpdateBuffer
//------------------------------------------------------------------------------
void VulkanReplay_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData)
{
    vkCmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdFillBuffer
//------------------------------------------------------------------------------
void VulkanReplay_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
    vkCmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdClearColorImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    image = GetActive_Image(tls.activeOverride, image);
    vkCmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdClearDepthStencilImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    image = GetActive_Image(tls.activeOverride, image);
    vkCmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdClearAttachments
//------------------------------------------------------------------------------
void VulkanReplay_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects)
{
    vkCmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdResolveImage
//------------------------------------------------------------------------------
void VulkanReplay_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    srcImage = GetActive_Image(tls.activeOverride, srcImage);
    dstImage = GetActive_Image(tls.activeOverride, dstImage);
    vkCmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetEvent
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    s_CommandBufferSetEvents[commandBuffer].insert(event);

    vkCmdSetEvent(commandBuffer, event, stageMask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdResetEvent
//------------------------------------------------------------------------------
void VulkanReplay_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
    s_CommandBufferResetEvents[commandBuffer].insert(event);

    vkCmdResetEvent(commandBuffer, event, stageMask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdWaitEvents
//------------------------------------------------------------------------------
void VulkanReplay_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    // Set global flag
    if (s_FrameIdx == 0)
    {
        s_SawWaitEvent = true;
    }

    for (uint32_t i = 0; i < eventCount; i++)
    {
        s_CommandBufferWaitEvents[commandBuffer].insert(pEvents[i]);
    }

    // Patch up overrides
    auto& tls = GetThreadState();
    std::vector<VkImageMemoryBarrier> vecImageMemoryBarrier(pImageMemoryBarriers, pImageMemoryBarriers + imageMemoryBarrierCount);
    for (VkImageMemoryBarrier& imageMemoryBarrier : vecImageMemoryBarrier)
    {
        imageMemoryBarrier.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier.image);
    }
    vkCmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdPipelineBarrier
//------------------------------------------------------------------------------
void VulkanReplay_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
    // Patch up overrides
    std::vector<VkImageMemoryBarrier> vecImageMemoryBarrier(pImageMemoryBarriers, pImageMemoryBarriers + imageMemoryBarrierCount);
    auto& tls = GetThreadState();
    for (VkImageMemoryBarrier& imageMemoryBarrier : vecImageMemoryBarrier)
    {
        imageMemoryBarrier.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier.image);
    }
    vkCmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, vecImageMemoryBarrier.data());
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginQuery
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
    // Skip if query not reset
    if (IsQueryAvailable(queryPool, query))
    {
        return;
    }

    if (!s_DisableCopyQueryPoolResults)
    {
        s_QueryPoolAvailableRanges[queryPool][query] = VK_TRUE;
    }
    vkCmdBeginQuery(commandBuffer, queryPool, query, flags);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndQuery
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
    vkCmdEndQuery(commandBuffer, queryPool, query);
}

#endif // VK_VERSION_1_0

#if defined(VK_EXT_conditional_rendering)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginConditionalRenderingEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin)
{
    vkCmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndConditionalRenderingEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer)
{
    vkCmdEndConditionalRenderingEXT(commandBuffer);
}

#endif // VK_EXT_conditional_rendering

#if defined(VK_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CmdResetQueryPool
//------------------------------------------------------------------------------
void VulkanReplay_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
    // If the range of the pool was not written it will probably be a hang (or fatal error)
    // on vkCmdResetQueryPool commands.
    if (!AllowCmdResetQueryPool(queryPool, firstQuery, queryCount))
    {
        return;
    }

    // Flag as reset
    if (!s_DisableCopyQueryPoolResults)
    {
        s_CommandBufferToQueryPoolReset[commandBuffer] = queryPool;
        std::fill_n(s_QueryPoolAvailableRanges[queryPool].begin() + firstQuery, queryCount, VK_FALSE);
    }

    return vkCmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteTimestamp
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
    // Skip if query not reset
    if (IsQueryAvailable(queryPool, query))
    {
        return;
    }

    if (!s_DisableCopyQueryPoolResults)
    {
        s_QueryPoolAvailableRanges[queryPool][query] = VK_TRUE;
    }
    vkCmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyQueryPoolResults
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
    // By default vkCmdCopyQueryPoolResults commands are ignored but we can
    // potentially allow them if the query pool was reset in frame. If the pool
    // never reset it will almost certainly be a hang (or fatal error) attempting
    // to copy the query results.
    if (!AllowCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount))
    {
        return;
    }

    vkCmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdPushConstants
//------------------------------------------------------------------------------
void VulkanReplay_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
    vkCmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginRenderPass
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
    // Patch up overrides
    VkRenderPassBeginInfo renderPassBegin = *pRenderPassBegin;
    pRenderPassBegin = &renderPassBegin;

    // Replace the framebuffer declared in the renderpass if needed
    auto& tls = GetThreadState();
    renderPassBegin.framebuffer = GetActive_Framebuffer(tls.activeOverride, renderPassBegin.framebuffer);

    // Replace the auxiliary imageviews declared in the renderpass if needed
    VkRenderPassAttachmentBeginInfo attachmentInfo;
    std::vector<VkImageView> overrideImageViews;
    auto pAttachmentInfo = reinterpret_cast<const VkRenderPassAttachmentBeginInfo*>(FindPNextStructure(pRenderPassBegin->pNext, VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO));
    if (pAttachmentInfo)
    {
        attachmentInfo = *pAttachmentInfo;
        ReplacePNextStructure((void**)&renderPassBegin.pNext, VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO, &attachmentInfo);

        overrideImageViews.assign(attachmentInfo.pAttachments, attachmentInfo.pAttachments + pAttachmentInfo->attachmentCount);
        attachmentInfo.pAttachments = overrideImageViews.data();

        for (VkImageView& imageView : overrideImageViews)
        {
            imageView = GetActive_ImageView(tls.activeOverride, imageView);
        }
    }

    vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdNextSubpass
//------------------------------------------------------------------------------
void VulkanReplay_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents)
{
    vkCmdNextSubpass(commandBuffer, contents);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndRenderPass
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndRenderPass(VkCommandBuffer commandBuffer)
{
    vkCmdEndRenderPass(commandBuffer);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdExecuteCommands
//------------------------------------------------------------------------------
void VulkanReplay_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
    std::vector<VkCommandBuffer> vecCommands(commandBufferCount);
    for (uint32_t i = 0; i < commandBufferCount; i++)
    {
        VkCommandBuffer secondaryCmdBuffer = pCommandBuffers[i];
        vecCommands[i] = GetActive_CommandBuffer(s_BufferingIdx, secondaryCmdBuffer);

        // Make sure this secondary command buffer is finished recording
        WaitForCommandBufferRecord(vecCommands[i]);
    }

    vkCmdExecuteCommands(commandBuffer, commandBufferCount, vecCommands.data());
}

#endif // VK_VERSION_1_0

#if defined(VK_KHR_android_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateAndroidSurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface));
}

#endif // VK_KHR_android_surface

#if defined(VK_KHR_display)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceDisplayPropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetPhysicalDeviceDisplayPropertiesKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceDisplayPlanePropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetPhysicalDeviceDisplayPlanePropertiesKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDisplayPlaneSupportedDisplaysKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetDisplayPlaneSupportedDisplaysKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDisplayModePropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetDisplayModePropertiesKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDisplayModeKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCreateDisplayModeKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDisplayPlaneCapabilitiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[physicalDevice], VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetDisplayPlaneCapabilitiesKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDisplayPlaneSurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(instance, VK_KHR_DISPLAY_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCreateDisplayPlaneSurfaceKHR as VK_KHR_display is unavailable");
        return VK_SUCCESS;
    }

    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface));
}

#endif // VK_KHR_display

#if defined(VK_KHR_display_swapchain)
//------------------------------------------------------------------------------
// VulkanReplay_CreateSharedSwapchainsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains));
}

#endif // VK_KHR_display_swapchain

#if defined(VK_KHR_surface)
//------------------------------------------------------------------------------
// VulkanReplay_DestroySurfaceKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroySurfaceKHR(instance, surface, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceSupportKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceCapabilitiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceFormatsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfacePresentModesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes));
}

#endif // VK_KHR_surface

#if defined(VK_KHR_swapchain)
//------------------------------------------------------------------------------
// ApplyDummyFullscreenSwapchain (helper)
//------------------------------------------------------------------------------
static void ApplyDummyFullscreenSwapchain(VkDevice device, VkSwapchainCreateInfoKHR* pCreateInfo)
{
    // Bail if not supported
#if !defined(NV_DUMMY_FULL_SCREEN)
    NV_MESSAGE("WARNING: Unable to setup dummy-fullscreen, unsupported surface");
    return;
#else

    VkSwapchainCreateInfoKHR& createInfo = *pCreateInfo;

    // Get screen size
    int screenWidth = 0;
    int screenHeight = 0;
    WindowSystemInstance().GetScreenSize(screenWidth, screenHeight);

    // Windows need addtional set-pos, the window may not created from the WindowSystem so
    // we need to resize it.
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    HWND hwnd = s_Win32SurfaceCreateInfoMap[createInfo.surface].hwnd;
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, screenWidth, screenHeight, SWP_FRAMECHANGED);
#endif

    // The screen extent shouldn't exceed the surface or don't apply fullscreen
    VkSurfaceCapabilitiesKHR surfCaps = {};
    NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(s_DeviceToPhysicalDeviceMap[device], createInfo.surface, &surfCaps));
    if (surfCaps.currentExtent.width != ~0u)
    {
        auto screenExtent = std::make_tuple(uint32_t(screenWidth), uint32_t(screenHeight));
        auto minSurfaceExtent = std::make_tuple(surfCaps.minImageExtent.width, surfCaps.minImageExtent.height);
        auto maxSurfaceExtent = std::make_tuple(surfCaps.maxImageExtent.width, surfCaps.maxImageExtent.height);
        if (screenExtent < minSurfaceExtent || screenExtent > maxSurfaceExtent)
        {
            return;
        }
    }

    // Override the dummy swapchain extent
    createInfo.imageExtent.width = screenWidth;
    createInfo.imageExtent.height = screenHeight;
#endif
}

//------------------------------------------------------------------------------
// GetDummySwapchainImages (helper)
//------------------------------------------------------------------------------
static void GetDummySwapchainImages(VkDevice device, SwapChainInfo& swapChainInfo, uint32_t* pSwapchainImageCount, std::vector<VkImage>& swapchainImages)
{
    // Allocate original swapchain sized dummy images for vkGetSwapchainImagesKHR
    const VkSwapchainCreateInfoKHR& createInfo = swapChainInfo.createInfo;
    const VkSwapchainCreateInfoKHR& originalCreateInfo = swapChainInfo.originalCreateInfo;
    unsigned dummyImageCount = createInfo.minImageCount;
    swapChainInfo.images.resize(dummyImageCount);
    swapChainInfo.dummyImageMemories.resize(dummyImageCount);

    VkImageCreateInfo imageCreateInfo = {};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.pNext = NULL;
    imageCreateInfo.flags = 0;
    imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    imageCreateInfo.format = createInfo.imageFormat;
    imageCreateInfo.extent.width = originalCreateInfo.imageExtent.width; // Use the original extent
    imageCreateInfo.extent.height = originalCreateInfo.imageExtent.height;
    imageCreateInfo.extent.depth = 1;
    imageCreateInfo.mipLevels = 1;
    imageCreateInfo.arrayLayers = createInfo.imageArrayLayers;
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageCreateInfo.usage = createInfo.imageUsage;
    imageCreateInfo.sharingMode = createInfo.imageSharingMode;
    imageCreateInfo.queueFamilyIndexCount = createInfo.queueFamilyIndexCount;
    imageCreateInfo.pQueueFamilyIndices = createInfo.pQueueFamilyIndices;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];
    const VkPhysicalDeviceMemoryProperties& phyMemoryProperties = s_MemoryProperties[physicalDevice];
    for (unsigned i = 0; i < dummyImageCount; i++)
    {
        VkImage dummyImage = VK_NULL_HANDLE;
        NV_VK_VALIDATE(vkCreateImage(device, &imageCreateInfo, swapChainInfo.pAllocator, &dummyImage));

        VkMemoryRequirements memReq = {};
        vkGetImageMemoryRequirements(device, dummyImage, &memReq);

        VkMemoryAllocateInfo memAlloc = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        memAlloc.allocationSize = memReq.size;
        auto memIndices = std::move(FindMemoryIndices(phyMemoryProperties, memReq.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT));
        NV_ASSERT(!memIndices.empty());
        memAlloc.memoryTypeIndex = memIndices[0];
        VkDeviceMemory dummyImageMemory = VK_NULL_HANDLE;
        NV_VK_VALIDATE(vkAllocateMemory(device, &memAlloc, swapChainInfo.pAllocator, &dummyImageMemory));
        NV_VK_VALIDATE(vkBindImageMemory(device, dummyImage, dummyImageMemory, 0));

        swapChainInfo.images[i] = dummyImage;
        swapChainInfo.dummyImageMemories[i] = dummyImageMemory;
    }

    *pSwapchainImageCount = dummyImageCount;
    swapchainImages = swapChainInfo.images;
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateSwapchainKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Create real
    VkSwapchainCreateInfoKHR createInfo = *pCreateInfo;

    // Allow for direct population of swapchian images
    if (s_MinimizeValidationWarnings)
    {
        createInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    }

    // Remove FSE extensions if using -wb
    if (Application::HasForceBorderlessWindow())
    {
#if defined(VK_EXT_full_screen_exclusive)
        RemovePNextStructure(&createInfo, VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_INFO_EXT);
        RemovePNextStructure(&createInfo, VK_STRUCTURE_TYPE_SURFACE_FULL_SCREEN_EXCLUSIVE_WIN32_INFO_EXT);
#endif
    }

    // Force present mode
    if (s_ForcePresentMode > -1)
    {
        createInfo.presentMode = static_cast<VkPresentModeKHR>(s_ForcePresentMode);
    }

    // Physical device
    const VkPhysicalDevice physicalDevice = s_DeviceToPhysicalDeviceMap[device];

    // Surface/queue support
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
    for (uint32_t queueFamilyIdx = 0; queueFamilyIdx < queueFamilyCount; queueFamilyIdx++)
    {
        VkBool32 supported = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIdx, createInfo.surface, &supported);
    }

#if NV_USE_MANAGED_WINSYS

    // Query supported surface formats
    uint32_t surfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, createInfo.surface, &surfaceFormatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> vecSurfaceFormats(surfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, createInfo.surface, &surfaceFormatCount, vecSurfaceFormats.data());

    // Check if the original format used in capture is supported in replay
    bool origFormatSupported = false;
    for (const auto& surfaceFormat : vecSurfaceFormats)
    {
        if ((createInfo.imageFormat == surfaceFormat.format) && (createInfo.imageColorSpace == surfaceFormat.colorSpace))
        {
            origFormatSupported = true;
            break;
        }
    }

    // Try to find a compatible format if needed
    if (!origFormatSupported)
    {

        // Uncompressed color formats are compatible with each other if they occupy the same number of bits per texel block.
        // Compressed color formats are compatible with each other if the only difference between them is the numerical type of the uncompressed pixels.
        // Each depth / stencil format is only compatible with itself.

        VkFormat overrideFormat = VK_FORMAT_UNDEFINED;
        VkColorSpaceKHR overrideSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        const uint32_t origFormatSize = GetTexelSizeInBitsForUncompressedColorFormat(createInfo.imageFormat);

        // Only try to find a compatible format if the original format is an uncompressed color format.
        if (origFormatSize != 0)
        {
            for (const auto& surfaceFormat : vecSurfaceFormats)
            {
                const uint32_t formatSize = GetTexelSizeInBitsForUncompressedColorFormat(surfaceFormat.format);
                if (formatSize == origFormatSize)
                {
                    overrideFormat = surfaceFormat.format;
                    overrideSpace = surfaceFormat.colorSpace;
                    break;
                }
            }
        }

        if (overrideFormat != VK_FORMAT_UNDEFINED)
        {

            // Log message
            NV_MESSAGE("WARNING: Surface format mismatch, the rendering in replay may differ from the rendering in capture");
            NV_MESSAGE(" > Capture: format %u, color space %u", uint32_t(createInfo.imageFormat), uint32_t(createInfo.imageColorSpace));
            NV_MESSAGE(" > Replay:  format %u, color space %u", uint32_t(overrideFormat), uint32_t(overrideSpace));

            // Override
            createInfo.imageFormat = overrideFormat;
            createInfo.imageColorSpace = overrideSpace;
        }
        else
        {
            NV_MESSAGE("ERROR: Failed to find a compatible surface format");
        }
    }

    // Query supported present modes
    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, createInfo.surface, &presentModeCount, nullptr);
    std::vector<VkPresentModeKHR> vecPresentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, createInfo.surface, &presentModeCount, vecPresentModes.data());

    // Make sure to use a valid present mode
    bool origPresentModeSupported = false;
    for (const VkPresentModeKHR presentMode : vecPresentModes)
    {
        if (createInfo.presentMode == presentMode)
        {
            origPresentModeSupported = true;
            break;
        }
    }
    if (!origPresentModeSupported)
    {

        // Simply use the first supported present mode instead
        const VkPresentModeKHR overridePresentMode = vecPresentModes[0];

        // Log message
        NV_MESSAGE("NOTE: Surface present mode mismatch");
        NV_MESSAGE(" > Capture: %u", uint32_t(createInfo.presentMode));
        NV_MESSAGE(" > Replay:  %u", uint32_t(overridePresentMode));

        // Override
        createInfo.presentMode = overridePresentMode;
    }

#endif // NV_USE_MANAGED_WINSYS

#if defined(NV_DUMMY_FULL_SCREEN)
    // Apply dummy fullscreen if required
    if (s_DummyFullscreen)
    {
        ApplyDummyFullscreenSwapchain(device, &createInfo);
    }
#endif

    // Validate swapchain supports this surface
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(s_DeviceToPhysicalDeviceMap[device], createInfo.surface, &surfaceCapabilities);
    if (createInfo.imageExtent.width > surfaceCapabilities.maxImageExtent.width || createInfo.imageExtent.height > surfaceCapabilities.maxImageExtent.height)
    {
        NV_MESSAGE("FATAL: Replay surface max extent is smaller than requested capture swapchain extent. "
                   "This can be avoided by either increasing the resolution of your desktop "
                   "or forcing borderless window mode via the -wb option.\n"
                   " > Max Surface Extent: %u x %u\n"
                   " > Swapchain Extent: %u x %u\n",
            surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height,
            createInfo.imageExtent.width, createInfo.imageExtent.height);

        throw std::runtime_error("invalid surface");
    }

    VkResult ret = vkCreateSwapchainKHR(device, &createInfo, pAllocator, pSwapchain);

    // Bail if error
    if (ret != VK_SUCCESS)
    {
        return NV_VK_VALIDATE(ret);
    }

    SwapChainInfo& swapchainInfo = s_SwapChainInfoMap[*pSwapchain];
    swapchainInfo.device = device;
    swapchainInfo.upToDateSwapchain = *pSwapchain;
    swapchainInfo.pAllocator = pAllocator;
    swapchainInfo.createInfo = createInfo;
    swapchainInfo.originalCreateInfo = *pCreateInfo;
    swapchainInfo.images.clear();
    std::queue<uint32_t> tmpQueue;
    swapchainInfo.acquiredImages.swap(tmpQueue);
    swapchainInfo.dummyImageMemories.clear();

    // Query images
    uint32_t count = 0;
    std::vector<VkImage> vecSwapchainImages;
#if defined(NV_DUMMY_FULL_SCREEN)
    if (s_DummyFullscreen)
    {
        GetDummySwapchainImages(device, swapchainInfo, &count, vecSwapchainImages);
    }
    else
#endif
    {
        vkGetSwapchainImagesKHR(device, *pSwapchain, &count, nullptr);
        vecSwapchainImages.resize(count);
        vkGetSwapchainImagesKHR(device, *pSwapchain, &count, vecSwapchainImages.data());
    }

    // Initialize the round-robin buffering size
    NV_ASSERT(s_BufferingSize == 0);
    s_BufferingSize = count;
    s_BufferingIdx = 0;

    // Update global LUT
    swapchainInfo.images = vecSwapchainImages;

    // Store image formats
    for (const VkImage& image : vecSwapchainImages)
    {
        s_ImageFormat[image] = pCreateInfo->imageFormat;
    }

    // Lookup instance
    const VkInstance instance = s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[device]];

    // Create override set where each {swapchain + idx} is a unique key
    std::vector<OverrideKey> vecOverrides(count);
    for (uint32_t i = 0; i < count; i++)
    {
        vecOverrides[i] = GetOverrideKey(*pSwapchain, i);
    }
    VulkanHelper_RegisterOverrideSet(instance, count, vecOverrides.data());

    // Create per-image overrides where we rotate through the swapchain images
    for (uint32_t i = 0; i < count; i++)
    {
        OverrideKey iKey = GetOverrideKey(*pSwapchain, i);
        VulkanHelper_AssociateImageWithOverrideKey(instance, vecSwapchainImages[i], iKey);
        for (uint32_t j = 0; j < count; j++)
        {
            OverrideKey jKey = GetOverrideKey(*pSwapchain, j);
            VulkanHelper_RegisterImageOverride(instance, jKey, vecSwapchainImages[i], vecSwapchainImages[j]);
        }
    }

    // TODO: (DG-11075) Add a new interface for this; there are some corner
    // cases we'll need this set correctly to reduce flickering.
    uint32_t initialImageIndex = 0;

    // Set initial override key
    auto& tls = GetThreadState();
    tls.activeOverride = GetOverrideKey(*pSwapchain, initialImageIndex);

    // Store to reset after present
    // NOTE: This doesn't support multiple swapchain presents in a single frame
    s_DefaultOverride = tls.activeOverride;

    return ret;
}

#endif // VK_KHR_swapchain

#if defined(VK_KHR_swapchain) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_DestroySwapchainKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    const SwapChainInfo& swapchainInfo = GetSwapchainInfo(swapchain);
    swapchain = swapchainInfo.upToDateSwapchain;

#if defined(NV_DUMMY_FULL_SCREEN)
    if (s_DummyFullscreen)
    {
        for (VkImage dummyImage : swapchainInfo.images)
        {
            vkDestroyImage(device, dummyImage, pAllocator);
        }
        for (VkDeviceMemory dummyMemory : swapchainInfo.dummyImageMemories)
        {
            vkFreeMemory(device, dummyMemory, pAllocator);
        }
    }
#endif

    vkDestroySwapchainKHR(device, swapchain, pAllocator);
}

#endif // VK_KHR_swapchain && !VKSC_VERSION_1_0

#if defined(VK_KHR_swapchain)
//------------------------------------------------------------------------------
// VulkanReplay_GetSwapchainImagesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
#if defined(NV_DUMMY_FULL_SCREEN)
    if (!s_DummyFullscreen)
    {
        return NV_VK_VALIDATE(vkGetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages));
    }
#endif

    const SwapChainInfo& swapchainInfo = GetSwapchainInfo(swapchain);
    if (!pSwapchainImages)
    {
        *pSwapchainImageCount = static_cast<uint32_t>(swapchainInfo.images.size());
        return VK_SUCCESS;
    }
    if (*pSwapchainImageCount < swapchainInfo.images.size())
    {
        std::copy_n(swapchainInfo.images.data(), *pSwapchainImageCount, pSwapchainImages);
        return VK_INCOMPLETE;
    }
    std::copy_n(swapchainInfo.images.data(), swapchainInfo.images.size(), pSwapchainImages);
    *pSwapchainImageCount = static_cast<uint32_t>(swapchainInfo.images.size());
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_AcquireNextImageKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
    // In complicated games. the swapchain-images could be acquired/presented in interleave orders:
    //      1. Acquire image N
    //      2. Present image N-1 (acquired in previous frames)
    //      3. Render to image N
    //      4. Acquire image N+1
    //      5. Present image N
    // Or acquire multiple times but present only once in the frame:
    //      1. Acquire image N-1
    //      2. Acquire image N
    //      3. Render to image N-1
    //      4. Present image N-1
    // It won't be correct if replaying them in original order. Since QueuePresent is the delimiter, as a short-term solution before we can better support
    // the complex cases, ensure every frame has unique AcquireNextImage.
    const SwapChainInfo& swapchainInfo = GetSwapchainInfo(swapchain);
    if (!swapchainInfo.acquiredImages.empty())
    {
        return VK_SUCCESS;
    }

    auto& tls = GetThreadState();

    // The swapchain may be recreated for reasons like OUT_OF_DATE so use the up-to-date one
    VkSwapchainKHR originalSwapchain = swapchain;
    swapchain = swapchainInfo.upToDateSwapchain;

    // Get double buffered versions of the semaphore and fences
    fence = GetActive_Fence(s_BufferingIdx, fence);

    // The semaphore must not have any uncompleted signal or wait operations pending
    if (semaphore != VK_NULL_HANDLE)
    {
        semaphore = GetActive_Sempahore(s_BufferingIdx, semaphore);
        SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(semaphore);
        if (semaphoreStatus.signaled)
        {
            // TODO: (DG-11075) Add paranoia mode to sync here
            semaphore = VK_NULL_HANDLE;
        }
        else
        {
            semaphoreStatus.signaled = true;
            semaphoreStatus.lastSignaledFrame = s_FrameIdx;
        }
    }

    // The fence must be unsignaled and must not be associated with any other queue
    // command that has not yet completed execution on that queue
    //
    // TODO: (DG-11075) Improve this
    WaitForPendingFence(device, fence, "AcquireNextImageKHR");

    // Try to acquire next image
    while (true)
    {
        const VkResult result = vkAcquireNextImageKHR(device, swapchain, timeout == 0 ? NV_DEFAULT_FENCE_WAIT_NS : timeout, s_IgnoreSemaphores ? VK_NULL_HANDLE : semaphore, fence, pImageIndex);
        if (result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR)
        {
            break;
        }

        // Try again
        if (result == VK_NOT_READY || result == VK_TIMEOUT)
        {
            continue;
        }

        // Something went wrong
        NV_THROW_IF(true, "Failed to acquire swapchain image");
    }

    // In flight fence
    if (fence != VK_NULL_HANDLE)
    {
        VULKAN_REPLAY_WRITE_LOCK();
        GetFenceStatus(fence).signaled = true;
    }

    // Record the new acquired image index.
    auto& acquiredImages = GetSwapchainInfo(originalSwapchain).acquiredImages;
    acquiredImages.push(*pImageIndex);

    // Set current override key based on swapchain and image index
    tls.activeOverride = GetOverrideKey(originalSwapchain, acquiredImages.front());

    // This must succeed
    return VK_SUCCESS;
}

//------------------------------------------------------------------------------
// VulkanReplay_QueuePresentKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
    auto& tls = GetThreadState();

    // Copy present info and override swapchain indices
    VkPresentInfoKHR presentInfo = *pPresentInfo;
    std::vector<uint32_t> vecImageIndices(pPresentInfo->swapchainCount);
    std::vector<VkSwapchainKHR> vecSwapchains(pPresentInfo->swapchainCount);
    for (size_t i = 0; i < vecImageIndices.size(); i++)
    {
        const VkSwapchainKHR swapchain = pPresentInfo->pSwapchains[i];
        vecSwapchains[i] = swapchain;
        auto itr = s_SwapChainInfoMap.find(swapchain);
        if (itr != s_SwapChainInfoMap.end() && !itr->second.acquiredImages.empty())
        {
            const SwapChainInfo& swapchainInfo = itr->second;
            const std::queue<uint32_t>& acquireQueue = swapchainInfo.acquiredImages;
            vecImageIndices[i] = acquireQueue.front();
            vecSwapchains[i] = swapchainInfo.upToDateSwapchain;
        }
        else
        {
            NV_LOG("Presenting on un-acquired swapchain");
            vecImageIndices[i] = pPresentInfo->pImageIndices[i];
        }
    }
    presentInfo.pImageIndices = vecImageIndices.data();
    presentInfo.pSwapchains = vecSwapchains.data();

    // Patch up semaphores and trigger a hard wait on all pending semaphores
    // if we are being asked to wait on a semaphore we don't know about. This
    // indicates a dependent multi-frame synchronization event.
    std::vector<VkSemaphore> vecWaitSemaphores;
    if (!s_IgnoreSemaphores)
    {
        for (uint32_t waitSemaphoreIdx = 0; waitSemaphoreIdx < pPresentInfo->waitSemaphoreCount; waitSemaphoreIdx++)
        {
            VkSemaphore waitSemaphore = pPresentInfo->pWaitSemaphores[waitSemaphoreIdx];
            waitSemaphore = GetActive_Sempahore(s_BufferingIdx, waitSemaphore);
            SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(waitSemaphore);
            if (!semaphoreStatus.signaled)
            {
                // TODO: (DG-11075) Add paranoia mode to sync here
            }
            else
            {
                vecWaitSemaphores.push_back(waitSemaphore);
                semaphoreStatus.signaled = false;
            }
        }
    }
    presentInfo.waitSemaphoreCount = static_cast<uint32_t>(vecWaitSemaphores.size());
    presentInfo.pWaitSemaphores = vecWaitSemaphores.data();

    // Increase frame counter
    IncreaseVulkanFrameCounters();

    // At this point the swapchain override is no longer active since it has been consumed
    // as part of the present. At this point, now image has been acquired -- however
    // there are a handful of applications that start recording to the next swapchain
    // image before it has been acquired because they assume round-robin. We can make
    // this assumption as well because it's probably better than going back to index
    // zero.
    tls.activeOverride = GetOverrideKey(pPresentInfo->pSwapchains[0], s_BufferingIdx);

    // Update the acquired images queue, and update the override when necessary.
    for (size_t i = 0; i < vecImageIndices.size(); i++)
    {
        const VkSwapchainKHR swapchain = pPresentInfo->pSwapchains[i];
        auto itr = s_SwapChainInfoMap.find(swapchain);
        if (itr != s_SwapChainInfoMap.end())
        {
            std::queue<uint32_t>& acquireQueue = itr->second.acquiredImages;
            acquireQueue.pop();
            if (!acquireQueue.empty())
            {
                tls.activeOverride = GetOverrideKey(swapchain, acquireQueue.front());
            }
        }
    }

    // Preset on overridden swapchain
    const VkResult result = vkQueuePresentKHR(queue, &presentInfo);

    // Collect events that were set in frame but never consumed. This indicates
    // some kind of cross-frame dependency we cannot observe in a single frame.
    for (VkEvent activeEvent : s_ActiveEvents)
    {
        s_RogueEvents.push_back(activeEvent);
    }

    // If using "sync at end of frame" option now is the time to sync
    if (s_SyncAtEndOfFrame && result == VK_SUCCESS)
    {
        for (VkDevice device : s_SetDevices)
        {

            std::vector<VkSemaphore> vecSemaphores;
            for (const auto& pair : s_SemaphoreStatus)
            {
                if (pair.second.signaled)
                {
                    VkSemaphore semaphore = pair.first;
                    vecSemaphores.push_back(semaphore);
                }
            }

            for (VkSemaphore semaphore : vecSemaphores)
            {
                ForceWaitForSignaledSemaphore(device, semaphore, "ResetEnd");
            }
            VULKAN_REPLAY_WRITE_LOCK();
            for (const auto& pair : s_FenceStatus)
            {
                WaitForPendingFence(device, pair.first, "ResetEnd");
            }
            FlushRogueEvents(device);
        }
    }

    // Recreate the swapchain if OUT_OF_DATE, this usually occurs on Linux fullscreen surface.
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        for (uint32_t i = 0; i < pPresentInfo->swapchainCount; i++)
        {
            const VkSwapchainKHR swapchain = pPresentInfo->pSwapchains[i];
            auto itr = s_SwapChainInfoMap.find(swapchain);
            if (itr != s_SwapChainInfoMap.end())
            {
                SwapChainInfo& swapchainInfo = itr->second;

                VkSwapchainCreateInfoKHR& createInfo = swapchainInfo.createInfo;
                createInfo.oldSwapchain = swapchainInfo.upToDateSwapchain;

                VkDevice device = swapchainInfo.device;
                const VkAllocationCallbacks* pAllocator = swapchainInfo.pAllocator;
                VkSwapchainKHR outSwapchain = VK_NULL_HANDLE;
                NV_VK_VALIDATE(vkCreateSwapchainKHR(device, &createInfo, pAllocator, &outSwapchain));
                swapchainInfo.upToDateSwapchain = outSwapchain;
            }
        }

        return result;
    }

    if (s_DumpFrame && s_NeedDumpFrame)
    {
        s_NeedDumpFrame = false; // only dump once
        for (size_t i = 0; i < vecImageIndices.size(); i++)
        {
            const VkSwapchainKHR swapchain = pPresentInfo->pSwapchains[i];
            vecSwapchains[i] = swapchain;
            auto itr = s_SwapChainInfoMap.find(swapchain);
            if (itr != s_SwapChainInfoMap.end())
            {
                const SwapChainInfo& swapchainInfo = itr->second;
                VkResult result = DumpFrame(uint32_t(i), vecImageIndices[i], queue, swapchainInfo);
                if (result != VK_SUCCESS)
                {
                    NV_LOG("ERROR: Cannot dump the frame in swapchain %d", i);
                }
            }
        }
    }

    return NV_VK_VALIDATE(result);
}

#endif // VK_KHR_swapchain

#if defined(VK_KHR_wayland_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateWaylandSurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return vkCreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceWaylandPresentationSupportKHR
//------------------------------------------------------------------------------
VkBool32 VulkanReplay_GetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display)
{
    return vkGetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display);
}

#endif // VK_KHR_wayland_surface

#if defined(VK_KHR_win32_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateWin32SurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Call real
    VkResult result = vkCreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);

    // Store LUT
    if (result == VK_SUCCESS)
    {
        s_Win32SurfaceCreateInfoMap[*pSurface] = *pCreateInfo;
    }

    // Query information to make the debug layer happy
    //
    // NOTE: Future implementations will validate this for compatibility
    for (VkPhysicalDevice physicalDevice : s_SetPhysicalDevices)
    {

        // Surface capabilities
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, *pSurface, &surfaceCapabilities);

        // Surface formats
        uint32_t surfaceFormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, *pSurface, &surfaceFormatCount, nullptr);
        std::vector<VkSurfaceFormatKHR> vecSurfaceFormats(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, *pSurface, &surfaceFormatCount, vecSurfaceFormats.data());

        // Surface Present Modes
        uint32_t presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, *pSurface, &presentModeCount, nullptr);
        std::vector<VkPresentModeKHR> vecPresentModes(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, *pSurface, &presentModeCount, vecPresentModes.data());
    }

    return NV_VK_VALIDATE(result);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceWin32PresentationSupportKHR
//------------------------------------------------------------------------------
VkBool32 VulkanReplay_GetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex)
{
    return vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
}

#endif // VK_KHR_win32_surface

#if defined(VK_KHR_xlib_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateXlibSurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    VkResult ret = vkCreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    if (ret == VK_SUCCESS)
    {
        s_XlibSurfaceCreateInfoMap[*pSurface] = *pCreateInfo;
    }

    return NV_VK_VALIDATE(ret);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceXlibPresentationSupportKHR
//------------------------------------------------------------------------------
VkBool32 VulkanReplay_GetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID)
{
    return vkGetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID);
}

#endif // VK_KHR_xlib_surface

#if defined(VK_KHR_xcb_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateXcbSurfaceKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    VkResult ret = vkCreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    if (ret == VK_SUCCESS)
    {
        s_XcbSurfaceCreateInfoMap[*pSurface] = *pCreateInfo;
    }

    return NV_VK_VALIDATE(ret);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceXcbPresentationSupportKHR
//------------------------------------------------------------------------------
VkBool32 VulkanReplay_GetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id)
{
    return vkGetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id);
}

#endif // VK_KHR_xcb_surface

#if defined(VK_EXT_debug_report)
//------------------------------------------------------------------------------
// VulkanReplay_CreateDebugReportCallbackEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyDebugReportCallbackEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDebugReportCallbackEXT(instance, callback, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_DebugReportMessageEXT
//------------------------------------------------------------------------------
void VulkanReplay_DebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage)
{
    vkDebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage);
}

#endif // VK_EXT_debug_report

#if defined(VK_EXT_debug_marker)
//------------------------------------------------------------------------------
// VulkanReplay_DebugMarkerSetObjectNameEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(device, VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkDebugMarkerSetObjectNameEXT as VK_EXT_debug_marker unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkDebugMarkerSetObjectNameEXT(device, pNameInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_DebugMarkerSetObjectTagEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(device, VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkDebugMarkerSetObjectTagEXT as VK_EXT_debug_marker unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkDebugMarkerSetObjectTagEXT(device, pTagInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDebugMarkerBeginEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(s_CommandBufferToDeviceMap[commandBuffer], VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdDebugMarkerBeginEXT as VK_EXT_debug_marker unavailable");
        return;
    }

    vkCmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDebugMarkerEndEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer)
{
    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(s_CommandBufferToDeviceMap[commandBuffer], VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdDebugMarkerEndEXT as VK_EXT_debug_marker unavailable");
        return;
    }

    vkCmdDebugMarkerEndEXT(commandBuffer);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDebugMarkerInsertEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(s_CommandBufferToDeviceMap[commandBuffer], VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdDebugMarkerInsertEXT as VK_EXT_debug_marker unavailable");
        return;
    }

    vkCmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo);
}

#endif // VK_EXT_debug_marker

#if defined(VK_NV_external_memory_capabilities)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalImageFormatPropertiesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties));
}

#endif // VK_NV_external_memory_capabilities

#if defined(VK_NV_external_memory_win32)
//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryWin32HandleNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle)
{
    return NV_VK_VALIDATE(vkGetMemoryWin32HandleNV(device, memory, handleType, pHandle));
}

#endif // VK_NV_external_memory_win32

#if defined(VK_NV_device_generated_commands)
//------------------------------------------------------------------------------
// VulkanReplay_CmdExecuteGeneratedCommandsNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo)
{
    vkCmdExecuteGeneratedCommandsNV(commandBuffer, isPreprocessed, pGeneratedCommandsInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdPreprocessGeneratedCommandsNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo)
{
    vkCmdPreprocessGeneratedCommandsNV(commandBuffer, pGeneratedCommandsInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindPipelineShaderGroupNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex)
{
    vkCmdBindPipelineShaderGroupNV(commandBuffer, pipelineBindPoint, pipeline, groupIndex);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetGeneratedCommandsMemoryRequirementsNV
//------------------------------------------------------------------------------
void VulkanReplay_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    vkGetGeneratedCommandsMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateIndirectCommandsLayoutNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateIndirectCommandsLayoutNV(device, pCreateInfo, pAllocator, pIndirectCommandsLayout));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyIndirectCommandsLayoutNV
//------------------------------------------------------------------------------
void VulkanReplay_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyIndirectCommandsLayoutNV(device, indirectCommandsLayout, pAllocator);
}

#endif // VK_NV_device_generated_commands

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFeatures2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures)
{
    vkGetPhysicalDeviceFeatures2(physicalDevice, pFeatures);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFeatures2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2KHR* pFeatures)
{
    vkGetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceProperties2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties)
{
    vkGetPhysicalDeviceProperties2(physicalDevice, pProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceProperties2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2KHR* pProperties)
{
    vkGetPhysicalDeviceProperties2KHR(physicalDevice, pProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFormatProperties2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties)
{
    vkGetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFormatProperties2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2KHR* pFormatProperties)
{
    vkGetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceImageFormatProperties2
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties));
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceImageFormatProperties2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2KHR* pImageFormatInfo, VkImageFormatProperties2KHR* pImageFormatProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties));
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties)
{
    vkGetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2KHR* pQueueFamilyProperties)
{
    vkGetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceMemoryProperties2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties)
{
    vkGetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceMemoryProperties2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2KHR* pMemoryProperties)
{
    vkGetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties)
{
    vkGetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_physical_device_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2KHR* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2KHR* pProperties)
{
    vkGetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties);
}

#endif // VK_KHR_get_physical_device_properties2

#if defined(VK_KHR_push_descriptor)
//------------------------------------------------------------------------------
// VulkanReplay_CmdPushDescriptorSetKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites)
{
    vkCmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites);
}

#endif // VK_KHR_push_descriptor

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_TrimCommandPool
//------------------------------------------------------------------------------
void VulkanReplay_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags)
{
    vkTrimCommandPool(device, commandPool, flags);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_maintenance1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_TrimCommandPoolKHR
//------------------------------------------------------------------------------
void VulkanReplay_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlagsKHR flags)
{
    vkTrimCommandPoolKHR(device, commandPool, flags);
}

#endif // VK_KHR_maintenance1 && !VKSC_VERSION_1_0

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalBufferProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties)
{
    vkGetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_memory_capabilities)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalBufferPropertiesKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfoKHR* pExternalBufferInfo, VkExternalBufferPropertiesKHR* pExternalBufferProperties)
{
    vkGetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties);
}

#endif // VK_KHR_external_memory_capabilities

#if defined(VK_KHR_external_memory_win32)
//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryWin32HandleKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    return NV_VK_VALIDATE(vkGetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryWin32HandlePropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties)
{
    return NV_VK_VALIDATE(vkGetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties));
}

#endif // VK_KHR_external_memory_win32

#if defined(VK_KHR_external_memory_fd)
//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryFdKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetMemoryFdKHR(device, pGetFdInfo, pFd));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryFdPropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties)
{
    return NV_VK_VALIDATE(vkGetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties));
}

#endif // VK_KHR_external_memory_fd

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalSemaphoreProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties)
{
    vkGetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_semaphore_capabilities)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalSemaphorePropertiesKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfoKHR* pExternalSemaphoreInfo, VkExternalSemaphorePropertiesKHR* pExternalSemaphoreProperties)
{
    vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}

#endif // VK_KHR_external_semaphore_capabilities

#if defined(VK_KHR_external_semaphore_win32)
//------------------------------------------------------------------------------
// VulkanReplay_GetSemaphoreWin32HandleKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    return NV_VK_VALIDATE(vkGetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle));
}

//------------------------------------------------------------------------------
// VulkanReplay_ImportSemaphoreWin32HandleKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo)
{
    return NV_VK_VALIDATE(vkImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo));
}

#endif // VK_KHR_external_semaphore_win32

#if defined(VK_KHR_external_semaphore_fd)
//------------------------------------------------------------------------------
// VulkanReplay_GetSemaphoreFdKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(device, VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkGetSemaphoreFdKHR as VK_KHR_external_semaphore_fd unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetSemaphoreFdKHR(device, pGetFdInfo, pFd));
}

//------------------------------------------------------------------------------
// VulkanReplay_ImportSemaphoreFdKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasDeviceExtension(device, VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkImportSemaphoreFdKHR as VK_KHR_external_semaphore_fd unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo));
}

#endif // VK_KHR_external_semaphore_fd

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalFenceProperties
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties)
{
    vkGetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_external_fence_capabilities)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalFencePropertiesKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfoKHR* pExternalFenceInfo, VkExternalFencePropertiesKHR* pExternalFenceProperties)
{
    vkGetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties);
}

#endif // VK_KHR_external_fence_capabilities

#if defined(VK_KHR_external_fence_win32)
//------------------------------------------------------------------------------
// VulkanReplay_GetFenceWin32HandleKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle)
{
    return NV_VK_VALIDATE(vkGetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle));
}

//------------------------------------------------------------------------------
// VulkanReplay_ImportFenceWin32HandleKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo)
{
    return NV_VK_VALIDATE(vkImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo));
}

#endif // VK_KHR_external_fence_win32

#if defined(VK_KHR_external_fence_fd)
//------------------------------------------------------------------------------
// VulkanReplay_GetFenceFdKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd)
{
    return NV_VK_VALIDATE(vkGetFenceFdKHR(device, pGetFdInfo, pFd));
}

//------------------------------------------------------------------------------
// VulkanReplay_ImportFenceFdKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo)
{
    return NV_VK_VALIDATE(vkImportFenceFdKHR(device, pImportFenceFdInfo));
}

#endif // VK_KHR_external_fence_fd

#if defined(VK_EXT_direct_mode_display)
//------------------------------------------------------------------------------
// VulkanReplay_ReleaseDisplayEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display)
{
    return NV_VK_VALIDATE(vkReleaseDisplayEXT(physicalDevice, display));
}

#endif // VK_EXT_direct_mode_display

#if defined(VK_EXT_acquire_xlib_display)
//------------------------------------------------------------------------------
// VulkanReplay_AcquireXlibDisplayEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display)
{
    return NV_VK_VALIDATE(vkAcquireXlibDisplayEXT(physicalDevice, dpy, display));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetRandROutputDisplayEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay)
{
    return NV_VK_VALIDATE(vkGetRandROutputDisplayEXT(physicalDevice, dpy, rrOutput, pDisplay));
}

#endif // VK_EXT_acquire_xlib_display

#if defined(VK_EXT_display_surface_counter)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2EXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities));
}

#endif // VK_EXT_display_surface_counter

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_EnumeratePhysicalDeviceGroups
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties)
{
    return NV_VK_VALIDATE(vkEnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties));
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group_creation)
//------------------------------------------------------------------------------
// VulkanReplay_EnumeratePhysicalDeviceGroupsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_EnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupPropertiesKHR* pPhysicalDeviceGroupProperties)
{
    return NV_VK_VALIDATE(vkEnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties));
}

#endif // VK_KHR_device_group_creation

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceGroupPeerMemoryFeatures
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures)
{
    vkGetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceGroupPeerMemoryFeaturesKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlagsKHR* pPeerMemoryFeatures)
{
    vkGetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}

#endif // VK_KHR_device_group

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_BindBufferMemory2
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // If explicit memory management this image was never created
    std::vector<VkBindBufferMemoryInfo> vecBindInfos(pBindInfos, pBindInfos + bindInfoCount);
    std::vector<uint32_t> vecMemoryTypeIndex(bindInfoCount);
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        VkBindBufferMemoryInfo& info = vecBindInfos[i];
        vecMemoryTypeIndex[i] = PatchBufferMemory(device, info.buffer, info.memory, info.memoryOffset);
    }

    // Real call
    VkResult result = NV_VK_VALIDATE(vkBindBufferMemory2(device, bindInfoCount, vecBindInfos.data()));

    // Store results
    if (result == VK_SUCCESS)
    {
        for (uint32_t i = 0; i < bindInfoCount; i++)
        {
            VkBindBufferMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO };
            info.buffer = vecBindInfos[i].buffer;
            info.memory = vecBindInfos[i].memory;
            info.memoryOffset = vecBindInfos[i].memoryOffset;
            s_BufferBindInfo[info.buffer] = BindBufferMemoryInfo{ vecMemoryTypeIndex[i], info };
        }
    }
    return result;
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
//------------------------------------------------------------------------------
// VulkanReplay_BindBufferMemory2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfoKHR* pBindInfos)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // If explicit memory management this image was never created
    std::vector<VkBindBufferMemoryInfo> vecBindInfos(pBindInfos, pBindInfos + bindInfoCount);
    std::vector<uint32_t> vecMemoryTypeIndex(bindInfoCount);
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        VkBindBufferMemoryInfo& info = vecBindInfos[i];
        vecMemoryTypeIndex[i] = PatchBufferMemory(device, info.buffer, info.memory, info.memoryOffset);
    }

    // Real call
    VkResult result = NV_VK_VALIDATE(vkBindBufferMemory2KHR(device, bindInfoCount, vecBindInfos.data()));

    // Store results
    if (result == VK_SUCCESS)
    {
        for (uint32_t i = 0; i < bindInfoCount; i++)
        {
            VkBindBufferMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO };
            info.buffer = vecBindInfos[i].buffer;
            info.memory = vecBindInfos[i].memory;
            info.memoryOffset = vecBindInfos[i].memoryOffset;
            s_BufferBindInfo[info.buffer] = BindBufferMemoryInfo{ vecMemoryTypeIndex[i], info };
        }
    }
    return result;
}

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_BindImageMemory2
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // If explicit memory management this image was never created
    std::vector<VkBindImageMemoryInfo> vecBindInfos(pBindInfos, pBindInfos + bindInfoCount);
    std::vector<uint32_t> vecMemoryTypeIndex(bindInfoCount);
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        VkBindImageMemoryInfo& info = vecBindInfos[i];
        vecMemoryTypeIndex[i] = PatchImageMemory(device, info.image, info.memory, info.memoryOffset);
    }

    // Real call
    VkResult result = NV_VK_VALIDATE(vkBindImageMemory2(device, bindInfoCount, vecBindInfos.data()));

    // Store results
    if (result == VK_SUCCESS)
    {
        for (uint32_t i = 0; i < bindInfoCount; i++)
        {
            VkBindImageMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO };
            info.image = vecBindInfos[i].image;
            info.memory = vecBindInfos[i].memory;
            info.memoryOffset = vecBindInfos[i].memoryOffset;
            s_ImageBindInfo[info.image] = BindImageMemoryInfo{ vecMemoryTypeIndex[i], info };
        }
    }
    return result;
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_bind_memory2)
//------------------------------------------------------------------------------
// VulkanReplay_BindImageMemory2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfoKHR* pBindInfos)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // If explicit memory management this image was never created
    std::vector<VkBindImageMemoryInfo> vecBindInfos(pBindInfos, pBindInfos + bindInfoCount);
    std::vector<uint32_t> vecMemoryTypeIndex(bindInfoCount);
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        VkBindImageMemoryInfo& info = vecBindInfos[i];
        vecMemoryTypeIndex[i] = PatchImageMemory(device, info.image, info.memory, info.memoryOffset);
    }

    // Real call
    VkResult result = NV_VK_VALIDATE(vkBindImageMemory2KHR(device, bindInfoCount, vecBindInfos.data()));

    // Store results
    if (result == VK_SUCCESS)
    {
        for (uint32_t i = 0; i < bindInfoCount; i++)
        {
            VkBindImageMemoryInfo info = { VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO };
            info.image = vecBindInfos[i].image;
            info.memory = vecBindInfos[i].memory;
            info.memoryOffset = vecBindInfos[i].memoryOffset;
            s_ImageBindInfo[info.image] = BindImageMemoryInfo{ vecMemoryTypeIndex[i], info };
        }
    }
    return result;
}

#endif // VK_KHR_bind_memory2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDeviceMask
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask)
{
    vkCmdSetDeviceMask(commandBuffer, deviceMask);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDeviceMaskKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask)
{
    vkCmdSetDeviceMaskKHR(commandBuffer, deviceMask);
}

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceGroupPresentCapabilitiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities)
{
    return NV_VK_VALIDATE(vkGetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceGroupSurfacePresentModesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes)
{
    return NV_VK_VALIDATE(vkGetDeviceGroupSurfacePresentModesKHR(device, surface, pModes));
}

//------------------------------------------------------------------------------
// VulkanReplay_AcquireNextImage2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex)
{
    // In complicated games. the swapchain-images could be acquired/presented in interleave orders:
    //      1. Acquire image N
    //      2. Present image N-1 (acquired in previous frames)
    //      3. Render to image N
    //      4. Acquire image N+1
    //      5. Present image N
    // Or acquire multiple times but present only once in the frame:
    //      1. Acquire image N-1
    //      2. Acquire image N
    //      3. Render to image N-1
    //      4. Present image N-1
    // It won't be correct if replaying them in original order. Since QueuePresent is the delimiter, as a short-term solution before we can better support
    // the complex cases, ensure every frame has unique AcquireNextImage.
    SwapChainInfo& swapchainInfo = GetSwapchainInfo(pAcquireInfo->swapchain);
    if (!swapchainInfo.acquiredImages.empty())
    {
        return VK_SUCCESS;
    }

    auto& tls = GetThreadState();

    // Local copy
    VkAcquireNextImageInfoKHR acquireInfo = *pAcquireInfo;

    // The swapchain may be recreated for reasons like OUT_OF_DATE so use the up-to-date one
    VkSwapchainKHR originalSwapchain = acquireInfo.swapchain;
    acquireInfo.swapchain = swapchainInfo.upToDateSwapchain;

    // Get multi-buffering overrides
    acquireInfo.semaphore = GetActive_Sempahore(s_BufferingIdx, pAcquireInfo->semaphore);
    acquireInfo.fence = GetActive_Fence(s_BufferingIdx, pAcquireInfo->fence);

    // The semaphore must not have any uncompleted signal or wait operations pending
    ForceWaitForSignaledSemaphore(device, acquireInfo.semaphore, "AcquireNextImage2KHR");

    // The fence must be unsignaled and must not be associated with any other queue
    // command that has not yet completed execution on that queue
    WaitForPendingFence(device, acquireInfo.fence, "AcquireNextImage2KHR");

    // Try to acquire next image
    while (true)
    {

        if (acquireInfo.timeout == 0)
        {
            acquireInfo.timeout = NV_DEFAULT_FENCE_WAIT_NS;
        }

        if (s_IgnoreSemaphores)
        {
            acquireInfo.semaphore = VK_NULL_HANDLE;
        }

        const VkResult result = vkAcquireNextImage2KHR(device, &acquireInfo, pImageIndex);

        if (result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR)
        {
            break;
        }

        // Try again
        if (result == VK_NOT_READY || result == VK_TIMEOUT)
        {
            continue;
        }

        // Something went wrong
        NV_THROW_IF(true, "Failed to acquire swapchain image");
    }

    // Add to list of signaled semaphores
    if (pAcquireInfo->semaphore != VK_NULL_HANDLE)
    {
        SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(acquireInfo.semaphore);
        semaphoreStatus.signaled = true;
        semaphoreStatus.lastSignaledFrame = s_FrameIdx;
    }

    // In flight fence
    if (acquireInfo.fence != VK_NULL_HANDLE)
    {
        GetFenceStatus(acquireInfo.fence).signaled = true;
    }

    // Record the new acquired image index.
    auto& acquiredImages = swapchainInfo.acquiredImages;
    acquiredImages.push(*pImageIndex);

    // Set current override key based on swapchain and image index
    tls.activeOverride = GetOverrideKey(originalSwapchain, acquiredImages.front());

    // This must succeed
    return VK_SUCCESS;
}

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDispatchBase
//------------------------------------------------------------------------------
void VulkanReplay_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    vkCmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_device_group)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDispatchBaseKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    vkCmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}

#endif // VK_KHR_device_group

#if defined(VK_KHR_swapchain) || defined(VK_KHR_device_group)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDevicePresentRectanglesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects)
{
    return NV_VK_VALIDATE(vkGetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects));
}

#endif // VK_KHR_swapchain || VK_KHR_device_group

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_CreateDescriptorUpdateTemplate
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate));
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
//------------------------------------------------------------------------------
// VulkanReplay_CreateDescriptorUpdateTemplateKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplateKHR* pDescriptorUpdateTemplate)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate));
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyDescriptorUpdateTemplate
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyDescriptorUpdateTemplateKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator);
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_UpdateDescriptorSetWithTemplate
//------------------------------------------------------------------------------
void VulkanReplay_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData)
{
    vkUpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_descriptor_update_template)
//------------------------------------------------------------------------------
// VulkanReplay_UpdateDescriptorSetWithTemplateKHR
//------------------------------------------------------------------------------
void VulkanReplay_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplateKHR descriptorUpdateTemplate, const void* pData)
{
    vkUpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData);
}

#endif // VK_KHR_descriptor_update_template

#if defined(VK_KHR_push_descriptor) || defined(VK_KHR_descriptor_update_template)
//------------------------------------------------------------------------------
// VulkanReplay_CmdPushDescriptorSetWithTemplateKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData)
{
    vkCmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData);
}

#endif // VK_KHR_push_descriptor || VK_KHR_descriptor_update_template

#if defined(VK_EXT_hdr_metadata)
//------------------------------------------------------------------------------
// VulkanReplay_SetHdrMetadataEXT
//------------------------------------------------------------------------------
void VulkanReplay_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata)
{
    std::vector<VkSwapchainKHR> upToDateSwapchains(swapchainCount);
    for (uint32_t i = 0; i < swapchainCount; i++)
    {
        upToDateSwapchains[i] = GetSwapchainInfo(pSwapchains[i]).upToDateSwapchain;
    }
    pSwapchains = upToDateSwapchains.data();

    vkSetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}

#endif // VK_EXT_hdr_metadata

#if defined(VK_KHR_shared_presentable_image)
//------------------------------------------------------------------------------
// VulkanReplay_GetSwapchainStatusKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain)
{
    swapchain = GetSwapchainInfo(swapchain).upToDateSwapchain;
    return NV_VK_VALIDATE(vkGetSwapchainStatusKHR(device, swapchain));
}

#endif // VK_KHR_shared_presentable_image

#if defined(VK_NV_clip_space_w_scaling)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportWScalingNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings)
{
    vkCmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings);
}

#endif // VK_NV_clip_space_w_scaling

#if defined(VK_EXT_discard_rectangles)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDiscardRectangleEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles)
{
    vkCmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_discard_rectangles) && VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION >= 2
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDiscardRectangleEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable)
{
    vkCmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDiscardRectangleModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode)
{
    vkCmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
}

#endif // VK_EXT_discard_rectangles

#if defined(VK_EXT_sample_locations)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetSampleLocationsEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo)
{
    vkCmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceMultisamplePropertiesEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties)
{
    vkGetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties);
}

#endif // VK_EXT_sample_locations

#if defined(VK_KHR_get_surface_capabilities2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfaceFormats2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats));
}

#endif // VK_KHR_get_surface_capabilities2

#if defined(VK_KHR_get_display_properties2)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceDisplayProperties2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceDisplayProperties2KHR(physicalDevice, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceDisplayPlaneProperties2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDisplayModeProperties2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties)
{
    return NV_VK_VALIDATE(vkGetDisplayModeProperties2KHR(physicalDevice, display, pPropertyCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDisplayPlaneCapabilities2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities)
{
    return NV_VK_VALIDATE(vkGetDisplayPlaneCapabilities2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities));
}

#endif // VK_KHR_get_display_properties2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferMemoryRequirements2
//------------------------------------------------------------------------------
void VulkanReplay_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    vkGetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferMemoryRequirements2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    vkGetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageMemoryRequirements2
//------------------------------------------------------------------------------
void VulkanReplay_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    vkGetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_get_memory_requirements2)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageMemoryRequirements2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2KHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    vkGetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_1) && !defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageSparseMemoryRequirements2
//------------------------------------------------------------------------------
void VulkanReplay_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements)
{
    vkGetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_VERSION_1_1 && !VKSC_VERSION_1_0

#if defined(VK_KHR_get_memory_requirements2)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageSparseMemoryRequirements2KHR
//------------------------------------------------------------------------------
void VulkanReplay_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2KHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements)
{
    vkGetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_KHR_get_memory_requirements2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceBufferMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    vkGetDeviceBufferMemoryRequirements(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceBufferMemoryRequirementsKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    vkGetDeviceBufferMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceImageMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements)
{
    vkGetDeviceImageMemoryRequirements(device, pInfo, pMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceImageMemoryRequirementsKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    vkGetDeviceImageMemoryRequirementsKHR(device, pInfo, pMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceImageSparseMemoryRequirements
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements)
{
    vkGetDeviceImageSparseMemoryRequirements(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_maintenance4)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceImageSparseMemoryRequirementsKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirementsKHR* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2KHR* pSparseMemoryRequirements)
{
    vkGetDeviceImageSparseMemoryRequirementsKHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}

#endif // VK_KHR_maintenance4

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_CreateSamplerYcbcrConversion
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion));
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
//------------------------------------------------------------------------------
// VulkanReplay_CreateSamplerYcbcrConversionKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversionKHR* pYcbcrConversion)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion));
}

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_DestroySamplerYcbcrConversion
//------------------------------------------------------------------------------
void VulkanReplay_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_sampler_ycbcr_conversion)
//------------------------------------------------------------------------------
// VulkanReplay_DestroySamplerYcbcrConversionKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversionKHR ycbcrConversion, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator);
}

#endif // VK_KHR_sampler_ycbcr_conversion

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceQueue2
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue)
{
    vkGetDeviceQueue2(device, pQueueInfo, pQueue);
}

#endif // VK_VERSION_1_1

#if defined(VK_EXT_validation_cache)
//------------------------------------------------------------------------------
// VulkanReplay_CreateValidationCacheEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyValidationCacheEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyValidationCacheEXT(device, validationCache, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetValidationCacheDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetValidationCacheDataEXT(device, validationCache, pDataSize, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_MergeValidationCachesEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches)
{
    return NV_VK_VALIDATE(vkMergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches));
}

#endif // VK_EXT_validation_cache

#if defined(VK_VERSION_1_1)
//------------------------------------------------------------------------------
// VulkanReplay_GetDescriptorSetLayoutSupport
//------------------------------------------------------------------------------
void VulkanReplay_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport)
{
    vkGetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
}

#endif // VK_VERSION_1_1

#if defined(VK_KHR_maintenance3)
//------------------------------------------------------------------------------
// VulkanReplay_GetDescriptorSetLayoutSupportKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupportKHR* pSupport)
{
    vkGetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport);
}

#endif // VK_KHR_maintenance3

#if defined(VK_AMD_shader_info)
//------------------------------------------------------------------------------
// VulkanReplay_GetShaderInfoAMD
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo)
{
    return NV_VK_VALIDATE(vkGetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo));
}

#endif // VK_AMD_shader_info

#if defined(VK_EXT_calibrated_timestamps)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceCalibrateableTimeDomainsEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainEXT* pTimeDomains)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice, pTimeDomainCount, pTimeDomains));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetCalibratedTimestampsEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation)
{
    return NV_VK_VALIDATE(vkGetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation));
}

#endif // VK_EXT_calibrated_timestamps

#if defined(VK_EXT_debug_utils)
//------------------------------------------------------------------------------
// VulkanReplay_SetDebugUtilsObjectNameEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[device]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkSetDebugUtilsObjectNameEXT as VK_EXT_debug_utils is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkSetDebugUtilsObjectNameEXT(device, pNameInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_SetDebugUtilsObjectTagEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[device]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkSetDebugUtilsObjectTagEXT as VK_EXT_debug_utils is unavailable");
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkSetDebugUtilsObjectTagEXT(device, pTagInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueBeginDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_QueueToDeviceMap[queue]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkQueueBeginDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueEndDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_QueueEndDebugUtilsLabelEXT(VkQueue queue)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_QueueToDeviceMap[queue]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkQueueEndDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    return vkQueueEndDebugUtilsLabelEXT(queue);
}

//------------------------------------------------------------------------------
// VulkanReplay_QueueInsertDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_QueueToDeviceMap[queue]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdBeginDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_CommandBufferToDeviceMap[commandBuffer]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdBeginDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_CommandBufferToDeviceMap[commandBuffer]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdBeginDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdInsertDebugUtilsLabelEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo)
{
    // It's possible this extension was available during capture but not replay
    if (!HasInstanceExtension(s_PhsyicalDeviceToInstanceMap[s_DeviceToPhysicalDeviceMap[s_CommandBufferToDeviceMap[commandBuffer]]], VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
    {
        NV_MESSAGE_ONCE("Skipping call to vkCmdBeginDebugUtilsLabelEXT as VK_EXT_debug_utils is unavailable");
        return;
    }

    vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateDebugUtilsMessengerEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyDebugUtilsMessengerEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_SubmitDebugUtilsMessageEXT
//------------------------------------------------------------------------------
void VulkanReplay_SubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
{
    vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
}

#endif // VK_EXT_debug_utils

#if defined(VK_EXT_external_memory_host)
//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryHostPointerPropertiesEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties)
{
    return NV_VK_VALIDATE(vkGetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties));
}

#endif // VK_EXT_external_memory_host

#if defined(VK_AMD_buffer_marker)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteBufferMarkerAMD
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker)
{
    vkCmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker);
}

#endif // VK_AMD_buffer_marker

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CreateRenderPass2
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    return NV_VK_VALIDATE(vkCreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass));
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
//------------------------------------------------------------------------------
// VulkanReplay_CreateRenderPass2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
    return NV_VK_VALIDATE(vkCreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass));
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginRenderPass2
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfo* pSubpassBeginInfo)
{
    // Patch up overrides
    VkRenderPassBeginInfo renderPassBegin = *pRenderPassBegin;
    auto& tls = GetThreadState();
    renderPassBegin.framebuffer = GetActive_Framebuffer(tls.activeOverride, renderPassBegin.framebuffer);
    vkCmdBeginRenderPass2(commandBuffer, &renderPassBegin, pSubpassBeginInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginRenderPass2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, const VkSubpassBeginInfoKHR* pSubpassBeginInfo)
{
    // Patch up overrides
    VkRenderPassBeginInfo renderPassBegin = *pRenderPassBegin;
    auto& tls = GetThreadState();
    renderPassBegin.framebuffer = GetActive_Framebuffer(tls.activeOverride, renderPassBegin.framebuffer);
    vkCmdBeginRenderPass2KHR(commandBuffer, &renderPassBegin, pSubpassBeginInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdNextSubpass2
//------------------------------------------------------------------------------
void VulkanReplay_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo* pSubpassBeginInfo, const VkSubpassEndInfo* pSubpassEndInfo)
{
    vkCmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdNextSubpass2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR* pSubpassBeginInfo, const VkSubpassEndInfoKHR* pSubpassEndInfo)
{
    vkCmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdEndRenderPass2
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo* pSubpassEndInfo)
{
    vkCmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_create_renderpass2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdEndRenderPass2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR* pSubpassEndInfo)
{
    vkCmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo);
}

#endif // VK_KHR_create_renderpass2

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_GetSemaphoreCounterValue
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    return NV_VK_VALIDATE(vkGetSemaphoreCounterValue(device, semaphore, pValue));
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
//------------------------------------------------------------------------------
// VulkanReplay_GetSemaphoreCounterValueKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue)
{
    return NV_VK_VALIDATE(vkGetSemaphoreCounterValueKHR(device, semaphore, pValue));
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_KHR_timeline_semaphore) || defined(VK_VERSION_1_2)

template <typename T_FnWait>
VkResult DoWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout, T_FnWait fnWait)
{
    if (s_IgnoreSemaphores)
    {
        return VK_SUCCESS;
    }

    // Local copy
    VkSemaphoreWaitInfo waitInfo = *pWaitInfo;
    std::vector<VkSemaphore> vecSemaphores;
    std::vector<uint64_t> vecValues;
    vecSemaphores.reserve(pWaitInfo->semaphoreCount);
    vecValues.reserve(pWaitInfo->semaphoreCount);

    for (uint32_t i = 0; i < pWaitInfo->semaphoreCount; i++)
    {
        VkSemaphore semaphore = pWaitInfo->pSemaphores[i];
        const SemaphoreInfo* pSemaphoreInfo = LookupSemaphoreInfo(semaphore);
        NV_ASSERT(pSemaphoreInfo);
        semaphore = GetActive_Sempahore(s_BufferingIdx, semaphore);
        const uint64_t waitValue = pWaitInfo->pValues[i];
        const uint64_t currentValue = pSemaphoreInfo->value;
        if (waitValue <= currentValue && IsAvailableForTimelineWait(pSemaphoreInfo, waitValue))
        {
            vecSemaphores.push_back(semaphore);
            vecValues.push_back(waitValue + (pSemaphoreInfo->delta * s_FrameIdx));
        }
        else
        {
            // We replay in a single thread mode which means there might be a timeline wait
            // on a value that is set by another thread. In an application scenario, that'll
            // keep that thread idle until the value is triggered by another thread and work
            // continues. As such, the linear replay function stream will actually submit the
            // work in the correct order and this is safe the majority of the time.
            NV_MESSAGE_ONCE("WARNING: Skipping timeline semaphore wait on value that will never be signaled. This is potentially a side effect single threaded replay and may lead to instability.");
        }
    }

    waitInfo.pSemaphores = vecSemaphores.data();
    waitInfo.pValues = vecValues.data();
    waitInfo.semaphoreCount = static_cast<uint32_t>(vecSemaphores.size());
    if (waitInfo.semaphoreCount)
    {
        return NV_VK_VALIDATE(fnWait(device, &waitInfo, timeout));
    }
    else
    {
        return VK_SUCCESS;
    }
}

#endif // defined(VK_KHR_timeline_semaphore) || defined(VK_VERSION_1_2)

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_WaitSemaphores
//------------------------------------------------------------------------------
VkResult VulkanReplay_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout)
{
    return DoWaitSemaphores(device, pWaitInfo, timeout, &vkWaitSemaphores);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
//------------------------------------------------------------------------------
// VulkanReplay_WaitSemaphoresKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfoKHR* pWaitInfo, uint64_t timeout)
{
    return DoWaitSemaphores(device, pWaitInfo, timeout, &vkWaitSemaphoresKHR);
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_SignalSemaphore
//------------------------------------------------------------------------------
VkResult VulkanReplay_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo)
{
    if (s_IgnoreSemaphores)
    {
        return VK_SUCCESS;
    }

    SemaphoreInfo* pInfo = LookupSemaphoreInfo(pSignalInfo->semaphore);
    NV_ASSERT(pInfo);
    VkSemaphoreSignalInfo signalInfo = *pSignalInfo;
    RecordTimelineSignal(pInfo, signalInfo.value);
    signalInfo.value += (pInfo->delta * s_FrameIdx);
    pInfo->value = signalInfo.value;
    VkSemaphore semaphore = GetActive_Sempahore(s_BufferingIdx, signalInfo.semaphore);
    signalInfo.semaphore = semaphore;
    return NV_VK_VALIDATE(vkSignalSemaphore(device, &signalInfo));
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_timeline_semaphore)
//------------------------------------------------------------------------------
// VulkanReplay_SignalSemaphoreKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfoKHR* pSignalInfo)
{
    if (s_IgnoreSemaphores)
    {
        return VK_SUCCESS;
    }

    SemaphoreInfo* pInfo = LookupSemaphoreInfo(pSignalInfo->semaphore);
    NV_ASSERT(pInfo);
    VkSemaphoreSignalInfo signalInfo = *pSignalInfo;
    RecordTimelineSignal(pInfo, signalInfo.value);
    signalInfo.value += (pInfo->delta * s_FrameIdx);
    pInfo->value = signalInfo.value;
    VkSemaphore semaphore = GetActive_Sempahore(s_BufferingIdx, signalInfo.semaphore);
    signalInfo.semaphore = semaphore;
    return NV_VK_VALIDATE(vkSignalSemaphoreKHR(device, &signalInfo));
}

#endif // VK_KHR_timeline_semaphore

#if defined(VK_ANDROID_external_memory_android_hardware_buffer)
//------------------------------------------------------------------------------
// VulkanReplay_GetAndroidHardwareBufferPropertiesANDROID
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties)
{
    return NV_VK_VALIDATE(vkGetAndroidHardwareBufferPropertiesANDROID(device, buffer, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetMemoryAndroidHardwareBufferANDROID
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer)
{
    return NV_VK_VALIDATE(vkGetMemoryAndroidHardwareBufferANDROID(device, pInfo, pBuffer));
}

#endif // VK_ANDROID_external_memory_android_hardware_buffer

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndirectCount
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndirectCountKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_KHR_draw_indirect_count

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndexedIndirectCount
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_draw_indirect_count)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndexedIndirectCountKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_KHR_draw_indirect_count

#if defined(VK_NV_device_diagnostic_checkpoints)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCheckpointNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker)
{
    // Skip if disabled
    if (s_DisableDeviceDiagnosticCheckpoints)
    {
        return;
    }

    vkCmdSetCheckpointNV(commandBuffer, pCheckpointMarker);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetQueueCheckpointDataNV
//------------------------------------------------------------------------------
void VulkanReplay_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData)
{
    // Skip if disabled
    if (s_DisableDeviceDiagnosticCheckpoints)
    {
        return;
    }

    vkGetQueueCheckpointDataNV(queue, pCheckpointDataCount, pCheckpointData);
}

#endif // VK_NV_device_diagnostic_checkpoints

#if defined(VK_EXT_transform_feedback)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBindTransformFeedbackBuffersEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes)
{
    vkCmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginTransformFeedbackEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets)
{
    vkCmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndTransformFeedbackEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets)
{
    vkCmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginQueryIndexedEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index)
{
    // Skip if query not reset
    if (IsQueryAvailable(queryPool, query))
    {
        return;
    }

    if (!s_DisableCopyQueryPoolResults)
    {
        s_QueryPoolAvailableRanges[queryPool][query] = VK_TRUE;
    }
    vkCmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndQueryIndexedEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index)
{
    vkCmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawIndirectByteCountEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride)
{
    vkCmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride);
}

#endif // VK_EXT_transform_feedback

#if defined(VK_NV_scissor_exclusive)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetExclusiveScissorNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors)
{
    vkCmdSetExclusiveScissorNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors);
}

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_scissor_exclusive) && VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION >= 2
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetExclusiveScissorEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables)
{
    vkCmdSetExclusiveScissorEnableNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissorEnables);
}

#endif // VK_NV_scissor_exclusive

#if defined(VK_NV_shading_rate_image)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBindShadingRateImageNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout)
{
    // Patch up overrides
    auto& tls = GetThreadState();
    imageView = GetActive_ImageView(tls.activeOverride, imageView);
    vkCmdBindShadingRateImageNV(commandBuffer, imageView, imageLayout);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportShadingRatePaletteNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes)
{
    vkCmdSetViewportShadingRatePaletteNV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoarseSampleOrderNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders)
{
    vkCmdSetCoarseSampleOrderNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders);
}

#endif // VK_NV_shading_rate_image

#if defined(VK_NV_mesh_shader)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask)
{
    vkCmdDrawMeshTasksNV(commandBuffer, taskCount, firstTask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksIndirectNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    vkCmdDrawMeshTasksIndirectNV(commandBuffer, buffer, offset, drawCount, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksIndirectCountNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawMeshTasksIndirectCountNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_NV_mesh_shader

#if defined(VK_EXT_mesh_shader)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ)
{
    vkCmdDrawMeshTasksEXT(commandBuffer, groupCountX, groupCountY, groupCountZ);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksIndirectEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
    vkCmdDrawMeshTasksIndirectEXT(commandBuffer, buffer, offset, drawCount, stride);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDrawMeshTasksIndirectCountEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride)
{
    vkCmdDrawMeshTasksIndirectCountEXT(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}

#endif // VK_EXT_mesh_shader

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_CompileDeferredNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader)
{
    // Ignore during frame loop; all deferred shaders are compiled as part of initialization
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCompileDeferredNV(device, pipeline, shader));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateAccelerationStructureNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // Real call
    VkResult result = NV_VK_VALIDATE(vkCreateAccelerationStructureNV(device, pCreateInfo, pAllocator, pAccelerationStructure));

    // Create object
    if (result == VK_SUCCESS)
    {
        s_AccelerationStructuresNV.Register(*pAccelerationStructure, device, pCreateInfo);
    }

    return result;
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyAccelerationStructureKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyAccelerationStructureKHR(device, accelerationStructure, pAllocator);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyAccelerationStructureNV
//------------------------------------------------------------------------------
void VulkanReplay_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyAccelerationStructureNV(device, accelerationStructure, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetAccelerationStructureMemoryRequirementsNV
//------------------------------------------------------------------------------
void VulkanReplay_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2KHR* pMemoryRequirements)
{
    vkGetAccelerationStructureMemoryRequirementsNV(device, pInfo, pMemoryRequirements);
}

//------------------------------------------------------------------------------
// VulkanReplay_BindAccelerationStructureMemoryNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    // JIT patch up acceleration structure memory if changes are needed
    std::vector<uint32_t> vecMemoryTypeIdx(bindInfoCount);
    std::vector<VkBindAccelerationStructureMemoryInfoNV> vecBindInfos(pBindInfos, pBindInfos + bindInfoCount);
    for (uint32_t i = 0; i < bindInfoCount; i++)
    {
        vecMemoryTypeIdx[i] = PatchAccelerationStructureMemoryNV(device, vecBindInfos[i]);
    }

    // Real call
    return NV_VK_VALIDATE(vkBindAccelerationStructureMemoryNV(device, bindInfoCount, vecBindInfos.data()));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyAccelerationStructureNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode)
{
    vkCmdCopyAccelerationStructureNV(commandBuffer, dst, src, mode);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyAccelerationStructureKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo)
{
    vkCmdCopyAccelerationStructureKHR(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo)
{
    return NV_VK_VALIDATE(vkCopyAccelerationStructureKHR(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyAccelerationStructureToMemoryKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo)
{
    vkCmdCopyAccelerationStructureToMemoryKHR(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyAccelerationStructureToMemoryKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo)
{
    return NV_VK_VALIDATE(vkCopyAccelerationStructureToMemoryKHR(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMemoryToAccelerationStructureKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo)
{
    vkCmdCopyMemoryToAccelerationStructureKHR(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyMemoryToAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo)
{
    return NV_VK_VALIDATE(vkCopyMemoryToAccelerationStructureKHR(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteAccelerationStructuresPropertiesKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    vkCmdWriteAccelerationStructuresPropertiesKHR(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteAccelerationStructuresPropertiesNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    vkCmdWriteAccelerationStructuresPropertiesNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBuildAccelerationStructureNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset)
{
    // First time through we need to patch the instance handle
    if (instanceData != VK_NULL_HANDLE)
    {
        const VkResult result = PatchInstanceBuffer<Feature::NV>(commandBuffer, pInfo->instanceCount, instanceData, instanceOffset);
        if (result == VK_ERROR_INVALID_DEVICE_ADDRESS_EXT)
        {
            return;
        }
    }

    vkCmdBuildAccelerationStructureNV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_WriteAccelerationStructuresPropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, size_t dataSize, void* pData, size_t stride)
{
    return NV_VK_VALIDATE(vkWriteAccelerationStructuresPropertiesKHR(device, accelerationStructureCount, pAccelerationStructures, queryType, dataSize, pData, stride));
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_CmdTraceRaysKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth)
{
    // Get index for this trace call dependent on the override because it can be recorded multiple times
    uint32_t& traceRaysIdx = s_TraceRaysNVIdx[commandBuffer];

    // First time through we need to patch the SBT shader handles
    VkStridedDeviceAddressRegionKHR raygenShaderBindingTable = {};
    if (pRaygenShaderBindingTable)
    {
        raygenShaderBindingTable = PatchShaderBindingTableKHR(traceRaysIdx, RayTracingShaderBindingTableType::RayGenShader, commandBuffer, *pRaygenShaderBindingTable);
    }

    VkStridedDeviceAddressRegionKHR missShaderBindingTable = {};
    if (pMissShaderBindingTable)
    {
        missShaderBindingTable = PatchShaderBindingTableKHR(traceRaysIdx, RayTracingShaderBindingTableType::MissShader, commandBuffer, *pMissShaderBindingTable);
    }

    VkStridedDeviceAddressRegionKHR hitShaderBindingTable = {};
    if (pHitShaderBindingTable)
    {
        hitShaderBindingTable = PatchShaderBindingTableKHR(traceRaysIdx, RayTracingShaderBindingTableType::HitShader, commandBuffer, *pHitShaderBindingTable);
    }

    VkStridedDeviceAddressRegionKHR callableShaderBindingTable = {};
    if (pCallableShaderBindingTable)
    {
        callableShaderBindingTable = PatchShaderBindingTableKHR(traceRaysIdx, RayTracingShaderBindingTableType::CallableShader, commandBuffer, *pCallableShaderBindingTable);
    }

    // Increase trace counter
    traceRaysIdx++;

    vkCmdTraceRaysKHR(commandBuffer,
        pRaygenShaderBindingTable ? &raygenShaderBindingTable : nullptr,
        pMissShaderBindingTable ? &missShaderBindingTable : nullptr,
        pHitShaderBindingTable ? &hitShaderBindingTable : nullptr,
        pCallableShaderBindingTable ? &callableShaderBindingTable : nullptr,
        width, height, depth);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_CmdTraceRaysNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth)
{
    // Get index for this trace call dependent on the override because it can be recorded multiple times
    uint32_t& traceRaysIdx = s_TraceRaysNVIdx[commandBuffer];

    // First time through we need to patch the SBT shader handles
    if (raygenShaderBindingTableBuffer != VK_NULL_HANDLE)
    {
        raygenShaderBindingTableBuffer = PatchShaderBindingTableNV(traceRaysIdx, RayTracingShaderBindingTableType::RayGenShader, commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, 0);
    }
    if (missShaderBindingTableBuffer != VK_NULL_HANDLE)
    {
        missShaderBindingTableBuffer = PatchShaderBindingTableNV(traceRaysIdx, RayTracingShaderBindingTableType::MissShader, commandBuffer, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride);
    }
    if (hitShaderBindingTableBuffer != VK_NULL_HANDLE)
    {
        hitShaderBindingTableBuffer = PatchShaderBindingTableNV(traceRaysIdx, RayTracingShaderBindingTableType::HitShader, commandBuffer, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride);
    }
    if (callableShaderBindingTableBuffer != VK_NULL_HANDLE)
    {
        callableShaderBindingTableBuffer = PatchShaderBindingTableNV(traceRaysIdx, RayTracingShaderBindingTableType::CallableShader, commandBuffer, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride);
    }

    // Increase trace counter
    traceRaysIdx++;

    vkCmdTraceRaysNV(commandBuffer, raygenShaderBindingTableBuffer, 0, missShaderBindingTableBuffer, 0, missShaderBindingStride, hitShaderBindingTableBuffer, 0, hitShaderBindingStride, callableShaderBindingTableBuffer, 0, callableShaderBindingStride, width, height, depth);
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_GetRayTracingShaderGroupHandlesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetRayTracingShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData));
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_GetRayTracingShaderGroupHandlesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetRayTracingShaderGroupHandlesNV(device, pipeline, firstGroup, groupCount, dataSize, pData));
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_GetRayTracingCaptureReplayShaderGroupHandlesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetRayTracingCaptureReplayShaderGroupHandlesKHR(device, pipeline, firstGroup, groupCount, dataSize, pData));
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_ray_tracing)
//------------------------------------------------------------------------------
// VulkanReplay_GetAccelerationStructureHandleNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetAccelerationStructureHandleNV(device, accelerationStructure, dataSize, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateRayTracingPipelinesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    const VkResult result = NV_VK_VALIDATE(vkCreateRayTracingPipelinesNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

    for (uint32_t i = 0; i < createInfoCount; i++)
    {
        VkPipeline pipeline = pPipelines[i];
        const VkRayTracingPipelineCreateInfoNV& createInfo = pCreateInfos[i];
        for (uint32_t group = 0; group < createInfo.groupCount; group++)
        {
            const VkRayTracingShaderGroupCreateInfoNV& groupCreateInfoNV = createInfo.pGroups[group];
            VkRayTracingShaderGroupCreateInfoKHR groupCreateInfoKHR = { VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR };
            groupCreateInfoKHR.type = groupCreateInfoNV.type;
            groupCreateInfoKHR.generalShader = groupCreateInfoNV.generalShader;
            groupCreateInfoKHR.closestHitShader = groupCreateInfoNV.closestHitShader;
            groupCreateInfoKHR.anyHitShader = groupCreateInfoNV.anyHitShader;
            groupCreateInfoKHR.intersectionShader = groupCreateInfoNV.intersectionShader;
            s_RayTracingGroupInfo[std::make_tuple(pipeline, group)] = groupCreateInfoKHR;
        }
    }

    return result;
}

#endif // VK_NV_ray_tracing

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_CreateRayTracingPipelinesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    const VkResult result = NV_VK_VALIDATE(vkCreateRayTracingPipelinesKHR(device, deferredOperation, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));

    for (uint32_t i = 0; i < createInfoCount; i++)
    {
        VkPipeline pipeline = pPipelines[i];
        const VkRayTracingPipelineCreateInfoKHR& createInfo = pCreateInfos[i];
        for (uint32_t group = 0; group < createInfo.groupCount; group++)
        {
            s_RayTracingGroupInfo[std::make_tuple(pipeline, group)] = createInfo.pGroups[group];
        }
    }

    return result;
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NV_cooperative_matrix)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceCooperativeMatrixPropertiesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice, pPropertyCount, pProperties));
}

#endif // VK_NV_cooperative_matrix

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_CmdTraceRaysIndirectKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress)
{
    vkCmdTraceRaysIndirectKHR(commandBuffer, pRaygenShaderBindingTable, pMissShaderBindingTable, pHitShaderBindingTable, pCallableShaderBindingTable, indirectDeviceAddress);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_KHR_ray_tracing_maintenance1)
//------------------------------------------------------------------------------
// VulkanReplay_CmdTraceRaysIndirect2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress)
{
    vkCmdTraceRaysIndirect2KHR(commandBuffer, indirectDeviceAddress);
}

#endif // VK_KHR_ray_tracing_maintenance1

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceAccelerationStructureCompatibilityKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility)
{
    vkGetDeviceAccelerationStructureCompatibilityKHR(device, pVersionInfo, pCompatibility);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_ray_tracing_pipeline)
//------------------------------------------------------------------------------
// VulkanReplay_GetRayTracingShaderGroupStackSizeKHR
//------------------------------------------------------------------------------
VkDeviceSize VulkanReplay_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader)
{
    return vkGetRayTracingShaderGroupStackSizeKHR(device, pipeline, group, groupShader);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRayTracingPipelineStackSizeKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize)
{
    vkCmdSetRayTracingPipelineStackSizeKHR(commandBuffer, pipelineStackSize);
}

#endif // VK_KHR_ray_tracing_pipeline

#if defined(VK_NVX_image_view_handle)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageViewHandleNVX
//------------------------------------------------------------------------------
uint32_t VulkanReplay_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo)
{
    return vkGetImageViewHandleNVX(device, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetImageViewAddressNVX
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties)
{
    return NV_VK_VALIDATE(vkGetImageViewAddressNVX(device, imageView, pProperties));
}

#endif // VK_NVX_image_view_handle

#if defined(VK_EXT_full_screen_exclusive)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSurfacePresentModes2EXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceSurfacePresentModes2EXT(physicalDevice, pSurfaceInfo, pPresentModeCount, pPresentModes));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceGroupSurfacePresentModes2EXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes)
{
    return NV_VK_VALIDATE(vkGetDeviceGroupSurfacePresentModes2EXT(device, pSurfaceInfo, pModes));
}

//------------------------------------------------------------------------------
// VulkanReplay_AcquireFullScreenExclusiveModeEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain)
{
    // -wb removes full screen exclusive usage
    if (Application::HasForceBorderlessWindow())
    {
        return VK_SUCCESS;
    }

    swapchain = GetSwapchainInfo(swapchain).upToDateSwapchain;
    return NV_VK_VALIDATE(vkAcquireFullScreenExclusiveModeEXT(device, swapchain));
}

//------------------------------------------------------------------------------
// VulkanReplay_ReleaseFullScreenExclusiveModeEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain)
{
    swapchain = GetSwapchainInfo(swapchain).upToDateSwapchain;
    return NV_VK_VALIDATE(vkReleaseFullScreenExclusiveModeEXT(device, swapchain));
}

#endif // VK_EXT_full_screen_exclusive

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferOpaqueCaptureAddress
//------------------------------------------------------------------------------
uint64_t VulkanReplay_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo)
{
    return vkGetBufferOpaqueCaptureAddress(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferOpaqueCaptureAddressKHR
//------------------------------------------------------------------------------
uint64_t VulkanReplay_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo)
{
    return vkGetBufferOpaqueCaptureAddressKHR(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferDeviceAddress
//------------------------------------------------------------------------------
VkDeviceAddress VulkanReplay_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo)
{
    return vkGetBufferDeviceAddress(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferDeviceAddressKHR
//------------------------------------------------------------------------------
VkDeviceAddress VulkanReplay_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfoKHR* pInfo)
{
    return vkGetBufferDeviceAddressKHR(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_EXT_buffer_device_address)
//------------------------------------------------------------------------------
// VulkanReplay_GetBufferDeviceAddressEXT
//------------------------------------------------------------------------------
VkDeviceAddress VulkanReplay_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfoEXT* pInfo)
{
    return vkGetBufferDeviceAddressEXT(device, pInfo);
}

#endif // VK_EXT_buffer_device_address

#if defined(VK_EXT_headless_surface)
//------------------------------------------------------------------------------
// VulkanReplay_CreateHeadlessSurfaceEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
    return NV_VK_VALIDATE(vkCreateHeadlessSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface));
}

#endif // VK_EXT_headless_surface

#if defined(VK_NV_coverage_reduction_mode)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(physicalDevice, pCombinationCount, pCombinations));
}

#endif // VK_NV_coverage_reduction_mode

#if defined(VK_VERSION_1_2)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceMemoryOpaqueCaptureAddress
//------------------------------------------------------------------------------
uint64_t VulkanReplay_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo)
{
    return vkGetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
}

#endif // VK_VERSION_1_2

#if defined(VK_KHR_buffer_device_address)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceMemoryOpaqueCaptureAddressKHR
//------------------------------------------------------------------------------
uint64_t VulkanReplay_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfoKHR* pInfo)
{
    return vkGetDeviceMemoryOpaqueCaptureAddressKHR(device, pInfo);
}

#endif // VK_KHR_buffer_device_address

#if defined(VK_KHR_pipeline_executable_properties)
//------------------------------------------------------------------------------
// VulkanReplay_GetPipelineExecutablePropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPipelineExecutableStatisticsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPipelineExecutableInternalRepresentationsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR* pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations));
}

#endif // VK_KHR_pipeline_executable_properties

#if defined(VK_EXT_line_rasterization)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLineStippleEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern)
{
    vkCmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
}

#endif // VK_EXT_line_rasterization

#if defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetFaultData
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetFaultData(VkDevice device, VkFaultQueryBehavior faultQueryBehavior, VkBool32* pUnrecordedFaults, uint32_t* pFaultCount, VkFaultData* pFaults)
{
    return NV_VK_VALIDATE(vkGetFaultData(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults));
}

#endif // VKSC_VERSION_1_0

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceToolProperties
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceToolProperties(physicalDevice, pToolCount, pToolProperties));
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_tooling_info)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceToolPropertiesEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolPropertiesEXT* pToolProperties)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties));
}

#endif // VK_EXT_tooling_info

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_CreateAccelerationStructureKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateAccelerationStructureKHR(VkDevice device, const VkAccelerationStructureCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR* pAccelerationStructure)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateAccelerationStructureKHR(device, pCreateInfo, pAllocator, pAccelerationStructure));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBuildAccelerationStructuresKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBuildAccelerationStructuresKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos)
{
    // On the first frame we can muck with recording information
    const VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

    for (uint32_t infoIdx = 0; infoIdx < infoCount; infoIdx++)
    {

        // We own pInfos in the layer above so we are free to copy without making a local copy
        VkAccelerationStructureBuildGeometryInfoKHR& info = const_cast<VkAccelerationStructureBuildGeometryInfoKHR&>(pInfos[infoIdx]);

        // We only need to perform this one time update once
        VULKAN_REPLAY_WRITE_LOCK();

        static std::set<const VkAccelerationStructureBuildGeometryInfoKHR*> k_HasUpdatedInfo;
        if (k_HasUpdatedInfo.find(&info) != k_HasUpdatedInfo.end())
        {
            continue;
        }
        else
        {
            k_HasUpdatedInfo.insert(&info);
        }

        for (uint32_t geometryIdx = 0; geometryIdx < info.geometryCount; geometryIdx++)
        {

            // Edit geometry in place; this only works because it is passed in a
            // static data;
            VkAccelerationStructureGeometryKHR* pGeometry = [=]() -> VkAccelerationStructureGeometryKHR* {
                if (info.pGeometries)
                {
                    return const_cast<VkAccelerationStructureGeometryKHR*>(info.pGeometries + geometryIdx);
                }
                return const_cast<VkAccelerationStructureGeometryKHR*>(*(info.ppGeometries) + geometryIdx);
            }();

            switch (pGeometry->geometryType)
            {
            case VK_GEOMETRY_TYPE_TRIANGLES_KHR:
            {
#if defined(VK_EXT_opacity_micromap)
                VkAccelerationStructureTrianglesOpacityMicromapEXT* pAccelerationStructureTrianglesOpacityMicromapEXT = (VkAccelerationStructureTrianglesOpacityMicromapEXT*)FindStructure(VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_TRIANGLES_OPACITY_MICROMAP_EXT, pGeometry->geometry.triangles.pNext);
                if (pAccelerationStructureTrianglesOpacityMicromapEXT && pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress != 0)
                {
                    s_BufferAddressManager.RemapCaptureAddressForReplay(device, pAccelerationStructureTrianglesOpacityMicromapEXT->indexBuffer.deviceAddress);
                }
#endif

                s_BufferAddressManager.RemapCaptureAddressForReplay(device, pGeometry->geometry.triangles.vertexData.deviceAddress);
                s_BufferAddressManager.RemapCaptureAddressForReplay(device, pGeometry->geometry.triangles.indexData.deviceAddress);
                s_BufferAddressManager.RemapCaptureAddressForReplay(device, pGeometry->geometry.triangles.transformData.deviceAddress);
            }
            break;
            case VK_GEOMETRY_TYPE_AABBS_KHR:
            {
                s_BufferAddressManager.RemapCaptureAddressForReplay(device, pGeometry->geometry.aabbs.data.deviceAddress);
            }
            break;
            case VK_GEOMETRY_TYPE_INSTANCES_KHR:
            {
                // This path should not be taken as the C++ code is instead generated with a special
                // VulkanHelper_CmdBuildAccelerationStructuresInstanceKHR command only for instance
                // data where we have stripped out the references.
                //
                // NOTE: If acceleration structure capture/replay is support by the driver this path will be unnecessary
                NV_ASSERT(false && "Unexpected VK_GEOMETRY_TYPE_INSTANCES_KHR");
                break;
            }
            default:
                break;
            }
        }

        // Get scratch memory for this build
        AccelerationStructureKHR* pAccelerationStructureKHR = s_AccelerationStructuresKHR.Lookup(info.dstAccelerationStructure);
        NV_ASSERT(pAccelerationStructureKHR);
        if (pAccelerationStructureKHR->replayManagedScratch || s_ForceReplayManagedScratch)
        {

            // Get build sizes associated with this object
            const VkDeviceSize requiredScratchSize = info.mode == VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR ? pAccelerationStructureKHR->sizeInfo.buildScratchSize : pAccelerationStructureKHR->sizeInfo.updateScratchSize;
            ScopedVmaBuffer* pBuffer = new ScopedVmaBuffer(s_Allocators[device], requiredScratchSize, VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT), VMA_MEMORY_USAGE_GPU_ONLY);
            NV_ASSERT(pBuffer);
            info.scratchData.deviceAddress = GetBufferAddress(device, pBuffer->GetBuffer());
            NV_ASSERT(info.scratchData.deviceAddress);
        }
        else
        {

            // Remap the the scratch data too; it doesn't need to be GPU addressable
            s_BufferAddressManager.RemapCaptureAddressForReplay(device, info.scratchData.deviceAddress);
        }
    }

    vkCmdBuildAccelerationStructuresKHR(commandBuffer, infoCount, pInfos, ppBuildRangeInfos);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBuildAccelerationStructuresIndirectKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress* pIndirectDeviceAddresses, const uint32_t* pIndirectStrides, const uint32_t* const* ppMaxPrimitiveCounts)
{
    vkCmdBuildAccelerationStructuresIndirectKHR(commandBuffer, infoCount, pInfos, pIndirectDeviceAddresses, pIndirectStrides, ppMaxPrimitiveCounts);
}

//------------------------------------------------------------------------------
// VulkanReplay_BuildAccelerationStructuresKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_BuildAccelerationStructuresKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos)
{
    return NV_VK_VALIDATE(vkBuildAccelerationStructuresKHR(device, deferredOperation, infoCount, pInfos, ppBuildRangeInfos));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetAccelerationStructureDeviceAddressKHR
//------------------------------------------------------------------------------
VkDeviceAddress VulkanReplay_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo)
{
    return vkGetAccelerationStructureDeviceAddressKHR(device, pInfo);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_KHR_deferred_host_operations)
//------------------------------------------------------------------------------
// VulkanReplay_CreateDeferredOperationKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateDeferredOperationKHR(device, pAllocator, pDeferredOperation));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyDeferredOperationKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyDeferredOperationKHR(device, operation, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeferredOperationMaxConcurrencyKHR
//------------------------------------------------------------------------------
uint32_t VulkanReplay_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    return vkGetDeferredOperationMaxConcurrencyKHR(device, operation);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeferredOperationResultKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    return NV_VK_VALIDATE(vkGetDeferredOperationResultKHR(device, operation));
}

//------------------------------------------------------------------------------
// VulkanReplay_DeferredOperationJoinKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation)
{
    return NV_VK_VALIDATE(vkDeferredOperationJoinKHR(device, operation));
}

#endif // VK_KHR_deferred_host_operations

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCullMode
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode)
{
    vkCmdSetCullMode(commandBuffer, cullMode);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCullModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode)
{
    vkCmdSetCullModeEXT(commandBuffer, cullMode);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetFrontFace
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace)
{
    vkCmdSetFrontFace(commandBuffer, frontFace);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetFrontFaceEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace)
{
    vkCmdSetFrontFaceEXT(commandBuffer, frontFace);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPrimitiveTopology
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology)
{
    vkCmdSetPrimitiveTopology(commandBuffer, primitiveTopology);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPrimitiveTopologyEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology)
{
    vkCmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportWithCount
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports)
{
    vkCmdSetViewportWithCount(commandBuffer, viewportCount, pViewports);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportWithCountEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports)
{
    vkCmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetScissorWithCount
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors)
{
    vkCmdSetScissorWithCount(commandBuffer, scissorCount, pScissors);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetScissorWithCountEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors)
{
    vkCmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBindVertexBuffers2
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides)
{
    vkCmdBindVertexBuffers2(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBindVertexBuffers2EXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides)
{
    vkCmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthTestEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable)
{
    vkCmdSetDepthTestEnable(commandBuffer, depthTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthTestEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable)
{
    vkCmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthWriteEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable)
{
    vkCmdSetDepthWriteEnable(commandBuffer, depthWriteEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthWriteEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable)
{
    vkCmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthCompareOp
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp)
{
    vkCmdSetDepthCompareOp(commandBuffer, depthCompareOp);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthCompareOpEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp)
{
    vkCmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBoundsTestEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable)
{
    vkCmdSetDepthBoundsTestEnable(commandBuffer, depthBoundsTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBoundsTestEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable)
{
    vkCmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilTestEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable)
{
    vkCmdSetStencilTestEnable(commandBuffer, stencilTestEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilTestEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable)
{
    vkCmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilOp
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp)
{
    vkCmdSetStencilOp(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetStencilOpEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp)
{
    vkCmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}

#endif // VK_EXT_extended_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPatchControlPointsEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints)
{
    vkCmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRasterizerDiscardEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable)
{
    vkCmdSetRasterizerDiscardEnable(commandBuffer, rasterizerDiscardEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRasterizerDiscardEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable)
{
    vkCmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBiasEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable)
{
    vkCmdSetDepthBiasEnable(commandBuffer, depthBiasEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthBiasEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable)
{
    vkCmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLogicOpEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp)
{
    vkCmdSetLogicOpEXT(commandBuffer, logicOp);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPrimitiveRestartEnable
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable)
{
    vkCmdSetPrimitiveRestartEnable(commandBuffer, primitiveRestartEnable);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_extended_dynamic_state2) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPrimitiveRestartEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable)
{
    vkCmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
}

#endif // VK_EXT_extended_dynamic_state2 || VK_EXT_shader_object

#if defined(VK_EXT_extended_dynamic_state3) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetTessellationDomainOriginEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin)
{
    vkCmdSetTessellationDomainOriginEXT(commandBuffer, domainOrigin);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthClampEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable)
{
    vkCmdSetDepthClampEnableEXT(commandBuffer, depthClampEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetPolygonModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode)
{
    vkCmdSetPolygonModeEXT(commandBuffer, polygonMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRasterizationSamplesEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits rasterizationSamples)
{
    vkCmdSetRasterizationSamplesEXT(commandBuffer, rasterizationSamples);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetSampleMaskEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits samples, const VkSampleMask* pSampleMask)
{
    vkCmdSetSampleMaskEXT(commandBuffer, samples, pSampleMask);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetAlphaToCoverageEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable)
{
    vkCmdSetAlphaToCoverageEnableEXT(commandBuffer, alphaToCoverageEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetAlphaToOneEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable)
{
    vkCmdSetAlphaToOneEnableEXT(commandBuffer, alphaToOneEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLogicOpEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable)
{
    vkCmdSetLogicOpEnableEXT(commandBuffer, logicOpEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetColorBlendEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables)
{
    vkCmdSetColorBlendEnableEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEnables);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetColorBlendEquationEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations)
{
    vkCmdSetColorBlendEquationEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendEquations);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetColorWriteMaskEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks)
{
    vkCmdSetColorWriteMaskEXT(commandBuffer, firstAttachment, attachmentCount, pColorWriteMasks);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRasterizationStreamEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream)
{
    vkCmdSetRasterizationStreamEXT(commandBuffer, rasterizationStream);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetConservativeRasterizationModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode)
{
    vkCmdSetConservativeRasterizationModeEXT(commandBuffer, conservativeRasterizationMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetExtraPrimitiveOverestimationSizeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize)
{
    vkCmdSetExtraPrimitiveOverestimationSizeEXT(commandBuffer, extraPrimitiveOverestimationSize);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthClipEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable)
{
    vkCmdSetDepthClipEnableEXT(commandBuffer, depthClipEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetSampleLocationsEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable)
{
    vkCmdSetSampleLocationsEnableEXT(commandBuffer, sampleLocationsEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetColorBlendAdvancedEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced)
{
    vkCmdSetColorBlendAdvancedEXT(commandBuffer, firstAttachment, attachmentCount, pColorBlendAdvanced);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetProvokingVertexModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode)
{
    vkCmdSetProvokingVertexModeEXT(commandBuffer, provokingVertexMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLineRasterizationModeEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode)
{
    vkCmdSetLineRasterizationModeEXT(commandBuffer, lineRasterizationMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetLineStippleEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable)
{
    vkCmdSetLineStippleEnableEXT(commandBuffer, stippledLineEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDepthClipNegativeOneToOneEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne)
{
    vkCmdSetDepthClipNegativeOneToOneEXT(commandBuffer, negativeOneToOne);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportWScalingEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable)
{
    vkCmdSetViewportWScalingEnableNV(commandBuffer, viewportWScalingEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetViewportSwizzleNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles)
{
    vkCmdSetViewportSwizzleNV(commandBuffer, firstViewport, viewportCount, pViewportSwizzles);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageToColorEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable)
{
    vkCmdSetCoverageToColorEnableNV(commandBuffer, coverageToColorEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageToColorLocationNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation)
{
    vkCmdSetCoverageToColorLocationNV(commandBuffer, coverageToColorLocation);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageModulationModeNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode)
{
    vkCmdSetCoverageModulationModeNV(commandBuffer, coverageModulationMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageModulationTableEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable)
{
    vkCmdSetCoverageModulationTableEnableNV(commandBuffer, coverageModulationTableEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageModulationTableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable)
{
    vkCmdSetCoverageModulationTableNV(commandBuffer, coverageModulationTableCount, pCoverageModulationTable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetShadingRateImageEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable)
{
    vkCmdSetShadingRateImageEnableNV(commandBuffer, shadingRateImageEnable);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetCoverageReductionModeNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode)
{
    vkCmdSetCoverageReductionModeNV(commandBuffer, coverageReductionMode);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetRepresentativeFragmentTestEnableNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable)
{
    vkCmdSetRepresentativeFragmentTestEnableNV(commandBuffer, representativeFragmentTestEnable);
}

#endif // VK_EXT_extended_dynamic_state3 || VK_EXT_shader_object

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CreatePrivateDataSlot
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreatePrivateDataSlot(device, pCreateInfo, pAllocator, pPrivateDataSlot));
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
//------------------------------------------------------------------------------
// VulkanReplay_CreatePrivateDataSlotEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlotEXT* pPrivateDataSlot)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreatePrivateDataSlotEXT(device, pCreateInfo, pAllocator, pPrivateDataSlot));
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyPrivateDataSlot
//------------------------------------------------------------------------------
void VulkanReplay_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyPrivateDataSlot(device, privateDataSlot, pAllocator);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
//------------------------------------------------------------------------------
// VulkanReplay_DestroyPrivateDataSlotEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlotEXT privateDataSlot, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyPrivateDataSlotEXT(device, privateDataSlot, pAllocator);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_SetPrivateData
//------------------------------------------------------------------------------
VkResult VulkanReplay_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data)
{
    return NV_VK_VALIDATE(vkSetPrivateData(device, objectType, objectHandle, privateDataSlot, data));
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
//------------------------------------------------------------------------------
// VulkanReplay_SetPrivateDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t data)
{
    return NV_VK_VALIDATE(vkSetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, data));
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_GetPrivateData
//------------------------------------------------------------------------------
void VulkanReplay_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData)
{
    vkGetPrivateData(device, objectType, objectHandle, privateDataSlot, pData);
}

#endif // VK_VERSION_1_3

#if defined(VK_EXT_private_data)
//------------------------------------------------------------------------------
// VulkanReplay_GetPrivateDataEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlotEXT privateDataSlot, uint64_t* pData)
{
    vkGetPrivateDataEXT(device, objectType, objectHandle, privateDataSlot, pData);
}

#endif // VK_EXT_private_data

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBuffer2
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo)
{
    vkCmdCopyBuffer2(commandBuffer, pCopyBufferInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBuffer2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2KHR* pCopyBufferInfo)
{
    vkCmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImage2
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo)
{
    vkCmdCopyImage2(commandBuffer, pCopyImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImage2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2KHR* pCopyImageInfo)
{
    vkCmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBlitImage2
//------------------------------------------------------------------------------
void VulkanReplay_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo)
{
    vkCmdBlitImage2(commandBuffer, pBlitImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBlitImage2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2KHR* pBlitImageInfo)
{
    vkCmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBufferToImage2
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo)
{
    vkCmdCopyBufferToImage2(commandBuffer, pCopyBufferToImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyBufferToImage2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2KHR* pCopyBufferToImageInfo)
{
    vkCmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImageToBuffer2
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo)
{
    vkCmdCopyImageToBuffer2(commandBuffer, pCopyImageToBufferInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyImageToBuffer2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2KHR* pCopyImageToBufferInfo)
{
    vkCmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdResolveImage2
//------------------------------------------------------------------------------
void VulkanReplay_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo)
{
    vkCmdResolveImage2(commandBuffer, pResolveImageInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_copy_commands2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdResolveImage2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2KHR* pResolveImageInfo)
{
    vkCmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
}

#endif // VK_KHR_copy_commands2

#if defined(VK_KHR_fragment_shading_rate)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetFragmentShadingRateKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetFragmentShadingRateKHR(VkCommandBuffer commandBuffer, const VkExtent2D* pFragmentSize, const VkFragmentShadingRateCombinerOpKHR combinerOps[2])
{
    vkCmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceFragmentShadingRatesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceFragmentShadingRatesKHR(physicalDevice, pFragmentShadingRateCount, pFragmentShadingRates));
}

#endif // VK_KHR_fragment_shading_rate

#if defined(VK_NV_fragment_shading_rate_enums)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetFragmentShadingRateEnumNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer commandBuffer, VkFragmentShadingRateNV shadingRate, const VkFragmentShadingRateCombinerOpKHR combinerOps[2])
{
    vkCmdSetFragmentShadingRateEnumNV(commandBuffer, shadingRate, combinerOps);
}

#endif // VK_NV_fragment_shading_rate_enums

#if defined(VK_KHR_acceleration_structure)
//------------------------------------------------------------------------------
// VulkanReplay_GetAccelerationStructureBuildSizesKHR
//------------------------------------------------------------------------------
void VulkanReplay_GetAccelerationStructureBuildSizesKHR(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkAccelerationStructureBuildGeometryInfoKHR* pBuildInfo, const uint32_t* pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkGetAccelerationStructureBuildSizesKHR(device, buildType, pBuildInfo, pMaxPrimitiveCounts, pSizeInfo);
}

#endif // VK_KHR_acceleration_structure

#if defined(VK_EXT_vertex_input_dynamic_state) || defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetVertexInputEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions)
{
    vkCmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}

#endif // VK_EXT_vertex_input_dynamic_state || VK_EXT_shader_object

#if defined(VK_EXT_color_write_enable)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetColorWriteEnableEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetColorWriteEnableEXT(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkBool32* pColorWriteEnables)
{
    vkCmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
}

#endif // VK_EXT_color_write_enable

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetEvent2
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetEvent2(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfo* pDependencyInfo)
{
    vkCmdSetEvent2(commandBuffer, event, pDependencyInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdSetEvent2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, const VkDependencyInfoKHR* pDependencyInfo)
{
    s_CommandBufferSetEvents[commandBuffer].insert(event);

    // Override image information
    auto& tls = GetThreadState();
    VkDependencyInfoKHR dependencyInfo = *pDependencyInfo;
    std::vector<VkImageMemoryBarrier2KHR> vecImageMemoryBarrier2KHR(dependencyInfo.pImageMemoryBarriers, dependencyInfo.pImageMemoryBarriers + dependencyInfo.imageMemoryBarrierCount);
    for (VkImageMemoryBarrier2KHR& imageMemoryBarrier : vecImageMemoryBarrier2KHR)
    {
        imageMemoryBarrier.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier.image);
    }
    dependencyInfo.pImageMemoryBarriers = vecImageMemoryBarrier2KHR.data();
    vkCmdSetEvent2KHR(commandBuffer, event, &dependencyInfo);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdResetEvent2
//------------------------------------------------------------------------------
void VulkanReplay_CmdResetEvent2(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2 stageMask)
{
    vkCmdResetEvent2(commandBuffer, event, stageMask);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdResetEvent2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdResetEvent2KHR(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags2KHR stageMask)
{
    // If we are reseting an active event, remove it from the active list. If
    // we are reseting an event we don't think is active we have observed a
    // potential cross-frame synchronization issue and need to flush.
    auto itr = s_ActiveEvents.find(event);
    if (itr != s_ActiveEvents.end())
    {
        s_ActiveEvents.erase(itr);
    }

    vkCmdResetEvent2KHR(commandBuffer, event, stageMask);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWaitEvents2
//------------------------------------------------------------------------------
void VulkanReplay_CmdWaitEvents2(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfo* pDependencyInfos)
{
    vkCmdWaitEvents2(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWaitEvents2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdWaitEvents2KHR(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, const VkDependencyInfoKHR* pDependencyInfos)
{
    // Set global flag
    if (s_FrameIdx == 0)
    {
        s_SawWaitEvent = true;
    }

    for (uint32_t i = 0; i < eventCount; i++)
    {
        s_CommandBufferWaitEvents[commandBuffer].insert(pEvents[i]);
    }

    // Override image information
    auto& tls = GetThreadState();
    std::vector<VkDependencyInfoKHR> vecDependencyInfoKHR(pDependencyInfos, pDependencyInfos + eventCount);
    std::vector<std::vector<VkImageMemoryBarrier2KHR>> vecImageMemoryBarrier2KHR(eventCount);
    for (uint32_t i = 0; i < eventCount; i++)
    {
        vecImageMemoryBarrier2KHR[i] = std::vector<VkImageMemoryBarrier2KHR>(pDependencyInfos[i].pImageMemoryBarriers, pDependencyInfos[i].pImageMemoryBarriers + pDependencyInfos[i].imageMemoryBarrierCount);
        for (VkImageMemoryBarrier2KHR& imageMemoryBarrier : vecImageMemoryBarrier2KHR[i])
        {
            imageMemoryBarrier.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier.image);
        }
        vecDependencyInfoKHR[i].pImageMemoryBarriers = vecImageMemoryBarrier2KHR[i].data();
    }
    vkCmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, vecDependencyInfoKHR.data());
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdPipelineBarrier2
//------------------------------------------------------------------------------
void VulkanReplay_CmdPipelineBarrier2(VkCommandBuffer commandBuffer, const VkDependencyInfo* pDependencyInfo)
{
    // Patch up image overrides
    auto& tls = GetThreadState();
    VkDependencyInfo dependencyInfo = *pDependencyInfo;
    std::vector<VkImageMemoryBarrier2> vecImageMemoryBarrier2(dependencyInfo.pImageMemoryBarriers, dependencyInfo.pImageMemoryBarriers + dependencyInfo.imageMemoryBarrierCount);
    for (VkImageMemoryBarrier2& imageMemoryBarrier2 : vecImageMemoryBarrier2)
    {
        imageMemoryBarrier2.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier2.image);
    }
    dependencyInfo.pImageMemoryBarriers = vecImageMemoryBarrier2.data();

    vkCmdPipelineBarrier2(commandBuffer, &dependencyInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdPipelineBarrier2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdPipelineBarrier2KHR(VkCommandBuffer commandBuffer, const VkDependencyInfoKHR* pDependencyInfo)
{
    // Patch up image overrides
    auto& tls = GetThreadState();
    VkDependencyInfoKHR dependencyInfo = *pDependencyInfo;
    std::vector<VkImageMemoryBarrier2KHR> vecImageMemoryBarrier2(dependencyInfo.pImageMemoryBarriers, dependencyInfo.pImageMemoryBarriers + dependencyInfo.imageMemoryBarrierCount);
    for (VkImageMemoryBarrier2KHR& imageMemoryBarrier2 : vecImageMemoryBarrier2)
    {
        imageMemoryBarrier2.image = GetActive_Image(tls.activeOverride, imageMemoryBarrier2.image);
    }
    dependencyInfo.pImageMemoryBarriers = vecImageMemoryBarrier2.data();

    vkCmdPipelineBarrier2KHR(commandBuffer, &dependencyInfo);
}

#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3) || defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// DoQueueSubmit2
//------------------------------------------------------------------------------
template <typename T_FnQueueSubmit2>
VkResult DoQueueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence, T_FnQueueSubmit2 fn)
{
    auto& tls = GetThreadState();

    // Count the number of command buffers
    size_t commandBufferInfoCount = 0;
    for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
    {
        commandBufferInfoCount += pSubmits[submitIdx].commandBufferInfoCount;
    }

    // Get associated device
    const VkDevice device = s_QueueToDeviceMap[queue];

    // We need to inject a fence for submit calls without one. This is a side effect of replaying
    // a single frame where we do not reallocate command buffers that were originally created in
    // frame using a "fired and forgot" pattern.
    if (fence == VK_NULL_HANDLE)
    {
        auto itr = s_InjectedSubmitFences.find(s_SubmitIdx);
        if (itr == s_InjectedSubmitFences.end())
        {
            VULKAN_REPLAY_WRITE_LOCK();
            VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
            vkCreateFence(device, &createInfo, nullptr, &fence);
            s_InjectedSubmitFences[s_SubmitIdx] = fence;
            s_FenceStatus[fence] = FenceStatus{};

            // Create multi-buffering clones
            for (uint32_t i = 1; i < s_BufferingSize; i++)
            {
                VkFence clone;
                vkCreateFence(device, &createInfo, nullptr, &clone);
                s_FenceOverrides[fence].push_back(clone);
                s_FenceStatus[clone] = FenceStatus{};
            }
        }
        else
        {
            fence = itr->second;
        }
    }

    // Update fence
    fence = GetActive_Fence(s_BufferingIdx, fence);

    // The fence must be unsignaled; this should only be possible in multi-frame
    // synchronization cases
    WaitForPendingFence(device, fence, "QueueSubmit2KHR");

    // Track the state of events within these command buffers
    HandleEvents(device, submitCount, pSubmits);

    // Helper generate patched queue submission parameters
    auto GenerateQueueSubmit2KHRParams = [&](uint32_t bufferingIndex, const OverrideKey& overrideKey) -> QueueSubmit2KHR_Params {
        // Local storage of submit information we are going to override
        std::vector<VkSubmitInfo2KHR> vecSubmits(pSubmits, pSubmits + submitCount);
        std::vector<std::vector<VkSemaphoreSubmitInfoKHR>> vecWaitSemaphoreInfos(submitCount);
        std::vector<std::vector<VkSemaphoreSubmitInfoKHR>> vecSignalSemaphores(submitCount);
        std::vector<std::vector<VkCommandBufferSubmitInfoKHR>> vecCommandBufferInfo(submitCount);

        // Patch up each submit
        for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
        {

            // Override command buffer based on swapchain usage
            for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferInfoCount; commandBufferIdx++)
            {
                VkCommandBufferSubmitInfoKHR commandBufferSubmitInfo = pSubmits[submitIdx].pCommandBufferInfos[commandBufferIdx];
                VkCommandBuffer activeCommandBuffer = GetActive_CommandBuffer(s_BufferingIdx, commandBufferSubmitInfo.commandBuffer);

                // Make sure this command buffer was re-recorded in frame if the option
                // is enabled.
                if (s_ForceResetCommandBuffers && !WasCommandBufferRecordedInFrame(commandBufferSubmitInfo.commandBuffer))
                {
                    auto itr = s_CommandBufferToRecordRev0.find(commandBufferSubmitInfo.commandBuffer);
                    NV_ASSERT(itr != s_CommandBufferToRecordRev0.end());
                    DoRecordCommandBuffer_Dispatch(GetThreadState().activeOverride, device, activeCommandBuffer, itr->second);
                }

                commandBufferSubmitInfo.commandBuffer = activeCommandBuffer;
                vecCommandBufferInfo[submitIdx].push_back(commandBufferSubmitInfo);
            }
            vecSubmits[submitIdx].commandBufferInfoCount = (uint32_t)vecCommandBufferInfo[submitIdx].size();
            vecSubmits[submitIdx].pCommandBufferInfos = vecCommandBufferInfo[submitIdx].data();

            // Clear signaled semaphores and trigger a hard wait on all pending semaphores
            // if we are being asked to wait on a semaphore we don't know about. This
            // indicates a dependent multi-frame synchronization event.
            if (!s_IgnoreSemaphores)
            {
                for (uint32_t waitSemaphoreIdx = 0; waitSemaphoreIdx < pSubmits[submitIdx].waitSemaphoreInfoCount; waitSemaphoreIdx++)
                {
                    VkSemaphoreSubmitInfoKHR waitSemaphoreInfo = pSubmits[submitIdx].pWaitSemaphoreInfos[waitSemaphoreIdx];
                    const SemaphoreInfo* pInfo = LookupSemaphoreInfo(waitSemaphoreInfo.semaphore);
                    waitSemaphoreInfo.semaphore = GetActive_Sempahore(bufferingIndex, waitSemaphoreInfo.semaphore);
#if defined(VK_KHR_timeline_semaphore)
                    if (pInfo->type == VK_SEMAPHORE_TYPE_BINARY_KHR)
                    {
                        SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(waitSemaphoreInfo.semaphore);
                        if (!semaphoreStatus.signaled)
                        {
                            // TODO: (DG-11075) Add paranoia mode to sync here
                        }
                        else
                        {
                            vecWaitSemaphoreInfos[submitIdx].push_back(waitSemaphoreInfo);
                            semaphoreStatus.signaled = false;
                        }
                    }
                    else if (pInfo->type == VK_SEMAPHORE_TYPE_TIMELINE_KHR)
                    {
                        if (waitSemaphoreInfo.value > pInfo->endValue)
                        {
                            NV_MESSAGE("WARNING: Timeline sempahore is waiting on value (%u) outside of frame (%u); work will never be submitted", waitSemaphoreInfo.value, pInfo->endValue);
                        }
                        if (IsAvailableForTimelineWait(pInfo, waitSemaphoreInfo.value))
                        {
                            waitSemaphoreInfo.value += (s_FrameIdx * pInfo->delta);
                            vecWaitSemaphoreInfos[submitIdx].push_back(waitSemaphoreInfo);
                        }
                    }
#else
                    SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(waitSemaphoreInfo.semaphore);
                    if (semaphoreStatus.signaled)
                    {
                        vecWaitSemaphoreInfos[submitIdx].push_back(waitSemaphoreInfo);
                        semaphoreStatus.signaled = false;
                    }
#endif
                }
            }
            vecSubmits[submitIdx].waitSemaphoreInfoCount = (uint32_t)vecWaitSemaphoreInfos[submitIdx].size();
            vecSubmits[submitIdx].pWaitSemaphoreInfos = vecWaitSemaphoreInfos[submitIdx].data();

            // Patch up signal semaphores to remove ones that are already signaled
            if (!s_IgnoreSemaphores)
            {
                for (uint32_t signalSemaphoreIdx = 0; signalSemaphoreIdx < pSubmits[submitIdx].signalSemaphoreInfoCount; signalSemaphoreIdx++)
                {
                    VkSemaphoreSubmitInfoKHR signalSemaphoreInfo = pSubmits[submitIdx].pSignalSemaphoreInfos[signalSemaphoreIdx];
                    SemaphoreInfo* pInfo = LookupSemaphoreInfo(signalSemaphoreInfo.semaphore);
                    signalSemaphoreInfo.semaphore = GetActive_Sempahore(bufferingIndex, signalSemaphoreInfo.semaphore);
#if defined(VK_KHR_timeline_semaphore)
                    if (pInfo->type == VK_SEMAPHORE_TYPE_BINARY_KHR)
                    {
                        SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(signalSemaphoreInfo.semaphore);
                        if (semaphoreStatus.signaled)
                        {
                            // TODO: (DG-11075) Add paranoia mode to sync here
                        }
                        else
                        {
                            vecSignalSemaphores[submitIdx].push_back(signalSemaphoreInfo);
                            semaphoreStatus.signaled = true;
                            semaphoreStatus.lastSignaledFrame = s_FrameIdx;
                        }
                    }
                    else if (pInfo->type == VK_SEMAPHORE_TYPE_TIMELINE_KHR)
                    {
                        RecordTimelineSignal(pInfo, signalSemaphoreInfo.value);
                        signalSemaphoreInfo.value += (s_FrameIdx * pInfo->delta);
                        vecSignalSemaphores[submitIdx].push_back(signalSemaphoreInfo);
                        pInfo->value = signalSemaphoreInfo.value;
                    }
#else
                    SemaphoreStatus& semaphoreStatus = GetSempahoreStatus(signalSemaphoreInfo.semaphore);
                    if (!semaphoreStatus.signaled)
                    {
                        vecSignalSemaphores[submitIdx].push_back(signalSemaphoreInfo);
                        semaphoreStatus.signaled = true;
                        semaphoreStatus.lastSignaledFrame = s_FrameIdx;
                    }
#endif
                }
            }
            vecSubmits[submitIdx].signalSemaphoreInfoCount = static_cast<uint32_t>(vecSignalSemaphores[submitIdx].size());
            vecSubmits[submitIdx].pSignalSemaphoreInfos = vecSignalSemaphores[submitIdx].data();
        }

        // Fences associated with this command buffer to so that we don't resubmit during capture
        if (fence != VK_NULL_HANDLE)
        {
            for (const auto& vecCommandBuffers_PerSubmit : vecCommandBufferInfo)
            {
                for (const VkCommandBufferSubmitInfoKHR& commandBufferSubmitInfo : vecCommandBuffers_PerSubmit)
                {
                    s_CommandBufferToFence[commandBufferSubmitInfo.commandBuffer] = fence;
                }
            }
        }

        // Patch up each submit
        for (uint32_t submitIdx = 0; submitIdx < submitCount; submitIdx++)
        {
            for (uint32_t commandBufferIdx = 0; commandBufferIdx < pSubmits[submitIdx].commandBufferInfoCount; commandBufferIdx++)
            {
                const VkCommandBuffer commandBuffer = pSubmits[submitIdx].pCommandBufferInfos[commandBufferIdx].commandBuffer;
                auto itr = s_CommandBufferToQueryPoolReset.find(commandBuffer);
                if (itr != s_CommandBufferToQueryPoolReset.end())
                {
                    s_QueryPoolResetInFrame.insert(itr->second);
                }
            }
        }

        // Helper do a
        return QueueSubmit2KHR_Params(*s_HostAllocators[device], queue, submitCount, vecSubmits.data(), fence);
    };

    const QueueSubmit2KHR_Params params = GenerateQueueSubmit2KHRParams(s_BufferingIdx, tls.activeOverride);

    // Wait for all async command buffer recording to finish
    for (uint32_t submitIdx = 0; submitIdx < params.submitCount; ++submitIdx)
    {
        const VkSubmitInfo2KHR& submitInfo = params.pSubmits[submitIdx];
        for (uint32_t cmdBufferIdx = 0; cmdBufferIdx < submitInfo.commandBufferInfoCount; ++cmdBufferIdx)
        {
            VkCommandBuffer cmdBuffer = submitInfo.pCommandBufferInfos[cmdBufferIdx].commandBuffer;
            WaitForCommandBufferRecord(cmdBuffer);
        }
    }

    VkResult result = fn(params.queue, params.submitCount, params.pSubmits, params.fence);
    s_SubmitIdx++;

    // In flight fence
    if (fence != VK_NULL_HANDLE)
    {
        GetFenceStatus(fence).signaled = true;
    }

    // Optionally wait immediately after every submit
    if (s_SyncAfterSumbit)
    {
        VkResult syncResult = vkQueueWaitIdle(params.queue);
        NV_VK_VALIDATE(syncResult)
    }

    return NV_VK_VALIDATE(result);
}
#endif

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_QueueSubmit2
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueueSubmit2(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2* pSubmits, VkFence fence)
{
    return DoQueueSubmit2(queue, submitCount, pSubmits, fence, &vkQueueSubmit2);
}
#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_QueueSubmit2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_QueueSubmit2KHR(VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence)
{
    return DoQueueSubmit2(queue, submitCount, pSubmits, fence, &vkQueueSubmit2KHR);
}
#endif // VK_KHR_synchronization2

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteTimestamp2
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteTimestamp2(VkCommandBuffer commandBuffer, VkPipelineStageFlags2 stage, VkQueryPool queryPool, uint32_t query)
{
    vkCmdWriteTimestamp2(commandBuffer, stage, queryPool, query);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_synchronization2)
//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteTimestamp2KHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteTimestamp2KHR(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkQueryPool queryPool, uint32_t query)
{
    vkCmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteBufferMarker2AMD
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteBufferMarker2AMD(VkCommandBuffer commandBuffer, VkPipelineStageFlags2KHR stage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker)
{
    vkCmdWriteBufferMarker2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetQueueCheckpointData2NV
//------------------------------------------------------------------------------
void VulkanReplay_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkGetQueueCheckpointData2NV(queue, pCheckpointDataCount, pCheckpointData);
}

#endif // VK_KHR_synchronization2

#if defined(VKSC_VERSION_1_0)
//------------------------------------------------------------------------------
// VulkanReplay_GetCommandPoolMemoryConsumption
//------------------------------------------------------------------------------
void VulkanReplay_GetCommandPoolMemoryConsumption(VkDevice device, VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkCommandPoolMemoryConsumption* pConsumption)
{
    vkGetCommandPoolMemoryConsumption(device, commandPool, commandBuffer, pConsumption);
}

#endif // VKSC_VERSION_1_0

#if defined(VK_KHR_video_queue)
//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceVideoCapabilitiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceVideoCapabilitiesKHR(physicalDevice, pVideoProfile, pCapabilities));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceVideoFormatPropertiesKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetPhysicalDeviceVideoFormatPropertiesKHR(physicalDevice, pVideoFormatInfo, pVideoFormatPropertyCount, pVideoFormatProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateVideoSessionKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession)
{
    return NV_VK_VALIDATE(vkCreateVideoSessionKHR(device, pCreateInfo, pAllocator, pVideoSession));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyVideoSessionKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyVideoSessionKHR(device, videoSession, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateVideoSessionParametersKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters)
{
    return NV_VK_VALIDATE(vkCreateVideoSessionParametersKHR(device, pCreateInfo, pAllocator, pVideoSessionParameters));
}

//------------------------------------------------------------------------------
// VulkanReplay_UpdateVideoSessionParametersKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo)
{
    return NV_VK_VALIDATE(vkUpdateVideoSessionParametersKHR(device, videoSessionParameters, pUpdateInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyVideoSessionParametersKHR
//------------------------------------------------------------------------------
void VulkanReplay_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyVideoSessionParametersKHR(device, videoSessionParameters, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetVideoSessionMemoryRequirementsKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements)
{
    // Ignore during frame loop; just a query
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkGetVideoSessionMemoryRequirementsKHR(device, videoSession, pMemoryRequirementsCount, pMemoryRequirements));
}

//------------------------------------------------------------------------------
// VulkanReplay_BindVideoSessionMemoryKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos)
{
    return NV_VK_VALIDATE(vkBindVideoSessionMemoryKHR(device, videoSession, bindSessionMemoryInfoCount, pBindSessionMemoryInfos));
}

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_decode_queue)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDecodeVideoKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo)
{
    vkCmdDecodeVideoKHR(commandBuffer, pDecodeInfo);
}

#endif // VK_KHR_video_decode_queue

#if defined(VK_KHR_video_queue)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginVideoCodingKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo)
{
    vkCmdBeginVideoCodingKHR(commandBuffer, pBeginInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdControlVideoCodingKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo)
{
    vkCmdControlVideoCodingKHR(commandBuffer, pCodingControlInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdEndVideoCodingKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo)
{
    vkCmdEndVideoCodingKHR(commandBuffer, pEndCodingInfo);
}

#endif // VK_KHR_video_queue

#if defined(VK_KHR_video_encode_queue)
//------------------------------------------------------------------------------
// VulkanReplay_CmdEncodeVideoKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo)
{
    vkCmdEncodeVideoKHR(commandBuffer, pEncodeInfo);
}

#endif // VK_KHR_video_encode_queue

#if defined(VK_NV_memory_decompression)
//------------------------------------------------------------------------------
// VulkanReplay_CmdDecompressMemoryNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions)
{
    vkCmdDecompressMemoryNV(commandBuffer, decompressRegionCount, pDecompressMemoryRegions);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdDecompressMemoryIndirectCountNV
//------------------------------------------------------------------------------
void VulkanReplay_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride)
{
    vkCmdDecompressMemoryIndirectCountNV(commandBuffer, indirectCommandsAddress, indirectCommandsCountAddress, stride);
}

#endif // VK_NV_memory_decompression

#if defined(VK_NVX_binary_import)
//------------------------------------------------------------------------------
// VulkanReplay_CreateCuModuleNVX
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateCuModuleNVX(device, pCreateInfo, pAllocator, pModule));
}

//------------------------------------------------------------------------------
// VulkanReplay_CreateCuFunctionNVX
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return VK_SUCCESS;
    }

    return NV_VK_VALIDATE(vkCreateCuFunctionNVX(device, pCreateInfo, pAllocator, pFunction));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyCuModuleNVX
//------------------------------------------------------------------------------
void VulkanReplay_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyCuModuleNVX(device, module, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyCuFunctionNVX
//------------------------------------------------------------------------------
void VulkanReplay_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyCuFunctionNVX(device, function, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCuLaunchKernelNVX
//------------------------------------------------------------------------------
void VulkanReplay_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo)
{
    vkCmdCuLaunchKernelNVX(commandBuffer, pLaunchInfo);
}

#endif // VK_NVX_binary_import

#if defined(VK_EXT_descriptor_buffer)
//------------------------------------------------------------------------------
// VulkanReplay_GetDescriptorSetLayoutSizeEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes)
{
    vkGetDescriptorSetLayoutSizeEXT(device, layout, pLayoutSizeInBytes);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDescriptorSetLayoutBindingOffsetEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset)
{
    vkGetDescriptorSetLayoutBindingOffsetEXT(device, layout, binding, pOffset);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDescriptorEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor)
{
    // Ignore during replay
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkGetDescriptorEXT(device, pDescriptorInfo, dataSize, pDescriptor);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindDescriptorBuffersEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos)
{
    vkCmdBindDescriptorBuffersEXT(commandBuffer, bufferCount, pBindingInfos);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdSetDescriptorBufferOffsetsEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets)
{
    vkCmdSetDescriptorBufferOffsetsEXT(commandBuffer, pipelineBindPoint, layout, firstSet, setCount, pBufferIndices, pOffsets);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindDescriptorBufferEmbeddedSamplersEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set)
{
    vkCmdBindDescriptorBufferEmbeddedSamplersEXT(commandBuffer, pipelineBindPoint, layout, set);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetBufferOpaqueCaptureDescriptorDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    return NV_VK_VALIDATE(vkGetBufferOpaqueCaptureDescriptorDataEXT(device, pInfo, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetImageOpaqueCaptureDescriptorDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    return NV_VK_VALIDATE(vkGetImageOpaqueCaptureDescriptorDataEXT(device, pInfo, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetImageViewOpaqueCaptureDescriptorDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    return NV_VK_VALIDATE(vkGetImageViewOpaqueCaptureDescriptorDataEXT(device, pInfo, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetSamplerOpaqueCaptureDescriptorDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    return NV_VK_VALIDATE(vkGetSamplerOpaqueCaptureDescriptorDataEXT(device, pInfo, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData)
{
    return NV_VK_VALIDATE(vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(device, pInfo, pData));
}

#endif // VK_EXT_descriptor_buffer

#if defined(VK_EXT_pageable_device_local_memory)
//------------------------------------------------------------------------------
// VulkanReplay_SetDeviceMemoryPriorityEXT
//------------------------------------------------------------------------------
void VulkanReplay_SetDeviceMemoryPriorityEXT(VkDevice device, VkDeviceMemory memory, float priority)
{
    vkSetDeviceMemoryPriorityEXT(device, memory, priority);
}

#endif // VK_EXT_pageable_device_local_memory

#if defined(VK_KHR_present_wait)
//------------------------------------------------------------------------------
// VulkanReplay_WaitForPresentKHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout)
{
    // For a single frame replay, there is nothing to wait on.
    return VK_SUCCESS;
}

#endif // VK_KHR_present_wait

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginRendering
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginRendering(VkCommandBuffer commandBuffer, const VkRenderingInfo* pRenderingInfo)
{
    vkCmdBeginRendering(commandBuffer, pRenderingInfo);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
//------------------------------------------------------------------------------
// VulkanReplay_CmdBeginRenderingKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdBeginRenderingKHR(VkCommandBuffer commandBuffer, const VkRenderingInfoKHR* pRenderingInfo)
{
    auto& tls = GetThreadState();

    VkRenderingInfoKHR renderingInfo = *pRenderingInfo;
    std::vector<VkRenderingAttachmentInfoKHR> vecColorInfo(pRenderingInfo->pColorAttachments, pRenderingInfo->pColorAttachments + pRenderingInfo->colorAttachmentCount);
    for (VkRenderingAttachmentInfoKHR& colorInfo : vecColorInfo)
    {
        colorInfo.imageView = GetActive_ImageView(tls.activeOverride, colorInfo.imageView);
    }
    renderingInfo.colorAttachmentCount = static_cast<uint32_t>(vecColorInfo.size());
    renderingInfo.pColorAttachments = vecColorInfo.data();

    VkRenderingAttachmentInfoKHR depthInfo = {};
    if (pRenderingInfo->pDepthAttachment)
    {
        depthInfo = *pRenderingInfo->pDepthAttachment;
        depthInfo.imageView = GetActive_ImageView(tls.activeOverride, depthInfo.imageView);
        renderingInfo.pDepthAttachment = &depthInfo;
    }
    VkRenderingAttachmentInfoKHR stencilInfo = {};
    if (pRenderingInfo->pStencilAttachment)
    {
        stencilInfo = *pRenderingInfo->pStencilAttachment;
        stencilInfo.imageView = GetActive_ImageView(tls.activeOverride, stencilInfo.imageView);
        renderingInfo.pStencilAttachment = &stencilInfo;
    }

    vkCmdBeginRenderingKHR(commandBuffer, &renderingInfo);
}

#endif // VK_KHR_dynamic_rendering

#if defined(VK_VERSION_1_3)
//------------------------------------------------------------------------------
// VulkanReplay_CmdEndRendering
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndRendering(VkCommandBuffer commandBuffer)
{
    vkCmdEndRendering(commandBuffer);
}

#endif // VK_VERSION_1_3

#if defined(VK_KHR_dynamic_rendering)
//------------------------------------------------------------------------------
// VulkanReplay_CmdEndRenderingKHR
//------------------------------------------------------------------------------
void VulkanReplay_CmdEndRenderingKHR(VkCommandBuffer commandBuffer)
{
    vkCmdEndRenderingKHR(commandBuffer);
}

#endif // VK_KHR_dynamic_rendering

#if defined(VK_EXT_opacity_micromap)
//------------------------------------------------------------------------------
// VulkanReplay_CreateMicromapEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateMicromapEXT(VkDevice device, const VkMicromapCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkMicromapEXT* pMicromap)
{
    return NV_VK_VALIDATE(vkCreateMicromapEXT(device, pCreateInfo, pAllocator, pMicromap));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBuildMicromapsEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBuildMicromapsEXT(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos)
{
    // On the first frame we can muck with recording information
    const VkDevice device = s_CommandBufferToDeviceMap[commandBuffer];

    for (uint32_t infoIdx = 0; infoIdx < infoCount; infoIdx++)
    {
        // We own pInfos in the layer above so we are free to copy without making a local copy
        VkMicromapBuildInfoEXT& info = const_cast<VkMicromapBuildInfoEXT&>(pInfos[infoIdx]);

        // We only need to perform this one time update once
        VULKAN_REPLAY_WRITE_LOCK();

        static std::set<const VkMicromapBuildInfoEXT*> k_HasUpdatedInfo;
        if (k_HasUpdatedInfo.find(&info) != k_HasUpdatedInfo.end())
        {
            continue;
        }
        else
        {
            k_HasUpdatedInfo.insert(&info);
        }

        s_BufferAddressManager.RemapCaptureAddressForReplay(device, info.data.deviceAddress);
        s_BufferAddressManager.RemapCaptureAddressForReplay(device, info.scratchData.deviceAddress);
        s_BufferAddressManager.RemapCaptureAddressForReplay(device, info.triangleArray.deviceAddress);
    }

    vkCmdBuildMicromapsEXT(commandBuffer, infoCount, pInfos);
}

//------------------------------------------------------------------------------
// VulkanReplay_BuildMicromapsEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_BuildMicromapsEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkMicromapBuildInfoEXT* pInfos)
{
    return NV_VK_VALIDATE(vkBuildMicromapsEXT(device, deferredOperation, infoCount, pInfos));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyMicromapEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyMicromapEXT(VkDevice device, VkMicromapEXT micromap, const VkAllocationCallbacks* pAllocator)
{
    // Ignore during frame loop
    if (s_ReplayPhase == VulkanReplayPhase::Frame)
    {
        return;
    }

    vkDestroyMicromapEXT(device, micromap, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMicromapEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT* pInfo)
{
    vkCmdCopyMicromapEXT(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyMicromapEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT* pInfo)
{
    return NV_VK_VALIDATE(vkCopyMicromapEXT(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMicromapToMemoryEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMicromapToMemoryEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo)
{
    vkCmdCopyMicromapToMemoryEXT(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyMicromapToMemoryEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyMicromapToMemoryEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT* pInfo)
{
    return NV_VK_VALIDATE(vkCopyMicromapToMemoryEXT(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdCopyMemoryToMicromapEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdCopyMemoryToMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo)
{
    vkCmdCopyMemoryToMicromapEXT(commandBuffer, pInfo);
}

//------------------------------------------------------------------------------
// VulkanReplay_CopyMemoryToMicromapEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CopyMemoryToMicromapEXT(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT* pInfo)
{
    return NV_VK_VALIDATE(vkCopyMemoryToMicromapEXT(device, deferredOperation, pInfo));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdWriteMicromapsPropertiesEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery)
{
    vkCmdWriteMicromapsPropertiesEXT(commandBuffer, micromapCount, pMicromaps, queryType, queryPool, firstQuery);
}

//------------------------------------------------------------------------------
// VulkanReplay_WriteMicromapsPropertiesEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_WriteMicromapsPropertiesEXT(VkDevice device, uint32_t micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType queryType, size_t dataSize, void* pData, size_t stride)
{
    return NV_VK_VALIDATE(vkWriteMicromapsPropertiesEXT(device, micromapCount, pMicromaps, queryType, dataSize, pData, stride));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceMicromapCompatibilityEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetDeviceMicromapCompatibilityEXT(VkDevice device, const VkMicromapVersionInfoEXT* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility)
{
    vkGetDeviceMicromapCompatibilityEXT(device, pVersionInfo, pCompatibility);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetMicromapBuildSizesEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetMicromapBuildSizesEXT(VkDevice device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT* pBuildInfo, VkMicromapBuildSizesInfoEXT* pSizeInfo)
{
    vkGetMicromapBuildSizesEXT(device, buildType, pBuildInfo, pSizeInfo);
}

#endif // VK_EXT_opacity_micromap

#if defined(VK_EXT_shader_module_identifier)
//------------------------------------------------------------------------------
// VulkanReplay_GetShaderModuleIdentifierEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier)
{
    vkGetShaderModuleIdentifierEXT(device, shaderModule, pIdentifier);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetShaderModuleCreateInfoIdentifierEXT
//------------------------------------------------------------------------------
void VulkanReplay_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier)
{
    vkGetShaderModuleCreateInfoIdentifierEXT(device, pCreateInfo, pIdentifier);
}

#endif // VK_EXT_shader_module_identifier

#if defined(VK_EXT_image_compression_control)
//------------------------------------------------------------------------------
// VulkanReplay_GetImageSubresourceLayout2EXT
//------------------------------------------------------------------------------
void VulkanReplay_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2EXT* pSubresource, VkSubresourceLayout2EXT* pLayout)
{
    vkGetImageSubresourceLayout2EXT(device, image, pSubresource, pLayout);
}

#endif // VK_EXT_image_compression_control

#if defined(VK_EXT_device_fault)
//------------------------------------------------------------------------------
// VulkanReplay_GetDeviceFaultInfoEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo)
{
    return NV_VK_VALIDATE(vkGetDeviceFaultInfoEXT(device, pFaultCounts, pFaultInfo));
}

#endif // VK_EXT_device_fault

#if defined(VK_EXT_swapchain_maintenance1)
//------------------------------------------------------------------------------
// VulkanReplay_ReleaseSwapchainImagesEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoEXT* pReleaseInfo)
{
    return NV_VK_VALIDATE(vkReleaseSwapchainImagesEXT(device, pReleaseInfo));
}

#endif // VK_EXT_swapchain_maintenance1

#if defined(VK_KHR_map_memory2)
//------------------------------------------------------------------------------
// VulkanReplay_MapMemory2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_MapMemory2KHR(VkDevice device, const VkMemoryMapInfoKHR* pMemoryMapInfo, void** ppData)
{
    return NV_VK_VALIDATE(vkMapMemory2KHR(device, pMemoryMapInfo, ppData));
}

//------------------------------------------------------------------------------
// VulkanReplay_UnmapMemory2KHR
//------------------------------------------------------------------------------
VkResult VulkanReplay_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfoKHR* pMemoryUnmapInfo)
{
    return NV_VK_VALIDATE(vkUnmapMemory2KHR(device, pMemoryUnmapInfo));
}

#endif // VK_KHR_map_memory2

#if defined(VK_EXT_shader_object)
//------------------------------------------------------------------------------
// VulkanReplay_CreateShadersEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders)
{
    return NV_VK_VALIDATE(vkCreateShadersEXT(device, createInfoCount, pCreateInfos, pAllocator, pShaders));
}

//------------------------------------------------------------------------------
// VulkanReplay_DestroyShaderEXT
//------------------------------------------------------------------------------
void VulkanReplay_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator)
{
    vkDestroyShaderEXT(device, shader, pAllocator);
}

//------------------------------------------------------------------------------
// VulkanReplay_GetShaderBinaryDataEXT
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData)
{
    return NV_VK_VALIDATE(vkGetShaderBinaryDataEXT(device, shader, pDataSize, pData));
}

//------------------------------------------------------------------------------
// VulkanReplay_CmdBindShadersEXT
//------------------------------------------------------------------------------
void VulkanReplay_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders)
{
    vkCmdBindShadersEXT(commandBuffer, stageCount, pStages, pShaders);
}

#endif // VK_EXT_shader_object

#if defined(VK_NV_external_memory_sci_buf)
//------------------------------------------------------------------------------
// VulkanReplay_GetMemorySciBufNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetMemorySciBufNV(VkDevice device, const VkMemoryGetSciBufInfoNV* pGetSciBufInfo, NvSciBufObj* pHandle)
{
    return NV_VK_VALIDATE(vkGetMemorySciBufNV(device, pGetSciBufInfo, pHandle));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceExternalMemorySciBufPropertiesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceExternalMemorySciBufPropertiesNV(VkPhysicalDevice physicalDevice, VkExternalMemoryHandleTypeFlagBits handleType, NvSciBufObj handle, VkMemorySciBufPropertiesNV* pMemorySciBufProperties)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV(physicalDevice, handleType, handle, pMemorySciBufProperties));
}

//------------------------------------------------------------------------------
// VulkanReplay_GetPhysicalDeviceSciBufAttributesNV
//------------------------------------------------------------------------------
VkResult VulkanReplay_GetPhysicalDeviceSciBufAttributesNV(VkPhysicalDevice physicalDevice, NvSciBufAttrList pAttributes)
{
    return NV_VK_VALIDATE(vkGetPhysicalDeviceSciBufAttributesNV(physicalDevice, pAttributes));
}

#endif // VK_NV_external_memory_sci_buf
