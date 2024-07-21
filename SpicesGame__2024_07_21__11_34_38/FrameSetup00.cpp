//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: FrameSetup00.cpp
// 
//-----------------------------------------------------------------------------

#include <vector>
#include <sstream>

#include <vulkan/vulkan.h>

#include "VulkanHelpers.h"
#include "VulkanReplay.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "Application.h"

NV_REPLAY_BEGIN_FRAME_SETUP()

//-----------------------------------------------------------------------------
// SetInitialFrameState00
//-----------------------------------------------------------------------------
void SetInitialFrameState00()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    NV_MESSAGE_VERBOSE("Initializing resources...(%d/%d)", 1, g_ResourceInitFunctionCount);
    NV_VK_REPLAY(VulkanHelper_InitBegin(VkInstance_uid_1));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_366[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DEVICE,
    /* objectHandle = */ uint64_t(VkDevice_uid_4),
    /* pObjectName = */ "NVIDIA GeForce RTX 4060"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_366));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_367[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SWAPCHAIN_KHR,
    /* objectHandle = */ uint64_t(VkSwapchainKHR_uid_13),
    /* pObjectName = */ "SpicesEngineSwapChainKHR"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_367));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_368[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5076),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_368));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_369[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5081),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_369));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_370[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5155),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_370));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_371[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5157),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_371));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_372[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5185),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_372));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_373[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5190),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_373));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_374[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5233),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_374));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_375[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5238),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_375));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_376[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5254),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_376));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_377[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5259),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_377));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_378[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5304),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_378));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_379[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5309),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_379));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_380[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5383),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_380));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_381[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5385),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_381));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_382[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5396),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_382));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_383[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5401),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_383));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_384[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5406),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_384));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_385[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5411),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_385));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_386[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5416),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_386));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_387[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5421),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_387));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_388[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5426),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_388));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_389[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5431),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_389));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_390[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5436),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_390));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_391[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5441),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_391));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_392[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5444),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_392));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_393[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5446),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_393));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_394[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5457),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_394));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_395[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5462),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_395));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_396[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5465),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_396));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_397[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5467),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_397));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_398[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5478),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_398));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_399[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5483),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_399));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_400[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5486),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_400));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_401[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5488),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_401));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_402[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5499),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_402));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_403[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5504),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_403));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_404[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5507),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_404));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_405[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5509),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_405));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_406[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5520),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_406));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_407[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5525),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_407));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_408[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5528),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_408));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_409[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5530),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_409));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_410[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5541),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_410));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_411[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5546),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_411));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_412[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5549),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_412));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_413[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5551),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_413));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_414[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5562),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_414));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_415[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5567),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_415));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_416[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5570),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_416));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_417[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5572),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_417));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_418[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5583),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_418));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_419[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5588),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_419));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_420[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5591),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_420));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_421[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5593),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_421));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_422[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5604),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_422));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_423[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5609),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_423));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_424[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5612),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_424));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_425[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5614),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_425));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_426[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5625),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_426));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_427[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5630),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_427));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_428[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5633),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_428));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_429[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5635),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_429));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_430[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5646),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_430));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_431[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5651),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_431));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_432[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5654),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_432));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_433[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5656),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_433));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_434[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5667),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_434));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_435[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5672),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_435));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_436[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5675),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_436));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_437[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5677),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_437));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_438[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5688),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_438));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_439[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5693),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_439));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_440[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5696),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_440));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_441[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5698),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_441));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_442[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5709),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_442));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_443[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5714),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_443));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_444[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5717),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_444));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_445[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5719),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_445));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_446[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5730),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_446));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_447[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5735),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_447));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_448[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5738),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_448));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_449[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5740),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_449));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_450[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5751),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_450));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_451[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5756),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_451));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_452[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5759),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_452));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_453[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5761),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_453));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_454[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5772),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_454));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_455[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5777),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_455));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_456[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5780),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_456));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_457[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5782),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_457));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_458[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5793),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_458));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_459[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5798),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_459));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_460[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5801),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_460));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_461[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5803),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_461));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_462[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5814),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_462));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_463[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5819),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_463));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_464[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5822),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_464));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_465[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5824),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_465));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_466[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5835),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_466));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_467[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5840),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_467));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_468[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5843),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_468));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_469[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5845),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_469));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_470[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5856),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_470));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_471[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5861),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_471));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_472[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5864),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_472));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_473[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5866),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_473));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_474[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5877),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_474));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_475[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5882),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_475));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_476[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5885),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_476));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_477[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5887),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_477));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_478[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5898),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_478));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_479[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5903),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_479));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_480[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5906),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_480));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_481[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5908),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_481));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_482[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5919),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_482));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_483[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5924),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_483));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_484[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5927),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_484));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_485[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5929),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_485));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_486[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5940),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_486));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_487[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5945),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_487));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_488[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5948),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_488));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_489[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5950),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_489));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_490[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5961),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_490));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_491[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5966),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_491));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_492[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5969),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_492));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_493[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5971),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_493));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_494[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5982),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_494));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_495[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5987),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_495));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_496[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5990),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_496));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_497[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_5992),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_497));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_498[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6003),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_498));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_499[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6008),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_499));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_500[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6011),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_500));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_501[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6013),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_501));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_502[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6024),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_502));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_503[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6029),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_503));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_504[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6032),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_504));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_505[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6034),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_505));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_506[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6045),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_506));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_507[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6050),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_507));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_508[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6053),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_508));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_509[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6055),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_509));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_510[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6066),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_510));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_511[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6071),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_511));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_512[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6074),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_512));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_513[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6076),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_513));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_514[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6087),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_514));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_515[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6092),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_515));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_516[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6095),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_516));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_517[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6097),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_517));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_518[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6108),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_518));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_519[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6113),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_519));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_520[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6116),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_520));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_521[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6118),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_521));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_522[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6129),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_522));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_523[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6134),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_523));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_524[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6137),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_524));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_525[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6139),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_525));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_526[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6150),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_526));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_527[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6155),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_527));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_528[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6158),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_528));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_529[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6160),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_529));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_530[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6171),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_530));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_531[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6176),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_531));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_532[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6179),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_532));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_533[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6181),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_533));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_534[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6192),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_534));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_535[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6197),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_535));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_536[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6200),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_536));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_537[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6202),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_537));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_538[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6213),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_538));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_539[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6218),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_539));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_540[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6221),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_540));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_541[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6223),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_541));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_542[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6234),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_542));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_543[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6239),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_543));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_544[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6242),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_544));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_545[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6244),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_545));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_546[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6255),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_546));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_547[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6260),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_547));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_548[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6263),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_548));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_549[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6265),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_549));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_550[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6276),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_550));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_551[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6281),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_551));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_552[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6284),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_552));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_553[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6286),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_553));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_554[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6297),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_554));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_555[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6302),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_555));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_556[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6305),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_556));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_557[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6307),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_557));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_558[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6318),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_558));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_559[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6323),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_559));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_560[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6326),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_560));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_561[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6328),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_561));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_562[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6339),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_562));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_563[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6344),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_563));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_564[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6347),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_564));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_565[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6349),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_565));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_566[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6360),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_566));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_567[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6365),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_567));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_568[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6386),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_568));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_569[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6391),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_569));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_570[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6403),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_570));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_571[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6408),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_571));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_572[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6420),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_572));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_573[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6425),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_573));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_574[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6580),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_574));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_575[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6583),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_575));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_576[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6586),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_576));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_577[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6589),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_577));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_578[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6592),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_578));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_579[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6595),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_579));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_580[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6598),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_580));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_581[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6601),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_581));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_582[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6604),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_582));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_583[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6607),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_583));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_584[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6610),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_584));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_585[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6613),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_585));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_586[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6616),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_586));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_587[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6619),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_587));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_588[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6622),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_588));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_589[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6625),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_589));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_590[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6628),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_590));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_591[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6631),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_591));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_592[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6634),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_592));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_593[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6637),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_593));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_594[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6640),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_594));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_595[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6643),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_595));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_596[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6646),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_596));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_597[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6649),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_597));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_598[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6652),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_598));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_599[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6655),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_599));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_600[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6658),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_600));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_601[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6661),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_601));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_602[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6664),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_602));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_603[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6667),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_603));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_604[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6670),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_604));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_605[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6673),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_605));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_606[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6676),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_606));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_607[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6679),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_607));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_608[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6682),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_608));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_609[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6685),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_609));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_610[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6688),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_610));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_611[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6691),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_611));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_612[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6694),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_612));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_613[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6697),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_613));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_614[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6700),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_614));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_615[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6703),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_615));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_616[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6706),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_616));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_617[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6709),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_617));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_618[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6712),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_618));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_619[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6715),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_619));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_620[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6718),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_620));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_621[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6721),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_621));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_622[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6724),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_622));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_623[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6733),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_623));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_624[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6762),
    /* pObjectName = */ "SBT Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_624));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_625[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6946),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_625));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_626[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6948),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_626));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_627[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6954),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_627));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_628[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6956),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_628));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_629[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6958),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_629));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_630[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6973),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_630));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_631[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6979),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_631));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_632[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_BUFFER,
    /* objectHandle = */ uint64_t(VkBuffer_uid_6981),
    /* pObjectName = */ "Buffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_632));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_633[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_14),
    /* pObjectName = */ "SwapChainImage"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_633));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_634[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_15),
    /* pObjectName = */ "SwapChainImage"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_634));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_635[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_5056),
    /* pObjectName = */ "skybox/kloofendal_48d_partly_cloudy_puresky_4k.hdr"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_635));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_636[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6370),
    /* pObjectName = */ "component/S_LightPoint.PNG"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_636));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_637[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6887),
    /* pObjectName = */ "RayImage"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_637));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_638[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6892),
    /* pObjectName = */ "SceneColor"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_638));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_639[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6909),
    /* pObjectName = */ "RayID"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_639));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_640[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6918),
    /* pObjectName = */ "TestCube"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_640));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_641[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6922),
    /* pObjectName = */ "ID"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_641));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_642[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE,
    /* objectHandle = */ uint64_t(VkImage_uid_6939),
    /* pObjectName = */ "SelectBuffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_642));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_643[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SAMPLER,
    /* objectHandle = */ uint64_t(VkSampler_uid_5062),
    /* pObjectName = */ "ImageSampler"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_643));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_644[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SAMPLER,
    /* objectHandle = */ uint64_t(VkSampler_uid_6376),
    /* pObjectName = */ "ImageSampler"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_644));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_645[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SAMPLER,
    /* objectHandle = */ uint64_t(VkSampler_uid_6895),
    /* pObjectName = */ "ImageSampler"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_645));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_646[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SAMPLER,
    /* objectHandle = */ uint64_t(VkSampler_uid_6942),
    /* pObjectName = */ "ImageSampler"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_646));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_647[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_POOL,
    /* objectHandle = */ uint64_t(VkDescriptorPool_uid_26),
    /* pObjectName = */ "SpicesEngineDescriptorPool"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_647));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_648[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_COMMAND_POOL,
    /* objectHandle = */ uint64_t(VkCommandPool_uid_7),
    /* pObjectName = */ "SpicesEngineCommandPool"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_648));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_649[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_5061),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_649));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_650[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6375),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_650));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_651[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6889),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_651));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_652[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6894),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_652));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_653[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6911),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_653));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_654[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6920),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_654));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_655[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6924),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_655));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_656[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_IMAGE_VIEW,
    /* objectHandle = */ uint64_t(VkImageView_uid_6941),
    /* pObjectName = */ "ImageView"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_656));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_657[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_5034),
    /* pObjectName = */ "DescriptorSetLayoutPreRenderer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_657));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_658[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_5095),
    /* pObjectName = */ "DescriptorSetLayoutRayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_658));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_659[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_5211),
    /* pObjectName = */ "DescriptorSetLayoutSpriteRenderer.Sprite.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_659));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_660[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_5245),
    /* pObjectName = */ "DescriptorSetLayoutWorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_660));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_661[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6411),
    /* pObjectName = */ "DescriptorSetLayoutSpriteRenderer.Sprite.S_LightPoint"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_661));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_662[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6747),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_662));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_663[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6748),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_663));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_664[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6749),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_664));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_665[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6950),
    /* pObjectName = */ "DescriptorSetLayoutPreRenderer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_665));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_666[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6960),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_666));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_667[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6961),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_667));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_668[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6962),
    /* pObjectName = */ "DescriptorSetLayoutRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_668));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_669[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6966),
    /* pObjectName = */ "DescriptorSetLayoutRayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_669));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_670[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,
    /* objectHandle = */ uint64_t(VkDescriptorSetLayout_uid_6995),
    /* pObjectName = */ "DescriptorSetLayoutWorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_670));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_671[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_5096),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_671));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_672[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_5212),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_672));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_673[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_5225),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_673));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_674[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_5246),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_674));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_675[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_5269),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_675));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_676[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_6412),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_676));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_677[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE_LAYOUT,
    /* objectHandle = */ uint64_t(VkPipelineLayout_uid_6750),
    /* pObjectName = */ "PipelineLayout"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_677));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_678[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_94),
    /* pObjectName = */ "DescriptorSetSpriteRenderer.Sprite.S_LightPoint"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_678));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_679[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_109),
    /* pObjectName = */ "DescriptorSetPreRenderer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_679));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_680[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_110),
    /* pObjectName = */ "DescriptorSetRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_680));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_681[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_111),
    /* pObjectName = */ "DescriptorSetRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_681));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_682[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_112),
    /* pObjectName = */ "DescriptorSetRayTracing"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_682));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_683[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_113),
    /* pObjectName = */ "DescriptorSetRayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_683));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_684[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_DESCRIPTOR_SET,
    /* objectHandle = */ uint64_t(VkDescriptorSet_uid_118),
    /* pObjectName = */ "DescriptorSetWorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_684));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_685[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5097),
    /* pObjectName = */ "RayTracingComposeRenderer.RayTracingCompose.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_685));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_686[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5098),
    /* pObjectName = */ "RayTracingComposeRenderer.RayTracingCompose.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_686));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_687[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5226),
    /* pObjectName = */ "WorldPickRenderer.WorldPick.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_687));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_688[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5227),
    /* pObjectName = */ "WorldPickRenderer.WorldPick.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_688));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_689[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5247),
    /* pObjectName = */ "WorldPickStage2Renderer.WorldPickStage2.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_689));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_690[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5248),
    /* pObjectName = */ "WorldPickStage2Renderer.WorldPickStage2.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_690));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_691[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5270),
    /* pObjectName = */ "TestRenderer.Test.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_691));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_692[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5271),
    /* pObjectName = */ "TestRenderer.Test.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_692));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_693[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_5272),
    /* pObjectName = */ "TestRenderer.Test.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_693));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_694[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6413),
    /* pObjectName = */ "SpriteRenderer.Sprite.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_694));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_695[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6414),
    /* pObjectName = */ "SpriteRenderer.Sprite.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_695));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_696[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6751),
    /* pObjectName = */ "RayTracingRenderer.RayTracing.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_696));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_697[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6752),
    /* pObjectName = */ "RayTracingRenderer.RayTracing.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_697));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_698[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6753),
    /* pObjectName = */ "RayTracingRenderer.RayTracing.DefaultShadow"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_698));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_699[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6754),
    /* pObjectName = */ "BasePassRenderer.Mesh.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_699));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_700[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SHADER_MODULE,
    /* objectHandle = */ uint64_t(VkShaderModule_uid_6755),
    /* pObjectName = */ "BasePassRenderer.Mesh.CornelBox"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_700));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_701[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5092),
    /* pObjectName = */ "RayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_701));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_702[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5208),
    /* pObjectName = */ "Sprite"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_702));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_703[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5222),
    /* pObjectName = */ "WorldPick"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_703));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_704[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5241),
    /* pObjectName = */ "WorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_704));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_705[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5266),
    /* pObjectName = */ "TestPass"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_705));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_706[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_5277),
    /* pObjectName = */ "Slate"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_706));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_707[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6943),
    /* pObjectName = */ "PreRenderer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_707));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_708[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6963),
    /* pObjectName = */ "RayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_708));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_709[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6985),
    /* pObjectName = */ "Sprite"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_709));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_710[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6988),
    /* pObjectName = */ "WorldPick"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_710));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_711[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6991),
    /* pObjectName = */ "WorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_711));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_712[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6996),
    /* pObjectName = */ "TestPass"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_712));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_713[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_RENDER_PASS,
    /* objectHandle = */ uint64_t(VkRenderPass_uid_6999),
    /* pObjectName = */ "Slate"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_713));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_714[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6945),
    /* pObjectName = */ "PreRenderer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_714));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_715[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6965),
    /* pObjectName = */ "RayTracingCompose"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_715));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_716[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6987),
    /* pObjectName = */ "Sprite"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_716));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_717[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6990),
    /* pObjectName = */ "WorldPick"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_717));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_718[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6993),
    /* pObjectName = */ "WorldPickStage2"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_718));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_719[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_6998),
    /* pObjectName = */ "TestPass"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_719));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_720[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FRAMEBUFFER,
    /* objectHandle = */ uint64_t(VkFramebuffer_uid_7001),
    /* pObjectName = */ "Slate"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_720));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_721[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_5099),
    /* pObjectName = */ "RayTracingComposeRenderer.RayTracingCompose.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_721));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_722[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_5228),
    /* pObjectName = */ "WorldPickRenderer.WorldPick.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_722));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_723[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_5249),
    /* pObjectName = */ "WorldPickStage2Renderer.WorldPickStage2.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_723));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_724[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_5273),
    /* pObjectName = */ "TestRenderer.Test.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_724));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_725[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_6415),
    /* pObjectName = */ "SpriteRenderer.Sprite.S_LightPoint"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_725));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_726[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_PIPELINE,
    /* objectHandle = */ uint64_t(VkPipeline_uid_6756),
    /* pObjectName = */ "RayTracingRenderer.RayTracing.Default"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_726));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_727[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_FENCE,
    /* objectHandle = */ uint64_t(VkFence_uid_25),
    /* pObjectName = */ "Fence"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_727));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_728[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SEMAPHORE,
    /* objectHandle = */ uint64_t(VkSemaphore_uid_23),
    /* pObjectName = */ "ImageSemaphore"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_728));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_729[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_SEMAPHORE,
    /* objectHandle = */ uint64_t(VkSemaphore_uid_24),
    /* pObjectName = */ "QueueSemaphore"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_729));

    static VkDebugUtilsObjectNameInfoEXT VkDebugUtilsObjectNameInfoEXT_temp_730[1] = { VkDebugUtilsObjectNameInfoEXT{
    /* sType = */ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
    /* pNext = */ nullptr,
    /* objectType = */ VK_OBJECT_TYPE_COMMAND_BUFFER,
    /* objectHandle = */ uint64_t(VkCommandBuffer_uid_9),
    /* pObjectName = */ "SpicesEngineCommandBuffer"} };
    NV_VK_REPLAY(VulkanReplay_SetDebugUtilsObjectNameEXT(VkDevice_uid_4, VkDebugUtilsObjectNameInfoEXT_temp_730));

    // Initialize VkSwapchainKHR_uid_13
    {
        VulkanHelper_InitializeSwapchain(VkDevice_uid_4, VkSwapchainKHR_uid_13, 0u);
    }

    // Initialize VkBuffer_uid_5076
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5076, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 30, 176ull)));
    }

    // Initialize VkBuffer_uid_5081
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5081, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 31, 24ull)));
    }

    // Initialize VkBuffer_uid_5155
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5155, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 32, 32ull)));
    }

    // Initialize VkBuffer_uid_5157
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5157, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 33, 8ull)));
    }

    // Initialize VkBuffer_uid_5185
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5185, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 34, 176ull)));
    }

    // Initialize VkBuffer_uid_5190
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5190, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 35, 24ull)));
    }

    // Initialize VkBuffer_uid_5233
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5233, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 36, 176ull)));
    }

    // Initialize VkBuffer_uid_5238
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5238, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 37, 24ull)));
    }

    // Initialize VkBuffer_uid_5254
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5254, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 38, 176ull)));
    }

    // Initialize VkBuffer_uid_5259
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5259, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 39, 24ull)));
    }

    // Initialize VkBuffer_uid_5304
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5304, 0ull, 1056ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 40, 1056ull)));
    }

    // Initialize VkBuffer_uid_5309
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5309, 0ull, 144ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 41, 144ull)));
    }

    // Initialize VkBuffer_uid_5383
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5383, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 42, 32ull)));
    }

    // Initialize VkBuffer_uid_5385
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5385, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 43, 8ull)));
    }

    // Initialize VkBuffer_uid_5396
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5396, 0ull, 935616ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 44, 935616ull)));
    }

    // Initialize VkBuffer_uid_5401
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5401, 0ull, 238884ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 45, 238884ull)));
    }

    // Initialize VkBuffer_uid_5406
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5406, 0ull, 502172ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 46, 502172ull)));
    }

    // Initialize VkBuffer_uid_5411
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5411, 0ull, 234264ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 47, 234264ull)));
    }

    // Initialize VkBuffer_uid_5416
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5416, 0ull, 989956ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 48, 989956ull)));
    }

    // Initialize VkBuffer_uid_5421
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5421, 0ull, 434544ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 49, 434544ull)));
    }

    // Initialize VkBuffer_uid_5426
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5426, 0ull, 710732ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 50, 710732ull)));
    }

    // Initialize VkBuffer_uid_5431
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5431, 0ull, 360324ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 51, 360324ull)));
    }

    // Initialize VkBuffer_uid_5436
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5436, 0ull, 1172160ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 52, 1172160ull)));
    }

    // Initialize VkBuffer_uid_5441
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5441, 0ull, 537840ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 53, 537840ull)));
    }

    // Initialize VkBuffer_uid_5444
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5444, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 54, 32ull)));
    }

    // Initialize VkBuffer_uid_5446
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5446, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 55, 8ull)));
    }

    // Initialize VkBuffer_uid_5457
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5457, 0ull, 24992ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 56, 24992ull)));
    }

    // Initialize VkBuffer_uid_5462
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5462, 0ull, 12744ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 57, 12744ull)));
    }

    // Initialize VkBuffer_uid_5465
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5465, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 58, 32ull)));
    }

    // Initialize VkBuffer_uid_5467
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5467, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 59, 8ull)));
    }

    // Initialize VkBuffer_uid_5478
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5478, 0ull, 24992ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 60, 24992ull)));
    }

    // Initialize VkBuffer_uid_5483
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5483, 0ull, 12744ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 61, 12744ull)));
    }

    // Initialize VkBuffer_uid_5486
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5486, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 62, 32ull)));
    }

    // Initialize VkBuffer_uid_5488
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5488, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 63, 8ull)));
    }

    // Initialize VkBuffer_uid_5499
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5499, 0ull, 24992ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 64, 24992ull)));
    }

    // Initialize VkBuffer_uid_5504
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5504, 0ull, 12744ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 65, 12744ull)));
    }

    // Initialize VkBuffer_uid_5507
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5507, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 66, 32ull)));
    }

    // Initialize VkBuffer_uid_5509
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5509, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 67, 8ull)));
    }

    // Initialize VkBuffer_uid_5520
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5520, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 68, 440000ull)));
    }

    // Initialize VkBuffer_uid_5525
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5525, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 69, 235224ull)));
    }

    // Initialize VkBuffer_uid_5528
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5528, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 70, 32ull)));
    }

    // Initialize VkBuffer_uid_5530
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5530, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 71, 8ull)));
    }

    // Initialize VkBuffer_uid_5541
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5541, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 72, 440000ull)));
    }

    // Initialize VkBuffer_uid_5546
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5546, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 73, 235224ull)));
    }

    // Initialize VkBuffer_uid_5549
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5549, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 74, 32ull)));
    }

    // Initialize VkBuffer_uid_5551
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5551, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 75, 8ull)));
    }

    // Initialize VkBuffer_uid_5562
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5562, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 76, 440000ull)));
    }

    // Initialize VkBuffer_uid_5567
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5567, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 77, 235224ull)));
    }

    // Initialize VkBuffer_uid_5570
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5570, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 78, 32ull)));
    }

    // Initialize VkBuffer_uid_5572
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5572, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 79, 8ull)));
    }

    // Initialize VkBuffer_uid_5583
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5583, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 80, 440000ull)));
    }

    // Initialize VkBuffer_uid_5588
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5588, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 81, 235224ull)));
    }

    // Initialize VkBuffer_uid_5591
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5591, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 82, 32ull)));
    }

    // Initialize VkBuffer_uid_5593
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5593, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 83, 8ull)));
    }

    // Initialize VkBuffer_uid_5604
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5604, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 84, 440000ull)));
    }

    // Initialize VkBuffer_uid_5609
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5609, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 85, 235224ull)));
    }

    // Initialize VkBuffer_uid_5612
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5612, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 86, 32ull)));
    }

    // Initialize VkBuffer_uid_5614
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5614, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 87, 8ull)));
    }

    // Initialize VkBuffer_uid_5625
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5625, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 88, 440000ull)));
    }

    // Initialize VkBuffer_uid_5630
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5630, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 89, 235224ull)));
    }

    // Initialize VkBuffer_uid_5633
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5633, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 90, 32ull)));
    }

    // Initialize VkBuffer_uid_5635
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5635, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 91, 8ull)));
    }

    // Initialize VkBuffer_uid_5646
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5646, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 92, 440000ull)));
    }

    // Initialize VkBuffer_uid_5651
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5651, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 93, 235224ull)));
    }

    // Initialize VkBuffer_uid_5654
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5654, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 94, 32ull)));
    }

    // Initialize VkBuffer_uid_5656
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5656, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 95, 8ull)));
    }

    // Initialize VkBuffer_uid_5667
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5667, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 96, 440000ull)));
    }

    // Initialize VkBuffer_uid_5672
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5672, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 97, 235224ull)));
    }

    // Initialize VkBuffer_uid_5675
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5675, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 98, 32ull)));
    }

    // Initialize VkBuffer_uid_5677
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5677, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 99, 8ull)));
    }

    // Initialize VkBuffer_uid_5688
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5688, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 100, 440000ull)));
    }

    // Initialize VkBuffer_uid_5693
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5693, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 101, 235224ull)));
    }

    // Initialize VkBuffer_uid_5696
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5696, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 102, 32ull)));
    }

    // Initialize VkBuffer_uid_5698
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5698, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 103, 8ull)));
    }

    // Initialize VkBuffer_uid_5709
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5709, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 104, 440000ull)));
    }

    // Initialize VkBuffer_uid_5714
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5714, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 105, 235224ull)));
    }

    // Initialize VkBuffer_uid_5717
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5717, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 106, 32ull)));
    }

    // Initialize VkBuffer_uid_5719
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5719, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 107, 8ull)));
    }

    // Initialize VkBuffer_uid_5730
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5730, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 108, 440000ull)));
    }

    // Initialize VkBuffer_uid_5735
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5735, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 109, 235224ull)));
    }

    // Initialize VkBuffer_uid_5738
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5738, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 110, 32ull)));
    }

    // Initialize VkBuffer_uid_5740
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5740, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 111, 8ull)));
    }

    // Initialize VkBuffer_uid_5751
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5751, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 112, 440000ull)));
    }

    // Initialize VkBuffer_uid_5756
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5756, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 113, 235224ull)));
    }

    // Initialize VkBuffer_uid_5759
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5759, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 114, 32ull)));
    }

    // Initialize VkBuffer_uid_5761
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5761, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 115, 8ull)));
    }

    // Initialize VkBuffer_uid_5772
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5772, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 116, 440000ull)));
    }

    // Initialize VkBuffer_uid_5777
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5777, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 117, 235224ull)));
    }

    // Initialize VkBuffer_uid_5780
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5780, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 118, 32ull)));
    }

    // Initialize VkBuffer_uid_5782
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5782, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 119, 8ull)));
    }

    // Initialize VkBuffer_uid_5793
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5793, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 120, 440000ull)));
    }

    // Initialize VkBuffer_uid_5798
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5798, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 121, 235224ull)));
    }

    // Initialize VkBuffer_uid_5801
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5801, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 122, 32ull)));
    }

    // Initialize VkBuffer_uid_5803
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5803, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 123, 8ull)));
    }

    // Initialize VkBuffer_uid_5814
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5814, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 124, 440000ull)));
    }

    // Initialize VkBuffer_uid_5819
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5819, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 125, 235224ull)));
    }

    // Initialize VkBuffer_uid_5822
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5822, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 126, 32ull)));
    }

    // Initialize VkBuffer_uid_5824
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5824, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 127, 8ull)));
    }

    // Initialize VkBuffer_uid_5835
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5835, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 128, 440000ull)));
    }

    // Initialize VkBuffer_uid_5840
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5840, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 129, 235224ull)));
    }

    // Initialize VkBuffer_uid_5843
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5843, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 130, 32ull)));
    }

    // Initialize VkBuffer_uid_5845
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5845, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 131, 8ull)));
    }

    // Initialize VkBuffer_uid_5856
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5856, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 132, 440000ull)));
    }

    // Initialize VkBuffer_uid_5861
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5861, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 133, 235224ull)));
    }

    // Initialize VkBuffer_uid_5864
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5864, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 134, 32ull)));
    }

    // Initialize VkBuffer_uid_5866
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5866, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 135, 8ull)));
    }

    // Initialize VkBuffer_uid_5877
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5877, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 136, 440000ull)));
    }

    // Initialize VkBuffer_uid_5882
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5882, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 137, 235224ull)));
    }

    // Initialize VkBuffer_uid_5885
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5885, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 138, 32ull)));
    }

    // Initialize VkBuffer_uid_5887
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5887, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 139, 8ull)));
    }

    // Initialize VkBuffer_uid_5898
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5898, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 140, 440000ull)));
    }

    // Initialize VkBuffer_uid_5903
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5903, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 141, 235224ull)));
    }

    // Initialize VkBuffer_uid_5906
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5906, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 142, 32ull)));
    }

    // Initialize VkBuffer_uid_5908
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5908, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 143, 8ull)));
    }

    // Initialize VkBuffer_uid_5919
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5919, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 144, 440000ull)));
    }

    // Initialize VkBuffer_uid_5924
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5924, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 145, 235224ull)));
    }

    // Initialize VkBuffer_uid_5927
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5927, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 146, 32ull)));
    }

    // Initialize VkBuffer_uid_5929
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5929, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 147, 8ull)));
    }

    // Initialize VkBuffer_uid_5940
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5940, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 148, 440000ull)));
    }

    // Initialize VkBuffer_uid_5945
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5945, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 149, 235224ull)));
    }

    // Initialize VkBuffer_uid_5948
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5948, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 150, 32ull)));
    }

    // Initialize VkBuffer_uid_5950
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5950, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 151, 8ull)));
    }

    // Initialize VkBuffer_uid_5961
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5961, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 152, 440000ull)));
    }

    // Initialize VkBuffer_uid_5966
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5966, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 153, 235224ull)));
    }

    // Initialize VkBuffer_uid_5969
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5969, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 154, 32ull)));
    }

    // Initialize VkBuffer_uid_5971
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5971, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 155, 8ull)));
    }

    // Initialize VkBuffer_uid_5982
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5982, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 156, 440000ull)));
    }

    // Initialize VkBuffer_uid_5987
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5987, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 157, 235224ull)));
    }

    // Initialize VkBuffer_uid_5990
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5990, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 158, 32ull)));
    }

    // Initialize VkBuffer_uid_5992
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_5992, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 159, 8ull)));
    }

    // Initialize VkBuffer_uid_6003
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6003, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 160, 440000ull)));
    }

    // Initialize VkBuffer_uid_6008
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6008, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 161, 235224ull)));
    }

    // Initialize VkBuffer_uid_6011
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6011, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 162, 32ull)));
    }

    // Initialize VkBuffer_uid_6013
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6013, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 163, 8ull)));
    }

    // Initialize VkBuffer_uid_6024
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6024, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 164, 440000ull)));
    }

    // Initialize VkBuffer_uid_6029
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6029, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 165, 235224ull)));
    }

    // Initialize VkBuffer_uid_6032
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6032, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 166, 32ull)));
    }

    // Initialize VkBuffer_uid_6034
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6034, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 167, 8ull)));
    }

    // Initialize VkBuffer_uid_6045
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6045, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 168, 440000ull)));
    }

    // Initialize VkBuffer_uid_6050
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6050, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 169, 235224ull)));
    }

    // Initialize VkBuffer_uid_6053
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6053, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 170, 32ull)));
    }

    // Initialize VkBuffer_uid_6055
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6055, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 171, 8ull)));
    }

    // Initialize VkBuffer_uid_6066
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6066, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 172, 440000ull)));
    }

    // Initialize VkBuffer_uid_6071
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6071, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 173, 235224ull)));
    }

    // Initialize VkBuffer_uid_6074
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6074, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 174, 32ull)));
    }

    // Initialize VkBuffer_uid_6076
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6076, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 175, 8ull)));
    }

    // Initialize VkBuffer_uid_6087
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6087, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 176, 440000ull)));
    }

    // Initialize VkBuffer_uid_6092
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6092, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 177, 235224ull)));
    }

    // Initialize VkBuffer_uid_6095
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6095, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 178, 32ull)));
    }

    // Initialize VkBuffer_uid_6097
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6097, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 179, 8ull)));
    }

    // Initialize VkBuffer_uid_6108
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6108, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 180, 440000ull)));
    }

    // Initialize VkBuffer_uid_6113
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6113, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 181, 235224ull)));
    }

    // Initialize VkBuffer_uid_6116
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6116, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 182, 32ull)));
    }

    // Initialize VkBuffer_uid_6118
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6118, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 183, 8ull)));
    }

    // Initialize VkBuffer_uid_6129
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6129, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 184, 440000ull)));
    }

    // Initialize VkBuffer_uid_6134
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6134, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 185, 235224ull)));
    }

    // Initialize VkBuffer_uid_6137
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6137, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 186, 32ull)));
    }

    // Initialize VkBuffer_uid_6139
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6139, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 187, 8ull)));
    }

    // Initialize VkBuffer_uid_6150
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6150, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 188, 440000ull)));
    }

    // Initialize VkBuffer_uid_6155
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6155, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 189, 235224ull)));
    }

    // Initialize VkBuffer_uid_6158
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6158, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 190, 32ull)));
    }

    // Initialize VkBuffer_uid_6160
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6160, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 191, 8ull)));
    }

    // Initialize VkBuffer_uid_6171
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6171, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 192, 440000ull)));
    }

    // Initialize VkBuffer_uid_6176
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6176, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 193, 235224ull)));
    }

    // Initialize VkBuffer_uid_6179
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6179, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 194, 32ull)));
    }

    // Initialize VkBuffer_uid_6181
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6181, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 195, 8ull)));
    }

    // Initialize VkBuffer_uid_6192
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6192, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 196, 440000ull)));
    }

    // Initialize VkBuffer_uid_6197
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6197, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 197, 235224ull)));
    }

    // Initialize VkBuffer_uid_6200
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6200, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 198, 32ull)));
    }

    // Initialize VkBuffer_uid_6202
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6202, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 199, 8ull)));
    }

    // Initialize VkBuffer_uid_6213
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6213, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 200, 440000ull)));
    }

    // Initialize VkBuffer_uid_6218
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6218, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 201, 235224ull)));
    }

    // Initialize VkBuffer_uid_6221
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6221, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 202, 32ull)));
    }

    // Initialize VkBuffer_uid_6223
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6223, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 203, 8ull)));
    }

    // Initialize VkBuffer_uid_6234
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6234, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 204, 440000ull)));
    }

    // Initialize VkBuffer_uid_6239
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6239, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 205, 235224ull)));
    }

    // Initialize VkBuffer_uid_6242
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6242, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 206, 32ull)));
    }

    // Initialize VkBuffer_uid_6244
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6244, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 207, 8ull)));
    }

    // Initialize VkBuffer_uid_6255
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6255, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 208, 440000ull)));
    }

    // Initialize VkBuffer_uid_6260
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6260, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 209, 235224ull)));
    }

    // Initialize VkBuffer_uid_6263
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6263, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 210, 32ull)));
    }

    // Initialize VkBuffer_uid_6265
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6265, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 211, 8ull)));
    }

    // Initialize VkBuffer_uid_6276
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6276, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 212, 440000ull)));
    }

    // Initialize VkBuffer_uid_6281
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6281, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 213, 235224ull)));
    }

    // Initialize VkBuffer_uid_6284
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6284, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 214, 32ull)));
    }

    // Initialize VkBuffer_uid_6286
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6286, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 215, 8ull)));
    }

    // Initialize VkBuffer_uid_6297
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6297, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 216, 440000ull)));
    }

    // Initialize VkBuffer_uid_6302
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6302, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 217, 235224ull)));
    }

    // Initialize VkBuffer_uid_6305
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6305, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 218, 32ull)));
    }

    // Initialize VkBuffer_uid_6307
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6307, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 219, 8ull)));
    }

    // Initialize VkBuffer_uid_6318
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6318, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 220, 440000ull)));
    }

    // Initialize VkBuffer_uid_6323
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6323, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 221, 235224ull)));
    }

    // Initialize VkBuffer_uid_6326
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6326, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 222, 32ull)));
    }

    // Initialize VkBuffer_uid_6328
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6328, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 223, 8ull)));
    }

    // Initialize VkBuffer_uid_6339
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6339, 0ull, 440000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 224, 440000ull)));
    }

    // Initialize VkBuffer_uid_6344
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6344, 0ull, 235224ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 225, 235224ull)));
    }

    // Initialize VkBuffer_uid_6347
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6347, 0ull, 32ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 226, 32ull)));
    }

    // Initialize VkBuffer_uid_6349
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6349, 0ull, 8ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 227, 8ull)));
    }

    // Initialize VkBuffer_uid_6360
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6360, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 228, 176ull)));
    }

    // Initialize VkBuffer_uid_6365
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6365, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 229, 24ull)));
    }

    // Initialize VkBuffer_uid_6386
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6386, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 230, 176ull)));
    }

    // Initialize VkBuffer_uid_6391
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6391, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 231, 24ull)));
    }

    // Initialize VkBuffer_uid_6403
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6403, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 232, 176ull)));
    }

    // Initialize VkBuffer_uid_6408
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6408, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 233, 24ull)));
    }

    // Initialize VkBuffer_uid_6420
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6420, 0ull, 176ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 234, 176ull)));
    }

    // Initialize VkBuffer_uid_6425
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6425, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 235, 24ull)));
    }

    // Initialize VkBuffer_uid_6580
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6583
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6586
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6589
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6592
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6595
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6598
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6601
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6604
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6607
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6610
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6613
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6616
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6619
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6622
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6625
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6628
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6631
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6634
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6637
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6640
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6643
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6646
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6649
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6652
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6655
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6658
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6661
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6664
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6667
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6670
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6673
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6676
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6679
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6682
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6685
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6688
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6691
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6694
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6697
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6700
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6703
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6706
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6709
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6712
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6715
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6718
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6721
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6724
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6733
    {
        BEGIN_DATA_SCOPE();

        // Buffer holds a VkAccelerationStructureKHR that'll be explicitly initialized.
    }

    // Initialize VkBuffer_uid_6762
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6762, 0ull, 192ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 236, 192ull)));
    }

    // Initialize VkBuffer_uid_6946
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6946, 0ull, 292ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 237, 292ull)));
    }

    // Initialize VkBuffer_uid_6948
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6948, 0ull, 24ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 238, 24ull)));
    }

    // Initialize VkBuffer_uid_6954
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6954, 0ull, 3200000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 239, 3200000ull)));
    }

    // Initialize VkBuffer_uid_6956
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6956, 0ull, 8000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 240, 8000ull)));
    }

    // Initialize VkBuffer_uid_6958
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6958, 0ull, 400000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 241, 400000ull)));
    }

    // Initialize VkBuffer_uid_6973
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6973, 0ull, 640ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 242, 640ull)));
    }

    // Initialize VkBuffer_uid_6979
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6979, 0ull, 8000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 243, 8000ull)));
    }

    // Initialize VkBuffer_uid_6981
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_6981, 0ull, 400000ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 244, 400000ull)));
    }

    // Initialize VkBuffer_uid_7268
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_7268, 0ull, 274688ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 245, 274688ull)));
    }

    // Initialize VkBuffer_uid_7289
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_PopulateBuffer3(VkDevice_uid_4, 0u, VkBuffer_uid_7289, 0ull, 66560ull, NV_GET_RESOURCE_CHECKED(const uint32_t*, 246, 66560ull)));
    }

    // Initialize VkImage_uid_14
    {
        BEGIN_DATA_SCOPE();

        static VkImageSubresource VkImageSubresource_temp_49 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_49 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_49 = VkExtent3D{
        /* width = */ 2200u,
        /* height = */ 1300u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateSwapchainImage(VkDevice_uid_4, 0u, VkImage_uid_14, VulkanHelper_PopulateImageFlags(0), VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkImageSubresource_temp_49, VkOffset3D_temp_49, VkExtent3D_temp_49, 11440000ull, NV_GET_RESOURCE(const uint32_t*, 247)));
    }

    // Initialize VkImage_uid_15
    {
        BEGIN_DATA_SCOPE();

        static VkImageSubresource VkImageSubresource_temp_50 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_50 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_50 = VkExtent3D{
        /* width = */ 2200u,
        /* height = */ 1300u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateSwapchainImage(VkDevice_uid_4, 0u, VkImage_uid_15, VulkanHelper_PopulateImageFlags(0), VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VkImageSubresource_temp_50, VkOffset3D_temp_50, VkExtent3D_temp_50, 11440000ull, NV_GET_RESOURCE(const uint32_t*, 248)));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_46[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_51 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_51 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_51 = VkExtent3D{
        /* width = */ 4096u,
        /* height = */ 2048u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_46, VkImageSubresource_temp_51, VkOffset3D_temp_51, VkExtent3D_temp_51, 33554432ull, NV_GET_RESOURCE(const uint32_t*, 249), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_47[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_52 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 1u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_52 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_52 = VkExtent3D{
        /* width = */ 2048u,
        /* height = */ 1024u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_47, VkImageSubresource_temp_52, VkOffset3D_temp_52, VkExtent3D_temp_52, 8388608ull, NV_GET_RESOURCE(const uint32_t*, 250), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_48[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_53 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 2u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_53 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_53 = VkExtent3D{
        /* width = */ 1024u,
        /* height = */ 512u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_48, VkImageSubresource_temp_53, VkOffset3D_temp_53, VkExtent3D_temp_53, 2097152ull, NV_GET_RESOURCE(const uint32_t*, 251), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_49[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_54 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 3u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_54 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_54 = VkExtent3D{
        /* width = */ 512u,
        /* height = */ 256u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_49, VkImageSubresource_temp_54, VkOffset3D_temp_54, VkExtent3D_temp_54, 524288ull, NV_GET_RESOURCE(const uint32_t*, 252), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_50[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_55 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 4u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_55 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_55 = VkExtent3D{
        /* width = */ 256u,
        /* height = */ 128u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_50, VkImageSubresource_temp_55, VkOffset3D_temp_55, VkExtent3D_temp_55, 131072ull, NV_GET_RESOURCE(const uint32_t*, 253), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_51[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_56 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 5u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_56 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_56 = VkExtent3D{
        /* width = */ 128u,
        /* height = */ 64u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_51, VkImageSubresource_temp_56, VkOffset3D_temp_56, VkExtent3D_temp_56, 32768ull, NV_GET_RESOURCE(const uint32_t*, 254), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_52[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_57 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 6u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_57 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_57 = VkExtent3D{
        /* width = */ 64u,
        /* height = */ 32u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_52, VkImageSubresource_temp_57, VkOffset3D_temp_57, VkExtent3D_temp_57, 8192ull, NV_GET_RESOURCE(const uint32_t*, 255), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_53[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_58 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 7u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_58 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_58 = VkExtent3D{
        /* width = */ 32u,
        /* height = */ 16u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_53, VkImageSubresource_temp_58, VkOffset3D_temp_58, VkExtent3D_temp_58, 2048ull, NV_GET_RESOURCE(const uint32_t*, 256), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_54[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_59 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 8u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_59 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_59 = VkExtent3D{
        /* width = */ 16u,
        /* height = */ 8u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_54, VkImageSubresource_temp_59, VkOffset3D_temp_59, VkExtent3D_temp_59, 512ull, NV_GET_RESOURCE(const uint32_t*, 257), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_55[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_60 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 9u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_60 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_60 = VkExtent3D{
        /* width = */ 8u,
        /* height = */ 4u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_55, VkImageSubresource_temp_60, VkOffset3D_temp_60, VkExtent3D_temp_60, 128ull, NV_GET_RESOURCE(const uint32_t*, 258), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_56[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_61 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 10u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_61 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_61 = VkExtent3D{
        /* width = */ 4u,
        /* height = */ 2u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_56, VkImageSubresource_temp_61, VkOffset3D_temp_61, VkExtent3D_temp_61, 32ull, NV_GET_RESOURCE(const uint32_t*, 259), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_57[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_62 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 11u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_62 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_62 = VkExtent3D{
        /* width = */ 2u,
        /* height = */ 1u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_57, VkImageSubresource_temp_62, VkOffset3D_temp_62, VkExtent3D_temp_62, 8ull, NV_GET_RESOURCE(const uint32_t*, 260), nullptr));
    }

    // Initialize VkImage_uid_5056
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_58[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_63 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 12u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_63 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_63 = VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5056, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_58, VkImageSubresource_temp_63, VkOffset3D_temp_63, VkExtent3D_temp_63, 4ull, NV_GET_RESOURCE(const uint32_t*, 261), nullptr));
    }

    // Initialize VkImage_uid_5290
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_59[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_64 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_64 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_64 = VkExtent3D{
        /* width = */ 1024u,
        /* height = */ 1024u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_5290, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_59, VkImageSubresource_temp_64, VkOffset3D_temp_64, VkExtent3D_temp_64, 4194304ull, NV_GET_RESOURCE(const uint32_t*, 262), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_60[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_65 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_65 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_65 = VkExtent3D{
        /* width = */ 256u,
        /* height = */ 256u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_60, VkImageSubresource_temp_65, VkOffset3D_temp_65, VkExtent3D_temp_65, 262144ull, NV_GET_RESOURCE(const uint32_t*, 263), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_61[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_66 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 1u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_66 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_66 = VkExtent3D{
        /* width = */ 128u,
        /* height = */ 128u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_61, VkImageSubresource_temp_66, VkOffset3D_temp_66, VkExtent3D_temp_66, 65536ull, NV_GET_RESOURCE(const uint32_t*, 264), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_62[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_67 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 2u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_67 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_67 = VkExtent3D{
        /* width = */ 64u,
        /* height = */ 64u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_62, VkImageSubresource_temp_67, VkOffset3D_temp_67, VkExtent3D_temp_67, 16384ull, NV_GET_RESOURCE(const uint32_t*, 265), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_63[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_68 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 3u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_68 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_68 = VkExtent3D{
        /* width = */ 32u,
        /* height = */ 32u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_63, VkImageSubresource_temp_68, VkOffset3D_temp_68, VkExtent3D_temp_68, 4096ull, NV_GET_RESOURCE(const uint32_t*, 266), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_64[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_69 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 4u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_69 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_69 = VkExtent3D{
        /* width = */ 16u,
        /* height = */ 16u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_64, VkImageSubresource_temp_69, VkOffset3D_temp_69, VkExtent3D_temp_69, 1024ull, NV_GET_RESOURCE(const uint32_t*, 267), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_65[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_70 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 5u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_70 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_70 = VkExtent3D{
        /* width = */ 8u,
        /* height = */ 8u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_65, VkImageSubresource_temp_70, VkOffset3D_temp_70, VkExtent3D_temp_70, 256ull, NV_GET_RESOURCE(const uint32_t*, 268), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_66[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_71 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 6u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_71 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_71 = VkExtent3D{
        /* width = */ 4u,
        /* height = */ 4u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_66, VkImageSubresource_temp_71, VkOffset3D_temp_71, VkExtent3D_temp_71, 64ull, NV_GET_RESOURCE(const uint32_t*, 269), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_67[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_72 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 7u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_72 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_72 = VkExtent3D{
        /* width = */ 2u,
        /* height = */ 2u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_67, VkImageSubresource_temp_72, VkOffset3D_temp_72, VkExtent3D_temp_72, 16ull, NV_GET_RESOURCE(const uint32_t*, 270), nullptr));
    }

    // Initialize VkImage_uid_6370
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_68[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_73 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 8u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_73 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_73 = VkExtent3D{
        /* width = */ 1u,
        /* height = */ 1u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6370, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_68, VkImageSubresource_temp_73, VkOffset3D_temp_73, VkExtent3D_temp_73, 4ull, NV_GET_RESOURCE(const uint32_t*, 271), nullptr));
    }

    // Initialize VkImage_uid_6887
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_69[1] = { VK_IMAGE_LAYOUT_GENERAL };
        static VkImageSubresource VkImageSubresource_temp_74 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_74 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_74 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6887, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_69, VkImageSubresource_temp_74, VkOffset3D_temp_74, VkExtent3D_temp_74, 23277632ull, NV_GET_RESOURCE(const uint32_t*, 272), nullptr));
    }

    // Initialize VkImage_uid_6892
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_70[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_75 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_75 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_75 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_26[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6892, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_70, VkImageSubresource_temp_75, VkOffset3D_temp_75, VkExtent3D_temp_75, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 273), unionVkClearValue_temp_26));
    }

    // Initialize VkImage_uid_6909
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_71[1] = { VK_IMAGE_LAYOUT_GENERAL };
        static VkImageSubresource VkImageSubresource_temp_76 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_76 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_76 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6909, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_71, VkImageSubresource_temp_76, VkOffset3D_temp_76, VkExtent3D_temp_76, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 274), nullptr));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_72[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_77 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_77 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_77 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_27[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_72, VkImageSubresource_temp_77, VkOffset3D_temp_77, VkExtent3D_temp_77, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 275), unionVkClearValue_temp_27));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_73[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_78 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 1u};
        static VkOffset3D VkOffset3D_temp_78 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_78 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_28[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_73, VkImageSubresource_temp_78, VkOffset3D_temp_78, VkExtent3D_temp_78, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 276), unionVkClearValue_temp_28));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_74[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_79 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 2u};
        static VkOffset3D VkOffset3D_temp_79 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_79 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_29[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_74, VkImageSubresource_temp_79, VkOffset3D_temp_79, VkExtent3D_temp_79, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 277), unionVkClearValue_temp_29));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_75[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_80 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 3u};
        static VkOffset3D VkOffset3D_temp_80 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_80 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_30[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_75, VkImageSubresource_temp_80, VkOffset3D_temp_80, VkExtent3D_temp_80, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 278), unionVkClearValue_temp_30));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_76[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_81 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 4u};
        static VkOffset3D VkOffset3D_temp_81 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_81 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_31[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_76, VkImageSubresource_temp_81, VkOffset3D_temp_81, VkExtent3D_temp_81, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 279), unionVkClearValue_temp_31));
    }

    // Initialize VkImage_uid_6918
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_77[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_82 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 5u};
        static VkOffset3D VkOffset3D_temp_82 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_82 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 1631u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_32[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6918, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_77, VkImageSubresource_temp_82, VkOffset3D_temp_82, VkExtent3D_temp_82, 10640644ull, NV_GET_RESOURCE(const uint32_t*, 280), unionVkClearValue_temp_32));
    }

    // Initialize VkImage_uid_6922
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_78[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_83 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_83 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_83 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_33[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6922, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_78, VkImageSubresource_temp_83, VkOffset3D_temp_83, VkExtent3D_temp_83, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 281), unionVkClearValue_temp_33));
    }

    // Initialize VkImage_uid_6939
    {
        BEGIN_DATA_SCOPE();

        static VkImageLayout VkImageLayout_temp_79[1] = { VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL };
        static VkImageSubresource VkImageSubresource_temp_84 = VkImageSubresource{
        /* aspectMask = */ VkImageAspectFlags(VK_IMAGE_ASPECT_COLOR_BIT),
        /* mipLevel = */ 0u,
        /* arrayLayer = */ 0u};
        static VkOffset3D VkOffset3D_temp_84 = VkOffset3D{
        /* x = */ 0,
        /* y = */ 0,
        /* z = */ 0};
        static VkExtent3D VkExtent3D_temp_84 = VkExtent3D{
        /* width = */ 1631u,
        /* height = */ 892u,
        /* depth = */ 1u};
        static union VkClearValue unionVkClearValue_temp_34[1] = { NV_TO_UNION(VkClearValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F) };
        NV_VK_REPLAY(VulkanHelper_PopulateImage3(VkDevice_uid_4, 0u, VkImage_uid_6939, VulkanHelper_PopulateImageFlags(0), 1u, VkImageLayout_temp_79, VkImageSubresource_temp_84, VkOffset3D_temp_84, VkExtent3D_temp_84, 5819408ull, NV_GET_RESOURCE(const uint32_t*, 282), unionVkClearValue_temp_34));
    }

    // Initialize VkDeviceMemory_uid_5156
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5156, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5156_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5158
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5158, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5158_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5384
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5384, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5384_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5386
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5386, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5386_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5445
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5445, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5445_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5447
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5447, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5447_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5466
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5466, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5466_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5468
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5468, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5468_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5487
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5487, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5487_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5489
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5489, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5489_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5508
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5508, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5508_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5510
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5510, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5510_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5529
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5529, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5529_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5531
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5531, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5531_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5550
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5550, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5550_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5552
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5552, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5552_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5571
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5571, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5571_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5573
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5573, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5573_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5592
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5592, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5592_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5594
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5594, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5594_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5613
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5613, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5613_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5615
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5615, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5615_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5634
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5634, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5634_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5636
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5636, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5636_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5655
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5655, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5655_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5657
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5657, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5657_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5676
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5676, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5676_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5678
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5678, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5678_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5697
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5697, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5697_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5699
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5699, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5699_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5718
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5718, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5718_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5720
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5720, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5720_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5739
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5739, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5739_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5741
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5741, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5741_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5760
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5760, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5760_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5762
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5762, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5762_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5781
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5781, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5781_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5783
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5783, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5783_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5802
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5802, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5802_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5804
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5804, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5804_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5823
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5823, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5823_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5825
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5825, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5825_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5844
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5844, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5844_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5846
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5846, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5846_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5865
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5865, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5865_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5867
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5867, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5867_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5886
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5886, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5886_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5888
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5888, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5888_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5907
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5907, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5907_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5909
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5909, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5909_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5928
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5928, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5928_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5930
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5930, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5930_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5949
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5949, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5949_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5951
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5951, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5951_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5970
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5970, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5970_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5972
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5972, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5972_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5991
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5991, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5991_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_5993
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_5993, 0ull, 64ull, 0u, &VkDeviceMemory_uid_5993_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6012
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6012, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6012_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6014
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6014, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6014_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6033
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6033, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6033_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6035
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6035, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6035_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6054
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6054, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6054_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6056
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6056, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6056_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6075
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6075, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6075_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6077
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6077, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6077_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6096
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6096, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6096_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6098
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6098, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6098_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6117
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6117, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6117_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6119
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6119, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6119_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6138
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6138, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6138_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6140
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6140, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6140_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6159
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6159, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6159_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6161
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6161, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6161_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6180
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6180, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6180_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6182
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6182, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6182_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6201
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6201, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6201_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6203
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6203, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6203_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6222
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6222, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6222_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6224
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6224, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6224_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6243
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6243, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6243_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6245
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6245, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6245_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6264
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6264, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6264_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6266
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6266, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6266_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6285
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6285, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6285_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6287
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6287, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6287_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6306
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6306, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6306_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6308
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6308, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6308_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6327
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6327, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6327_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6329
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6329, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6329_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6348
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6348, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6348_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6350
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6350, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6350_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6947
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6947, 0ull, 320ull, 0u, &VkDeviceMemory_uid_6947_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6949
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6949, 0ull, 64ull, 0u, &VkDeviceMemory_uid_6949_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6955
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6955, 0ull, 3200000ull, 0u, &VkDeviceMemory_uid_6955_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6957
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6957, 0ull, 8000ull, 0u, &VkDeviceMemory_uid_6957_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6959
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6959, 0ull, 400000ull, 0u, &VkDeviceMemory_uid_6959_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6974
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6974, 0ull, 640ull, 0u, &VkDeviceMemory_uid_6974_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6980
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6980, 0ull, 8000ull, 0u, &VkDeviceMemory_uid_6980_MappedPointer));
    }

    // Initialize VkDeviceMemory_uid_6982
    {
        BEGIN_DATA_SCOPE();

        // Initialize pre-frame mapping
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_6982, 0ull, 400000ull, 0u, &VkDeviceMemory_uid_6982_MappedPointer));
    }

    // Initialize VkAccelerationStructureKHR_uid_6582
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_51[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_101[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 3u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_51[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 2u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6582, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_51, 1ull, VkAccelerationStructureGeometryKHR_temp_101, VkAccelerationStructureBuildRangeInfoKHR_temp_51, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6585
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_52[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_102[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_52[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6585, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_52, 1ull, VkAccelerationStructureGeometryKHR_temp_102, VkAccelerationStructureBuildRangeInfoKHR_temp_52, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6588
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_53[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_103[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x1D, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_53[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6588, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_53, 1ull, VkAccelerationStructureGeometryKHR_temp_103, VkAccelerationStructureBuildRangeInfoKHR_temp_53, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6591
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_54[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_104[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x1E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_54[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6591, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_54, 1ull, VkAccelerationStructureGeometryKHR_temp_104, VkAccelerationStructureBuildRangeInfoKHR_temp_54, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6594
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_55[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_105[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x1F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_55[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6594, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_55, 1ull, VkAccelerationStructureGeometryKHR_temp_105, VkAccelerationStructureBuildRangeInfoKHR_temp_55, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6597
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_56[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_106[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_56[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6597, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_56, 1ull, VkAccelerationStructureGeometryKHR_temp_106, VkAccelerationStructureBuildRangeInfoKHR_temp_56, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6600
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_57[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_107[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x21, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_57[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6600, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_57, 1ull, VkAccelerationStructureGeometryKHR_temp_107, VkAccelerationStructureBuildRangeInfoKHR_temp_57, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6603
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_58[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_108[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x22, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_58[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6603, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_58, 1ull, VkAccelerationStructureGeometryKHR_temp_108, VkAccelerationStructureBuildRangeInfoKHR_temp_58, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6606
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_59[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_109[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_59[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6606, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_59, 1ull, VkAccelerationStructureGeometryKHR_temp_109, VkAccelerationStructureBuildRangeInfoKHR_temp_59, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6609
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_60[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_110[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x24, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_60[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6609, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_60, 1ull, VkAccelerationStructureGeometryKHR_temp_110, VkAccelerationStructureBuildRangeInfoKHR_temp_60, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6612
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_61[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_111[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x25, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_61[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6612, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_61, 1ull, VkAccelerationStructureGeometryKHR_temp_111, VkAccelerationStructureBuildRangeInfoKHR_temp_61, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6615
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_62[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_112[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x26, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_62[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6615, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_62, 1ull, VkAccelerationStructureGeometryKHR_temp_112, VkAccelerationStructureBuildRangeInfoKHR_temp_62, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6618
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_63[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_113[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x27, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_63[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6618, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_63, 1ull, VkAccelerationStructureGeometryKHR_temp_113, VkAccelerationStructureBuildRangeInfoKHR_temp_63, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6621
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_64[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_114[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x28, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_64[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6621, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_64, 1ull, VkAccelerationStructureGeometryKHR_temp_114, VkAccelerationStructureBuildRangeInfoKHR_temp_64, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6624
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_65[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_115[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x29, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_65[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6624, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_65, 1ull, VkAccelerationStructureGeometryKHR_temp_115, VkAccelerationStructureBuildRangeInfoKHR_temp_65, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6627
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_66[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_116[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_66[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6627, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_66, 1ull, VkAccelerationStructureGeometryKHR_temp_116, VkAccelerationStructureBuildRangeInfoKHR_temp_66, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6630
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_67[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_117[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_67[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6630, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_67, 1ull, VkAccelerationStructureGeometryKHR_temp_117, VkAccelerationStructureBuildRangeInfoKHR_temp_67, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6633
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_68[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_118[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_68[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6633, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_68, 1ull, VkAccelerationStructureGeometryKHR_temp_118, VkAccelerationStructureBuildRangeInfoKHR_temp_68, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6636
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_69[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_119[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2D, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_69[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6636, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_69, 1ull, VkAccelerationStructureGeometryKHR_temp_119, VkAccelerationStructureBuildRangeInfoKHR_temp_69, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6639
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_70[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_120[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_70[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6639, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_70, 1ull, VkAccelerationStructureGeometryKHR_temp_120, VkAccelerationStructureBuildRangeInfoKHR_temp_70, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6642
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_71[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_121[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x2F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_71[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6642, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_71, 1ull, VkAccelerationStructureGeometryKHR_temp_121, VkAccelerationStructureBuildRangeInfoKHR_temp_71, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6645
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_72[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_122[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x30, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_72[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6645, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_72, 1ull, VkAccelerationStructureGeometryKHR_temp_122, VkAccelerationStructureBuildRangeInfoKHR_temp_72, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6648
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_73[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_123[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x31, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_73[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6648, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_73, 1ull, VkAccelerationStructureGeometryKHR_temp_123, VkAccelerationStructureBuildRangeInfoKHR_temp_73, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6651
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_74[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_124[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_74[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6651, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_74, 1ull, VkAccelerationStructureGeometryKHR_temp_124, VkAccelerationStructureBuildRangeInfoKHR_temp_74, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6654
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_75[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_125[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x33, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_75[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6654, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_75, 1ull, VkAccelerationStructureGeometryKHR_temp_125, VkAccelerationStructureBuildRangeInfoKHR_temp_75, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6657
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_76[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_126[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x34, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_76[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6657, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_76, 1ull, VkAccelerationStructureGeometryKHR_temp_126, VkAccelerationStructureBuildRangeInfoKHR_temp_76, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6660
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_77[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_127[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x35, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_77[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6660, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_77, 1ull, VkAccelerationStructureGeometryKHR_temp_127, VkAccelerationStructureBuildRangeInfoKHR_temp_77, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6663
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_78[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_128[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x36, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_78[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6663, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_78, 1ull, VkAccelerationStructureGeometryKHR_temp_128, VkAccelerationStructureBuildRangeInfoKHR_temp_78, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6666
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_79[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_129[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x37, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_79[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6666, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_79, 1ull, VkAccelerationStructureGeometryKHR_temp_129, VkAccelerationStructureBuildRangeInfoKHR_temp_79, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6669
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_80[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_130[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x38, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_80[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6669, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_80, 1ull, VkAccelerationStructureGeometryKHR_temp_130, VkAccelerationStructureBuildRangeInfoKHR_temp_80, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6672
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_81[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_131[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x39, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_81[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6672, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_81, 1ull, VkAccelerationStructureGeometryKHR_temp_131, VkAccelerationStructureBuildRangeInfoKHR_temp_81, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6675
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_82[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_132[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_82[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6675, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_82, 1ull, VkAccelerationStructureGeometryKHR_temp_132, VkAccelerationStructureBuildRangeInfoKHR_temp_82, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6678
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_83[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_133[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_83[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6678, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_83, 1ull, VkAccelerationStructureGeometryKHR_temp_133, VkAccelerationStructureBuildRangeInfoKHR_temp_83, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6681
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_84[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_134[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_84[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6681, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_84, 1ull, VkAccelerationStructureGeometryKHR_temp_134, VkAccelerationStructureBuildRangeInfoKHR_temp_84, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6684
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_85[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_135[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3D, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_85[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6684, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_85, 1ull, VkAccelerationStructureGeometryKHR_temp_135, VkAccelerationStructureBuildRangeInfoKHR_temp_85, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6687
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_86[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_136[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_86[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6687, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_86, 1ull, VkAccelerationStructureGeometryKHR_temp_136, VkAccelerationStructureBuildRangeInfoKHR_temp_86, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6690
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_87[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_137[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x3F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_87[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6690, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_87, 1ull, VkAccelerationStructureGeometryKHR_temp_137, VkAccelerationStructureBuildRangeInfoKHR_temp_87, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6693
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_88[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_138[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x40, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_88[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6693, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_88, 1ull, VkAccelerationStructureGeometryKHR_temp_138, VkAccelerationStructureBuildRangeInfoKHR_temp_88, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6696
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_89[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_139[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_89[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6696, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_89, 1ull, VkAccelerationStructureGeometryKHR_temp_139, VkAccelerationStructureBuildRangeInfoKHR_temp_89, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6699
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_90[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_140[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x42, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_90[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6699, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_90, 1ull, VkAccelerationStructureGeometryKHR_temp_140, VkAccelerationStructureBuildRangeInfoKHR_temp_90, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6702
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_91[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_141[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 9999u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_91[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19602u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6702, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_91, 1ull, VkAccelerationStructureGeometryKHR_temp_141, VkAccelerationStructureBuildRangeInfoKHR_temp_91, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6705
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_92[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_142[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x44, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_92[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 1062u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6705, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_92, 1ull, VkAccelerationStructureGeometryKHR_temp_142, VkAccelerationStructureBuildRangeInfoKHR_temp_92, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6708
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_93[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_143[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x45, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_93[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 1062u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6708, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_93, 1ull, VkAccelerationStructureGeometryKHR_temp_143, VkAccelerationStructureBuildRangeInfoKHR_temp_93, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6711
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_94[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_144[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x46, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 567u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_94[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 1062u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6711, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_94, 1ull, VkAccelerationStructureGeometryKHR_temp_144, VkAccelerationStructureBuildRangeInfoKHR_temp_94, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6714
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_95[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_145[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x47, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 21263u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_95[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19907u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6714, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_95, 1ull, VkAccelerationStructureGeometryKHR_temp_145, VkAccelerationStructureBuildRangeInfoKHR_temp_95, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6717
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_96[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_146[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x48, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 11412u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_96[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 19522u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6717, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_96, 1ull, VkAccelerationStructureGeometryKHR_temp_146, VkAccelerationStructureBuildRangeInfoKHR_temp_96, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6720
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_97[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_147[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x49, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 22498u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_97[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 36212u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6720, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_97, 1ull, VkAccelerationStructureGeometryKHR_temp_147, VkAccelerationStructureBuildRangeInfoKHR_temp_97, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6723
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_98[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_148[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x4A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 16152u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_98[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 30027u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6723, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_98, 1ull, VkAccelerationStructureGeometryKHR_temp_148, VkAccelerationStructureBuildRangeInfoKHR_temp_98, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6726
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_99[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_TRUE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_149[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_TRIANGLES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryTrianglesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR,
        /* pNext = */ nullptr,
        /* vertexFormat = */ VK_FORMAT_R32G32B32_SFLOAT,
        /* vertexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x4B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* vertexStride = */ 12ull,
        /* maxVertex = */ 26639u,
        /* indexType = */ VK_INDEX_TYPE_NONE_KHR,
        /* indexData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
        /* transformData = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(VK_GEOMETRY_OPAQUE_BIT_KHR)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_99[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 44820u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6726, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_99, 1ull, VkAccelerationStructureGeometryKHR_temp_149, VkAccelerationStructureBuildRangeInfoKHR_temp_99, VK_FALSE));
    }

    // Initialize VkAccelerationStructureKHR_uid_6735
    {
        BEGIN_DATA_SCOPE();

        static VulkanHelper_InitializeAccelerationStructureInfoKHR VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_100[1] = { VulkanHelper_InitializeAccelerationStructureInfoKHR{
         /* .version = */ 2u,
         /* .type = */ VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
         /* .flags = */ VkBuildAccelerationStructureFlagsKHR(VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR | VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR),
         /* .mode = */ VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR,
         /* .hasHostGeometryData = */ VK_TRUE,
         /* .hasHostTransformData = */ VK_TRUE,
         /* .hasHostInstanceData = */ VK_TRUE,
         /* .isCompacted = */ VK_FALSE
        } };
        static VkAccelerationStructureGeometryKHR VkAccelerationStructureGeometryKHR_temp_150[1] = { VkAccelerationStructureGeometryKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR,
        /* pNext = */ nullptr,
        /* geometryType = */ VK_GEOMETRY_TYPE_INSTANCES_KHR,
        /* geometry = */ VulkanHelper_ToAccelerationStructureGeometryDataKHR(VkAccelerationStructureGeometryInstancesDataKHR{
        /* sType = */ VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR,
        /* pNext = */ nullptr,
        /* arrayOfPointers = */ 0u,
        /* data = */ NV_TO_UNION(VkDeviceOrHostAddressConstKHR, 0x4C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)}),
        /* flags = */ VkGeometryFlagsKHR(0)} };
        static VkAccelerationStructureBuildRangeInfoKHR VkAccelerationStructureBuildRangeInfoKHR_temp_100[1] = { VkAccelerationStructureBuildRangeInfoKHR{
        /* primitiveCount = */ 49u,
        /* primitiveOffset = */ 0u,
        /* firstVertex = */ 0u,
        /* transformOffset = */ 0u} };
        NV_VK_REPLAY(VulkanHelper_InitializeAccelerationStructureKHR2(VkDevice_uid_4, VkAccelerationStructureKHR_uid_6735, VulkanHelper_InitializeAccelerationStructureInfoKHR_temp_100, 1ull, VkAccelerationStructureGeometryKHR_temp_150, VkAccelerationStructureBuildRangeInfoKHR_temp_100, VK_FALSE));
    }

    // Updating VkDescriptorSet_uid_40
    // Binding 0: { VkImageView_uid_5292, VkSampler_uid_5280, }
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 1u, Serialization::DATABASE_HANDLE(333), 88ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_94
    // Binding 0: { VkImageView_uid_6375, VkSampler_uid_6376, }
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 1u, Serialization::DATABASE_HANDLE(334), 88ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_109
    // Binding 0: VkBuffer_uid_6946
    // Binding 1: VkBuffer_uid_6948
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 2u, Serialization::DATABASE_HANDLE(335), 176ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_110
    // Binding 0: VkAccelerationStructureKHR_uid_6735
    // Binding 1: VkImageView_uid_6889
    // Binding 2: VkImageView_uid_6911
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 3u, Serialization::DATABASE_HANDLE(336), 320ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_111
    // Binding 0: VkBuffer_uid_6954
    // Binding 1: VkBuffer_uid_6956
    // Binding 2: VkBuffer_uid_6958
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 3u, Serialization::DATABASE_HANDLE(337), 264ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_112
    // Binding 0: { VkImageView_uid_5061, VkSampler_uid_5062, }
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 1u, Serialization::DATABASE_HANDLE(338), 88ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_113
    // Binding 0: VkImageView_uid_6889
    // Binding 1: VkImageView_uid_6911
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 2u, Serialization::DATABASE_HANDLE(339), 176ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_118
    // Binding 0: { VkImageView_uid_6941, VkSampler_uid_6942, }
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 1u, Serialization::DATABASE_HANDLE(340), 88ull, 0, nullptr));

    // Updating VkDescriptorSet_uid_119
    // Binding 0: { VkImageView_uid_6894, VkSampler_uid_6895, }
    NV_VK_REPLAY(VulkanHelper_UpdateDescriptorSetsFromDatabase(VkDevice_uid_4, 1u, Serialization::DATABASE_HANDLE(341), 88ull, 0, nullptr));

    // Initialize VkPipeline_uid_5099
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_5099), 5099ull));
    }

    // Initialize VkPipeline_uid_5228
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_5228), 5228ull));
    }

    // Initialize VkPipeline_uid_5249
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_5249), 5249ull));
    }

    // Initialize VkPipeline_uid_5273
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_5273), 5273ull));
    }

    // Initialize VkPipeline_uid_5285
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_5285), 5285ull));
    }

    // Initialize VkPipeline_uid_6415
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_6415), 6415ull));
    }

    // Initialize VkPipeline_uid_6756
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanHelper_RegisterObject(VK_OBJECT_TYPE_PIPELINE, uint64_t(VkPipeline_uid_6756), 6756ull));
    }

    NV_VK_REPLAY(VulkanHelper_InitEnd(VkInstance_uid_1));
    FreeCachedMemory();
}

NV_REPLAY_END_FRAME_SETUP()
