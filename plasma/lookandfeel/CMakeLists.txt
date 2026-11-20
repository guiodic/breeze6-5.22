set(BREEZE522_CURSOR_DEFAULT "")
if(BUILD_CURSOR)
    set(BREEZE522_CURSOR_DEFAULT "\n[kcminputrc][Mouse]\ncursorTheme=breeze_cursors_522\n")
endif()

set(BREEZE522_DECORATION_DEFAULT "")
if(WITH_DECORATIONS)
    set(BREEZE522_DECORATION_DEFAULT "\n[kwinrc][org.kde.kdecoration2]\nlibrary=org.kde.breeze522\ntheme=Breeze\n")
endif()

set(lookandfeel_install_dir "${PLASMA_DATA_INSTALL_DIR}/look-and-feel/org.kde.breeze522.desktop")
configure_file(contents/defaults.in defaults @ONLY)
install(FILES metadata.json DESTINATION "${lookandfeel_install_dir}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/defaults" DESTINATION "${lookandfeel_install_dir}/contents")

if(BUILD_GTK_THEME)
    install(PROGRAMS breeze522-apply-theme DESTINATION "${KDE_INSTALL_BINDIR}")
endif()
