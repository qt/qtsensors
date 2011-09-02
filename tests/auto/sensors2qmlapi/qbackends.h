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

#ifndef BACKENDS_H
#define BACKENDS_H

#include "qdeclaccelerometer.h"
#include "qdeclambientlightsensor.h"
#include "qdeclproximitysensor.h"
#include <qsensorplugin.h>
#include <QtCore/QDebug>


class TestSensorPlugin : public QObject,
                         public QSensorPluginInterface,
                         public QSensorChangesInterface,
                         public QSensorBackendFactory
{
    Q_OBJECT
    Q_INTERFACES(QSensorPluginInterface QSensorChangesInterface)
public:
    void registerSensors()
    {
        QSensorManager::registerBackend("QAccelerometer", "QAccelerometer", this);
        QSensorManager::registerBackend("QAmbientLightSensor", "QAmbientLightSensor", this);
        QSensorManager::registerBackend("QProximitySensor", "QProximitySensor", this);
    }

    void sensorsChanged()
    {
    }

    QSensorBackend *createBackend(QSensor *sensor)
    {
        if (sensor->identifier() == "QAccelerometer") {
            if (TestSensorPlugin::stAccel != 0)
                return TestSensorPlugin::stAccel;
            else
                TestSensorPlugin::stAccel = new QDeclAccelerometer(sensor);
            return createBackend(sensor);
        }
        else if (sensor->identifier() == "QAmbientLightSensor") {
            if (TestSensorPlugin::stAbl != 0)
                return TestSensorPlugin::stAbl;
            else
                TestSensorPlugin::stAbl = new QDeclAmbientLightSensor(sensor);
            return createBackend(sensor);
        }
        else if (sensor->identifier() == "QProximitySensor") {
            if (TestSensorPlugin::stProxi != 0)
                return TestSensorPlugin::stProxi;
            else
                TestSensorPlugin::stProxi = new QDeclProximitySensor(sensor);
            return createBackend(sensor);
        }

        qWarning() << "Can't create backend" << sensor->identifier();
        return 0;
    }
public:
    static QDeclAccelerometer* stAccel;
    static QDeclAmbientLightSensor* stAbl;
    static QDeclProximitySensor* stProxi;
};

#endif

