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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>
#include <QtSensors/QSensorManager>

#include <QtSensors/qaccelerometer.h>
#include <QtSensors/qambientlightsensor.h>
#include <QtSensors/qcompass.h>
#include <QtSensors/qmagnetometer.h>
#include <QtSensors/qorientationsensor.h>
#include <QtSensors/qproximitysensor.h>
#include <QtSensors/qrotationsensor.h>
#include <QtSensors/qtapsensor.h>
#include <QtSensors/qlightsensor.h>
#include <QtSensors/qgyroscope.h>
#include <QtSensors/qirproximitysensor.h>
#include <QtSensors/qtiltsensor.h>

#include "qmlsensorglobal.h"
#include "qmlsensor.h"
#include "qmlaccelerometer.h"
#include "qmlambientlightsensor.h"
#include "qmlcompass.h"
#include "qmlgyroscope.h"
#include "qmlirproximitysensor.h"
#include "qmllightsensor.h"
#include "qmlmagnetometer.h"
#include "qmlorientationsensor.h"
#include "qmlproximitysensor.h"
#include "qmlrotationsensor.h"
#include "qmltapsensor.h"
#include "qmltiltsensor.h"
#include "qmlsensorgesture.h"

QT_BEGIN_NAMESPACE

static QObject *global_object_13(QQmlEngine *, QJSEngine *)
{
    return new QmlSensorGlobal;
}

class QtSensorsDeclarativeModule : public QQmlExtensionPlugin
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
        qmlRegisterSingletonType  <QmlSensorGlobal             >(package, major, minor, "QtSensors", global_object_13);
        qmlRegisterUncreatableType<QmlSensorRange              >(package, major, minor, "Range",                QLatin1String("Cannot create Range"));
        qmlRegisterUncreatableType<QmlSensorOutputRange        >(package, major, minor, "OutputRange",          QLatin1String("Cannot create OutputRange"));
        qmlRegisterUncreatableType<QmlSensor                   >(package, major, minor, "Sensor",               QLatin1String("Cannot create Sensor"));
        qmlRegisterUncreatableType<QmlSensorReading            >(package, major, minor, "SensorReading",        QLatin1String("Cannot create SensorReading"));
        qmlRegisterType           <QmlAccelerometer            >(package, major, minor, "Accelerometer");
        qmlRegisterUncreatableType<QmlAccelerometerReading     >(package, major, minor, "AccelerometerReading", QLatin1String("Cannot create AccelerometerReading"));
        qmlRegisterType           <QmlAmbientLightSensor       >(package, major, minor, "AmbientLightSensor");
        qmlRegisterUncreatableType<QmlAmbientLightSensorReading>(package, major, minor, "AmbientLightReading",  QLatin1String("Cannot create AmbientLightReading"));
        qmlRegisterType           <QmlCompass                  >(package, major, minor, "Compass");
        qmlRegisterUncreatableType<QmlCompassReading           >(package, major, minor, "CompassReading",       QLatin1String("Cannot create CompassReading"));
        qmlRegisterType           <QmlGyroscope                >(package, major, minor, "Gyroscope");
        qmlRegisterUncreatableType<QmlGyroscopeReading         >(package, major, minor, "GyroscopeReading",     QLatin1String("Cannot create GyroscopeReading"));
        qmlRegisterType           <QmlIRProximitySensor        >(package, major, minor, "IRProximitySensor");
        qmlRegisterUncreatableType<QmlIRProximitySensorReading >(package, major, minor, "IRProximityReading",   QLatin1String("Cannot create IRProximityReading"));
        qmlRegisterType           <QmlLightSensor              >(package, major, minor, "LightSensor");
        qmlRegisterUncreatableType<QmlLightSensorReading       >(package, major, minor, "LightReading",         QLatin1String("Cannot create LightReading"));
        qmlRegisterType           <QmlMagnetometer             >(package, major, minor, "Magnetometer");
        qmlRegisterUncreatableType<QmlMagnetometerReading      >(package, major, minor, "MagnetometerReading",  QLatin1String("Cannot create MagnetometerReading"));
        qmlRegisterType           <QmlOrientationSensor        >(package, major, minor, "OrientationSensor");
        qmlRegisterUncreatableType<QmlOrientationSensorReading >(package, major, minor, "OrientationReading",   QLatin1String("Cannot create OrientationReading"));
        qmlRegisterType           <QmlProximitySensor          >(package, major, minor, "ProximitySensor");
        qmlRegisterUncreatableType<QmlProximitySensorReading   >(package, major, minor, "ProximityReading",     QLatin1String("Cannot create ProximityReading"));
        qmlRegisterType           <QmlRotationSensor           >(package, major, minor, "RotationSensor");
        qmlRegisterUncreatableType<QmlRotationSensorReading    >(package, major, minor, "RotationReading",      QLatin1String("Cannot create RotationReading"));
        qmlRegisterType           <QmlTapSensor                >(package, major, minor, "TapSensor");
        qmlRegisterUncreatableType<QmlTapSensorReading         >(package, major, minor, "TapReading",           QLatin1String("Cannot create TapReading"));
        qmlRegisterType           <QmlTiltSensor               >(package, major, minor, "TiltSensor");
        qmlRegisterUncreatableType<QmlTiltSensorReading        >(package, major, minor, "TiltReading",          QLatin1String("Cannot create TiltReading"));

        qmlRegisterType           <QmlSensorGesture            >(package, major, minor, "SensorGesture");
    }
};

QT_END_NAMESPACE

#include "sensors.moc"
