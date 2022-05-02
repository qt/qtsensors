/****************************************************************************
**
** Copyright (C) 2016 Canonical, Ltd
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
******************************************************************************/
#ifndef QMLLIDSENSOR_P_H
#define QMLLIDSENSOR_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qmlsensor_p.h"

QT_BEGIN_NAMESPACE

class QLidSensor;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlLidSensor : public QmlSensor
{
    Q_OBJECT
    QML_NAMED_ELEMENT(LidSensor)
    QML_ADDED_IN_VERSION(5,9)
public:
    explicit QmlLidSensor(QObject *parent = 0);
    ~QmlLidSensor();

    QSensor *sensor() const override;

private:
    QmlSensorReading *createReading() const override;

    QLidSensor *m_sensor;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlLidReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool backLidClosed READ backLidClosed
               NOTIFY backLidChanged BINDABLE bindableBackLidClosed)
    Q_PROPERTY(bool frontLidClosed READ frontLidClosed
               NOTIFY frontLidChanged BINDABLE bindableFrontLidClosed)
    QML_NAMED_ELEMENT(LidReading)
    QML_UNCREATABLE("Cannot create LidReading")
    QML_ADDED_IN_VERSION(5,9)
public:
    explicit QmlLidReading(QLidSensor *sensor);
    ~QmlLidReading();

    bool backLidClosed() const;
    QBindable<bool> bindableBackLidClosed() const;
    bool frontLidClosed() const;
    QBindable<bool> bindableFrontLidClosed() const;

Q_SIGNALS:
    void backLidChanged(bool closed);
    bool frontLidChanged(bool closed);

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QLidSensor *m_sensor;
    Q_OBJECT_BINDABLE_PROPERTY(QmlLidReading, bool,
                               m_backClosed, &QmlLidReading::backLidChanged)
    Q_OBJECT_BINDABLE_PROPERTY(QmlLidReading, bool,
                               m_frontClosed, &QmlLidReading::frontLidChanged)
};

QT_END_NAMESPACE
#endif
