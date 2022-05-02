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

#ifndef QMLSENSORGLOBAL_P_H
#define QMLSENSORGLOBAL_P_H

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

#include "qsensorsquickglobal_p.h"
#include <QtQml/qqml.h>
#include <QObject>
#include <QStringList>

QT_BEGIN_NAMESPACE

class QSensor;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensorGlobal : public QObject
{
    Q_OBJECT
public:
    explicit QmlSensorGlobal(QObject *parent = 0);
    ~QmlSensorGlobal();

    Q_INVOKABLE QStringList sensorTypes() const;
    Q_INVOKABLE QStringList sensorsForType(const QString &type) const;
    Q_INVOKABLE QString defaultSensorForType(const QString &type) const;
    QML_NAMED_ELEMENT(QmlSensors)
    QML_SINGLETON
    QML_ADDED_IN_VERSION(5,0)

Q_SIGNALS:
    void availableSensorsChanged();

private:
    QSensor *m_sensor;
};

QT_END_NAMESPACE

#endif
