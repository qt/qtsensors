# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(shakeit LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/shakeit")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

qt_add_executable(shakeit
    main.cpp
)

set_target_properties(shakeit PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(shakeit PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
)

# Resources:
set(shakeit_resource_files
    "audio/loopy2a_mono.wav"
    "audio/phone.wav"
    "content/triangle.png"
    "content/triangle2.png"
    "content/triangle3.png"
    "shakeit.qml"
)

qt6_add_resources(shakeit "shakeit"
    PREFIX
        "/"
    FILES
        ${shakeit_resource_files}
)

install(TARGETS shakeit
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
