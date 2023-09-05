if (RIOT_BUILD_TOOLS)
    # This tool is solely internal and does not need to be built by our ci
    if(NOT (RIOT_OS_MACOS OR RIOT_OS_IOS OR RIOT_OS_ANDROID OR RIOT_OS_PSX OR RIOT_OS_XBOX))
        add_subdirectory(code-formatter)
    endif()
    add_subdirectory(EmbeddedShader)
endif()