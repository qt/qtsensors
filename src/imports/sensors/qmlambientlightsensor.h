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

#ifndef QMLAMBIENTLIGHTSENSOR_H
#define QMLAMBIENTLIGHTSENSOR_H

#include "qmlsensor.h"
#include <QtSensors/QAmbientLightSensor>

QT_BEGIN_NAMESPACE

class QAmbientLightSensor;

class QmlAmbientLightSensor : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlAmbientLightSensor(QObject *parent = 0);
    ~QmlAmbientLightSensor();

private:
    QSensor *sensor() const override;
    QAmbientLightSensor *m_sensor;
    QmlSensorReading *createReading() const override;

};

class QmlAmbientLightSensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(QAmbientLightReading::LightLevel lightLevel READ lightLevel NOTIFY lightLevelChanged)
public:

    explicit QmlAmbientLightSensorReading(QAmbientLightSensor *sensor);
    ~QmlAmbientLightSensorReading();

    QAmbientLightReading::LightLevel lightLevel() const;

Q_SIGNALS:
    void lightLevelChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QAmbientLightSensor *m_sensor;
    QAmbientLightReading::LightLevel m_lightLevel;
};

QT_END_NAMESPACE
#endif
