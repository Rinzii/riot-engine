// Copyright (c) 2023-present Genesis Engine contributors (see LICENSE.txt)

#pragma once

/*
 * Currently supported defines include:
 *      RIOT_COMPILER_MSVC
 *      RIOT_COMPILER_GCC
 *      RIOT_COMPILER_CLANG
 *      RIOT_COMPILER_CLANG_CL
 *
 *      RIOT_COMPILER_VERSION = <integer>
 *      RIOT_COMPILER_NAME = <string>
 *      RIOT_COMPILER_STRING = <string>
 */

// Note: This is used to generate the RIOT_COMPILER_STRING macros
#ifndef INTERNAL_STRINGIFY
	#define INTERNAL_STRINGIFY(x) INTERNAL_PRIMITIVE_STRINGIFY(x)
#endif
#ifndef INTERNAL_PRIMITIVE_STRINGIFY
	#define INTERNAL_PRIMITIVE_STRINGIFY(x) #x
#endif

/// RIOT_COMPILER_CPP17_ENABLED
#if !defined(RIOT_COMPILER_CPP17_ENABLED) && defined(__cplusplus)
	#if (__cplusplus >= 201703L)
		#define RIOT_COMPILER_CPP17_ENABLED 1
	#elif defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L) // C++17+
		#define RIOT_COMPILER_CPP17_ENABLED 1
	#endif
#endif

/// RIOT_COMPILER_CPP20_ENABLED
// This check could have some issues with some compilers as a few have decided not to
// define __cplusplus correctly until they are fully supporting C++20, but this should
// not matter to use for our purposes.
#if !defined(RIOT_COMPILER_CPP20_ENABLED) && defined(__cplusplus)
	#if (__cplusplus >= 202002L)
		#define RIOT_COMPILER_CPP20_ENABLED 1
	#elif defined(_MSVC_LANG) && (_MSVC_LANG >= 202002L) // C++20+
		#define RIOT_COMPILER_CPP20_ENABLED 1
	#endif
#endif

// Clang's GCC-compatible driver.
#if defined(__clang__) && !defined(_MSC_VER)
	#define RIOT_COMPILER_CLANG	 1
	#define RIOT_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
	#define RIOT_COMPILER_NAME	 "clang"
	#define RIOT_COMPILER_STRING	 RIOT_COMPILER_NAME __clang_version__

// GCC (a.k.a. GNUC)
#elif defined(__GNUC__)
	// Define interchangeably between GCC and GNUC. Though RIOT_COMPILER_GCC is preferred.
	#define RIOT_COMPILER_GCC	 1
	#define RIOT_COMPILER_GNUC	 1
	#define RIOT_COMPILER_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
	#define RIOT_COMPILER_NAME	 "GCC"
	#define RIOT_COMPILER_STRING	 RIOT_COMPILER_NAME " compiler, version " INTERNAL_STRINGIFY(__GNUC__) "." INTERNAL_STRINGIFY(__GNUC_MINOR__)

#elif defined(_MSC_VER) // TODO: Validate everything is properly being set for MSVC
	#define RIOT_COMPILER_MSVC	   1
	#define RIOT_COMPILER_MICROSOFT 1
	#define RIOT_COMPILER_VERSION   _MSC_VER
	#define RIOT_COMPILER_NAME	   "Microsoft Visual C++"
	#define RIOT_COMPILER_STRING	   RIOT_COMPILER_NAME " compiler, version " INTERNAL_STRINGIFY(_MSC_VER)

	#if defined(__clang__)
		// Clang's MSVC-compatible driver.
		#define RIOT_COMPILER_CLANG_CL 1
	#endif

#endif
