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

#include "qsensor2proximity.h"
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmlclass ProximitySensor QSensor2Proximity
    \inherits QtSensors5::Sensor
    \inqmlmodule QtSensors 5
    \ingroup qml-QtSensors5
    \since QtSensors 5.0
    \brief Provides access to the proximity sensor.

    This element allows determining if something is held in close proximity to the device, such
    as determining if the user is holding the device to their ear.

    This element is part of the \b{QtSensors 5} module.

    The \l {QML Qt Sensors example} is an example how to use this QML element.

*/

QSensor2Proximity::QSensor2Proximity(QObject* parent)
    : qsensor2common(parent)
    , _near(false)
{
    _proximity = new QProximitySensor(this);
    _proximity->addFilter(this);
}

QSensor2Proximity::~QSensor2Proximity()
{
}

/*!
    \qmlproperty bool QtSensors5::ProximitySensor::near
    This property holds whether the sensor has detected something in close proximity.
    The definition of close proximity is device dependent, but it
    typically stands for a distance of 1-2 cm.
*/
bool QSensor2Proximity::near()
{
    return _near;
}

bool QSensor2Proximity::filter(QProximityReading *reading)
{
    bool cl = reading->close();
    if (_near != cl){
        _near = cl;
        emit nearChanged();
    }

    return false;
}

QT_END_NAMESPACE
