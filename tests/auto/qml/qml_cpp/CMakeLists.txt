# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_sensors_qmlcpp LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

qt_internal_add_test(tst_sensors_qmlcpp
    SOURCES
        ../../common/test_backends.cpp ../../common/test_backends.h
        tst_sensors_qmlcpp.cpp
    LIBRARIES
        Qt::Qml
        Qt::SensorsPrivate
        Qt::SensorsQuickPrivate
        Qt::TestPrivate
)
