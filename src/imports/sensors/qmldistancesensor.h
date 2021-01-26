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

#ifndef QMLDISTANCESENSOR_H
#define QMLDISTANCESENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QDistanceSensor;

class QmlDistanceSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlDistanceSensor(QObject *parent = 0);
    ~QmlDistanceSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QDistanceSensor *m_sensor;
};

class QmlDistanceReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal distance READ distance NOTIFY distanceChanged)
public:
    explicit QmlDistanceReading(QDistanceSensor *sensor);
    ~QmlDistanceReading();

    qreal distance() const;

Q_SIGNALS:
    void distanceChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QDistanceSensor *m_sensor;
    qreal m_distance;
};

QT_END_NAMESPACE
#endif
