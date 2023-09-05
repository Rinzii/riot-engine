

set(core_base_config_headers
        include/riot/core/base/config/architecture.h
        include/riot/core/base/config/compiler.h
        include/riot/core/base/config/compilerTraits.h
        include/riot/core/base/config/defines.h
        include/riot/core/base/config/platform.h
        include/riot/core/base/config/settings.h
)

set(core_base_headers
        ${core_base_config_headers}
        include/riot/core/base/base.h
)

set(core_platform_win32_internal_headers
        include/riot/core/platform/win32/internal/minWindows.h
        include/riot/core/platform/win32/internal/postWinapi.h
        include/riot/core/platform/win32/internal/preWinapi.h
)

set(core_platform_win32_headers
        ${core_platform_win32_internal_headers}
        include/riot/core/platform/win32/windows.h
)

set(core_platform_headers
        ${core_platform_win32_headers}
)

set(core_headers
        ${core_base_headers}
        ${core_platform_headers}

        include/riot/core/monoInstance.h
)

set(rhi_headers

)

set(rtl_headers
        include/riot/rtl/staticVector.h
)

set(system_headers
        include/riot/system/logging.h
)

set(util_headers
        include/riot/util/version.h
)

# core header include
set(engine_headers
        ${core_headers}
        ${rhi_headers}
        ${rtl_headers}
        ${system_headers}
        ${util_headers}
        )
