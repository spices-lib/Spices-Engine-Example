//--------------------------------------------------------------------------------------
// File: VulkanHelpers.h
//
// Distributed as part of NVIDIA Nsight serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>
#else
#include <vulkan/vulkan.h>
#endif

#include "function_overrides.h"

#include "CommonReplay.h"
#include "VulkanReplay.h"

#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <memory>
#include <vector>

namespace VulkanHelpers {

//------------------------------------------------------------------------------
// NV_VK_REPLAY
//------------------------------------------------------------------------------
#define NV_VK_REPLAY(FCN)                                                                                          \
    {                                                                                                              \
        VulkanHelpers::AutoCallingContext autoContext(VulkanHelper_IsCallingContextEnabled(), __FILE__, __LINE__); \
        FCN;                                                                                                       \
    }

//------------------------------------------------------------------------------
// AutoCallingContext
//------------------------------------------------------------------------------
struct AutoCallingContext
{
    AutoCallingContext(bool contextEnabled, const char* file, int line)
        : m_contextEnabled(contextEnabled)
    {
        if (m_contextEnabled)
        {
            VulkanHelper_CallingContext context = { sizeof(VulkanHelper_CallingContext), file, line };
            VulkanHelper_SetCallingContext(&context);
        }
    }

    ~AutoCallingContext()
    {
        if (m_contextEnabled)
        {
            VulkanHelper_CallingContext context = { sizeof(VulkanHelper_CallingContext), nullptr, 0 };
            VulkanHelper_SetCallingContext(&context);
        }
    }

    const bool m_contextEnabled;
};

//------------------------------------------------------------------------------
// ToPointer
//------------------------------------------------------------------------------
template <typename T>
T* ToPointer(const std::initializer_list<T>&& x)
{
    size_t size = x.size() * sizeof(T);
    T* pData = reinterpret_cast<T*>(std::malloc(size));
    std::memcpy(pData, x.begin(), size);
    return pData;
}

//------------------------------------------------------------------------------
// ToStackPointer
//------------------------------------------------------------------------------
template <typename T>
const T* ToStackPointer(const std::initializer_list<T>&& x)
{
    return x.begin();
}

//------------------------------------------------------------------------------
// ToUnion
//------------------------------------------------------------------------------
template <typename T>
T ToUnion(const std::initializer_list<uint8_t>& data)
{
    T value;
    uint8_t* pValue = reinterpret_cast<uint8_t*>(&value);
    size_t i = 0;
    for (const uint8_t& element : data)
    {
        pValue[i++] = element;
    }
    return value;
}

//------------------------------------------------------------------------------
// NvOutputArray
//------------------------------------------------------------------------------
template <typename T_Ptr>
class NvOutputArray
{
public:
    using T = typename std::remove_pointer<T_Ptr>::type;

    NvOutputArray(const std::initializer_list<T*>& x)
        : m_array(x)
        , m_vecTemp(x.size())
    {
        uint32_t i = 0;
        for (T* pOut : m_array)
        {
            m_vecTemp[i++] = pOut ? *pOut : 0;
        }
    }

    ~NvOutputArray()
    {
        uint32_t i = 0;
        for (T* pOut : m_array)
        {
            if (pOut)
            {
                *pOut = m_vecTemp[i++];
            }
        }
    }

    operator T*()
    {
        return m_vecTemp.data();
    }

private:
    const std::initializer_list<T*>& m_array;
    std::vector<T> m_vecTemp;
};

//------------------------------------------------------------------------------
// MakeNvOutputArray
//------------------------------------------------------------------------------
template <typename T>
NvOutputArray<T> MakeNvOutputArray(const std::initializer_list<T>& x)
{
    return NvOutputArray<T>(x);
}

} // namespace VulkanHelpers

