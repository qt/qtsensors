/****************************************************************************
**
** Copyright (C) 2016 Canonical, Ltd
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
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

private:
    QSensor *sensor() const override;
    QmlSensorReading *createReading() const override;

    QLidSensor *m_sensor;
};

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlLidReading : public QmlSensorReading
{
    Q_OBJECT
    Q_PROPERTY(bool backLidChanged READ backLidChanged NOTIFY backLidChanged)
    Q_PROPERTY(bool frontLidClosed READ frontLidClosed NOTIFY frontLidChanged)
    QML_NAMED_ELEMENT(LidReading)
    QML_UNCREATABLE("Cannot create LidReading")
    QML_ADDED_IN_VERSION(5,9)
public:
    explicit QmlLidReading(QLidSensor *sensor);
    ~QmlLidReading();

    bool backLidChanged() const;
    bool frontLidClosed() const;

Q_SIGNALS:
    void backLidChanged(bool closed);
    bool frontLidChanged(bool closed);

private:
    QSensorReading *reading() const override;
    void readingUpdate() override;

    QLidSensor *m_sensor;
    bool m_backClosed;
    bool m_frontClosed;
};

QT_END_NAMESPACE
#endif
