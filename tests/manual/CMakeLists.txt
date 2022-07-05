# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

if(TARGET Qt::Widgets)
    add_subdirectory(sensor_explorer)
endif()
if (TARGET Qt::Quick)
    add_subdirectory(sensorclerk)
endif()
