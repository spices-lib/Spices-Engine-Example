//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: Main.cpp
// 
//-----------------------------------------------------------------------------

// Defines the entry point that initializes and runs the serialized frame capture

#include "Application.h"
#if __linux__
#include <pthread.h>
#endif

extern const char* ProcessName;

#ifdef NV_WIN32_SUBSYSTEM

#include <windows.h>

extern HINSTANCE currentInstance;

//-----------------------------------------------------------------------------
// WinMain
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    currentInstance = hInstance;

    return Application::PlatformInstance().Execute(__argc, __argv);
}

#else

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
#if _PTHREAD_H
    pthread_setname_np(pthread_self(), ProcessName);
#endif
    return Application::PlatformInstance().Execute(argc, argv);
}

#endif


