//---------------------------------------------------------------------------
// File: function_overrides.h
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#pragma once

#if defined(NV_VULKAN_SC_SUPPORT)
#include <vulkan/vulkan_sc_core.hpp>
#else
#include <vulkan/vulkan.h>
#endif

#define My_init() \
    init()
#define My_frame(frame_number, frame_functions) \
    frame_functions
#define My_done() \
    done()

// D3D style perf markers
#define My_D3DPERF_BeginEvent(col, wszName) \
    D3DPERF_BeginEvent(col, wszName)
#define My_D3DPERF_EndEvent() \
    D3DPERF_EndEvent()
#define My_D3DPERF_SetMarker(col, wszName) \
    D3DPERF_SetMarker(col, wszName)

// NVTX style perf markers
#define My_nvtxMarkEx(eventAttrib) \
    nvtxMarkEx(eventAttrib)
#define My_nvtxMarkA(message) \
    nvtxMarkA(message)
#define My_nvtxMarkW(message) \
    nvtxMarkW(message)
#define My_nvtxRangeStartEx(eventAttrib) \
    nvtxRangeStartEx(eventAttrib)
#define My_nvtxRangeStartA(message) \
    nvtxRangeStartA(message)
#define My_nvtxRangeStartW(message) \
    nvtxRangeStartW(message)
#define My_nvtxRangeEnd(id) \
    nvtxRangeEnd(id)
#define My_nvtxRangePushEx(eventAttrib) \
    nvtxRangePushEx(eventAttrib)
#define My_nvtxRangePushA(message) \
    nvtxRangePushA(message)
#define My_nvtxRangePushW(message) \
    nvtxRangePushW(message)
#define My_nvtxRangePop() \
    nvtxRangePop()
#define My_nvtxNameCategoryA(category, name) \
    nvtxNameCategoryA(category, name)
#define My_nvtxNameCategoryW(category, name) \
    nvtxNameCategoryW(category, name)
#define My_nvtxNameOsThreadA(threadId, name) \
    nvtxNameOsThreadA(threadId, name)
#define My_nvtxNameOsThreadW(threadId, name) \
    nvtxNameOsThreadW(threadId, name)

//
// Example override usage:
//
// function_overrides.h
//
//     #define VKCREATEINSTANCE_PRE(...)  OVERRIDE_VkCreateInstance_Pre(__VA_ARGS__)
//     #define VKCREATEINSTANCE_POST(...) OVERRIDE_VkCreateInstance_Post(__VA_ARGS__)
//
//     void OVERRIDE_VkCreateInstance_Pre(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
//     void OVERRIDE_VkCreateInstance_Post(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
//
// function_overrides.cpp
//
//     void OVERRIDE_VkCreateInstance_Pre(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
//     {
//     }
//
//     void OVERRIDE_VkCreateInstance_Post(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
//     {
//     }
//
