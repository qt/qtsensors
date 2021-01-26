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

#ifndef QMLIRPROXIMITYSENSOR_H
#define QMLIRPROXIMITYSENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QIRProximitySensor;

class QmlIRProximitySensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlIRProximitySensor(QObject *parent = 0);
    ~QmlIRProximitySensor();

private:
    QSensor *sensor() const override;
    QIRProximitySensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlIRProximitySensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal reflectance READ reflectance NOTIFY reflectanceChanged)
public:
    explicit QmlIRProximitySensorReading(QIRProximitySensor *sensor);
    ~QmlIRProximitySensorReading();

    qreal reflectance() const;

Q_SIGNALS:
    void reflectanceChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QIRProximitySensor *m_sensor;
    qreal m_reflectance;
};

QT_END_NAMESPACE
#endif
