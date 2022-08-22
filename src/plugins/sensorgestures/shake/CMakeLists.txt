# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QShakeSensorGesturePlugin Plugin:
#####################################################################

qt_internal_add_plugin(QShakeSensorGesturePlugin
    OUTPUT_NAME qtsensorgestures_shakeplugin
    PLUGIN_TYPE sensorgestures
    DEFAULT_IF FALSE
    SOURCES
        qshakerecognizer.cpp qshakerecognizer.h
        qshakesensorgestureplugin.cpp qshakesensorgestureplugin.h
    LIBRARIES
        Qt::Core
        Qt::Sensors
)

#### Keys ignored in scope 1:.:.:shake.pro:<TRUE>:
# OTHER_FILES = "plugin.json"
# PLUGIN_EXTENDS = "-"
