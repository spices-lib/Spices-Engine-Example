//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Resources00.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <vulkan/vulkan.h>

#include "VulkanHelpers.h"
#include "VulkanReplay.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "WindowSystem.h"

NV_REPLAY_BEGIN_RESOURCE_INIT()

//-----------------------------------------------------------------------------
// CreateResources00
//-----------------------------------------------------------------------------
void CreateResources00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    NV_MESSAGE_VERBOSE("Creating resources...");

    // Create VkInstance_uid_1
    {
        static VkDebugUtilsMessengerCreateInfoEXT VkDebugUtilsMessengerCreateInfoEXT_pNext_2[1] = { VkDebugUtilsMessengerCreateInfoEXT{
        /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        /* pNext = */ nullptr,
        /* flags = */ VkDebugUtilsMessengerCreateFlagsEXT(0),
        /* messageSeverity = */ VkDebugUtilsMessageSeverityFlagsEXT(VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT),
        /* messageType = */ VkDebugUtilsMessageTypeFlagsEXT(VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT),
        /* pfnUserCallback = */ NV_VK_FUNCTION_PTR,
        /* pUserData = */ NV_VK_USER_PTR} };
        static VkApplicationInfo VkApplicationInfo_pApplicationInfo_2[1] = { VkApplicationInfo{
        /* sType = */ VK_STRUCTURE_TYPE_APPLICATION_INFO,
        /* pNext = */ nullptr,
        /* pApplicationName = */ "app",
        /* applicationVersion = */ 4194304u,
        /* pEngineName = */ "engine",
        /* engineVersion = */ 4194304u,
        /* apiVersion = */ VK_MAKE_API_VERSION(0, 1, 3, 0)} };
        static const char* pconstchar_ppEnabledLayerNames_5[1] = { "VK_LAYER_KHRONOS_validation" };
        static const char* pconstchar_ppEnabledExtensionNames_6[3] = { "VK_KHR_surface", "VK_KHR_win32_surface", "VK_EXT_debug_utils" };
        static VkInstanceCreateInfo VkInstanceCreateInfo_temp_2[1] = { VkInstanceCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        /* pNext = */ VkDebugUtilsMessengerCreateInfoEXT_pNext_2,
        /* flags = */ VkInstanceCreateFlags(0),
        /* pApplicationInfo = */ VkApplicationInfo_pApplicationInfo_2,
        /* enabledLayerCount = */ 1u,
        /* ppEnabledLayerNames = */ pconstchar_ppEnabledLayerNames_5,
        /* enabledExtensionCount = */ 3u,
        /* ppEnabledExtensionNames = */ pconstchar_ppEnabledExtensionNames_6} };
        NV_VK_REPLAY(VulkanReplay_CreateInstance(VkInstanceCreateInfo_temp_2, nullptr, &VkInstance_uid_1));
    }

    // Create VkPhysicalDevice_uid_2
    {
        static VkPhysicalDeviceProperties VkPhysicalDeviceProperties_temp_2 = VkPhysicalDeviceProperties{
        /* apiVersion = */ VK_MAKE_API_VERSION(0, 1, 3, 278),
        /* driverVersion = */ 2329460736u,
        /* vendorID = */ 4318u,
        /* deviceID = */ 10370u,
        /* deviceType = */ VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,
        /* deviceName = */ "NVIDIA GeForce RTX 4060",
        /* pipelineCacheUUID = */ NV_TO_ARRAY(50, 65, 160, 100, 137, 67, 190, 234, 89, 142, 23, 132, 16, 245, 81, 3),
        /* limits = */ VkPhysicalDeviceLimits{
        /* maxImageDimension1D = */ 32768u,
        /* maxImageDimension2D = */ 32768u,
        /* maxImageDimension3D = */ 16384u,
        /* maxImageDimensionCube = */ 32768u,
        /* maxImageArrayLayers = */ 2048u,
        /* maxTexelBufferElements = */ 134217728u,
        /* maxUniformBufferRange = */ 65536u,
        /* maxStorageBufferRange = */ 4294967295u,
        /* maxPushConstantsSize = */ 256u,
        /* maxMemoryAllocationCount = */ 4294967295u,
        /* maxSamplerAllocationCount = */ 4000u,
        /* bufferImageGranularity = */ 1024ull,
        /* sparseAddressSpaceSize = */ 1099511627776ull,
        /* maxBoundDescriptorSets = */ 32u,
        /* maxPerStageDescriptorSamplers = */ 1048576u,
        /* maxPerStageDescriptorUniformBuffers = */ 1048576u,
        /* maxPerStageDescriptorStorageBuffers = */ 1048576u,
        /* maxPerStageDescriptorSampledImages = */ 1048576u,
        /* maxPerStageDescriptorStorageImages = */ 1048576u,
        /* maxPerStageDescriptorInputAttachments = */ 1048576u,
        /* maxPerStageResources = */ 4294967295u,
        /* maxDescriptorSetSamplers = */ 1048576u,
        /* maxDescriptorSetUniformBuffers = */ 1048576u,
        /* maxDescriptorSetUniformBuffersDynamic = */ 15u,
        /* maxDescriptorSetStorageBuffers = */ 1048576u,
        /* maxDescriptorSetStorageBuffersDynamic = */ 16u,
        /* maxDescriptorSetSampledImages = */ 1048576u,
        /* maxDescriptorSetStorageImages = */ 1048576u,
        /* maxDescriptorSetInputAttachments = */ 1048576u,
        /* maxVertexInputAttributes = */ 32u,
        /* maxVertexInputBindings = */ 32u,
        /* maxVertexInputAttributeOffset = */ 2047u,
        /* maxVertexInputBindingStride = */ 2048u,
        /* maxVertexOutputComponents = */ 128u,
        /* maxTessellationGenerationLevel = */ 64u,
        /* maxTessellationPatchSize = */ 32u,
        /* maxTessellationControlPerVertexInputComponents = */ 128u,
        /* maxTessellationControlPerVertexOutputComponents = */ 128u,
        /* maxTessellationControlPerPatchOutputComponents = */ 120u,
        /* maxTessellationControlTotalOutputComponents = */ 4216u,
        /* maxTessellationEvaluationInputComponents = */ 128u,
        /* maxTessellationEvaluationOutputComponents = */ 128u,
        /* maxGeometryShaderInvocations = */ 32u,
        /* maxGeometryInputComponents = */ 128u,
        /* maxGeometryOutputComponents = */ 128u,
        /* maxGeometryOutputVertices = */ 1024u,
        /* maxGeometryTotalOutputComponents = */ 1024u,
        /* maxFragmentInputComponents = */ 128u,
        /* maxFragmentOutputAttachments = */ 8u,
        /* maxFragmentDualSrcAttachments = */ 1u,
        /* maxFragmentCombinedOutputResources = */ 4294967295u,
        /* maxComputeSharedMemorySize = */ 49152u,
        /* maxComputeWorkGroupCount = */ NV_TO_ARRAY(2147483647u, 65535u, 65535u),
        /* maxComputeWorkGroupInvocations = */ 1024u,
        /* maxComputeWorkGroupSize = */ NV_TO_ARRAY(1024u, 1024u, 64u),
        /* subPixelPrecisionBits = */ 8u,
        /* subTexelPrecisionBits = */ 8u,
        /* mipmapPrecisionBits = */ 8u,
        /* maxDrawIndexedIndexValue = */ 4294967295u,
        /* maxDrawIndirectCount = */ 4294967295u,
        /* maxSamplerLodBias = */ HexToFloat(0x41700000/*15.0f*/),
        /* maxSamplerAnisotropy = */ HexToFloat(0x41800000/*16.0f*/),
        /* maxViewports = */ 16u,
        /* maxViewportDimensions = */ NV_TO_ARRAY(32768u, 32768u),
        /* viewportBoundsRange = */ NV_TO_ARRAY(HexToFloat(0xC7800000/*-65536.0f*/), HexToFloat(0x47800000/*65536.0f*/)),
        /* viewportSubPixelBits = */ 8u,
        /* minMemoryMapAlignment = */ 64ull,
        /* minTexelBufferOffsetAlignment = */ 16ull,
        /* minUniformBufferOffsetAlignment = */ 64ull,
        /* minStorageBufferOffsetAlignment = */ 16ull,
        /* minTexelOffset = */ -8,
        /* maxTexelOffset = */ 7u,
        /* minTexelGatherOffset = */ -32,
        /* maxTexelGatherOffset = */ 31u,
        /* minInterpolationOffset = */ HexToFloat(0xBF000000/*-0.5f*/),
        /* maxInterpolationOffset = */ HexToFloat(0x3EE00000/*0.4375f*/),
        /* subPixelInterpolationOffsetBits = */ 4u,
        /* maxFramebufferWidth = */ 32768u,
        /* maxFramebufferHeight = */ 32768u,
        /* maxFramebufferLayers = */ 2048u,
        /* framebufferColorSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* framebufferDepthSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* framebufferStencilSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT | VK_SAMPLE_COUNT_16_BIT),
        /* framebufferNoAttachmentsSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT | VK_SAMPLE_COUNT_16_BIT),
        /* maxColorAttachments = */ 8u,
        /* sampledImageColorSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* sampledImageIntegerSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* sampledImageDepthSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* sampledImageStencilSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT | VK_SAMPLE_COUNT_16_BIT),
        /* storageImageSampleCounts = */ VkSampleCountFlags(VK_SAMPLE_COUNT_1_BIT | VK_SAMPLE_COUNT_2_BIT | VK_SAMPLE_COUNT_4_BIT | VK_SAMPLE_COUNT_8_BIT),
        /* maxSampleMaskWords = */ 1u,
        /* timestampComputeAndGraphics = */ 1u,
        /* timestampPeriod = */ HexToFloat(0x3F800000/*1.0f*/),
        /* maxClipDistances = */ 8u,
        /* maxCullDistances = */ 8u,
        /* maxCombinedClipAndCullDistances = */ 8u,
        /* discreteQueuePriorities = */ 2u,
        /* pointSizeRange = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x44FFFE00/*2047.94f*/)),
        /* lineWidthRange = */ NV_TO_ARRAY(HexToFloat(0x3F800000/*1.0f*/), HexToFloat(0x42800000/*64.0f*/)),
        /* pointSizeGranularity = */ HexToFloat(0x3D800000/*0.0625f*/),
        /* lineWidthGranularity = */ HexToFloat(0x3D800000/*0.0625f*/),
        /* strictLines = */ 1u,
        /* standardSampleLocations = */ 1u,
        /* optimalBufferCopyOffsetAlignment = */ 1ull,
        /* optimalBufferCopyRowPitchAlignment = */ 1ull,
        /* nonCoherentAtomSize = */ 64ull},
        /* sparseProperties = */ VkPhysicalDeviceSparseProperties{
        /* residencyStandard2DBlockShape = */ 1u,
        /* residencyStandard2DMultisampleBlockShape = */ 1u,
        /* residencyStandard3DBlockShape = */ 1u,
        /* residencyAlignedMipSize = */ 0u,
        /* residencyNonResidentStrict = */ 1u}};
        static VkQueueFamilyProperties VkQueueFamilyProperties_temp_2[6] = { VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT),
        /* queueCount = */ 16u,
        /* timestampValidBits = */ 64u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}}, VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT),
        /* queueCount = */ 2u,
        /* timestampValidBits = */ 64u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}}, VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT),
        /* queueCount = */ 8u,
        /* timestampValidBits = */ 64u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}}, VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT | VK_QUEUE_VIDEO_DECODE_BIT_KHR),
        /* queueCount = */ 1u,
        /* timestampValidBits = */ 32u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}}, VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT | 0x40),
        /* queueCount = */ 1u,
        /* timestampValidBits = */ 32u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}}, VkQueueFamilyProperties{
        /* queueFlags = */ VkQueueFlags(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT | 0x100),
        /* queueCount = */ 1u,
        /* timestampValidBits = */ 64u,
        /* minImageTransferGranularity = */ VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u}} };
        static VkPhysicalDeviceMemoryProperties VkPhysicalDeviceMemoryProperties_temp_2 = VkPhysicalDeviceMemoryProperties{
        /* memoryTypeCount = */ 5u,
        /* memoryTypes = */ NV_TO_ARRAY(VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 1u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
        /* heapIndex = */ 1u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT),
        /* heapIndex = */ 1u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}, VkMemoryType{
        /* propertyFlags = */ VkMemoryPropertyFlags(0),
        /* heapIndex = */ 0u}),
        /* memoryHeapCount = */ 2u,
        /* memoryHeaps = */ NV_TO_ARRAY(VkMemoryHeap{
        /* size = */ 8343519232ull,
        /* flags = */ VkMemoryHeapFlags(VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)}, VkMemoryHeap{
        /* size = */ 17081991168ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)}, VkMemoryHeap{
        /* size = */ 0ull,
        /* flags = */ VkMemoryHeapFlags(0)})};
        NV_VK_REPLAY(VulkanHelper_GetCompatiblePhysicalDevice(VkInstance_uid_1, 0u, VkPhysicalDeviceProperties_temp_2, 6u, VkQueueFamilyProperties_temp_2, VkPhysicalDeviceMemoryProperties_temp_2, &VkPhysicalDevice_uid_2));
    }

    // Create VkDevice_uid_4
    {
        static VkPhysicalDeviceShaderClockFeaturesKHR VkPhysicalDeviceShaderClockFeaturesKHR_pNext_2[1] = { VkPhysicalDeviceShaderClockFeaturesKHR{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CLOCK_FEATURES_KHR,
        /* pNext = */ nullptr,
        /* shaderSubgroupClock = */ 1u,
        /* shaderDeviceClock = */ 1u} };
        static VkPhysicalDeviceScalarBlockLayoutFeatures VkPhysicalDeviceScalarBlockLayoutFeatures_pNext_2[1] = { VkPhysicalDeviceScalarBlockLayoutFeatures{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SCALAR_BLOCK_LAYOUT_FEATURES,
        /* pNext = */ VkPhysicalDeviceShaderClockFeaturesKHR_pNext_2,
        /* scalarBlockLayout = */ 1u} };
        static VkPhysicalDeviceHostQueryResetFeatures VkPhysicalDeviceHostQueryResetFeatures_pNext_2[1] = { VkPhysicalDeviceHostQueryResetFeatures{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_HOST_QUERY_RESET_FEATURES,
        /* pNext = */ VkPhysicalDeviceScalarBlockLayoutFeatures_pNext_2,
        /* hostQueryReset = */ 1u} };
        static VkPhysicalDeviceRayTracingPipelineFeaturesKHR VkPhysicalDeviceRayTracingPipelineFeaturesKHR_pNext_2[1] = { VkPhysicalDeviceRayTracingPipelineFeaturesKHR{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
        /* pNext = */ VkPhysicalDeviceHostQueryResetFeatures_pNext_2,
        /* rayTracingPipeline = */ 1u,
        /* rayTracingPipelineShaderGroupHandleCaptureReplay = */ 0u,
        /* rayTracingPipelineShaderGroupHandleCaptureReplayMixed = */ 0u,
        /* rayTracingPipelineTraceRaysIndirect = */ 1u,
        /* rayTraversalPrimitiveCulling = */ 1u} };
        static VkPhysicalDeviceAccelerationStructureFeaturesKHR VkPhysicalDeviceAccelerationStructureFeaturesKHR_pNext_2[1] = { VkPhysicalDeviceAccelerationStructureFeaturesKHR{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR,
        /* pNext = */ VkPhysicalDeviceRayTracingPipelineFeaturesKHR_pNext_2,
        /* accelerationStructure = */ 1u,
        /* accelerationStructureCaptureReplay = */ 1u,
        /* accelerationStructureIndirectBuild = */ 0u,
        /* accelerationStructureHostCommands = */ 0u,
        /* descriptorBindingAccelerationStructureUpdateAfterBind = */ 1u} };
        static VkPhysicalDeviceDescriptorIndexingFeatures VkPhysicalDeviceDescriptorIndexingFeatures_pNext_2[1] = { VkPhysicalDeviceDescriptorIndexingFeatures{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
        /* pNext = */ VkPhysicalDeviceAccelerationStructureFeaturesKHR_pNext_2,
        /* shaderInputAttachmentArrayDynamicIndexing = */ 1u,
        /* shaderUniformTexelBufferArrayDynamicIndexing = */ 1u,
        /* shaderStorageTexelBufferArrayDynamicIndexing = */ 1u,
        /* shaderUniformBufferArrayNonUniformIndexing = */ 1u,
        /* shaderSampledImageArrayNonUniformIndexing = */ 1u,
        /* shaderStorageBufferArrayNonUniformIndexing = */ 1u,
        /* shaderStorageImageArrayNonUniformIndexing = */ 1u,
        /* shaderInputAttachmentArrayNonUniformIndexing = */ 1u,
        /* shaderUniformTexelBufferArrayNonUniformIndexing = */ 1u,
        /* shaderStorageTexelBufferArrayNonUniformIndexing = */ 1u,
        /* descriptorBindingUniformBufferUpdateAfterBind = */ 1u,
        /* descriptorBindingSampledImageUpdateAfterBind = */ 1u,
        /* descriptorBindingStorageImageUpdateAfterBind = */ 1u,
        /* descriptorBindingStorageBufferUpdateAfterBind = */ 1u,
        /* descriptorBindingUniformTexelBufferUpdateAfterBind = */ 1u,
        /* descriptorBindingStorageTexelBufferUpdateAfterBind = */ 1u,
        /* descriptorBindingUpdateUnusedWhilePending = */ 1u,
        /* descriptorBindingPartiallyBound = */ 1u,
        /* descriptorBindingVariableDescriptorCount = */ 1u,
        /* runtimeDescriptorArray = */ 1u} };
        static VkPhysicalDeviceBufferDeviceAddressFeatures VkPhysicalDeviceBufferDeviceAddressFeatures_pNext_2[1] = { VkPhysicalDeviceBufferDeviceAddressFeatures{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES,
        /* pNext = */ VkPhysicalDeviceDescriptorIndexingFeatures_pNext_2,
        /* bufferDeviceAddress = */ 1u,
        /* bufferDeviceAddressCaptureReplay = */ 1u,
        /* bufferDeviceAddressMultiDevice = */ 1u} };
        static VkPhysicalDeviceFeatures2 VkPhysicalDeviceFeatures2_pNext_2[1] = { VkPhysicalDeviceFeatures2{
        /* sType = */ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        /* pNext = */ VkPhysicalDeviceBufferDeviceAddressFeatures_pNext_2,
        /* features = */ VkPhysicalDeviceFeatures{
        /* robustBufferAccess = */ 1u,
        /* fullDrawIndexUint32 = */ 1u,
        /* imageCubeArray = */ 1u,
        /* independentBlend = */ 1u,
        /* geometryShader = */ 1u,
        /* tessellationShader = */ 1u,
        /* sampleRateShading = */ 1u,
        /* dualSrcBlend = */ 1u,
        /* logicOp = */ 1u,
        /* multiDrawIndirect = */ 1u,
        /* drawIndirectFirstInstance = */ 1u,
        /* depthClamp = */ 1u,
        /* depthBiasClamp = */ 1u,
        /* fillModeNonSolid = */ 1u,
        /* depthBounds = */ 1u,
        /* wideLines = */ 1u,
        /* largePoints = */ 1u,
        /* alphaToOne = */ 1u,
        /* multiViewport = */ 1u,
        /* samplerAnisotropy = */ 1u,
        /* textureCompressionETC2 = */ 0u,
        /* textureCompressionASTC_LDR = */ 0u,
        /* textureCompressionBC = */ 1u,
        /* occlusionQueryPrecise = */ 1u,
        /* pipelineStatisticsQuery = */ 1u,
        /* vertexPipelineStoresAndAtomics = */ 1u,
        /* fragmentStoresAndAtomics = */ 1u,
        /* shaderTessellationAndGeometryPointSize = */ 1u,
        /* shaderImageGatherExtended = */ 1u,
        /* shaderStorageImageExtendedFormats = */ 1u,
        /* shaderStorageImageMultisample = */ 1u,
        /* shaderStorageImageReadWithoutFormat = */ 1u,
        /* shaderStorageImageWriteWithoutFormat = */ 1u,
        /* shaderUniformBufferArrayDynamicIndexing = */ 1u,
        /* shaderSampledImageArrayDynamicIndexing = */ 1u,
        /* shaderStorageBufferArrayDynamicIndexing = */ 1u,
        /* shaderStorageImageArrayDynamicIndexing = */ 1u,
        /* shaderClipDistance = */ 1u,
        /* shaderCullDistance = */ 1u,
        /* shaderFloat64 = */ 1u,
        /* shaderInt64 = */ 1u,
        /* shaderInt16 = */ 1u,
        /* shaderResourceResidency = */ 1u,
        /* shaderResourceMinLod = */ 1u,
        /* sparseBinding = */ 1u,
        /* sparseResidencyBuffer = */ 1u,
        /* sparseResidencyImage2D = */ 1u,
        /* sparseResidencyImage3D = */ 1u,
        /* sparseResidency2Samples = */ 1u,
        /* sparseResidency4Samples = */ 1u,
        /* sparseResidency8Samples = */ 1u,
        /* sparseResidency16Samples = */ 1u,
        /* sparseResidencyAliased = */ 1u,
        /* variableMultisampleRate = */ 1u,
        /* inheritedQueries = */ 1u}} };
        static float float_pQueuePriorities_2[1] = { HexToFloat(0x3F800000/*1.0f*/) };
        static VkDeviceQueueCreateInfo VkDeviceQueueCreateInfo_pQueueCreateInfos_2[1] = { VkDeviceQueueCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkDeviceQueueCreateFlags(0),
        /* queueFamilyIndex = */ 0u,
        /* queueCount = */ 1u,
        /* pQueuePriorities = */ float_pQueuePriorities_2} };
        static const char* pconstchar_ppEnabledExtensionNames_8[7] = { "VK_KHR_swapchain", "VK_KHR_maintenance1", "VK_KHR_acceleration_structure", "VK_KHR_ray_tracing_pipeline", "VK_KHR_deferred_host_operations", "VK_KHR_shader_clock", "VK_KHR_shader_non_semantic_info" };
        static VkDeviceCreateInfo VkDeviceCreateInfo_temp_2[1] = { VkDeviceCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        /* pNext = */ VkPhysicalDeviceFeatures2_pNext_2,
        /* flags = */ VkDeviceCreateFlags(0),
        /* queueCreateInfoCount = */ 1u,
        /* pQueueCreateInfos = */ VkDeviceQueueCreateInfo_pQueueCreateInfos_2,
        /* enabledLayerCount = */ 0u,
        /* ppEnabledLayerNames = */ nullptr,
        /* enabledExtensionCount = */ 7u,
        /* ppEnabledExtensionNames = */ pconstchar_ppEnabledExtensionNames_8,
        /* pEnabledFeatures = */ nullptr} };
        NV_VK_REPLAY(VulkanReplay_CreateDevice(VkPhysicalDevice_uid_2, VkDeviceCreateInfo_temp_2, nullptr, &VkDevice_uid_4));
    }

    // Create VkQueue_uid_6
    {
        NV_VK_REPLAY(VulkanReplay_GetDeviceQueue(VkDevice_uid_4, 0u, 0u, &VkQueue_uid_6));
    }

    // Create VkSurfaceKHR_uid_3
    {
        {
            BEGIN_DATA_SCOPE();

            #if NV_USE_MANAGED_WINSYS
                WindowSystemInstance().CreateDisplay();
                WindowSystemInstance().CreateNativeWindow(2200, 1300);
                NV_VK_REPLAY(VulkanHelper_CreateWindowSystemSurface(VkInstance_uid_1, nullptr, &VkSurfaceKHR_uid_3));
#else

                static VkWin32SurfaceCreateInfoKHR VkWin32SurfaceCreateInfoKHR_temp_2[1] = { VkWin32SurfaceCreateInfoKHR{
                /* sType = */ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
                /* pNext = */ nullptr,
                /* flags = */ VkWin32SurfaceCreateFlagsKHR(0),
                /* hinstance = */ currentInstance,
                /* hwnd = */ hwnd_00000000002F0AAC} };
                NV_VK_REPLAY(VulkanReplay_CreateWin32SurfaceKHR(VkInstance_uid_1, VkWin32SurfaceCreateInfoKHR_temp_2, nullptr, &VkSurfaceKHR_uid_3));
                #endif
        }
    }

    // Create VkSwapchainKHR_uid_13
    {
        static VkSwapchainCreateInfoKHR VkSwapchainCreateInfoKHR_temp_2[1] = { VkSwapchainCreateInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        /* pNext = */ nullptr,
        /* flags = */ VkSwapchainCreateFlagsKHR(0),
        /* surface = */ VkSurfaceKHR_uid_3,
        /* minImageCount = */ 2u,
        /* imageFormat = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* imageColorSpace = */ VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
        /* imageExtent = */ VkExtent2D{
        /* width = */ 2200u,
        /* height = */ 1300u},
        /* imageArrayLayers = */ 1u,
        /* imageUsage = */ VkImageUsageFlags(VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT),
        /* imageSharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* preTransform = */ VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        /* compositeAlpha = */ VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        /* presentMode = */ VK_PRESENT_MODE_MAILBOX_KHR,
        /* clipped = */ 1u,
        /* oldSwapchain = */ VkSwapchainKHR(VK_NULL_HANDLE)} };
        NV_VK_REPLAY(VulkanReplay_CreateSwapchainKHR(VkDevice_uid_4, VkSwapchainCreateInfoKHR_temp_2, nullptr, &VkSwapchainKHR_uid_13));

        // Get swapchain images associated with this swapchain
        uint32_t uint32_t_temp_270(2u);
        VulkanReplay_GetSwapchainImagesKHR(VkDevice_uid_4, VkSwapchainKHR_uid_13, &uint32_t_temp_270, nullptr);
        std::vector<VkImage> std_vector_of_VkImage_temp_2(uint32_t_temp_270);
        VulkanReplay_GetSwapchainImagesKHR(VkDevice_uid_4, VkSwapchainKHR_uid_13, &uint32_t_temp_270, std_vector_of_VkImage_temp_2.data());
        VkImage_uid_14 = std_vector_of_VkImage_temp_2[0];
        VkImage_uid_15 = std_vector_of_VkImage_temp_2[1];
    }

    // Create VkBuffer_uid_5076
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_268[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_277[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_268, VkMemoryRequirements_temp_277, 0x000000e003ef0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5076));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5076), 5076ull));
    }

    // Create VkBuffer_uid_5081
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_269[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_278[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_269, VkMemoryRequirements_temp_278, 0x000000e003f00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5081));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5081), 5081ull));
    }

    // Create VkBuffer_uid_5155
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_270[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_279[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_270, VkMemoryRequirements_temp_279, 0x000000e003ee0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5155));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5155), 5155ull));
    }

    // Create VkBuffer_uid_5157
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_271[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_280[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_271, VkMemoryRequirements_temp_280, 0x000000e0056d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5157));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5157), 5157ull));
    }

    // Create VkBuffer_uid_5185
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_272[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_281[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_272, VkMemoryRequirements_temp_281, 0x000000e0112a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5185));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5185), 5185ull));
    }

    // Create VkBuffer_uid_5190
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_273[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_282[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_273, VkMemoryRequirements_temp_282, 0x000000e0112b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5190));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5190), 5190ull));
    }

    // Create VkBuffer_uid_5233
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_274[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_283[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_274, VkMemoryRequirements_temp_283, 0x000000e011340000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5233));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5233), 5233ull));
    }

    // Create VkBuffer_uid_5238
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_275[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_284[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_275, VkMemoryRequirements_temp_284, 0x000000e011350000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5238));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5238), 5238ull));
    }

    // Create VkBuffer_uid_5254
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_276[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_285[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_276, VkMemoryRequirements_temp_285, 0x000000e011360000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5254));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5254), 5254ull));
    }

    // Create VkBuffer_uid_5259
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_277[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_286[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_277, VkMemoryRequirements_temp_286, 0x000000e011370000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5259));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5259), 5259ull));
    }

    // Create VkBuffer_uid_5304
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_278[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1056ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_287[1] = { VkMemoryRequirements{
        /* size = */ 1280ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_278, VkMemoryRequirements_temp_287, 0x000000e0056e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5304));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5304), 5304ull));
    }

    // Create VkBuffer_uid_5309
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_279[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 144ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_288[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_279, VkMemoryRequirements_temp_288, 0x000000e0056f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5309));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5309), 5309ull));
    }

    // Create VkBuffer_uid_5383
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_280[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_289[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_280, VkMemoryRequirements_temp_289, 0x000000e011330000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5383));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5383), 5383ull));
    }

    // Create VkBuffer_uid_5385
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_281[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_290[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_281, VkMemoryRequirements_temp_290, 0x000000e005700000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5385));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5385), 5385ull));
    }

    // Create VkBuffer_uid_5396
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_282[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 935616ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_291[1] = { VkMemoryRequirements{
        /* size = */ 935680ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_282, VkMemoryRequirements_temp_291, 0x000000e011380000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5396));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5396), 5396ull));
    }

    // Create VkBuffer_uid_5401
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_283[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 238884ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_292[1] = { VkMemoryRequirements{
        /* size = */ 239104ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_283, VkMemoryRequirements_temp_292, 0x000000e005750000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5401));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5401), 5401ull));
    }

    // Create VkBuffer_uid_5406
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_284[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 502172ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_293[1] = { VkMemoryRequirements{
        /* size = */ 502272ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_284, VkMemoryRequirements_temp_293, 0x000000e0114f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5406));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5406), 5406ull));
    }

    // Create VkBuffer_uid_5411
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_285[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 234264ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_294[1] = { VkMemoryRequirements{
        /* size = */ 234496ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_285, VkMemoryRequirements_temp_294, 0x000000e005790000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5411));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5411), 5411ull));
    }

    // Create VkBuffer_uid_5416
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_286[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 989956ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_295[1] = { VkMemoryRequirements{
        /* size = */ 990208ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_286, VkMemoryRequirements_temp_295, 0x000000e005d00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5416));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5416), 5416ull));
    }

    // Create VkBuffer_uid_5421
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_287[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 434544ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_296[1] = { VkMemoryRequirements{
        /* size = */ 434688ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_287, VkMemoryRequirements_temp_296, 0x000000e011570000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5421));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5421), 5421ull));
    }

    // Create VkBuffer_uid_5426
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_288[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 710732ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_297[1] = { VkMemoryRequirements{
        /* size = */ 710912ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_288, VkMemoryRequirements_temp_297, 0x000000e005e00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5426));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5426), 5426ull));
    }

    // Create VkBuffer_uid_5431
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_289[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 360324ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_298[1] = { VkMemoryRequirements{
        /* size = */ 360448ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_289, VkMemoryRequirements_temp_298, 0x000000e005c00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5431));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5431), 5431ull));
    }

    // Create VkBuffer_uid_5436
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_290[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1172160ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_299[1] = { VkMemoryRequirements{
        /* size = */ 1172224ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_290, VkMemoryRequirements_temp_299, 0x000000e01c100000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5436));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5436), 5436ull));
    }

    // Create VkBuffer_uid_5441
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_291[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 537840ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_300[1] = { VkMemoryRequirements{
        /* size = */ 537856ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_291, VkMemoryRequirements_temp_300, 0x000000e005eb0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5441));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5441), 5441ull));
    }

    // Create VkBuffer_uid_5444
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_292[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_301[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_292, VkMemoryRequirements_temp_301, 0x000000e0115e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5444));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5444), 5444ull));
    }

    // Create VkBuffer_uid_5446
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_293[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_302[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_293, VkMemoryRequirements_temp_302, 0x000000e0115f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5446));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5446), 5446ull));
    }

    // Create VkBuffer_uid_5457
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_294[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24992ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_303[1] = { VkMemoryRequirements{
        /* size = */ 25088ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_294, VkMemoryRequirements_temp_303, 0x000000e0057e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5457));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5457), 5457ull));
    }

    // Create VkBuffer_uid_5462
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_295[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 12744ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_304[1] = { VkMemoryRequirements{
        /* size = */ 12800ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_295, VkMemoryRequirements_temp_304, 0x000000e0057d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5462));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5462), 5462ull));
    }

    // Create VkBuffer_uid_5465
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_296[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_305[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_296, VkMemoryRequirements_temp_305, 0x000000e0057f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5465));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5465), 5465ull));
    }

    // Create VkBuffer_uid_5467
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_297[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_306[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_297, VkMemoryRequirements_temp_306, 0x000000e005710000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5467));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5467), 5467ull));
    }

    // Create VkBuffer_uid_5478
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_298[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24992ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_307[1] = { VkMemoryRequirements{
        /* size = */ 25088ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_298, VkMemoryRequirements_temp_307, 0x000000e005730000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5478));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5478), 5478ull));
    }

    // Create VkBuffer_uid_5483
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_299[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 12744ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_308[1] = { VkMemoryRequirements{
        /* size = */ 12800ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_299, VkMemoryRequirements_temp_308, 0x000000e005720000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5483));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5483), 5483ull));
    }

    // Create VkBuffer_uid_5486
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_300[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_309[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_300, VkMemoryRequirements_temp_309, 0x000000e005740000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5486));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5486), 5486ull));
    }

    // Create VkBuffer_uid_5488
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_301[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_310[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_301, VkMemoryRequirements_temp_310, 0x000000e011470000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5488));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5488), 5488ull));
    }

    // Create VkBuffer_uid_5499
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_302[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24992ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_311[1] = { VkMemoryRequirements{
        /* size = */ 25088ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_302, VkMemoryRequirements_temp_311, 0x000000e011490000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5499));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5499), 5499ull));
    }

    // Create VkBuffer_uid_5504
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_303[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 12744ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_312[1] = { VkMemoryRequirements{
        /* size = */ 12800ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_303, VkMemoryRequirements_temp_312, 0x000000e0114a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5504));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5504), 5504ull));
    }

    // Create VkBuffer_uid_5507
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_304[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_313[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_304, VkMemoryRequirements_temp_313, 0x000000e011480000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5507));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5507), 5507ull));
    }

    // Create VkBuffer_uid_5509
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_305[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_314[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_305, VkMemoryRequirements_temp_314, 0x000000e0114b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5509));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5509), 5509ull));
    }

    // Create VkBuffer_uid_5520
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_306[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_315[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_306, VkMemoryRequirements_temp_315, 0x000000e005f40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5520));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5520), 5520ull));
    }

    // Create VkBuffer_uid_5525
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_307[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_316[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_307, VkMemoryRequirements_temp_316, 0x000000e005c60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5525));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5525), 5525ull));
    }

    // Create VkBuffer_uid_5528
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_308[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_317[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_308, VkMemoryRequirements_temp_317, 0x000000e0114c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5528));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5528), 5528ull));
    }

    // Create VkBuffer_uid_5530
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_309[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_318[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_309, VkMemoryRequirements_temp_318, 0x000000e0114d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5530));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5530), 5530ull));
    }

    // Create VkBuffer_uid_5541
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_310[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_319[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_310, VkMemoryRequirements_temp_319, 0x000000e01c290000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5541));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5541), 5541ull));
    }

    // Create VkBuffer_uid_5546
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_311[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_320[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_311, VkMemoryRequirements_temp_320, 0x000000e005ca0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5546));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5546), 5546ull));
    }

    // Create VkBuffer_uid_5549
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_312[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_321[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_312, VkMemoryRequirements_temp_321, 0x000000e0114e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5549));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5549), 5549ull));
    }

    // Create VkBuffer_uid_5551
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_313[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_322[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_313, VkMemoryRequirements_temp_322, 0x000000e005ce0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5551));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5551), 5551ull));
    }

    // Create VkBuffer_uid_5562
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_314[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_323[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_314, VkMemoryRequirements_temp_323, 0x000000e01c300000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5562));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5562), 5562ull));
    }

    // Create VkBuffer_uid_5567
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_315[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_324[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_315, VkMemoryRequirements_temp_324, 0x000000e01c220000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5567));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5567), 5567ull));
    }

    // Create VkBuffer_uid_5570
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_316[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_325[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_316, VkMemoryRequirements_temp_325, 0x000000e005cf0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5570));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5570), 5570ull));
    }

    // Create VkBuffer_uid_5572
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_317[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_326[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_317, VkMemoryRequirements_temp_326, 0x000000e01c260000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5572));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5572), 5572ull));
    }

    // Create VkBuffer_uid_5583
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_318[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_327[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_318, VkMemoryRequirements_temp_327, 0x000000e01c3e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5583));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5583), 5583ull));
    }

    // Create VkBuffer_uid_5588
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_319[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_328[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_319, VkMemoryRequirements_temp_328, 0x000000e01c370000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5588));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5588), 5588ull));
    }

    // Create VkBuffer_uid_5591
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_320[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_329[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_320, VkMemoryRequirements_temp_329, 0x000000e01c270000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5591));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5591), 5591ull));
    }

    // Create VkBuffer_uid_5593
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_321[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_330[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_321, VkMemoryRequirements_temp_330, 0x000000e01c280000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5593));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5593), 5593ull));
    }

    // Create VkBuffer_uid_5604
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_322[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_331[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_322, VkMemoryRequirements_temp_331, 0x000000e01c4c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5604));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5604), 5604ull));
    }

    // Create VkBuffer_uid_5609
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_323[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_332[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_323, VkMemoryRequirements_temp_332, 0x000000e01c450000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5609));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5609), 5609ull));
    }

    // Create VkBuffer_uid_5612
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_324[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_333[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_324, VkMemoryRequirements_temp_333, 0x000000e01c3b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5612));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5612), 5612ull));
    }

    // Create VkBuffer_uid_5614
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_325[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_334[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_325, VkMemoryRequirements_temp_334, 0x000000e01c3c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5614));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5614), 5614ull));
    }

    // Create VkBuffer_uid_5625
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_326[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_335[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_326, VkMemoryRequirements_temp_335, 0x000000e01c5a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5625));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5625), 5625ull));
    }

    // Create VkBuffer_uid_5630
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_327[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_336[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_327, VkMemoryRequirements_temp_336, 0x000000e01c530000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5630));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5630), 5630ull));
    }

    // Create VkBuffer_uid_5633
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_328[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_337[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_328, VkMemoryRequirements_temp_337, 0x000000e01c3d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5633));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5633), 5633ull));
    }

    // Create VkBuffer_uid_5635
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_329[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_338[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_329, VkMemoryRequirements_temp_338, 0x000000e01c490000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5635));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5635), 5635ull));
    }

    // Create VkBuffer_uid_5646
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_330[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_339[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_330, VkMemoryRequirements_temp_339, 0x000000e01c680000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5646));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5646), 5646ull));
    }

    // Create VkBuffer_uid_5651
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_331[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_340[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_331, VkMemoryRequirements_temp_340, 0x000000e01c610000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5651));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5651), 5651ull));
    }

    // Create VkBuffer_uid_5654
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_332[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_341[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_332, VkMemoryRequirements_temp_341, 0x000000e01c4a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5654));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5654), 5654ull));
    }

    // Create VkBuffer_uid_5656
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_333[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_342[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_333, VkMemoryRequirements_temp_342, 0x000000e01c4b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5656));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5656), 5656ull));
    }

    // Create VkBuffer_uid_5667
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_334[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_343[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_334, VkMemoryRequirements_temp_343, 0x000000e01c760000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5667));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5667), 5667ull));
    }

    // Create VkBuffer_uid_5672
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_335[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_344[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_335, VkMemoryRequirements_temp_344, 0x000000e01c6f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5672));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5672), 5672ull));
    }

    // Create VkBuffer_uid_5675
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_336[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_345[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_336, VkMemoryRequirements_temp_345, 0x000000e01c570000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5675));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5675), 5675ull));
    }

    // Create VkBuffer_uid_5677
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_337[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_346[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_337, VkMemoryRequirements_temp_346, 0x000000e01c580000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5677));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5677), 5677ull));
    }

    // Create VkBuffer_uid_5688
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_338[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_347[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_338, VkMemoryRequirements_temp_347, 0x000000e01c840000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5688));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5688), 5688ull));
    }

    // Create VkBuffer_uid_5693
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_339[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_348[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_339, VkMemoryRequirements_temp_348, 0x000000e01c7d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5693));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5693), 5693ull));
    }

    // Create VkBuffer_uid_5696
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_340[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_349[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_340, VkMemoryRequirements_temp_349, 0x000000e01c590000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5696));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5696), 5696ull));
    }

    // Create VkBuffer_uid_5698
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_341[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_350[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_341, VkMemoryRequirements_temp_350, 0x000000e01c650000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5698));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5698), 5698ull));
    }

    // Create VkBuffer_uid_5709
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_342[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_351[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_342, VkMemoryRequirements_temp_351, 0x000000e01c920000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5709));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5709), 5709ull));
    }

    // Create VkBuffer_uid_5714
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_343[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_352[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_343, VkMemoryRequirements_temp_352, 0x000000e01c8b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5714));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5714), 5714ull));
    }

    // Create VkBuffer_uid_5717
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_344[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_353[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_344, VkMemoryRequirements_temp_353, 0x000000e01c660000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5717));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5717), 5717ull));
    }

    // Create VkBuffer_uid_5719
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_345[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_354[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_345, VkMemoryRequirements_temp_354, 0x000000e01c670000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5719));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5719), 5719ull));
    }

    // Create VkBuffer_uid_5730
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_346[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_355[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_346, VkMemoryRequirements_temp_355, 0x000000e01ca00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5730));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5730), 5730ull));
    }

    // Create VkBuffer_uid_5735
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_347[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_356[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_347, VkMemoryRequirements_temp_356, 0x000000e01c990000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5735));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5735), 5735ull));
    }

    // Create VkBuffer_uid_5738
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_348[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_357[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_348, VkMemoryRequirements_temp_357, 0x000000e01c730000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5738));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5738), 5738ull));
    }

    // Create VkBuffer_uid_5740
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_349[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_358[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_349, VkMemoryRequirements_temp_358, 0x000000e01c740000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5740));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5740), 5740ull));
    }

    // Create VkBuffer_uid_5751
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_350[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_359[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_350, VkMemoryRequirements_temp_359, 0x000000e01cae0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5751));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5751), 5751ull));
    }

    // Create VkBuffer_uid_5756
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_351[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_360[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_351, VkMemoryRequirements_temp_360, 0x000000e01ca70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5756));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5756), 5756ull));
    }

    // Create VkBuffer_uid_5759
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_352[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_361[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_352, VkMemoryRequirements_temp_361, 0x000000e01c750000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5759));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5759), 5759ull));
    }

    // Create VkBuffer_uid_5761
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_353[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_362[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_353, VkMemoryRequirements_temp_362, 0x000000e01c810000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5761));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5761), 5761ull));
    }

    // Create VkBuffer_uid_5772
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_354[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_363[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_354, VkMemoryRequirements_temp_363, 0x000000e01cbc0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5772));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5772), 5772ull));
    }

    // Create VkBuffer_uid_5777
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_355[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_364[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_355, VkMemoryRequirements_temp_364, 0x000000e01cb50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5777));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5777), 5777ull));
    }

    // Create VkBuffer_uid_5780
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_356[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_365[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_356, VkMemoryRequirements_temp_365, 0x000000e01c820000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5780));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5780), 5780ull));
    }

    // Create VkBuffer_uid_5782
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_357[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_366[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_357, VkMemoryRequirements_temp_366, 0x000000e01c830000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5782));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5782), 5782ull));
    }

    // Create VkBuffer_uid_5793
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_358[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_367[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_358, VkMemoryRequirements_temp_367, 0x000000e01cca0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5793));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5793), 5793ull));
    }

    // Create VkBuffer_uid_5798
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_359[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_368[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_359, VkMemoryRequirements_temp_368, 0x000000e01cc30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5798));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5798), 5798ull));
    }

    // Create VkBuffer_uid_5801
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_360[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_369[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_360, VkMemoryRequirements_temp_369, 0x000000e01c8f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5801));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5801), 5801ull));
    }

    // Create VkBuffer_uid_5803
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_361[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_370[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_361, VkMemoryRequirements_temp_370, 0x000000e01c900000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5803));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5803), 5803ull));
    }

    // Create VkBuffer_uid_5814
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_362[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_371[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_362, VkMemoryRequirements_temp_371, 0x000000e01cd80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5814));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5814), 5814ull));
    }

    // Create VkBuffer_uid_5819
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_363[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_372[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_363, VkMemoryRequirements_temp_372, 0x000000e01cd10000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5819));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5819), 5819ull));
    }

    // Create VkBuffer_uid_5822
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_364[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_373[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_364, VkMemoryRequirements_temp_373, 0x000000e01c910000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5822));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5822), 5822ull));
    }

    // Create VkBuffer_uid_5824
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_365[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_374[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_365, VkMemoryRequirements_temp_374, 0x000000e01c9d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5824));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5824), 5824ull));
    }

    // Create VkBuffer_uid_5835
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_366[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_375[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_366, VkMemoryRequirements_temp_375, 0x000000e01ce60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5835));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5835), 5835ull));
    }

    // Create VkBuffer_uid_5840
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_367[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_376[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_367, VkMemoryRequirements_temp_376, 0x000000e01cdf0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5840));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5840), 5840ull));
    }

    // Create VkBuffer_uid_5843
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_368[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_377[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_368, VkMemoryRequirements_temp_377, 0x000000e01c9e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5843));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5843), 5843ull));
    }

    // Create VkBuffer_uid_5845
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_369[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_378[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_369, VkMemoryRequirements_temp_378, 0x000000e01c9f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5845));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5845), 5845ull));
    }

    // Create VkBuffer_uid_5856
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_370[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_379[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_370, VkMemoryRequirements_temp_379, 0x000000e01cf40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5856));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5856), 5856ull));
    }

    // Create VkBuffer_uid_5861
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_371[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_380[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_371, VkMemoryRequirements_temp_380, 0x000000e01ced0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5861));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5861), 5861ull));
    }

    // Create VkBuffer_uid_5864
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_372[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_381[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_372, VkMemoryRequirements_temp_381, 0x000000e01cab0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5864));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5864), 5864ull));
    }

    // Create VkBuffer_uid_5866
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_373[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_382[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_373, VkMemoryRequirements_temp_382, 0x000000e01cac0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5866));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5866), 5866ull));
    }

    // Create VkBuffer_uid_5877
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_374[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_383[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_374, VkMemoryRequirements_temp_383, 0x000000e01d020000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5877));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5877), 5877ull));
    }

    // Create VkBuffer_uid_5882
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_375[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_384[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_375, VkMemoryRequirements_temp_384, 0x000000e01cfb0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5882));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5882), 5882ull));
    }

    // Create VkBuffer_uid_5885
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_376[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_385[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_376, VkMemoryRequirements_temp_385, 0x000000e01cad0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5885));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5885), 5885ull));
    }

    // Create VkBuffer_uid_5887
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_377[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_386[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_377, VkMemoryRequirements_temp_386, 0x000000e01cb90000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5887));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5887), 5887ull));
    }

    // Create VkBuffer_uid_5898
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_378[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_387[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_378, VkMemoryRequirements_temp_387, 0x000000e01d100000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5898));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5898), 5898ull));
    }

    // Create VkBuffer_uid_5903
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_379[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_388[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_379, VkMemoryRequirements_temp_388, 0x000000e01d090000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5903));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5903), 5903ull));
    }

    // Create VkBuffer_uid_5906
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_380[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_389[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_380, VkMemoryRequirements_temp_389, 0x000000e01cba0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5906));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5906), 5906ull));
    }

    // Create VkBuffer_uid_5908
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_381[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_390[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_381, VkMemoryRequirements_temp_390, 0x000000e01cbb0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5908));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5908), 5908ull));
    }

    // Create VkBuffer_uid_5919
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_382[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_391[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_382, VkMemoryRequirements_temp_391, 0x000000e01d1e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5919));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5919), 5919ull));
    }

    // Create VkBuffer_uid_5924
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_383[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_392[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_383, VkMemoryRequirements_temp_392, 0x000000e01d170000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5924));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5924), 5924ull));
    }

    // Create VkBuffer_uid_5927
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_384[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_393[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_384, VkMemoryRequirements_temp_393, 0x000000e01cc70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5927));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5927), 5927ull));
    }

    // Create VkBuffer_uid_5929
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_385[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_394[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_385, VkMemoryRequirements_temp_394, 0x000000e01cc80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5929));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5929), 5929ull));
    }

    // Create VkBuffer_uid_5940
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_386[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_395[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_386, VkMemoryRequirements_temp_395, 0x000000e01d2c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5940));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5940), 5940ull));
    }

    // Create VkBuffer_uid_5945
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_387[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_396[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_387, VkMemoryRequirements_temp_396, 0x000000e01d250000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5945));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5945), 5945ull));
    }

    // Create VkBuffer_uid_5948
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_388[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_397[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_388, VkMemoryRequirements_temp_397, 0x000000e01cc90000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5948));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5948), 5948ull));
    }

    // Create VkBuffer_uid_5950
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_389[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_398[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_389, VkMemoryRequirements_temp_398, 0x000000e01cd50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5950));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5950), 5950ull));
    }

    // Create VkBuffer_uid_5961
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_390[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_399[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_390, VkMemoryRequirements_temp_399, 0x000000e01d3a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5961));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5961), 5961ull));
    }

    // Create VkBuffer_uid_5966
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_391[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_400[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_391, VkMemoryRequirements_temp_400, 0x000000e01d330000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5966));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5966), 5966ull));
    }

    // Create VkBuffer_uid_5969
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_392[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_401[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_392, VkMemoryRequirements_temp_401, 0x000000e01cd60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5969));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5969), 5969ull));
    }

    // Create VkBuffer_uid_5971
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_393[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_402[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_393, VkMemoryRequirements_temp_402, 0x000000e01cd70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5971));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5971), 5971ull));
    }

    // Create VkBuffer_uid_5982
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_394[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_403[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_394, VkMemoryRequirements_temp_403, 0x000000e01d480000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5982));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5982), 5982ull));
    }

    // Create VkBuffer_uid_5987
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_395[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_404[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_395, VkMemoryRequirements_temp_404, 0x000000e01d410000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5987));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5987), 5987ull));
    }

    // Create VkBuffer_uid_5990
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_396[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_405[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_396, VkMemoryRequirements_temp_405, 0x000000e01ce30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5990));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5990), 5990ull));
    }

    // Create VkBuffer_uid_5992
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_397[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_406[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_397, VkMemoryRequirements_temp_406, 0x000000e01ce40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_5992));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_5992), 5992ull));
    }

    // Create VkBuffer_uid_6003
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_398[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_407[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_398, VkMemoryRequirements_temp_407, 0x000000e01d560000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6003));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6003), 6003ull));
    }

    // Create VkBuffer_uid_6008
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_399[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_408[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_399, VkMemoryRequirements_temp_408, 0x000000e01d4f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6008));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6008), 6008ull));
    }

    // Create VkBuffer_uid_6011
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_400[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_409[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_400, VkMemoryRequirements_temp_409, 0x000000e01ce50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6011));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6011), 6011ull));
    }

    // Create VkBuffer_uid_6013
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_401[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_410[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_401, VkMemoryRequirements_temp_410, 0x000000e01cf10000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6013));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6013), 6013ull));
    }

    // Create VkBuffer_uid_6024
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_402[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_411[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_402, VkMemoryRequirements_temp_411, 0x000000e01d640000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6024));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6024), 6024ull));
    }

    // Create VkBuffer_uid_6029
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_403[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_412[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_403, VkMemoryRequirements_temp_412, 0x000000e01d5d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6029));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6029), 6029ull));
    }

    // Create VkBuffer_uid_6032
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_404[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_413[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_404, VkMemoryRequirements_temp_413, 0x000000e01cf20000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6032));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6032), 6032ull));
    }

    // Create VkBuffer_uid_6034
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_405[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_414[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_405, VkMemoryRequirements_temp_414, 0x000000e01cf30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6034));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6034), 6034ull));
    }

    // Create VkBuffer_uid_6045
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_406[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_415[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_406, VkMemoryRequirements_temp_415, 0x000000e01d720000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6045));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6045), 6045ull));
    }

    // Create VkBuffer_uid_6050
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_407[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_416[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_407, VkMemoryRequirements_temp_416, 0x000000e01d6b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6050));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6050), 6050ull));
    }

    // Create VkBuffer_uid_6053
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_408[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_417[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_408, VkMemoryRequirements_temp_417, 0x000000e01cff0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6053));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6053), 6053ull));
    }

    // Create VkBuffer_uid_6055
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_409[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_418[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_409, VkMemoryRequirements_temp_418, 0x000000e01d000000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6055));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6055), 6055ull));
    }

    // Create VkBuffer_uid_6066
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_410[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_419[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_410, VkMemoryRequirements_temp_419, 0x000000e01d800000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6066));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6066), 6066ull));
    }

    // Create VkBuffer_uid_6071
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_411[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_420[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_411, VkMemoryRequirements_temp_420, 0x000000e01d790000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6071));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6071), 6071ull));
    }

    // Create VkBuffer_uid_6074
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_412[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_421[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_412, VkMemoryRequirements_temp_421, 0x000000e01d010000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6074));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6074), 6074ull));
    }

    // Create VkBuffer_uid_6076
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_413[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_422[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_413, VkMemoryRequirements_temp_422, 0x000000e01d0d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6076));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6076), 6076ull));
    }

    // Create VkBuffer_uid_6087
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_414[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_423[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_414, VkMemoryRequirements_temp_423, 0x000000e01d8e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6087));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6087), 6087ull));
    }

    // Create VkBuffer_uid_6092
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_415[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_424[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_415, VkMemoryRequirements_temp_424, 0x000000e01d870000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6092));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6092), 6092ull));
    }

    // Create VkBuffer_uid_6095
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_416[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_425[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_416, VkMemoryRequirements_temp_425, 0x000000e01d0e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6095));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6095), 6095ull));
    }

    // Create VkBuffer_uid_6097
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_417[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_426[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_417, VkMemoryRequirements_temp_426, 0x000000e01d0f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6097));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6097), 6097ull));
    }

    // Create VkBuffer_uid_6108
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_418[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_427[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_418, VkMemoryRequirements_temp_427, 0x000000e01d9c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6108));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6108), 6108ull));
    }

    // Create VkBuffer_uid_6113
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_419[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_428[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_419, VkMemoryRequirements_temp_428, 0x000000e01d950000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6113));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6113), 6113ull));
    }

    // Create VkBuffer_uid_6116
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_420[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_429[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_420, VkMemoryRequirements_temp_429, 0x000000e01d1b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6116));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6116), 6116ull));
    }

    // Create VkBuffer_uid_6118
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_421[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_430[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_421, VkMemoryRequirements_temp_430, 0x000000e01d1c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6118));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6118), 6118ull));
    }

    // Create VkBuffer_uid_6129
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_422[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_431[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_422, VkMemoryRequirements_temp_431, 0x000000e01daa0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6129));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6129), 6129ull));
    }

    // Create VkBuffer_uid_6134
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_423[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_432[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_423, VkMemoryRequirements_temp_432, 0x000000e01da30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6134));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6134), 6134ull));
    }

    // Create VkBuffer_uid_6137
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_424[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_433[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_424, VkMemoryRequirements_temp_433, 0x000000e01d1d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6137));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6137), 6137ull));
    }

    // Create VkBuffer_uid_6139
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_425[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_434[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_425, VkMemoryRequirements_temp_434, 0x000000e01d290000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6139));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6139), 6139ull));
    }

    // Create VkBuffer_uid_6150
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_426[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_435[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_426, VkMemoryRequirements_temp_435, 0x000000e01db80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6150));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6150), 6150ull));
    }

    // Create VkBuffer_uid_6155
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_427[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_436[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_427, VkMemoryRequirements_temp_436, 0x000000e01db10000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6155));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6155), 6155ull));
    }

    // Create VkBuffer_uid_6158
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_428[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_437[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_428, VkMemoryRequirements_temp_437, 0x000000e01d2a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6158));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6158), 6158ull));
    }

    // Create VkBuffer_uid_6160
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_429[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_438[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_429, VkMemoryRequirements_temp_438, 0x000000e01d2b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6160));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6160), 6160ull));
    }

    // Create VkBuffer_uid_6171
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_430[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_439[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_430, VkMemoryRequirements_temp_439, 0x000000e01dc60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6171));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6171), 6171ull));
    }

    // Create VkBuffer_uid_6176
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_431[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_440[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_431, VkMemoryRequirements_temp_440, 0x000000e01dbf0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6176));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6176), 6176ull));
    }

    // Create VkBuffer_uid_6179
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_432[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_441[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_432, VkMemoryRequirements_temp_441, 0x000000e01d370000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6179));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6179), 6179ull));
    }

    // Create VkBuffer_uid_6181
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_433[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_442[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_433, VkMemoryRequirements_temp_442, 0x000000e01d380000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6181));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6181), 6181ull));
    }

    // Create VkBuffer_uid_6192
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_434[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_443[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_434, VkMemoryRequirements_temp_443, 0x000000e01dd40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6192));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6192), 6192ull));
    }

    // Create VkBuffer_uid_6197
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_435[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_444[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_435, VkMemoryRequirements_temp_444, 0x000000e01dcd0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6197));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6197), 6197ull));
    }

    // Create VkBuffer_uid_6200
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_436[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_445[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_436, VkMemoryRequirements_temp_445, 0x000000e01d390000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6200));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6200), 6200ull));
    }

    // Create VkBuffer_uid_6202
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_437[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_446[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_437, VkMemoryRequirements_temp_446, 0x000000e01d450000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6202));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6202), 6202ull));
    }

    // Create VkBuffer_uid_6213
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_438[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_447[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_438, VkMemoryRequirements_temp_447, 0x000000e01de20000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6213));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6213), 6213ull));
    }

    // Create VkBuffer_uid_6218
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_439[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_448[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_439, VkMemoryRequirements_temp_448, 0x000000e01ddb0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6218));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6218), 6218ull));
    }

    // Create VkBuffer_uid_6221
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_440[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_449[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_440, VkMemoryRequirements_temp_449, 0x000000e01d460000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6221));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6221), 6221ull));
    }

    // Create VkBuffer_uid_6223
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_441[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_450[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_441, VkMemoryRequirements_temp_450, 0x000000e01d470000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6223));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6223), 6223ull));
    }

    // Create VkBuffer_uid_6234
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_442[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_451[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_442, VkMemoryRequirements_temp_451, 0x000000e01df00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6234));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6234), 6234ull));
    }

    // Create VkBuffer_uid_6239
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_443[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_452[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_443, VkMemoryRequirements_temp_452, 0x000000e01de90000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6239));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6239), 6239ull));
    }

    // Create VkBuffer_uid_6242
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_444[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_453[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_444, VkMemoryRequirements_temp_453, 0x000000e01d530000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6242));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6242), 6242ull));
    }

    // Create VkBuffer_uid_6244
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_445[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_454[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_445, VkMemoryRequirements_temp_454, 0x000000e01d540000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6244));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6244), 6244ull));
    }

    // Create VkBuffer_uid_6255
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_446[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_455[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_446, VkMemoryRequirements_temp_455, 0x000000e01dfe0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6255));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6255), 6255ull));
    }

    // Create VkBuffer_uid_6260
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_447[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_456[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_447, VkMemoryRequirements_temp_456, 0x000000e01df70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6260));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6260), 6260ull));
    }

    // Create VkBuffer_uid_6263
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_448[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_457[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_448, VkMemoryRequirements_temp_457, 0x000000e01d550000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6263));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6263), 6263ull));
    }

    // Create VkBuffer_uid_6265
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_449[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_458[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_449, VkMemoryRequirements_temp_458, 0x000000e01d610000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6265));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6265), 6265ull));
    }

    // Create VkBuffer_uid_6276
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_450[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_459[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_450, VkMemoryRequirements_temp_459, 0x000000e01e0c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6276));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6276), 6276ull));
    }

    // Create VkBuffer_uid_6281
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_451[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_460[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_451, VkMemoryRequirements_temp_460, 0x000000e01e050000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6281));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6281), 6281ull));
    }

    // Create VkBuffer_uid_6284
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_452[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_461[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_452, VkMemoryRequirements_temp_461, 0x000000e01d620000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6284));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6284), 6284ull));
    }

    // Create VkBuffer_uid_6286
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_453[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_462[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_453, VkMemoryRequirements_temp_462, 0x000000e01d630000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6286));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6286), 6286ull));
    }

    // Create VkBuffer_uid_6297
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_454[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_463[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_454, VkMemoryRequirements_temp_463, 0x000000e01e1a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6297));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6297), 6297ull));
    }

    // Create VkBuffer_uid_6302
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_455[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_464[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_455, VkMemoryRequirements_temp_464, 0x000000e01e130000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6302));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6302), 6302ull));
    }

    // Create VkBuffer_uid_6305
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_456[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_465[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_456, VkMemoryRequirements_temp_465, 0x000000e01d6f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6305));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6305), 6305ull));
    }

    // Create VkBuffer_uid_6307
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_457[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_466[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_457, VkMemoryRequirements_temp_466, 0x000000e01d700000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6307));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6307), 6307ull));
    }

    // Create VkBuffer_uid_6318
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_458[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_467[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_458, VkMemoryRequirements_temp_467, 0x000000e01e280000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6318));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6318), 6318ull));
    }

    // Create VkBuffer_uid_6323
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_459[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_468[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_459, VkMemoryRequirements_temp_468, 0x000000e01e210000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6323));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6323), 6323ull));
    }

    // Create VkBuffer_uid_6326
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_460[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_469[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_460, VkMemoryRequirements_temp_469, 0x000000e01d710000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6326));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6326), 6326ull));
    }

    // Create VkBuffer_uid_6328
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_461[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_470[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_461, VkMemoryRequirements_temp_470, 0x000000e01d7d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6328));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6328), 6328ull));
    }

    // Create VkBuffer_uid_6339
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_462[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 440000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_471[1] = { VkMemoryRequirements{
        /* size = */ 440064ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_462, VkMemoryRequirements_temp_471, 0x000000e01e360000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6339));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6339), 6339ull));
    }

    // Create VkBuffer_uid_6344
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_463[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 235224ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_472[1] = { VkMemoryRequirements{
        /* size = */ 235264ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_463, VkMemoryRequirements_temp_472, 0x000000e01e2f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6344));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6344), 6344ull));
    }

    // Create VkBuffer_uid_6347
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_464[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 32ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_473[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_464, VkMemoryRequirements_temp_473, 0x000000e01d7e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6347));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6347), 6347ull));
    }

    // Create VkBuffer_uid_6349
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_465[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_474[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_465, VkMemoryRequirements_temp_474, 0x000000e01d7f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6349));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6349), 6349ull));
    }

    // Create VkBuffer_uid_6360
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_466[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_475[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_466, VkMemoryRequirements_temp_475, 0x000000e01d8c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6360));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6360), 6360ull));
    }

    // Create VkBuffer_uid_6365
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_467[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_476[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_467, VkMemoryRequirements_temp_476, 0x000000e01d8b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6365));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6365), 6365ull));
    }

    // Create VkBuffer_uid_6386
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_468[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_477[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_468, VkMemoryRequirements_temp_477, 0x000000e01d990000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6386));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6386), 6386ull));
    }

    // Create VkBuffer_uid_6391
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_469[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_478[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_469, VkMemoryRequirements_temp_478, 0x000000e01d9a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6391));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6391), 6391ull));
    }

    // Create VkBuffer_uid_6403
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_470[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_479[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_470, VkMemoryRequirements_temp_479, 0x000000e01d8d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6403));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6403), 6403ull));
    }

    // Create VkBuffer_uid_6408
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_471[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_480[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_471, VkMemoryRequirements_temp_480, 0x000000e01da70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6408));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6408), 6408ull));
    }

    // Create VkBuffer_uid_6420
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_472[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 176ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_481[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_472, VkMemoryRequirements_temp_481, 0x000000e01da80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6420));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6420), 6420ull));
    }

    // Create VkBuffer_uid_6425
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_473[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_482[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_473, VkMemoryRequirements_temp_482, 0x000000e01d9b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6425));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6425), 6425ull));
    }

    // Create VkBuffer_uid_6580
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_474[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 2944ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_483[1] = { VkMemoryRequirements{
        /* size = */ 3072ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_474, VkMemoryRequirements_temp_483, 0x000000e01dc50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6580));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6580), 6580ull));
    }

    // Create VkBuffer_uid_6583
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_475[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_484[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_475, VkMemoryRequirements_temp_484, 0x000000e0200f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6583));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6583), 6583ull));
    }

    // Create VkBuffer_uid_6586
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_476[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_485[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_476, VkMemoryRequirements_temp_485, 0x000000e0320b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6586));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6586), 6586ull));
    }

    // Create VkBuffer_uid_6589
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_477[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_486[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_477, VkMemoryRequirements_temp_486, 0x000000e0321c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6589));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6589), 6589ull));
    }

    // Create VkBuffer_uid_6592
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_478[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_487[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_478, VkMemoryRequirements_temp_487, 0x000000e0322d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6592));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6592), 6592ull));
    }

    // Create VkBuffer_uid_6595
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_479[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_488[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_479, VkMemoryRequirements_temp_488, 0x000000e0323e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6595));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6595), 6595ull));
    }

    // Create VkBuffer_uid_6598
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_480[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_489[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_480, VkMemoryRequirements_temp_489, 0x000000e0324f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6598));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6598), 6598ull));
    }

    // Create VkBuffer_uid_6601
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_481[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_490[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_481, VkMemoryRequirements_temp_490, 0x000000e032600000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6601));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6601), 6601ull));
    }

    // Create VkBuffer_uid_6604
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_482[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_491[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_482, VkMemoryRequirements_temp_491, 0x000000e032710000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6604));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6604), 6604ull));
    }

    // Create VkBuffer_uid_6607
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_483[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_492[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_483, VkMemoryRequirements_temp_492, 0x000000e032820000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6607));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6607), 6607ull));
    }

    // Create VkBuffer_uid_6610
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_484[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_493[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_484, VkMemoryRequirements_temp_493, 0x000000e032930000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6610));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6610), 6610ull));
    }

    // Create VkBuffer_uid_6613
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_485[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_494[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_485, VkMemoryRequirements_temp_494, 0x000000e032a40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6613));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6613), 6613ull));
    }

    // Create VkBuffer_uid_6616
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_486[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_495[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_486, VkMemoryRequirements_temp_495, 0x000000e032b50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6616));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6616), 6616ull));
    }

    // Create VkBuffer_uid_6619
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_487[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_496[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_487, VkMemoryRequirements_temp_496, 0x000000e032c60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6619));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6619), 6619ull));
    }

    // Create VkBuffer_uid_6622
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_488[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_497[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_488, VkMemoryRequirements_temp_497, 0x000000e032d70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6622));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6622), 6622ull));
    }

    // Create VkBuffer_uid_6625
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_489[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_498[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_489, VkMemoryRequirements_temp_498, 0x000000e032e80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6625));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6625), 6625ull));
    }

    // Create VkBuffer_uid_6628
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_490[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_499[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_490, VkMemoryRequirements_temp_499, 0x000000e032f90000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6628));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6628), 6628ull));
    }

    // Create VkBuffer_uid_6631
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_491[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_500[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_491, VkMemoryRequirements_temp_500, 0x000000e0330a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6631));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6631), 6631ull));
    }

    // Create VkBuffer_uid_6634
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_492[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_501[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_492, VkMemoryRequirements_temp_501, 0x000000e0331b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6634));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6634), 6634ull));
    }

    // Create VkBuffer_uid_6637
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_493[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_502[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_493, VkMemoryRequirements_temp_502, 0x000000e0332c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6637));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6637), 6637ull));
    }

    // Create VkBuffer_uid_6640
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_494[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_503[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_494, VkMemoryRequirements_temp_503, 0x000000e0333d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6640));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6640), 6640ull));
    }

    // Create VkBuffer_uid_6643
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_495[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_504[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_495, VkMemoryRequirements_temp_504, 0x000000e0334e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6643));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6643), 6643ull));
    }

    // Create VkBuffer_uid_6646
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_496[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_505[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_496, VkMemoryRequirements_temp_505, 0x000000e0335f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6646));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6646), 6646ull));
    }

    // Create VkBuffer_uid_6649
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_497[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_506[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_497, VkMemoryRequirements_temp_506, 0x000000e033700000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6649));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6649), 6649ull));
    }

    // Create VkBuffer_uid_6652
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_498[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_507[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_498, VkMemoryRequirements_temp_507, 0x000000e033810000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6652));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6652), 6652ull));
    }

    // Create VkBuffer_uid_6655
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_499[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_508[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_499, VkMemoryRequirements_temp_508, 0x000000e033920000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6655));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6655), 6655ull));
    }

    // Create VkBuffer_uid_6658
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_500[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_509[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_500, VkMemoryRequirements_temp_509, 0x000000e033a30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6658));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6658), 6658ull));
    }

    // Create VkBuffer_uid_6661
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_501[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_510[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_501, VkMemoryRequirements_temp_510, 0x000000e033b40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6661));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6661), 6661ull));
    }

    // Create VkBuffer_uid_6664
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_502[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_511[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_502, VkMemoryRequirements_temp_511, 0x000000e033c50000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6664));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6664), 6664ull));
    }

    // Create VkBuffer_uid_6667
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_503[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_512[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_503, VkMemoryRequirements_temp_512, 0x000000e033d60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6667));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6667), 6667ull));
    }

    // Create VkBuffer_uid_6670
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_504[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_513[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_504, VkMemoryRequirements_temp_513, 0x000000e033e70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6670));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6670), 6670ull));
    }

    // Create VkBuffer_uid_6673
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_505[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_514[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_505, VkMemoryRequirements_temp_514, 0x000000e033f80000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6673));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6673), 6673ull));
    }

    // Create VkBuffer_uid_6676
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_506[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_515[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_506, VkMemoryRequirements_temp_515, 0x000000e034090000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6676));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6676), 6676ull));
    }

    // Create VkBuffer_uid_6679
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_507[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_516[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_507, VkMemoryRequirements_temp_516, 0x000000e0341a0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6679));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6679), 6679ull));
    }

    // Create VkBuffer_uid_6682
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_508[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_517[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_508, VkMemoryRequirements_temp_517, 0x000000e0342b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6682));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6682), 6682ull));
    }

    // Create VkBuffer_uid_6685
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_509[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_518[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_509, VkMemoryRequirements_temp_518, 0x000000e0343c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6685));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6685), 6685ull));
    }

    // Create VkBuffer_uid_6688
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_510[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_519[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_510, VkMemoryRequirements_temp_519, 0x000000e0344d0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6688));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6688), 6688ull));
    }

    // Create VkBuffer_uid_6691
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_511[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_520[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_511, VkMemoryRequirements_temp_520, 0x000000e0345e0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6691));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6691), 6691ull));
    }

    // Create VkBuffer_uid_6694
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_512[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_521[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_512, VkMemoryRequirements_temp_521, 0x000000e0346f0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6694));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6694), 6694ull));
    }

    // Create VkBuffer_uid_6697
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_513[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_522[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_513, VkMemoryRequirements_temp_522, 0x000000e034800000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6697));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6697), 6697ull));
    }

    // Create VkBuffer_uid_6700
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_514[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1092736ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_523[1] = { VkMemoryRequirements{
        /* size = */ 1092864ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_514, VkMemoryRequirements_temp_523, 0x000000e034910000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6700));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6700), 6700ull));
    }

    // Create VkBuffer_uid_6703
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_515[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 64128ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_524[1] = { VkMemoryRequirements{
        /* size = */ 64256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_515, VkMemoryRequirements_temp_524, 0x000000e01dd30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6703));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6703), 6703ull));
    }

    // Create VkBuffer_uid_6706
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_516[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 64128ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_525[1] = { VkMemoryRequirements{
        /* size = */ 64256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_516, VkMemoryRequirements_temp_525, 0x000000e01de10000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6706));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6706), 6706ull));
    }

    // Create VkBuffer_uid_6709
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_517[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 64128ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_526[1] = { VkMemoryRequirements{
        /* size = */ 64256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_517, VkMemoryRequirements_temp_526, 0x000000e01ded0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6709));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6709), 6709ull));
    }

    // Create VkBuffer_uid_6712
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_518[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1150592ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_527[1] = { VkMemoryRequirements{
        /* size = */ 1150720ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_518, VkMemoryRequirements_temp_527, 0x000000e034a20000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6712));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6712), 6712ull));
    }

    // Create VkBuffer_uid_6715
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_519[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1125632ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_528[1] = { VkMemoryRequirements{
        /* size = */ 1125632ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_519, VkMemoryRequirements_temp_528, 0x000000e034b40000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6715));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6715), 6715ull));
    }

    // Create VkBuffer_uid_6718
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_520[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 2096256ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_529[1] = { VkMemoryRequirements{
        /* size = */ 2096384ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_520, VkMemoryRequirements_temp_529, 0x000000e034e00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6718));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6718), 6718ull));
    }

    // Create VkBuffer_uid_6721
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_521[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 1724416ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_530[1] = { VkMemoryRequirements{
        /* size = */ 1724416ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_521, VkMemoryRequirements_temp_530, 0x000000e035000000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6721));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6721), 6721ull));
    }

    // Create VkBuffer_uid_6724
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_522[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 2572288ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_531[1] = { VkMemoryRequirements{
        /* size = */ 2572288ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_522, VkMemoryRequirements_temp_531, 0x000000e0351b0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6724));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6724), 6724ull));
    }

    // Create VkBuffer_uid_6733
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_523[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 18560ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_532[1] = { VkMemoryRequirements{
        /* size = */ 18688ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_523, VkMemoryRequirements_temp_532, 0x000000e01def0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6733));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6733), 6733ull));
    }

    // Create VkBuffer_uid_6762
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_524[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 192ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_533[1] = { VkMemoryRequirements{
        /* size = */ 256ull,
        /* alignment = */ 256ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_524, VkMemoryRequirements_temp_533, 0x000000e01da90000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6762));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6762), 6762ull));
    }

    // Create VkBuffer_uid_6946
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_525[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 292ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_534[1] = { VkMemoryRequirements{
        /* size = */ 320ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_525, VkMemoryRequirements_temp_534, VkDeviceAddress(0), VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6946));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6946), 6946ull));
    }

    // Create VkBuffer_uid_6948
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_526[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 24ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_535[1] = { VkMemoryRequirements{
        /* size = */ 64ull,
        /* alignment = */ 64ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_526, VkMemoryRequirements_temp_535, VkDeviceAddress(0), VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6948));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6948), 6948ull));
    }

    // Create VkBuffer_uid_6954
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_527[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 3200000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_536[1] = { VkMemoryRequirements{
        /* size = */ 3200000ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_527, VkMemoryRequirements_temp_536, 0x000000e01ef70000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6954));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6954), 6954ull));
    }

    // Create VkBuffer_uid_6956
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_528[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_537[1] = { VkMemoryRequirements{
        /* size = */ 8000ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_528, VkMemoryRequirements_temp_537, 0x000000e01de00000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6956));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6956), 6956ull));
    }

    // Create VkBuffer_uid_6958
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_529[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 400000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_538[1] = { VkMemoryRequirements{
        /* size = */ 400000ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_529, VkMemoryRequirements_temp_538, 0x000000e030d60000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6958));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6958), 6958ull));
    }

    // Create VkBuffer_uid_6973
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_530[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 640ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_539[1] = { VkMemoryRequirements{
        /* size = */ 640ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_530, VkMemoryRequirements_temp_539, 0x000000e01dee0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6973));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6973), 6973ull));
    }

    // Create VkBuffer_uid_6979
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_531[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 8000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_540[1] = { VkMemoryRequirements{
        /* size = */ 8000ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_531, VkMemoryRequirements_temp_540, 0x000000e01dc30000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6979));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6979), 6979ull));
    }

    // Create VkBuffer_uid_6981
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_532[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 400000ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_541[1] = { VkMemoryRequirements{
        /* size = */ 400000ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_532, VkMemoryRequirements_temp_541, 0x000000e0112c0000, VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_6981));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_6981), 6981ull));
    }

    // Create VkBuffer_uid_7268
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_533[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 274688ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_542[1] = { VkMemoryRequirements{
        /* size = */ 274688ull,
        /* alignment = */ 16ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_533, VkMemoryRequirements_temp_542, VkDeviceAddress(0), VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_7268));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_7268), 7268ull));
    }

    // Create VkBuffer_uid_7289
    {
        static VkBufferCreateInfo VkBufferCreateInfo_temp_534[1] = { VkBufferCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkBufferCreateFlags(0),
        /* size = */ 66560ull,
        /* usage = */ VkBufferUsageFlags(VK_BUFFER_USAGE_INDEX_BUFFER_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr} };
        static VkMemoryRequirements VkMemoryRequirements_temp_543[1] = { VkMemoryRequirements{
        /* size = */ 66560ull,
        /* alignment = */ 4ull,
        /* memoryTypeBits = */ 31u} };
        NV_VK_REPLAY(VulkanHelper_CreateBuffer3(VkDevice_uid_4, VkBufferCreateInfo_temp_534, VkMemoryRequirements_temp_543, VkDeviceAddress(0), VkDeviceAddress(0), 0ull, nullptr, &VkBuffer_uid_7289));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_BUFFER, uint64_t(VkBuffer_uid_7289), 7289ull));
    }

    // Create VkImage_uid_5056
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_10[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* extent = */ VkExtent3D{
        /* width = */ 4096u,
        /* height = */ 2048u,
        /* depth = */ 1u},
        /* mipLevels = */ 13u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_10, 0ull, nullptr, &VkImage_uid_5056));

        static VkMemoryRequirements VkMemoryRequirements_temp_544[1] = { VkMemoryRequirements{
        /* size = */ 44741120ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_5056, VkMemoryRequirements_temp_544));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_5056), 5056ull));
    }

    // Create VkImage_uid_5290
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_11[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* extent = */ VkExtent3D{
        /* width = */ 1024u,
        /* height = */ 1024u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_11, 0ull, nullptr, &VkImage_uid_5290));

        static VkMemoryRequirements VkMemoryRequirements_temp_545[1] = { VkMemoryRequirements{
        /* size = */ 4194304ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_5290, VkMemoryRequirements_temp_545));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_5290), 5290ull));
    }

    // Create VkImage_uid_6370
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_12[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R8G8B8A8_UNORM,
        /* extent = */ VkExtent3D{
        /* width = */ 256u,
        /* height = */ 256u,
        /* depth = */ 1u},
        /* mipLevels = */ 9u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_12, 0ull, nullptr, &VkImage_uid_6370));

        static VkMemoryRequirements VkMemoryRequirements_temp_546[1] = { VkMemoryRequirements{
        /* size = */ 351232ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6370, VkMemoryRequirements_temp_546));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6370), 6370ull));
    }

    // Create VkImage_uid_6887
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_13[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R32G32B32A32_SFLOAT,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_13, 0ull, nullptr, &VkImage_uid_6887));

        static VkMemoryRequirements VkMemoryRequirements_temp_547[1] = { VkMemoryRequirements{
        /* size = */ 23396352ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6887, VkMemoryRequirements_temp_547));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6887), 6887ull));
    }

    // Create VkImage_uid_6892
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_14[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_14, 0ull, nullptr, &VkImage_uid_6892));

        static VkMemoryRequirements VkMemoryRequirements_temp_548[1] = { VkMemoryRequirements{
        /* size = */ 5849088ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6892, VkMemoryRequirements_temp_548));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6892), 6892ull));
    }

    // Create VkImage_uid_6909
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_15[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_15, 0ull, nullptr, &VkImage_uid_6909));

        static VkMemoryRequirements VkMemoryRequirements_temp_549[1] = { VkMemoryRequirements{
        /* size = */ 5849088ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6909, VkMemoryRequirements_temp_549));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6909), 6909ull));
    }

    // Create VkImage_uid_6918
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_16[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_B8G8R8A8_UNORM,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 6u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_16, 0ull, nullptr, &VkImage_uid_6918));

        static VkMemoryRequirements VkMemoryRequirements_temp_550[1] = { VkMemoryRequirements{
        /* size = */ 65175552ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6918, VkMemoryRequirements_temp_550));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6918), 6918ull));
    }

    // Create VkImage_uid_6922
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_17[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_17, 0ull, nullptr, &VkImage_uid_6922));

        static VkMemoryRequirements VkMemoryRequirements_temp_551[1] = { VkMemoryRequirements{
        /* size = */ 5849088ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6922, VkMemoryRequirements_temp_551));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6922), 6922ull));
    }

    // Create VkImage_uid_6939
    {
        static VkImageCreateInfo VkImageCreateInfo_temp_18[1] = { VkImageCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkImageCreateFlags(0),
        /* imageType = */ VK_IMAGE_TYPE_2D,
        /* format = */ VK_FORMAT_R32_SFLOAT,
        /* extent = */ VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u},
        /* mipLevels = */ 1u,
        /* arrayLayers = */ 1u,
        /* samples = */ VK_SAMPLE_COUNT_1_BIT,
        /* tiling = */ VK_IMAGE_TILING_OPTIMAL,
        /* usage = */ VkImageUsageFlags(VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT),
        /* sharingMode = */ VK_SHARING_MODE_EXCLUSIVE,
        /* queueFamilyIndexCount = */ 0u,
        /* pQueueFamilyIndices = */ nullptr,
        /* initialLayout = */ VK_IMAGE_LAYOUT_UNDEFINED} };
        NV_VK_REPLAY(VulkanHelper_CreateImage(VkDevice_uid_4, VkImageCreateInfo_temp_18, 0ull, nullptr, &VkImage_uid_6939));

        static VkMemoryRequirements VkMemoryRequirements_temp_552[1] = { VkMemoryRequirements{
        /* size = */ 5849088ull,
        /* alignment = */ 1024ull,
        /* memoryTypeBits = */ 3u} };
        NV_VK_REPLAY(VulkanHelper_ValidateImageMemoryRequirements(VkDevice_uid_4, VkImage_uid_6939, VkMemoryRequirements_temp_552));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_IMAGE, uint64_t(VkImage_uid_6939), 6939ull));
    }

    // Create VkSampler_uid_5062
    {
        static VkSamplerCreateInfo VkSamplerCreateInfo_temp_6[1] = { VkSamplerCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSamplerCreateFlags(0),
        /* magFilter = */ VK_FILTER_LINEAR,
        /* minFilter = */ VK_FILTER_LINEAR,
        /* mipmapMode = */ VK_SAMPLER_MIPMAP_MODE_LINEAR,
        /* addressModeU = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeV = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeW = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* mipLodBias = */ 0.0f,
        /* anisotropyEnable = */ 1u,
        /* maxAnisotropy = */ HexToFloat(0x41800000/*16.0f*/),
        /* compareEnable = */ 0u,
        /* compareOp = */ VK_COMPARE_OP_ALWAYS,
        /* minLod = */ 0.0f,
        /* maxLod = */ HexToFloat(0x41500000/*13.0f*/),
        /* borderColor = */ VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        /* unnormalizedCoordinates = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_CreateSampler(VkDevice_uid_4, VkSamplerCreateInfo_temp_6, 0ull, nullptr, &VkSampler_uid_5062));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_SAMPLER, uint64_t(VkSampler_uid_5062), 5062ull));
    }

    // Create VkSampler_uid_5280
    {
        static VkSamplerCreateInfo VkSamplerCreateInfo_temp_7[1] = { VkSamplerCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSamplerCreateFlags(0),
        /* magFilter = */ VK_FILTER_LINEAR,
        /* minFilter = */ VK_FILTER_LINEAR,
        /* mipmapMode = */ VK_SAMPLER_MIPMAP_MODE_LINEAR,
        /* addressModeU = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeV = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeW = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* mipLodBias = */ 0.0f,
        /* anisotropyEnable = */ 0u,
        /* maxAnisotropy = */ HexToFloat(0x3F800000/*1.0f*/),
        /* compareEnable = */ 0u,
        /* compareOp = */ VK_COMPARE_OP_NEVER,
        /* minLod = */ HexToFloat(0xC47A0000/*-1000.0f*/),
        /* maxLod = */ HexToFloat(0x447A0000/*1000.0f*/),
        /* borderColor = */ VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
        /* unnormalizedCoordinates = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_CreateSampler(VkDevice_uid_4, VkSamplerCreateInfo_temp_7, 0ull, nullptr, &VkSampler_uid_5280));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_SAMPLER, uint64_t(VkSampler_uid_5280), 5280ull));
    }

    // Create VkSampler_uid_6376
    {
        static VkSamplerCreateInfo VkSamplerCreateInfo_temp_8[1] = { VkSamplerCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSamplerCreateFlags(0),
        /* magFilter = */ VK_FILTER_LINEAR,
        /* minFilter = */ VK_FILTER_LINEAR,
        /* mipmapMode = */ VK_SAMPLER_MIPMAP_MODE_LINEAR,
        /* addressModeU = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeV = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeW = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* mipLodBias = */ 0.0f,
        /* anisotropyEnable = */ 1u,
        /* maxAnisotropy = */ HexToFloat(0x41800000/*16.0f*/),
        /* compareEnable = */ 0u,
        /* compareOp = */ VK_COMPARE_OP_ALWAYS,
        /* minLod = */ 0.0f,
        /* maxLod = */ HexToFloat(0x41100000/*9.0f*/),
        /* borderColor = */ VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        /* unnormalizedCoordinates = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_CreateSampler(VkDevice_uid_4, VkSamplerCreateInfo_temp_8, 0ull, nullptr, &VkSampler_uid_6376));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_SAMPLER, uint64_t(VkSampler_uid_6376), 6376ull));
    }

    // Create VkSampler_uid_6895
    {
        static VkSamplerCreateInfo VkSamplerCreateInfo_temp_9[1] = { VkSamplerCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSamplerCreateFlags(0),
        /* magFilter = */ VK_FILTER_LINEAR,
        /* minFilter = */ VK_FILTER_LINEAR,
        /* mipmapMode = */ VK_SAMPLER_MIPMAP_MODE_LINEAR,
        /* addressModeU = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeV = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeW = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* mipLodBias = */ 0.0f,
        /* anisotropyEnable = */ 1u,
        /* maxAnisotropy = */ HexToFloat(0x41800000/*16.0f*/),
        /* compareEnable = */ 0u,
        /* compareOp = */ VK_COMPARE_OP_ALWAYS,
        /* minLod = */ 0.0f,
        /* maxLod = */ HexToFloat(0x3F800000/*1.0f*/),
        /* borderColor = */ VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        /* unnormalizedCoordinates = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_CreateSampler(VkDevice_uid_4, VkSamplerCreateInfo_temp_9, 0ull, nullptr, &VkSampler_uid_6895));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_SAMPLER, uint64_t(VkSampler_uid_6895), 6895ull));
    }

    // Create VkSampler_uid_6942
    {
        static VkSamplerCreateInfo VkSamplerCreateInfo_temp_10[1] = { VkSamplerCreateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkSamplerCreateFlags(0),
        /* magFilter = */ VK_FILTER_LINEAR,
        /* minFilter = */ VK_FILTER_LINEAR,
        /* mipmapMode = */ VK_SAMPLER_MIPMAP_MODE_LINEAR,
        /* addressModeU = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeV = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* addressModeW = */ VK_SAMPLER_ADDRESS_MODE_REPEAT,
        /* mipLodBias = */ 0.0f,
        /* anisotropyEnable = */ 1u,
        /* maxAnisotropy = */ HexToFloat(0x41800000/*16.0f*/),
        /* compareEnable = */ 0u,
        /* compareOp = */ VK_COMPARE_OP_ALWAYS,
        /* minLod = */ 0.0f,
        /* maxLod = */ HexToFloat(0x3F800000/*1.0f*/),
        /* borderColor = */ VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        /* unnormalizedCoordinates = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_CreateSampler(VkDevice_uid_4, VkSamplerCreateInfo_temp_10, 0ull, nullptr, &VkSampler_uid_6942));

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_SAMPLER, uint64_t(VkSampler_uid_6942), 6942ull));
    }

    // Create VkDeviceMemory_uid_5057
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_277[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 44741120ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_277[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_5056,
        /* memory = */ VkDeviceMemory_uid_5057,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_277[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962173337600ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_277,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_277, VulkanHelper_InitializeDeviceMemoryInfo_temp_277, &VkDeviceMemory_uid_5057, nullptr));
    }

    // Create VkDeviceMemory_uid_5077
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_264[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_278[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_264,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_278[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5076,
        /* memory = */ VkDeviceMemory_uid_5077,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_278[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962138669056ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_278,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_278, VulkanHelper_InitializeDeviceMemoryInfo_temp_278, &VkDeviceMemory_uid_5077, nullptr));
    }

    // Create VkDeviceMemory_uid_5082
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_265[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_279[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_265,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_279[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5081,
        /* memory = */ VkDeviceMemory_uid_5082,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_279[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962138734592ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_279,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_279, VulkanHelper_InitializeDeviceMemoryInfo_temp_279, &VkDeviceMemory_uid_5082, nullptr));
    }

    // Create VkDeviceMemory_uid_5156
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_266[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_280[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_266,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_280[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5155,
        /* memory = */ VkDeviceMemory_uid_5156,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_280[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962138603520ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_280,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_280, VulkanHelper_InitializeDeviceMemoryInfo_temp_280, &VkDeviceMemory_uid_5156, nullptr));
    }

    // Create VkDeviceMemory_uid_5158
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_267[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_281[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_267,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_281[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5157,
        /* memory = */ VkDeviceMemory_uid_5158,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_281[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962163703808ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_281,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_281, VulkanHelper_InitializeDeviceMemoryInfo_temp_281, &VkDeviceMemory_uid_5158, nullptr));
    }

    // Create VkDeviceMemory_uid_5186
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_268[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_282[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_268,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_282[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5185,
        /* memory = */ VkDeviceMemory_uid_5186,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_282[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962360639488ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_282,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_282, VulkanHelper_InitializeDeviceMemoryInfo_temp_282, &VkDeviceMemory_uid_5186, nullptr));
    }

    // Create VkDeviceMemory_uid_5191
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_269[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_283[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_269,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_283[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5190,
        /* memory = */ VkDeviceMemory_uid_5191,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_283[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962360705024ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_283,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_283, VulkanHelper_InitializeDeviceMemoryInfo_temp_283, &VkDeviceMemory_uid_5191, nullptr));
    }

    // Create VkDeviceMemory_uid_5234
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_270[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_284[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_270,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_284[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5233,
        /* memory = */ VkDeviceMemory_uid_5234,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_284[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361294848ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_284,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_284, VulkanHelper_InitializeDeviceMemoryInfo_temp_284, &VkDeviceMemory_uid_5234, nullptr));
    }

    // Create VkDeviceMemory_uid_5239
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_271[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_285[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_271,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_285[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5238,
        /* memory = */ VkDeviceMemory_uid_5239,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_285[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361360384ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_285,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_285, VulkanHelper_InitializeDeviceMemoryInfo_temp_285, &VkDeviceMemory_uid_5239, nullptr));
    }

    // Create VkDeviceMemory_uid_5255
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_272[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_286[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_272,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_286[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5254,
        /* memory = */ VkDeviceMemory_uid_5255,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_286[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361425920ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_286,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_286, VulkanHelper_InitializeDeviceMemoryInfo_temp_286, &VkDeviceMemory_uid_5255, nullptr));
    }

    // Create VkDeviceMemory_uid_5260
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_273[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_287[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_273,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_287[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5259,
        /* memory = */ VkDeviceMemory_uid_5260,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_287[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361491456ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_287,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_287, VulkanHelper_InitializeDeviceMemoryInfo_temp_287, &VkDeviceMemory_uid_5260, nullptr));
    }

    // Create VkDeviceMemory_uid_5291
    {
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_288[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ nullptr,
        /* allocationSize = */ 4194304ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindImageMemoryInfo VkBindImageMemoryInfo_pBindImageMemoryInfo_288[1] = { VkBindImageMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_IMAGE_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* image = */ VkImage_uid_5290,
        /* memory = */ VkDeviceMemory_uid_5291,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_288[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164948992ull,
        0u,
        /* pBindBufferMemoryInfo = */ nullptr,
        1u,
        /* pBindImageMemoryInfo = */ VkBindImageMemoryInfo_pBindImageMemoryInfo_288,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_288, VulkanHelper_InitializeDeviceMemoryInfo_temp_288, &VkDeviceMemory_uid_5291, nullptr));
    }

    // Create VkDeviceMemory_uid_5305
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_274[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_289[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_274,
        /* allocationSize = */ 1280ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_289[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5304,
        /* memory = */ VkDeviceMemory_uid_5305,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_289[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962163769344ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_289,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_289, VulkanHelper_InitializeDeviceMemoryInfo_temp_289, &VkDeviceMemory_uid_5305, nullptr));
    }

    // Create VkDeviceMemory_uid_5310
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_275[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_290[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_275,
        /* allocationSize = */ 256ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_290[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5309,
        /* memory = */ VkDeviceMemory_uid_5310,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_290[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962163834880ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_290,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_290, VulkanHelper_InitializeDeviceMemoryInfo_temp_290, &VkDeviceMemory_uid_5310, nullptr));
    }

    // Create VkDeviceMemory_uid_5384
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_276[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_291[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_276,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_291[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5383,
        /* memory = */ VkDeviceMemory_uid_5384,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_291[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361229312ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_291,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_291, VulkanHelper_InitializeDeviceMemoryInfo_temp_291, &VkDeviceMemory_uid_5384, nullptr));
    }

    // Create VkDeviceMemory_uid_5386
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_277[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_292[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_277,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_292[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5385,
        /* memory = */ VkDeviceMemory_uid_5386,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_292[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962163900416ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_292,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_292, VulkanHelper_InitializeDeviceMemoryInfo_temp_292, &VkDeviceMemory_uid_5386, nullptr));
    }

    // Create VkDeviceMemory_uid_5397
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_278[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_293[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_278,
        /* allocationSize = */ 935680ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_293[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5396,
        /* memory = */ VkDeviceMemory_uid_5397,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_293[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962361556992ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_293,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_293, VulkanHelper_InitializeDeviceMemoryInfo_temp_293, &VkDeviceMemory_uid_5397, nullptr));
    }

    // Create VkDeviceMemory_uid_5402
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_279[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_294[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_279,
        /* allocationSize = */ 239104ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_294[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5401,
        /* memory = */ VkDeviceMemory_uid_5402,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_294[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164228096ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_294,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_294, VulkanHelper_InitializeDeviceMemoryInfo_temp_294, &VkDeviceMemory_uid_5402, nullptr));
    }

    // Create VkDeviceMemory_uid_5407
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_280[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_295[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_280,
        /* allocationSize = */ 502272ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_295[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5406,
        /* memory = */ VkDeviceMemory_uid_5407,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_295[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962363064320ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_295,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_295, VulkanHelper_InitializeDeviceMemoryInfo_temp_295, &VkDeviceMemory_uid_5407, nullptr));
    }

    // Create VkDeviceMemory_uid_5412
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_281[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_296[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_281,
        /* allocationSize = */ 234496ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_296[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5411,
        /* memory = */ VkDeviceMemory_uid_5412,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_296[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164490240ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_296,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_296, VulkanHelper_InitializeDeviceMemoryInfo_temp_296, &VkDeviceMemory_uid_5412, nullptr));
    }

    // Create VkDeviceMemory_uid_5417
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_282[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_297[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_282,
        /* allocationSize = */ 990208ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_297[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5416,
        /* memory = */ VkDeviceMemory_uid_5417,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_297[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962170191872ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_297,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_297, VulkanHelper_InitializeDeviceMemoryInfo_temp_297, &VkDeviceMemory_uid_5417, nullptr));
    }

    // Create VkDeviceMemory_uid_5422
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_283[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_298[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_283,
        /* allocationSize = */ 434688ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_298[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5421,
        /* memory = */ VkDeviceMemory_uid_5422,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_298[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962363588608ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_298,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_298, VulkanHelper_InitializeDeviceMemoryInfo_temp_298, &VkDeviceMemory_uid_5422, nullptr));
    }

    // Create VkDeviceMemory_uid_5427
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_284[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_299[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_284,
        /* allocationSize = */ 710912ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_299[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5426,
        /* memory = */ VkDeviceMemory_uid_5427,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_299[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962171240448ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_299,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_299, VulkanHelper_InitializeDeviceMemoryInfo_temp_299, &VkDeviceMemory_uid_5427, nullptr));
    }

    // Create VkDeviceMemory_uid_5432
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_285[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_300[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_285,
        /* allocationSize = */ 360448ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_300[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5431,
        /* memory = */ VkDeviceMemory_uid_5432,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_300[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962169143296ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_300,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_300, VulkanHelper_InitializeDeviceMemoryInfo_temp_300, &VkDeviceMemory_uid_5432, nullptr));
    }

    // Create VkDeviceMemory_uid_5437
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_286[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_301[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_286,
        /* allocationSize = */ 1172224ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_301[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5436,
        /* memory = */ VkDeviceMemory_uid_5437,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_301[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962543484928ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_301,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_301, VulkanHelper_InitializeDeviceMemoryInfo_temp_301, &VkDeviceMemory_uid_5437, nullptr));
    }

    // Create VkDeviceMemory_uid_5442
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_287[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_302[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_287,
        /* allocationSize = */ 537856ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_302[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5441,
        /* memory = */ VkDeviceMemory_uid_5442,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_302[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962171961344ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_302,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_302, VulkanHelper_InitializeDeviceMemoryInfo_temp_302, &VkDeviceMemory_uid_5442, nullptr));
    }

    // Create VkDeviceMemory_uid_5445
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_288[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_303[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_288,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_303[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5444,
        /* memory = */ VkDeviceMemory_uid_5445,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_303[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962364047360ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_303,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_303, VulkanHelper_InitializeDeviceMemoryInfo_temp_303, &VkDeviceMemory_uid_5445, nullptr));
    }

    // Create VkDeviceMemory_uid_5447
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_289[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_304[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_289,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_304[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5446,
        /* memory = */ VkDeviceMemory_uid_5447,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_304[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962364112896ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_304,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_304, VulkanHelper_InitializeDeviceMemoryInfo_temp_304, &VkDeviceMemory_uid_5447, nullptr));
    }

    // Create VkDeviceMemory_uid_5458
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_290[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_305[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_290,
        /* allocationSize = */ 25088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_305[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5457,
        /* memory = */ VkDeviceMemory_uid_5458,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_305[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164817920ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_305,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_305, VulkanHelper_InitializeDeviceMemoryInfo_temp_305, &VkDeviceMemory_uid_5458, nullptr));
    }

    // Create VkDeviceMemory_uid_5463
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_291[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_306[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_291,
        /* allocationSize = */ 12800ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_306[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5462,
        /* memory = */ VkDeviceMemory_uid_5463,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_306[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164752384ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_306,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_306, VulkanHelper_InitializeDeviceMemoryInfo_temp_306, &VkDeviceMemory_uid_5463, nullptr));
    }

    // Create VkDeviceMemory_uid_5466
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_292[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_307[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_292,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_307[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5465,
        /* memory = */ VkDeviceMemory_uid_5466,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_307[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164883456ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_307,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_307, VulkanHelper_InitializeDeviceMemoryInfo_temp_307, &VkDeviceMemory_uid_5466, nullptr));
    }

    // Create VkDeviceMemory_uid_5468
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_293[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_308[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_293,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_308[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5467,
        /* memory = */ VkDeviceMemory_uid_5468,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_308[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962163965952ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_308,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_308, VulkanHelper_InitializeDeviceMemoryInfo_temp_308, &VkDeviceMemory_uid_5468, nullptr));
    }

    // Create VkDeviceMemory_uid_5479
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_294[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_309[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_294,
        /* allocationSize = */ 25088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_309[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5478,
        /* memory = */ VkDeviceMemory_uid_5479,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_309[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164097024ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_309,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_309, VulkanHelper_InitializeDeviceMemoryInfo_temp_309, &VkDeviceMemory_uid_5479, nullptr));
    }

    // Create VkDeviceMemory_uid_5484
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_295[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_310[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_295,
        /* allocationSize = */ 12800ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_310[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5483,
        /* memory = */ VkDeviceMemory_uid_5484,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_310[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164031488ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_310,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_310, VulkanHelper_InitializeDeviceMemoryInfo_temp_310, &VkDeviceMemory_uid_5484, nullptr));
    }

    // Create VkDeviceMemory_uid_5487
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_296[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_311[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_296,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_311[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5486,
        /* memory = */ VkDeviceMemory_uid_5487,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_311[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962164162560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_311,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_311, VulkanHelper_InitializeDeviceMemoryInfo_temp_311, &VkDeviceMemory_uid_5487, nullptr));
    }

    // Create VkDeviceMemory_uid_5489
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_297[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_312[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_297,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_312[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5488,
        /* memory = */ VkDeviceMemory_uid_5489,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_312[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362540032ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_312,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_312, VulkanHelper_InitializeDeviceMemoryInfo_temp_312, &VkDeviceMemory_uid_5489, nullptr));
    }

    // Create VkDeviceMemory_uid_5500
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_298[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_313[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_298,
        /* allocationSize = */ 25088ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_313[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5499,
        /* memory = */ VkDeviceMemory_uid_5500,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_313[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362671104ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_313,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_313, VulkanHelper_InitializeDeviceMemoryInfo_temp_313, &VkDeviceMemory_uid_5500, nullptr));
    }

    // Create VkDeviceMemory_uid_5505
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_299[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_314[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_299,
        /* allocationSize = */ 12800ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_314[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5504,
        /* memory = */ VkDeviceMemory_uid_5505,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_314[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362736640ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_314,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_314, VulkanHelper_InitializeDeviceMemoryInfo_temp_314, &VkDeviceMemory_uid_5505, nullptr));
    }

    // Create VkDeviceMemory_uid_5508
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_300[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_315[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_300,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_315[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5507,
        /* memory = */ VkDeviceMemory_uid_5508,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_315[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362605568ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_315,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_315, VulkanHelper_InitializeDeviceMemoryInfo_temp_315, &VkDeviceMemory_uid_5508, nullptr));
    }

    // Create VkDeviceMemory_uid_5510
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_301[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_316[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_301,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_316[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5509,
        /* memory = */ VkDeviceMemory_uid_5510,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_316[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362802176ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_316,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_316, VulkanHelper_InitializeDeviceMemoryInfo_temp_316, &VkDeviceMemory_uid_5510, nullptr));
    }

    // Create VkDeviceMemory_uid_5521
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_302[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_317[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_302,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_317[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5520,
        /* memory = */ VkDeviceMemory_uid_5521,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_317[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962172551168ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_317,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_317, VulkanHelper_InitializeDeviceMemoryInfo_temp_317, &VkDeviceMemory_uid_5521, nullptr));
    }

    // Create VkDeviceMemory_uid_5526
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_303[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_318[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_303,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_318[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5525,
        /* memory = */ VkDeviceMemory_uid_5526,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_318[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962169536512ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_318,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_318, VulkanHelper_InitializeDeviceMemoryInfo_temp_318, &VkDeviceMemory_uid_5526, nullptr));
    }

    // Create VkDeviceMemory_uid_5529
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_304[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_319[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_304,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_319[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5528,
        /* memory = */ VkDeviceMemory_uid_5529,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_319[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362867712ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_319,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_319, VulkanHelper_InitializeDeviceMemoryInfo_temp_319, &VkDeviceMemory_uid_5529, nullptr));
    }

    // Create VkDeviceMemory_uid_5531
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_305[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_320[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_305,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_320[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5530,
        /* memory = */ VkDeviceMemory_uid_5531,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_320[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362933248ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_320,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_320, VulkanHelper_InitializeDeviceMemoryInfo_temp_320, &VkDeviceMemory_uid_5531, nullptr));
    }

    // Create VkDeviceMemory_uid_5542
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_306[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_321[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_306,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_321[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5541,
        /* memory = */ VkDeviceMemory_uid_5542,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_321[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962545123328ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_321,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_321, VulkanHelper_InitializeDeviceMemoryInfo_temp_321, &VkDeviceMemory_uid_5542, nullptr));
    }

    // Create VkDeviceMemory_uid_5547
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_307[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_322[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_307,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_322[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5546,
        /* memory = */ VkDeviceMemory_uid_5547,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_322[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962169798656ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_322,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_322, VulkanHelper_InitializeDeviceMemoryInfo_temp_322, &VkDeviceMemory_uid_5547, nullptr));
    }

    // Create VkDeviceMemory_uid_5550
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_308[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_323[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_308,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_323[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5549,
        /* memory = */ VkDeviceMemory_uid_5550,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_323[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962362998784ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_323,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_323, VulkanHelper_InitializeDeviceMemoryInfo_temp_323, &VkDeviceMemory_uid_5550, nullptr));
    }

    // Create VkDeviceMemory_uid_5552
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_309[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_324[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_309,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_324[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5551,
        /* memory = */ VkDeviceMemory_uid_5552,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_324[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962170060800ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_324,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_324, VulkanHelper_InitializeDeviceMemoryInfo_temp_324, &VkDeviceMemory_uid_5552, nullptr));
    }

    // Create VkDeviceMemory_uid_5563
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_310[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_325[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_310,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_325[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5562,
        /* memory = */ VkDeviceMemory_uid_5563,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_325[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962545582080ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_325,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_325, VulkanHelper_InitializeDeviceMemoryInfo_temp_325, &VkDeviceMemory_uid_5563, nullptr));
    }

    // Create VkDeviceMemory_uid_5568
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_311[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_326[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_311,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_326[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5567,
        /* memory = */ VkDeviceMemory_uid_5568,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_326[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962544664576ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_326,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_326, VulkanHelper_InitializeDeviceMemoryInfo_temp_326, &VkDeviceMemory_uid_5568, nullptr));
    }

    // Create VkDeviceMemory_uid_5571
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_312[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_327[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_312,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_327[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5570,
        /* memory = */ VkDeviceMemory_uid_5571,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_327[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962170126336ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_327,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_327, VulkanHelper_InitializeDeviceMemoryInfo_temp_327, &VkDeviceMemory_uid_5571, nullptr));
    }

    // Create VkDeviceMemory_uid_5573
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_313[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_328[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_313,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_328[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5572,
        /* memory = */ VkDeviceMemory_uid_5573,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_328[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962544926720ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_328,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_328, VulkanHelper_InitializeDeviceMemoryInfo_temp_328, &VkDeviceMemory_uid_5573, nullptr));
    }

    // Create VkDeviceMemory_uid_5584
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_314[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_329[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_314,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_329[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5583,
        /* memory = */ VkDeviceMemory_uid_5584,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_329[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546499584ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_329,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_329, VulkanHelper_InitializeDeviceMemoryInfo_temp_329, &VkDeviceMemory_uid_5584, nullptr));
    }

    // Create VkDeviceMemory_uid_5589
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_315[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_330[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_315,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_330[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5588,
        /* memory = */ VkDeviceMemory_uid_5589,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_330[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546040832ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_330,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_330, VulkanHelper_InitializeDeviceMemoryInfo_temp_330, &VkDeviceMemory_uid_5589, nullptr));
    }

    // Create VkDeviceMemory_uid_5592
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_316[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_331[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_316,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_331[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5591,
        /* memory = */ VkDeviceMemory_uid_5592,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_331[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962544992256ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_331,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_331, VulkanHelper_InitializeDeviceMemoryInfo_temp_331, &VkDeviceMemory_uid_5592, nullptr));
    }

    // Create VkDeviceMemory_uid_5594
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_317[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_332[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_317,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_332[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5593,
        /* memory = */ VkDeviceMemory_uid_5594,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_332[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962545057792ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_332,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_332, VulkanHelper_InitializeDeviceMemoryInfo_temp_332, &VkDeviceMemory_uid_5594, nullptr));
    }

    // Create VkDeviceMemory_uid_5605
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_318[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_333[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_318,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_333[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5604,
        /* memory = */ VkDeviceMemory_uid_5605,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_333[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962547417088ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_333,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_333, VulkanHelper_InitializeDeviceMemoryInfo_temp_333, &VkDeviceMemory_uid_5605, nullptr));
    }

    // Create VkDeviceMemory_uid_5610
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_319[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_334[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_319,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_334[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5609,
        /* memory = */ VkDeviceMemory_uid_5610,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_334[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546958336ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_334,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_334, VulkanHelper_InitializeDeviceMemoryInfo_temp_334, &VkDeviceMemory_uid_5610, nullptr));
    }

    // Create VkDeviceMemory_uid_5613
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_320[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_335[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_320,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_335[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5612,
        /* memory = */ VkDeviceMemory_uid_5613,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_335[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546302976ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_335,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_335, VulkanHelper_InitializeDeviceMemoryInfo_temp_335, &VkDeviceMemory_uid_5613, nullptr));
    }

    // Create VkDeviceMemory_uid_5615
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_321[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_336[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_321,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_336[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5614,
        /* memory = */ VkDeviceMemory_uid_5615,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_336[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546368512ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_336,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_336, VulkanHelper_InitializeDeviceMemoryInfo_temp_336, &VkDeviceMemory_uid_5615, nullptr));
    }

    // Create VkDeviceMemory_uid_5626
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_322[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_337[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_322,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_337[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5625,
        /* memory = */ VkDeviceMemory_uid_5626,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_337[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962548334592ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_337,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_337, VulkanHelper_InitializeDeviceMemoryInfo_temp_337, &VkDeviceMemory_uid_5626, nullptr));
    }

    // Create VkDeviceMemory_uid_5631
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_323[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_338[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_323,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_338[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5630,
        /* memory = */ VkDeviceMemory_uid_5631,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_338[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962547875840ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_338,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_338, VulkanHelper_InitializeDeviceMemoryInfo_temp_338, &VkDeviceMemory_uid_5631, nullptr));
    }

    // Create VkDeviceMemory_uid_5634
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_324[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_339[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_324,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_339[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5633,
        /* memory = */ VkDeviceMemory_uid_5634,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_339[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962546434048ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_339,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_339, VulkanHelper_InitializeDeviceMemoryInfo_temp_339, &VkDeviceMemory_uid_5634, nullptr));
    }

    // Create VkDeviceMemory_uid_5636
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_325[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_340[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_325,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_340[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5635,
        /* memory = */ VkDeviceMemory_uid_5636,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_340[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962547220480ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_340,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_340, VulkanHelper_InitializeDeviceMemoryInfo_temp_340, &VkDeviceMemory_uid_5636, nullptr));
    }

    // Create VkDeviceMemory_uid_5647
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_326[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_341[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_326,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_341[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5646,
        /* memory = */ VkDeviceMemory_uid_5647,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_341[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549252096ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_341,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_341, VulkanHelper_InitializeDeviceMemoryInfo_temp_341, &VkDeviceMemory_uid_5647, nullptr));
    }

    // Create VkDeviceMemory_uid_5652
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_327[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_342[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_327,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_342[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5651,
        /* memory = */ VkDeviceMemory_uid_5652,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_342[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962548793344ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_342,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_342, VulkanHelper_InitializeDeviceMemoryInfo_temp_342, &VkDeviceMemory_uid_5652, nullptr));
    }

    // Create VkDeviceMemory_uid_5655
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_328[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_343[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_328,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_343[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5654,
        /* memory = */ VkDeviceMemory_uid_5655,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_343[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962547286016ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_343,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_343, VulkanHelper_InitializeDeviceMemoryInfo_temp_343, &VkDeviceMemory_uid_5655, nullptr));
    }

    // Create VkDeviceMemory_uid_5657
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_329[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_344[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_329,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_344[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5656,
        /* memory = */ VkDeviceMemory_uid_5657,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_344[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962547351552ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_344,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_344, VulkanHelper_InitializeDeviceMemoryInfo_temp_344, &VkDeviceMemory_uid_5657, nullptr));
    }

    // Create VkDeviceMemory_uid_5668
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_330[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_345[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_330,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_345[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5667,
        /* memory = */ VkDeviceMemory_uid_5668,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_345[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550169600ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_345,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_345, VulkanHelper_InitializeDeviceMemoryInfo_temp_345, &VkDeviceMemory_uid_5668, nullptr));
    }

    // Create VkDeviceMemory_uid_5673
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_331[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_346[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_331,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_346[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5672,
        /* memory = */ VkDeviceMemory_uid_5673,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_346[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549710848ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_346,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_346, VulkanHelper_InitializeDeviceMemoryInfo_temp_346, &VkDeviceMemory_uid_5673, nullptr));
    }

    // Create VkDeviceMemory_uid_5676
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_332[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_347[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_332,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_347[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5675,
        /* memory = */ VkDeviceMemory_uid_5676,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_347[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962548137984ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_347,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_347, VulkanHelper_InitializeDeviceMemoryInfo_temp_347, &VkDeviceMemory_uid_5676, nullptr));
    }

    // Create VkDeviceMemory_uid_5678
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_333[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_348[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_333,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_348[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5677,
        /* memory = */ VkDeviceMemory_uid_5678,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_348[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962548203520ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_348,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_348, VulkanHelper_InitializeDeviceMemoryInfo_temp_348, &VkDeviceMemory_uid_5678, nullptr));
    }

    // Create VkDeviceMemory_uid_5689
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_334[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_349[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_334,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_349[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5688,
        /* memory = */ VkDeviceMemory_uid_5689,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_349[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551087104ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_349,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_349, VulkanHelper_InitializeDeviceMemoryInfo_temp_349, &VkDeviceMemory_uid_5689, nullptr));
    }

    // Create VkDeviceMemory_uid_5694
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_335[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_350[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_335,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_350[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5693,
        /* memory = */ VkDeviceMemory_uid_5694,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_350[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550628352ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_350,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_350, VulkanHelper_InitializeDeviceMemoryInfo_temp_350, &VkDeviceMemory_uid_5694, nullptr));
    }

    // Create VkDeviceMemory_uid_5697
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_336[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_351[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_336,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_351[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5696,
        /* memory = */ VkDeviceMemory_uid_5697,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_351[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962548269056ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_351,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_351, VulkanHelper_InitializeDeviceMemoryInfo_temp_351, &VkDeviceMemory_uid_5697, nullptr));
    }

    // Create VkDeviceMemory_uid_5699
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_337[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_352[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_337,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_352[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5698,
        /* memory = */ VkDeviceMemory_uid_5699,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_352[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549055488ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_352,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_352, VulkanHelper_InitializeDeviceMemoryInfo_temp_352, &VkDeviceMemory_uid_5699, nullptr));
    }

    // Create VkDeviceMemory_uid_5710
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_338[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_353[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_338,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_353[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5709,
        /* memory = */ VkDeviceMemory_uid_5710,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_353[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552004608ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_353,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_353, VulkanHelper_InitializeDeviceMemoryInfo_temp_353, &VkDeviceMemory_uid_5710, nullptr));
    }

    // Create VkDeviceMemory_uid_5715
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_339[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_354[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_339,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_354[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5714,
        /* memory = */ VkDeviceMemory_uid_5715,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_354[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551545856ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_354,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_354, VulkanHelper_InitializeDeviceMemoryInfo_temp_354, &VkDeviceMemory_uid_5715, nullptr));
    }

    // Create VkDeviceMemory_uid_5718
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_340[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_355[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_340,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_355[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5717,
        /* memory = */ VkDeviceMemory_uid_5718,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_355[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549121024ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_355,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_355, VulkanHelper_InitializeDeviceMemoryInfo_temp_355, &VkDeviceMemory_uid_5718, nullptr));
    }

    // Create VkDeviceMemory_uid_5720
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_341[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_356[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_341,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_356[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5719,
        /* memory = */ VkDeviceMemory_uid_5720,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_356[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549186560ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_356,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_356, VulkanHelper_InitializeDeviceMemoryInfo_temp_356, &VkDeviceMemory_uid_5720, nullptr));
    }

    // Create VkDeviceMemory_uid_5731
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_342[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_357[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_342,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_357[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5730,
        /* memory = */ VkDeviceMemory_uid_5731,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_357[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552922112ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_357,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_357, VulkanHelper_InitializeDeviceMemoryInfo_temp_357, &VkDeviceMemory_uid_5731, nullptr));
    }

    // Create VkDeviceMemory_uid_5736
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_343[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_358[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_343,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_358[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5735,
        /* memory = */ VkDeviceMemory_uid_5736,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_358[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552463360ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_358,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_358, VulkanHelper_InitializeDeviceMemoryInfo_temp_358, &VkDeviceMemory_uid_5736, nullptr));
    }

    // Create VkDeviceMemory_uid_5739
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_344[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_359[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_344,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_359[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5738,
        /* memory = */ VkDeviceMemory_uid_5739,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_359[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962549972992ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_359,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_359, VulkanHelper_InitializeDeviceMemoryInfo_temp_359, &VkDeviceMemory_uid_5739, nullptr));
    }

    // Create VkDeviceMemory_uid_5741
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_345[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_360[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_345,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_360[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5740,
        /* memory = */ VkDeviceMemory_uid_5741,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_360[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550038528ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_360,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_360, VulkanHelper_InitializeDeviceMemoryInfo_temp_360, &VkDeviceMemory_uid_5741, nullptr));
    }

    // Create VkDeviceMemory_uid_5752
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_346[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_361[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_346,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_361[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5751,
        /* memory = */ VkDeviceMemory_uid_5752,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_361[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962553839616ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_361,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_361, VulkanHelper_InitializeDeviceMemoryInfo_temp_361, &VkDeviceMemory_uid_5752, nullptr));
    }

    // Create VkDeviceMemory_uid_5757
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_347[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_362[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_347,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_362[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5756,
        /* memory = */ VkDeviceMemory_uid_5757,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_362[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962553380864ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_362,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_362, VulkanHelper_InitializeDeviceMemoryInfo_temp_362, &VkDeviceMemory_uid_5757, nullptr));
    }

    // Create VkDeviceMemory_uid_5760
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_348[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_363[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_348,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_363[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5759,
        /* memory = */ VkDeviceMemory_uid_5760,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_363[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550104064ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_363,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_363, VulkanHelper_InitializeDeviceMemoryInfo_temp_363, &VkDeviceMemory_uid_5760, nullptr));
    }

    // Create VkDeviceMemory_uid_5762
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_349[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_364[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_349,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_364[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5761,
        /* memory = */ VkDeviceMemory_uid_5762,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_364[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550890496ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_364,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_364, VulkanHelper_InitializeDeviceMemoryInfo_temp_364, &VkDeviceMemory_uid_5762, nullptr));
    }

    // Create VkDeviceMemory_uid_5773
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_350[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_365[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_350,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_365[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5772,
        /* memory = */ VkDeviceMemory_uid_5773,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_365[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962554757120ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_365,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_365, VulkanHelper_InitializeDeviceMemoryInfo_temp_365, &VkDeviceMemory_uid_5773, nullptr));
    }

    // Create VkDeviceMemory_uid_5778
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_351[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_366[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_351,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_366[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5777,
        /* memory = */ VkDeviceMemory_uid_5778,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_366[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962554298368ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_366,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_366, VulkanHelper_InitializeDeviceMemoryInfo_temp_366, &VkDeviceMemory_uid_5778, nullptr));
    }

    // Create VkDeviceMemory_uid_5781
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_352[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_367[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_352,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_367[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5780,
        /* memory = */ VkDeviceMemory_uid_5781,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_367[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962550956032ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_367,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_367, VulkanHelper_InitializeDeviceMemoryInfo_temp_367, &VkDeviceMemory_uid_5781, nullptr));
    }

    // Create VkDeviceMemory_uid_5783
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_353[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_368[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_353,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_368[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5782,
        /* memory = */ VkDeviceMemory_uid_5783,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_368[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551021568ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_368,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_368, VulkanHelper_InitializeDeviceMemoryInfo_temp_368, &VkDeviceMemory_uid_5783, nullptr));
    }

    // Create VkDeviceMemory_uid_5794
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_354[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_369[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_354,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_369[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5793,
        /* memory = */ VkDeviceMemory_uid_5794,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_369[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962555674624ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_369,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_369, VulkanHelper_InitializeDeviceMemoryInfo_temp_369, &VkDeviceMemory_uid_5794, nullptr));
    }

    // Create VkDeviceMemory_uid_5799
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_355[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_370[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_355,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_370[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5798,
        /* memory = */ VkDeviceMemory_uid_5799,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_370[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962555215872ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_370,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_370, VulkanHelper_InitializeDeviceMemoryInfo_temp_370, &VkDeviceMemory_uid_5799, nullptr));
    }

    // Create VkDeviceMemory_uid_5802
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_356[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_371[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_356,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_371[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5801,
        /* memory = */ VkDeviceMemory_uid_5802,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_371[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551808000ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_371,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_371, VulkanHelper_InitializeDeviceMemoryInfo_temp_371, &VkDeviceMemory_uid_5802, nullptr));
    }

    // Create VkDeviceMemory_uid_5804
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_357[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_372[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_357,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_372[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5803,
        /* memory = */ VkDeviceMemory_uid_5804,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_372[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551873536ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_372,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_372, VulkanHelper_InitializeDeviceMemoryInfo_temp_372, &VkDeviceMemory_uid_5804, nullptr));
    }

    // Create VkDeviceMemory_uid_5815
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_358[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_373[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_358,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_373[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5814,
        /* memory = */ VkDeviceMemory_uid_5815,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_373[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962556592128ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_373,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_373, VulkanHelper_InitializeDeviceMemoryInfo_temp_373, &VkDeviceMemory_uid_5815, nullptr));
    }

    // Create VkDeviceMemory_uid_5820
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_359[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_374[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_359,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_374[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5819,
        /* memory = */ VkDeviceMemory_uid_5820,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_374[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962556133376ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_374,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_374, VulkanHelper_InitializeDeviceMemoryInfo_temp_374, &VkDeviceMemory_uid_5820, nullptr));
    }

    // Create VkDeviceMemory_uid_5823
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_360[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_375[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_360,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_375[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5822,
        /* memory = */ VkDeviceMemory_uid_5823,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_375[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962551939072ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_375,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_375, VulkanHelper_InitializeDeviceMemoryInfo_temp_375, &VkDeviceMemory_uid_5823, nullptr));
    }

    // Create VkDeviceMemory_uid_5825
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_361[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_376[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_361,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_376[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5824,
        /* memory = */ VkDeviceMemory_uid_5825,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_376[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552725504ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_376,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_376, VulkanHelper_InitializeDeviceMemoryInfo_temp_376, &VkDeviceMemory_uid_5825, nullptr));
    }

    // Create VkDeviceMemory_uid_5836
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_362[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_377[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_362,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_377[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5835,
        /* memory = */ VkDeviceMemory_uid_5836,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_377[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557509632ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_377,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_377, VulkanHelper_InitializeDeviceMemoryInfo_temp_377, &VkDeviceMemory_uid_5836, nullptr));
    }

    // Create VkDeviceMemory_uid_5841
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_363[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_378[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_363,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_378[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5840,
        /* memory = */ VkDeviceMemory_uid_5841,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_378[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557050880ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_378,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_378, VulkanHelper_InitializeDeviceMemoryInfo_temp_378, &VkDeviceMemory_uid_5841, nullptr));
    }

    // Create VkDeviceMemory_uid_5844
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_364[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_379[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_364,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_379[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5843,
        /* memory = */ VkDeviceMemory_uid_5844,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_379[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552791040ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_379,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_379, VulkanHelper_InitializeDeviceMemoryInfo_temp_379, &VkDeviceMemory_uid_5844, nullptr));
    }

    // Create VkDeviceMemory_uid_5846
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_365[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_380[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_365,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_380[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5845,
        /* memory = */ VkDeviceMemory_uid_5846,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_380[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962552856576ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_380,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_380, VulkanHelper_InitializeDeviceMemoryInfo_temp_380, &VkDeviceMemory_uid_5846, nullptr));
    }

    // Create VkDeviceMemory_uid_5857
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_366[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_381[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_366,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_381[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5856,
        /* memory = */ VkDeviceMemory_uid_5857,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_381[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962558427136ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_381,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_381, VulkanHelper_InitializeDeviceMemoryInfo_temp_381, &VkDeviceMemory_uid_5857, nullptr));
    }

    // Create VkDeviceMemory_uid_5862
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_367[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_382[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_367,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_382[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5861,
        /* memory = */ VkDeviceMemory_uid_5862,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_382[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962557968384ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_382,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_382, VulkanHelper_InitializeDeviceMemoryInfo_temp_382, &VkDeviceMemory_uid_5862, nullptr));
    }

    // Create VkDeviceMemory_uid_5865
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_368[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_383[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_368,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_383[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5864,
        /* memory = */ VkDeviceMemory_uid_5865,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_383[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962553643008ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_383,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_383, VulkanHelper_InitializeDeviceMemoryInfo_temp_383, &VkDeviceMemory_uid_5865, nullptr));
    }

    // Create VkDeviceMemory_uid_5867
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_369[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_384[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_369,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_384[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5866,
        /* memory = */ VkDeviceMemory_uid_5867,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_384[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962553708544ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_384,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_384, VulkanHelper_InitializeDeviceMemoryInfo_temp_384, &VkDeviceMemory_uid_5867, nullptr));
    }

    // Create VkDeviceMemory_uid_5878
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_370[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_385[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_370,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_385[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5877,
        /* memory = */ VkDeviceMemory_uid_5878,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_385[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962559344640ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_385,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_385, VulkanHelper_InitializeDeviceMemoryInfo_temp_385, &VkDeviceMemory_uid_5878, nullptr));
    }

    // Create VkDeviceMemory_uid_5883
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_371[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_386[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_371,
        /* allocationSize = */ 235264ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_386[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5882,
        /* memory = */ VkDeviceMemory_uid_5883,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_386[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962558885888ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_386,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_386, VulkanHelper_InitializeDeviceMemoryInfo_temp_386, &VkDeviceMemory_uid_5883, nullptr));
    }

    // Create VkDeviceMemory_uid_5886
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_372[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_387[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_372,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_387[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5885,
        /* memory = */ VkDeviceMemory_uid_5886,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_387[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962553774080ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_387,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_387, VulkanHelper_InitializeDeviceMemoryInfo_temp_387, &VkDeviceMemory_uid_5886, nullptr));
    }

    // Create VkDeviceMemory_uid_5888
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_373[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_388[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_373,
        /* allocationSize = */ 64ull,
        /* memoryTypeIndex = */ 2u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_388[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5887,
        /* memory = */ VkDeviceMemory_uid_5888,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_388[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962554560512ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_388,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_388, VulkanHelper_InitializeDeviceMemoryInfo_temp_388, &VkDeviceMemory_uid_5888, nullptr));
    }

    // Create VkDeviceMemory_uid_5899
    {
        static VkMemoryAllocateFlagsInfo VkMemoryAllocateFlagsInfo_pNext_374[1] = { VkMemoryAllocateFlagsInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO,
        /* pNext = */ nullptr,
        /* flags = */ VkMemoryAllocateFlags(VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT),
        /* deviceMask = */ 0u} };
        static VkMemoryAllocateInfo VkMemoryAllocateInfo_temp_389[1] = { VkMemoryAllocateInfo{
        /* sType = */ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        /* pNext = */ VkMemoryAllocateFlagsInfo_pNext_374,
        /* allocationSize = */ 440064ull,
        /* memoryTypeIndex = */ 1u} };
        static VkBindBufferMemoryInfo VkBindBufferMemoryInfo_pBindBufferMemoryInfo_389[1] = { VkBindBufferMemoryInfo{
        /* sType = */ VK_STRUCTURE_TYPE_BIND_BUFFER_MEMORY_INFO,
        /* pNext = */ nullptr,
        /* buffer = */ VkBuffer_uid_5898,
        /* memory = */ VkDeviceMemory_uid_5899,
        /* memoryOffset = */ 0ull} };
        static VulkanHelper_InitializeDeviceMemoryInfo VulkanHelper_InitializeDeviceMemoryInfo_temp_389[1] = { VulkanHelper_InitializeDeviceMemoryInfo{/* .version = */ 2u,
        962560262144ull,
        1u,
        /* pBindBufferMemoryInfo = */ VkBindBufferMemoryInfo_pBindBufferMemoryInfo_389,
        0u,
        /* pBindImageMemoryInfo = */ nullptr,
        0u,
        /* pBindAccelerationStructureMemoryInfoNV = */ nullptr,
        0u,
        /* pVideoSessions = */ nullptr,
        /* pVideoBindMemory = */ nullptr,
        VK_TRUE} };
        NV_VK_REPLAY(VulkanHelper_AllocateAndInitializeMemory3(VkDevice_uid_4, VkMemoryAllocateInfo_temp_389, VulkanHelper_InitializeDeviceMemoryInfo_temp_389, &VkDeviceMemory_uid_5899, nullptr));
    }
}

NV_REPLAY_END_RESOURCE_INIT()
