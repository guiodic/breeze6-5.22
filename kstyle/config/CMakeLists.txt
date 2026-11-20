### configuration plugin
add_definitions(-DTRANSLATION_DOMAIN=\"breeze522_style_config\")
set(kstyle_breeze_config_PART_SRCS breezestyleconfig.cpp)

set(kstyle_breeze_config_PART_SRCS ${kstyle_breeze_config_PART_SRCS} breezestyleconfigmodule.cpp)

kconfig_add_kcfg_files(kstyle_breeze_config_PART_SRCS ../breezestyleconfigdata.kcfgc)
set(kstyle_breeze_config_PART_FORMS ui/breezestyleconfig.ui)
ki18n_wrap_ui(kstyle_breeze_config_PART_FORMS_HEADERS ${kstyle_breeze_config_PART_FORMS})

kcoreaddons_add_plugin(breeze522styleconfig SOURCES
    ${kstyle_breeze_config_PART_SRCS}
    ${kstyle_breeze_config_PART_FORMS_HEADERS}
    INSTALL_NAMESPACE "kstyle_config"
)

target_link_libraries(breeze522styleconfig
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if(HAVE_QTDBUS)
    target_link_libraries(breeze522styleconfig
        PUBLIC
            Qt6::DBus
    )
endif()

target_link_libraries(breeze522styleconfig
    PUBLIC
        KF6::CoreAddons
        KF6::ConfigCore
        KF6::ConfigWidgets
        KF6::I18n
)
if(QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(breeze522styleconfig
        PUBLIC
    KF6::KCMUtils
)
endif()
kcmutils_generate_desktop_file(breeze522styleconfig)

set(breeze_settings_SOURCES main.cpp)
add_executable(breeze-settings ${breeze_settings_SOURCES} )
target_link_libraries(breeze-settings Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(breeze-settings KF6::I18n KF6::KCMUtils KF6::CoreAddons)

set_target_properties(breeze-settings PROPERTIES OUTPUT_NAME breeze522-settings6)

install(TARGETS breeze-settings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

# icon
ecm_install_icons(ICONS sc-apps-breeze522-settings.svg
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor )

# kcmshell6 < 6.27.0 doesn't know the --smoke-test param, so skip this test for
# now.
# TODO: Drop this when KF6_MIN_VERSION >= 6.27.0
if(KF6KCMUtils_VERSION VERSION_GREATER_EQUAL "6.27.0")
    add_test(NAME breeze522styleconfig_smoketest COMMAND kcmshell6 -style Breeze-5.22 --smoke-test kstyle_config/breeze522styleconfig)
    set_tests_properties(breeze522styleconfig_smoketest PROPERTIES
        ENVIRONMENT_MODIFICATION QT_PLUGIN_PATH=path_list_prepend:${CMAKE_BINARY_DIR}/bin
    )
endif()
