// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

ApplicationWindow {
    title: "Sensors Showcase"
    id: mainWindow
    width: 540
    height: 1200
    visible: true
    color: "dimgray"

    property int titleHeight: height/7
    readonly property real buttonHeight: height/7
    property int textHeight: height/24
    readonly property int buttonFontSize: 30
    readonly property int textFontSize: 20
    readonly property int titleFontSize: 35
    readonly property int titleTopMargin: mainWindow.height/24

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: ColumnLayout {
            width: stack.width
            Text {
                Layout.topMargin: mainWindow.height/12
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: titleHeight
                text: "Sensors Showcase"
                color: "White"
                font.pixelSize: titleFontSize
            }

            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: stack.width
                text: "Accelerometer"
                font.pixelSize: buttonFontSize
                onClicked: stack.push("qrc:/accelerometer.qml")
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: stack.width
                text: "Proximity"
                font.pixelSize: buttonFontSize
                onClicked: stack.push("qrc:/proximity.qml")
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: stack.width
                text: "Compass"
                font.pixelSize: buttonFontSize
                onClicked: stack.push("qrc:/compass.qml")
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: stack.width
                text: "Magnetometer"
                font.pixelSize: buttonFontSize
                onClicked: stack.push("qrc:/magnetometer.qml")
            }
            Button {
                Layout.fillHeight: true
                Layout.preferredWidth: stack.width
                text: "Gyroscope"
                font.pixelSize: buttonFontSize
                onClicked: stack.push("qrc:/gyroscope.qml")
            }
        }
    }
}
