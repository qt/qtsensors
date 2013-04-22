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

#include "qsensorbackend.h"
#include "qsensor_p.h"
#include <QDebug>

QT_BEGIN_NAMESPACE

/*!
    \class QSensorBackend
    \ingroup sensors_backend
    \inmodule QtSensors

    \brief The QSensorBackend class is a sensor implementation.

    Sensors on a device will be represented by sub-classes of
    QSensorBackend.
*/

/*!
    \internal
*/
QSensorBackend::QSensorBackend(QSensor *sensor)
    : m_sensor(sensor)
{
}

/*!
    \internal
*/
QSensorBackend::~QSensorBackend()
{
}

/*!
   Checks whether a feature is supported by this sensor backend.

   This is the backend side of QSensor::isFeatureSupported(). Reimplement this function if the
   backend supports one of the additional sensor features of QSensor::Feature.

   Returns whether the feature \a feature is supported by this backend. The default implementation returns false.
   \since 5.0
 */
bool QSensorBackend::isFeatureSupported(QSensor::Feature feature) const
{
    Q_UNUSED(feature);
    return false;
}

/*!
    Notify the QSensor class that a new reading is available.
*/
void QSensorBackend::newReadingAvailable()
{
    QSensorPrivate *d = m_sensor->d_func();

    // Copy the values from the device reading to the filter reading
    d->filter_reading->copyValuesFrom(d->device_reading);

    for (QFilterList::const_iterator it = d->filters.constBegin(); it != d->filters.constEnd(); ++it) {
        QSensorFilter *filter = (*it);
        if (!filter->filter(d->filter_reading))
            return;
    }

    // Copy the values from the filter reading to the cached reading
    d->cache_reading->copyValuesFrom(d->filter_reading);

    Q_EMIT m_sensor->readingChanged();
}

/*!
    \fn QSensorBackend::start()

    Start reporting values.
*/

/*!
    \fn QSensorBackend::stop()

    Stop reporting values.
*/

/*!
    If the backend has lost its reference to the reading
    it can call this method to get the address.

    Note that you will need to down-cast to the appropriate
    type.

    \sa setReading()
*/
QSensorReading *QSensorBackend::reading() const
{
    QSensorPrivate *d = m_sensor->d_func();
    return d->device_reading;
}

/*!
    Returns the sensor front end associated with this backend.
*/
QSensor *QSensorBackend::sensor() const
{
    return m_sensor;
}

/*!
    \fn QSensorBackend::setReading(T *reading)

    This function is called to initialize the \a reading
    classes used for a sensor.

    If your backend has already allocated a reading you
    should pass the address of this to the function.
    Otherwise you should pass 0 and the function will
    return the address of the reading your backend
    should use when it wants to notify the sensor API
    of new readings.

    Note that this is a template function so it should
    be called with the appropriate type.

    \code
    class MyBackend : public QSensorBackend
    {
        QAccelerometerReading m_reading;
    public:
        MyBackend(QSensor *sensor)
            : QSensorBackend(sensor)
        {
            setReading<QAccelerometerReading>(&m_reading);
        }

        ...
    \endcode

    Note that this function must be called or you will
    not be able to send readings to the front end.

    If you do not wish to store the address of the reading
    you may use the reading() method to get it again later.

    \code
    class MyBackend : public QSensorBackend
    {
    public:
        MyBackend(QSensor *sensor)
            : QSensorBackend(sensor)
        {
            setReading<QAccelerometerReading>(0);
        }

        void poll()
        {
            quint64 timestamp;
            qreal x, y, z;
            ...
            QAccelerometerReading *reading = static_cast<QAccelerometerReading*>(reading());
            reading->setTimestamp(timestamp);
            reading->setX(x);
            reading->setY(y);
            reading->setZ(z);
        }

        ...
    \endcode

    \sa reading()
*/

/*!
    \internal
*/
void QSensorBackend::setReadings(QSensorReading *device, QSensorReading *filter, QSensorReading *cache)
{
    QSensorPrivate *d = m_sensor->d_func();
    d->device_reading = device;
    d->filter_reading = filter;
    d->cache_reading = cache;
}

/*!
    Add a data rate (consisting of \a min and \a max values) for the sensor.

    Note that this function should be called from the constructor so that the information
    is available immediately.

    \sa QSensor::availableDataRates
*/
void QSensorBackend::addDataRate(qreal min, qreal max)
{
    QSensorPrivate *d = m_sensor->d_func();
    d->availableDataRates << qrange(min, max);
}

/*!
    Set the data rates for the sensor based on \a otherSensor.

    This is designed for sensors that are based on other sensors.

    \code
    setDataRates(otherSensor);
    \endcode

    Note that this function must be called from the constructor.

    \sa QSensor::availableDataRates, addDataRate()
*/
void QSensorBackend::setDataRates(const QSensor *otherSensor)
{
    if (!otherSensor) {
        qWarning() << "ERROR: Cannot call QSensorBackend::setDataRates with 0";
        return;
    }
    if (otherSensor->identifier().isEmpty()) {
        qWarning() << "ERROR: Cannot call QSensorBackend::setDataRates with an invalid sensor";
        return;
    }
    if (m_sensor->isConnectedToBackend()) {
        qWarning() << "ERROR: Cannot call QSensorBackend::setDataRates outside of the constructor";
        return;
    }
    QSensorPrivate *d = m_sensor->d_func();
    d->availableDataRates = otherSensor->availableDataRates();
}

/*!
    Add an output range (consisting of \a min, \a max values and \a accuracy) for the sensor.

    Note that this function should be called from the constructor so that the information
    is available immediately.

    \sa QSensor::outputRange, QSensor::outputRanges
*/
void QSensorBackend::addOutputRange(qreal min, qreal max, qreal accuracy)
{
    QSensorPrivate *d = m_sensor->d_func();

    qoutputrange details = {min, max, accuracy};

    d->outputRanges << details;
}

/*!
    Set the \a description for the sensor.

    Note that this function should be called from the constructor so that the information
    is available immediately.
*/
void QSensorBackend::setDescription(const QString &description)
{
    QSensorPrivate *d = m_sensor->d_func();
    d->description = description;
}

/*!
    Inform the front end that the sensor has stopped.
    This can be due to start() failing or for some
    unexpected reason (eg. hardware failure).

    Note that the front end must call QSensor::isActive() to see if
    the sensor has stopped. If the sensor has stopped due to an error
    the sensorError() function should be called to notify the class
    of the error condition.
*/
void QSensorBackend::sensorStopped()
{
    QSensorPrivate *d = m_sensor->d_func();
    d->active = false;
}

/*!
    Inform the front end that the sensor is busy.
    This implicitly calls sensorStopped() and
    is typically called from start().

    Note that the front end must call QSensor::isBusy() to see if
    the sensor is busy. If the sensor has stopped due to an error
    the sensorError() function should be called to notify the class
    of the error condition.
*/
void QSensorBackend::sensorBusy()
{
    QSensorPrivate *d = m_sensor->d_func();
    d->active = false;
    d->busy = true;
}

/*!
    Inform the front end that a sensor error occurred.
    Note that this only reports an \a error code. It does
    not stop the sensor.

    \sa sensorStopped()
*/
void QSensorBackend::sensorError(int error)
{
    QSensorPrivate *d = m_sensor->d_func();
    d->error = error;
    Q_EMIT m_sensor->sensorError(error);
}

#include "moc_qsensorbackend.cpp"
QT_END_NAMESPACE

