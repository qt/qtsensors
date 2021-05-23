/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Copyright (C) 2016 Canonical, Ltd.
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

#include "sensortagaccelerometer.h"
#include "sensortagals.h"
#include "sensortagbase.h"
#include "sensortaggyroscope.h"
#include "sensortaghumiditysensor.h"
#include "sensortaglightsensor.h"
#include "sensortagmagnetometer.h"
#include "sensortagpressuresensor.h"
#include "sensortagtemperaturesensor.h"

#include <QtSensors/qsensorplugin.h>
#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qsensormanager.h>
#include <QSettings>

class SensortagSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)

public:

    void registerSensors() override
    {
        if (!QSensorManager::isBackendRegistered(QAccelerometer::sensorType, SensorTagAccelerometer::id))
            QSensorManager::registerBackend(QAccelerometer::sensorType, SensorTagAccelerometer::id, this);

        if (!QSensorManager::isBackendRegistered(QAmbientLightSensor::sensorType, SensorTagAls::id))
            QSensorManager::registerBackend(QAmbientLightSensor::sensorType, SensorTagAls::id, this);

        if (!QSensorManager::isBackendRegistered(QLightSensor::sensorType, SensorTagLightSensor::id))
            QSensorManager::registerBackend(QLightSensor::sensorType, SensorTagLightSensor::id, this);

        if (!QSensorManager::isBackendRegistered(QAmbientTemperatureSensor::sensorType, SensorTagTemperatureSensor::id))
            QSensorManager::registerBackend(QAmbientTemperatureSensor::sensorType, SensorTagTemperatureSensor::id, this);

        if (!QSensorManager::isBackendRegistered(QHumiditySensor::sensorType, SensorTagHumiditySensor::id))
            QSensorManager::registerBackend(QHumiditySensor::sensorType, SensorTagHumiditySensor::id, this);

        if (!QSensorManager::isBackendRegistered(QPressureSensor::sensorType, SensorTagPressureSensor::id))
            QSensorManager::registerBackend(QPressureSensor::sensorType, SensorTagPressureSensor::id, this);

        if (!QSensorManager::isBackendRegistered(QGyroscope::sensorType, SensorTagGyroscope::id))
            QSensorManager::registerBackend(QGyroscope::sensorType, SensorTagGyroscope::id, this);

        if (!QSensorManager::isBackendRegistered(QMagnetometer::sensorType, SensorTagMagnetometer::id))
            QSensorManager::registerBackend(QMagnetometer::sensorType, SensorTagMagnetometer::id, this);
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == SensorTagAccelerometer::id)
            return new SensorTagAccelerometer(sensor);
        if (sensor->identifier() == SensorTagAls::id)
            return new SensorTagAls(sensor);
        if (sensor->identifier() == SensorTagLightSensor::id)
            return new SensorTagLightSensor(sensor);
        if (sensor->identifier() == SensorTagTemperatureSensor::id)
            return new SensorTagTemperatureSensor(sensor);
        if (sensor->identifier() == SensorTagHumiditySensor::id)
            return new SensorTagHumiditySensor(sensor);
        if (sensor->identifier() == SensorTagPressureSensor::id)
            return new SensorTagPressureSensor(sensor);
        if (sensor->identifier() == SensorTagGyroscope::id)
            return new SensorTagGyroscope(sensor);
        if (sensor->identifier() == SensorTagMagnetometer::id)
            return new SensorTagMagnetometer(sensor);
        return nullptr;
    }
};

#include "main.moc"
