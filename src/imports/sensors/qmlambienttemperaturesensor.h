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
#ifndef QMLAMBIENTTEMPERATURESENSOR_H
#define QMLAMBIENTTEMPERATURESENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QAmbientTemperatureSensor;

class QmlAmbientTemperatureSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlAmbientTemperatureSensor(QObject *parent = 0);
    ~QmlAmbientTemperatureSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QAmbientTemperatureSensor *m_sensor;
};

class QmlAmbientTemperatureReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal temperature READ temperature NOTIFY temperatureChanged)
public:
    explicit QmlAmbientTemperatureReading(QAmbientTemperatureSensor *sensor);
    ~QmlAmbientTemperatureReading();

    qreal temperature() const;

Q_SIGNALS:
    void temperatureChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QAmbientTemperatureSensor *m_sensor;
    qreal m_temperature;
};

QT_END_NAMESPACE
#endif
