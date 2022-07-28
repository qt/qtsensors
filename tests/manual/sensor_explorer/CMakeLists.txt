# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#####################################################################
## sensor_explorer Binary:
#####################################################################

qt_internal_add_manual_test(tst_manual_sensor_explorer
    GUI
    SOURCES
        explorer.cpp explorer.h explorer.ui
        main.cpp
    LIBRARIES
        Qt::Sensors
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)
