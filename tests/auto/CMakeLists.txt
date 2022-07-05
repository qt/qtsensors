# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

add_subdirectory(qsensor)
add_subdirectory(cmake)
if(TARGET Qt::Quick)
    add_subdirectory(qml)
endif()
# add_subdirectory(qsensorgestures)
# add_subdirectory(qsensorgestureplugins)
# if(UNIX AND NOT APPLE)
#     add_subdirectory(qsensorgestures_gestures)
# endif()
