// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Rectangle {
    id: root
    color: "dimgray"

    function resetRotations() {
        imageXRotation.angle = 0
        imageYRotation.angle = 0
        imageZRotation.angle = 0
    }

//! [0]
    Accelerometer {
        id: accelerometer
        active: true
        dataRate: 25

        property real x: 0
        property real y: 0
        property real z: 0

        onReadingChanged: {
            x = reading.x
            y = reading.y
            z = reading.z

            imageTranslation.x = -reading.x * 10
            imageTranslation.y = reading.y * 10
        }
    }
//! [0]

    ColumnLayout {
        anchors.fill: parent
        id: layout

        Text {
            Layout.topMargin: titleTopMargin
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: textHeight
            color: "White"
            text: "Accelerometer"
            font.pixelSize: titleFontSize
        }

        Image {
            id: image
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.width/2
            Layout.preferredHeight: root.height/3
            source: "qrc:/images/qt_logo.png"
            fillMode: Image.PreserveAspectFit

            transform: [
                Translate {
                    id: imageTranslation
                    x: 0
                    y: 0
                }
            ]
        }

        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "X: " + accelerometer.x.toFixed(2)
            font.pixelSize: textFontSize
        }

        ProgressBar {
            id: xbar
            value: 0.5 + (accelerometer.x / 100)
            Layout.preferredWidth: root.width
        }

        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Y: " + accelerometer.y.toFixed(2)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: ybar
            value: 0.5 + (accelerometer.y / 100)
            Layout.preferredWidth: root.width
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Z: " + accelerometer.z.toFixed(2)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: zbar
            value: 0.5 + (accelerometer.z / 100)
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

