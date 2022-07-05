# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(sensorsshowcase LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/sensorsshowcase")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Sensors Svg)

qt_add_executable(sensorsshowcase
    main.cpp
)

set_target_properties(sensorsshowcase PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(ANDROID)
    set_property(TARGET sensorsshowcase PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/android)
    endif()
if(APPLE)
    if(IOS)
        set_property(TARGET sensorsshowcase PROPERTY
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
        )
    endif()
endif()

target_link_libraries(sensorsshowcase PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Sensors
    Qt::Svg
)

# Resources:
set(sensorsshowcase_resource_files
    "sensorsshowcase.qml"
    "accelerometer.qml"
    "proximity.qml"
    "compass.qml"
    "magnetometer.qml"
    "gyroscope.qml"
    "images/magnet.svg"
    "images/compass.svg"
    "images/qt_logo.png"
)

qt6_add_resources(sensorsshowcase "sensorsshowcase"
    PREFIX
        "/"
    FILES
        ${sensorsshowcase_resource_files}
)

install(TARGETS sensorsshowcase
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
