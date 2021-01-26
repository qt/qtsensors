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

#ifndef QMLGYROSCOPE_H
#define QMLGYROSCOPE_H

#include "qmlsensor.h"

QT_BEGIN_NAMESPACE

class QGyroscope;

class QmlGyroscope : public QmlSensor
{
    Q_OBJECT
public:
    explicit QmlGyroscope(QObject *parent = 0);
    ~QmlGyroscope();


private:
    QSensor *sensor() const override;
    QGyroscope *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlGyroscopeReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z NOTIFY zChanged)
public:
    explicit QmlGyroscopeReading(QGyroscope *sensor);
    ~QmlGyroscopeReading();

    qreal x() const;
    qreal y() const;
    qreal z() const;

Q_SIGNALS:
    void xChanged();
    void yChanged();
    void zChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QGyroscope *m_sensor;
    qreal m_x;
    qreal m_y;
    qreal m_z;
};

QT_END_NAMESPACE
#endif
