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

#ifndef QMLACCELEROMETER_H
#define QMLACCELEROMETER_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QAccelerometer;

class QmlAccelerometer : public QmlSensor
{
    Q_OBJECT
    Q_ENUMS(AccelerationMode)
    Q_PROPERTY(AccelerationMode accelerationMode READ accelerationMode WRITE setAccelerationMode
               NOTIFY accelerationModeChanged REVISION 1)
public:
    explicit QmlAccelerometer(QObject *parent = 0);
    ~QmlAccelerometer();

    // Keep this enum in sync with QAccelerometer::AccelerationMode
    enum AccelerationMode {
        Combined,
        Gravity,
        User
    };

    AccelerationMode accelerationMode() const;
    void setAccelerationMode(AccelerationMode accelerationMode);

signals:
    Q_REVISION(1) void accelerationModeChanged(AccelerationMode accelerationMode);

private:
    QSensor *sensor() const override;
    QAccelerometer *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlAccelerometerReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z NOTIFY zChanged)
public:
    explicit QmlAccelerometerReading(QAccelerometer *sensor);
    ~QmlAccelerometerReading();

    qreal x() const;
    qreal y() const;
    qreal z() const;

Q_SIGNALS:
    void xChanged();
    void yChanged();
    void zChanged();

private:
    QSensorReading *reading() const  override;
    void readingUpdate() override;
    QAccelerometer *m_sensor;
    qreal m_x;
    qreal m_y;
    qreal m_z;
};

QT_END_NAMESPACE
#endif
