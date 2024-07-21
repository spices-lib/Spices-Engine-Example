#include "Application.h"
#include "Arguments.h"
#include "Helpers.h"
#include "Threading.h"

#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <thread>

#if defined(__linux__)
#include <dlfcn.h>
#endif

#ifdef NV_HAS_FUNCTION_OVERRIDES
#include "function_overrides.h"
#else
#define My_init() init()
#define My_frame(frame_number, frame_functions) frame_functions
#define My_done() done()
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define FPS_AVG_WINDOW 32
#define FPS_WARMUP_WINDOW (2 * FPS_AVG_WINDOW)

static Application* s_instance = nullptr;

#ifdef NV_REPLAY_LIB_SHARED
typedef void (*PFN_CreateAndSetupResources)();
typedef void (*PFN_ReleaseResources)();
typedef void (*PFN_RunFrame)(uint64_t frameIndex);
PFN_CreateAndSetupResources CreateAndSetupResources = nullptr;
PFN_ReleaseResources ReleaseResources = nullptr;
PFN_RunFrame RunFrame = nullptr;
#else
#include "ReplayProcedures.h"
#endif

//------------------------------------------------------------------------------
// Application
//------------------------------------------------------------------------------
Application::Application()
{
    NV_ASSERT(s_instance == nullptr);
    s_instance = this;
}

