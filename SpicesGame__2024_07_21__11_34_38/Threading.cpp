//--------------------------------------------------------------------------------------
// File: Threading.cpp
//
// Distributed as part of NVIDIA Nsight serialization output.
//
// Copyright (c) NVIDIA Corporation.  All rights reserved.
//--------------------------------------------------------------------------------------

#include "Threading.h"

#if defined(_WIN32)

//--------------------------------------------------------------------------------------
// ThreadStartParams - Struct used to pass the params to the thread startup function
//--------------------------------------------------------------------------------------
struct ThreadStartParams
{
    ThreadRunner* threadRunner;
    HANDLE sequenceEvent;
    HANDLE doneEvent;
    bool* exitReplayerThreads;
    bool* releaseReplayerThreads;
};

#define WAIT_FOR_SIGNAL() \
    WaitForSingleObject(params->sequenceEvent, INFINITE)

#define SIGNAL_THREAD_DONE() \
    SetEvent(params->doneEvent)

#define RELEASE_THREAD_RESOURCES()      \
    CloseHandle(params->sequenceEvent); \
    CloseHandle(params->doneEvent)

//--------------------------------------------------------------------------------------
// ThreadStart - The method each replayer thread begins running
//--------------------------------------------------------------------------------------
DWORD WINAPI ThreadStart(LPVOID lpParameter)
{
    ThreadStartParams* params = (ThreadStartParams*)lpParameter;

    bool firstTime = true;

    while (true)
    {
        WAIT_FOR_SIGNAL();

        if (firstTime)
        {
            params->threadRunner->Init();
            firstTime = false;
        }

        if (*params->releaseReplayerThreads)
        {
            params->threadRunner->Release();
            SIGNAL_THREAD_DONE();
            continue;
        }

        if (*params->exitReplayerThreads)
        {
            SIGNAL_THREAD_DONE();
            break;
        }

        params->threadRunner->RunThread();
        SIGNAL_THREAD_DONE();
    }

    RELEASE_THREAD_RESOURCES();

    delete params;

    return EXIT_SUCCESS;
}

//--------------------------------------------------------------------------------------
// CreateThreadEvents - Create Windows events used to synchronize the threads
//--------------------------------------------------------------------------------------
bool CreateThreadEvents(unsigned int numThreads, HANDLE* events)
{
    for (unsigned int currentEvent = 0; currentEvent < numThreads; ++currentEvent)
    {
        HANDLE eventHandle = CreateEvent(NULL, // Cannot be inherited
            FALSE, // Auto reset object
            FALSE, // Initially not signaled
            NULL); // No need for a name

        if (!eventHandle)
        {
            for (unsigned int existingHandle = 0; existingHandle < currentEvent; ++existingHandle)
            {
                CloseHandle(events[existingHandle]);
            }

            return false;
        }

        events[currentEvent] = eventHandle;
    }

    return true;
}

//--------------------------------------------------------------------------------------
// CreateReplayerThreads - Create and start the replayer threads
//--------------------------------------------------------------------------------------
bool CreateReplayerThreads(ThreadRunner** threadRunners, unsigned int numThreads, HANDLE* sequenceEvents, HANDLE* doneEvents, bool& exitThreads, bool& releaseThreads)
{
    for (unsigned int currentThread = 0; currentThread < numThreads; ++currentThread)
    {
        ThreadStartParams* params = new ThreadStartParams();
        {
            params->threadRunner = threadRunners[currentThread];
            params->sequenceEvent = sequenceEvents[currentThread];
            params->doneEvent = doneEvents[currentThread];
            params->exitReplayerThreads = &exitThreads;
            params->releaseReplayerThreads = &releaseThreads;
        }

        // Create the thread
        HANDLE threadHandle = CreateThread(NULL, // Cannot be inherited
            0, // Default stack size
            ThreadStart, // The function to run
            (LPVOID)params, // The arguments
            0, // Start immediately
            NULL); // No need for the Windows thread id

        if (!threadHandle)
        {
            for (unsigned int existingHandle = currentThread; existingHandle < numThreads; ++existingHandle)
            {
                CloseHandle(sequenceEvents[existingHandle]);
                CloseHandle(doneEvents[existingHandle]);
            }

            delete params;
            ExitReplayerThreads(currentThread, sequenceEvents, doneEvents, exitThreads);
            return false;
        }

        CloseHandle(threadHandle);
    }

    return true;
}

