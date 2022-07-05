# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(grue_app LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/grue")

find_package(Qt6 REQUIRED COMPONENTS Quick Sensors)

qt_add_executable(grue_app
    main.cpp qmlgruesensor.h qmlgruesensor.cpp
)

set_target_properties(grue_app PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(grue_app PUBLIC
    Qt::Quick
    Qt::Sensors
)

qt6_add_qml_module(grue_app
    VERSION 1.0
    URI "QMLGrueSensor"
    QML_FILES
        grue.qml
    RESOURCES
        grue.png
)

add_subdirectory(plugin)

# Need to link to the plugin manually in a static Qt build.
if(NOT QT6_IS_SHARED_LIBS_BUILD)
    target_link_libraries(grue_app PRIVATE qtsensors_grue)
    target_sources(grue_app PRIVATE grue_plugin_import_custom.cpp)
endif()

set(build_console_app TRUE)

# The console app is not a macos bundle, so the shared library plugin wouldn't be found
if(APPLE AND QT6_IS_SHARED_LIBS_BUILD)
    set(build_console_app FALSE)
endif()

# Gui-less apps don't make sense for these platforms
if(IOS OR EMSCRIPTEN OR ANDROID)
    set(build_console_app FALSE)
endif()

if(build_console_app)
    add_subdirectory(console_app)
endif()

install(TARGETS grue_app
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
