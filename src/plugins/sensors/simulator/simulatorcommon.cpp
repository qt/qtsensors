/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "simulatorcommon.h"
#include "qsensordata_simulator_p.h"
#include "mobilitysimulatorglobal.h"
#include <mobilityconnection_p.h>

#include <private/qsimulatordata_p.h>

#include <QtNetwork/QLocalSocket>

using namespace QtSimulatorPrivate;

Q_GLOBAL_STATIC(QAmbientLightReadingData, qtAmbientLightData)
Q_GLOBAL_STATIC(QLightReadingData, qtLightData)
Q_GLOBAL_STATIC(QAccelerometerReadingData, qtAccelerometerData)
Q_GLOBAL_STATIC(QMagnetometerReadingData, qtMagnetometerData)
Q_GLOBAL_STATIC(QCompassReadingData, qtCompassData)
Q_GLOBAL_STATIC(QProximityReadingData, qtProximityData)

namespace Simulator
{
    SensorsConnection::SensorsConnection(MobilityConnection *mobilityCon)
        : QObject(mobilityCon)
        , mConnection(mobilityCon)
        , mInitialDataReceived(false)
    {
        qt_registerSensorTypes();
        mobilityCon->addMessageHandler(this);
    }


    void SensorsConnection::getInitialData()
    {
        RemoteMetacall<void>::call(mConnection->sendSocket(), NoSync, "setRequestsSensors");

        while (!mInitialDataReceived) {
            mConnection->receiveSocket()->waitForReadyRead(100);
            mConnection->onReadyRead();
        }
    }

    void SensorsConnection::initialSensorsDataSent()
    {
        mInitialDataReceived = true;
    }

    void SensorsConnection::setAmbientLightData(const QAmbientLightReadingData &data)
    {
        *qtAmbientLightData() = data;
    }

    void SensorsConnection::setLightData(const QLightReadingData &data)
    {
        *qtLightData() = data;
    }

    void SensorsConnection::setAccelerometerData(const QAccelerometerReadingData &data)
    {
        *qtAccelerometerData() = data;
    }

    void SensorsConnection::setMagnetometerData(const QMagnetometerReadingData &data)
    {
        *qtMagnetometerData() = data;
    }

    void SensorsConnection::setCompassData(const QCompassReadingData &data)
    {
        *qtCompassData() = data;
    }

    void SensorsConnection::setProximityData(const QProximityReadingData &data)
    {
        *qtProximityData() = data;
    }
} // namespace

void ensureSimulatorConnection()
{
    using namespace Simulator;

    static bool connected = false;
    if (connected)
        return;

    connected = true;
    MobilityConnection *connection = MobilityConnection::instance();
    SensorsConnection *sensorsConnection = new SensorsConnection(connection);
    sensorsConnection->getInitialData();
}

SimulatorCommon::SimulatorCommon(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_timerid(0)
{
    addDataRate(1, 100);
    sensor->setDataRate(20);
    ensureSimulatorConnection();
}

void SimulatorCommon::start()
{
    if (m_timerid)
        return;

    int rate = sensor()->dataRate();
    if (rate == 0)
        rate = 20;
    int interval = 1000 / rate;
    if (interval < 0)
        interval = 1000;

    if (interval)
        m_timerid = startTimer(interval);
}

void SimulatorCommon::stop()
{
    if (m_timerid) {
        killTimer(m_timerid);
        m_timerid = 0;
    }
}

void SimulatorCommon::timerEvent(QTimerEvent * /*event*/)
{
    poll();
}

QAccelerometerReadingData get_qtAccelerometerData()
{
    return *qtAccelerometerData();
}

QMagnetometerReadingData get_qtMagnetometerData()
{
    return *qtMagnetometerData();
}

QAmbientLightReadingData get_qtAmbientLightData()
{
    return *qtAmbientLightData();
}

QLightReadingData get_qtLightData()
{
    return *qtLightData();
}

QCompassReadingData get_qtCompassData()
{
    return *qtCompassData();
}

QProximityReadingData get_qtProximityData()
{
    return *qtProximityData();
}

#include "moc_simulatorcommon.cpp"
