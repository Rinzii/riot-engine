include(CMakeDependentOption)

option(RIOT_PCH "Use pre-compiled headers for the riot Engine" ON)
option(RIOT_ENABLE_SIMD "Enable SIMD for riot" OFF)


add_library(riot)
add_library(riot::lib ALIAS riot)

target_compile_definitions(riot
        PUBLIC
        $<$<CONFIG:Debug>:RIOT_DEBUG>
        $<$<CONFIG:RelWithDebInfo>:RIOT_DEBUG>
        $<$<CONFIG:Release>:RIOT_NDEBUG>
        $<$<CONFIG:Release>:RIOT_RELEASE>
        )

if (RIOT_ENABLE_SIMD)
  # This create an internal definition that allows our project to check if it can use simd.
  # If the code decides it can then GEN_SIMD will be defined along with a bunch of other SIMD related defines.
  # This definition is only used once to to allow GEN_SIMD to figure out if it can be enabled and nowhere else.
  add_compile_definitions(INTERNAL_RIOT_SIMD_ENABLE)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  # Make MSVC shut up about not actually deprecated functions
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()


# COMPILER FLAGS
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(riot PRIVATE
          -Wall -Wextra -Wpedantic -Wconversion
          )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  target_compile_options(riot PRIVATE
          /W4 /WX
          )
endif()

# COMPILE FEATURES
target_compile_features(riot PUBLIC cxx_std_17)

# LINK LIBRARIES
target_link_libraries(riot
        PUBLIC
        mim::mim
        imgui::imgui
        SDL2::SDL2

        PRIVATE
        riot::ext
        )

# Setup our include structure
target_include_directories(riot
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE src
        )

# Generate build version header
configure_file(src/riot_version.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/riot/riot_version.hpp" @ONLY)

if(CMAKE_GENERATOR MATCHES "^(Visual Studio)")
    target_compile_options(riot INTERFACE /MP)
endif()


# PRECOMPILED HEADERS
if(RIOT_PCH)
    target_precompile_headers(riot PRIVATE
            <vector>
            )
endif()
message(STATUS "PRECOMPILED HEADERS: ${RIOT_PCH}")


# HEADERS AND SOURCES
include(header_list.cmake)
target_sources(riot PRIVATE ${engine_headers})
add_subdirectory(src)

