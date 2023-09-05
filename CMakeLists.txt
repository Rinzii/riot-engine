cmake_minimum_required(VERSION 3.18 FATAL_ERROR) # 3.18 required for extracting zip files.

if (NOT DEFINED RIOTENGINE_ROOT_DIR)
  set(RIOTENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
endif ()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")


project(riot VERSION "0.0.1")


# Include cmake modules
include(cmake/InitialSetup.cmake)
include(cmake/Config.cmake)


set(is_root_project OFF)
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(is_root_project ON)
endif()


# Establish core project options
option(RIOT_BUILD_EDITOR "Build the riot editor (else only library)" ON)
option(RIOT_BUILD_LAUNCHER "Build the riot launcher" ON)
option(RIOT_BUILD_SHADERS "Build the riot shaders" ON)
option(RIOT_BUILD_TOOLS "Build riot tools" ON)
option(RIOT_AUTOFORMAT "Run code-formatter before building riot" ON)


# Validate options
if (RIOT_BUILD_EDITOR)
  if (NOT RIOT_BUILD_LAUNCHER)
    message(FATAL_ERROR "RIOT_BUILD_EDITOR requires RIOT_BUILD_LAUNCHER")
  endif ()

  if (NOT RIOT_BUILD_SHADERS)
    # TODO: This may not actually be required in the near future.
    message(STATUS "RIOT_BUILD_EDITOR requires RIOT_BUILD_SHADERS. Enabling RIOT_BUILD_SHADERS!")
    set(GENESIS_BUILD_SHADERS ON CACHE BOOL "Launcher requires the shaders" FORCE)
  endif ()
endif ()

if(NOT RIOT_BUILD_TOOLS AND RIOT_AUTOFORMAT)
  message(FATAL_ERROR "Cannot enable RIOT_AUTOFORMAT without RIOT_BUILD_TOOLS")
endif()


# Add subdirectories
add_subdirectory(tools) # This must be added first. As it provides many runtime tools required by the engine.
add_subdirectory(code)
#add_subdirectory(engine)
#add_subdirectory(editor)




