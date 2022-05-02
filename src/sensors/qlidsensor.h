/****************************************************************************
**
** Copyright (C) 2016 Canonical, Ltd
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
#ifndef QLIDSENSOR_H
#define QLIDSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QLidReadingPrivate;

class Q_SENSORS_EXPORT QLidReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool backLidClosed READ backLidClosed)
    Q_PROPERTY(bool frontLidClosed READ frontLidClosed)
    DECLARE_READING(QLidReading)
public:

    bool backLidClosed() const;
    void setBackLidClosed(bool closed);

    bool frontLidClosed() const;
    void setFrontLidClosed(bool closed);

Q_SIGNALS:
    void backLidChanged(bool closed);
    void frontLidChanged(bool closed);
};

class Q_SENSORS_EXPORT QLidFilter : public QSensorFilter
{
public:
    virtual bool filter(QLidReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QLidSensor : public QSensor
{
    Q_OBJECT
public:
    explicit QLidSensor(QObject *parent = nullptr);
    ~QLidSensor();
    QLidReading *reading() const;
    static char const * const sensorType;

private:
    Q_DISABLE_COPY(QLidSensor)
};

QT_END_NAMESPACE

#endif
