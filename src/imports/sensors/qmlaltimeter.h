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
#ifndef QMLALTIMETER_H
#define QMLALTIMETER_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QAltimeter;

class QmlAltimeter : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlAltimeter(QObject *parent = 0);
    ~QmlAltimeter();

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QAltimeter *m_sensor;
};

class QmlAltimeterReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal altitude READ altitude NOTIFY altitudeChanged)
public:
    explicit QmlAltimeterReading(QAltimeter *sensor);
    ~QmlAltimeterReading();

    qreal altitude() const;

Q_SIGNALS:
    void altitudeChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QAltimeter *m_sensor;
    qreal m_altitude;
};

QT_END_NAMESPACE
#endif
