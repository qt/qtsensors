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

#ifndef QMLCOMPASS_P_H
#define QMLCOMPASS_P_H

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

class QCompass;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlCompass : public QmlSensor
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Compass)
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlCompass(QObject *parent = 0);
    ~QmlCompass();

    QSensor *sensor() const override;

private:
    QCompass *m_sensor;
    QmlSensorReading *createReading() const override;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlCompassReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal azimuth READ azimuth NOTIFY azimuthChanged BINDABLE bindableAzimuth)
    Q_PROPERTY(qreal calibrationLevel READ calibrationLevel
               NOTIFY calibrationLevelChanged BINDABLE bindableCalibrationLevel)
    QML_NAMED_ELEMENT(CompassReading)
    QML_UNCREATABLE("Cannot create CompassReading")
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlCompassReading(QCompass *sensor);
    ~QmlCompassReading();

    qreal azimuth() const;
    QBindable<qreal> bindableAzimuth() const;
    qreal calibrationLevel() const;
    QBindable<qreal> bindableCalibrationLevel() const;

Q_SIGNALS:
    void azimuthChanged();
    void calibrationLevelChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QCompass *m_sensor;
    Q_OBJECT_BINDABLE_PROPERTY(QmlCompassReading, qreal,
                               m_azimuth, &QmlCompassReading::azimuthChanged)
    Q_OBJECT_BINDABLE_PROPERTY(QmlCompassReading, qreal,
                               m_calibrationLevel, &QmlCompassReading::calibrationLevelChanged)
};

QT_END_NAMESPACE
#endif
