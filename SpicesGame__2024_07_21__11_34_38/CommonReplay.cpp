#include "CommonReplay.h"

#include <sstream>
#if defined(__ANDROID__)
#include <android/log.h>
#endif

#include "Arguments.h"
#include "Helpers.h"
#include "ReadOnlyDatabase.h"

bool hasFrameReset = true;
bool forceDebug = false;
bool automated = false;
bool useDebugBytecode = false;
bool debuggerBreakOnError = false;
char errorBuf[512];

#if defined(_WIN32)
// Tell the driver to use the high performance GPU
extern "C" {
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
};

HINSTANCE currentInstance = NULL;

HRESULT result;

//-----------------------------------------------------------------------------
// CheckResult
//-----------------------------------------------------------------------------
void CheckResult(HRESULT r, const char* file, int line)
{
    if (FAILED(r))
    {
        std::stringstream stream;
        stream << "Error 0x" << std::hex << r;
        ThrowErrorWithMessage(stream.str().c_str(), file, line);
    }
}

//-----------------------------------------------------------------------------
// NvNameHelperSetObjectName
//-----------------------------------------------------------------------------
void NvNameHelperSetObjectName(void* pObj, const char* pName)
{
    // NvSetObjectName does not support this type
}

#endif

union HexFloat
{
    float f;
    uint32_t h;
};

union HexDouble
{
    double d;
    uint64_t h;
};

float HexToFloat(uint32_t h)
{
    HexFloat v;
    v.h = h;
    return v.f;
}

double HexToDouble(uint64_t h)
{
    HexDouble v;
    v.h = h;
    return v.d;
}

float NAN_F()
{
    return HexToFloat(0xffc00000);
}

float INF_F()
{
    return HexToFloat(0x7f800000);
}

double NAN_D()
{
    return HexToDouble(0xfff8000000000000);
}

double INF_D()
{
    return HexToDouble(0x7ff0000000000000);
}

//-----------------------------------------------------------------------------
// Threading Resources
//-----------------------------------------------------------------------------
bool releaseReplayerThreads = false;
bool exitReplayerThreads = false;

#if defined(_WIN32)
HANDLE threadSequenceEvents[NUM_REPLAYER_THREADS] = { NULL };
HANDLE threadDoneEvents[NUM_REPLAYER_THREADS] = { NULL };
#else
EventsArray threadSequenceEvents;
EventsArray threadDoneEvents;
#endif

//-----------------------------------------------------------------------------
// ReportErrorWithMessage
//-----------------------------------------------------------------------------
void ReportErrorWithMessage(const char* message, const char* file, int line)
{
    std::stringstream stream;
    stream << message << " at " << file << "(" << line << ")";
    NV_MESSAGE(stream.str().c_str());
}

//-----------------------------------------------------------------------------
// ThrowErrorWithMessage
//-----------------------------------------------------------------------------
void ThrowErrorWithMessage(const char* message, const char* file, int line)
{
    std::stringstream stream;
    stream << message << " at " << file << "(" << line << ")";

    if (debuggerBreakOnError)
    {
#if defined(_WIN32)
        __debugbreak();
#else
        __builtin_trap();
#endif
    }

    throw std::runtime_error(stream.str());
}

//-----------------------------------------------------------------------------
// WriteMessage
//-----------------------------------------------------------------------------
void WriteMessage(const char* message)
{
#ifdef NV_WIN32_SUBSYSTEM
    if (!automated)
    {
        ::OutputDebugStringA(message);
        ::OutputDebugStringA("\n");
        return;
    }
#endif

#if defined(__ANDROID__)
    __android_log_print(ANDROID_LOG_INFO, "ngfx", "%s\n", message);
#else
    fprintf(stderr, "%s", message);
    fprintf(stderr, "\n");
#endif
}

//-----------------------------------------------------------------------------
// Database
//-----------------------------------------------------------------------------
static Serialization::ReadOnlyDatabase* s_pDatabase = nullptr;

//-----------------------------------------------------------------------------
// InitializeDatabase
//-----------------------------------------------------------------------------
void InitializeDatabase()
{
    // Set max page size: 64MB
    const static uint64_t MAX_PAGE_SIZE = 1 << 26;

    // Set max resident page count
#if defined(__arm__) || defined(__aarch64__) || defined(__ARM64__)
    const static size_t MAX_RESIDENT_PAGES = 4;
#else
    const static size_t MAX_RESIDENT_PAGES = 16;
#endif

    s_pDatabase = new Serialization::ReadOnlyDatabase(DATABASE_BIN_FILE, MAX_PAGE_SIZE, MAX_RESIDENT_PAGES);

    const auto lastInitResult = s_pDatabase->GetLastInitResult();
    if (lastInitResult != Serialization::ReadOnlyDatabase::InitResult::Ok)
    {
        std::stringstream stream;
        stream << "Failed to initialize database: " << Serialization::ReadOnlyDatabase::InitResultToString(lastInitResult);
        throw std::runtime_error(stream.str());
    }
}

