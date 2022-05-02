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
******************************************************************************/

#ifndef QMLHUMIDITYSENSOR_P_H
#define QMLHUMIDITYSENSOR_P_H

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

class QHumiditySensor;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlHumiditySensor : public QmlSensor
{
    Q_OBJECT

    QML_NAMED_ELEMENT(HumiditySensor)
    QML_ADDED_IN_VERSION(5,9)
public:
    explicit QmlHumiditySensor(QObject *parent = nullptr);
    ~QmlHumiditySensor();

    QSensor *sensor() const override;

private:
    QmlSensorReading *createReading() const override;

    QHumiditySensor *m_sensor;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlHumidityReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal relativeHumidity READ relativeHumidity
               NOTIFY relativeHumidityChanged BINDABLE bindableRelativeHumidity)
    Q_PROPERTY(qreal absoluteHumidity READ absoluteHumidity
               NOTIFY absoluteHumidityChanged BINDABLE bindableAbsoluteHumidity)
    QML_NAMED_ELEMENT(HumidityReading)
    QML_UNCREATABLE("Cannot create HumidityReading")
    QML_ADDED_IN_VERSION(5,9)
public:
    explicit QmlHumidityReading(QHumiditySensor *sensor);
    ~QmlHumidityReading();

    qreal relativeHumidity() const;
    QBindable<qreal> bindableRelativeHumidity() const;
    qreal absoluteHumidity() const;
    QBindable<qreal> bindableAbsoluteHumidity() const;

Q_SIGNALS:
    void relativeHumidityChanged();
    void absoluteHumidityChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QHumiditySensor *m_sensor;
    Q_OBJECT_BINDABLE_PROPERTY(QmlHumidityReading, qreal,
                               m_relativeHumidity, &QmlHumidityReading::relativeHumidityChanged)
    Q_OBJECT_BINDABLE_PROPERTY(QmlHumidityReading, qreal,
                               m_absoluteHumidity, &QmlHumidityReading::absoluteHumidityChanged)
};

QT_END_NAMESPACE
#endif