#ifdef VK_KHR_acceleration_structure
//--------------------------------------------------------------------------
// VulkanHelper_ToAccelerationStructureGeometryDataKHR
//--------------------------------------------------------------------------
inline VkAccelerationStructureGeometryDataKHR VulkanHelper_ToAccelerationStructureGeometryDataKHR(const VkAccelerationStructureGeometryTrianglesDataKHR& triangles)
{
    VkAccelerationStructureGeometryDataKHR x;
    x.triangles = triangles;
    return x;
}

//------------------------------------------------------------------------------
// VulkanHelper_ToAccelerationStructureGeometryDataKHR
//------------------------------------------------------------------------------
inline VkAccelerationStructureGeometryDataKHR VulkanHelper_ToAccelerationStructureGeometryDataKHR(const VkAccelerationStructureGeometryAabbsDataKHR& aabbs)
{
    VkAccelerationStructureGeometryDataKHR x;
    x.aabbs = aabbs;
    return x;
}

//------------------------------------------------------------------------------
// VulkanHelper_ToAccelerationStructureGeometryDataKHR
//------------------------------------------------------------------------------
inline VkAccelerationStructureGeometryDataKHR VulkanHelper_ToAccelerationStructureGeometryDataKHR(const VkAccelerationStructureGeometryInstancesDataKHR& instances)
{
    VkAccelerationStructureGeometryDataKHR x;
    x.instances = instances;
    return x;
}
#endif // VK_KHR_acceleration_structure

//--------------------------------------------------------------------------
// NV_TO_PTR
//--------------------------------------------------------------------------
#define NV_TO_PTR(...) VulkanHelpers::ToPointer({ __VA_ARGS__ })
#define NV_TO_STACK_PTR(...) VulkanHelpers::ToStackPointer({ __VA_ARGS__ })

//--------------------------------------------------------------------------
// NV_TO_ARRAY
//--------------------------------------------------------------------------
#define NV_TO_ARRAY(...) \
    {                    \
        __VA_ARGS__      \
    }

//--------------------------------------------------------------------------
// NV_TO_UNION
//
// Wrapper to represent a union as a blob of data
//--------------------------------------------------------------------------
#define NV_TO_UNION(TYPE, ...) VulkanHelpers::ToUnion<TYPE>({ __VA_ARGS__ })

//--------------------------------------------------------------------------
// NV_TO_OUTPUT_ARRAY
//--------------------------------------------------------------------------
#define NV_TO_OUTPUT_ARRAY(...) VulkanHelpers::MakeNvOutputArray({ __VA_ARGS__ })

//--------------------------------------------------------------------------
// NV_LOG
//--------------------------------------------------------------------------
#ifndef _DEBUG
#define NV_LOG(...) ignore_unused_variable(__VA_ARGS__)
#else
#define NV_LOG(...) NV_MESSAGE(__VA_ARGS__)
#endif

//--------------------------------------------------------------------------
// NV_INVALID_OBJECT
//
// This is an object that we encountered during the C++ export process that
// we did not recognize. This might be due to an object that was illegally
// (or legally if its never used) deleted while still referenced.
//--------------------------------------------------------------------------
#define NV_INVALID_OBJECT VK_NULL_HANDLE
#define NV_POINTER_TO_INVALID_OBJECT nullptr

//--------------------------------------------------------------------------
// NV_VK_USER_PTR & NV_VK_FUNCTION_PTR
//
// These were non-null pointers to user data or functions in the original
// capture. It's impossible to recreate exactly what they were doing so
// we instead pass in a nullptr which is safe in all cases.
//--------------------------------------------------------------------------
#define NV_VK_USER_PTR nullptr
#define NV_VK_FUNCTION_PTR nullptr

//--------------------------------------------------------------------------
// NV_VK_VALIDATE
//
// Validate the result and throw error if failed
//--------------------------------------------------------------------------
NV_REPLAY_EXPORT VkResult VkDoValidate(VkResult result, const char* function, const char* file, int line);
#define NV_VK_VALIDATE(result) VkDoValidate(result, __FUNCTION__, __FILE__, __LINE__);