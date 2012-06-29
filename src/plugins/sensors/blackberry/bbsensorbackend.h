/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
** Contact: http://www.qt-project.org/
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
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef BBSENSORBACKEND_H
#define BBSENSORBACKEND_H

#include <qsensorbackend.h>
#include <QtCore/QFile>
#include <QtCore/QSocketNotifier>

// Earlier NDK versions did not ship sensor.h, that is why we have our own copy in
// here.
// We prefer the NDK version if that exists, as that is more up-to-date.
#ifdef HAVE_NDK_SENSOR_H
#include <sensor/sensor.h>
#include <devctl.h>
#include <errno.h>
#else
#include "sensor.h"
#endif

class BbSensorBackendBase : public QSensorBackend
{
    Q_OBJECT

public:
    BbSensorBackendBase(const QString &devicePath, sensor_type_e sensorType, QSensor *sensor);

    void initSensorInfo();

    void start() Q_DECL_OVERRIDE;
    void stop() Q_DECL_OVERRIDE;

protected:
    QFile& deviceFile();
    sensor_type_e sensorType() const;

    // This is called while the device file is open during initalization and gives a subclass
    // an opportunity to do additional initalization.
    virtual void additionalDeviceInit();

    // If true is returned here, initSensorInfo() will read the output range from the OS sensor
    // service and pass it to the QtSensor API.
    virtual bool addDefaultRange();

    // Converts a value from units of the OS sensor service to units needed by the QtSensors API.
    // This is used in initSensorInfo(), where the output range is read from the backend and passed
    // on to the QtSensors side.
    // One example is the magnetometer: The OS sensor service returns units in microtesla, whereas
    // QtSensors expects tesla. This function would therefore convert from microtesla to tesla.
    virtual qreal convertValue(float bbValue);

    virtual void processEvent(const sensor_event_t &sensorEvent) = 0;

    virtual bool eventFilter(QObject *object, QEvent *event);

private slots:
    void dataAvailable();
    void applyAlwaysOnProperty();
    void setPaused(bool paused);

private:
    QFile m_deviceFile;
    QScopedPointer<QSocketNotifier> m_socketNotifier;
    sensor_type_e m_sensorType;
};

template<class SensorReading>
class BbSensorBackend : public BbSensorBackendBase
{
public:
    BbSensorBackend(const QString &devicePath, sensor_type_e sensorType, QSensor *sensor)
        : BbSensorBackendBase(devicePath, sensorType, sensor)
    {
        setReading(&m_reading);
    }

protected:
    virtual bool updateReadingFromEvent(const sensor_event_t &sensorEvent, SensorReading *reading) = 0;

private:
    void processEvent(const sensor_event_t &sensorEvent)
    {
        // There may be "non-sensor" event types added later for housekeeping, so we have to check
        // if the senor type matches the expected value
        if (sensorEvent.type != sensorType())
            return;

        if (updateReadingFromEvent(sensorEvent, &m_reading)) {
            // The OS timestamp is in nanoseconds, QtMobility expects microseconds
            m_reading.setTimestamp(sensorEvent.timestamp / 1000);
            newReadingAvailable();
        }
    }

    SensorReading m_reading;
};

#endif
