// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
pragma ComponentBehavior: Bound
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Item {
    id: root

    property alias headingFontSize: heading.font.pixelSize
    required property StackView parentStack
    required property int imageSize
    required property int fontSize

    property bool near: false

    ProximitySensor {
        id: proximity
        onReadingChanged: root.near = (reading as ProximityReading).near
    }

    ColumnLayout {
        id: layout

        anchors.fill: parent
        spacing: 10

        Text {
            id: heading
            Layout.preferredWidth: parent.width
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.Wrap
            text: "Proximity"
        }

        Image {
            id: image

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: root.near ? root.imageSize : root.imageSize * 0.75
            Layout.fillHeight: true

            source: "images/qt_logo.png"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: separator
            Layout.topMargin: 10
            Layout.bottomMargin: 10
            Layout.preferredWidth: parent.width * 0.75
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignHCenter
            color: "black"
        }

        Text {
            id: error
            visible: !proximity.active
            Layout.preferredWidth: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: "The proximity sensor is not available on this device!"
            font.pixelSize: root.fontSize
            font.bold: true
            wrapMode: Text.Wrap
            color: "red"
        }

        Text {
            visible: proximity.active
            Layout.fillHeight: true
            font.pixelSize: root.fontSize
            text: "Near: " + root.near
        }

        Button {
            Layout.fillWidth: true
            onClicked: root.parentStack.pop()
            text: "Back"
        }
    }
}
