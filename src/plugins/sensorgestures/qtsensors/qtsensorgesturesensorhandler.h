/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
**
** $QT_END_LICENSE$
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
