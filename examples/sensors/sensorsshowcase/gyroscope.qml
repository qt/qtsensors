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
    Gyroscope {
        id: gyroscope
        active: true
        dataRate: 25

        property variant lastTimeStamp: 0

        property real x: 0
        property real y: 0
        property real z: 0

        onReadingChanged: {

            x = reading.x
            y = reading.y
            z = reading.z

            var firstCall = false
            if (lastTimeStamp == 0) {
                firstCall = true
            }

            var timeSinceLast = reading.timestamp - lastTimeStamp
            lastTimeStamp = reading.timestamp

            //Skipping the initial time jump from 0
            if (firstCall === true) return

            var normalizedX = reading.x * (timeSinceLast/1000000)
            imageXRotation.angle += normalizedX

            var normalizedY = reading.y * (timeSinceLast/1000000)
            imageYRotation.angle -= normalizedY

            var normalizedZ = reading.z * (timeSinceLast/1000000)
            imageZRotation.angle += normalizedZ
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
            text: "Gyroscope"
            font.pixelSize: titleFontSize
        }

        Image {
            id: image
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.height/3
            Layout.preferredHeight: root.height/3
            source: "qrc:/images/qt_logo.png"
            fillMode: Image.PreserveAspectFit

            transform: [
                Rotation {
                    id: imageXRotation
                    origin.x: layout.width/2
                    origin.y: layout.height/3
                    axis.x: 1
                    axis.y: 0
                    axis.z: 0
                    angle: 0
                },
                Rotation {
                    id: imageYRotation
                    origin.x: layout.width/2
                    origin.y: layout.height/3
                    axis.x: 0
                    axis.y: 1
                    axis.z: 0
                    angle: 0
                },
                Rotation {
                    id: imageZRotation
                    origin.x: layout.width/2
                    origin.y: layout.height/3
                    axis.x: 0
                    axis.y: 0
                    axis.z: 1
                    angle: 0
                }
            ]
        }

        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "X: " + gyroscope.x.toFixed(2)
            font.pixelSize: textFontSize
        }

        ProgressBar {
            id: xbar
            value: 0.5 + (gyroscope.x / 1000)
            Layout.preferredWidth: root.width
        }

        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Y: " + gyroscope.y.toFixed(2)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: ybar
            value: 0.5 + (gyroscope.y / 1000)
            Layout.preferredWidth: root.width
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Z: " + gyroscope.z.toFixed(2)
            font.pixelSize: textFontSize
        }
        ProgressBar {
            id: zbar
            value: 0.5 + (gyroscope.z / 1000)
            Layout.preferredWidth: root.width
        }
        Button {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: root.width
            Layout.preferredHeight: buttonHeight
            text:"Reset rotation"
            font.pixelSize: buttonFontSize
            onClicked: {
                resetRotations()
            }
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

