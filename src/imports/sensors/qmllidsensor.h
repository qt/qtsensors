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
****************************************************************************/
#ifndef QMLLIDSENSOR_H
#define QMLLIDSENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QLidSensor;

class QmlLidSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlLidSensor(QObject *parent = 0);
    ~QmlLidSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QLidSensor *m_sensor;
};

class QmlLidReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool backLidChanged READ backLidChanged NOTIFY backLidChanged)
    Q_PROPERTY(bool frontLidClosed READ frontLidClosed NOTIFY frontLidChanged)
public:
    explicit QmlLidReading(QLidSensor *sensor);
    ~QmlLidReading();

    bool backLidChanged() const;
    bool frontLidClosed() const;

Q_SIGNALS:
    void backLidChanged(bool closed);
    bool frontLidChanged(bool closed);

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QLidSensor *m_sensor;
    bool m_backClosed;
    bool m_frontClosed;
};

QT_END_NAMESPACE
#endif
