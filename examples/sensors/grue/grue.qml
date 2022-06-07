// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtSensors
import QtQuick.Layouts
import QMLGrueSensor

Rectangle {
    id: root
    anchors.fill: parent
    color: "black"

    property int percent: -1
    property string text: ""
    property real grueOpacity: 0.0

    function updateStatus(newPercent, newOpacity, newText) {
        if (root.percent === newPercent)
            return;

        // Delay updating the visual status to prevent flicker
        timer.interval = (newPercent < root.percent) ? 500 : 0;

        root.percent = newPercent;
        root.text = newText;
        root.grueOpacity = newOpacity;

        timer.start()
    }

    Timer {
        id: timer
        running: false
        repeat: false
        onTriggered: {
            text.text = root.text
            grueimg.opacity = root.grueOpacity
        }
    }

    QMLGrueSensor {
        id: sensor
        active: true
        onReadingChanged: {
            var percent = reading.chanceOfBeingEaten;
            if (percent === 0) {
                updateStatus(percent, 0.0, "It is light.<br>You are safe from Grues.");
            }
            else if (percent === 100) {
                updateStatus(percent, 1.0, "You have been eaten by a Grue!");
                sensor.active = false;
            }
            else if (percent > 0) {
                updateStatus(percent, 0.05 + (percent * 0.001),
                             "It is dark.<br>You are " + percent +" % " +
                             "likely to be eaten by a Grue.");
            }
        }
    }

    Text {
        id: text
        anchors.fill: parent
        wrapMode: Text.WordWrap
        text: "I can't tell if you're going to be eaten by a Grue or not. You're on your own!"
        font.pixelSize: 30
        color: "lightgray"
    }

    Image {
        id: grueimg
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        source: "grue.png"
        opacity: 0.0
        Behavior on opacity { PropertyAnimation { duration: 250 } }
    }
}
