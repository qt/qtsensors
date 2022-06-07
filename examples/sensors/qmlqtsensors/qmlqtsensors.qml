// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

/* Layout
                                                                                  mainWnd
                                                                                 /
---------------------------------------------------------------------------------
|--------------------------------------------------------------------------------
||                                  labelTitle                                  |
|--------------------------------------------------------------------------------
|-------------------------------------------------------------------------------- <---- tiltLine
|--------------------------------------------------------------------------------
||                                  labelTilt                                   |
|--------------------------------------------------------------------------------
|         / accuracyRect                               / speedRect
|-------------------------------------------||----------------------------------|
|| Accuracy <----- textAccuracy             || Speed <-----textSpeed            |
||  value   <- textAccuracyValue            ||  value    <- textSpeedValue      |
|| ----------------- ------------------     || --------------- ---------------- |
|| | accuracyLower | | accuracyHigher |     || | speedLower  | | speedHigher  | |
|| ----------------- ------------------     || --------------- ---------------- |
|------------------------------------------ ||----------------------------------|
| -----------
| |Calibrate|    <------------------ calibrate
| -----------
| ---------
| |Degree |    <-------------------- useRadian                   X Rotation: 0  <------------------ xrottext
| ---------
| ---------
| |Start  |    <-------------------- tiltStart                   Y Rotation: 0  <------------------ yrottext
| ---------
|-------------------------------------------------------------------------------- <---- ambientlightLine
|--------------------------------------------------------------------------------
||                                  labelAmbientLight                           |
|--------------------------------------------------------------------------------
| ---------
| |Start  |    <-------------------- ablStart                    Ambient light: -  <--------------- abltext
| ---------
|-------------------------------------------------------------------------------- <---- proximityLine
|--------------------------------------------------------------------------------
||                                  labelProximityLight                           |
|--------------------------------------------------------------------------------
| ---------
| |Start  |    <-------------------- proxiStart                  Proximity: -  <--------------- proxitext
| ---------
------------------------------------------------------------------------------
*/

//Import the declarative plugins
import QtQuick
import "components"

//! [0]
import QtSensors
//! [0]

ApplicationWindow {

    anchors.fill: parent

    // Sensor types used
    //! [1]
    TiltSensor {
        id: tilt
        active: false
    }
    //! [1]

    AmbientLightSensor {
        id: ambientlight
        active: false
        //! [5]
        onReadingChanged: {
            if (reading.lightLevel == AmbientLightReading.Dark)
                ambientlighttext.text = "Ambient light: Dark";
            else if (reading.lightLevel == AmbientLightReading.Twilight)
                ambientlighttext.text = "Ambient light: Twilight";
            else if (reading.lightLevel == AmbientLightReading.Light)
                ambientlighttext.text = "Ambient light: Light";
            else if (reading.lightLevel == AmbientLightReading.Bright)
                ambientlighttext.text = "Ambient light: Bright";
            else if (reading.lightLevel == AmbientLightReading.Sunny)
                ambientlighttext.text = "Ambient light: Sunny";
            else
                ambientlighttext.text = "Ambient light: Unknown";
        }
        //! [5]
    }

    ProximitySensor {
        id: proxi
        active: false
    }

    Column {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 5

        Text {
            id: labelTitle
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
            font.bold: true
            text: "QML QtSensors"
        }

        // Tilt region
        Divider { label: "TiltSensor" }

        Row {
            spacing: 20
            width: parent.width
            anchors.margins: 5
            Button {
                id: calibrate
                height: 30
                width: 80
                text: "Calibrate"
                onClicked: tilt.calibrate();
            }
            Text {
                id: xrottext
                height: 30
                verticalAlignment: Text.AlignVCenter
                //! [3]
                text: "X Rotation: " + (tilt.reading ? tilt.reading.xRotation.toFixed(2) + "°" : "Unknown")
                //! [3]
            }
        }
        Row {
            spacing: 20
            width: parent.width
            anchors.margins: 5
            Button {
                id: tiltStart
                height: 30
                width: 80
                text: tilt.active ? "Stop" : "Start"
                onClicked: {
                    //! [2]
                    tilt.active = (tiltStart.text === "Start");
                    //! [2]
                }
            }
            Text {
                id: yrottext
                height: 30
                verticalAlignment: Text.AlignVCenter
                //! [4]
                text: "Y Rotation: " + (tilt.reading ? tilt.reading.yRotation.toFixed(2) + "°" : "Unknown")
                //! [4]
            }
        }

        Divider { label: "AmbientLightSensor" }

        Row {
            spacing: 20
            width: parent.width
            anchors.margins: 5

            Button{
                id: ambientlightStart
                height: 30
                width: 80
                text: ambientlight.active ? "Stop" : "Start"
                onClicked: {
                    ambientlight.active = (ambientlightStart.text === "Start" ? true : false);
                }
            }

            Text {
                id: ambientlighttext
                height: 30
                verticalAlignment: Text.AlignVCenter
                text: "Ambient light: Unknown"
            }
        }

        // Proximity region
        Divider { label: "ProximitySensor" }

        Row {
            spacing: 20
            width: parent.width
            anchors.margins: 5

            Button {
                id: proxiStart
                height: 30
                width: 80
                text: proxi.active ? "Stop" : "Start"

                onClicked: {
                    proxi.active = (proxiStart.text === "Start"  ? true: false);
                }
            }

            Text {
                id: proxitext
                height: 30
                verticalAlignment: Text.AlignVCenter
                //! [6]
                text: "Proximity: " +
                      (proxi.active ? (proxi.reading.near ? "Near" : "Far") : "Unknown")
                //! [6]
            }
        }
    }
}
