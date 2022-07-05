# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

cmake_minimum_required(VERSION 3.16)
project(sensorgesturessdocsnippet LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Sensors)

qt_add_executable(sensorgesturessdocsnippet
    creating.cpp
    main.cpp
    myplugin.h
    plugin.cpp
)

target_link_libraries(sensorgesturessdocsnippet PUBLIC
        Qt::Sensors
)

if (GCC AND UNIX)
    target_link_libraries(sensorgesturessdocsnippet PUBLIC
        rdynamic
        log
    )
endif()
