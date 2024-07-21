#include "VulkanStructHydrator.h"

namespace NV {
namespace Vulkan {

uint8_t* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const uint8_t* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const uint8_t* pSrc = OffsetPointer(pBase, pOffset);
    uint8_t* pDst = Copy(count, pSrc);
    return pDst;
}

VkDescriptorImageInfo* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkDescriptorImageInfo* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkDescriptorImageInfo* pSrc = OffsetPointer(pBase, pOffset);
    VkDescriptorImageInfo* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].imageView = RehydrateObject<VK_OBJECT_TYPE_IMAGE_VIEW>(pDst[i].imageView);
        pDst[i].sampler = RehydrateObject<VK_OBJECT_TYPE_SAMPLER>(pDst[i].sampler);
    }
    return pDst;
}

VkDescriptorBufferInfo* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkDescriptorBufferInfo* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkDescriptorBufferInfo* pSrc = OffsetPointer(pBase, pOffset);
    VkDescriptorBufferInfo* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].buffer = RehydrateObject<VK_OBJECT_TYPE_BUFFER>(pDst[i].buffer);
    }
    return pDst;
}

#if defined(VK_EXT_inline_uniform_block)
VkWriteDescriptorSetInlineUniformBlockEXT* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetInlineUniformBlockEXT* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkWriteDescriptorSetInlineUniformBlockEXT* pSrc = OffsetPointer(pBase, pOffset);
    VkWriteDescriptorSetInlineUniformBlockEXT* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].pNext = RehydratePNext(pSrc, pDst[i].pNext);
        pDst[i].pData = Rehydrate(pSrc, pDst[i].dataSize, reinterpret_cast<const uint8_t*>(pDst[i].pData));
    }
    return pDst;
}
#endif

#if defined(VK_NV_ray_tracing)
VkWriteDescriptorSetAccelerationStructureNV* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetAccelerationStructureNV* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkWriteDescriptorSetAccelerationStructureNV* pSrc = OffsetPointer(pBase, pOffset);
    VkWriteDescriptorSetAccelerationStructureNV* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].pNext = RehydratePNext(pSrc, pDst[i].pNext);
        pDst[i].pAccelerationStructures = RehydrateObjectArray<VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV>(pSrc, pDst[i].accelerationStructureCount, pDst[i].pAccelerationStructures);
    }
    return pDst;
}
#endif

#if defined(VK_KHR_acceleration_structure)
VkWriteDescriptorSetAccelerationStructureKHR* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetAccelerationStructureKHR* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkWriteDescriptorSetAccelerationStructureKHR* pSrc = OffsetPointer(pBase, pOffset);
    VkWriteDescriptorSetAccelerationStructureKHR* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].pNext = RehydratePNext(pSrc, pDst[i].pNext);
        pDst[i].pAccelerationStructures = RehydrateObjectArray<VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_KHR>(pSrc, pDst[i].accelerationStructureCount, pDst[i].pAccelerationStructures);
    }
    return pDst;
}
#endif

VkWriteDescriptorSet* StructHydrator::Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSet* pOffset)
{
    if (!pOffset || count == 0)
    {
        return 0;
    }

    const VkWriteDescriptorSet* pSrc = OffsetPointer(pBase, pOffset);
    VkWriteDescriptorSet* pDst = Copy(count, pSrc);
    for (uint32_t i = 0; i < count; i++)
    {
        pDst[i].pNext = RehydratePNext(pSrc, pDst[i].pNext);
        pDst[i].dstSet = RehydrateObject<VK_OBJECT_TYPE_DESCRIPTOR_SET>(pDst[i].dstSet);
        pDst[i].pImageInfo = Rehydrate(pSrc, pDst[i].descriptorCount, pDst[i].pImageInfo);
        pDst[i].pBufferInfo = Rehydrate(pSrc, pDst[i].descriptorCount, pDst[i].pBufferInfo);
        pDst[i].pTexelBufferView = RehydrateObjectArray<VK_OBJECT_TYPE_BUFFER_VIEW>(pSrc, pDst[i].descriptorCount, pDst[i].pTexelBufferView);
    }
    return pDst;
}

void* StructHydrator::RehydratePNext(const void* pBase, const void* pOffset)
{
    if (!pOffset)
    {
        return nullptr;
    }

    const VkBaseInStructure* pSrc = OffsetPointer(pBase, reinterpret_cast<const VkBaseInStructure*>(pOffset));

    switch (pSrc->sType)
    {
#if defined(VK_EXT_inline_uniform_block)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_INLINE_UNIFORM_BLOCK_EXT:
        return Rehydrate(pBase, 1, reinterpret_cast<const VkWriteDescriptorSetInlineUniformBlockEXT*>(pOffset));
#endif
#if defined(VK_NV_ray_tracing)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_NV:
        return Rehydrate(pBase, 1, reinterpret_cast<const VkWriteDescriptorSetAccelerationStructureNV*>(pOffset));
#endif
#if defined(VK_KHR_acceleration_structure)
    case VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET_ACCELERATION_STRUCTURE_KHR:
        return Rehydrate(pBase, 1, reinterpret_cast<const VkWriteDescriptorSetAccelerationStructureKHR*>(pOffset));
#endif
    // WAR for warning C4065: switch statement contains 'default' but no 'case' labels
    case VK_STRUCTURE_TYPE_MAX_ENUM:
    default:
        NV_ASSERT(false && "unknown stype");
        break;
    }

    return nullptr;
}
}
} // namespace NV::Vulkan