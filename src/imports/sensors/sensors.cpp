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

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>

#include <qaccelerometer.h>
#include <qambientlightsensor.h>
#include <qcompass.h>
#include <qmagnetometer.h>
#include <qorientationsensor.h>
#include <qproximitysensor.h>
#include <qrotationsensor.h>
#include <qtapsensor.h>
#include <qlightsensor.h>
#include <qgyroscope.h>
#include <qirproximitysensor.h>

QT_BEGIN_NAMESPACE


class QSensorsDeclarativeModule : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        char const * const package = "Qt.sensors";
        if (QLatin1String(uri) != QLatin1String(package)) return;
        int major;
        int minor;

        // Register the 1.0 interfaces
        major = 1;
        minor = 0;
        qmlRegisterUncreatableType<QSensor              >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
        qmlRegisterUncreatableType<QSensorReading       >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
        qmlRegisterType           <QAccelerometer       >(package, major, minor, "Accelerometer");
        qmlRegisterUncreatableType<QAccelerometerReading>(package, major, minor, "AccelerometerReading", QLatin1String("Cannot create AccelerometerReading"));
        qmlRegisterType           <QAmbientLightSensor  >(package, major, minor, "AmbientLightSensor");
        qmlRegisterUncreatableType<QAmbientLightReading >(package, major, minor, "AmbientLightReading",  QLatin1String("Cannot create AmbientLightReading"));
        qmlRegisterType           <QCompass             >(package, major, minor, "Compass");
        qmlRegisterUncreatableType<QCompassReading      >(package, major, minor, "CompassReading",       QLatin1String("Cannot create CompassReading"));
        qmlRegisterType           <QMagnetometer        >(package, major, minor, "Magnetometer");
        qmlRegisterUncreatableType<QMagnetometerReading >(package, major, minor, "MagnetometerReading",  QLatin1String("Cannot create MagnetometerReading"));
        qmlRegisterType           <QOrientationSensor   >(package, major, minor, "OrientationSensor");
        qmlRegisterUncreatableType<QOrientationReading  >(package, major, minor, "OrientationReading",   QLatin1String("Cannot create OrientationReading"));
        qmlRegisterType           <QProximitySensor     >(package, major, minor, "ProximitySensor");
        qmlRegisterUncreatableType<QProximityReading    >(package, major, minor, "ProximityReading",     QLatin1String("Cannot create ProximityReading"));
        qmlRegisterType           <QRotationSensor      >(package, major, minor, "RotationSensor");
        qmlRegisterUncreatableType<QRotationReading     >(package, major, minor, "RotationReading",      QLatin1String("Cannot create RotationReading"));
        qmlRegisterType           <QTapSensor           >(package, major, minor, "TapSensor");
        qmlRegisterUncreatableType<QTapReading          >(package, major, minor, "TapReading",           QLatin1String("Cannot create TapReading"));
        qmlRegisterType           <QLightSensor         >(package, major, minor, "LightSensor");
        qmlRegisterUncreatableType<QLightReading        >(package, major, minor, "LightReading",         QLatin1String("Cannot create LightReading"));
        qmlRegisterType           <QGyroscope           >(package, major, minor, "Gyroscope");
        qmlRegisterUncreatableType<QGyroscopeReading    >(package, major, minor, "GyroscopeReading",     QLatin1String("Cannot create GyroscopeReading"));
        qmlRegisterType           <QIRProximitySensor   >(package, major, minor, "IRProximitySensor");
        qmlRegisterUncreatableType<QIRProximityReading  >(package, major, minor, "IRProximityReading",   QLatin1String("Cannot create IRProximityReading"));
    }
};

QT_END_NAMESPACE

#include "sensors.moc"

Q_EXPORT_PLUGIN2(qsensorsdeclarativemodule, QT_PREPEND_NAMESPACE(QSensorsDeclarativeModule));

// =====================================================================

/*!
    \qmlclass Sensor QSensor
    \ingroup qml-sensors_type
    \brief The Sensor element serves as a base type for sensors.

    The Sensor element serves as a base type for sensors.

    This element wraps the QSensor class. Please see the documentation for
    QSensor for details.

    This element cannot be directly created. Please use one of the sub-classes instead.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty int Sensor::dataRate
    Sets the rate at which data is returned by the sensor.
    Please see QSensor::dataRate for information about this property.
*/

/*!
    \qmlproperty bool Sensor::active
    Starts or stops the sensor.
    Please see QSensor::active for information about this property.
*/

/*!
    \qmlproperty SensorReading Sensor::reading
    Holds the most recent sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Sensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass SensorReading QSensorReading
    \ingroup qml-sensors_reading
    \brief The SensorReading element serves as a base type for sensor readings.

    The SensorReading element serves as a base type for sensor readings.

    This element wraps the QSensorReading class. Please see the documentation for
    QSensorReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty quint64 SensorReading::timestamp
    A timestamp for the reading.
    Please see QSensorReading::timestamp for information about this property.
*/

