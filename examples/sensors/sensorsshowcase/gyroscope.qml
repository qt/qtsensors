/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

