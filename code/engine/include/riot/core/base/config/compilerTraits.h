// Copyright (c) 2023-present Genesis Engine contributors (see LICENSE.txt)

#pragma once

// Use this for reference: https://en.cppreference.com/w/cpp/compiler_support

#include "compiler.h"


// https://learn.microsoft.com/en-us/cpp/intrinsics/compiler-intrinsics?view=msvc-170
// https://clang.llvm.org/docs/LanguageExtensions.html
// https://gcc.gnu.org/onlinedocs/gcc-4.8.5/gcc/X86-Built-in-Functions.html

// ------------------------------------------------------------------------
// RIOT_STRINGIFY
//
// Example usage:
//     printf("Line: %s", RIOT_STRINGIFY(__LINE__));
//
#ifndef RIOT_STRINGIFY
#define RIOT_STRINGIFY(x) RIOT_STRINGIFY_IMPL(x)
#define RIOT_STRINGIFY_IMPL(x) #x
#endif

// https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html
// https://clang.llvm.org/docs/UsersManual.html#controlling-diagnostics-via-pragmas
#ifndef RIOT_WARNING
#if defined(RIOT_COMPILER_CLANG) || defined(RIOT_COMPILER_GCC)
#define RIOT_WARNING(msg) _Pragma(RIOT_STRINGIFY(GCC warning msg)
#else
#define RIOT_WARNING(msg)
#endif
#endif

#ifndef RIOT_FORCE_INLINE
#ifndef RIOT_DISABLE_FORCED_INLINING
#if defined(RIOT_COMPILER_MSVC)
#define RIOT_FORCE_INLINE __forceinline
#elif defined(RIOT_COMPILER_GCC) && (((__GNUC__ * 100) + __GNUC_MINOR__) >= 301) || defined(RIOT_COMPILER_CLANG)
#if defined(__cplusplus)
#define RIOT_FORCE_INLINE inline __attribute__((always_inline))
#else
#define RIOT_FORCE_INLINE __inline__ __attribute__((always_inline))
#endif
#else
#if defined(__cplusplus)
#define RIOT_FORCE_INLINE inline
#else
#define RIOT_FORCE_INLINE __inline
#endif
#endif
#else // If RIOT_DISABLE_FORCED_INLINING is defined then don't force inlining
#if defined(__cplusplus)
			#define RIOT_FORCE_INLINE inline
		#else
			#define RIOT_FORCE_INLINE __inline
		#endif
#endif
#endif

#ifndef RIOT_NOINLINE
#if defined(RIOT_COMPILER_MSVC)
#define RIOT_NOINLINE __declspec(noinline)
#elif defined(RIOT_COMPILER_GCC) || defined(RIOT_COMPILER_CLANG)
#define RIOT_NOINLINE __attribute__((noinline))
#else
#define RIOT_NOINLINE
#endif
#endif

#ifndef RIOT_DEPRECATED
#define RIOT_DEPRECATED [[deprecated]]
#endif

#ifndef RIOT_DEPRECATED_MESSAGE
#define RIOT_DEPRECATED_MESSAGE(message) [[deprecated(message)]]
#endif

#ifndef RIOT_NODISCARD
    #if defined(RIOT_COMPILER_CPP17_ENABLED)
        #define RIOT_NODISCARD [[nodiscard]]
    #else
        #if defined(RIOT_COMPILER_MSVC)
            #include <sal.h>
			#define RIOT_NODISCARD __checkReturn
        #elif defined(RIOT_COMPILER_GCC) || defined(RIOT_COMPILER_CLANG)
			#define RIOT_NODISCARD __attribute__((warn_unused_result))
        #else
            #define RIOT_NODISCARD
        #endif
    #endif
#endif

#ifndef RIOT_NODISCARD_MESSAGE
#if defined(RIOT_COMPILER_CPP20_ENABLED)
#define RIOT_NODISCARD_MESSAGE(message) [[nodiscard(message)]]
#else
#define RIOT_NODISCARD_MESSAGE(message) RIOT_NODISCARD
#endif
#endif

#ifndef RIOT_FALLTHROUGH
#if defined(RIOT_COMPILER_CPP17_ENABLED)
#define RIOT_FALLTHROUGH [[fallthrough]]
#elif defined(RIOT_COMPILER_GCC) || defined(RIOT_COMPILER_CLANG)
#define RIOT_FALLTHROUGH __attribute__((fallthrough))
#elif defined(RIOT_COMPILER_MSVC)
#define RIOT_FALLTHROUGH __fallthrough
#else
#define RIOT_FALLTHROUGH
#endif
#endif

#ifndef RIOT_MAYBEUNUSED
#if defined(RIOT_COMPILER_CPP17_ENABLED)
#define RIOT_MAYBEUNUSED [[maybe_unused]]
#elif defined(RIOT_COMPILER_GCC) || defined(RIOT_COMPILER_CLANG)
#define RIOT_MAYBEUNUSED __attribute__((unused))
#else
#define RIOT_MAYBEUNUSED
#endif
#endif

