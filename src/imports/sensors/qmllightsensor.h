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

#ifndef QMLLightSensor_H
#define QMLLightSensor_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QLightSensor;

class QmlLightSensor : public QmlSensor
{
    Q_OBJECT
    Q_PROPERTY(qreal fieldOfView READ fieldOfView NOTIFY fieldOfViewChanged)
public:
    explicit QmlLightSensor(QObject *parent = 0);
    ~QmlLightSensor();

    qreal fieldOfView() const;

Q_SIGNALS:
    void fieldOfViewChanged(qreal fieldOfView);

private:
    QSensor *sensor() const override;
    QLightSensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlLightSensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal illuminance READ illuminance NOTIFY illuminanceChanged)
public:
    explicit QmlLightSensorReading(QLightSensor *sensor);
    ~QmlLightSensorReading();

    qreal illuminance() const;

Q_SIGNALS:
    void illuminanceChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QLightSensor *m_sensor;
    qreal m_illuminance;
};

QT_END_NAMESPACE
#endif
