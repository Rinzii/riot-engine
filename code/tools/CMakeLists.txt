if (RIOT_BUILD_TOOLS)
    # This tool is solely internal and does not need to be built by our ci
    if(RIOT_OS_WINDOWS OR RIOT_OS_LINUX OR INTERNAL_RIOT_FORCE_AUTOFORMAT)
        add_subdirectory(code-formatter)
    endif()
    add_subdirectory(EmbeddedShader)
endif()