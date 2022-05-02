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

#ifndef QMLGYROSCOPE_P_H
#define QMLGYROSCOPE_P_H

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

class QGyroscope;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlGyroscope : public QmlSensor
{
    Q_OBJECT
    QML_NAMED_ELEMENT(Gyroscope)
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlGyroscope(QObject *parent = 0);
    ~QmlGyroscope();

    QSensor *sensor() const override;

private:
    QGyroscope *m_sensor;
    QmlSensorReading *createReading() const override;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlGyroscopeReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x NOTIFY xChanged BINDABLE bindableX)
    Q_PROPERTY(qreal y READ y NOTIFY yChanged BINDABLE bindableY)
    Q_PROPERTY(qreal z READ z NOTIFY zChanged BINDABLE bindableZ)
    QML_NAMED_ELEMENT(GyroscopeReading)
    QML_UNCREATABLE("Cannot create GyroscopeReading")
    QML_ADDED_IN_VERSION(5,0)
public:
    explicit QmlGyroscopeReading(QGyroscope *sensor);
    ~QmlGyroscopeReading();

    qreal x() const;
    QBindable<qreal> bindableX() const;
    qreal y() const;
    QBindable<qreal> bindableY() const;
    qreal z() const;
    QBindable<qreal> bindableZ() const;

Q_SIGNALS:
    void xChanged();
    void yChanged();
    void zChanged();

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;
    QGyroscope *m_sensor;
    Q_OBJECT_BINDABLE_PROPERTY(QmlGyroscopeReading, qreal,
                               m_x, &QmlGyroscopeReading::xChanged)
    Q_OBJECT_BINDABLE_PROPERTY(QmlGyroscopeReading, qreal,
                               m_y, &QmlGyroscopeReading::yChanged)
    Q_OBJECT_BINDABLE_PROPERTY(QmlGyroscopeReading, qreal,
                               m_z, &QmlGyroscopeReading::zChanged)
};

QT_END_NAMESPACE
#endif
