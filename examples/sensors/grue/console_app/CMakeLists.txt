# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(detect_grue LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/grue")

find_package(Qt6 REQUIRED COMPONENTS Core Sensors)

qt_add_executable(detect_grue
    main.cpp
)

set_target_properties(detect_grue PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE FALSE
)

if(WIN32 OR (UNIX AND NOT APPLE))
    set_target_properties(detect_grue PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
    )
endif()

target_link_libraries(detect_grue PUBLIC
    Qt::Core
    Qt::Sensors
)

# Need to link to the plugin manually in a static Qt build.
if(NOT QT6_IS_SHARED_LIBS_BUILD)
    target_link_libraries(detect_grue PRIVATE qtsensors_grue)
    target_sources(detect_grue PRIVATE ../grue_plugin_import_custom.cpp)
endif()

install(TARGETS detect_grue
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
