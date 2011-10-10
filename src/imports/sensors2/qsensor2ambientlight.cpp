/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsensor2ambientlight.h"
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmlclass AmbientLightSensor QSensor2AmbientLight
    \inqmlmodule QtSensors 5
    \ingroup qml-QtSensors5
    \since QtSensors 5.0
    \brief The AmbientLightSensor element provide an easy access to determine the ambient light by using the ambient light sensor.

    This element is part of the \bold{QtSensors 5} module.
*/
QSensor2AmbientLight::QSensor2AmbientLight(QObject* parent)
    : QObject(parent)
    , _lightLevel(QSensor2AmbientLight::Unknown)
{
    _ambientLight = new QAmbientLightSensor(this);
    _ambientLight->addFilter(this);
}


QSensor2AmbientLight::~QSensor2AmbientLight()
{
}

/*!
    \qmlproperty bool QtSensors5::QSensor2AmbientLight::enabled
    This property can be used to activate or deactivate the sensor.
*/
bool QSensor2AmbientLight::enabled()
{
    return _ambientLight->isActive();
}

void QSensor2AmbientLight::setEnabled(bool val)
{
    bool active = enabled();
    if (active != val){
        if (val){
            bool ret = _ambientLight->start();
            if (!ret)
                qWarning() << "couldn't start the sensor.";
        }
        else
            _ambientLight->stop();
        emit enabledChanged();
    }
}

/*!
    \qmlproperty enumeration QtSensors5::AmbientLightSensor::lightLevel
    Holds the ambient light level in the form of the LightLevel enum:

    \table
    \row
        \o AmbientLightSensor.Unknown
        \o Ambient light value is not set yet.
    \row
        \o AmbientLightSensor.Dark
        \o It is dark.
    \row
        \o AmbientLightSensor.Twilight
        \o It is moderately dark.
    \row
        \o AmbientLightSensor.Light
        \o It is light (eg. internal lights).
    \row
        \o AmbientLightSensor.Bright
        \o It is bright (eg. shade).
    \row
        \o AmbientLightSensor.Sunny
        \o It is very bright (eg. direct sunlight).
    \endtable
*/
QSensor2AmbientLight::LightLevel QSensor2AmbientLight::lightLevel()
{
    return _lightLevel;
}

bool QSensor2AmbientLight::filter(QAmbientLightReading *reading)
{
    QSensor2AmbientLight::LightLevel lv = (QSensor2AmbientLight::LightLevel)reading->lightLevel();
    if (lv != _lightLevel){
        _lightLevel = lv;
        emit lightLevelChanged();
    }
    return false;
}

QT_END_NAMESPACE
