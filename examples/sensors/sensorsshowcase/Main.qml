// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root

    readonly property int dynamicMargin: width / 12
    readonly property int defaultFontSize: 20
    readonly property int headingFontSize: 35
    readonly property int imageSize: width / 2

    width: 420
    height: 760
    visible: true
    title: "Sensors Showcase"

    StackView {
        id: stack

        // Pushes the object and forwards the properties
        function pusher(object : string) : void
        {
            stack.push(object, {
                    parentStack: stack,
                    fontSize: root.defaultFontSize,
                    headingFontSize: root.headingFontSize,
                    imageSize: root.imageSize
                })
        }

        anchors.fill: parent
        anchors.margins: root.dynamicMargin

        initialItem: Item {
            ColumnLayout {
                id: initialItem

                anchors.bottomMargin: (root.width < root.height) ? 2 * root.dynamicMargin : 0
                anchors.fill: parent
                spacing: 5

                Text {
                    Layout.bottomMargin: root.dynamicMargin
                    Layout.preferredWidth: parent.width
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pixelSize: root.headingFontSize
                    text: "Sensors Showcase"
                    wrapMode: Text.WordWrap
                }

                component CustomButton: Button {
                    Layout.alignment: Qt.AlignCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.pixelSize: root.defaultFontSize
                    highlighted: true
                }

                CustomButton {
                    text: "Accelerometer"
                    onClicked: stack.pusher("Accelerometer.qml")
                }
                CustomButton {
                    text: "Proximity"
                    onClicked: stack.pusher("Proximity.qml")
                }
                CustomButton {
                    text: "Compass"
                    onClicked: stack.pusher("Compass.qml")
                }
                CustomButton {
                    text: "Magnetometer"
                    onClicked: stack.pusher("Magnetometer.qml")
                }
                CustomButton {
                    text: "Gyroscope"
                    onClicked: stack.pusher("Gyroscope.qml")
                }
            }
        }
    }

}
