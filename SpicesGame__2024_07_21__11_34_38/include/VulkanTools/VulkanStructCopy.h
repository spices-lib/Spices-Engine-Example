#pragma once

#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>
#else
#include <vulkan/vulkan.h>
#endif

#include <VulkanTools/VulkanNamespace.h>

#include <memory>

namespace NV {
namespace VulkanTools {

inline namespace VK_NAMESPACE {

// HostAllocator
class HostAllocator
{
public:
    HostAllocator() = default;
    HostAllocator(const HostAllocator&) = delete;
    HostAllocator& operator=(const HostAllocator&) = delete;

    void* Allocate(size_t size);
    void Free(void* pAllocation);
    void Reset();
    void Copy(void* pDst, const void* pSrc, size_t size);
};

// Parameter packs
struct UpdateDescriptorSets_Params
{
    UpdateDescriptorSets_Params(HostAllocator& allocator, VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies);

    VkDevice device;
    uint32_t descriptorWriteCount;
    VkWriteDescriptorSet* pDescriptorWrites;
    uint32_t descriptorCopyCount;
    VkCopyDescriptorSet* pDescriptorCopies;
};

struct QueueSubmit_Params
{
    QueueSubmit_Params(HostAllocator& allocator, VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence);

    VkQueue queue;
    uint32_t submitCount;
    VkSubmitInfo* pSubmits;
    VkFence fence;
};

#if defined(VK_KHR_synchronization2)
struct QueueSubmit2KHR_Params
{
    QueueSubmit2KHR_Params(HostAllocator& allocator, VkQueue queue, uint32_t submitCount, const VkSubmitInfo2KHR* pSubmits, VkFence fence);

    VkQueue queue;
    uint32_t submitCount;
    VkSubmitInfo2KHR* pSubmits;
    VkFence fence;
};
#endif

}

}
} // namespace NV::VulkanTools