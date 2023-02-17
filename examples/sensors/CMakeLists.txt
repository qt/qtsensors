# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

if(TARGET Qt::Quick)
    qt_internal_add_example(grue)
    qt_internal_add_example(qmlqtsensors)
    qt_internal_add_example(sensor_explorer)
    if(TARGET Qt::Svg)
        qt_internal_add_example(sensorsshowcase)
    endif()
endif()
