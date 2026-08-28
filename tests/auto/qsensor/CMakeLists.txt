# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(NOT QT_BUILD_STANDALONE_TESTS AND NOT QT_BUILDING_QT)
    cmake_minimum_required(VERSION 3.16)
    project(tst_qsensor LANGUAGES CXX)
    find_package(Qt6BuildInternals REQUIRED COMPONENTS STANDALONE_TEST)
endif()

#####################################################################
## tst_qsensor Test:
#####################################################################

qt_internal_add_test(tst_qsensor
    SOURCES
        ../common/test_backends.cpp ../common/test_backends.h
        test_sensor.cpp test_sensor.h test_sensor_p.h
        test_sensor2.cpp test_sensor2.h test_sensor2_p.h
        test_sensor2impl.cpp test_sensor2impl.h
        test_sensorimpl.cpp test_sensorimpl.h
        test_sensorplugin.cpp
        tst_qsensor.cpp
    DEFINES
        QT_STATICPLUGIN
    LIBRARIES
        Qt::CorePrivate
        Qt::SensorsPrivate
)
