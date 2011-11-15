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

#include "simulatoraccelerometer.h"
#include "simulatorambientlightsensor.h"
#include "simulatorlightsensor.h"
#include "simulatorcompass.h"
#include "simulatorproximitysensor.h"
#include "simulatormagnetometer.h"
#include <QSensorPluginInterface>
#include <QSensorBackend>
#include <QSensorManager>

class SimulatorSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_INTERFACES(QSensorPluginInterface:QFactoryInterface)
public:
    void registerSensors()
    {
        QSensorManager::registerBackend(QAccelerometer::type, SimulatorAccelerometer::id, this);
        QSensorManager::registerBackend(QAmbientLightSensor::type, SimulatorAmbientLightSensor::id, this);
        QSensorManager::registerBackend(QLightSensor::type, SimulatorLightSensor::id, this);
        QSensorManager::registerBackend(QCompass::type, SimulatorCompass::id, this);
        QSensorManager::registerBackend(QProximitySensor::type, SimulatorProximitySensor::id, this);
        QSensorManager::registerBackend(QMagnetometer::type, SimulatorMagnetometer::id, this);
    }

    QSensorBackend *createBackend(QSensor *sensor)
    {
        if (sensor->identifier() == SimulatorAccelerometer::id) {
            return new SimulatorAccelerometer(sensor);
        }

        if (sensor->identifier() == SimulatorAmbientLightSensor::id) {
            return new SimulatorAmbientLightSensor(sensor);
        }

        if (sensor->identifier() == SimulatorLightSensor::id) {
            return new SimulatorLightSensor(sensor);
        }

        if (sensor->identifier() == SimulatorProximitySensor::id) {
            return new SimulatorProximitySensor(sensor);
        }

        if (sensor->identifier() == SimulatorCompass::id) {
            return new SimulatorCompass(sensor);
        }

        if (sensor->identifier() == SimulatorMagnetometer::id) {
            return new SimulatorMagnetometer(sensor);
        }

        return 0;
    }
    QStringList keys() const { return QStringList() << "simulator";}
};

Q_EXPORT_PLUGIN2(libsensors_simulator, SimulatorSensorPlugin)

#include "main.moc"