//------------------------------------------------------------------------------
// ExecuteInternal
//------------------------------------------------------------------------------
int Application::ExecuteInternal(int argc, char** argv)
{
    int ret = EXIT_SUCCESS;

    // Necessary for override system
    auto init = [this]() { this->PlatformInit(); };
    auto done = [this]() { this->PlatformDone(); };

    std::vector<std::pair<uint64_t, ApplicationMemoryStats>> frameTimesAndMemory;

    if (m_dumpFrameTimes)
    {
        const auto frameTimeReservation = (m_repeatCount > 0) ? m_repeatCount : uint64_t(60 * 60 * 3);
        frameTimesAndMemory.reserve(static_cast<size_t>(frameTimeReservation));
    }

    // Dynamically load for shared library builds
#if defined(NV_REPLAY_LIB_SHARED)
#if defined(_WIN32)
    HMODULE lib = LoadLibrary(L"GeneratedReplay.dll");
    auto pfnGetProc = &GetProcAddress;
#else
    void* lib = dlopen("libGeneratedReplay.so", RTLD_NOW | RTLD_LOCAL);
    auto pfnGetProc = &dlsym;
#endif
    NV_THROW_IF(!lib, "Failed to load GeneratedReplay library");
    CreateAndSetupResources = reinterpret_cast<PFN_CreateAndSetupResources>(pfnGetProc(lib, "CreateAndSetupResources"));
    NV_THROW_IF(!CreateAndSetupResources, "Failed to find symbol CreateAndSetupResources");
    ReleaseResources = reinterpret_cast<PFN_ReleaseResources>(pfnGetProc(lib, "ReleaseResources"));
    NV_THROW_IF(!ReleaseResources, "Failed to find symbol ReleaseResources");
    RunFrame = reinterpret_cast<PFN_RunFrame>(pfnGetProc(lib, "RunFrame"));
    NV_THROW_IF(!RunFrame, "Failed to find symbol RunFrame");
#endif

    std::thread watchdogThread;

    try
    {

        My_init();

        auto lastFpsReport = std::chrono::high_resolution_clock::now();
        float minDurationMs = FLT_MAX;
        float maxDurationMs = 0;
        float runningAverage[FPS_AVG_WINDOW] = { 0 };
        float totalDurationMs = 0;
        float minDurationMsTotal = FLT_MAX;
        float maxDurationMsTotal = 0;

        if (m_watchdogThreadEnabled)
        {
            m_watchdogThreadActive = true;
            watchdogThread = std::thread(&Application::ExecWatchdog, this);
        }

        auto OutputPerfStats = [](const char* prefix, float durationAVGMs, float fps, float minDurationMs, float maxDurationMs, uint64_t frames) {
            NV_MESSAGE("%sAVG: %6.3f ms (%6.3f FPS) | MIN: %6.3f ms | MAX: %6.3f ms | Frames: %6u", prefix, durationAVGMs, fps, minDurationMs, maxDurationMs, frames);
        };

        while (!m_shutdown && (m_repeatCount == 0 || m_frameIndex < m_repeatCount))
        {

            if (!ProcessMessages())
            {
                break;
            }

            const auto start = std::chrono::high_resolution_clock::now();

            My_frame(
                m_frameIndex,
                RunFrame(m_frameIndex););

            const auto end = std::chrono::high_resolution_clock::now();
            const auto diff = (end - start);
            const auto deltaInMs = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();

            if (m_dumpFrameTimes)
            {
                ApplicationMemoryStats memoryStats = {};
                if (m_fnGetMemoryStats)
                {
                    m_fnGetMemoryStats(memoryStats);
                }
                frameTimesAndMemory.emplace_back(deltaInMs, memoryStats);
            }

            if (m_perfStats)
            {
                if (m_frameIndex > FPS_WARMUP_WINDOW)
                {
                    const auto timeSinceLastReport = std::chrono::duration_cast<std::chrono::milliseconds>(end - lastFpsReport);
                    float durationMs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.f;
                    minDurationMs = std::min<float>(minDurationMs, durationMs);
                    maxDurationMs = std::max<float>(maxDurationMs, durationMs);

                    const auto indexAfterWarmup = (m_frameIndex - FPS_WARMUP_WINDOW);

                    runningAverage[indexAfterWarmup % FPS_AVG_WINDOW] = durationMs;
                    totalDurationMs += durationMs;
                    if (timeSinceLastReport >= std::chrono::seconds(1))
                    {
                        float sum = 0;
                        const uint32_t nFramesToAverage = std::min<uint32_t>(static_cast<uint32_t>(indexAfterWarmup + 1), FPS_AVG_WINDOW);
                        for (uint32_t i = 0; i < nFramesToAverage; i++)
                        {
                            sum += runningAverage[i];
                        }
                        OutputPerfStats("", sum / float(nFramesToAverage), (1000.f / durationMs), minDurationMs, maxDurationMs, nFramesToAverage);
                        lastFpsReport = end;
                        minDurationMsTotal = std::min<float>(minDurationMsTotal, minDurationMs);
                        maxDurationMsTotal = std::max<float>(maxDurationMsTotal, maxDurationMs);

                        minDurationMs = FLT_MAX;
                        maxDurationMs = 0;
                    }
                }
                else if (m_frameIndex == FPS_WARMUP_WINDOW)
                {
                    lastFpsReport = end;
                }
            }

            m_frameIndex++;
        }

        if (m_perfStats && m_frameIndex > FPS_WARMUP_WINDOW)
        {
            const float durationAVGMs = totalDurationMs / float(m_frameIndex - FPS_WARMUP_WINDOW);
            OutputPerfStats("Total ", durationAVGMs, (1000.f / durationAVGMs), minDurationMsTotal, maxDurationMsTotal, m_frameIndex);
        }
    }
    catch (std::exception& e)
    {
        OnError(e.what());
        ret = EXIT_FAILURE;
    }

    // Clean up the watchdog thread if it is running
    if (watchdogThread.joinable())
    {
        m_watchdogThreadActive = false;
        watchdogThread.join();
    }

    My_done();

    if (m_dumpFrameTimes)
    {
        auto convertToMs = [](uint64_t n) -> float {
            return n / 1000.f;
        };

        FILE* f = fopen("frametimes.csv", "w");
        if (f)
        {
            // Print label row
            fprintf(f, "time, ");
            const auto statCount = m_memoryStatNames.size();
            for (const auto& memStat : m_memoryStatNames)
            {
                fprintf(f, "%s, ", memStat.c_str());
            }
            fprintf(f, "\n");

            // Print stat rows
            for (const auto& frameTimeAndMemory : frameTimesAndMemory)
            {
                fprintf(f, "%.3f, ", convertToMs(frameTimeAndMemory.first));
                for (size_t statIdx = 0; statIdx < statCount; ++statIdx)
                {
                    fprintf(f, "%llu, ", (long long unsigned int)frameTimeAndMemory.second.stats[statIdx]);
                }
                fprintf(f, "\n");
            }
            fclose(f);
        }
        else
        {
            OutputMessage("Failed to dump frame times");
        }
    }

    return ret;
}

