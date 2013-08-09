/****************************************************************************
**
** Copyright (C) 2013 Tomasz Olszak
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

#include "tizensensorbase.h"


TizenSensorBase::TizenSensorBase(QSensor *sensor, sensor_type_e sensorType, QObject *parent):
    QSensorBackend(sensor, parent), m_sensor(0), m_sensorType(sensorType), m_supported(-1), m_sensorDescription(sensorDescription(sensorType))
{

    createSensor();
    int sensorMinRate, sensorMaxRate;
    sensor_error_e result = sensor_error_e(sensor_get_delay_boundary(m_sensorType, &sensorMinRate, &sensorMaxRate));
    if (wasError(result)) {
        TIZENSENSORLOG() << QStringLiteral("Error while getting delay boundary for %1 sensor").arg(m_sensorDescription);
        addDataRate(0, 1000);
    } else {
        addDataRate(sensorMinRate, sensorMaxRate);
    }

    float maxRange;
    float minRange;
    float resolution;
    char *vendor = 0;
    char *model = 0;
    result  = sensor_error_e(sensor_get_spec(m_sensorType, &vendor, &model, &maxRange, &minRange, &resolution));
    if (!wasError(result)) {
        addOutputRange(minRange, maxRange, resolution);
        setDescription(QString("%1 - %2").arg(vendor).arg(model));
        delete vendor;
        delete model;
    } else {
        TIZENSENSORLOG() << QStringLiteral("Error while getting %1 sensor specs").arg(m_sensorDescription);
    }

    connect(sensor, &QSensor::dataRateChanged, this, &TizenSensorBase::onDataRateChanged);
}

TizenSensorBase::~TizenSensorBase()
{
    destroySensor();
}

void TizenSensorBase::onDataRateChanged()
{

}

sensor_h TizenSensorBase::createSensor()
{
    if (m_sensor)
        return m_sensor;

    TIZENSENSORLOG() << QStringLiteral("Creating %1 sensor").arg(m_sensorDescription);
    if (isSupported()) {
        sensor_error_e result = sensor_error_e(sensor_create(&m_sensor));
        if (wasError(result)) {
            m_sensor = 0;
            printErrorMessage(QStringLiteral("Error while creating %1 sensor").arg(m_sensorDescription), result);
        }
    } else {
        qWarning() << "Device orientation sensor is not supported - can't create sensor";
    }
    return m_sensor;
}

void TizenSensorBase::destroySensor()
{
    TIZENSENSORLOG() << QStringLiteral("Destroying %1 sensor").arg(m_sensorDescription);
    if (m_sensor) {
        sensor_error_e result = sensor_error_e(sensor_destroy(m_sensor));
        printErrorMessage(QStringLiteral("Error while destroying %1 sensor").arg(m_sensorDescription), result);
    }
}

bool TizenSensorBase::isSupported()
{
    if (m_supported > -1)
        return m_supported == 1;
    m_supported = TizenSensorBase::isTizenSensorSupported(m_sensorType) ? 1 : 0;
    return m_supported;
}

bool TizenSensorBase::isTizenSensorSupported(sensor_type_e type)
{
    bool result = false;
    sensor_error_e operationResult = sensor_error_e(sensor_is_supported(type, &result));
    if (wasError(operationResult)) {
        printErrorMessage(QStringLiteral("Checking if %1 sensor is supported failed").arg(sensorDescription(type)), operationResult);
        result = false;
    }
    return result;
}


void TizenSensorBase::start()
{
    if (!createSensor())
        return;

    TIZENSENSORLOG() << QStringLiteral("Starting %1 sensor.").arg(m_sensorDescription);
    sensor_error_e result = sensor_error_e(sensor_start(m_sensor, m_sensorType));
    printErrorMessage(QStringLiteral("Error while starting %1 sensor").arg(m_sensorDescription), result);
}


void TizenSensorBase::stop()
{
    TIZENSENSORLOG() << QStringLiteral("Stopping %1 sensor").arg(m_sensorDescription);
    if (m_sensor) {
        sensor_error_e result = sensor_error_e(sensor_stop(m_sensor, m_sensorType));
        printErrorMessage(QStringLiteral("Error while stopping %1 sensor").arg(m_sensorDescription), result);
    }
}

void TizenSensorBase::printErrorMessage(QString prefix, sensor_error_e error)
{
    if (error == SENSOR_ERROR_NONE)
        return;

    switch (error) {
    case SENSOR_ERROR_INVALID_PARAMETER:
        qWarning() << prefix <<": Invalid parameter.";
        break;
    case SENSOR_ERROR_NOT_SUPPORTED:
        qWarning() << prefix <<": The sensor type is not supported in current device.";
        break;
    case SENSOR_ERROR_IO_ERROR:
        qWarning() << prefix <<": I/O error.";
        break;
    case SENSOR_ERROR_OPERATION_FAILED:
        qWarning() << prefix <<": Operation failed.";
        break;
    case SENSOR_ERROR_OUT_OF_MEMORY:
        qWarning() << prefix <<": Out of memory.";
        break;
    default:
        qWarning() << prefix <<": Undefined Error.";
        break;
    }
}

QString TizenSensorBase::sensorDescription(sensor_type_e type)
{
    switch (type) {
    case SENSOR_ACCELEROMETER:
        return QStringLiteral("Accelerometer");
    case SENSOR_GRAVITY:
        return QStringLiteral("Gravity");
    case SENSOR_LINEAR_ACCELERATION:
        return QStringLiteral("Linear acceleration");
    case SENSOR_DEVICE_ORIENTATION:
        return QStringLiteral("Device orientation");
    case SENSOR_MAGNETIC:
        return QStringLiteral("Magnetic");
    case SENSOR_ORIENTATION:
        return QStringLiteral("Orientation");
    case SENSOR_GYROSCOPE:
        return QStringLiteral("Gyroscope");
    case SENSOR_LIGHT:
        return QStringLiteral("Light");
    case SENSOR_PROXIMITY:
        return QStringLiteral("Proximity");
    case SENSOR_MOTION_SNAP:
        return QStringLiteral("Snap motion");
    case SENSOR_MOTION_SHAKE:
        return QStringLiteral("Shake motion");
    case SENSOR_MOTION_DOUBLETAP:
        return QStringLiteral("Double tap motion");
    case SENSOR_MOTION_PANNING:
        return QStringLiteral("Panning motion");
    case SENSOR_MOTION_PANNING_BROWSE:
        return QStringLiteral("Panning browse motion");
    case SENSOR_MOTION_TILT:
        return QStringLiteral("Tilt motion");
    case SENSOR_MOTION_FACEDOWN:
        return QStringLiteral("Face down motion");
    case SENSOR_MOTION_DIRECTCALL:
        return QStringLiteral("Direct call motion");
    case SENSOR_MOTION_SMART_ALERT:
        return QStringLiteral("Smart alert motion");
    case SENSOR_MOTION_NO_MOVE:
        return QStringLiteral("No motion");
    default:
        return QStringLiteral("Unknown");
    }
}
