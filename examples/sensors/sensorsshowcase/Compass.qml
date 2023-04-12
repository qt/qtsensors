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
    required property int fontSize
    required property int imageSize

    property real azimuth: 30

    Compass {
        id: compass
        active: true
        dataRate: 7
        onReadingChanged: root.azimuth = -(reading as CompassReading).azimuth
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
            text: "Compass"
        }

        Image {
            id: arrow

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: root.imageSize * 1.25
            Layout.fillHeight: true

            source: "images/compass.svg"
            fillMode: Image.PreserveAspectFit
            rotation: root.azimuth
        }

        Rectangle {
            id: separator

            Layout.topMargin: 10
            Layout.preferredWidth: parent.width * 0.75
            Layout.preferredHeight: 1
            Layout.alignment: Qt.AlignHCenter
            color: "black"
        }

        Text {
            id: info
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.topMargin: 10
            text: "Azimuth: " + root.azimuth.toFixed(2) + "°"
            font.pixelSize: root.fontSize
        }

        Button {
            Layout.fillWidth: true
            onClicked: root.parentStack.pop()
            text: "Back"
        }
    }
}
