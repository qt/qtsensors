/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    SimulatorSensorPlugin()
    {
        SensorsConnection *connection = SensorsConnection::instance();
        if (!connection) return; // hardly likely but just in case...
        connect(connection, SIGNAL(setAvailableFeatures(quint32)), this, SLOT(setAvailableFeatures(quint32)));
    }

    void registerSensors() override
    {
        QSensorManager::registerBackend(QAccelerometer::type, SimulatorAccelerometer::id, this);
        QSensorManager::registerBackend(QAmbientLightSensor::type, SimulatorAmbientLightSensor::id, this);
        QSensorManager::registerBackend(QLightSensor::type, SimulatorLightSensor::id, this);
        QSensorManager::registerBackend(QCompass::type, SimulatorCompass::id, this);
        QSensorManager::registerBackend(QProximitySensor::type, SimulatorProximitySensor::id, this);
        QSensorManager::registerBackend(QIRProximitySensor::type, SimulatorIRProximitySensor::id, this);
        QSensorManager::registerBackend(QMagnetometer::type, SimulatorMagnetometer::id, this);
    }

    QSensorBackend *createBackend(QSensor *sensor) override
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

    // Copied from the emulator codebase
    enum Features {
        Accelerometer  = 0x01,
        Magnetometer   = 0x02,
        Compass        = 0x04,
        Infraredsensor = 0x08,
        Lightsensor    = 0x10
    };

public slots:
    void setAvailableFeatures(quint32 features)
    {
        check(features&Accelerometer,  QAccelerometer::type,      SimulatorAccelerometer::id);
        check(features&Lightsensor,    QLightSensor::type,        SimulatorLightSensor::id);
        check(features&Lightsensor,    QAmbientLightSensor::type, SimulatorAmbientLightSensor::id);
        check(features&Magnetometer,   QMagnetometer::type,       SimulatorMagnetometer::id);
        check(features&Compass,        QCompass::type,            SimulatorCompass::id);
        check(features&Infraredsensor, QIRProximitySensor::type,  SimulatorIRProximitySensor::id);
        check(features&Infraredsensor, QProximitySensor::type,    SimulatorProximitySensor::id);
    }

private:
    void check(bool test, const QByteArray &type, const QByteArray &id)
    {
        if (test) {
            if (!QSensorManager::isBackendRegistered(type, id))
                QSensorManager::registerBackend(type, id, this);
        } else {
            if (QSensorManager::isBackendRegistered(type, id))
                QSensorManager::unregisterBackend(type, id);
        }
    }
};

#include "main.moc"

