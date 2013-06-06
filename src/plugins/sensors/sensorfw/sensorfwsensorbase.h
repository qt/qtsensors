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


#ifndef SENSORFWSENSORBASE_H
#define SENSORFWSENSORBASE_H

#include <qsensorbackend.h>
#include <sensormanagerinterface.h>
#include <abstractsensor_i.h>

#include <QAmbientLightSensor>
#include <QIRProximitySensor>
#include <QTapSensor>
#include <QProximitySensor>

class SensorfwSensorBase : public QSensorBackend
{
public:
    SensorfwSensorBase(QSensor *sensor);
    virtual ~SensorfwSensorBase();


protected:
    virtual bool doConnect()=0;
    virtual void start();
    virtual void stop();

    static const float GRAVITY_EARTH;
    static const float GRAVITY_EARTH_THOUSANDTH;    //for speed
    static const int KErrNotFound;
    static const int KErrInUse;
    static QStringList m_bufferingSensors;

    void setRanges(qreal correctionFactor=1);
    virtual QString sensorName() const=0;

    template<typename T>
    void initSensor(bool &initDone)
    {

        const QString name = sensorName();

        if (!initDone) {
            if (!m_remoteSensorManager->loadPlugin(name)) {
                sensorError(KErrNotFound);
                return;
            }
            m_remoteSensorManager->registerSensorInterface<T>(name);
        }
        m_sensorInterface = T::controlInterface(name);
        if (!m_sensorInterface) {
            m_sensorInterface = const_cast<T*>(T::listenInterface(name));
        }
        if (!m_sensorInterface) {
            sensorError(KErrNotFound);
            return;
        }
        if (!m_sensorInterface) {
            sensorError(KErrNotFound);
            return;
        }

        initDone = true;

        //metadata
        QList<DataRange> intervals = m_sensorInterface->getAvailableIntervals();

        for (int i = 0, l = intervals.size(); i < l; i++) {
            qreal intervalMax = ((DataRange)(intervals.at(i))).max;
            qreal intervalMin =((DataRange)(intervals.at(i))).min;

            if (intervalMin == 0 && intervalMax == 0) {
                // 0 interval has different meanings in e.g. magge/acce
                // magge -> best-effort
                // acce -> lowest possible
                // in Qt API setting 0 means default
                continue;
            }

            qreal rateMin = intervalMax < 1 ? 1 : 1 / intervalMax * 1000;
            rateMin = rateMin < 1 ? 1 : rateMin;

            intervalMin = intervalMin < 1 ? 10: intervalMin;     // do not divide with 0
            qreal rateMax = 1 / intervalMin * 1000;
            addDataRate(rateMin, rateMax);
        }

        //bufferSizes
        if (m_bufferingSensors.contains(sensor()->identifier())) {

            IntegerRangeList sizes = m_sensorInterface->getAvailableBufferSizes();
            int l = sizes.size();
            for (int i = 0; i < l; i++) {
                int second = sizes.at(i).second;
                m_maxBufferSize = second > m_bufferSize ? second : m_maxBufferSize;
            }
            m_maxBufferSize = m_maxBufferSize < 0 ? 1 : m_maxBufferSize;
            //SensorFW guarantees to provide the most efficient size first
            //TODO: remove from comments
            //m_efficientBufferSize  = m_sensorInterface->hwBuffering()? (l>0?sizes.at(0).first:1) : 1;
        }
        else
            m_maxBufferSize = 1;

        sensor()->setMaxBufferSize(m_maxBufferSize);
        sensor()->setEfficientBufferSize(m_efficientBufferSize);

        QByteArray type = sensor()->type();
        if (type == QAmbientLightSensor::type) return;   // SensorFW returns lux values, plugin enumerated values
        if (type == QIRProximitySensor::type) return;    // SensorFW returns raw reflectance values, plugin % of max reflectance
        if (name == "accelerometersensor") return;      // SensorFW returns milliGs, plugin m/s^2
        if (name == "magnetometersensor") return;       // SensorFW returns nanoTeslas, plugin Teslas
        if (name == "gyroscopesensor") return;          // SensorFW returns DSPs, plugin milliDSPs

        setDescription(m_sensorInterface->description());

        if (name == "tapsensor") return;
        setRanges();
    };


    AbstractSensorChannelInterface* m_sensorInterface;
    int m_bufferSize;
    int bufferSize() const;
    virtual qreal correctionFactor() const;

private:

    static SensorManagerInterface* m_remoteSensorManager;
    int m_prevOutputRange;
    bool doConnectAfterCheck();
    int m_efficientBufferSize, m_maxBufferSize;

};

#endif