#ifndef RIOT_ASSUME
#if defined(RIOT_COMPILER_CPP23_ENABLED)// This is a dummy define for when c++23 is finalized.
#define RIOT_ASSUME(expr) [[assume(expr)]]
#elif defined(RIOT_COMPILER_GCC) && (__GNUC__ >= 13) // Currently only GCC supports assume
#define RIOT_ASSUME(expr) [[assume(expr)]]
#elif defined(RIOT_COMPILER_MSVC)
#define RIOT_ASSUME(expr) __assume(expr)
#elif defined(RIOT_COMPILER_CLANG) && (__clang_major__ >= 4)
#define RIOT_ASSUME(expr) __builtin_assume(expr)
#elif defined(RIOT_COMPILER_GCC) && ((__GNUC__ >= 12) && (__GNUC_MINOR__ >= 1))
#define RIOT_ASSUME(expr) __attribute__((assume(expr)))
#else
#define RIOT_ASSUME(expr)
#endif
#endif

#ifndef RIOT_LIKELY
#if defined(RIOT_COMPILER_CPP20_ENABLED)
#define RIOT_LIKELY [[likely]]
#else
#define RIOT_LIKELY
#endif
#endif

#ifndef RIOT_LIKELY_EXPR
#if defined(RIOT_COMPILER_GCC) || defined(RIOT_COMPILER_CLANG)
#define RIOT_LIKELY_EXPR(expr) __builtin_expect(!!(expr), 1)
#else
#define RIOT_LIKELY_EXPR(expr) (expr)
#endif
#endif



#if defined(RIOT_COMPILER_MSVC)
#define RIOT_PRAGMA(x) __pragma(x)
#else
#define RIOT_PRAGMA(x) _Pragma(#x)
#endif

// ------------------------------------------------------------------------
// RIOT_DISABLE_GCC_WARNING / RIOT_RESTORE_GCC_WARNING
//
// Example usage:
//     // Only one warning can be ignored per statement, due to how GCC works.
//     RIOT_DISABLE_GCC_WARNING(-Wuninitialized)
//     RIOT_DISABLE_GCC_WARNING(-Wunused)
//     <code>
//     RIOT_RESTORE_GCC_WARNING()
//     RIOT_RESTORE_GCC_WARNING()
//
#ifndef RIOT_DISABLE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC)
#define RIOT_GCCWHELP0(x) #x
#define RIOT_GCCWHELP1(x) RIOT_GCCWHELP0(GCC diagnostic ignored x)
#define RIOT_GCCWHELP2(x) RIOT_GCCWHELP1(#x)
#endif

#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4006) // Can't test directly for __GNUC__ because some compilers lie.
#define RIOT_DISABLE_GCC_WARNING(w) _Pragma("GCC diagnostic push") _Pragma(RIOT_GCCWHELP2(w))
#else
#define RIOT_DISABLE_GCC_WARNING(w)
#endif
#endif

#ifndef RIOT_RESTORE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4006)
#define RIOT_RESTORE_GCC_WARNING() _Pragma("GCC diagnostic pop")
#else
#define RIOT_RESTORE_GCC_WARNING()
#endif
#endif

// ------------------------------------------------------------------------
// RIOT_ENABLE_GCC_WARNING_AS_ERROR / RIOT_DISABLE_GCC_WARNING_AS_ERROR
//
// Example usage:
//     // Only one warning can be treated as an error per statement, due to how GCC works.
//     RIOT_ENABLE_GCC_WARNING_AS_ERROR(-Wuninitialized)
//     RIOT_ENABLE_GCC_WARNING_AS_ERROR(-Wunused)
//     <code>
//     RIOT_DISABLE_GCC_WARNING_AS_ERROR()
//     RIOT_DISABLE_GCC_WARNING_AS_ERROR()
//
#ifndef RIOT_ENABLE_GCC_WARNING_AS_ERROR
#if defined(RIOT_COMPILER_GNUC)
#define RIOT_GCCWERRORHELP0(x) #x
#define RIOT_GCCWERRORHELP1(x) RIOT_GCCWERRORHELP0(GCC diagnostic error x)
#define RIOT_GCCWERRORHELP2(x) RIOT_GCCWERRORHELP1(#x)
#endif
#endif

#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4006) // Can't test directly for __GNUC__ because some compilers lie.
#define RIOT_ENABLE_GCC_WARNING_AS_ERROR(w) _Pragma("GCC diagnostic push") _Pragma(RIOT_GCCWERRORHELP2(w))
#else
#define RIOT_ENABLE_GCC_WARNING_AS_ERROR(w)
#endif

#ifndef RIOT_DISABLE_GCC_WARNING_AS_ERROR
#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4006)
#define RIOT_DISABLE_GCC_WARNING_AS_ERROR() _Pragma("GCC diagnostic pop")
#else
#define RIOT_DISABLE_GCC_WARNING_AS_ERROR()
#endif
#endif

#ifndef RIOT_ENABLE_IGNORE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC)
#define RIOT_GCCIGNOREHELP0(x) #x
#define RIOT_GCCIGNOREHELP1(x) RIOT_GCCIGNOREHELP0(GCC diagnostic ignored x)
#define RIOT_GCCIGNOREHELP2(x) RIOT_GCCIGNOREHELP1(#x)
#endif
#endif

