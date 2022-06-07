// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "gruesensorimpl.h"
#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>
#include <QFile>
#include <QDebug>

class GrueSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorChangesInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface QSensorChangesInterface)
public:
    void registerSensors() override
    {
    }

    void sensorsChanged() override
    {
        if (!QSensor::defaultSensorForType(QAmbientLightSensor::sensorType).isEmpty()) {
            // There is a light sensor available. Register the backend
            if (!QSensorManager::isBackendRegistered(GrueSensor::sensorType, gruesensorimpl::id))
                QSensorManager::registerBackend(GrueSensor::sensorType, gruesensorimpl::id, this);
        } else {
            if (QSensorManager::isBackendRegistered(GrueSensor::sensorType, gruesensorimpl::id))
                QSensorManager::unregisterBackend(GrueSensor::sensorType, gruesensorimpl::id);
        }
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == gruesensorimpl::id)
            return new gruesensorimpl(sensor);

        return 0;
    }
};

#include "main.moc"
