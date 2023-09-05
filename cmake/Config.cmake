# detect our OS
# TODO: Figure out how to detect if we're on the switch or not.
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    if(XBOX_CONSOLE_TARGET MATCHES "scarlett" OR XBOX_CONSOLE_TARGET MATCHES "xboxone") # TODO: This may not work. Verify once I have access to xbox docs.
        set(RIOT_OS_XBOX 1)
    else()
        set(RIOT_OS_WINDOWS 1)
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(RIOT_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(RIOT_OS_MACOS 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
    set(RIOT_OS_IOS 1)
    # As we want to find packages in our bin folder too
    # we need to tell CMake we want to search there instead
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(RIOT_OS_ANDROID 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "^Orbis$") # TODO: This may not work. Verify once I have access to ps4 docs.
    set(RIOT_OS_PSX 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^k?FreeBSD$")
    set(RIOT_OS_FREEBSD 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^OpenBSD$")
    set(RIOT_OS_OPENBSD 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^NetBSD$")
    set(RIOT_OS_NETBSD 1)
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()


# detect the compiler
# Note: The detection order is important because:
# - Visual Studio can both use MSVC and Clang
# - GNUCXX can still be set on macOS when using Clang
if(MSVC)
    set(RIOT_COMPILER_MSVC 1)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(RIOT_COMPILER_CLANG_CL 1)
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(RIOT_COMPILER_CLANG 1)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(RIOT_COMPILER_GCC 1)

    execute_process(COMMAND "${CMAKE_CXX_COMPILER}" "--version" OUTPUT_VARIABLE GCC_COMPILER_VERSION)
    string(REGEX MATCHALL ".*(tdm[64]*-[1-9]).*" RIOT_COMPILER_GCC_TDM "${GCC_COMPILER_VERSION}")
else()
    message(FATAL_ERROR "Unsupported compiler")
    return()
endif()


# detect the architecture (note: this test won't work for cross-compilation)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(RIOT_ARCH_X64 1)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(RIOT_ARCH_X86 1)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^armv7")
    set(RIOT_ARCH_ARM 1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^aarch64")
    set(RIOT_ARCH_ARM64 1)
else()
    message(FATAL_ERROR "Unsupported architecture")
    return()
endif()


message(STATUS "Detected Operating system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Detected Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Detected Architecture: ${CMAKE_SYSTEM_PROCESSOR}")

