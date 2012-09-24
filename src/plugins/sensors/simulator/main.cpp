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

#include "simulatoraccelerometer.h"
#include "simulatorambientlightsensor.h"
#include "simulatorlightsensor.h"
#include "simulatorcompass.h"
#include "simulatorproximitysensor.h"
#include "simulatorirproximitysensor.h"
#include "simulatormagnetometer.h"
#include <QSensorPluginInterface>
#include <QSensorBackend>
#include <QSensorManager>

class SimulatorSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.nokia.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    void registerSensors()
    {
        QSensorManager::registerBackend(QAccelerometer::type, SimulatorAccelerometer::id, this);
        QSensorManager::registerBackend(QAmbientLightSensor::type, SimulatorAmbientLightSensor::id, this);
        QSensorManager::registerBackend(QLightSensor::type, SimulatorLightSensor::id, this);
        QSensorManager::registerBackend(QCompass::type, SimulatorCompass::id, this);
        QSensorManager::registerBackend(QProximitySensor::type, SimulatorProximitySensor::id, this);
        QSensorManager::registerBackend(QIRProximitySensor::type, SimulatorIRProximitySensor::id, this);
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

        if (sensor->identifier() == SimulatorIRProximitySensor::id) {
            return new SimulatorIRProximitySensor(sensor);
        }

        if (sensor->identifier() == SimulatorCompass::id) {
            return new SimulatorCompass(sensor);
        }

        if (sensor->identifier() == SimulatorMagnetometer::id) {
            return new SimulatorMagnetometer(sensor);
        }

        return 0;
    }
};

#include "main.moc"

