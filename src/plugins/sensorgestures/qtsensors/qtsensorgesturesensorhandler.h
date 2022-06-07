// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QTSENSORGESTURESENSORHANDLER_H
#define QTSENSORGESTURESENSORHANDLER_H

#include <QObject>

#include <QtSensors/QAccelerometer>
#include <QtSensors/QAccelerometerFilter>
#include <QtSensors/QSensor>
#include <QtSensors/QOrientationSensor>
#include <QtSensors/QProximitySensor>
#include <QtSensors/QIRProximitySensor>
#include <QtSensors/QTapSensor>

class QtSensorGestureSensorHandler : public QObject
{
    Q_OBJECT
public:
    explicit QtSensorGestureSensorHandler(QObject *parent = 0);

    enum SensorGestureSensors {
        Accel = 0,
        Orientation,
        Proximity,
        IrProximity,
        Tap
    };
    Q_ENUM(SensorGestureSensors)
    static QtSensorGestureSensorHandler *instance();
    qreal accelRange;

public slots:
    void accelChanged();
    void orientationChanged();
    void proximityChanged();
    void irProximityChanged();
    void doubletap();

    bool startSensor(SensorGestureSensors sensor);
    void stopSensor(SensorGestureSensors sensor);

Q_SIGNALS:
    void accelReadingChanged(QAccelerometerReading *reading);
    void orientationReadingChanged(QOrientationReading *reading);
    void proximityReadingChanged(QProximityReading *reading);
    void irProximityReadingChanged(QIRProximityReading *reading);
    void dTabReadingChanged(QTapReading *reading);

private:
    QAccelerometer *accel;
    QOrientationSensor *orientation;
    QProximitySensor *proximity;
    QIRProximitySensor *irProx;
    QTapSensor *tapSensor;

    QMap<SensorGestureSensors, int> usedSensorsMap;

};

#endif // QTSENSORGESTURESENSORHANDLER_H
