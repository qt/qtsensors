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

#include "simulatorcommon.h"
#include "qsensordata_simulator_p.h"
#include <QtSimulator/QtSimulator>
#include <QDebug>

using namespace Simulator;

Q_GLOBAL_STATIC(QtMobility::QAmbientLightReadingData, qtAmbientLightData)
Q_GLOBAL_STATIC(QtMobility::QLightReadingData, qtLightData)
Q_GLOBAL_STATIC(QtMobility::QAccelerometerReadingData, qtAccelerometerData)
Q_GLOBAL_STATIC(QtMobility::QMagnetometerReadingData, qtMagnetometerData)
Q_GLOBAL_STATIC(QtMobility::QCompassReadingData, qtCompassData)
Q_GLOBAL_STATIC(QtMobility::QProximityReadingData, qtProximityData)
Q_GLOBAL_STATIC(SensorsConnection, sensorsConnection)

SensorsConnection::SensorsConnection(QObject *parent)
    : QObject(parent)
    , mInitialDataSent(false)
{
    QtMobility::qt_registerSensorTypes();
    mConnection = new Connection(Connection::Client, "QtSimulator_Mobility_ServerName1.3.0.0", 0xbeef+1, Version(1,0,0,0), this);
    mWorker = mConnection->connectToServer(Connection::simulatorHostName(true), 0xbeef+1);
    if (!mWorker)
        qFatal("Could not connect to server");
    mWorker->addReceiver(this);
    mWorker->call("setRequestsSensors");
}

SensorsConnection::~SensorsConnection()
{
    delete mWorker;
}

void SensorsConnection::setAmbientLightData(const QtMobility::QAmbientLightReadingData &data)
{
    *qtAmbientLightData() = data;
}

void SensorsConnection::setLightData(const QtMobility::QLightReadingData &data)
{
    *qtLightData() = data;
}

void SensorsConnection::setAccelerometerData(const QtMobility::QAccelerometerReadingData &data)
{
    *qtAccelerometerData() = data;
}

void SensorsConnection::setMagnetometerData(const QtMobility::QMagnetometerReadingData &data)
{
    *qtMagnetometerData() = data;
}

void SensorsConnection::setCompassData(const QtMobility::QCompassReadingData &data)
{
    *qtCompassData() = data;
}

void SensorsConnection::setProximityData(const QtMobility::QProximityReadingData &data)
{
    *qtProximityData() = data;
}

void SensorsConnection::initialSensorsDataSent()
{
    mInitialDataSent = true;
}

SimulatorCommon::SimulatorCommon(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_timerid(0)
{
    addDataRate(1, 100);
    sensor->setDataRate(20);
    (void)sensorsConnection(); // Ensure this exists
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
    if (!sensorsConnection()->safe()) return; // wait until it's safe to read the data
    poll();
}

QtMobility::QAccelerometerReadingData get_qtAccelerometerData()
{
    return *qtAccelerometerData();
}

QtMobility::QMagnetometerReadingData get_qtMagnetometerData()
{
    return *qtMagnetometerData();
}

QtMobility::QAmbientLightReadingData get_qtAmbientLightData()
{
    return *qtAmbientLightData();
}

QtMobility::QLightReadingData get_qtLightData()
{
    return *qtLightData();
}

QtMobility::QCompassReadingData get_qtCompassData()
{
    return *qtCompassData();
}

QtMobility::QProximityReadingData get_qtProximityData()
{
    return *qtProximityData();
}

