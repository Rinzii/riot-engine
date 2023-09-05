// Copyright WizWorks, Inc. All Rights Reserved.

#pragma once

#include "riot/core/base/config/platform.h"

// clang-format off

#if RIOT_PLATFORM_WINDOWS

// Save these macros for later; Windows redefines them
#pragma push_macro("MAX_uint8")
#pragma push_macro("MAX_uint16")
#pragma push_macro("MAX_uint32")
#pragma push_macro("MAX_int32")
#pragma push_macro("TEXT")
#pragma push_macro("TRUE")
#pragma push_macro("FALSE")

// Undefine the TEXT macro for winnt.h to redefine it, unless it's already been included
#ifndef _WINNT_
#undef TEXT
#endif

#endif // RIOT_PLATFORM_WINDOWS
