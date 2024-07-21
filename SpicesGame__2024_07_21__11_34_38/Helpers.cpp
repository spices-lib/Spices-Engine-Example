//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Helpers.cpp
// 
//-----------------------------------------------------------------------------

#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "ReadOnlyDatabase.h"

#if defined(ANDROID) || defined(__linux__) || defined(__QNX__)

#include <dlfcn.h>

#endif

#if !defined(_WIN64) && !defined(__x86_64__) && !defined(__ppc64__) && !defined(__LP64__)
#if defined(BUILD_UNSUPPORTED_CAPTURE) || defined(NV_AUTOMATED_BUILD)
#if defined(_MSC_VER)
#pragma message("Warning: Application originally targeted 64-bit; compiling now as 32-bit")
#else
#warning Application originally targeted 64-bit; compiling now as 32-bit
#endif
#else
#error Application originally targeted 64-bit; compiling now as 32-bit
#endif
#endif


//-----------------------------------------------------------------------------
// Common Resources
//-----------------------------------------------------------------------------
const char* ProcessName = "SpicesGame";
double array_of_0s[256] = { 0 };
const int g_ResourceInitFunctionCount = 1;
