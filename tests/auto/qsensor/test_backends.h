/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TEST_BACKENDS_H
#define TEST_BACKENDS_H

#include <qsensorbackend.h>

void register_test_backends();
void unregister_test_backends();

#include <qaccelerometer.h>
#include <qambientlightsensor.h>
#include <qcompass.h>
#include <qgyroscope.h>
#include <qlightsensor.h>
#include <qmagnetometer.h>
#include <qorientationsensor.h>
#include <qproximitysensor.h>
#include <qrotationsensor.h>
#include <qtapsensor.h>
#include <qirproximitysensor.h>

#define PREPARE_SENSORINTERFACE_DECLS(SensorClass, ReadingClass, FilterClass, readingcode)\
    class SensorClass ## _impl : public QSensorBackend\
    {\
    public:\
        SensorClass ## _impl(QSensor *sensor);\
        void start();\
        void stop();\
    };\
    class SensorClass ## _testfilter : public FilterClass { bool filter(ReadingClass *); };

#define PREPARE_SENSORINTERFACE_IMPLS(SensorClass, ReadingClass, FilterClass, readingcode)\
    SensorClass ## _impl::SensorClass ##_impl(QSensor *sensor) : QSensorBackend(sensor) {}\
    void SensorClass ## _impl::start() {\
        ReadingClass *reading = setReading<ReadingClass>(0);\
        readingcode\
        newReadingAvailable();\
    }\
    void SensorClass ##_impl::stop() {}\
    bool SensorClass ## _testfilter::filter(ReadingClass *) { return true; }\
    static QSensorBackend *create_ ## SensorClass ## _impl(QSensor *sensor) { return new SensorClass ## _impl(sensor); }\
    static bool registered_ ## SensorClass = registerTestBackend(#SensorClass, create_ ## SensorClass ## _impl);

#ifdef REGISTER_TOO
#define PREPARE_SENSORINTERFACE(SensorClass, ReadingClass, FilterClass, readingcode)\
        PREPARE_SENSORINTERFACE_DECLS(SensorClass, ReadingClass, FilterClass, readingcode)\
        PREPARE_SENSORINTERFACE_IMPLS(SensorClass, ReadingClass, FilterClass, readingcode)
#else
#define PREPARE_SENSORINTERFACE(SensorClass, ReadingClass, FilterClass, readingcode)\
        PREPARE_SENSORINTERFACE_DECLS(SensorClass, ReadingClass, FilterClass, readingcode)
#endif

PREPARE_SENSORINTERFACE(QAccelerometer, QAccelerometerReading, QAccelerometerFilter, {
    reading->setX(1.0);
    reading->setY(1.0);
    reading->setZ(1.0);
})
PREPARE_SENSORINTERFACE(QAmbientLightSensor, QAmbientLightReading, QAmbientLightFilter, {
    reading->setLightLevel(QAmbientLightReading::Twilight);
})
PREPARE_SENSORINTERFACE(QCompass, QCompassReading, QCompassFilter, {
    reading->setAzimuth(1.0);
    reading->setCalibrationLevel(1.0);
})
PREPARE_SENSORINTERFACE(QGyroscope, QGyroscopeReading, QGyroscopeFilter, {
    reading->setX(1.0);
    reading->setY(1.0);
    reading->setZ(1.0);
})
PREPARE_SENSORINTERFACE(QLightSensor, QLightReading, QLightFilter, {
    reading->setLux(1.0);
})
PREPARE_SENSORINTERFACE(QMagnetometer, QMagnetometerReading, QMagnetometerFilter, {
    reading->setX(1.0);
    reading->setY(1.0);
    reading->setZ(1.0);
    reading->setCalibrationLevel(1.0);
})
PREPARE_SENSORINTERFACE(QOrientationSensor, QOrientationReading, QOrientationFilter, {
    reading->setOrientation(QOrientationReading::LeftUp);
})
PREPARE_SENSORINTERFACE(QProximitySensor, QProximityReading, QProximityFilter, {
    reading->setClose(true);
})
PREPARE_SENSORINTERFACE(QRotationSensor, QRotationReading, QRotationFilter, {
    reading->setX(1.0);
    reading->setY(1.0);
    reading->setZ(1.0);
})
PREPARE_SENSORINTERFACE(QTapSensor, QTapReading, QTapFilter, {
    reading->setTapDirection(QTapReading::Z_Both);
    reading->setDoubleTap(true);
})
PREPARE_SENSORINTERFACE(QIRProximitySensor, QIRProximityReading, QIRProximityFilter, {
    reading->setReflectance(0.5);
})

#define TEST_SENSORINTERFACE(SensorClass, ReadingClass, readingcode)\
    do {\
        SensorClass sensor;\
        SensorClass ## _testfilter filter;\
        sensor.addFilter(&filter);\
        sensor.start();\
        ReadingClass *reading = sensor.reading();\
        readingcode\
    } while (0);

#endif
