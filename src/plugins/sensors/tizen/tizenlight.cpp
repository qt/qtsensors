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

#include "tizenlight.h"

char const *const TizenLight::id("tizen.light");

static void tizen_light_cb(unsigned long long timestamp, float lux, void* user_data) {
    TizenLight *tizenLight = static_cast<TizenLight*>(user_data);
    Q_CHECK_PTR(tizenLight);
    tizenLight->update(timestamp, lux);
}

TizenLight::TizenLight(QSensor *sensor, QObject *parent) :
    TizenSensorBase(sensor, SENSOR_LIGHT, parent)
{
    int intervalInMs = 1000;

    if (sensor->dataRate() > 0)
        intervalInMs = 1000 / sensor->dataRate();

    setReading<QLightReading>(&m_reading);

    sensor_error_e result = sensor_error_e(sensor_light_set_cb(m_sensor, intervalInMs, tizen_light_cb, this));
    printErrorMessage(QStringLiteral("Error while setting %1 sensor callback").arg(m_sensorDescription), result);
}

TizenLight::~TizenLight()
{
    sensor_error_e result = sensor_error_e(sensor_light_unset_cb(m_sensor));
    printErrorMessage(QStringLiteral("Error while unsetting %1 sensor callback").arg(m_sensorDescription), result);
}

void TizenLight::start()
{
    TizenSensorBase::start();
    if (m_sensor) {
        float lux;
        sensor_error_e result = sensor_error_e(sensor_light_read_data(m_sensor, &lux));
        if (wasError(result)) {
            printErrorMessage(QStringLiteral("Error while getting %1 sensor data").arg(m_sensorDescription), result);
        } else {
            update(0, lux);
        }
    }
}

void TizenLight::update(quint64 timestamp, float lux)
{
    m_reading.setTimestamp(timestamp);
    m_reading.setLux(lux);
    TIZENSENSORLOG() << "lux:" << lux;
    newReadingAvailable();
}

void TizenLight::onDataRateChanged()
{
    TIZENSENSORLOG() << "Changing data rate to:" << sensor()->dataRate();
    if (m_sensor) {
        sensor_error_e result = sensor_error_e(sensor_light_set_interval(m_sensor, sensor()->dataRate()));
        printErrorMessage(QStringLiteral("Error while changing interval for %1 sensor").arg(m_sensorDescription), result);
    }
}


