/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

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

class QSensorsDeclarativeModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "plugin.json")
public:
    virtual void registerTypes(const char *uri)
    {
        char const * const package = "QtMobility.sensors";
        if (QLatin1String(uri) != QLatin1String(package)) return;
        int major;
        int minor;

        // Register the 1.1 interfaces
        major = 1;
        minor = 1;
        qmlRegisterUncreatableType<QSensorReading       >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
        qmlRegisterType           <QAccelerometer       >(package, major, minor, "Accelerometer");
        qmlRegisterType           <QAccelerometerReading>(package, major, minor, "AccelerometerReading");
        qmlRegisterType           <QAmbientLightSensor  >(package, major, minor, "AmbientLightSensor");
        qmlRegisterType           <QAmbientLightReading >(package, major, minor, "AmbientLightReading");
        qmlRegisterType           <QCompass             >(package, major, minor, "Compass");
        qmlRegisterType           <QCompassReading      >(package, major, minor, "CompassReading");
        qmlRegisterType           <QMagnetometer        >(package, major, minor, "Magnetometer");
        qmlRegisterType           <QMagnetometerReading >(package, major, minor, "MagnetometerReading");
        qmlRegisterType           <QOrientationSensor   >(package, major, minor, "OrientationSensor");
        qmlRegisterType           <QOrientationReading  >(package, major, minor, "OrientationReading");
        qmlRegisterType           <QProximitySensor     >(package, major, minor, "ProximitySensor");
        qmlRegisterType           <QProximityReading    >(package, major, minor, "ProximityReading");
        qmlRegisterType           <QRotationSensor      >(package, major, minor, "RotationSensor");
        qmlRegisterType           <QRotationReading     >(package, major, minor, "RotationReading");
        qmlRegisterType           <QTapSensor           >(package, major, minor, "TapSensor");
        qmlRegisterType           <QTapReading          >(package, major, minor, "TapReading");

        // Register the 1.2 interfaces
        major = 1;
        minor = 2;
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

        // Register the 1.3 interfaces
        major = 1;
        minor = 3;
        qmlRegisterUncreatableType<QSensor            ,1>(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
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

// =====================================================================

/*!
    \qmlclass QtMobility.sensors1::Sensor QSensor
    \inqmlmodule QtMobility.sensors 1.3
    \brief The Sensor type serves as a base type for sensors.

    The Sensor type serves as a base type for sensors.

    This type wraps the QSensor class. Please see the documentation for
    QSensor for details.

    This type cannot be directly created. Please use one of the sub-classes instead.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty int QtMobility.sensors1::Sensor::dataRate
    Sets the rate at which data is returned by the sensor.
    Please see QSensor::dataRate for information about this property.
*/

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::active
    Starts or stops the sensor.
    Please see QSensor::active for information about this property.
*/

/*!
    \qmlproperty SensorReading QtMobility.sensors1::Sensor::reading
    Holds the most recent sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlproperty bool QtMobility.sensors1::Sensor::alwaysOn
    Keeps the sensor running when the display turns off.
    Please see QSensor::alwaysOn for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::Sensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass SensorReading QSensorReading
    \inqmlmodule QtMobility.sensors 1.3
    \brief The SensorReading type serves as a base type for sensor readings.

    The SensorReading type serves as a base type for sensor readings.

    This type wraps the QSensorReading class. Please see the documentation for
    QSensorReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty quint64 QtMobility.sensors1::SensorReading::timestamp
    A timestamp for the reading.
    Please see QSensorReading::timestamp for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::Accelerometer QAccelerometer
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The Accelerometer type reports on linear acceleration
           along the X, Y and Z axes.

    The Accelerometer type reports on linear acceleration
    along the X, Y and Z axes.

    This type wraps the QAccelerometer class. Please see the documentation for
    QAccelerometer for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty AccelerometerReading QtMobility.sensors1::Accelerometer::reading
    Holds the most recent accelerometer reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::Accelerometer::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass AccelerometerReading QAccelerometerReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The AccelerometerReading type holds the most recent Accelerometer reading.

    The AccelerometerReading type holds the most recent Accelerometer reading.

    This type wraps the QAccelerometerReading class. Please see the documentation for
    QAccelerometerReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::AccelerometerReading::x
    Please see QAccelerometerReading::x for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::AccelerometerReading::y
    Please see QAccelerometerReading::y for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::AccelerometerReading::z
    Please see QAccelerometerReading::z for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::AmbientLightSensor QAmbientLightSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The AmbientLightSensor type repors on ambient lighting conditions.

    The AmbientLightSensor type repors on ambient lighting conditions.

    This type wraps the QAmbientLightSensor class. Please see the documentation for
    QAmbientLightSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty AmbientLightReading QtMobility.sensors1::AmbientLightSensor::reading
    Holds the most recent ambient light reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::AmbientLightSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass AmbientLightReading QAmbientLightReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The AmbientLightReading type holds the most AmbientLightSensor reading.

    The AmbientLightReading type holds the most AmbientLightSensor reading.

    This type wraps the QAmbientLightReading class. Please see the documentation for
    QAmbientLightReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty QAmbientLightReading::LightLevel QtMobility.sensors1::AmbientLightReading::lightLevel
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
    \qmlclass QtMobility.sensors1::Compass QCompass
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The Compass type reports on heading using magnetic north as a reference.

    The Compass type reports on heading using magnetic north as a reference.

    This type wraps the QCompass class. Please see the documentation for
    QCompass for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty CompassReading QtMobility.sensors1::Compass::reading
    Holds the most recent compass reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::Compass::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass CompassReading QCompassReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The CompassReading type holds the most recent Compass reading.

    The CompassReading type holds the most recent Compass reading.

    This type wraps the QCompassReading class. Please see the documentation for
    QCompassReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::CompassReading::azimuth
    Please see QCompassReading::azimuth for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::CompassReading::calibrationLevel
    Please see QCompassReading::calibrationLevel for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::Magnetometer QMagnetometer
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The Magnetometer type reports on magnetic field strength
           along the Z, Y and Z axes.

    The Magnetometer type reports on magnetic field strength
    along the Z, Y and Z axes.

    This type wraps the QMagnetometer class. Please see the documentation for
    QMagnetometer for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty MagnetometerReading QtMobility.sensors1::Magnetometer::reading
    Holds the most recent magnetometer reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::Magnetometer::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass MagnetometerReading QMagnetometerReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The MagnetometerReading type holds the most recent Magnetometer reading.

    The MagnetometerReading type holds the most recent Magnetometer reading.

    This type wraps the QMagnetometerReading class. Please see the documentation for
    QMagnetometerReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::MagnetometerReading::x
    Please see QMagnetometerReading::x for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::MagnetometerReading::y
    Please see QMagnetometerReading::y for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::MagnetometerReading::z
    Please see QMagnetometerReading::z for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::MagnetometerReading::calibrationLevel
    Please see QMagnetometerReading::calibrationLevel for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::OrientationSensor QOrientationSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The OrientationSensor type reports device orientation.

    The OrientationSensor type reports device orientation.

    This type wraps the QOrientationSensor class. Please see the documentation for
    QOrientationSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty OrientationReading QtMobility.sensors1::OrientationSensor::reading
    Holds the most recent orientation reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::OrientationSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass OrientationReading QOrientationReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The OrientationReading type holds the most recent OrientationSensor reading.

    The OrientationReading type holds the most recent OrientationSensor reading.

    This type wraps the QOrientationReading class. Please see the documentation for
    QOrientationReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty QOrientationReading::Orientation QtMobility.sensors1::OrientationReading::orientation
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
    \qmlclass QtMobility.sensors1::ProximitySensor QProximitySensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The ProximitySensor type reports on object proximity.

    The ProximitySensor type reports on object proximity.

    This type wraps the QProximitySensor class. Please see the documentation for
    QProximitySensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty ProximityReading QtMobility.sensors1::ProximitySensor::reading
    Holds the most recent proximity reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::ProximitySensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass ProximityReading QProximityReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The ProximityReading type holds the most recent ProximitySensor reading.

    The ProximityReading type holds the most recent ProximitySensor reading.

    This type wraps the QProximityReading class. Please see the documentation for
    QProximityReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty bool QtMobility.sensors1::ProximityReading::close
    Please see QProximityReading::close for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::RotationSensor QRotationSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The RotationSensor type reports on device rotation
           around the X, Y and Z axes.

    The RotationSensor type reports on device rotation
    around the X, Y and Z axes.

    This type wraps the QRotationSensor class. Please see the documentation for
    QRotationSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty RotationReading QtMobility.sensors1::RotationSensor::reading
    Holds the most recent rotation reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::RotationSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass RotationReading QRotationReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The RotationReading type holds the most recent RotationSensor reading.

    The RotationReading type holds the most recent RotationSensor reading.

    This type wraps the QRotationReading class. Please see the documentation for
    QRotationReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::RotationReading::x
    Please see QRotationReading::x for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::RotationReading::y
    Please see QRotationReading::y for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::RotationReading::z
    Please see QRotationReading::z for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::TapSensor QTapSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The TapSensor type reports tap and double tap events
           along the X, Y and Z axes.

    The TapSensor type reports tap and double tap events
    along the X, Y and Z axes.

    This type wraps the QTapSensor class. Please see the documentation for
    QTapSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty TapReading QtMobility.sensors1::TapSensor::reading
    Holds the most recent tap sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::TapSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass TapReading QTapReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The TapReading type holds the most recent TapSensor reading.

    The TapReading type holds the most recent TapSensor reading.

    This type wraps the QTapReading class. Please see the documentation for
    QTapReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty bool QtMobility.sensors1::TapReading::doubleTap
    Please see QTapReading::doubleTap for information about this property.
*/

/*!
    \qmlproperty QTapReading::TapDirection QtMobility.sensors1::TapReading::tapDirection
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
    \qmlclass QtMobility.sensors1::LightSensor QLightSensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.2
    \inherits QtMobility.sensors1::Sensor
    \brief The LightSensor type reports on light levels using LUX.

    The LightSensor type reports on light levels using LUX.

    This type wraps the QLightSensor class. Please see the documentation for
    QLightSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty LightReading QtMobility.sensors1::LightSensor::reading
    Holds the most recent light sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::LightSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass LightReading QLightReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.2
    \inherits QtMobility.sensors1::SensorReading
    \brief The LightReading type holds the most recent LightSensor reading.

    The LightReading type holds the most recent LightSensor reading.

    This type wraps the QLightReading class. Please see the documentation for
    QLightReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::LightReading::lux
    Please see QLightReading::lux for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::Gyroscope QGyroscope
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.2
    \inherits QtMobility.sensors1::Sensor
    \brief The Gyroscope type reports on rotational acceleration
           around the X, Y and Z axes.

    This type wraps the QGyroscope class. Please see the documentation for
    QGyroscope for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty GyroscopeReading QtMobility.sensors1::Gyroscope::reading
    Holds the most recent gyroscope reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::Gyroscope::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass GyroscopeReading QGyroscopeReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.2
    \inherits QtMobility.sensors1::SensorReading
    \brief The GyroscopeReading type holds the most recent Gyroscope reading.

    The GyroscopeReading type holds the most recent Gyroscope reading.

    This type wraps the QGyroscopeReading class. Please see the documentation for
    QGyroscopeReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::GyroscopeReading::x
    Please see QGyroscopeReading::x for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::GyroscopeReading::y
    Please see QGyroscopeReading::y for information about this property.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::GyroscopeReading::z
    Please see QGyroscopeReading::z for information about this property.
*/

/*!
    \qmlclass QtMobility.sensors1::IRProximitySensor QIRProximitySensor
    \ingroup qml-sensors_type
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::Sensor
    \brief The IRProximitySensor type reports on infra-red reflectance values.

    This type wraps the QIRProximitySensor class. Please see the documentation for
    QIRProximitySensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty IRProximityReading QtMobility.sensors1::IRProximitySensor::reading
    Holds the most recent IR proximity reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal QtMobility.sensors1::IRProximitySensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass IRProximityReading QIRProximityReading
    \ingroup qml-sensors_reading
    \inqmlmodule QtMobility.sensors 1.3
    \since QtMobility.sensors 1.3
    \inherits QtMobility.sensors1::SensorReading
    \brief The IRProximityReading type holds the most recent IR proximity reading.

    The IRProximityReading type holds the most recent IR proximity reading.

    This type wraps the QIRProximityReading class. Please see the documentation for
    QIRProximityReading for details.

    This type cannot be directly created.
*/

/*!
    \qmlproperty qreal QtMobility.sensors1::IRProximityReading::reflectance
    Please see QIRProximityReading::reflectance for information about this property.
*/

