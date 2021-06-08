/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/QList>
#include "qsensorbackend.h"

typedef QSensorBackend* (*CreateFunc) (QSensor *sensor);
class Record
{
public:
    QByteArray type;
    CreateFunc func;
};
static QList<Record> records;

static bool registerTestBackend(const char *className, CreateFunc func)
{
    Record record;
    record.type = className;
    record.func = func;
    records << record;
    return true;
}

#define REGISTER_TOO
#include "test_backends.h"
#include <QDebug>

// The sensor-to-backend mapping is maintained in order to be able to change
// the sensor reading values in the backend
static QMap<QSensor*, QSensorBackend*> sensorToBackend;

void set_test_backend_busy(QSensor* sensor, bool busy)
{
    Q_ASSERT(sensor->isConnectedToBackend());
    QSensorBackend* backend = sensorToBackend.value(sensor);
    backend->sensorBusy(busy);
}

void set_test_backend_reading(QSensor* sensor, const QJsonObject& values)
{
    Q_ASSERT(sensor->isConnectedToBackend());
    QSensorBackend* backend = sensorToBackend.value(sensor);
    backend->reading()->setTimestamp(values["timestamp"].toInt()); // timestamp is common to all
    if (sensor->type() == "QAccelerometer") {
        QAccelerometerReading* reading = static_cast<QAccelerometerReading*>(backend->reading());
        reading->setX(values["x"].toDouble());
        reading->setY(values["y"].toDouble());
        reading->setZ(values["z"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QPressureSensor") {
        QPressureReading* reading = static_cast<QPressureReading*>(backend->reading());
        reading->setPressure(values["pressure"].toDouble());
        reading->setTemperature(values["temperature"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QGyroscope") {
        QGyroscopeReading* reading = static_cast<QGyroscopeReading*>(backend->reading());
        reading->setX(values["x"].toDouble());
        reading->setY(values["y"].toDouble());
        reading->setZ(values["z"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QTapSensor") {
        QTapReading* reading = static_cast<QTapReading*>(backend->reading());
        reading->setDoubleTap(values["doubleTap"].toBool());
        reading->setTapDirection(QTapReading::TapDirection(values["tapDirection"].toInt()));
        backend->newReadingAvailable();
    } else if (sensor->type() == "QCompass") {
        QCompassReading* reading = static_cast<QCompassReading*>(backend->reading());
        reading->setAzimuth(values["azimuth"].toDouble());
        reading->setCalibrationLevel(values["calibrationLevel"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QProximitySensor") {
        QProximityReading* reading = static_cast<QProximityReading*>(backend->reading());
        reading->setClose(values["near"].toBool());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QOrientationSensor") {
        QOrientationReading* reading = static_cast<QOrientationReading*>(backend->reading());
        reading->setOrientation(QOrientationReading::Orientation(values["orientation"].toInt()));
        backend->newReadingAvailable();
    } else if (sensor->type() == "QDistanceSensor") {
        QDistanceReading* reading = static_cast<QDistanceReading*>(backend->reading());
        reading->setDistance(values["distance"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QAmbientLightSensor") {
        QAmbientLightReading* reading = static_cast<QAmbientLightReading*>(backend->reading());
        reading->setLightLevel(QAmbientLightReading::LightLevel(values["lightLevel"].toInt()));
        backend->newReadingAvailable();
    } else if (sensor->type() == "QMagnetometer") {
        QMagnetometerReading* reading = static_cast<QMagnetometerReading*>(backend->reading());
        reading->setX(values["x"].toDouble());
        reading->setY(values["y"].toDouble());
        reading->setZ(values["z"].toDouble());
        reading->setCalibrationLevel(values["calibrationLevel"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QLidSensor") {
        QLidReading* reading = static_cast<QLidReading*>(backend->reading());
        reading->setBackLidClosed(values["backLidClosed"].toBool());
        reading->setFrontLidClosed(values["frontLidClosed"].toBool());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QTiltSensor") {
        QTiltReading* reading = static_cast<QTiltReading*>(backend->reading());
        reading->setYRotation(values["yRotation"].toDouble());
        reading->setXRotation(values["xRotation"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QRotationSensor") {
        QRotationReading* reading = static_cast<QRotationReading*>(backend->reading());
        reading->setFromEuler(values["x"].toDouble(), values["y"].toDouble(), values["z"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QHumiditySensor") {
        QHumidityReading* reading = static_cast<QHumidityReading*>(backend->reading());
        reading->setRelativeHumidity(values["relativeHumidity"].toDouble());
        reading->setAbsoluteHumidity(values["absoluteHumidity"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QHolsterSensor") {
        QHolsterReading* reading = static_cast<QHolsterReading*>(backend->reading());
        reading->setHolstered(values["holstered"].toBool());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QAmbientTemperatureSensor") {
        QAmbientTemperatureReading* reading = static_cast<QAmbientTemperatureReading*>(backend->reading());
        reading->setTemperature(values["temperature"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QLightSensor") {
        QLightReading* reading = static_cast<QLightReading*>(backend->reading());
        reading->setLux(values["illuminance"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QAltimeter") {
        QAltimeterReading* reading = static_cast<QAltimeterReading*>(backend->reading());
        reading->setAltitude(values["altitude"].toDouble());
        backend->newReadingAvailable();
    } else if (sensor->type() == "QIRProximitySensor") {
        QIRProximityReading* reading = static_cast<QIRProximityReading*>(backend->reading());
        reading->setReflectance(values["reflectance"].toDouble());
        backend->newReadingAvailable();
    } else {
        qWarning() << "Unsupported test sensor backend:" << sensor->type();
    }
}

class BackendFactory : public QSensorBackendFactory
{
    QSensorBackend *createBackend(QSensor *sensor) override
    {
        for (const Record &record : records) {
            if (sensor->identifier() == record.type) {
                QSensorBackend* backend = record.func(sensor);
                sensorToBackend.insert(sensor, backend);
                return backend;
            }
        }
        return nullptr;
    }
};
static BackendFactory factory;

void register_test_backends()
{
    sensorToBackend.clear();
    for (const Record &record : records)
        QSensorManager::registerBackend(record.type, record.type, &factory);
}

void unregister_test_backends()
{
    sensorToBackend.clear();
    for (const Record &record : records)
        QSensorManager::unregisterBackend(record.type, record.type);
}
