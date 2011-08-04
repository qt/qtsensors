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

#include "simulatorambientlightsensor.h"
#include <QDebug>
#include <QtGlobal>

const char *SimulatorAmbientLightSensor::id("Simulator.AmbientLightSensor");

SimulatorAmbientLightSensor::SimulatorAmbientLightSensor(QSensor *sensor)
    : SimulatorCommon(sensor)
{
    setReading<QAmbientLightReading>(&m_reading);
}

void SimulatorAmbientLightSensor::poll()
{
    QAmbientLightReadingData data = get_qtAmbientLightData();
    quint64 newTimestamp;
    if (!data.timestamp.isValid())
        newTimestamp = QDateTime::currentDateTime().toTime_t();
    else
        newTimestamp = data.timestamp.toTime_t();
    if (m_reading.timestamp() != newTimestamp
        || m_reading.lightLevel() != data.lightLevel) {
            m_reading.setTimestamp(newTimestamp);
            m_reading.setLightLevel(data.lightLevel);

            newReadingAvailable();
    }
}