//------------------------------------------------------------------------------
// OnError
//------------------------------------------------------------------------------
void Application::OnError(const char* pMessage)
{
    OutputMessage(std::string("Nvda.Replay Error: ") + std::string(pMessage));
    if (!automated)
    {
        OutputMessage("Press any key to continue . . .");
        std::getchar();
    }
}

//------------------------------------------------------------------------------
// Execute
//------------------------------------------------------------------------------
int Application::Execute()
{
    int argc = 0;
    char* argv[] = { const_cast<char*>("") };
    return ExecuteInternal(argc, argv);
}

//------------------------------------------------------------------------------
// Execute
//------------------------------------------------------------------------------
int Application::Execute(int argc, char** argv)
{
    // Parse the command line arguments
    if (!ParseCommandLine(argc, argv))
    {
        return EXIT_FAILURE;
    }

    return ExecuteInternal(argc, argv);
}

//------------------------------------------------------------------------------
// VerboseOutput (static)
//------------------------------------------------------------------------------
bool Application::VerboseOutput()
{
    return s_instance->m_verbose;
}

//------------------------------------------------------------------------------
// HasForceBorderlessWindow (static)
//------------------------------------------------------------------------------
bool Application::HasForceBorderlessWindow()
{
    return s_instance->m_forceBorderlessWindow;
}

//------------------------------------------------------------------------------
// RegisterForAsyncDataReset
//------------------------------------------------------------------------------
void Application::RegisterForAsyncDataReset(Application::AsyncResetFlags flags)
{
    s_instance->m_asyncDataResetFlags = flags;
}

//------------------------------------------------------------------------------
// GetAsyncDataResetFlags
//------------------------------------------------------------------------------
Application::AsyncResetFlags Application::GetAsyncDataResetFlags()
{
    return s_instance->m_asyncDataResetFlags;
}

//------------------------------------------------------------------------------
// SetAsyncDataResetter
//------------------------------------------------------------------------------
void Application::SetAsyncDataResetter(std::function<void()> fnDataResetter)
{
    s_instance->m_fnDataResetter = fnDataResetter;
}

//------------------------------------------------------------------------------
// DoAsyncDataReset
//------------------------------------------------------------------------------
void Application::DoAsyncDataReset()
{
    NV_THROW_IF(!s_instance->m_fnDataResetter, "Expected function");
    s_instance->m_fnDataResetter();
}

#if defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
//------------------------------------------------------------------------------
// HasMultiThreadedReplay
//------------------------------------------------------------------------------
bool Application::HasMultiThreadedReplay()
{
    return s_instance->m_multiThreadedReplay;
}

//------------------------------------------------------------------------------
// EnableMultiThreadedReplay
//------------------------------------------------------------------------------
void Application::EnableMultiThreadedReplay(bool enable)
{
    s_instance->m_multiThreadedReplay = enable;
}
#endif

//------------------------------------------------------------------------------
// MinimizeCPUOverheadRequested
//------------------------------------------------------------------------------
bool Application::MinimizeCPUOverheadRequested()
{
    return s_instance->m_minimizeCPUOverhead;
}

//------------------------------------------------------------------------------
// SetFrameExecutor
//------------------------------------------------------------------------------
void Application::SetFrameExecutor(std::function<bool(uint64_t)> fnExecutor)
{
    s_instance->m_fnFrameExecutor = fnExecutor;
}

