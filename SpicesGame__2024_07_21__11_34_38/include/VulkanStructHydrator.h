#pragma once

#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>
#else
#include <vulkan/vulkan.h>
#endif

#include <cstring>
#include <functional>
#include <vector>

#ifndef NV_ASSERT
#define NV_ASSERT(X)
#endif

namespace NV {
namespace Vulkan {

using FnDecodeObject = std::function<uint64_t(VkObjectType, uint64_t)>;

//------------------------------------------------------------------------------
// StructHydrator
//------------------------------------------------------------------------------
struct StructHydrator
{
private:
    uint8_t* const m_pData;
    const size_t m_size;
    size_t m_offset;
    FnDecodeObject m_fnDecodeObject;

public:
    StructHydrator(std::vector<uint8_t>& buffer, const FnDecodeObject& fnDecodeObject)
        : m_pData(buffer.data())
        , m_size(buffer.size())
        , m_offset(0)
        , m_fnDecodeObject(fnDecodeObject)
    {
    }

    template <typename T>
    T* Top()
    {
        return reinterpret_cast<T*>(m_pData + m_offset);
    }

    template <typename T>
    T* Copy(uint32_t count, const T* pIn)
    {
        const size_t size = sizeof(T) * count;
        NV_ASSERT(Free() >= size);
        memcpy(Top<T>(), pIn, size);
        T* ret = Top<T>();
        m_offset += size;
        return ret;
    }

    size_t Free() const
    {
        return m_size - m_offset;
    }

    template <typename T>
    const T* OffsetPointer(const void* pParent, const T* pSrc)
    {
        const uintptr_t offset = reinterpret_cast<uintptr_t>(pSrc);
        const uint8_t* pData = reinterpret_cast<const uint8_t*>(pParent) + offset;
        return reinterpret_cast<const T*>(pData);
    }

    template <VkObjectType T_Type, typename T>
    T RehydrateObject(const T& object)
    {
        if (object == VK_NULL_HANDLE)
        {
            return VK_NULL_HANDLE;
        }

        return (T)m_fnDecodeObject(T_Type, (uint64_t)object);
    }

    template <VkObjectType T_Type, typename T>
    T* RehydrateObjectArray(const void* pBase, uint32_t count, const T* pOffset)
    {
        if (!pOffset || count == 0)
        {
            return 0;
        }

        const T* pSrc = OffsetPointer(pBase, pOffset);
        T* pDst = Copy(count, pSrc);
        NV_ASSERT(pDst);
        for (uint32_t i = 0; i < count; i++)
        {
            pDst[i] = RehydrateObject<T_Type>(pDst[i]);
        }

        return pDst;
    }

    uint8_t* Rehydrate(const void* pBase, uint32_t count, const uint8_t* pOffset);

    VkDescriptorImageInfo* Rehydrate(const void* pBase, uint32_t count, const VkDescriptorImageInfo* pOffset);
    VkDescriptorBufferInfo* Rehydrate(const void* pBase, uint32_t count, const VkDescriptorBufferInfo* pOffset);
#if defined(VK_EXT_inline_uniform_block)
    VkWriteDescriptorSetInlineUniformBlockEXT* Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetInlineUniformBlockEXT* pOffset);
#endif
#if defined(VK_NV_ray_tracing)
    VkWriteDescriptorSetAccelerationStructureNV* Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetAccelerationStructureNV* pOffset);
#endif
#if defined(VK_KHR_acceleration_structure)
    VkWriteDescriptorSetAccelerationStructureKHR* Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSetAccelerationStructureKHR* pOffset);
#endif
    VkWriteDescriptorSet* Rehydrate(const void* pBase, uint32_t count, const VkWriteDescriptorSet* pOffset);

    void* RehydratePNext(const void* pBase, const void* pOffset);
};
}
} // namespace NV::Vulkan