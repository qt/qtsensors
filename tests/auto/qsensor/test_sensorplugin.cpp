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

#include "test_sensorimpl.h"
#include "test_sensor2impl.h"
#include <QtSensors/qsensorplugin.h>
#include <QtSensors/qsensorbackend.h>
#include <QtSensors/qsensormanager.h>
#include <QFile>
#include <QDebug>
#include <QTest>

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
        static bool recursive = false;
        QVERIFY2(!recursive, "Recursively called TestSensorPlugin::registerSensors!");
        if (recursive) return;
        recursive = true;

        // This is bad code. It caused a crash due to recursively calling
        // loadPlugins() in qsensormanager.cpp (because loadPlugins() did
        // not set the pluginsLoaded flag soon enough).
        (void)QSensor::defaultSensorForType(TestSensor::type);

        QSensorManager::registerBackend(TestSensor::type, testsensorimpl::id, this);
        QSensorManager::registerBackend(TestSensor::type, "test sensor 2", this);
        QSensorManager::registerBackend(TestSensor2::type, testsensor2impl::id, this);
    }

    void sensorsChanged()
    {
        // Register a new type on initial load
        // This is testing the "don't emit availableSensorsChanged() too many times" functionality.
        if (!QSensorManager::isBackendRegistered(TestSensor::type, "test sensor 3"))
            QSensorManager::registerBackend(TestSensor::type, "test sensor 3", this);

        // When a sensor of type "a random type" is registered, register another sensor.
        // This is testing the "don't emit availableSensorsChanged() too many times" functionality.
        if (!QSensor::defaultSensorForType("a random type").isEmpty()) {
            if (!QSensorManager::isBackendRegistered("a random type 2", "random.dynamic"))
                QSensorManager::registerBackend("a random type 2", "random.dynamic", this);
        } else {
            if (QSensorManager::isBackendRegistered("a random type 2", "random.dynamic"))
                QSensorManager::unregisterBackend("a random type 2", "random.dynamic");
        }
    }

    QSensorBackend *createBackend(QSensor *sensor)
    {
        if (sensor->identifier() == testsensorimpl::id) {
            return new testsensorimpl(sensor);
        }
        if (sensor->identifier() == testsensor2impl::id) {
            return new testsensor2impl(sensor);
        }

        qWarning() << "Can't create backend" << sensor->identifier();
        return 0;
    }
};

REGISTER_STATIC_PLUGIN_V2(TestSensorPlugin)

class LegacySensorPlugin : public QSensorPluginInterface
{
public:
    void registerSensors()
    {
        qWarning() << "Loaded the LegacySensorPlugin";
    }
};

REGISTER_STATIC_PLUGIN_V1(LegacySensorPlugin)

#include "test_sensorplugin.moc"

