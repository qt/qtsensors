/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsensor2ambientlight.h"
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmltype AmbientLightSensor
    \instantiates QSensor2AmbientLight
    \inherits QtSensors5::Sensor
    \inqmlmodule QtSensors 5.0
    \ingroup qml-QtSensors5
    \since QtSensors 5.0
    \brief Provides access to the current ambient light level.

    This type provides easy access to determine the ambient light by using the ambient light sensor.
    For example brightening the screen according to whether the device is in full sunlight or not.

    This type is part of the \b{QtSensors 5} module.

    The \l {Qt Sensors - QML example} is an example how to use this QML type.
*/
QSensor2AmbientLight::QSensor2AmbientLight(QObject* parent)
    : qsensor2common(parent)
    , _lightLevel(QSensor2AmbientLight::Unknown)
{
    _ambientLight = new QAmbientLightSensor(this);
    _ambientLight->addFilter(this);
}


QSensor2AmbientLight::~QSensor2AmbientLight()
{
}

/*!
    \qmlproperty enumeration QtSensors5::AmbientLightSensor::lightLevel
    Holds the ambient light level in the form of the LightLevel enum:

    \table
    \row
        \li AmbientLightSensor.Unknown
        \li Ambient light value is not set yet.
    \row
        \li AmbientLightSensor.Dark
        \li It is dark.
    \row
        \li AmbientLightSensor.Twilight
        \li It is moderately dark.
    \row
        \li AmbientLightSensor.Light
        \li It is light (internal lights).
    \row
        \li AmbientLightSensor.Bright
        \li It is bright (outside but in the shade).
    \row
        \li AmbientLightSensor.Sunny
        \li It is very bright (direct sunlight).
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
