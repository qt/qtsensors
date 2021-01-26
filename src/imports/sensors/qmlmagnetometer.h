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

#ifndef QMLMAGNETOMETER_H
#define QMLMAGNETOMETER_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QMagnetometer;

class QmlMagnetometer : public QmlSensor
{
    Q_OBJECT
    Q_PROPERTY(bool returnGeoValues READ returnGeoValues WRITE setReturnGeoValues NOTIFY returnGeoValuesChanged)
public:
    explicit QmlMagnetometer(QObject *parent = 0);
    ~QmlMagnetometer();

    bool returnGeoValues() const;
    void setReturnGeoValues(bool geo);

Q_SIGNALS:
    void returnGeoValuesChanged(bool returnGeoValues);

private:
    QSensor *sensor() const override;
    QMagnetometer *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlMagnetometerReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z NOTIFY zChanged)
    Q_PROPERTY(qreal calibrationLevel READ calibrationLevel NOTIFY calibrationLevelChanged)
public:
    explicit QmlMagnetometerReading(QMagnetometer *sensor);
    ~QmlMagnetometerReading();

    qreal x() const;
    qreal y() const;
    qreal z() const;
    qreal calibrationLevel() const;

Q_SIGNALS:
    void xChanged();
    void yChanged();
    void zChanged();
    void calibrationLevelChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QMagnetometer *m_sensor;
    qreal m_x;
    qreal m_y;
    qreal m_z;
    qreal m_calibrationLevel;
};

QT_END_NAMESPACE
#endif
