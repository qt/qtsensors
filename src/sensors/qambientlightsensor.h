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

#ifndef QAMBIENTLIGHTSENSOR_H
#define QAMBIENTLIGHTSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QAmbientLightReadingPrivate;

class Q_SENSORS_EXPORT QAmbientLightReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(LightLevel lightLevel READ lightLevel)
    DECLARE_READING(QAmbientLightReading)
public:
    enum LightLevel {
        Undefined = 0,
        Dark,
        Twilight,
        Light,
        Bright,
        Sunny
    };
    Q_ENUM(LightLevel)

    LightLevel lightLevel() const;
    void setLightLevel(LightLevel lightLevel);
};

class Q_SENSORS_EXPORT QAmbientLightFilter : public QSensorFilter
{
public:
    virtual bool filter(QAmbientLightReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QAmbientLightSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QAmbientLightSensor(QObject *parent = nullptr);
    virtual ~QAmbientLightSensor();
    QAmbientLightReading *reading() const;
    static char const * const sensorType;

private:
    Q_DISABLE_COPY(QAmbientLightSensor)
};

QT_END_NAMESPACE

#endif
