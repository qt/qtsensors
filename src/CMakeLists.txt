# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial

add_subdirectory(sensors)
add_subdirectory(plugins)
if(TARGET Qt::Quick)
    add_subdirectory(sensorsquick)
endif()
