// Copyright (c) 2023-present Genesis Engine contributors (see LICENSE.txt)

#pragma once

// Reference for all preprocessor macros used here
// https://sourceforge.net/p/predef/wiki/Architectures/
// https://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html
// https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
// https://www.intel.com/content/www/us/en/docs/cpp-compiler/developer-guide-reference/2021-8/additional-predefined-macros.html
// https://developer.arm.com/documentation/dui0491/latest/Compiler-specific-Features/Predefined-macros

/// Identify what processor architecture we are compiling for.

/// x86 Architecture
// VS defines: _M_IX86
// GCC defines: i386, __i386, __i386__
#if defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
	#define RIOT_ARCH_X86

/// x86_64 Architecture
// VS defines: _M_X64 and _M_AMD64
// GCC defines: __amd64__, __amd64, __x86_64__, and __x86_64
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
	#define RIOT_ARCH_X64

/// ARM Architecture
// VS defines: _M_ARM
// GCC defines: __arm__
#elif defined(_M_ARM) || defined(__arm__)
	#define RIOT_ARCH_ARM

/// ARM64 Architecture
// VS defines: _M_ARM64
// GCC defines: __aarch64__
#elif defined(_M_ARM64) || defined(__aarch64__)
	#define RIOT_ARCH_ARM64

#else
	#error "Unknown architecture"
#endif


// RIOT_MISALIGNED_SUPPORT_LEVEL
// Specifies if the processor can read and write built-in types that aren't
// naturally aligned.
//    0 - not supported. Likely causes an exception.
//    1 - supported but slow.
//    2 - supported and fast.
//
#ifndef RIOT_MISALIGNED_SUPPORT_LEVEL
#if defined(RIOT_ARCH_X64)
#define RIOT_MISALIGNED_SUPPORT_LEVEL 2
#else
#define RIOT_MISALIGNED_SUPPORT_LEVEL 0
#endif
#endif

// NOTE: Mirrored from riot/core/base/config/platform.h
// NOTE: This is being mirrored to avoid requiring the entire platform.h file to be included.

#ifndef RIOT_PLATFORM_PTR_SIZE
#if defined(__WORDSIZE) // Defined by some variations of GCC.
#define RIOT_PLATFORM_PTR_SIZE ((__WORDSIZE) / 8)
#elif defined(_WIN64) || defined(__LP64__) || defined(_LP64) || defined(_M_IA64) || defined(__ia64__) || defined(__arch64__) || defined(__aarch64__) || defined(__mips64__) || defined(__64BIT__) || defined(__Ptr_Is_64)
#define RIOT_PLATFORM_PTR_SIZE 8
#elif defined(__CC_ARM) && (__sizeof_ptr == 8)
#define RIOT_PLATFORM_PTR_SIZE 8
	#else
		#define RIOT_PLATFORM_PTR_SIZE 4
#endif
#endif

#ifndef RIOT_PLATFORM_WORD_SIZE
#define RIOT_PLATFORM_WORD_SIZE RIOT_PLATFORM_PTR_SIZE
#endif

// RIOT_CACHE_LINE_SIZE
// Specifies the cache line size broken down by compile target.
// This the expected best guess values for the targets that we can make at compilation time.

#ifndef RIOT_CACHE_LINE_SIZE
#if   defined(RIOT_ARCH_X86)
#define RIOT_CACHE_LINE_SIZE 32    // This is the minimum possible value.
#elif defined(RIOT_ARCH_X64)
#define RIOT_CACHE_LINE_SIZE 64    // This is the minimum possible value
#elif defined(RIOT_ARCH_ARM)
#define RIOT_CACHE_LINE_SIZE 32    // This varies between implementations and is usually 32 or 64.
#elif defined(RIOT_ARCH_ARM64)
#define RIOT_CACHE_LINE_SIZE 64    // Cache line Cortex-A8  (64 bytes) http://shervinemami.info/armAssembly.html however this remains to be mostly an assumption at this stage
#elif (RIOT_PLATFORM_WORD_SIZE == 4)
#define RIOT_CACHE_LINE_SIZE 32    // This is the minimum possible value
#else
#define RIOT_CACHE_LINE_SIZE 64    // This is the minimum possible value
#endif
#endif