//------------------------------------------------------------------------------
// ExecuteFrame
//------------------------------------------------------------------------------
bool Application::ExecuteFrame(uint64_t frameIndex)
{
    NV_ASSERT(!!s_instance->m_fnFrameExecutor);
    return s_instance->m_fnFrameExecutor(frameIndex);
}

//------------------------------------------------------------------------------
// RegisterMemoryStats
//------------------------------------------------------------------------------
void Application::RegisterMemoryStats(size_t count, const char** names, ApplicationMemoryStatsCallback getStatsCallback)
{
    NV_THROW_IF(!getStatsCallback, "Require callback");
    NV_THROW_IF(!names, "Require at least one name");
    NV_THROW_IF(!count, "Require at least one name");
    NV_THROW_IF(count > ApplicationMemoryStats::MAX_STATS, "Too many stats");

    for (size_t i = 0; i < count; ++i)
    {
        NV_THROW_IF(!names[i], "Name cannot be null");
        m_memoryStatNames.push_back(names[i]);
    }
    m_fnGetMemoryStats = getStatsCallback;
}

//------------------------------------------------------------------------------
// ShouldCatchAndReportSystemExceptions
//------------------------------------------------------------------------------
bool Application::ShouldCatchAndReportSystemExceptions()
{
    return s_instance->m_catchAndReportSystemExceptions;
}

//------------------------------------------------------------------------------
// Init
//------------------------------------------------------------------------------
void Application::PlatformInit()
{
    CreateAndSetupResources();
}

//------------------------------------------------------------------------------
// Done
//------------------------------------------------------------------------------
void Application::PlatformDone()
{
    ReleaseResources();
}

//------------------------------------------------------------------------------
// OutputMessage
//------------------------------------------------------------------------------
void Application::OutputMessage(const std::string& message) const
{
    NV_MESSAGE(message.c_str());
}

