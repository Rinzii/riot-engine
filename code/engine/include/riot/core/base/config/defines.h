// Copyright (c) 2023-present Genesis Engine contributors (see LICENSE.txt)

#pragma once

// clang-format off

#ifndef RIOT_TRUE
	#define RIOT_TRUE 1
#endif

#ifndef RIOT_FALSE
	#define RIOT_FALSE 0
#endif


#ifndef RIOT_IMPORT
	#if defined(RIOT_COMPILER_MSVC)
		#define RIOT_IMPORT __declspec(dllimport)
	#elif defined(RIOT_COMPILER_GNUC) || defined(RIOT_COMPILER_CLANG)
		#define RIOT_IMPORT __attribute__((visibility("default")))
	#else
		#define RIOT_IMPORT
	#endif
#endif


#ifndef RIOT_EXPORT
	#if defined(_MSC_VER)
		#define RIOT_EXPORT __declspec(dllexport)
	#elif defined(__GNUC__) || defined(__clang__)
		#define RIOT_EXPORT __attribute__((visibility("default")))
	#else
		#define RIOT_EXPORT
	#endif
#endif


// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER
	#pragma warning(disable : 4251)
#endif


// Define portable import / export macros
#if defined(RIOT_DLL)
	#if defined(RIOT_DLL_EXPORT)
		#define RIOT_API RIOT_EXPORT
	#else
		#define RIOT_API RIOT_IMPORT
	#endif
#else
	#define RIOT_API
#endif


// Portable debug macro - this should be defined in cmake but just in case double check
#if !defined(NDEBUG) || !defined(RIOT_NDEBUG)
	#if !defined(RIOT_DEBUG)
		#define RIOT_DEBUG
	#endif
#endif


namespace riot
{
    constexpr bool debug_v =
#if defined(RIOT_DEBUG)
	    true;
#else
	    false;
#endif

    constexpr bool freetype_v =
#if defined(RIOT_USE_FREETYPE)
	    true;
#else
	    false;
#endif
} // namespace riot
