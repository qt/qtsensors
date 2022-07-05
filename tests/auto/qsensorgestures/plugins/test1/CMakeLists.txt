# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#####################################################################
## QTestSensorGestureDupPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QTestSensorGestureDupPlugin
    OUTPUT_NAME qtsensorgestures_testplugin1
    PLUGIN_TYPE sensorgestures
    DEFAULT_IF FALSE
    SOURCES
        qtest2recognizerduo.cpp
        qtest2recognizerdup.h
        qtestrecognizerdup.cpp qtestrecognizerdup.h
        qtestsensorgestureplugindup.cpp qtestsensorgestureplugindup_p.h
    DEFINES
        QT_DISABLE_DEPRECATED_BEFORE=0
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Sensors
        Qt::SensorGestures
)
