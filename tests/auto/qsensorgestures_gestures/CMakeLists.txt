# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## tst_sensorgestures_gestures Test:
#####################################################################

# Collect test data
file(GLOB_RECURSE test_data_glob
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    mock_data/*
    dataset2_mock_data/*)
list(APPEND test_data ${test_data_glob})

qt_internal_add_test(tst_sensorgestures_gestures
    SOURCES
        mockbackends.h
        mockcommon.cpp mockcommon.h
        tst_sensorgestures_gestures.cpp
    LIBRARIES
        Qt::SensorsPrivate
)

qt_internal_add_resource(tst_sensorgestures_gestures
    "tst_sensorgestures_gestures_testdata"
    PREFIX "/"
    FILES ${test_data})
