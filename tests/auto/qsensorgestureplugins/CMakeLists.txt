# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## tst_qsensorgesturepluginstest Binary:
#####################################################################

qt_internal_add_test(tst_qsensorgesturepluginstest
    SOURCES
        ../common/test_backends.cpp ../common/test_backends.h
        tst_qsensorgesturepluginstest.cpp
    INCLUDE_DIRECTORIES
        ../qsensor
    LIBRARIES
        Qt::Sensors
        Qt::Test
)
