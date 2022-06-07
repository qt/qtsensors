// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Rectangle {
    id: root
    color: "dimgray"
    property bool near: false

    ProximitySensor {
        id: proximity
        active: true
        onReadingChanged: {
            root.near = reading.near
        }
    }

    ColumnLayout {
        anchors.fill: parent
        id: layout

        Text {
            Layout.topMargin: titleTopMargin
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: textHeight
            color: "White"
            text: "Proximity"
            font.pixelSize: titleFontSize
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.near ? root.height/3 : root.height/4
            Layout.preferredHeight: root.near ? root.height/3 : root.height/4
            source: "qrc:/images/qt_logo.png"
            fillMode: Image.PreserveAspectFit
        }
        Text {
            visible: !proximity
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            font.pixelSize: textFontSize
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            color: "White"
            text: "The proximity sensor is not available on this device!"
        }
        Text {
//            visible: typeof proximity.available !== 'undefined'
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Near: " + root.near
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