/*!
    \qmlclass Accelerometer QAccelerometer
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The Accelerometer element reports on linear acceleration
           along the X, Y and Z axes.

    The Accelerometer element reports on linear acceleration
    along the X, Y and Z axes.

    This element wraps the QAccelerometer class. Please see the documentation for
    QAccelerometer for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty AccelerometerReading Accelerometer::reading
    Holds the most recent accelerometer reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Accelerometer::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass AccelerometerReading QAccelerometerReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The AccelerometerReading element holds the most recent Accelerometer reading.

    The AccelerometerReading element holds the most recent Accelerometer reading.

    This element wraps the QAccelerometerReading class. Please see the documentation for
    QAccelerometerReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal AccelerometerReading::x
    Please see QAccelerometerReading::x for information about this property.
*/

/*!
    \qmlproperty qreal AccelerometerReading::y
    Please see QAccelerometerReading::y for information about this property.
*/

/*!
    \qmlproperty qreal AccelerometerReading::z
    Please see QAccelerometerReading::z for information about this property.
*/

/*!
    \qmlclass AmbientLightSensor QAmbientLightSensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The AmbientLightSensor element repors on ambient lighting conditions.

    The AmbientLightSensor element repors on ambient lighting conditions.

    This element wraps the QAmbientLightSensor class. Please see the documentation for
    QAmbientLightSensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty AmbientLightReading AmbientLightSensor::reading
    Holds the most recent ambient light reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal AmbientLightSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass AmbientLightReading QAmbientLightReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The AmbientLightReading element holds the most AmbientLightSensor reading.

    The AmbientLightReading element holds the most AmbientLightSensor reading.

    This element wraps the QAmbientLightReading class. Please see the documentation for
    QAmbientLightReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty QAmbientLightReading::LightLevel AmbientLightReading::lightLevel
    Please see QAmbientLightReading::lightLevel for information about this property.

    LightLevel constants are exposed through the AmbientLightReading class.
    \code
        AmbientLightSensor {
            onReadingChanged: {
                if (reading.lightLevel == AmbientLightReading.Dark)
                    // do something
            }
        }
    \endcode
*/

/*!
    \qmlclass Compass QCompass
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The Compass element reports on heading using magnetic north as a reference.

    The Compass element reports on heading using magnetic north as a reference.

    This element wraps the QCompass class. Please see the documentation for
    QCompass for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty CompassReading Compass::reading
    Holds the most recent compass reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Compass::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass CompassReading QCompassReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The CompassReading element holds the most recent Compass reading.

    The CompassReading element holds the most recent Compass reading.

    This element wraps the QCompassReading class. Please see the documentation for
    QCompassReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal CompassReading::azimuth
    Please see QCompassReading::azimuth for information about this property.
*/

/*!
    \qmlproperty qreal CompassReading::calibrationLevel
    Please see QCompassReading::calibrationLevel for information about this property.
*/

/*!
    \qmlclass Magnetometer QMagnetometer
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The Magnetometer element reports on magnetic field strength
           along the Z, Y and Z axes.

    The Magnetometer element reports on magnetic field strength
    along the Z, Y and Z axes.

    This element wraps the QMagnetometer class. Please see the documentation for
    QMagnetometer for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty MagnetometerReading Magnetometer::reading
    Holds the most recent magnetometer reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Magnetometer::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass MagnetometerReading QMagnetometerReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The MagnetometerReading element holds the most recent Magnetometer reading.

    The MagnetometerReading element holds the most recent Magnetometer reading.

    This element wraps the QMagnetometerReading class. Please see the documentation for
    QMagnetometerReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal MagnetometerReading::x
    Please see QMagnetometerReading::x for information about this property.
*/

/*!
    \qmlproperty qreal MagnetometerReading::y
    Please see QMagnetometerReading::y for information about this property.
*/

/*!
    \qmlproperty qreal MagnetometerReading::z
    Please see QMagnetometerReading::z for information about this property.
*/

/*!
    \qmlproperty qreal MagnetometerReading::calibrationLevel
    Please see QMagnetometerReading::calibrationLevel for information about this property.
*/

/*!
    \qmlclass OrientationSensor QOrientationSensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The OrientationSensor element reports device orientation.

    The OrientationSensor element reports device orientation.

    This element wraps the QOrientationSensor class. Please see the documentation for
    QOrientationSensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty OrientationReading OrientationSensor::reading
    Holds the most recent orientation reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal OrientationSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass OrientationReading QOrientationReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The OrientationReading element holds the most recent OrientationSensor reading.

    The OrientationReading element holds the most recent OrientationSensor reading.

    This element wraps the QOrientationReading class. Please see the documentation for
    QOrientationReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty QOrientationReading::Orientation OrientationReading::orientation
    Please see QOrientationReading::orientation for information about this property.

    Orientation constants are exposed through the OrientationReading class.
    \code
        OrientationSensor {
            onReadingChanged: {
                if (reading.orientation == OrientationReading.TopUp)
                    // do something
            }
        }
    \endcode
*/

