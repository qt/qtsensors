/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
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
#ifndef QMLHOLSTERSENSOR_H
#define QMLHOLSTERSENSOR_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QHolsterSensor;

class QmlHolsterSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlHolsterSensor(QObject *parent = 0);
    ~QmlHolsterSensor();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QHolsterSensor *m_sensor;
};

class QmlHolsterReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool holstered READ holstered NOTIFY holsteredChanged)
public:
    explicit QmlHolsterReading(QHolsterSensor *sensor);
    ~QmlHolsterReading();

    bool holstered() const;

Q_SIGNALS:
    void holsteredChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QHolsterSensor *m_sensor;
    bool m_holstered;
};

QT_END_NAMESPACE
#endif
