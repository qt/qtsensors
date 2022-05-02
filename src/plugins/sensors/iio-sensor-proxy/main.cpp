/****************************************************************************
**
** Copyright (C) 2016 Alexander Volkov <a.volkov@rusbitech.ru>
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

#include "iiosensorproxyorientationsensor.h"
#include "iiosensorproxylightsensor.h"
#include "iiosensorproxycompass.h"

#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusConnectionInterface>

#include <QtCore/QFile>
#include <QtCore/QDebug>

class IIOSensorProxySensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    void registerSensors() override
    {
        if (QDBusConnection::systemBus().interface()->isServiceRegistered("net.hadess.SensorProxy")) {
            if (!QSensorManager::isBackendRegistered(QOrientationSensor::sensorType, IIOSensorProxyOrientationSensor::id))
                QSensorManager::registerBackend(QOrientationSensor::sensorType, IIOSensorProxyOrientationSensor::id, this);
            if (!QSensorManager::isBackendRegistered(QLightSensor::sensorType, IIOSensorProxyLightSensor::id))
                QSensorManager::registerBackend(QLightSensor::sensorType, IIOSensorProxyLightSensor::id, this);
            if (!QSensorManager::isBackendRegistered(QCompass::sensorType, IIOSensorProxyCompass::id))
                QSensorManager::registerBackend(QCompass::sensorType, IIOSensorProxyCompass::id, this);
        }
    }

    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == IIOSensorProxyOrientationSensor::id)
            return new IIOSensorProxyOrientationSensor(sensor);
        else if (sensor->identifier() == IIOSensorProxyLightSensor::id)
            return new IIOSensorProxyLightSensor(sensor);
        else if (sensor->identifier() == IIOSensorProxyCompass::id)
            return new IIOSensorProxyCompass(sensor);

        return 0;
    }
};

#include "main.moc"
