/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
#include "genericorientationsensor.h"
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
#include "genericrotationsensor.h"
#endif
#ifdef QTSENSORS_GENERICALSSENSOR
#include "genericalssensor.h"
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
#include "generictiltsensor.h"
#endif
#include <QtSensors/qsensorplugin.h>
#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qsensormanager.h>
#include <QFile>
#include <QDebug>

class genericSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorChangesInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface QSensorChangesInterface)
public:
    void registerSensors() override
    {
        // Nothing to register here
    }

    void sensorsChanged() override
    {
        if (!QSensor::defaultSensorForType(QAccelerometer::sensorType).isEmpty()) {
            // There is an accelerometer available. Register the backends
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
            if (!QSensorManager::isBackendRegistered(QOrientationSensor::sensorType, genericorientationsensor::id))
                QSensorManager::registerBackend(QOrientationSensor::sensorType, genericorientationsensor::id, this);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
            if (!QSensorManager::isBackendRegistered(QRotationSensor::sensorType, genericrotationsensor::id))
                QSensorManager::registerBackend(QRotationSensor::sensorType, genericrotationsensor::id, this);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
            if (!QSensorManager::isBackendRegistered(QTiltSensor::sensorType, GenericTiltSensor::id))
                QSensorManager::registerBackend(QTiltSensor::sensorType, GenericTiltSensor::id, this);
#endif
        } else {
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
            if (QSensorManager::isBackendRegistered(QOrientationSensor::sensorType, genericorientationsensor::id))
                QSensorManager::unregisterBackend(QOrientationSensor::sensorType, genericorientationsensor::id);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
            if (QSensorManager::isBackendRegistered(QRotationSensor::sensorType, genericrotationsensor::id))
                QSensorManager::unregisterBackend(QRotationSensor::sensorType, genericrotationsensor::id);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
            if (QSensorManager::isBackendRegistered(QTiltSensor::sensorType, GenericTiltSensor::id))
                QSensorManager::unregisterBackend(QTiltSensor::sensorType, GenericTiltSensor::id);
#endif
        }

        if (!QSensor::defaultSensorForType(QLightSensor::sensorType).isEmpty()) {
#ifdef QTSENSORS_GENERICALSSENSOR
            if (!QSensorManager::isBackendRegistered(QAmbientLightSensor::sensorType, genericalssensor::id))
                QSensorManager::registerBackend(QAmbientLightSensor::sensorType, genericalssensor::id, this);
#endif
        } else {
#ifdef QTSENSORS_GENERICALSSENSOR
            if (QSensorManager::isBackendRegistered(QAmbientLightSensor::sensorType, genericalssensor::id))
                QSensorManager::unregisterBackend(QAmbientLightSensor::sensorType, genericalssensor::id);
#endif
        }
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
#ifdef QTSENSORS_GENERICORIENTATIONSENSOR
        if (sensor->identifier() == genericorientationsensor::id)
            return new genericorientationsensor(sensor);
#endif
#ifdef QTSENSORS_GENERICROTATIONSENSOR
        if (sensor->identifier() == genericrotationsensor::id)
            return new genericrotationsensor(sensor);
#endif
#ifdef QTSENSORS_GENERICALSSENSOR
        if (sensor->identifier() == genericalssensor::id)
            return new genericalssensor(sensor);
#endif
#ifdef QTSENSORS_GENERICTILTSENSOR
        if (sensor->identifier() == GenericTiltSensor::id)
            return new GenericTiltSensor(sensor);
#endif

        return 0;
    }
};

#include "main.moc"
