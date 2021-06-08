/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtTest
import QtSensors

TestCase {
    id: testCase

    SignalSpy {
        id: sensorActiveSpy
        signalName: "activeChanged"
    }

    SignalSpy {
        id: sensorReadingSpy
        signalName: "readingChanged"
    }

    SignalSpy {
        id: sensorBusySpy
        signalName: "busyChanged"
    }

    function init() {
        TestControl.registerTestBackends()
    }

    function cleanup() {
        TestControl.unregisterTestBackends()
    }

    function test_busy() {
        var sensor = Qt.createQmlObject("import QtSensors; Accelerometer {identifier: \"QAccelerometer\"}", testCase);
        sensorBusySpy.target = sensor
        compare(sensor.busy, false)
        verify(sensor.start())

        // set sensor busy and verify 'busy' property and its signaling
        TestControl.setSensorBusy(sensor, true)
        compare(sensorBusySpy.count, 1)
        TestControl.setSensorBusy(sensor, false)
        compare(sensorBusySpy.count, 2)
        TestControl.setSensorBusy(sensor, false)
        compare(sensorBusySpy.count, 2)

        // tidy up
        sensor.destroy()
        sensorBusySpy.clear()
    }

    function test_reading(data) {

        var sensor = Qt.createQmlObject(
                    "import QtSensors; "
                    + data.tag + "{"
                    + "identifier: " + "\"Q" + data.tag + "\""
                    + "}"
                    ,testCase)
        sensorActiveSpy.target = sensor
        sensorReadingSpy.target = sensor

        // verify initial values of sensor
        // note: 'reading' values are 'undefined by design' before activation, and therefore aren't tested
        compare(sensor.type, "Q" + data.tag)
        compare(sensor.active, false)
        compare(sensor.alwaysOn, false )
        compare(sensor.busy, false)
        compare(sensor.description, "")
        compare(sensor.error, 0)
        compare(sensor.skipDuplicates, false)

        // start the sensor and verify activation
        sensor.start()
        compare(sensor.active, true)
        compare(sensorActiveSpy.count, 1)
        compare(sensorReadingSpy.count, 1)

        // verify the initial reading values
        for (var prop in data.initialReading)
            fuzzyCompare(sensor.reading[prop], data.initialReading[prop], 0.0001, data.tag + "::" + prop)

        // change reading values and verify them
        TestControl.setSensorReading(sensor, data.newReading)
        compare(sensorReadingSpy.count, 2)
        for (prop in data.newReading)
            fuzzyCompare(sensor.reading[prop], data.newReading[prop], 0.0001, data.tag + "::" + prop)

        // stop the sensor and verify deactivation
        sensor.stop()
        compare(sensor.active, false)
        compare(sensorActiveSpy.count, 2)
        compare(sensorReadingSpy.count, 2)

        // tidy up
        sensor.destroy()
        sensorActiveSpy.clear()
        sensorReadingSpy.clear()
    }

    function test_reading_data() {
        return [
                    {tag: "Accelerometer", initialReading: {timestamp: 0, x: 1.0, y: 1.0, z: 1.0}, newReading: {timestamp: 1, x: 2.0, y: 3.0, z: 4.0}},
                    {tag: "PressureSensor", initialReading: {pressure: 1.0, temperature: 1.0}, newReading: {pressure: 2.0, temperature: 3.0}},
                    {tag: "Gyroscope", initialReading: {x : 1.0, y: 1.0, z: 1.0}, newReading: {x : 2.0, y: 3.0, z: 4.0}},
                    {tag: "TapSensor", initialReading: {doubleTap: true, tapDirection: TapReading.Z_Both}, newReading: {doubleTap: false, tapDirection: TapReading.X_Both}},
                    {tag: "Compass", initialReading: {azimuth: 1.0, calibrationLevel: 1.0}, newReading: {azimuth: 2.0, calibrationLevel: 3.0}},
                    {tag: "ProximitySensor", initialReading: {near: true}, newReading: {near: false}},
                    {tag: "OrientationSensor", initialReading: {orientation: OrientationReading.LeftUp}, newReading: {orientation: OrientationReading.RightUp}},
                    {tag: "DistanceSensor", initialReading: {distance: 1.0}, newReading: {distance: 2.0}},
                    {tag: "AmbientLightSensor", initialReading: {lightLevel: AmbientLightReading.Twilight}, newReading: {lightLevel: AmbientLightReading.Sunny}},
                    {tag: "Magnetometer", initialReading: {x : 1.0, y: 1.0, z: 1.0, calibrationLevel: 1.0}, newReading:  {x : 2.0, y: 3.0, z: 4.0, calibrationLevel: 5.0}},
                    {tag: "LidSensor", initialReading: {backLidClosed:true, frontLidClosed: true}, newReading:  {backLidClosed:false, frontLidClosed: false}},
                    {tag: "TiltSensor", initialReading: {yRotation: 1.0, xRotation: 1.0}, newReading: {yRotation: 2.0, xRotation: 3.0}},
                    {tag: "RotationSensor", initialReading: {x: 1.0, y: 1.0, z: 1.0}, newReading: {x: 2.0, y: 3.0, z: 4.0}},
                    {tag: "HumiditySensor", initialReading: {relativeHumidity: 1.0, absoluteHumidity: 1.0}, newReading: {relativeHumidity: 2.0, absoluteHumidity: 3.0}},
                    {tag: "HolsterSensor", initialReading: {holstered: true}, newReading: {holstered: false}},
                    {tag: "AmbientTemperatureSensor", initialReading: {temperature: 30.0}, newReading: {temperature: 40.0}},
                    {tag: "LightSensor", initialReading: {illuminance: 1.0}, newReading: {illuminance: 2.0}},
                    {tag: "Altimeter", initialReading: {altitude: 8848}, newReading: {altitude: 9959}},
                    {tag: "IRProximitySensor", initialReading: {reflectance: 0.5}, newReading: {reflectance: 0.6}}
               ];
    }
}
