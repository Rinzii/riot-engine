if (NOT DEFINED RIOTENGINE_ROOT_DIR)
        message(FATAL_ERROR "RIOTENGINE_ROOT_DIR is not defined!")
endif ()

project(riot-ext)

find_package(Threads)


file(ARCHIVE_EXTRACT INPUT "${RIOTENGINE_ROOT_DIR}/code/ext/src.zip" DESTINATION "${RIOTENGINE_ROOT_DIR}/code/ext")


include(FetchContent)
FetchContent_Declare(
        mim
        GIT_REPOSITORY https://github.com/Rinzii/mim.git
        GIT_TAG       origin/main # TODO: change this to a commit hash or tag once mim is stable
)
FetchContent_MakeAvailable(mim)

set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX17 ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        RapidJSON
        GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
        GIT_TAG        476ffa2fd272243275a74c36952f210267dc3088
        GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(RapidJSON)


if (NOT RIOT_OS_XBOX AND NOT RIOT_OS_PSX)
        add_subdirectory(src/vk_dynamic)
        add_library(vk-dynamic::vk-dynamic ALIAS vk-dynamic)

        add_subdirectory(src/vma)
        add_library(vma::vma ALIAS vma)

        set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
        set(SPIRV_CROSS_CLI OFF)
        set(SPIRV_CROSS_ENABLE_CPP OFF)
        set(SPIRV_CROSS_ENABLE_C_API OFF)
        set(SPIRV_CROSS_ENABLE_GLSL ON)
        set(SPIRV_CROSS_ENABLE_HLSL ON)
        set(SPIRV_CROSS_ENABLE_MSL OFF)
        set(SPIRV_CROSS_ENABLE_REFLECT OFF)
        set(SPIRV_CROSS_ENABLE_TESTS OFF)
        set(SPIRV_CROSS_ENABLE_UTIL OFF)
        set(SPIRV_CROSS_SHARED OFF)
        set(SPIRV_CROSS_STATIC ON)
        set(SPIRV_CROSS_SKIP_INSTALL ON)
        add_subdirectory(src/spirv_cross)
        add_library(SPIRVCross::HLSL ALIAS spirv-cross-hlsl)
endif ()

if (RIOT_OS_WINDOWS OR RIOT_OS_XBOX)
        add_subdirectory(src/d3dma)
        add_library(d3d12ma::d3d12ma ALIAS D3D12MemoryAllocator)
endif ()


add_subdirectory(src/dxc)
add_library(dxc::dxc ALIAS dxc)

add_subdirectory(src/fmt)

#add_subdirectory(src/freetype)

add_subdirectory(src/sdl2)

add_subdirectory(src/imgui)
add_library(imgui::imgui ALIAS imgui)

set(LUABRIDGE_CXX17 ON)
set(LUABRIDGE_TESTING OFF)
add_subdirectory(src/LuaBridge)
add_library(luabridge::luabridge ALIAS LuaBridge)



add_subdirectory(src/stb)
add_library(stb::image ALIAS stb-image)



add_library(riot-ext INTERFACE)
add_library(riot::ext ALIAS riot-ext)

if (NOT RIOT_OS_XBOX AND NOT RIOT_OS_PSX)
        target_link_libraries(riot-ext INTERFACE
                vk-dynamic::vk-dynamic
                vma::vma
                SPIRVCross::HLSL
        )
endif ()

if (RIOT_OS_WINDOWS OR RIOT_OS_XBOX)
        target_link_libraries(riot-ext INTERFACE
                d3d12ma::d3d12ma
        )
endif ()

target_link_libraries(riot-ext INTERFACE
        mim::mim
        dxc::dxc
        fmt::fmt
        SDL2::SDL2
        imgui::imgui
        luabridge::luabridge
        RapidJSON
        SPIRVCross::HLSL
        stb::image

        Threads::Threads
        )






