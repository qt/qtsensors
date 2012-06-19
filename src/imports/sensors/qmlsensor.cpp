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

#include "qmlsensor.h"
#include <QSensor>
#include <QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmltype Sensor
    \instantiates QmlSensor
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.1
    \brief The Sensor element serves as a base type for sensors.

    The Sensor element serves as a base type for sensors.

    This element wraps the QSensor class. Please see the documentation for
    QSensor for details.

    This element cannot be directly created. Please use one of the sub-classes instead.
*/

QmlSensor::QmlSensor(QObject *parent)
    : QObject(parent)
    , m_parsed(false)
    , m_active(false)
    , m_reading(0)
{
}

QmlSensor::~QmlSensor()
{
}

/*!
    \qmlproperty string QtMobility.sensors1::Sensor::identifier
    This property holds the backend identifier for the sensor.

    Please see QSensor::identifier for information about this property.
*/

QString QmlSensor::identifier() const
{
    return m_identifier;
}

void QmlSensor::setIdentifier(const QString &identifier)
{
    if (m_parsed) return;
    m_identifier = identifier;
    Q_EMIT identifierChanged();
}

/*!
    \qmlproperty string QtMobility.sensors1::Sensor::type
    This property holds the type of the sensor.
*/

QString QmlSensor::type() const
{
    return QString::fromLatin1(sensor()->type());
}

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::connectedToBackend
    This property holds a value indicating if the sensor has connected to a backend.

    Please see QSensor::connectedToBackend for information about this property.
*/

bool QmlSensor::isConnectedToBackend() const
{
    return sensor()->isConnectedToBackend();
}

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::busy
    This property holds a value to indicate if the sensor is busy.

    Please see QSensor::busy for information about this property.
*/

bool QmlSensor::isBusy() const
{
    return sensor()->isBusy();
}

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::active
    This property holds a value to indicate if the sensor is active.

    Please see QSensor::active for information about this property.
*/

void QmlSensor::setActive(bool active)
{
    m_active = active;
    if (!m_parsed) return; // delay (it'll get called again later)!
    bool wasActive = sensor()->isActive();
    if (wasActive == active) return;
    if (active) {
        sensor()->start();
        m_active = sensor()->isActive();
    } else {
        sensor()->stop();
    }
    if (m_active != wasActive)
        emit activeChanged();
}

bool QmlSensor::isActive() const
{
    return m_active;
}

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::alwaysOn
    This property holds a value to indicate if the sensor should remain running when the screen is off.

    Please see QSensor::alwaysOn for information about this property.
*/

bool QmlSensor::isAlwaysOn() const
{
    return sensor()->isAlwaysOn();
}

void QmlSensor::setAlwaysOn(bool alwaysOn)
{
    sensor()->setAlwaysOn(alwaysOn);
}

/*!
    \qmlproperty list<Range> QtMobility.sensors1::Sensor::availableDataRates
    This property holds the data rates that the sensor supports.

    Please see QSensor::availableDataRates for information about this property.
*/

QQmlListProperty<QmlSensorRange> QmlSensor::availableDataRates() const
{
    QList<QmlSensorRange*> ret;
    ret.reserve(sensor()->availableDataRates().size());
    foreach (const qrange &r, sensor()->availableDataRates()) {
        QmlSensorRange *range = new QmlSensorRange;
        //QQmlEngine::setObjectOwnership(range, QQmlEngine::JavaScriptOwnership);
        range->setMinumum(r.first);
        range->setMaximum(r.second);
        ret << range;
    }
    return QQmlListProperty<QmlSensorRange>(const_cast<QmlSensor*>(this), ret);
}

/*!
    \qmlproperty int QtMobility.sensors1::Sensor::dataRate
    This property holds the data rate that the sensor should be run at.

    Please see QSensor::dataRate for information about this property.
*/

int QmlSensor::dataRate() const
{
    return sensor()->dataRate();
}

void QmlSensor::setDataRate(int rate)
{
    if (rate != dataRate()) {
      sensor()->setDataRate(rate);
      Q_EMIT dataRateChanged();
    }
}

/*!
    \qmlproperty list<OutputRange> QtMobility.sensors1::Sensor::outputRanges
    This property holds a list of output ranges the sensor supports.

    Please see QSensor::outputRanges for information about this property.
*/

QQmlListProperty<QmlSensorOutputRange> QmlSensor::outputRanges() const
{
    QList<QmlSensorOutputRange*> ret;
    ret.reserve(sensor()->outputRanges().size());
    foreach (const qoutputrange &r, sensor()->outputRanges()) {
        QmlSensorOutputRange *range = new QmlSensorOutputRange;
        //QQmlEngine::setObjectOwnership(range, QQmlEngine::JavaScriptOwnership);
        range->setMinimum(r.minimum);
        range->setMaximum(r.maximum);
        range->setAccuracy(r.accuracy);
        ret << range;
    }
    return QQmlListProperty<QmlSensorOutputRange>(const_cast<QmlSensor*>(this), ret);
}

