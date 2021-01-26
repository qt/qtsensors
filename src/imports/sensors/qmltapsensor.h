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

#ifndef QMLTAPSENSOR_H
#define QMLTAPSENSOR_H

#include "qmlsensor.h"
#include <QtSensors/QTapSensor>

QT_BEGIN_NAMESPACE

class QTapSensor;

class QmlTapSensor : public QmlSensor
{
    Q_OBJECT
    Q_PROPERTY(bool returnDoubleTapEvents READ returnDoubleTapEvents WRITE setReturnDoubleTapEvents NOTIFY returnDoubleTapEventsChanged)
public:
    explicit QmlTapSensor(QObject *parent = 0);
    ~QmlTapSensor();

    bool returnDoubleTapEvents() const;
    void setReturnDoubleTapEvents(bool ret);

Q_SIGNALS:
    void returnDoubleTapEventsChanged(bool returnDoubleTapEvents);

private:
    QSensor *sensor() const override;
    QTapSensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class QmlTapSensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(QTapReading::TapDirection tapDirection READ tapDirection NOTIFY tapDirectionChanged)
    Q_PROPERTY(bool doubleTap READ isDoubleTap NOTIFY isDoubleTapChanged)
public:

    explicit QmlTapSensorReading(QTapSensor *sensor);
    ~QmlTapSensorReading();

    QTapReading::TapDirection tapDirection() const;
    bool isDoubleTap() const;

Q_SIGNALS:
    void tapDirectionChanged();
    void isDoubleTapChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QTapSensor *m_sensor;
    QTapReading::TapDirection m_tapDirection;
    bool m_isDoubleTap;
};

QT_END_NAMESPACE
#endif