//--------------------------------------------------------------------------------------
// ReleaseReplayerThreads - Release all of the replayer threads
//--------------------------------------------------------------------------------------
void ReleaseReplayerThreads(unsigned int numThreads, HANDLE* sequenceEvents, HANDLE* doneEvents, bool& releaseThreads)
{
    // Set the flag telling the threads to release
    releaseThreads = true;

    // Wake up each thread
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        SetEvent(sequenceEvents[i]);
    }

    // Wait for each thread to release
    WaitForMultipleObjects(numThreads, doneEvents, TRUE, INFINITE);

    releaseThreads = false;
}

//--------------------------------------------------------------------------------------
// ExitReplayerThreads - Exit all of the replayer threads
//--------------------------------------------------------------------------------------
void ExitReplayerThreads(unsigned int numThreads, HANDLE* sequenceEvents, HANDLE* doneEvents, bool& exitThreads)
{
    // Set the flag telling the threads to exit
    exitThreads = true;

    // Wake up each thread
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        SetEvent(sequenceEvents[i]);
    }

    // Wait for each thread to exit
    WaitForMultipleObjects(numThreads, doneEvents, TRUE, INFINITE);
}

//--------------------------------------------------------------------------------------
// RunReplayerThreads - Tell each replayer thread to run a frame and wait for
// them to complete
//--------------------------------------------------------------------------------------
void RunReplayerThreads(unsigned int numThreads, unsigned int startThread, HANDLE* doneEvents, HANDLE* sequenceEvents)
{
    // Tell the first thread to begin the frame
    SetEvent(sequenceEvents[startThread]);

    // Wait for the threads to report that they are ready to run the post frame method
    WaitForMultipleObjects(numThreads, doneEvents, TRUE, INFINITE);

    // Wake up the threads so they can run their post frame methods
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        SetEvent(sequenceEvents[i]);
    }

    // Wait for all of the post frame methods to finish
    WaitForMultipleObjects(numThreads, doneEvents, TRUE, INFINITE);
}

//--------------------------------------------------------------------------------------
// ThreadRunner implementations - Implementation of ThreadRunner class and derived
// classes
//--------------------------------------------------------------------------------------
ThreadRunner::ThreadRunner(HANDLE sequenceEvent, HANDLE doneEvent, RunFrameFunc runFrameFunc)
    : m_sequenceEvent(sequenceEvent)
    , m_doneEvent(doneEvent)
    , m_runFrameFunc(runFrameFunc)
{
}

void ThreadRunner::RunThread()
{
    PreRunThread();
    m_runFrameFunc();
    PostRunThread();
}

void ThreadRunner::SignalMainThreadAndWait() const
{
    SetEvent(m_doneEvent);
    WaitForSingleObject(m_sequenceEvent, INFINITE);
}

BasicThreadRunner::BasicThreadRunner(HANDLE sequenceEvent, HANDLE doneEvent, RunFrameFunc runFrameFunc, ResetFrameFunc resetFrameFunc)
    : ThreadRunner(sequenceEvent, doneEvent, runFrameFunc)
    , m_resetFrameFunc(resetFrameFunc)
{
}

void BasicThreadRunner::PostRunThread()
{
    // Make sure to let the main thread know we are here and wait for its permission
    // to continue.
    SignalMainThreadAndWait();
    if (hasFrameReset)
    {
        m_resetFrameFunc(false);
    }
}

#else // defined(WIN32)

#include <thread>

#define WAIT_FOR_SIGNAL(_ThreadID) \
    threadSequenceEvents[_ThreadID]->Wait()

#define SIGNAL_THREAD_DONE(_ThreadID) \
    threadDoneEvents[_ThreadID]->Signal()

//--------------------------------------------------------------------------------------
// ThreadStart - The method each replayer thread begins running
//--------------------------------------------------------------------------------------
static void ThreadStart(unsigned int threadId, std::shared_ptr<ThreadRunner> spThreadRunner)
{
    bool firstTime = true;
    while (true)
    {
        WAIT_FOR_SIGNAL(threadId);

        if (firstTime)
        {
            spThreadRunner->Init();
            firstTime = false;
        }

        if (releaseReplayerThreads)
        {
            spThreadRunner->Release();
            SIGNAL_THREAD_DONE(threadId);
            continue;
        }

        if (exitReplayerThreads)
        {
            SIGNAL_THREAD_DONE(threadId);
            break;
        }

        spThreadRunner->RunThread();
        SIGNAL_THREAD_DONE(threadId);
    }
}

//--------------------------------------------------------------------------------------
// CreateThreadEvents - Create events used to synchronize the threads
//--------------------------------------------------------------------------------------
bool CreateThreadEvents(EventsArray& events)
{
    for (auto& event : events)
    {
        event = std::make_shared<AutoResetEvent>();
    }

    return true;
}

