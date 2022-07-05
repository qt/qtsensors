# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(qtsensorgestures_counterplugin LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sensors)

qt_add_plugin(qtsensorgestures_counterplugin)

target_sources(qtsensorgestures_counterplugin PRIVATE
    qcountergestureplugin.cpp qcountergestureplugin.h
    qcounterrecognizer.cpp qcounterrecognizer.h
)

set_target_properties(qtsensorgestures_counterplugin PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qtsensorgestures_counterplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Sensors
)

install(TARGETS qtsensorgestures_counterplugin
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