//-----------------------------------------------------------------------------
// GetDatabase
//-----------------------------------------------------------------------------
Serialization::ReadOnlyDatabase& GetDatabase()
{
    return *s_pDatabase;
}

//-----------------------------------------------------------------------------
// FreeCachedMemory
//-----------------------------------------------------------------------------
void FreeCachedMemory()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    GetDatabase().FreeCachedMemory();
}

//------------------------------------------------------------------------------
// Common options
//------------------------------------------------------------------------------
static bool s_lazyMemcpy = false;
static bool s_noopMemcpy = false;
bool g_minSync = false;
size_t g_threadPoolThreadCount = 0;

static FnParseResults CommonReplayArguments(args::ArgumentParser& parser)
{
    static args::Group optCommongroup(parser, "Common options:");
    static args::Group optThreadinggroup(parser, "Threading options:", args::Group::Validators::AtMostOne);

    static args::Flag optLazyMemcpy(optCommongroup, "lazy-memcpy", "Only repeat memcpys when the data is known to have changed [default=false]", { "lazy-memcpy" });
    static args::Flag optNoopMemcpy(optCommongroup, "noop-memcpy", "Do not call memcpy after an initial few frames [default=false]", { "noop-memcpy" });
    static args::Flag optMinSync(optCommongroup, "minsync", "Use agressive fence/semaphore options.  May cause incorrect replay or crash. [default=false]", { "minsync" });

    static args::Flag optMultithreadedRecord(optThreadinggroup, "multithreaded-record", "Record commandlists/commandbuffers on a thread pool if supported. Deprecated since this is now default. [default=true]", { "multithreaded-record" });
    static args::Flag optSinglethreadedRecord(optThreadinggroup, "no-multithreaded-record", "Force inhibit multithreaded recording. This only affect D3D12 and Vulkan. [default=false]", { "no-multithreaded-record" });
    static args::ValueFlag<size_t> optMultithreadedThreadCount(optThreadinggroup, "force-threadpool-size", "Record commandlists/commandbuffers on the specified number of threads [default=automatic]", { "force-threadpool-size" });

    return [=]() {
        // No-op and lazy memcpy are mutually exclusive, with no-op superseding lazy
        if (optNoopMemcpy)
        {
            s_noopMemcpy = optNoopMemcpy.Get();
        }
        else if (optLazyMemcpy)
        {
            s_lazyMemcpy = optLazyMemcpy.Get();
        }

        if (optMinSync)
        {
            g_minSync = optMinSync.Get();
        }

        if (Application::MinimizeCPUOverheadRequested())
        {
            // This is where we set any options that we know are safe to enable and minimize the CPU overhead
        }

#if !defined(NV_REPLAY_ON_ORIGINAL_THREAD_IDS)
        g_threadPoolThreadCount = [&]() -> size_t {
            if (optSinglethreadedRecord)
            {
                return 0;
            }

            if (optMultithreadedThreadCount)
            {
                return optMultithreadedThreadCount.Get();
            }

            return std::thread::hardware_concurrency() - 1u;
        }();
#endif
    };
}

REGISTER_ARGUMENTS(CommonReplayArguments);

//------------------------------------------------------------------------------
// NVCheckedMemcpy
//------------------------------------------------------------------------------
void NVCheckedMemcpy(void* dst, const void* src, size_t size, NVCheckedMemcpyState& state)
{
    if (!s_lazyMemcpy && !s_noopMemcpy)
    {
        memcpy(dst, src, size);
        return;
    }

    switch (state)
    {
    case NVCheckedMemcpyState::PASS_0:
        memcpy(dst, src, size);
        state = NVCheckedMemcpyState::PASS_1;
        break;
    case NVCheckedMemcpyState::PASS_1:
        // Lazy memcpy only stops performing the memcopies if there are no changes
        // Noop memcpy stops performing the memcopies unconditionally
        if ((s_lazyMemcpy && 0 == memcmp(dst, src, size)) || s_noopMemcpy)
        {
            state = NVCheckedMemcpyState::DETECTED_NO_DIFFS;
            break;
        }
        state = NVCheckedMemcpyState::DETECTED_DIFFS;
        memcpy(dst, src, size);
        break;
    case NVCheckedMemcpyState::DETECTED_DIFFS:
        memcpy(dst, src, size);
        break;
    case NVCheckedMemcpyState::DETECTED_NO_DIFFS:
        break;
    }
}
