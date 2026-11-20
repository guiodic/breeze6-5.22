set(BREEZE_THEME_ID "breeze-5.22")
set(BREEZE_DARK_THEME_ID "breeze-dark-5.22")
set(BREEZE_LIGHT_THEME_ID "breeze-light-5.22")

option(GZIP_DESKTOPTHEME_SVG "Install Desktop Theme SVG files as .svgz." ON)

if (GZIP_DESKTOPTHEME_SVG)
    if(WIN32)
        find_program(SEVEN_Z_EXECUTABLE NAMES 7z 7zz REQUIRED)
    else()
        find_program(GZIP_EXECUTABLE NAMES gzip REQUIRED)
    endif()
endif()

# Helper function, private for now
# Once it has matured and proven, add to public macros
function(PLASMA_INSTALL_DESKTOPTHEME_SVGS theme_name)
    set(options
    )
    set(oneValueArgs
        SUBPATH
    )
    set(multiValueArgs
        FILES
    )

    cmake_parse_arguments(PIDS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT DEFINED PIDS_SUBPATH)
        message(FATAL_ERROR "SUBPATH needs to be defined when calling plasma_install_desktoptheme_svgs.")
    endif()

    if(NOT PIDS_FILES)
        message(FATAL_ERROR "No files passed when calling plasma_install_desktoptheme_svgs.")
    endif()

    set(_target_name "${theme_name}_desktoptheme_graphics_${PIDS_SUBPATH}")
    string(REPLACE "/" "_" _target_name "${_target_name}")

    set(desktoptheme_COMPONENTDIR "${theme_name}/${PIDS_SUBPATH}")

    if (GZIP_DESKTOPTHEME_SVG)
        set(desktoptheme_GZIPDIR "${theme_name}.gzipped/${PIDS_SUBPATH}")
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${desktoptheme_GZIPDIR}")
    endif()

    set(_install_files)

    foreach(_src_file ${PIDS_FILES})
        if (NOT IS_ABSOLUTE ${_src_file})
            set(_src_file "${CMAKE_CURRENT_SOURCE_DIR}/${_src_file}")
        endif()
        if (NOT EXISTS ${_src_file})
            message(FATAL_ERROR "No such file found: ${_src_file}")
        endif()
        get_filename_component(_fileName "${_src_file}" NAME)

        if (GZIP_DESKTOPTHEME_SVG)
            set(_gzipped_file_displayname "${desktoptheme_COMPONENTDIR}/${_fileName}z")
            set(_gzipped_file "${CMAKE_CURRENT_BINARY_DIR}/${desktoptheme_GZIPDIR}/${_fileName}z")
            if(WIN32)
                add_custom_command(
                    OUTPUT ${_gzipped_file}
                    COMMAND "${SEVEN_Z_EXECUTABLE}"
                    ARGS
                        a
                        -tgzip
                        ${_gzipped_file} ${_src_file}
                    DEPENDS ${_src_file}
                    COMMENT "Gzipping ${_gzipped_file_displayname}"
                )
            else()
                add_custom_command(
                    OUTPUT ${_gzipped_file}
                    COMMAND "${GZIP_EXECUTABLE}"
                    ARGS
                        -9 # compress best
                        -n # no original name and timestamp stored, for reproducibility
                        -c # write to stdout
                        ${_src_file} > ${_gzipped_file}
                    DEPENDS ${_src_file}
                    COMMENT "Gzipping ${_gzipped_file_displayname}"
                )
            endif()
        else()
            set(_gzipped_file "${_src_file}")
        endif()

        list(APPEND _install_files "${_gzipped_file}")
    endforeach()

    add_custom_target(${_target_name} ALL DEPENDS ${_install_files})

    # KSvg falls back to the system's default image set. Give each variant its own assets.
    foreach(theme_id IN ITEMS "${theme_name}" "${BREEZE_DARK_THEME_ID}" "${BREEZE_LIGHT_THEME_ID}")
        install(FILES ${_install_files}
            DESTINATION "${PLASMA_DATA_INSTALL_DIR}/desktoptheme/${theme_id}/${PIDS_SUBPATH}")
    endforeach()
endfunction()


add_subdirectory( breeze )
add_subdirectory( breeze-dark )
add_subdirectory( breeze-light )
