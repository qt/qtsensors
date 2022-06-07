// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef MOCKBACKENDS_H
#define MOCKBACKENDS_H

#include "mockcommon.h"

#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>

#include <QAccelerometer>
#include <QOrientationSensor>
#include <QIRProximitySensor>
#include <QProximitySensor>

#include <QFile>
#include <QDebug>
#include <QTest>


class mockSensorPlugin : public QObject,
                         public QSensorPluginInterface,
                         public QSensorBackendFactory
{
    Q_OBJECT
  //  Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    QString m_filename;

    void registerSensors() override
    {
        qDebug() << "loaded the mock plugin";

        QSensorManager::registerBackend("QAccelerometer", mockaccelerometer::id, this);
        QSensorManager::registerBackend("QIRProximitySensor", mockirproximitysensor::id, this);
        QSensorManager::registerBackend("QOrientationSensor", mockorientationsensor::id, this);
        QSensorManager::registerBackend("QTapSensor", mocktapsensor::id, this);
        QSensorManager::registerBackend("QProximitySensor", mockproximitysensor::id, this);
    }

    void unregisterSensors()
    {
        QSensorManager::unregisterBackend("QAccelerometer", mockaccelerometer::id);
        QSensorManager::unregisterBackend("QIRProximitySensor", mockirproximitysensor::id);
        QSensorManager::unregisterBackend("QOrientationSensor", mockorientationsensor::id);
        QSensorManager::unregisterBackend("QTapSensor", mocktapsensor::id);
        QSensorManager::unregisterBackend("QProximitySensor", mockproximitysensor::id);
    }


    QSensorBackend *createBackend(QSensor *sensor) override
    {
        if (sensor->identifier() == mockaccelerometer::id) {
            return new mockaccelerometer(sensor);
        }

        if (sensor->identifier() == mockorientationsensor::id) {
            return new mockorientationsensor(sensor);
        }

        if (sensor->identifier() == mockirproximitysensor::id) {
            return  new mockirproximitysensor(sensor);
        }
        if (sensor->identifier() == mocktapsensor::id) {
             return  new mocktapsensor(sensor);
        }
        if (sensor->identifier() == mockproximitysensor::id) {
            return new mockproximitysensor(sensor);
        }

        qWarning() << "Can't create backend" << sensor->identifier();
        return 0;
    }
};

#endif
