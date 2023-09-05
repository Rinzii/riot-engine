add_subdirectory(ext)
add_subdirectory(engine)

if (RIOT_BUILD_LAUNCHER)
    add_subdirectory(launcher)
endif()



if (RIOT_BUILD_TOOLS)
    add_subdirectory(tools)

    if (RIOT_AUTOFORMAT)
        # TODO: Bring this back in later.
        #add_custom_target(autoformat ALL
        #        code-formatter -q engine
        #        COMMAND code-formatter -q editor/src
        #        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        #        USES_TERMINAL
        #        COMMENT "Formatting sources"
        #)

        #add_dependencies(riot autoformat)
        #add_dependencies(riot-editor autoformat)
    endif()
endif()
