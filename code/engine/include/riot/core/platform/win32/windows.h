// Copyright WizWorks, Inc. All Rights Reserved.

#pragma once

#include "riot/core/base/config/platform.h"

// clang-format off

#if RIOT_PLATFORM_WINDOWS

#include "riot/platform/win32/internal/preWinapi.hpp"

// We enable STRICT mode to avoid some type conversions in the Win32 API
// https://learn.microsoft.com/en-us/windows/win32/winprog/enabling-strict
#ifndef STRICT
#define STRICT
#endif

#include "riot/platform/win32/internal/minWindows.hpp"
#include "riot/platform/win32/internal/postWinapi.hpp"

#endif // RIOT_PLATFORM_WINDOWS

// clang-format on
