/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QMLIRPROXIMITYSENSOR_P_H
#define QMLIRPROXIMITYSENSOR_P_H

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

class QIRProximitySensor;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlIRProximitySensor : public QmlSensor
{
    Q_OBJECT
    QML_NAMED_ELEMENT(IRProximitySensor)
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlIRProximitySensor(QObject *parent = 0);
    ~QmlIRProximitySensor();

    QSensor *sensor() const override;

private:
    QIRProximitySensor *m_sensor;
    QmlSensorReading *createReading() const override;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlIRProximitySensorReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal reflectance READ reflectance
               NOTIFY reflectanceChanged BINDABLE bindableReflectance)
    QML_NAMED_ELEMENT(IRProximityReading)
    QML_UNCREATABLE("Cannot create IRProximityReading")
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlIRProximitySensorReading(QIRProximitySensor *sensor);
    ~QmlIRProximitySensorReading();

    qreal reflectance() const;
    QBindable<qreal> bindableReflectance() const;

Q_SIGNALS:
    void reflectanceChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QIRProximitySensor *m_sensor;
    Q_OBJECT_BINDABLE_PROPERTY(QmlIRProximitySensorReading, qreal,
                               m_reflectance, &QmlIRProximitySensorReading::reflectanceChanged)
};

QT_END_NAMESPACE
#endif
