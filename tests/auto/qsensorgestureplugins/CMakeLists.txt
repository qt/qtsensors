# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#####################################################################
## tst_qsensorgesturepluginstest Binary:
#####################################################################

qt_internal_add_test(tst_qsensorgesturepluginstest
    SOURCES
        ../common/test_backends.cpp ../common/test_backends.h
        tst_qsensorgesturepluginstest.cpp
    INCLUDE_DIRECTORIES
        ../qsensor
    PUBLIC_LIBRARIES
        Qt::Sensors
        Qt::Test
)
