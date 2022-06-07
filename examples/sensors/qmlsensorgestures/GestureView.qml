// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick

//! [0]
import QtSensors
//! [0]

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
| ----------------------------------- |
| |           id: valueText         | |
| ----------------------------------- |
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
//! [2]
    property alias gestureId: sensorGesture.gestures
//! [2]
    property alias gestureTitle: titleText.text
    property alias enabled: sensorGesture.enabled
    property string oldGesture: ""
    property int count: 0

//! [1]
    SensorGesture {
        id: sensorGesture
        enabled: false
        onDetected: {
            if (gesture !== oldGesture)
                count = 0;
            valueText.text = gesture + " " + count;
            oldGesture = gesture;
            count++;
        }
        onEnabledChanged: {
            valueText.text = ""
        }
    }
//! [1]

    Text {
        id: titleText
        anchors.top: gestureRect.top
        anchors.left: gestureRect.left
        anchors.right: gestureRect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 20
        font.bold: true
        text: ""
    }

    Text {
        id: detectionText
        anchors.top: titleText.bottom
        anchors.left: gestureRect.left
        anchors.right: gestureRect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
        text: "Detection:"
    }

    Text {
        id: valueText
        anchors.top: detectionText.bottom
        anchors.left: gestureRect.left
        anchors.right: gestureRect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 15
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
