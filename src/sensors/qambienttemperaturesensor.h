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
******************************************************************************/
#ifndef QAMBIENTTEMPERATURESENSOR_H
#define QAMBIENTTEMPERATURESENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QAmbientTemperatureReadingPrivate;

class Q_SENSORS_EXPORT QAmbientTemperatureReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal temperature READ temperature)
    DECLARE_READING(QAmbientTemperatureReading)
public:
    qreal temperature() const;
    void setTemperature(qreal temperature);
};

class Q_SENSORS_EXPORT QAmbientTemperatureFilter : public QSensorFilter
{
public:
    virtual bool filter(QAmbientTemperatureReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QAmbientTemperatureSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QAmbientTemperatureSensor(QObject *parent = nullptr);
    ~QAmbientTemperatureSensor();
    QAmbientTemperatureReading *reading() const;
    static char const * const sensorType;

private:
    Q_DISABLE_COPY(QAmbientTemperatureSensor)
};

QT_END_NAMESPACE

#endif
