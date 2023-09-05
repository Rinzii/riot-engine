if (NOT DEFINED RIOTENGINE_ROOT_DIR)
    message(FATAL_ERROR "RIOTENGINE_ROOT_DIR is not defined!")
endif ()



file(ARCHIVE_EXTRACT INPUT "${RIOTENGINE_ROOT_DIR}/tools/dxc.zip" DESTINATION "${RIOTENGINE_ROOT_DIR}/tools")

if (RIOT_OS_LINUX)
    # This is required the the ci to be able to use dxc
    execute_process(COMMAND chmod +x "${RIOTENGINE_ROOT_DIR}/tools/dxc/linux/bin/dxc")
    message(STATUS "Giving execute permissions to dxc at ${RIOTENGINE_ROOT_DIR}/tools/dxc/linux/bin/dxc")
endif()