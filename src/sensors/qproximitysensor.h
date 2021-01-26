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

#ifndef QPROXIMITYSENSOR_H
#define QPROXIMITYSENSOR_H

#include <QtSensors/qsensor.h>

QT_BEGIN_NAMESPACE

class QProximityReadingPrivate;

class Q_SENSORS_EXPORT QProximityReading : public QSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool close READ close)
    DECLARE_READING(QProximityReading)
public:
    bool close() const;
    void setClose(bool close);
};

class Q_SENSORS_EXPORT QProximityFilter : public QSensorFilter
{
public:
    virtual bool filter(QProximityReading *reading) = 0;
private:
    bool filter(QSensorReading *reading) override;
};

class Q_SENSORS_EXPORT QProximitySensor : public QSensor
{
    Q_OBJECT
public:
    explicit QProximitySensor(QObject *parent = Q_NULLPTR);
    virtual ~QProximitySensor();
    QProximityReading *reading() const;
    static char const * const type;

private:
    Q_DISABLE_COPY(QProximitySensor)
};

QT_END_NAMESPACE

#endif