#ifndef RIOT_ENABLE_IGNORE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4006) // Can't test directly for __GNUC__ because some compilers lie.
#define RIOT_ENABLE_IGNORE_GCC_WARNING(w) _Pragma("GCC diagnostic push") _Pragma(RIOT_GCCIGNOREHELP2(w))
#else
#define RIOT_ENABLE_IGNORE_GCC_WARNING(w)
#endif
#endif

#ifndef RIOT_DISABLE_IGNORE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC)
#define RIOT_GCCIGNOREDISABLEHELP0(x) #x
#define RIOT_GCCIGNOREDISABLEHELP1(x) RIOT_GCCIGNOREDISABLEHELP0(GCC diagnostic warning x)
#define RIOT_GCCIGNOREDISABLEHELP2(x) RIOT_GCCIGNOREDISABLEHELP1(#x)
#endif
#endif

#ifndef RIOT_DISABLE_IGNORE_GCC_WARNING
#if defined(RIOT_COMPILER_GNUC) && (RIOT_COMPILER_VERSION >= 4004)
#define RIOT_DISABLE_IGNORE_GCC_WARNING(w) _Pragma(RIOT_GCCIGNOREDISABLEHELP2(w)) _Pragma("GCC diagnostic pop")
#else
#define RIOT_DISABLE_IGNORE_GCC_WARNING(w)
#endif
#endif

// ------------------------------------------------------------------------
// RIOT_DISABLE_CLANG_WARNING / RIOT_RESTORE_CLANG_WARNING
//
// Example usage:
//     // Only one warning can be ignored per statement, due to how clang works.
//     RIOT_DISABLE_CLANG_WARNING(-Wuninitialized)
//     RIOT_DISABLE_CLANG_WARNING(-Wunused)
//     <code>
//     RIOT_RESTORE_CLANG_WARNING()
//     RIOT_RESTORE_CLANG_WARNING()
//
#ifndef RIOT_DISABLE_CLANG_WARNING
#if defined(RIOT_COMPILER_CLANG) || defined(RIOT_COMPILER_CLANG_CL)
#define RIOT_CLANGWHELP0(x) #x
		#define RIOT_CLANGWHELP1(x) RIOT_CLANGWHELP0(clang diagnostic ignored x)
		#define RIOT_CLANGWHELP2(x) RIOT_CLANGWHELP1(#x)

		#define RIOT_DISABLE_CLANG_WARNING(w) _Pragma("clang diagnostic push") _Pragma(RIOT_CLANGWHELP2(-Wunknown-warning-option)) _Pragma(RIOT_CLANGWHELP2(w))
#else
#define RIOT_DISABLE_CLANG_WARNING(w)
#endif
#endif

#ifndef RIOT_RESTORE_CLANG_WARNING
#if defined(RIOT_COMPILER_CLANG) || defined(RIOT_COMPILER_CLANG_CL)
#define RIOT_RESTORE_CLANG_WARNING() _Pragma("clang diagnostic pop")
#else
#define RIOT_RESTORE_CLANG_WARNING()
#endif
#endif

// ------------------------------------------------------------------------
// RIOT_ENABLE_CLANG_WARNING_AS_ERROR / RIOT_DISABLE_CLANG_WARNING_AS_ERROR
//
// Example usage:
//     // Only one warning can be treated as an error per statement, due to how clang works.
//     RIOT_ENABLE_CLANG_WARNING_AS_ERROR(-Wuninitialized)
//     RIOT_ENABLE_CLANG_WARNING_AS_ERROR(-Wunused)
//     <code>
//     RIOT_DISABLE_CLANG_WARNING_AS_ERROR()
//     RIOT_DISABLE_CLANG_WARNING_AS_ERROR()
//
#ifndef RIOT_ENABLE_CLANG_WARNING_AS_ERROR
#if defined(RIOT_COMPILER_CLANG) || defined(RIOT_COMPILER_CLANG_CL)
#define RIOT_CLANGWERRORHELP0(x) #x
		#define RIOT_CLANGWERRORHELP1(x) RIOT_CLANGWERRORHELP0(clang diagnostic error x)
		#define RIOT_CLANGWERRORHELP2(x) RIOT_CLANGWERRORHELP1(#x)

		#define RIOT_ENABLE_CLANG_WARNING_AS_ERROR(w) _Pragma("clang diagnostic push") _Pragma(RIOT_CLANGWERRORHELP2(w))
#else
#define RIOT_DISABLE_CLANG_WARNING(w)
#endif
#endif

#ifndef RIOT_DISABLE_CLANG_WARNING_AS_ERROR
#if defined(RIOT_COMPILER_CLANG) || defined(RIOT_COMPILER_CLANG_CL)
#define RIOT_DISABLE_CLANG_WARNING_AS_ERROR() _Pragma("clang diagnostic pop")
#else
#define RIOT_DISABLE_CLANG_WARNING_AS_ERROR()
#endif
#endif
