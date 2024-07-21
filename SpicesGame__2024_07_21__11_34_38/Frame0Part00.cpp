//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Frame0Part00.cpp
// 
//-----------------------------------------------------------------------------

#include <vulkan/vulkan.h>

#include "VulkanHelpers.h"
#include "VulkanReplay.h"
#include "Resources.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Threading.h"

NV_REPLAY_BEGIN_FRAME()

//-----------------------------------------------------------------------------
// RunFrame0Part00
//-----------------------------------------------------------------------------
void RunFrame0Part00(uint64_t frameIndex)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanReplay_WaitForFences(VkDevice_uid_4, 1u, NV_TO_STACK_PTR(VkFence_uid_25), 1u, 18446744073709551615ull));
    }

    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanReplay_ResetFences(VkDevice_uid_4, 1u, NV_TO_STACK_PTR(VkFence_uid_25)));
    }

    {
        BEGIN_DATA_SCOPE();

        static uint32_t uint32_t_temp_1[1] = { 1u };
        NV_VK_REPLAY(VulkanReplay_AcquireNextImageKHR(VkDevice_uid_4, VkSwapchainKHR_uid_13, 18446744073709551615ull, VkSemaphore_uid_23, VkFence(VK_NULL_HANDLE), uint32_t_temp_1));
    }

    // Host update to memory

    static VkDescriptorBufferInfo VkDescriptorBufferInfo_temp_1[1] = { VkDescriptorBufferInfo{
    /* buffer = */ VkBuffer_uid_6946,
    /* offset = */ 0ull,
    /* range = */ 320ull} };
    NV_VK_REPLAY(VulkanHelper_UpdateMappedMemory2(VkDevice_uid_4, VkDeviceMemory_uid_6947, VkDeviceMemory_uid_6947_MappedPointer, 0ull, 320ull, NV_GET_RESOURCE(const uint8_t*, 0), 1ull, VkDescriptorBufferInfo_temp_1));

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_1[1] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_6947,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 1u, VkMappedMemoryRange_temp_1));
    }

    // Host update to memory

    static VkDescriptorBufferInfo VkDescriptorBufferInfo_temp_2[1] = { VkDescriptorBufferInfo{
    /* buffer = */ VkBuffer_uid_6948,
    /* offset = */ 0ull,
    /* range = */ 64ull} };
    NV_VK_REPLAY(VulkanHelper_UpdateMappedMemory2(VkDevice_uid_4, VkDeviceMemory_uid_6949, VkDeviceMemory_uid_6949_MappedPointer, 0ull, 64ull, NV_GET_RESOURCE(const uint8_t*, 1), 1ull, VkDescriptorBufferInfo_temp_2));

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_2[1] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_6949,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 1u, VkMappedMemoryRange_temp_2));
    }

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_3[1] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_6955,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 1u, VkMappedMemoryRange_temp_3));
    }

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_4[1] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_6957,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 1u, VkMappedMemoryRange_temp_4));
    }

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_5[1] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_6959,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 1u, VkMappedMemoryRange_temp_5));
    }

    {
        BEGIN_DATA_SCOPE();

        // Map #0 [0...1]
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_7269, 0ull, 271360ull, VkMemoryMapFlags(0), &VkDeviceMemory_uid_7269_MappedPointer));
    }

    {
        BEGIN_DATA_SCOPE();

        // Map #1 [0...1]
        NV_VK_REPLAY(VulkanReplay_MapMemory(VkDevice_uid_4, VkDeviceMemory_uid_7290, 0ull, 65536ull, VkMemoryMapFlags(0), &VkDeviceMemory_uid_7290_MappedPointer));
    }

    // Host update to memory

    static VkDescriptorBufferInfo VkDescriptorBufferInfo_temp_3[1] = { VkDescriptorBufferInfo{
    /* buffer = */ VkBuffer_uid_7268,
    /* offset = */ 258048ull,
    /* range = */ 8192ull} };
    NV_VK_REPLAY(VulkanHelper_UpdateMappedMemory2(VkDevice_uid_4, VkDeviceMemory_uid_7269, VkDeviceMemory_uid_7269_MappedPointer, 258048ull, 8192ull, NV_GET_RESOURCE(const uint8_t*, 2), 1ull, VkDescriptorBufferInfo_temp_3));

    {
        BEGIN_DATA_SCOPE();

        static VkMappedMemoryRange VkMappedMemoryRange_temp_6[2] = { VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_7269,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull}, VkMappedMemoryRange{
        /* sType = */ VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        /* pNext = */ nullptr,
        /* memory = */ VkDeviceMemory_uid_7290,
        /* offset = */ 0ull,
        /* size = */ 18446744073709551615ull} };
        NV_VK_REPLAY(VulkanReplay_FlushMappedMemoryRanges(VkDevice_uid_4, 2u, VkMappedMemoryRange_temp_6));
    }

    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanReplay_UnmapMemory(VkDevice_uid_4, VkDeviceMemory_uid_7269));
    }

    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanReplay_UnmapMemory(VkDevice_uid_4, VkDeviceMemory_uid_7290));
    }

    VulkanHelper_RecordCommandBuffer(VkDevice_uid_4, VkCommandBuffer_uid_9, 1u, &Record_VkCommandBuffer_uid_9_r1);
    {
        BEGIN_DATA_SCOPE();

        NV_VK_REPLAY(VulkanReplay_ResetFences(VkDevice_uid_4, 1u, NV_TO_STACK_PTR(VkFence_uid_25)));
    }

    {
        BEGIN_DATA_SCOPE();

        static VkSemaphore VkSemaphore_pWaitSemaphores_1[1] = { VkSemaphore_uid_23 };
        static uint32_t uint32_t_pWaitDstStageMask_2[1] = { 1024u };
        static VkCommandBuffer VkCommandBuffer_pCommandBuffers_1[1] = { VkCommandBuffer_uid_9 };
        static VkSemaphore VkSemaphore_pSignalSemaphores_2[1] = { VkSemaphore_uid_24 };
        static VkSubmitInfo VkSubmitInfo_temp_1[1] = { VkSubmitInfo{
        /* sType = */ VK_STRUCTURE_TYPE_SUBMIT_INFO,
        /* pNext = */ nullptr,
        /* waitSemaphoreCount = */ 1u,
        /* pWaitSemaphores = */ VkSemaphore_pWaitSemaphores_1,
        /* pWaitDstStageMask = */ uint32_t_pWaitDstStageMask_2,
        /* commandBufferCount = */ 1u,
        /* pCommandBuffers = */ VkCommandBuffer_pCommandBuffers_1,
        /* signalSemaphoreCount = */ 1u,
        /* pSignalSemaphores = */ VkSemaphore_pSignalSemaphores_2} };
        NV_VK_REPLAY(VulkanReplay_QueueSubmit(VkQueue_uid_6, 1u, VkSubmitInfo_temp_1, VkFence_uid_25));
    }

    {
        BEGIN_DATA_SCOPE();

        static VkSemaphore VkSemaphore_pWaitSemaphores_3[1] = { VkSemaphore_uid_24 };
        static VkSwapchainKHR VkSwapchainKHR_pSwapchains_1[1] = { VkSwapchainKHR_uid_13 };
        static uint32_t uint32_t_pImageIndices_3[1] = { 1u };
        static VkPresentInfoKHR VkPresentInfoKHR_temp_1[1] = { VkPresentInfoKHR{
        /* sType = */ VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        /* pNext = */ nullptr,
        /* waitSemaphoreCount = */ 1u,
        /* pWaitSemaphores = */ VkSemaphore_pWaitSemaphores_3,
        /* swapchainCount = */ 1u,
        /* pSwapchains = */ VkSwapchainKHR_pSwapchains_1,
        /* pImageIndices = */ uint32_t_pImageIndices_3,
        /* pResults = */ nullptr} };
        NV_VK_REPLAY(VulkanReplay_QueuePresentKHR(VkQueue_uid_6, VkPresentInfoKHR_temp_1));
    }
}

NV_REPLAY_END_FRAME()
