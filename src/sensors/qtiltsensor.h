/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QTILTSENSOR_H
#define QTILTSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QTiltReadingPrivate;

class Q_SENSORS_EXPORT QTiltReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal yRotation READ yRotation)
    Q_PROPERTY(qreal xRotation READ xRotation)
    DECLARE_READING(QTiltReading)

public:
    qreal yRotation() const;
    void setYRotation(qreal y);

    qreal xRotation() const;
    void setXRotation(qreal x);

};

class Q_SENSORS_EXPORT QTiltFilter : public QSensorFilter
{
public:
    virtual bool filter(QTiltReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QTiltSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QTiltSensor(QObject *parent = nullptr);
    ~QTiltSensor();
    QTiltReading *reading() const;
    static char const * const sensorType;

    Q_INVOKABLE void calibrate();

private:
    Q_DISABLE_COPY(QTiltSensor)
};

QT_END_NAMESPACE
#endif
