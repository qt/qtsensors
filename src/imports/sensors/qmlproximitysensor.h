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

#ifndef QMLPROXIMITYSENSOR_H
#define QMLPROXIMITYSENSOR_H

#include "qmlsensor.h"
#ifdef near
#undef near
#endif
QT_BEGIN_NAMESPACE

class QProximitySensor;

class QmlProximitySensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlProximitySensor(QObject *parent = 0);
    ~QmlProximitySensor();


private:
    QSensor *sensor() const override;
    QProximitySensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlProximitySensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool near READ near NOTIFY nearChanged)
public:
    explicit QmlProximitySensorReading(QProximitySensor *sensor);
    ~QmlProximitySensorReading();

    bool near() const;

Q_SIGNALS:
    void nearChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QProximitySensor *m_sensor;
    bool m_near;
};

QT_END_NAMESPACE
#endif
