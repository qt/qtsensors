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

#ifndef QMLSENSORGLOBAL_H
#define QMLSENSORGLOBAL_H

#include <QObject>
#include <QStringList>

QT_BEGIN_NAMESPACE

class QSensor;

class QmlSensorGlobal : public QObject
{
    Q_OBJECT
public:
    explicit QmlSensorGlobal(QObject *parent = 0);
    ~QmlSensorGlobal();

    Q_INVOKABLE QStringList sensorTypes() const;
    Q_INVOKABLE QStringList sensorsForType(const QString &type) const;
    Q_INVOKABLE QString defaultSensorForType(const QString &type) const;

Q_SIGNALS:
    void availableSensorsChanged();

private:
    QSensor *m_sensor;
};

QT_END_NAMESPACE

#endif