//--------------------------------------------------------------------------------------
// CreateReplayerThreads - Create and start the replayer threads
//--------------------------------------------------------------------------------------
bool CreateReplayerThreads(ThreadRunnerArray& threadRunners)
{
    unsigned int numCreatedThreads = 0;
    try
    {
        for (auto& threadRunner : threadRunners)
        {
            // Create a new replayer thread
            threadRunner->CreateThread(ThreadStart, numCreatedThreads);
            ++numCreatedThreads;
        }
    }
    catch (...)
    {
        ExitReplayerThreads(numCreatedThreads);
        return false;
    }

    return true;
}

//--------------------------------------------------------------------------------------
// WaitForReplayerThreadsToComplete - Helper to wake up the main thread once all
// replayer threads have signaled they are done
//--------------------------------------------------------------------------------------
static void WaitForReplayerThreadsToComplete(unsigned int numThreads)
{
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        threadDoneEvents[i]->Wait();
    }
}

//--------------------------------------------------------------------------------------
// ReleaseReplayerThreads - Release all of the replayer threads, the context is still
// avialable at the time.
//--------------------------------------------------------------------------------------
void ReleaseReplayerThreads(unsigned int numThreads)
{
    // Set the flag telling the threads to release
    releaseReplayerThreads = true;

    // Wake up each thread
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        threadSequenceEvents[i]->Signal();
    }

    WaitForReplayerThreadsToComplete(numThreads);

    // Reset the flag in case we are started again
    releaseReplayerThreads = false;
}

//--------------------------------------------------------------------------------------
// ExitReplayerThreads - Exit all of the replayer threads
//--------------------------------------------------------------------------------------
void ExitReplayerThreads(unsigned int numThreads)
{
    // Set the flag telling the threads to exit
    exitReplayerThreads = true;

    // Wake up each thread
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        threadSequenceEvents[i]->Signal();
    }

    WaitForReplayerThreadsToComplete(numThreads);

    // Reset the flag in case we are started again
    exitReplayerThreads = false;
}

//--------------------------------------------------------------------------------------
// RunReplayerThreads - Tell each replayer thread to run a frame and wait for
// them to complete
//--------------------------------------------------------------------------------------
void RunReplayerThreads()
{
    // Tell the first thread to begin the frame
    threadSequenceEvents[0]->Signal();

    // Wait for the threads to report that they are ready to run the post frame method
    WaitForReplayerThreadsToComplete(NUM_REPLAYER_THREADS);

    // Wake up the threads so they can run their post frame methods
    for (auto& sequenceEvent : threadSequenceEvents)
    {
        sequenceEvent->Signal();
    }

    // Wait for all of the post frame methods to finish
    WaitForReplayerThreadsToComplete(NUM_REPLAYER_THREADS);
}

//--------------------------------------------------------------------------------------
// AutoResetEvent implementation
//--------------------------------------------------------------------------------------
AutoResetEvent::AutoResetEvent()
    : m_signaled(false)
    , m_mutex()
    , m_condtionVariable()
{
}

void AutoResetEvent::Signal()
{
    // Manage scope of lock
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        m_signaled = true;
    }

    m_condtionVariable.notify_one();
}

void AutoResetEvent::Wait()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_condtionVariable.wait(lock, [this]() { return m_signaled; });
    m_signaled = false;
}

//--------------------------------------------------------------------------------------
// ThreadRunner implementations - Implementation of ThreadRunner class and derived
// classes
//--------------------------------------------------------------------------------------
ThreadRunner::ThreadRunner(unsigned int threadId, RunFrameFunc runFrameFunc)
    : m_threadId(threadId)
    , m_runFrameFunc(runFrameFunc)
{
}

void ThreadRunner::CreateThread(ThreadStartFunc threadStartFunc, unsigned int threadId)
{
    std::thread newthread(threadStartFunc, threadId, shared_from_this());
    newthread.detach();
}

void ThreadRunner::RunThread()
{
    PreRunThread();
    m_runFrameFunc();
    PostRunThread();
}

void ThreadRunner::SignalMainThreadAndWait() const
{
    SIGNAL_THREAD_DONE(m_threadId);
    WAIT_FOR_SIGNAL(m_threadId);
}

unsigned int ThreadRunner::GetThreadId() const
{
    return m_threadId;
}

BasicThreadRunner::BasicThreadRunner(unsigned int threadId, RunFrameFunc runFrameFunc, ResetFrameFunc resetFrameFunc)
    : ThreadRunner(threadId, runFrameFunc)
    , m_resetFrameFunc(resetFrameFunc)
{
}

void BasicThreadRunner::PostRunThread()
{
    // Make sure to let the main thread know we are here and wait for its permission
    // to continue.
    SignalMainThreadAndWait();
    if (hasFrameReset)
    {
        m_resetFrameFunc(false);
    }
}

#endif // defined(_WIN32)
