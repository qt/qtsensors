/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

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
    Q_ENUMS(SensorGestureSensors)
public:
    explicit QtSensorGestureSensorHandler(QObject *parent = 0);

    enum SensorGestureSensors {
        Accel = 0,
        Orientation,
        Proximity,
        IrProximity,
        Tap
    };
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
