# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#####################################################################
## tst_qsensor Test:
#####################################################################

qt_internal_add_test(tst_qsensor
    SOURCES
        ../common/test_backends.cpp ../common/test_backends.h
        test_sensor.cpp test_sensor.h test_sensor_p.h
        test_sensor2.cpp test_sensor2.h test_sensor2_p.h
        test_sensor2impl.cpp test_sensor2impl.h
        test_sensorimpl.cpp test_sensorimpl.h
        test_sensorplugin.cpp
        tst_qsensor.cpp
    DEFINES
        QT_STATICPLUGIN
    LIBRARIES
        Qt::CorePrivate
        Qt::SensorsPrivate
)