/*!
    \qmlclass ProximitySensor QProximitySensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The ProximitySensor element reports on object proximity.

    The ProximitySensor element reports on object proximity.

    This element wraps the QProximitySensor class. Please see the documentation for
    QProximitySensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty ProximityReading ProximitySensor::reading
    Holds the most recent proximity reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal ProximitySensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass ProximityReading QProximityReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The ProximityReading element holds the most recent ProximitySensor reading.

    The ProximityReading element holds the most recent ProximitySensor reading.

    This element wraps the QProximityReading class. Please see the documentation for
    QProximityReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty bool ProximityReading::close
    Please see QProximityReading::close for information about this property.
*/

/*!
    \qmlclass RotationSensor QRotationSensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The RotationSensor element reports on device rotation
           around the X, Y and Z axes.

    The RotationSensor element reports on device rotation
    around the X, Y and Z axes.

    This element wraps the QRotationSensor class. Please see the documentation for
    QRotationSensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty RotationReading RotationSensor::reading
    Holds the most recent rotation reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal RotationSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass RotationReading QRotationReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The RotationReading element holds the most recent RotationSensor reading.

    The RotationReading element holds the most recent RotationSensor reading.

    This element wraps the QRotationReading class. Please see the documentation for
    QRotationReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal RotationReading::x
    Please see QRotationReading::x for information about this property.
*/

/*!
    \qmlproperty qreal RotationReading::y
    Please see QRotationReading::y for information about this property.
*/

/*!
    \qmlproperty qreal RotationReading::z
    Please see QRotationReading::z for information about this property.
*/

/*!
    \qmlclass TapSensor QTapSensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The TapSensor element reports tap and double tap events
           along the X, Y and Z axes.

    The TapSensor element reports tap and double tap events
    along the X, Y and Z axes.

    This element wraps the QTapSensor class. Please see the documentation for
    QTapSensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty TapReading TapSensor::reading
    Holds the most recent tap sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal TapSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass TapReading QTapReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The TapReading element holds the most recent TapSensor reading.

    The TapReading element holds the most recent TapSensor reading.

    This element wraps the QTapReading class. Please see the documentation for
    QTapReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty bool TapReading::doubleTap
    Please see QTapReading::doubleTap for information about this property.
*/

/*!
    \qmlproperty QTapReading::TapDirection TapReading::tapDirection
    Please see QTapReading::tapDirection for information about this property.

    TapDirection constants are exposed through the TapReading class.
    \code
        TapSensor {
            onReadingChanged: {
                if ((reading.tapDirection & TapReading.X_Both))
                    // do something
            }
        }
    \endcode
*/

/*!
    \qmlclass LightSensor QLightSensor
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The LightSensor element reports on light levels using LUX.

    The LightSensor element reports on light levels using LUX.

    This element wraps the QLightSensor class. Please see the documentation for
    QLightSensor for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty LightReading LightSensor::reading
    Holds the most recent light sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal LightSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass LightReading QLightReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The LightReading element holds the most recent LightSensor reading.

    The LightReading element holds the most recent LightSensor reading.

    This element wraps the QLightReading class. Please see the documentation for
    QLightReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal LightReading::lux
    Please see QLightReading::lux for information about this property.
*/

/*!
    \qmlclass Gyroscope QGyroscope
    \ingroup qml-sensors_type
    \inherits Sensor
    \brief The Gyroscope element reports on rotational acceleration
           around the X, Y and Z axes.

    This element wraps the QGyroscope class. Please see the documentation for
    QGyroscope for details.

    \sa {Sensors QML Limitations}
*/

/*!
    \qmlproperty GyroscopeReading Gyroscope::reading
    Holds the most recent gyroscope reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Gyroscope::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass GyroscopeReading QGyroscopeReading
    \ingroup qml-sensors_reading
    \inherits SensorReading
    \brief The GyroscopeReading element holds the most recent Gyroscope reading.

    The GyroscopeReading element holds the most recent Gyroscope reading.

    This element wraps the QGyroscopeReading class. Please see the documentation for
    QGyroscopeReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal GyroscopeReading::x
    Please see QGyroscopeReading::x for information about this property.
*/

/*!
    \qmlproperty qreal GyroscopeReading::y
    Please see QGyroscopeReading::y for information about this property.
*/

/*!
    \qmlproperty qreal GyroscopeReading::z
    Please see QGyroscopeReading::z for information about this property.
*/


