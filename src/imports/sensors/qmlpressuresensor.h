/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
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
#ifndef QMLPRESSURESENSOR_H
#define QMLPRESSURESENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QPressureSensor;

class QmlPressureSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlPressureSensor(QObject *parent = 0);
    ~QmlPressureSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QPressureSensor *m_sensor;
};

class QmlPressureReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal pressure READ pressure NOTIFY pressureChanged)
    Q_PROPERTY(qreal temperature READ temperature NOTIFY temperatureChanged REVISION 1)
public:
    explicit QmlPressureReading(QPressureSensor *sensor);
    ~QmlPressureReading();

    qreal pressure() const;
    qreal temperature() const;

Q_SIGNALS:
    void pressureChanged();
    Q_REVISION(1) void temperatureChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QPressureSensor *m_sensor;
    qreal m_pressure;
    qreal m_temperature;
};

QT_END_NAMESPACE
#endif