// TODO: This could prob be made much better but for now it will work.

// Currently we allow simd to be enabled by cmake which creates a preprocessor macro.
// This macro is then used to identify if we should enable simd instructions. Then internally identify
// what simd instructions are available. If none are available then we remove the RIOT_SIMD macro if it exists.

// There may be better ways to handle this, and it can be argued that having CMake create a preprocessor macro is
// not the best way to handle this case, but for the time being this will be a simple solution. Though it may change later.

#if defined(INTERNAL_RIOT_SIMD_ENABLE)

	// Identify if we are allowing simd instructions.
	#if defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
		#define RIOT_SIMD_SSE 1
	#endif

	#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
		#define RIOT_SIMD_SSE2 1
	#endif

	#if defined(__SSE3__)
		#define RIOT_SIMD_SSE3 1
	#endif

	#if defined(__SSSE3__)
		#define RIOT_SIMD_SSSE3 1
	#endif

	#if defined(__SSE4_1__)
		#define RIOT_SIMD_SSE4_1 1
	#endif

	#if defined(__SSE4_2__)
		#define RIOT_SIMD_SSE4_2 1
	#endif

	#if defined(__AVX__)
		#define RIOT_SIMD_AVX 1
	#endif

	#if defined(__AVX2__)
		#define RIOT_SIMD_AVX2 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Byte and Word instructions.
	#if defined(__AVX512BW__)
		#define RIOT_SIMD_AVX512BW 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Conflict Detection instructions.
	#if defined(__AVX512CD__)
		#define RIOT_SIMD_AVX512CD 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Doubleword and Quadword instructions.
	#if defined(__AVX512DQ__)
		#define RIOT_SIMD_AVX512DQ 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Exponential and Reciprocal instructions.
	#if defined(__AVX512ER__)
		#define RIOT_SIMD_AVX512ER 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Foundation instructions.
	#if defined(__AVX512F__)
		#define RIOT_SIMD_AVX512F 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Prefetch instructions.
	#if defined(__AVX512PF__)
		#define RIOT_SIMD_AVX512PF 1
	#endif

	// Processors that support Intel Advanced Vector Extensions 512 (Intel AVX-512) Vector Length extensions.
	#if defined(__AVX512VL__)
		#define RIOT_SIMD_AVX512VL 1
	#endif

	#if defined(__ARM_NEON) || defined(__ARM_NEON__)
		#define RIOT_SIMD_NEON 1
	#endif

	// If we have any simd instructions, then we define RIOT_SIMD so that we can use it in our code.
	#if defined(RIOT_SIMD_SSE) || defined(RIOT_SIMD_SSE2) || defined(RIOT_SIMD_SSE3) || defined(RIOT_SIMD_SSSE3) || defined(RIOT_SIMD_SSE4_1) ||                    \
		defined(RIOT_SIMD_SSE4_2) || defined(RIOT_SIMD_AVX) || defined(RIOT_SIMD_AVX2) || defined(RIOT_SIMD_AVX512BW) || defined(RIOT_SIMD_AVX512CD) ||             \
		defined(RIOT_SIMD_AVX512DQ) || defined(RIOT_SIMD_AVX512ER) || defined(RIOT_SIMD_AVX512F) || defined(RIOT_SIMD_AVX512PF) || defined(RIOT_SIMD_AVX512VL) ||   \
		defined(RIOT_SIMD_NEON)
		#ifdef RIOT_SIMD
			#undef RIOT_SIMD
		#endif
		#define RIOT_SIMD 1
	#else
		#error "RIOT_SIMD defined but no valid simd instruction sets detected"
	#endif

#endif // defined(RIOT_SIMD)
