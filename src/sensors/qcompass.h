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

#ifndef QCOMPASS_H
#define QCOMPASS_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QCompassReadingPrivate;

class Q_SENSORS_EXPORT QCompassReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal azimuth READ azimuth)
    Q_PROPERTY(qreal calibrationLevel READ calibrationLevel)
    DECLARE_READING(QCompassReading)
public:
    qreal azimuth() const;
    void setAzimuth(qreal azimuth);

    qreal calibrationLevel() const;
    void setCalibrationLevel(qreal calibrationLevel);
};

class Q_SENSORS_EXPORT QCompassFilter : public QSensorFilter
{
public:
    virtual bool filter(QCompassReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QCompass : public QSensor
{
    Q_OBJECT
public:
    explicit QCompass(QObject *parent = Q_NULLPTR);
    virtual ~QCompass();
    QCompassReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QCompass)
};

QT_END_NAMESPACE

#endif

