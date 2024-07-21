#include "VulkanTools/VulkanStructCopy.h"

#include <cstdlib>
#include <cstring>
#include <type_traits>

#ifndef NV_ASSERT
#include <cassert>
#define NV_ASSERT(x) assert(x)
#endif // !NV_ASSERT

namespace NV {
namespace VulkanTools {

inline namespace VK_NAMESPACE {

//------------------------------------------------------------------------------
// HostAllocator
//------------------------------------------------------------------------------
void* HostAllocator::Allocate(size_t size)
{
    return malloc(size);
}

void HostAllocator::Free(void* ptr)
{
}

void HostAllocator::Reset()
{
}

void HostAllocator::Copy(void* pDst, const void* pSrc, size_t size)
{
    memcpy(pDst, pSrc, size);
}

template <typename T>
T* AllocateAndCopy(HostAllocator& allocator, const T* pSrc, uint32_t count = 1)
{
    if (!pSrc || count == 0)
    {
        return nullptr;
    }

    const size_t size = sizeof(T) * count;
    T* pDst = reinterpret_cast<T*>(allocator.Allocate(size));
    allocator.Copy(pDst, pSrc, size);
    for (uint32_t i = 0; i < count; ++i)
    {
        DoAllocateAndCopyIndirectMembers(allocator, pDst[i], pSrc[i], std::is_class<T>{});
    }

    return pDst;
}

template <typename T>
T* AllocateAndCopy(HostAllocator& allocator, const T& src)
{
    return AllocateAndCopy<T>(allocator, &src, 1);
}

template <typename T>
void DoAllocateAndCopyIndirectMembers(HostAllocator& allocator, T& dst, const T& src, std::false_type)
{
    // no-op for false_type
}

template <typename T>
void DoAllocateAndCopyIndirectMembers(HostAllocator& allocator, T& dst, const T& src, std::true_type)
{
    AllocateAndCopyIndirectMembers(allocator, dst, src);
}

//------------------------------------------------------------------------------
// AllocateAndCopy_pNext
//------------------------------------------------------------------------------

static void* AllocateAndCopy_pNext(HostAllocator& allocator, const void* pSrc);

static void* AllocateAndCopy_pNext(HostAllocator& allocator, const VkBaseInStructure& src)
{
    switch (src.sType)
    {
#if defined(VK_EXT_inline_uniform_block)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT:
    {
        VkWriteDescriptorSetInlineUniformBlockEXT* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkWriteDescriptorSetInlineUniformBlockEXT&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
#if defined(VK_NV_ray_tracing)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV:
    {
        VkWriteDescriptorSetAccelerationStructureNV* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkWriteDescriptorSetAccelerationStructureNV&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
#if defined(VK_KHR_ray_tracing_pipeline)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR:
    {
        VkWriteDescriptorSetAccelerationStructureKHR* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkWriteDescriptorSetAccelerationStructureKHR&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
#if defined(VK_KHR_external_semaphore_win32)
    case VK_STRUCTURE_TYPE_D3D12_FENCE_SUBMIT_INFO_KHR:
    {
        VkD3D12FenceSubmitInfoKHR* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkD3D12FenceSubmitInfoKHR&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
    case VK_STRUCTURE_TYPE_DEVICE_GROUP_SUBMIT_INFO:
    {
        VkDeviceGroupSubmitInfo* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkDeviceGroupSubmitInfo&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
    case VK_STRUCTURE_TYPE_PERFORMANCE_QUERY_SUBMIT_INFO_KHR:
    {
        VkPerformanceQuerySubmitInfoKHR* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkPerformanceQuerySubmitInfoKHR&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
    case VK_STRUCTURE_TYPE_PROTECTED_SUBMIT_INFO:
    {
        VkProtectedSubmitInfo* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkProtectedSubmitInfo&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
    case VK_STRUCTURE_TYPE_TIMELINE_SEMAPHORE_SUBMIT_INFO:
    {
        VkTimelineSemaphoreSubmitInfo* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkTimelineSemaphoreSubmitInfo&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#if defined(VK_KHR_win32_keyed_mutex)
    case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_KHR:
    {
        VkWin32KeyedMutexAcquireReleaseInfoKHR* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkWin32KeyedMutexAcquireReleaseInfoKHR&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
#if defined(VK_NV_win32_keyed_mutex)
    case VK_STRUCTURE_TYPE_WIN32_KEYED_MUTEX_ACQUIRE_RELEASE_INFO_NV:
    {
        VkWin32KeyedMutexAcquireReleaseInfoNV* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkWin32KeyedMutexAcquireReleaseInfoNV&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
#if defined(VK_EXT_opacity_micromap)
    case VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR:
    {
        VkAccelerationStructureGeometryTrianglesDataKHR* pDst = AllocateAndCopy(allocator, reinterpret_cast<const VkAccelerationStructureGeometryTrianglesDataKHR&>(src));
        pDst->pNext = AllocateAndCopy_pNext(allocator, src.pNext);
        return pDst;
    }
    break;
#endif
    default:
        NV_ASSERT(false && "unsupported type");
        break;
    }

    return nullptr;
}

static void* AllocateAndCopy_pNext(HostAllocator& allocator, const void* pSrc)
{
    if (!pSrc)
    {
        return nullptr;
    }

    return AllocateAndCopy_pNext(allocator, *reinterpret_cast<const VkBaseInStructure*>(pSrc));
}

#if defined(VK_KHR_external_semaphore_win32)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkD3D12FenceSubmitInfoKHR& dst, const VkD3D12FenceSubmitInfoKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pWaitSemaphoreValues = AllocateAndCopy(allocator, src.pWaitSemaphoreValues, src.waitSemaphoreValuesCount);
    dst.pSignalSemaphoreValues = AllocateAndCopy(allocator, src.pSignalSemaphoreValues, src.signalSemaphoreValuesCount);
}
#endif // defined(VK_KHR_external_semaphore_win32)

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkDeviceGroupSubmitInfo& dst, const VkDeviceGroupSubmitInfo& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pWaitSemaphoreDeviceIndices = AllocateAndCopy(allocator, src.pWaitSemaphoreDeviceIndices, src.waitSemaphoreCount);
    dst.pCommandBufferDeviceMasks = AllocateAndCopy(allocator, src.pCommandBufferDeviceMasks, src.commandBufferCount);
    dst.pSignalSemaphoreDeviceIndices = AllocateAndCopy(allocator, src.pSignalSemaphoreDeviceIndices, src.signalSemaphoreCount);
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkPerformanceQuerySubmitInfoKHR& dst, const VkPerformanceQuerySubmitInfoKHR& src)
{
    NV_ASSERT(false && "unsupported");
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkProtectedSubmitInfo& dst, const VkProtectedSubmitInfo& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkTimelineSemaphoreSubmitInfo& dst, const VkTimelineSemaphoreSubmitInfo& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pWaitSemaphoreValues = AllocateAndCopy(allocator, src.pWaitSemaphoreValues, src.waitSemaphoreValueCount);
    dst.pSignalSemaphoreValues = AllocateAndCopy(allocator, src.pSignalSemaphoreValues, src.signalSemaphoreValueCount);
}

#if defined(VK_KHR_win32_keyed_mutex)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWin32KeyedMutexAcquireReleaseInfoKHR& dst, const VkWin32KeyedMutexAcquireReleaseInfoKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pAcquireSyncs = AllocateAndCopy(allocator, src.pAcquireSyncs, src.acquireCount);
    dst.pAcquireKeys = AllocateAndCopy(allocator, src.pAcquireKeys, src.acquireCount);
    dst.pAcquireTimeouts = AllocateAndCopy(allocator, src.pAcquireTimeouts, src.acquireCount);
    dst.pReleaseSyncs = AllocateAndCopy(allocator, src.pReleaseSyncs, src.releaseCount);
    dst.pReleaseKeys = AllocateAndCopy(allocator, src.pReleaseKeys, src.releaseCount);
}
#endif // defined(VK_KHR_external_semaphore_win32)

#if defined(VK_KHR_win32_keyed_mutex)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWin32KeyedMutexAcquireReleaseInfoNV& dst, const VkWin32KeyedMutexAcquireReleaseInfoNV& src)
{
    NV_ASSERT(false && "unsupported");
}
#endif // defined(VK_KHR_win32_keyed_mutex)

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkDescriptorImageInfo& dst, const VkDescriptorImageInfo& src)
{
    // no members need deep copy
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkDescriptorBufferInfo& dst, const VkDescriptorBufferInfo& src)
{
    // no members need deep copy
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkBufferView& dst, const VkBufferView& src)
{
    // no members need deep copy
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkCopyDescriptorSet& dst, const VkCopyDescriptorSet& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkSubmitInfo& dst, const VkSubmitInfo& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pWaitSemaphores = AllocateAndCopy(allocator, src.pWaitSemaphores, src.waitSemaphoreCount);
    dst.pWaitDstStageMask = AllocateAndCopy(allocator, src.pWaitDstStageMask, src.waitSemaphoreCount);
    dst.pCommandBuffers = AllocateAndCopy(allocator, src.pCommandBuffers, src.commandBufferCount);
    dst.pSignalSemaphores = AllocateAndCopy(allocator, src.pSignalSemaphores, src.signalSemaphoreCount);
}

#if defined(VK_KHR_synchronization2)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkCommandBufferSubmitInfoKHR& dst, const VkCommandBufferSubmitInfoKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkSemaphoreSubmitInfoKHR& dst, const VkSemaphoreSubmitInfoKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
}

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkSubmitInfo2KHR& dst, const VkSubmitInfo2KHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pWaitSemaphoreInfos = AllocateAndCopy(allocator, src.pWaitSemaphoreInfos, src.waitSemaphoreInfoCount);
    dst.pCommandBufferInfos = AllocateAndCopy(allocator, src.pCommandBufferInfos, src.commandBufferInfoCount);
    dst.pSignalSemaphoreInfos = AllocateAndCopy(allocator, src.pSignalSemaphoreInfos, src.signalSemaphoreInfoCount);
}
#endif // defined(VK_KHR_synchronization2)

#if defined(VK_EXT_inline_uniform_block)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWriteDescriptorSetInlineUniformBlockEXT& dst, const VkWriteDescriptorSetInlineUniformBlockEXT& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pData = AllocateAndCopy(allocator, reinterpret_cast<const uint8_t*>(dst.pData), src.dataSize);
}
#endif // defined(VK_EXT_inline_uniform_block)

#if defined(VK_NV_ray_tracing)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWriteDescriptorSetAccelerationStructureNV& dst, const VkWriteDescriptorSetAccelerationStructureNV& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pAccelerationStructures = AllocateAndCopy(allocator, dst.pAccelerationStructures, src.accelerationStructureCount);
}
#endif // defined(VK_NV_ray_tracing)

#if defined(VK_KHR_ray_tracing_pipeline)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWriteDescriptorSetAccelerationStructureKHR& dst, const VkWriteDescriptorSetAccelerationStructureKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    dst.pAccelerationStructures = AllocateAndCopy(allocator, dst.pAccelerationStructures, src.accelerationStructureCount);
}
#endif // defined(VK_KHR_ray_tracing_pipeline)

#if defined(VK_EXT_opacity_micromap)
static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkAccelerationStructureGeometryTrianglesDataKHR& dst, const VkAccelerationStructureGeometryTrianglesDataKHR& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
}
#endif // defined(VK_EXT_opacity_micromap)

static void AllocateAndCopyIndirectMembers(HostAllocator& allocator, VkWriteDescriptorSet& dst, const VkWriteDescriptorSet& src)
{
    dst.pNext = AllocateAndCopy_pNext(allocator, src.pNext);
    switch (src.descriptorType)
    {
    case VK_DESCRIPTOR_TYPE_SAMPLER:
    case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
    case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
    case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
    case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
        dst.pImageInfo = AllocateAndCopy(allocator, src.pImageInfo, src.descriptorCount);
        break;
    case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
    case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
        dst.pTexelBufferView = AllocateAndCopy(allocator, src.pTexelBufferView, src.descriptorCount);
        break;
    case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
    case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
    case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
    case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
        dst.pBufferInfo = AllocateAndCopy(allocator, src.pBufferInfo, src.descriptorCount);
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------
// UpdateDescriptorSets_Params
//------------------------------------------------------------------------------
UpdateDescriptorSets_Params::UpdateDescriptorSets_Params(HostAllocator& allocator, VkDevice _device, uint32_t _descriptorWriteCount, const VkWriteDescriptorSet* _pDescriptorWrites, uint32_t _descriptorCopyCount, const VkCopyDescriptorSet* _pDescriptorCopies)
    : device(_device)
    , descriptorWriteCount(_descriptorWriteCount)
    , pDescriptorWrites(AllocateAndCopy(allocator, _pDescriptorWrites, _descriptorWriteCount))
    , descriptorCopyCount(_descriptorCopyCount)
    , pDescriptorCopies(AllocateAndCopy(allocator, _pDescriptorCopies, _descriptorCopyCount))
{
}

//------------------------------------------------------------------------------
// QueueSubmit_Params
//------------------------------------------------------------------------------
QueueSubmit_Params::QueueSubmit_Params(HostAllocator& allocator, VkQueue _queue, uint32_t _submitCount, const VkSubmitInfo* _pSubmits, VkFence _fence)
    : queue(_queue)
    , submitCount(_submitCount)
    , pSubmits(AllocateAndCopy(allocator, _pSubmits, _submitCount))
    , fence(_fence)
{
}

#if defined(VK_KHR_synchronization2)
QueueSubmit2KHR_Params::QueueSubmit2KHR_Params(HostAllocator& allocator, VkQueue _queue, uint32_t _submitCount, const VkSubmitInfo2KHR* _pSubmits, VkFence _fence)
    : queue(_queue)
    , submitCount(_submitCount)
    , pSubmits(AllocateAndCopy(allocator, _pSubmits, _submitCount))
    , fence(_fence)
{
}
#endif

}

}
} // namespace NV::VulkanTools