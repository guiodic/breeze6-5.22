find_package(Python3 REQUIRED COMPONENTS Interpreter)
find_program(SASSC_EXECUTABLE NAMES sassc REQUIRED)
execute_process(COMMAND "${Python3_EXECUTABLE}" -c "import cairo" RESULT_VARIABLE cairo_import)
if(NOT cairo_import EQUAL 0)
    message(FATAL_ERROR "Python Cairo is required to generate the Breeze GTK assets.")
endif()

file(GLOB_RECURSE gtk_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.scss"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/gtk2/*"
)
set(light_palette "${PROJECT_SOURCE_DIR}/colors/Breeze522.colors")

function(build_gtk_theme name palette)
    set(output "${CMAKE_CURRENT_BINARY_DIR}/${name}")
    set(outputs "${output}/gtk-2.0/gtkrc" "${output}/gtk-3.0/gtk.css" "${output}/gtk-4.0/gtk.css")
    add_custom_command(
        OUTPUT ${outputs}
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${output}/gtk-3.0" "${output}/gtk-4.0"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/gtk2" "${output}/gtk-2.0"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/render_assets.py"
            -c "${palette}" -b "${light_palette}" -a "${output}/assets" -g "${output}/gtk-2.0" -G "${output}"
        COMMAND "${SASSC_EXECUTABLE}" -I "${output}" "${CMAKE_CURRENT_SOURCE_DIR}/gtk3/gtk.scss" "${output}/gtk-3.0/gtk.css"
        COMMAND "${SASSC_EXECUTABLE}" -I "${output}" "${CMAKE_CURRENT_SOURCE_DIR}/gtk4/gtk.scss" "${output}/gtk-4.0/gtk.css"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${output}/assets"
        DEPENDS ${gtk_sources} "${CMAKE_CURRENT_SOURCE_DIR}/render_assets.py" "${palette}" "${light_palette}"
        VERBATIM
    )
    add_custom_target(${name}-gtk ALL DEPENDS ${outputs})
    install(DIRECTORY "${output}/" DESTINATION "${KDE_INSTALL_DATADIR}/themes/${name}"
        PATTERN "_global.scss" EXCLUDE)
endfunction()

build_gtk_theme(Breeze-5.22 "${light_palette}")
build_gtk_theme(Breeze-Dark-5.22 "${PROJECT_SOURCE_DIR}/colors/BreezeDark522.colors")

foreach(version IN ITEMS 3 4)
    set(dark_css "${CMAKE_CURRENT_BINARY_DIR}/gtk-${version}-dark.css")
    file(WRITE "${dark_css}" "@import url(\"../../Breeze-Dark-5.22/gtk-${version}.0/gtk.css\");\n")
    install(FILES "${dark_css}" DESTINATION "${KDE_INSTALL_DATADIR}/themes/Breeze-5.22/gtk-${version}.0"
        RENAME gtk-dark.css)
endforeach()
