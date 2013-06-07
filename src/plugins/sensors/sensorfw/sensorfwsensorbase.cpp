/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
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

#include "sensorfwsensorbase.h"


SensorManagerInterface* SensorfwSensorBase::m_remoteSensorManager = 0;

//According to wikipedia link http://en.wikipedia.org/wiki/Standard_gravity
//const float sensorfwsensorbase::GRAVITY_EARTH = 9.812865328;
const float SensorfwSensorBase::GRAVITY_EARTH_THOUSANDTH = 0.009812865328;
const int SensorfwSensorBase::KErrNotFound=-1;
const int SensorfwSensorBase::KErrInUse=-14;
QStringList SensorfwSensorBase::m_bufferingSensors = QStringList()
        <<"sensorfw.accelerometer"<<"sensorfw.magnetometer"
       <<"sensorfw.gyroscope"<<"sensorfw.rotationsensor";

SensorfwSensorBase::SensorfwSensorBase(QSensor *sensor)
    : QSensorBackend(sensor), m_sensorInterface(0), m_bufferSize(-1), m_prevOutputRange(0), m_efficientBufferSize(1), m_maxBufferSize(1)
{
    if (!m_remoteSensorManager)
        m_remoteSensorManager = &SensorManagerInterface::instance();
}

SensorfwSensorBase::~SensorfwSensorBase()
{
    if (m_sensorInterface) {
        stop();
        delete m_sensorInterface, m_sensorInterface = 0;
    }
}

void SensorfwSensorBase::start()
{
    if (m_sensorInterface) {
        // dataRate
        QByteArray type = sensor()->type();
        if (type != QTapSensor::type && type != QProximitySensor::type) {
            int dataRate = sensor()->dataRate();
            int interval = dataRate > 0 ? 1000 / dataRate : 0;
            // for testing maximum speed
            //interval = 1;
            //dataRate = 1000;
            m_sensorInterface->setInterval(interval);
        }

        // outputRange
        int currentRange = sensor()->outputRange();
        int l = sensor()->outputRanges().size();
        if (l > 1) {
            if (currentRange != m_prevOutputRange) {
//#ifdef Q_WS_MAEMO_6
                bool isOk = m_sensorInterface->setDataRangeIndex(currentRange); //NOTE THAT THE CHANGE MIGHT NOT SUCCEED, FIRST COME FIRST SERVED
                if (!isOk) sensorError(KErrInUse);
                else m_prevOutputRange = currentRange;
//#else
//                // TODO: remove when sensord integrated, in sensorfw env there is a delay
//                qoutputrange range = sensor()->outputRanges().at(currentRange);
//                qreal correction = 1/correctionFactor();
//                DataRange range1(range.minimum*correction, range.maximum*correction, range.accuracy*correction);
//                m_sensorInterface->requestDataRange(range1);
//                m_prevOutputRange = currentRange;
//#endif
            }
        }

        // always on
        bool alwaysOn = sensor()->isAlwaysOn();
        m_sensorInterface->setStandbyOverride(alwaysOn);

        // connects after buffering checks
        doConnectAfterCheck();

        int returnCode = m_sensorInterface->start().error().type();
        if (returnCode == 0) return;
        qWarning() << "m_sensorInterface did not start, error code:" << returnCode;
    }
    sensorStopped();
}

void SensorfwSensorBase::stop()
{
    if (m_sensorInterface) m_sensorInterface->stop();
}

void SensorfwSensorBase::setRanges(qreal correctionFactor)
{
    if (!m_sensorInterface) return;

    QList<DataRange> ranges = m_sensorInterface->getAvailableDataRanges();

    for (int i = 0, l = ranges.size(); i < l; i++) {
        DataRange range = ranges.at(i);
        qreal rangeMin = range.min * correctionFactor;
        qreal rangeMax = range.max * correctionFactor;
        qreal resolution = range.resolution * correctionFactor;
        addOutputRange(rangeMin, rangeMax, resolution);
    }
}


bool SensorfwSensorBase::doConnectAfterCheck()
{
    if (!m_sensorInterface) return false;

    // buffer size
    int size = bufferSize();
    if (size == m_bufferSize) return true;

    if (m_bufferingSensors.contains(sensor()->identifier()))
        m_sensorInterface->setBufferSize(size);
    else
        size = 1;

    // if multiple->single or single->multiple or if uninitialized
    if ((m_bufferSize > 1 && size == 1) || (m_bufferSize == 1 && size > 1) || m_bufferSize == -1) {
        m_bufferSize = size;
        disconnect(this);
        if (!doConnect()) {
            qWarning() << "Unable to connect "<< sensorName();
            return false;
        }
        return true;
    }
    m_bufferSize = size;
    return true;
}

int SensorfwSensorBase::bufferSize() const
{
    int bufferSize = sensor()->bufferSize();
    if (bufferSize == 1)
        return 1;

    // otherwise check validit
    if (bufferSize < 1) {
        qWarning() << "bufferSize cannot be " << bufferSize << ", must be a positive number >= 1";
        return 1;
    }
    if (bufferSize > m_maxBufferSize) {
        qWarning() << "bufferSize cannot be " << bufferSize << ", MAX value is " << m_maxBufferSize;
        return m_maxBufferSize;
    }
    return bufferSize;
}

qreal SensorfwSensorBase::correctionFactor() const
{
    return 1;
}

