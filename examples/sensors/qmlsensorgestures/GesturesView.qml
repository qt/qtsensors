// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick
import QtSensors

/* Layout
                                         gesturerect
                                        /
---------------------------------------/
| ----------------------------------- |
| |           id: titleText         | |
| ----------------------------------- |
|                                     |
|                                     |
| ----------------------------------- |
| |           id: detectionText     | |
| ----------------------------------- |
|                                     |
|                                     |
|                                     |
| ----------------- ----------------- |
| | id: valueText | | id: valueText1| |
| ----------------- ----------------- |
|                                     |
|                                     |
|                                     |
| ------------------------------      |
| | id: gestureStartStopButton |      |
| ------------------------------      |
---------------------------------------
*/

Rectangle {
    id: gestureRect
    border.width: 1
    anchors.margins: 5
    property alias enabled: sensorGesture.enabled
    property int count: 0
    property int count1: 0

    SensorGesture {
        id: sensorGesture
        enabled: true
        gestures: availableGestures
        onDetected:{
            if (gesture === "QtSensors.shake")
                gestureRect.count++;
            else
                gestureRect.count1++;
        }
        onEnabledChanged: {
            gestureRect.count = 0;
            gestureRect.count1 = 0;
        }
    }

    Text {
        id: titleText
        anchors.top: gestureRect.top
        anchors.left: gestureRect.left
        anchors.right: gestureRect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: true
        text: "Gesture Counter"
    }

    Text {
        id: detectionText
        anchors.top: titleText.bottom
        anchors.left: gestureRect.left
        anchors.right: gestureRect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        text: "Shake : SecondCounter"
    }

    Text {
        id: valueText
        anchors.top: detectionText.bottom
        anchors.left: gestureRect.left
        width: gestureRect.width / 2
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        text: gestureRect.count
        visible: sensorGesture.enabled
    }

    Text {
        id: valueText1
        anchors.top: detectionText.bottom
        anchors.right: gestureRect.right
        width: gestureRect.width / 2
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        text: gestureRect.count1
        visible: sensorGesture.enabled
    }

    Button{
        id: gestureStartStopButton
        anchors.left: gestureRect.left
        anchors.bottom: gestureRect.bottom
        height: 30
        width: 100
        buttonText: (sensorGesture.enabled ? "Stop" : "Start")
        enabled: true;
        onClicked: {
            if (gestureStartStopButton.buttonText === "Start") {
                sensorGesture.enabled = true;
            }
            else {
                sensorGesture.enabled = false;
            }
        }
    }
}
