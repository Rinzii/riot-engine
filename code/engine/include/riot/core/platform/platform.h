#pragma once

#include "riot/core/base/config/platform.h"

#if RIOT_PLATFORM_WINDOWS

#elif RIOT_PLATFORM_LINUX

#elif RIOT_PLATFORM_OSX

#elif RIOT_PLATFORM_ANDROID

#elif RIOT_PLATFORM_IPHONE

#elif RIOT_PLATFORM_DURANGO

#elif RIOT_PLATFORM_ORBIS

#else

#endif

namespace riot
{
    enum class Platform
    {
        eWindows,
        eLinux,
        eMacOS,
        eAndroid,
        eiOS,
        eXboxOne,
        ePS4,
        eUnknown,

#if defined(RIOT_PLATFORM_WINDOWS)
        Current = Platform::eWindows,
#elif defined(RIOT_PLATFORM_LINUX)
        Current = Platform::eLinux,
#elif defined(RIOT_PLATFORM_OSX)
        Current = Platform::eMacOS,
#elif defined(RIOT_PLATFORM_ANDROID)
        Current = Platform::eAndroid,
#elif defined(RIOT_PLATFORM_IPHONE)
        Current = Platform::eiOS,
#elif defined(RIOT_PLATFORM_XBOXONE)
        Current = Platform::eXboxOne,
#elif defined(RIOT_PLATFORM_PS4)
        Current = Platform::ePS4,
#else
        Current = Platform::eUnknown,
#endif
    };

    enum class QuestionResult
    {
        eQR_None,
        eQR_Cancel,
        eQR_Yes,
        eQR_No,
        eQR_Abort,
        eQR_Retry,
        eQR_Ignore
    };

    enum class MessageBox
    {
        eMB_Info,
        eMB_YesCancel,
        eMB_YesNoCancel,
        eMB_Error,
        eMB_AbortRetryIgnore
    };

    bool RiotInitializeEngine(struct SystemInitParams& startupParams, bool bManualEngineLoop = false);

}

