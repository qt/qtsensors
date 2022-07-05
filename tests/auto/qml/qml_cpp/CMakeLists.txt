# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

qt_internal_add_test(tst_sensors_qmlcpp
    SOURCES
        ../../common/test_backends.cpp ../../common/test_backends.h
        # qtemplategestureplugin.cpp qtemplategestureplugin.h
        # qtemplaterecognizer.cpp qtemplaterecognizer.h
        tst_sensors_qmlcpp.cpp
    LIBRARIES
        Qt::Qml
        Qt::SensorsPrivate
        Qt::SensorsQuickPrivate
        Qt::TestPrivate
)
