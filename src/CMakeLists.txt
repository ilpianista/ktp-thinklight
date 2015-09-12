kconfig_add_kcfg_files(ktptextui_message_filter_thinklight_SRCS thinklightconfig.kcfgc)

add_library(ktptextui_message_filter_thinklight MODULE thinklight-filter.cpp
                 ${ktptextui_message_filter_thinklight_SRCS}
)

target_link_libraries (ktptextui_message_filter_thinklight
    ktpchat
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::ConfigGui
    KTp::CommonInternals
)

ki18n_wrap_ui(kcm_ktptextui_message_filter_thinklight_SRCS
    thinklight-config.ui
)

kconfig_add_kcfg_files(kcm_ktptextui_message_filter_thinklight_SRCS thinklightconfig.kcfgc)

add_library(kcm_ktptextui_message_filter_thinklight MODULE thinklight-config.cpp
                 ${kcm_ktptextui_message_filter_thinklight_SRCS}
)

kcoreaddons_desktop_to_json(kcm_ktptextui_message_filter_thinklight kcm_ktptextui_message_filter_thinklight.desktop)

target_link_libraries (kcm_ktptextui_message_filter_thinklight
    ktpchat
    KF5::ConfigWidgets
    KF5::I18n
)

# Install:
install (TARGETS ktptextui_message_filter_thinklight
                 kcm_ktptextui_message_filter_thinklight
         DESTINATION ${PLUGIN_INSTALL_DIR}
)

install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/ktptextui_message_filter_thinklight.desktop
               ${CMAKE_CURRENT_SOURCE_DIR}/kcm_ktptextui_message_filter_thinklight.desktop
         DESTINATION ${SERVICES_INSTALL_DIR}
)