//------------------------------------------------------------------------------
// ParseCommandLine
//------------------------------------------------------------------------------
bool Application::ParseCommandLine(int argc, char** argv)
{
    // Create parses
    args::ArgumentParser parser("Nvda.Replayer -- NVIDIA Nsight C++ Capture Replayer");

    // This matches the previous parser
    parser.ShortPrefix("/");
    parser.LongPrefix("-");
    parser.helpParams.showTerminator = false;

    // API agnostic options
    args::HelpFlag help(parser, "help", "Display this help menu", { "help" });
    args::ValueFlag<uint32_t> optRepeat(parser, "N", "Number of frames to run", { "repeat" });
    args::Flag optNoReset(parser, "noreset", "Do not perform a state reset in between frames", { "noreset", "no-reset" });
    args::Flag optWatchdog(parser, "watchdog", "Automatically terminate unresponsive applications after 10 seconds", { "watchdog" });
    args::Flag optForceDebug(parser, "forcedebug", "Force enable API validation", { "forcedebug", "force-debug" });
    args::Flag optAutomated(parser, "automated", "Do not use facilities that require user interaction", { "automated" });
    args::Flag optPerfStats(parser, "fps", "Include FPS in output messages", { "fps" });
    args::Flag optForceBorderlessWindow(parser, "wb", "Force borderless window", { "wb" });
    args::ValueFlag<std::string> optLogDir(parser, "FILE", "Write stdout/stderr messages to an output file", { "log" });
    args::Flag optDumpFrameTimes(parser, "dumpframetimes", "Dumps individual frame times into a csv", { "dumpframetimes" });
    args::Flag optDebugShaderBytecode(parser, "debugshaderbytecode", "Use debug shader bytecode (default is to use release bytecode)", { "debugshaderbytecode" });
    args::Flag optVerbose(parser, "verbose", "Verbose output", { "v", "verbose" });
    args::Flag optMinimizeCPUOverhead(parser, "mincpu", "Enable all known safe options for minimizing CPU overhead", { "mincpu" });
    args::Flag optNoSystemExceptionHandling(parser, "noseh", "Suppress catching system exceptions", { "noseh" });
    args::Flag optDebuggerBreakOnError(parser, "debuggerbreakonerror", "Issue a debugger break on an error", { "debuggerbreakonerror" });

    // Register add external API-specific options
    std::vector<FnParseResults> vecFnParseResults;
    for (auto& fnAddArguments : GetExternalArguments())
    {
        vecFnParseResults.push_back(fnAddArguments(parser));
    }

    // Positional options
    args::PositionalList<std::string> overrideArguments(parser, "override_arguments", "Extra arguments to be made available to function_overrides", args::Options::Hidden);

    // Perform parse
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Completion& e)
    {
        std::cout << e.what();
        return false;
    }
    catch (const args::Help&)
    {
        OutputMessage(parser.Help());
        return false;
    }
    catch (const args::Error& e)
    {
        std::stringstream ss;
        ss << e.what() << std::endl;
        ss << parser.Help();
        OutputMessage(ss.str());
        return false;
    }
    catch (const std::exception& e)
    {
        OutputMessage(e.what());
        return false;
    }

    if (optRepeat)
    {
        m_repeatCount = optRepeat.Get();
    }

    if (optNoReset)
    {
        hasFrameReset = false;
    }

    if (optWatchdog)
    {
        m_watchdogThreadEnabled = true;
    }

    if (optForceDebug)
    {
        forceDebug = true;
    }

    if (optAutomated)
    {
        automated = true;
#if defined(_WIN32)
        _putenv("NSIGHT_AUTOMATED_TEST=1");
#else
        setenv("NSIGHT_AUTOMATED_TEST", "1", 1);
#endif
    }

    if (optLogDir)
    {
        automated = true;
        FILE* file = freopen(optLogDir.Get().c_str(), "w", stderr);
        if (!file)
        {
            OutputMessage("Failed to open log file");
        }
    }

    if (optDumpFrameTimes)
    {
        m_dumpFrameTimes = true;
    }

    if (optForceBorderlessWindow)
    {
        m_forceBorderlessWindow = true;
    }

    if (optPerfStats)
    {
        m_perfStats = true;
    }

    if (optDebugShaderBytecode)
    {
        useDebugBytecode = true;
    }

    if (optVerbose)
    {
        m_verbose = true;
    }

    if (optMinimizeCPUOverhead)
    {
        m_minimizeCPUOverhead = true;
    }

    if (m_minimizeCPUOverhead)
    {
        // This is where we set any options that we know are safe to enable and minimize the CPU overhead
        hasFrameReset = false;
    }

    if (optNoSystemExceptionHandling)
    {
        m_catchAndReportSystemExceptions = false;
    }

    if (optDebuggerBreakOnError)
    {
        debuggerBreakOnError = true;
    }

    // Parse additional options
    for (auto& fnParseResults : vecFnParseResults)
    {
        fnParseResults();
    }

    return true;
}

//------------------------------------------------------------------------------
// Watchdog
//------------------------------------------------------------------------------
void Application::ExecWatchdog()
{
    static const std::chrono::milliseconds WATCHDOG_INTERVAL(500);
    static const std::chrono::milliseconds WATCHDOG_TIMEOUT(10000);

    std::chrono::milliseconds millisecondsSinceLastFrame(0);
    uint64_t lastFrameIndex = 0;
    while (m_watchdogThreadActive)
    {
        // Sleep and increment the counter
        std::this_thread::sleep_for(WATCHDOG_INTERVAL);
        millisecondsSinceLastFrame += WATCHDOG_INTERVAL;

        // If the frame index has changed, reset the counter. Otherwise,
        // check if we've timed out and terminate the process.
        const uint64_t currentFrameIndex = m_frameIndex;
        if (lastFrameIndex != currentFrameIndex)
        {
            lastFrameIndex = currentFrameIndex;
            millisecondsSinceLastFrame = std::chrono::milliseconds(0);
        }
        else if (millisecondsSinceLastFrame > WATCHDOG_TIMEOUT)
        {
            std::terminate();
        }
    }
}
