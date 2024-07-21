//-----------------------------------------------------------------------------
// Generated with NVIDIA Nsight Graphics 2023.3.2.0
// 
// File: ReplayProcedures.cpp
// 
//-----------------------------------------------------------------------------

#include "ReplayProcedures.h"
#include "Application.h"
#include "Helpers.h"
#include "CommonReplay.h"
#include "Resources.h"
#include "Threading.h"

//-----------------------------------------------------------------------------
// Replay Procedures
//-----------------------------------------------------------------------------
extern void SetupWinResources();
extern void TerminateEventRanges();
extern void ResetWinResources(bool firstTime);
extern void RestoreEventRanges();
extern void SetInitialFrameState00();
extern void ResetInitialFrameState00(bool firstTime, bool isAsync);
extern void ResetState00();
extern void CreateResources00();
extern void CreateResources01();
extern void CreateResources02();
extern void OnBeforeWinResourcesInit00();
extern void CreateWinResources00();
extern void OnAfterWinResourcesInit00();
extern void ReleaseResources00();
extern void ReleaseWinResources00();
extern void OnAfterWinResourcesReleased00();

extern void RunFrame0Part00(uint64_t frameIndex);

//-----------------------------------------------------------------------------
// CreateAndSetupResources
//-----------------------------------------------------------------------------
void CreateAndSetupResources()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    InitializeDatabase();
    OnBeforeWinResourcesInit00();
    CreateWinResources00();
    OnAfterWinResourcesInit00();
    SetupWinResources();
    GetDatabase().SetForceEvict(true);
    CreateResources00();
    CreateResources01();
    CreateResources02();

    SetInitialFrameState00();
    GetDatabase().SetForceEvict(false);
}

//-----------------------------------------------------------------------------
// ReleaseResources
//-----------------------------------------------------------------------------
void ReleaseResources()
{
    BEGIN_DATA_SCOPE_FUNCTION();

    ReleaseResources00();
    ReleaseWinResources00();
    OnAfterWinResourcesReleased00();
}

//-----------------------------------------------------------------------------
// RunFrame
//-----------------------------------------------------------------------------
void RunFrame(uint64_t frameIndex)
{
    BEGIN_DATA_SCOPE_FUNCTION();

    if (frameIndex == 0)
    {
        BEGIN_DATA_SCOPE();

        NV_MESSAGE_VERBOSE("Start rendering...");
        Application::SetAsyncDataResetter([]() -> void {

            ResetInitialFrameState00(false, true);
        });
        Application::SetFrameExecutor([](uint64_t frameIndex) -> bool {

            BEGIN_DATA_SCOPE_FUNCTION();

            RestoreEventRanges();
            RunFrame0Part00(frameIndex);
            TerminateEventRanges();
            ResetState00();
            if (hasFrameReset)
            {
                BEGIN_DATA_SCOPE();

                ResetWinResources(false);
                ResetInitialFrameState00(frameIndex == 0, false);
            }

            return true;
        });
    }

    Application::ExecuteFrame(frameIndex);
}
