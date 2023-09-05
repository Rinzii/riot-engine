
if (NOT DEFINED RIOTENGINE_ROOT_DIR)
    message(FATAL_ERROR "RIOTENGINE_ROOT_DIR is not defined. It must ve set before we can include InitialSetup")
endif()

if (NOT DEFINED RIOTENGINE_TOOLS_DIR)
    set(RIOTENGINE_TOOLS_DIR "${RIOTENGINE_ROOT_DIR}/tools")
endif ()

