#pragma once

#include <vk_mem_alloc.h>
#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>
#else
#include <vulkan/vulkan.h>
#endif

#include <VulkanTools/VulkanNamespace.h>

#include <new>
#include <vector>
#include <memory>

namespace NV {
namespace VulkanTools {
inline namespace VK_NAMESPACE {

//------------------------------------------------------------------------------
// GetDefaultMemoryTypeBits
// 
// This gets all memory types bits except HVVM because we want to leave that 
// for the user -- unless we are on an integrated system where there is only
// HVVM for the entire system.
//------------------------------------------------------------------------------
inline uint32_t GetDefaultMemoryTypeBits(VmaAllocator allocator)
{
    // All types are OK by default
    uint32_t memoryTypeBits = UINT32_MAX;

    // For an integrated system allow all memory types (usually only has HVVM)
    const VkPhysicalDeviceProperties* pPhysicalDeviceProperties = nullptr;
    vmaGetPhysicalDeviceProperties(allocator, &pPhysicalDeviceProperties);
    if (pPhysicalDeviceProperties->deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
    {
        return memoryTypeBits;
    }

    // For a desktop system strip out HVVM. We don't want to use this type unless 
    // we explicitly opt into it as there isn't much of it and we want to leave it
    // for the application.
    const VkPhysicalDeviceMemoryProperties* pPhysicalDeviceMemoryProperties = nullptr;
    vmaGetMemoryProperties(allocator, &pPhysicalDeviceMemoryProperties);
    for (uint32_t i = 0; i < pPhysicalDeviceMemoryProperties->memoryTypeCount; i++)
    {
        const VkMemoryPropertyFlags propertyFlags = pPhysicalDeviceMemoryProperties->memoryTypes[i].propertyFlags;
        const bool isHostVisible = propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
        const bool isDeviceLocal = propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
        if (isHostVisible && isDeviceLocal)
        {
            memoryTypeBits &= ~(1 << i);
        }
    }

    // Filtered types
    return memoryTypeBits;
}

//------------------------------------------------------------------------------
// ScopedVmaPool
//------------------------------------------------------------------------------
class ScopedVmaPool
{
public:
    ScopedVmaPool(VmaAllocator allocator, VmaMemoryUsage memoryUsage, uint32_t blockSize = 0, uint32_t minBlockCount = 0, uint32_t maxBlockCount = 0, VkMemoryPropertyFlags preferredFlags = {})
        : m_allocator(allocator)
    {
        VmaAllocationCreateInfo allocationCreateInfo = {};
        allocationCreateInfo.usage = memoryUsage;
        allocationCreateInfo.preferredFlags = preferredFlags;
        uint32_t memoryTypeIndex = 0;
        vmaFindMemoryTypeIndex(m_allocator, GetDefaultMemoryTypeBits(m_allocator), &allocationCreateInfo, &memoryTypeIndex);

        VmaPoolCreateInfo poolCreateInfo = {};
        poolCreateInfo.memoryTypeIndex = memoryTypeIndex;
        poolCreateInfo.blockSize = blockSize;
        poolCreateInfo.minBlockCount = minBlockCount;
        poolCreateInfo.maxBlockCount = maxBlockCount;
        vmaCreatePool(m_allocator, &poolCreateInfo, &m_pool);
    }

    ~ScopedVmaPool()
    {
        vmaDestroyPool(m_allocator, m_pool);
    }

    VmaPool GetPool() const
    {
        return m_pool;
    }

private:

    VmaAllocator m_allocator = VK_NULL_HANDLE;
    VmaPool m_pool;
};

//------------------------------------------------------------------------------
// ScopedVmaBuffer
//------------------------------------------------------------------------------
class ScopedVmaBuffer
{
public:
    ScopedVmaBuffer()
    {
    }

    ScopedVmaBuffer(VmaAllocator allocator, VkDeviceSize size, uint32_t memoryTypeBits, VkBufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage, VkMemoryPropertyFlags preferredFlags = {})
        : m_allocator(allocator)
        , m_size(size)
        , m_memoryUsage(memoryUsage)
    {
        if (size == 0)
        {
            return;
        }

        VkBufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        createInfo.size = size;
        createInfo.usage = bufferUsage;
        VmaAllocationCreateInfo allocationCreateInfo = {};
        allocationCreateInfo.usage = memoryUsage;
        allocationCreateInfo.memoryTypeBits = memoryTypeBits;
        allocationCreateInfo.preferredFlags = preferredFlags;
        if (memoryUsage != VMA_MEMORY_USAGE_GPU_ONLY && memoryUsage != VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE) 
        {
            allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
            if (memoryUsage == VMA_MEMORY_USAGE_AUTO)
            {
                // If we want to map the allocation when memory usage is VMA_MEMORY_USAGE_AUTO,
                // we must pass VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT
                // or VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT in flags
                allocationCreateInfo.flags |= VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
            }
        }
        VkResult ret = vmaCreateBuffer(allocator, &createInfo, &allocationCreateInfo, &m_buffer, &m_allocation, &m_info);
        if (ret != VK_SUCCESS)
        {
            throw std::bad_alloc();
        }
    }

    ScopedVmaBuffer(VmaAllocator allocator, VkDeviceSize size, VkBufferUsageFlags bufferUsage, VmaMemoryUsage memoryUsage, VkMemoryPropertyFlags preferredFlags = {})
        : ScopedVmaBuffer(allocator, size, GetGlobalMemoryTypeBits(allocator, memoryUsage), bufferUsage, memoryUsage, preferredFlags)
    {
    }

    ScopedVmaBuffer(VmaAllocator allocator, VkDeviceSize size, VkBufferUsageFlags bufferUsage, const std::shared_ptr<ScopedVmaPool>& spPool)
        : m_allocator(allocator)
        , m_size(size)
        , m_spPool(spPool)
    {
        if (size == 0)
        {
            return;
        }

        VkBufferCreateInfo createInfo = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        createInfo.size = size;
        createInfo.usage = bufferUsage;
        VmaAllocationCreateInfo allocationCreateInfo = {};
        allocationCreateInfo.pool = m_spPool->GetPool();
        allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
        VkResult ret = vmaCreateBuffer(allocator, &createInfo, &allocationCreateInfo, &m_buffer, &m_allocation, &m_info);
        if (ret != VK_SUCCESS)
        {
            throw std::bad_alloc();
        }
    }

    ScopedVmaBuffer(ScopedVmaBuffer&& rhs)
    {
        Swap(rhs);
    }

    ScopedVmaBuffer& operator=(ScopedVmaBuffer&& rhs)
    {
        Swap(rhs);
        return *this;
    }

    VkBuffer GetBuffer() const
    {
        return m_buffer;
    }

    bool IsValid() const
    {
        return m_buffer != VK_NULL_HANDLE;
    }

    VkDeviceSize Size() const
    {
        return m_size;
    }

    operator VkBuffer() const
    {
        return m_buffer;
    }

    void* Map() const
    {
        return m_info.pMappedData;
    }

    void Unmap() const
    {
        // We use VMA_ALLOCATION_CREATE_MAPPED_BIT now; no need to manually unmap
    }

    void Flush(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE)
    {
        if (m_info.pMappedData)
        {
            vmaFlushAllocation(m_allocator, m_allocation, offset, size);
        }
    }

    void Invalidate(VkDeviceSize offset = 0, VkDeviceSize size = VK_WHOLE_SIZE)
    {
        if (m_info.pMappedData)
        {
            vmaInvalidateAllocation(m_allocator, m_allocation, offset, size);
        }
    }

    void Reset()
    {
        if (m_allocator && m_buffer && m_allocation)
        {
            vmaDestroyBuffer(m_allocator, m_buffer, m_allocation);
        }

        m_allocation = VK_NULL_HANDLE;
        m_size = 0;
        m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
        m_buffer = VK_NULL_HANDLE;
        m_allocation = VK_NULL_HANDLE;
        m_info = {};
        m_spPool.reset();
    }

    const VmaAllocationInfo& GetInfo() const
    {
        return m_info;
    }

    ScopedVmaBuffer(const ScopedVmaBuffer& rhs) = delete;
    ScopedVmaBuffer& operator=(const ScopedVmaBuffer& rhs) = delete;

    ~ScopedVmaBuffer()
    {
        Reset();
    }

private:
    static uint32_t GetGlobalMemoryTypeBits(VmaAllocator allocator, VmaMemoryUsage memoryUsage)
    {
        // Bit mask of valid memory types
        uint32_t validBits = 0;

        // Get properties from VMA
        const VkPhysicalDeviceMemoryProperties* pProperties = nullptr;
        vmaGetMemoryProperties(allocator, &pProperties);
        if (!pProperties)
        {
            return 0;
        }

        // Guarantees to be 'HOST_VISIBLE'?
        // NOTE: This follows the logic of vmaFindMemoryTypeIndex ("Convert usage to requiredFlags and preferredFlags")
        bool requireHostVisible = false;
        switch (memoryUsage)
        {
        case VMA_MEMORY_USAGE_CPU_ONLY:
        case VMA_MEMORY_USAGE_CPU_TO_GPU:
        case VMA_MEMORY_USAGE_GPU_TO_CPU:
            requireHostVisible = true;
            break;

        case VMA_MEMORY_USAGE_UNKNOWN:
        case VMA_MEMORY_USAGE_GPU_ONLY:
        case VMA_MEMORY_USAGE_CPU_COPY:
        case VMA_MEMORY_USAGE_GPU_LAZILY_ALLOCATED:
        default:
            break;
        }

        // Add all types except HVVM as that memory is extremely limited and we don't have any reason to gobble it up.
        for (uint32_t i = 0; i < pProperties->memoryTypeCount; i++)
        {
            VkMemoryPropertyFlags flags = pProperties->memoryTypes[i].propertyFlags;
            bool isHostVisible = (flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            bool isDeviceLocal = (flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            if (requireHostVisible && !isHostVisible)
            {
                continue;
            }
            if (isHostVisible && isDeviceLocal)
            {
                continue;
            }
            validBits |= (1 << i);
        }

        // On embedded platforms, typically all HOST_VISIBLE memory is DEVICE_LOCAL which would result in
        // the 'validBits' 0 --> any memory type is accepted

        return validBits;
    }

    void Swap(ScopedVmaBuffer& rhs)
    {
        m_allocator = rhs.m_allocator;
        m_size = rhs.m_size;
        m_memoryUsage = rhs.m_memoryUsage;
        m_buffer = rhs.m_buffer;
        m_allocation = rhs.m_allocation;
        m_info = rhs.m_info;
        m_spPool = rhs.m_spPool;

        rhs.m_allocation = VK_NULL_HANDLE;
        rhs.m_size = 0;
        rhs.m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
        rhs.m_buffer = VK_NULL_HANDLE;
        rhs.m_allocation = VK_NULL_HANDLE;
        rhs.m_info = {};
        rhs.m_spPool.reset();
    }

    VmaAllocator m_allocator = VK_NULL_HANDLE;
    VkDeviceSize m_size = 0;
    VmaMemoryUsage m_memoryUsage = VMA_MEMORY_USAGE_UNKNOWN;
    VkBuffer m_buffer = VK_NULL_HANDLE;
    VmaAllocation m_allocation = VK_NULL_HANDLE;
    VmaAllocationInfo m_info = {};

    // Optional pool this was allocated from
    std::shared_ptr<ScopedVmaPool> m_spPool = nullptr;
};

// Shorter name alias
using VmaBuffer = ScopedVmaBuffer;

}
}
} // NV::VulkanTools
