// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "androidlight.h"

AndroidLight::AndroidLight(int type, QSensor *sensor, QObject *parent)
    : SensorEventQueue<QLightReading>(type, sensor, parent)
{}

void AndroidLight::dataReceived(const ASensorEvent &event)
{
    // check https://developer.android.com/reference/android/hardware/SensorEvent.html#sensor.type_light:
    if (sensor()->skipDuplicates() && qFuzzyCompare(m_reader.lux(), qreal(event.light)))
        return;

    m_reader.setTimestamp(uint64_t(event.timestamp / 1000));
    m_reader.setLux(qreal(event.light));
    newReadingAvailable();
}
