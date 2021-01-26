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

#ifndef QMLORIENTATIONSENSOR_H
#define QMLORIENTATIONSENSOR_H

#include "qmlsensor.h"
#include <QtSensors/QOrientationSensor>

QT_BEGIN_NAMESPACE

class QOrientationSensor;

class QmlOrientationSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlOrientationSensor(QObject *parent = 0);
    ~QmlOrientationSensor();


private:
    QSensor *sensor() const override;
    QOrientationSensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlOrientationSensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(QOrientationReading::Orientation orientation READ orientation NOTIFY orientationChanged)
public:

    explicit QmlOrientationSensorReading(QOrientationSensor *sensor);
    ~QmlOrientationSensorReading();

    QOrientationReading::Orientation orientation() const;

Q_SIGNALS:
    void orientationChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QOrientationSensor *m_sensor;
    QOrientationReading::Orientation m_orientation;
};

QT_END_NAMESPACE
#endif
