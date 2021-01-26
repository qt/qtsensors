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

#ifndef QMLTILTSENSOR_H
#define QMLTILTSENSOR_H

#include "qmlsensor.h"
#include <QtSensors/QTiltSensor>

QT_BEGIN_NAMESPACE

class QTiltSensor;

class QmlTiltSensor : public QmlSensor
{
    Q_OBJECT
public:

    explicit QmlTiltSensor(QObject *parent = 0);
    ~QmlTiltSensor();
    Q_INVOKABLE void calibrate();

private:
    QSensor *sensor() const override;
    QTiltSensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlTiltSensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal yRotation READ yRotation NOTIFY yRotationChanged)
    Q_PROPERTY(qreal xRotation READ xRotation NOTIFY xRotationChanged)
public:
    explicit QmlTiltSensorReading(QTiltSensor *sensor);
    ~QmlTiltSensorReading();

    qreal yRotation() const;
    qreal xRotation() const;

Q_SIGNALS:
    void yRotationChanged();
    void xRotationChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QTiltSensor *m_sensor;
    qreal m_yRotation;
    qreal m_xRotation;
};

QT_END_NAMESPACE
#endif
