// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtCore/private/qohoslogger_p.h>
#include <QtSensors/qsensormanager.h>
#include <QtSensors/qsensorplugin.h>
#include <ohosaccelerometerbackend.h>
#include <ohosgyroscopebackend.h>
#include <ohoslightsensorbackend.h>
#include <ohosmagnetometerbackend.h>
#include <ohosrotationsensorbackend.h>
#include <ohossensorsmanager.h>
#include <ohossensorutils.h>

class QOhosSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)

public:
    void registerSensors() override;
    QSensorBackend *createBackend(QSensor *sensor) override;
};

void QOhosSensorPlugin::registerSensors()
{
    for (auto ohosSensorType : OhosSensorsManager::instance()->getAvailableSensorsTypes()) {
        auto *qtSensorType = tryMapOhosToQtSensorType(ohosSensorType);
        if (qtSensorType != nullptr) {
            QSensorManager::registerBackend(qtSensorType, QByteArray::number(ohosSensorType), this);
        } else {
            qOhosPrintfWarning(
                "%s: cannot match ohos sensor type: %d to Qt type, ignore this sensor",
                Q_FUNC_INFO, ohosSensorType);
        }
    }
}

QSensorBackend *QOhosSensorPlugin::createBackend(QSensor *sensor)
{
    int type = sensor->identifier().toInt();
    switch (type) {
    case ::SENSOR_TYPE_ACCELEROMETER:
        return new OhosAccelerometerBackend(sensor);
    case ::SENSOR_TYPE_GYROSCOPE:
        return new OhosGyroscopeBackend(sensor);
    case ::SENSOR_TYPE_AMBIENT_LIGHT:
        return new OhosLightSensorBackend(sensor);
    case ::SENSOR_TYPE_MAGNETIC_FIELD:
        return new OhosMagnetometerBackend(sensor);
    case ::SENSOR_TYPE_ORIENTATION:
        return new OhosRotationSensorBackend(sensor);
    }
    return nullptr;
}

#include "main.moc"
