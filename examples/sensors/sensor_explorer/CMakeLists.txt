# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

cmake_minimum_required(VERSION 3.16)
project(sensor_explorer LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/sensor_explorer")

find_package(Qt6 REQUIRED COMPONENTS Qml Quick Sensors)

qt_add_executable(sensor_explorer
    main.cpp
    sensormodels.cpp sensormodels.h
)

set_target_properties(sensor_explorer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(sensor_explorer PUBLIC
    Qt::Qml
    Qt::Quick
    Qt::Sensors
)

qt_add_qml_module(sensor_explorer
    URI SensorModels
    VERSION 1.0
    QML_FILES sensor_explorer.qml
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS sensor_explorer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
