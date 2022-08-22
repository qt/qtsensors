# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(TARGET Qt::Widgets)
    add_subdirectory(sensor_explorer)
endif()
if (TARGET Qt::Quick)
    add_subdirectory(sensorclerk)
endif()
