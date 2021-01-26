/****************************************************************************
**
** Copyright (C) 2016 Canonical Ltd
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

#ifndef QMLHUMIDITYSENSOR_H
#define QMLHUMIDITYSENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QHumiditySensor;

class QmlHumiditySensor : public QmlSensor
{
    Q_OBJECT

public:
    explicit QmlHumiditySensor(QObject *parent = Q_NULLPTR);
    ~QmlHumiditySensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QHumiditySensor *m_sensor;
};

class QmlHumidityReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal relativeHumidity READ relativeHumidity NOTIFY relativeHumidityChanged)
    Q_PROPERTY(qreal absoluteHumidity READ absoluteHumidity NOTIFY absoluteHumidityChanged)
public:
    explicit QmlHumidityReading(QHumiditySensor *sensor);
    ~QmlHumidityReading();

    qreal relativeHumidity() const;
    qreal absoluteHumidity() const;

Q_SIGNALS:
    void relativeHumidityChanged();
    void absoluteHumidityChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QHumiditySensor *m_sensor;
    qreal m_relativeHumidity;
    qreal m_absoluteHumidity;
};

QT_END_NAMESPACE
#endif
