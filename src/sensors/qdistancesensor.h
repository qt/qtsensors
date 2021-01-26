/****************************************************************************
**
** Copyright (C) 2016 BlackBerry Limited. All rights reserved.
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

#ifndef QDISTANCESENSOR_H
#define QDISTANCESENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QDistanceReadingPrivate;

class Q_SENSORS_EXPORT QDistanceReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal distance READ distance)
    DECLARE_READING(QDistanceReading)
public:
    qreal distance() const;
    void setDistance(qreal distance);
};

class Q_SENSORS_EXPORT QDistanceFilter : public QSensorFilter
{
public:
    virtual bool filter(QDistanceReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QDistanceSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QDistanceSensor(QObject *parent = Q_NULLPTR);
    ~QDistanceSensor();
    QDistanceReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QDistanceSensor)
};

QT_END_NAMESPACE

#endif
