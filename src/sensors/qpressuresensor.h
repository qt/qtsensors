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
#ifndef QPRESSURESENSOR_H
#define QPRESSURESENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QPressureReadingPrivate;

class Q_SENSORS_EXPORT QPressureReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal pressure READ pressure)
    Q_PROPERTY(qreal temperature READ temperature)
    DECLARE_READING(QPressureReading)
public:
    qreal pressure() const;
    void setPressure(qreal pressure);

    qreal temperature() const;
    void setTemperature(qreal temperature);
};

class Q_SENSORS_EXPORT QPressureFilter : public QSensorFilter
{
public:
    virtual bool filter(QPressureReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QPressureSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QPressureSensor(QObject *parent = Q_NULLPTR);
    ~QPressureSensor();
    QPressureReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QPressureSensor)
};

QT_END_NAMESPACE

#endif
