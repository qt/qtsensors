/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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
import QtSensors 5.0

/* Layout
                                                                              tiltrect
                                                                             /
----------------------------------------------------------------------------/
| Accuracy <----- textAccuracy
| @ 0 Degree   <- selButton0DegreeAccuracy @ Slow   <- selButtonSlowSpeed
| O 1 Degree   <- selButton1DegreeAccuracy O Medium <- selButtonMediumSpeed
| O 5 Degree   <- selButton5DegreeAccuracy O Fast   <- selButtonFastSpeed
| -----------
| |calibrate|    <------------------ calibrate
| -----------
| ---------
| |degree |    <-------------------- useRadian
| ---------
| X Rotation: 0  <------------------ xrottext
| Y Rotation: 0  <------------------ yrottext
| ---------
| |start  |    <-------------------- tiltStart
| ---------                     ablrect
------------------------------ /
------------------------------/
| Ambient light: -  <--------------- abltext
| ---------
| |start  |    <-------------------- ablStart
| ---------                     proxirect
------------------------------ /
------------------------------/
| Proximity: false  <--------------- proxitext
| ---------
| |start  |    <-------------------- proxiStart
| ---------
------------------------------------------------------------------------------

*/

Rectangle {
    width: 320
    height: 480

    Rectangle {
        id: tiltrect
        x: 2
        y: 22
        width: 315
        height: 270
        border.width: 1

        TiltSensor {
            id: tilt
            unit: TiltSensor.Degrees
            enabled: false
            accuracy: 1.0
        }

        Text{
            id: textAccuracy
            x: 5
            y: 20
            text: "Accuracy"
        }

        Text{
            id: textSpeed
            x: 150
            y: 20
            text: "Speed"
        }

        SelectionButton{
            id: selButton0DegreeAccuracy
            x: 5
            y: 45
            checked: true
            text: "0 Degree"
            onClicked:{
                selButton1DegreeAccuracy.setCheck(false);
                selButton5DegreeAccuracy.setCheck(false);
                tilt.accuracy = 0.0;
            }
        }
        SelectionButton{
            id: selButtonSlowSpeed
            x: 150
            y: 45
            checked: true
            text: "Slow"
            onClicked:{
                selButtonMediumSpeed.setCheck(false);
                selButtonFastSpeed.setCheck(false);
                tilt.speed = TiltSensor.Slow;
            }
        }

        SelectionButton{
            id: selButton1DegreeAccuracy
            x: 5
            y: 70
            checked: false
            text: "1 Degree"
            onClicked:{
                selButton0DegreeAccuracy.setCheck(false);
                selButton5DegreeAccuracy.setCheck(false);
                tilt.accuracy = (tilt.unit == TiltSensor.Degrees ? 1.0 : (3.14 / 180.0));
            }
        }
        SelectionButton{
            id: selButtonMediumSpeed
            x: 150
            y: 70
            checked: false
            text: "Medium"
            onClicked:{
                selButtonSlowSpeed.setCheck(false);
                selButtonFastSpeed.setCheck(false);
                tilt.speed = TiltSensor.Medium;
            }
        }

        SelectionButton{
            id: selButton5DegreeAccuracy
            x: 5
            y: 95
            checked: false
            text: "5 Degree"
            onClicked:{
                selButton0DegreeAccuracy.setCheck(false);
                selButton1DegreeAccuracy.setCheck(false);
                tilt.accuracy = (tilt.unit == TiltSensor.Degrees ? 5.0 : (5.0 * 3.14 / 180.0));
            }
        }

        SelectionButton{
            id: selButtonFastSpeed
            x: 150
            y: 95
            checked: false
            text: "Fast"
            onClicked:{
                selButtonSlowSpeed.setCheck(false);
                selButtonMediumSpeed.setCheck(false);
                tilt.speed = TiltSensor.Fast;
            }
        }

        Button{
            id: calibrate
            x: 5
            y: 145
            text: "calibrate"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: false
            color: "lightyellow"

            onClicked:{
                tilt.calibrate();
                unchecktimer.running = true;
            }
            Timer {
                id: unchecktimer
                interval: 1000; running: false; repeat: false
                onTriggered: {
                    calibrate.checked = false;
                    calibrate.color = "lightyellow";
                }
            }
        }

        Button{
            id: useRadian
            x: 5
            y: 170
            text: "degree"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: (tilt.unit == TiltSensor.Radians ? true : false)
            color: "lightyellow"

            onClicked:{
                tilt.unit = (useRadian.checked ? TiltSensor.Radians : TiltSensor.Degrees);
                if (useRadian.checked)
                    useRadian.text = "radian";
                else
                    useRadian.text = "degree";
            }
        }

        Text {
            id: xrottext
            x:5
            y:195
            text: "X Rotation: " + tilt.xRotation
        }
        Text {
            id: yrottext
            x:5
            y:220
            text: "Y Rotation: " + tilt.yRotation
        }
        Button{
            id: tiltStart
            x: 5
            y: 245
            text: tilt.enabled ? "running" : "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            color: tilt.enabled ? checkColor : unCheckColor
            checked: tilt.enabled

            onClicked:{
                tilt.enabled = tiltStart.checked;
                if (tiltStart.checked)
                    tiltStart.text = "running";
                else
                    tiltStart.text = "stopped";
            }
        }
    }

    Rectangle {
        id: ambientlightrect
        x: 2
        y: tiltrect.y + tiltrect.height + 10
        width: 315
        height: 70
        border.width: 1

        AmbientLightSensor {
            id: ambientlight
            enabled: false
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
        }
        Text {
            id: ambientlighttext
            x: 5
            y: 10
            text: "Ambient light: -"
        }
        Button{
            id: ambientlightStart
            x: 5
            y: 35
            text: ambientlight.enabled ? "running" : "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            color: ambientlight.enabled ? checkColor : unCheckColor
            checked: ambientlight.enabled

            onClicked:{
                ambientlight.enabled = ambientlightStart.checked;
                if (ambientlightStart.checked)
                    ambientlightStart.text = "running";
                else
                    ambientlightStart.text = "stopped";
            }
        }
    }

    Rectangle {
        id: proxirect
        x: 2
        y: ambientlightrect.y + ambientlightrect.height + 10
        width: 315
        height: 70
        border.width: 1

        ProximitySensor {
            id: proxi
            enabled: true
        }
        Text {
            id: proxitext
            x: 5
            y: 10
            text: "Proximity: " + proxi.near
        }
        Button{
            id: proxiStart
            x: 5
            y: 35
            text: proxi.enabled ? "running" : "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            color: proxi.enabled ? checkColor : unCheckColor
            checked: proxi.enabled

            onClicked:{
                proxi.enabled = proxiStart.checked;
                if (proxiStart.checked)
                    proxiStart.text = "running";
                else
                    proxiStart.text = "stopped";
            }
        }
    }
}
