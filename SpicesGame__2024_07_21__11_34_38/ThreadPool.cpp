//-------------------------------------------------------------------------------
// File: ThreadPool.h
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//-------------------------------------------------------------------------------

#include "ThreadPool.h"
#include "Application.h"
#include "ThreadPoolImpl.h"

#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
//--------------------------------------------------------------------------------------
// NvHasMultithreadedReplay
//--------------------------------------------------------------------------------------
bool NvHasMultithreadedReplay()
{
    return Application::HasMultiThreadedReplay();
}
#endif