/*!
    \qmlproperty int QtMobility.sensors1::Sensor::outputRange
    This property holds the output range in use by the sensor.

    Please see QSensor::outputRange for information about this property.
*/

int QmlSensor::outputRange() const
{
    return sensor()->outputRange();
}

void QmlSensor::setOutputRange(int index)
{
    int oldRange = outputRange();
    if (oldRange == index) return;
    sensor()->setOutputRange(index);
    if (sensor()->outputRange() == index)
        Q_EMIT outputRangeChanged();
}

/*!
    \qmlproperty string QtMobility.sensors1::Sensor::description
    This property holds a descriptive string for the sensor.
*/

QString QmlSensor::description() const
{
    return sensor()->description();
}

/*!
    \qmlproperty int QtMobility.sensors1::Sensor::error
    This property holds the last error code set on the sensor.
*/

int QmlSensor::error() const
{
    return sensor()->error();
}

/*!
    \qmlproperty SensorReading QtMobility.sensors1::Sensor::reading
    This property holds the reading class.

    Please see QSensor::reading for information about this property.
    \sa {QML Reading types}
*/

QmlSensorReading *QmlSensor::reading() const
{
    return m_reading;
}

/*!
    \qmlmethod bool QtMobility.sensors1::Sensor::start()
    Start retrieving values from the sensor. Returns true if the sensor was started, false otherwise.

    Please see QSensor::start() for information.
*/

bool QmlSensor::start()
{
    setActive(true);
    return isActive();
}

/*!
    \qmlmethod bool QtMobility.sensors1::Sensor::stop()
    Stop retrieving values from the sensor.

    Please see QSensor::stop() for information.
*/

void QmlSensor::stop()
{
    setActive(false);
}

void QmlSensor::classBegin()
{
}

void QmlSensor::componentComplete()
{
    m_parsed = true;

    connect(sensor(), SIGNAL(sensorError(int)), this, SIGNAL(errorChanged()));
    connect(sensor(), SIGNAL(activeChanged()), this, SIGNAL(activeChanged()));
    connect(sensor(), SIGNAL(alwaysOnChanged()), this, SIGNAL(alwaysOnChanged()));

    // We need to set this on the sensor object now
    sensor()->setIdentifier(m_identifier.toLocal8Bit());

    // These can change!
    QByteArray oldIdentifier = sensor()->identifier();
    int oldDataRate = dataRate();
    int oldOutputRange = outputRange();

    bool ok = sensor()->connectToBackend();
    if (ok) {
        Q_EMIT connectedToBackendChanged();
        m_reading = createReading();
        m_reading->setParent(this);
    }

    if (oldIdentifier != sensor()->identifier()) {
        m_identifier = QString::fromLatin1(sensor()->identifier());
        Q_EMIT identifierChanged();
    }
    if (oldDataRate != dataRate())
        Q_EMIT dataRateChanged();
    if (oldOutputRange != outputRange())
        Q_EMIT outputRangeChanged();

    // meta-data should become non-empty
    if (!description().isEmpty())
        Q_EMIT descriptionChanged();
    if (sensor()->availableDataRates().count())
        Q_EMIT availableDataRatesChanged();
    if (sensor()->outputRanges().count())
        Q_EMIT outputRangesChanged();

    _update();

    connect(sensor(), SIGNAL(readingChanged()), this, SLOT(updateReading()));
    if (m_active) {
        m_active = false;
        start();
    }
}

void QmlSensor::_update()
{
}

void QmlSensor::updateReading()
{
    if (m_reading) {
        m_reading->update();
        Q_EMIT readingChanged();
    }
}

/*!
    \qmltype SensorReading
    \instantiates QmlSensorReading
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.1
    \brief The SensorReading element serves as a base type for sensor readings.

    The SensorReading element serves as a base type for sensor readings.

    This element wraps the QSensorReading class. Please see the documentation for
    QSensorReading for details.

    This element cannot be directly created.
*/

QmlSensorReading::QmlSensorReading(QSensor *)
    : QObject(0)
{
}

QmlSensorReading::~QmlSensorReading()
{
}

/*!
    \qmlproperty quint64 QtMobility.sensors1::SensorReading::timestamp
    A timestamp for the reading.

    Please see QSensorReading::timestamp for information about this property.
*/

quint64 QmlSensorReading::timestamp() const
{
    return m_timestamp;
}

void QmlSensorReading::update()
{
    quint64 ts = reading()->timestamp();
    if (m_timestamp != ts) {
        m_timestamp = ts;
        Q_EMIT timestampChanged();
    }
    readingUpdate();
}

QT_END_NAMESPACE
