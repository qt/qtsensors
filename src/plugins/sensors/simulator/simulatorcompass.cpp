/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#include "simulatorcompass.h"
#include <QDebug>
#include <QtGlobal>

const char *SimulatorCompass::id("Simulator.Compass");

SimulatorCompass::SimulatorCompass(QSensor *sensor)
    : SimulatorCommon(sensor)
{
    setReading<QCompassReading>(&m_reading);
}

void SimulatorCompass::poll()
{
    QtMobility::QCompassReadingData data = SensorsConnection::instance()->qtCompassData;
    quint64 newTimestamp;
    if (!data.timestamp.isValid())
        newTimestamp = static_cast<quint64>(QDateTime::currentMSecsSinceEpoch()) / 1000;
    else
        newTimestamp = static_cast<quint64>(data.timestamp.toSecsSinceEpoch());
    if (m_reading.azimuth() != data.azimuth
        || m_reading.calibrationLevel() != data.calibrationLevel) {
            m_reading.setTimestamp(newTimestamp);
            m_reading.setAzimuth(data.azimuth);
            m_reading.setCalibrationLevel(data.calibrationLevel);

            newReadingAvailable();
    }
}

