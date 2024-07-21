#include "Win32Application.h"

#include <sstream>

#include <windows.h>

#include "CommonReplay.h"
#include "Helpers.h"

#include <imagehlp.h>
#pragma comment(lib, "Dbghelp.lib")

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
std::string g_exceptionReport;

//------------------------------------------------------------------------------
// GetExceptionString
//------------------------------------------------------------------------------
static const char* GetExceptionString(DWORD code)
{
    switch (code)
    {
    case EXCEPTION_ACCESS_VIOLATION:
        return "EXCEPTION_ACCESS_VIOLATION";
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
    case EXCEPTION_BREAKPOINT:
        return "EXCEPTION_BREAKPOINT";
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        return "EXCEPTION_DATATYPE_MISALIGNMENT";
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        return "EXCEPTION_FLT_DENORMAL_OPERAND";
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        return "EXCEPTION_FLT_DIVIDE_BY_ZERO";
    case EXCEPTION_FLT_INEXACT_RESULT:
        return "EXCEPTION_FLT_INEXACT_RESULT";
    case EXCEPTION_FLT_INVALID_OPERATION:
        return "EXCEPTION_FLT_INVALID_OPERATION";
    case EXCEPTION_FLT_OVERFLOW:
        return "EXCEPTION_FLT_OVERFLOW";
    case EXCEPTION_FLT_STACK_CHECK:
        return "EXCEPTION_FLT_STACK_CHECK";
    case EXCEPTION_FLT_UNDERFLOW:
        return "EXCEPTION_FLT_UNDERFLOW";
    case EXCEPTION_GUARD_PAGE:
        return "EXCEPTION_GUARD_PAGE";
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        return "EXCEPTION_ILLEGAL_INSTRUCTION";
    case EXCEPTION_IN_PAGE_ERROR:
        return "EXCEPTION_IN_PAGE_ERROR";
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        return "EXCEPTION_INT_DIVIDE_BY_ZERO";
    case EXCEPTION_INT_OVERFLOW:
        return "EXCEPTION_INT_OVERFLOW";
    case EXCEPTION_INVALID_DISPOSITION:
        return "EXCEPTION_INVALID_DISPOSITION";
    case EXCEPTION_INVALID_HANDLE:
        return "EXCEPTION_INVALID_HANDLE";
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        return "EXCEPTION_NONCONTINUABLE_EXCEPTION";
    case EXCEPTION_PRIV_INSTRUCTION:
        return "EXCEPTION_PRIV_INSTRUCTION";
    case EXCEPTION_SINGLE_STEP:
        return "EXCEPTION_SINGLE_STEP";
    case EXCEPTION_STACK_OVERFLOW:
        return "EXCEPTION_STACK_OVERFLOW";
    default:
        return nullptr;
    }
}

//------------------------------------------------------------------------------
// GetStackTrace
//------------------------------------------------------------------------------
static std::string GetStackTrace()
{
    std::ostringstream out;
    char buf[128];

    HANDLE process = GetCurrentProcess();
    SymInitialize(process, NULL, TRUE);

    const unsigned int numEntries = 24;
    void* stack[numEntries];
    unsigned short frames = CaptureStackBackTrace(0, numEntries, stack, NULL);

    const unsigned int maxNameLen = 256;
    SYMBOL_INFO* pSymbol = (SYMBOL_INFO*)malloc(sizeof(SYMBOL_INFO) + maxNameLen * sizeof(char));
    if (!pSymbol)
    {
        return out.str();
    }

    pSymbol->MaxNameLen = maxNameLen - 1;
    pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    bool foundAppCode = false;

    out << "Stack trace:\n";
    for (unsigned short i = 0; i < frames; ++i)
    {
        SymFromAddr(process, (DWORD64)(stack[i]), 0, pSymbol);

        if (!foundAppCode)
        {
            const char exceptionDispatcherPrefix[] = "KiUser";
            if (strncmp(pSymbol->Name, exceptionDispatcherPrefix, sizeof(exceptionDispatcherPrefix) - 1) == 0)
            {
                foundAppCode = true;
            }

            continue;
        }

        const auto thisFrame = (frames - i - 1);
        snprintf(buf, sizeof(buf), "    %2i: %s - 0x%0llX\n", thisFrame, pSymbol->Name, pSymbol->Address);
        out << buf;
    }

    free(pSymbol);

    return out.str();
}

//------------------------------------------------------------------------------
// ProcessException
//------------------------------------------------------------------------------
static int ProcessException(unsigned int code, struct _EXCEPTION_POINTERS* /*ep*/)
{
    if (!Application::ShouldCatchAndReportSystemExceptions())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    g_exceptionReport = "\n";
    g_exceptionReport += GetStackTrace();

    char buf[128];
    const char* pExceptionString = GetExceptionString(code);
    if (pExceptionString)
    {
        snprintf(buf, sizeof(buf), "Exception Code: %s", pExceptionString);
    }
    else
    {
        // See ntstatus.h for the full status code list
        snprintf(buf, sizeof(buf), "Exception Code: 0x%X", code);
    }

    g_exceptionReport += "\n";
    g_exceptionReport += buf;

    return EXCEPTION_EXECUTE_HANDLER;
}

//------------------------------------------------------------------------------
// Win32Application
//------------------------------------------------------------------------------
Win32Application::Win32Application()
{
}

//------------------------------------------------------------------------------
// OutputMessage
//------------------------------------------------------------------------------
void Win32Application::OutputMessage(const std::string& message) const
{
#ifdef NV_WIN32_SUBSYSTEM
    if (!automated)
    {
        std::wstring wstr_message(message.begin(), message.end());
        MessageBox(NULL, wstr_message.c_str(), L"Nvda.Replayer", MB_ICONEXCLAMATION);
        return;
    }
#endif

    NV_MESSAGE(message.c_str());
}

//------------------------------------------------------------------------------
// ExecuteInternal
//------------------------------------------------------------------------------
int Win32Application::ExecuteInternal(int argc, char** argv)
{
    __try
    {
        return Application::ExecuteInternal(argc, argv);
    }
    __except (ProcessException(GetExceptionCode(), GetExceptionInformation()))
    {
        OnError(g_exceptionReport.c_str());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// ProcessMessages
//------------------------------------------------------------------------------
bool Win32Application::ProcessMessages()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        else
        {
            // Translate and dispatch the message
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return true;
}

//------------------------------------------------------------------------------
// PlatformInstance
//------------------------------------------------------------------------------
Application& Application::PlatformInstance()
{
    static Win32Application app;
    return app;
}
