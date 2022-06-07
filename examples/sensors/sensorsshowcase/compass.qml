// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Rectangle {
    id: root
    color: "dimgray"
    property real azimuth: 30
    readonly property real buttonHeight: height/8

    Compass {
        id: compass
        active: true
        dataRate: 7
        onReadingChanged: {
            root.azimuth = -reading.azimuth
        }
    }

    ColumnLayout {
        anchors.fill: parent
        id: layout

        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: titleHeight
            Layout.topMargin: titleTopMargin
            verticalAlignment: Text.AlignVCenter
            color: "White"
            text: "Compass"
            font.pixelSize: titleFontSize
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.width
            Layout.preferredHeight: root.height
            id: arrow
            source: "qrc:/images/compass.svg"
            fillMode: Image.PreserveAspectFit
            rotation:root.azimuth
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Azimuth: " + root.azimuth.toFixed(2) + "°"
            font.pixelSize: textFontSize
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
