// Copyright (C) 2016 Lorn Potter
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only
#include <qmath.h>

#include "qfreefallsensorgesturerecognizer.h"

QT_BEGIN_NAMESPACE

QFreefallSensorGestureRecognizer::QFreefallSensorGestureRecognizer(QObject *parent)
    : QSensorGestureRecognizer(parent)
    , active(0)
    , detecting(0)
{
}

QFreefallSensorGestureRecognizer::~QFreefallSensorGestureRecognizer()
{
}

void QFreefallSensorGestureRecognizer::create()
{
}

QString QFreefallSensorGestureRecognizer::id() const
{
    return QString("QtSensors.freefall");
}

bool QFreefallSensorGestureRecognizer::start()
{
    if (QtSensorGestureSensorHandler::instance()->startSensor(QtSensorGestureSensorHandler::Accel)) {
        active = true;
        connect(QtSensorGestureSensorHandler::instance(),SIGNAL(accelReadingChanged(QAccelerometerReading*)),
                this,SLOT(accelChanged(QAccelerometerReading*)));
    } else {
        active = false;
    }
    return active;

}

bool QFreefallSensorGestureRecognizer::stop()
{
    QtSensorGestureSensorHandler::instance()->stopSensor(QtSensorGestureSensorHandler::Accel);
    disconnect(QtSensorGestureSensorHandler::instance(),SIGNAL(accelReadingChanged(QAccelerometerReading*)),
            this,SLOT(accelChanged(QAccelerometerReading*)));
    active = false;

    return active;
}

bool QFreefallSensorGestureRecognizer::isActive()
{
    return active;
}

#define FREEFALL_THRESHOLD 1.0
#define LANDED_THRESHOLD 20.0
#define FREEFALL_MAX 4

void QFreefallSensorGestureRecognizer::accelChanged(QAccelerometerReading *reading)
{
    const qreal x = reading->x();
    const qreal y = reading->y();
    const qreal z = reading->z();
    qreal sum = qSqrt(x * x + y * y + z * z);

    if (qAbs(sum) < FREEFALL_THRESHOLD) {
        detecting = true;
        freefallList.append(sum);
    } else {
        if (detecting && qAbs(sum) > LANDED_THRESHOLD) {
            Q_EMIT landed();
            Q_EMIT detected("landed");
            freefallList.clear();
        }
    }

    if (freefallList.count() > FREEFALL_MAX) {
        Q_EMIT freefall();
        Q_EMIT detected("freefall");
    }
}


QT_END_NAMESPACE

