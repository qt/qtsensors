/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

//Import the declarative plugins
import QtQuick 2.0

//! [0]
import QtSensors 5.0
//! [0]

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
|| @ 0 Degree   <- selButton0DegreeAccuracy || @ Slow   <- selButtonSlowSpeed   |
|| O 1 Degree   <- selButton1DegreeAccuracy || O Medium <- selButtonMediumSpeed |
|| O 5 Degree   <- selButton5DegreeAccuracy || O Fast   <- selButtonFastSpeed   |
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

Rectangle {
    id: mainWnd
    x: 0
    y: 0
    width: 320
    height: 480
    color: "#ececec"

    Text {
        id: labelTitle
        anchors.top: mainWnd.top
        anchors.topMargin: 25
        anchors.left: mainWnd.left
        anchors.right: mainWnd.right

        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 30
        font.bold: true
        text: "QML QtSensors"
    }

    //Tile region

    Rectangle {
        id: tiltLine
        anchors.top: labelTitle.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        border.width: 1
        height: 1
        border.color: "#888888"
    }

    Text {
        id: labelTilt
        anchors.top: tiltLine.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.right: mainWnd.right

        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        text: "TiltSensor"
    }

//! [1]
    TiltSensor {
        id: tilt
        unit: TiltSensor.Degrees
        enabled: false
        accuracy: 1.0
    }
//! [1]

    Rectangle{
        id: accuracyRect
        anchors.top: labelTilt.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        anchors.right: mainWnd.right
        anchors.rightMargin: mainWnd.width / 2
        height: 110
        color: "transparent"

        Text{
            id: textAccuracy
            anchors.top: accuracyRect.top
            anchors.left: accuracyRect.left
            text: "Accuracy"
            font.bold: true
        }

        RadioButton{
            id: selButton0DegreeAccuracy
            anchors.top: textAccuracy.bottom
            anchors.left: accuracyRect.left
            anchors.right: accuracyRect.right
            anchors.rightMargin: 10
            checked: true
            text: "0 Degree"

            onClicked:{
                selButton1DegreeAccuracy.setCheck(false);
                selButton5DegreeAccuracy.setCheck(false);
                tilt.accuracy = 0.0;
            }
        }

        RadioButton{
            id: selButton1DegreeAccuracy
            anchors.top: selButton0DegreeAccuracy.bottom
            anchors.left: accuracyRect.left
            anchors.right: accuracyRect.right
            anchors.rightMargin: 10
            checked: false
            text: "1 Degree"

            onClicked:{
                selButton0DegreeAccuracy.setCheck(false);
                selButton5DegreeAccuracy.setCheck(false);
                tilt.accuracy = (tilt.unit == TiltSensor.Degrees ? 1.0 : (3.14 / 180.0));
            }
        }

        RadioButton{
            id: selButton5DegreeAccuracy
            anchors.top: selButton1DegreeAccuracy.bottom
            anchors.left: accuracyRect.left
            anchors.right: accuracyRect.right
            anchors.rightMargin: 10
            checked: false
            text: "5 Degree"

            onClicked:{
                selButton0DegreeAccuracy.setCheck(false);
                selButton1DegreeAccuracy.setCheck(false);
                tilt.accuracy = (tilt.unit == TiltSensor.Degrees ? 5.0 : (5.0 * 3.14 / 180.0));
            }
        }
    }

    Rectangle{
        id: speedRect
        anchors.top: labelTilt.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: mainWnd.width / 2
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        height: 110
        color: "transparent"

        Text{
            id: textSpeed
            anchors.top: speedRect.top
            anchors.left: speedRect.left
            text: "Speed"
            font.bold: true
        }

        RadioButton{
            id: selButtonSlowSpeed
            anchors.top: textSpeed.bottom
            anchors.left: speedRect.left
            anchors.right: speedRect.right
            anchors.rightMargin: 10
            checked: true
            text: "Slow"

            onClicked:{
                selButtonMediumSpeed.setCheck(false);
                selButtonFastSpeed.setCheck(false);
                tilt.speed = TiltSensor.Slow;
            }
        }


        RadioButton{
            id: selButtonMediumSpeed
            anchors.top: selButtonSlowSpeed.bottom
            anchors.left: speedRect.left
            anchors.right: speedRect.right
            anchors.rightMargin: 10
            checked: false
            text: "Medium"

            onClicked:{
                selButtonSlowSpeed.setCheck(false);
                selButtonFastSpeed.setCheck(false);
                tilt.speed = TiltSensor.Medium;
            }
        }


        RadioButton{
            id: selButtonFastSpeed
            anchors.top: selButtonMediumSpeed.bottom
            anchors.left: speedRect.left
            anchors.right: speedRect.right
            anchors.rightMargin: 10
            checked: false
            text: "Fast"

            onClicked:{
                selButtonSlowSpeed.setCheck(false);
                selButtonMediumSpeed.setCheck(false);
                tilt.speed = TiltSensor.Fast;
            }
        }
    }


    Button{
        id: calibrate
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        anchors.top: accuracyRect.bottom
        height: 30
        width: 80
        text: "Calibrate"

        onClicked:{
            tilt.calibrate();
        }
    }

    Button{
        id: useRadian
        anchors.top: calibrate.bottom
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        height: 30
        width: 80
        text: (tilt !== null ? tilt.unit === TiltSensor.Radians ? "Degree" : "Radians" : "Degree")

        onClicked:{
            tilt.unit = (useRadian.text === "Radians"  ? TiltSensor.Radians : TiltSensor.Degrees);
        }
    }

    Button{
        id: tiltStart
        anchors.top: useRadian.bottom
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        height: 30
        width: 80
        text: tilt.enabled ? "Stop" : "Start"

        onClicked:{
//! [2]
            tilt.enabled = (tiltStart.text === "Start"  ? true: false);
//! [2]
        }
    }

    Text {
        id: xrottext
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        anchors.left: useRadian.right
        anchors.leftMargin: 15
        anchors.top: useRadian.top
        anchors.bottom: useRadian.bottom
        verticalAlignment: Text.AlignVCenter
//! [3]
        text: "X Rotation: " + tilt.xRotation + (tilt.unit === TiltSensor.Radians ? " rad" : "°")
//! [3]
    }

    Text {
        id: yrottext
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        anchors.left: tiltStart.right
        anchors.leftMargin: 15
        anchors.top: tiltStart.top
        anchors.bottom: tiltStart.bottom
        verticalAlignment: Text.AlignVCenter
//! [4]
        text: "Y Rotation: " + tilt.yRotation + (tilt.unit === TiltSensor.Radians ? " rad" : "°")
//! [4]
    }

    //Ambient Light region

    Rectangle {
        id: ambientlightLine
        anchors.top: tiltStart.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        border.width: 1
        height: 1
        border.color: "#888888"
    }

    Text {
        id: labelAmbientLight
        anchors.top: ambientlightLine.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.right: mainWnd.right

        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        text: "AmbientLightSensor"
    }

    AmbientLightSensor {
        id: ambientlight
        enabled: false
//! [5]
        onLightLevelChanged:{
            if (ambientlight.lightLevel == AmbientLightSensor.Unknown)
                ambientlighttext.text = "Ambient light: Unknown";
            else if (ambientlight.lightLevel == AmbientLightSensor.Dark)
                ambientlighttext.text = "Ambient light: Dark";
            else if (ambientlight.lightLevel == AmbientLightSensor.Twilight)
                ambientlighttext.text = "Ambient light: Twilight";
            else if (ambientlight.lightLevel == AmbientLightSensor.Light)
                ambientlighttext.text = "Ambient light: Light";
            else if (ambientlight.lightLevel == AmbientLightSensor.Bright)
                ambientlighttext.text = "Ambient light: Bright";
            else if (ambientlight.lightLevel == AmbientLightSensor.Sunny)
                ambientlighttext.text = "Ambient light: Sunny";
        }
//! [5]
    }

    Button{
        id: ambientlightStart
        anchors.top: labelAmbientLight.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        height: 30
        width: 80
        text: ambientlight.enabled ? "Stop" : "Start"

        onClicked:{
            ambientlight.enabled = (ambientlightStart.text === "Start"  ? true: false);
        }
    }

    Text {
        id: ambientlighttext
        anchors.left: ambientlightStart.right
        anchors.leftMargin: 15
        anchors.top: ambientlightStart.top
        anchors.bottom: ambientlightStart.bottom
        verticalAlignment: Text.AlignVCenter
        text: "Ambient light: -"
    }

    //Proximity region

    Rectangle {
        id: proximityLine
        anchors.top: ambientlightStart.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        anchors.right: mainWnd.right
        anchors.rightMargin: 5
        border.width: 1
        height: 1
        border.color: "#888888"
    }

    Text {
        id: labelProximityLight
        anchors.top: proximityLine.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.right: mainWnd.right
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        text: "ProximitySensor"
    }

    ProximitySensor {
        id: proxi
        enabled: false
    }

    Button{
        id: proxiStart
        anchors.top: labelProximityLight.bottom
        anchors.topMargin: 5
        anchors.left: mainWnd.left
        anchors.leftMargin: 5
        height: 30
        width: 80
        text: proxi.enabled ? "Stop" : "Start"

        onClicked:{
            proxi.enabled = (proxiStart.text === "Start"  ? true: false);
        }
    }

    Text {
        id: proxitext
        anchors.left: proxiStart.right
        anchors.leftMargin: 15
        anchors.top: proxiStart.top
        anchors.bottom: proxiStart.bottom
        verticalAlignment: Text.AlignVCenter
//! [6]
        text: "Proximity: " + (proxi.near ? "near" : "far")
//! [6]
    }
}
