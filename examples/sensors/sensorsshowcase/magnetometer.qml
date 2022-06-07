// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Rectangle {
    id: root
    color: "dimgray"

    property real magnetRotation: 40
    property real magnetometerX: 0
    property real magnetometerY: 0
    property real magnetometerZ: 0
    property int barScaleFactor: 10000

//! [0]
    Magnetometer {
        id: magnetometer
        active: true
        dataRate: 25
        onReadingChanged: {
            root.magnetometerX = reading.x
            root.magnetometerY = reading.y
            root.magnetometerZ = reading.z
            root.magnetRotation = ((Math.atan2(reading.x, reading.y) / Math.PI) * 180)
        }
    }
//! [0]

    ColumnLayout {
        anchors.fill: parent
        id: layout

        Text {
            Layout.topMargin: titleTopMargin
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: titleHeight
            verticalAlignment: Text.AlignVCenter
            color: "White"
            text: "Magnetometer"
            font.pixelSize: titleFontSize
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.width / 2
            Layout.preferredHeight: root.height / 2
            source: "qrc:/images/magnet.svg"
            fillMode: Image.PreserveAspectFit
            rotation: magnetRotation
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "X: " + root.magnetometerX.toFixed(9)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: xbar
            value: 0.5 + (root.magnetometerX * barScaleFactor)
            Layout.preferredWidth: root.width
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Y: " + root.magnetometerY.toFixed(9)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: ybar
            value: 0.5 + (root.magnetometerY * barScaleFactor)
            Layout.preferredWidth: root.width
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Z: " + root.magnetometerZ.toFixed(9)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: zbar
            value: 0.5 + (root.magnetometerZ * barScaleFactor)
            Layout.preferredWidth: root.width
        }
        Button {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: root.width
            Layout.preferredHeight: buttonHeight
            text:"Back"
            font.pixelSize: buttonFontSize
            onClicked:stack.pop()
        }
    }
}
