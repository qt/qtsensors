/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsensor2common.h"
#include <QSensor>
#include <QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmlclass Sensor qsensor2common
    \inqmlmodule QtSensors 5
    \brief The Sensor element serves as a base type for sensors.

    The Sensor element serves as a base type for sensors.

    This element cannot be directly created. Please use one of the sub-classes instead.
*/

qsensor2common::qsensor2common(QObject *parent)
    : QObject(parent)
{
}

qsensor2common::~qsensor2common()
{
}

/*!
    \qmlproperty bool QtSensors5::Sensor::enabled
    Starts or stops the sensor.
*/

bool qsensor2common::enabled()
{
    return sensor()->isActive();
}

void qsensor2common::setEnabled(bool val)
{
    bool active = enabled();
    if (active != val){
        if (val){
            bool ret = sensor()->start();
            if (!ret)
                qWarning() << "couldn't start the sensor.";
        }
        else
            sensor()->stop();
        emit enabledChanged();
    }
}

/*!
    \qmlproperty bool QtSensors5::Sensor::alwaysOn
    Keeps the sensor running when the screen turns off.
*/

bool qsensor2common::alwaysOn()
{
    return sensor()->isAlwaysOn();
}

void qsensor2common::setAlwaysOn(bool alwaysOn)
{
    if (sensor()->isAlwaysOn() == alwaysOn) return;
    sensor()->setAlwaysOn(alwaysOn);
    emit alwaysOnChanged();
}

QT_END_NAMESPACE

