// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick

//Implementation of the Button control.
Item {
    id: button
    width: 30
    height: 100
    property alias text: innerText.text
    signal clicked

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: (button.enabled ? "images/button_background_normal.png" : "images/button_background_disabled.png")
    }

    Text {
        id: innerText
        anchors.centerIn: parent
        color: "white"
        font.bold: true
    }

    //Mouse area to react on click events
    MouseArea {
        anchors.fill: button
        onClicked: { button.clicked();}
        onPressed: {
            backgroundImage.source = "images/button_background_pressed.png" }
        onReleased: {
            backgroundImage.source = (button.enabled ? "images/button_background_normal.png" : "images/button_background_disabled.png")
        }
    }
}
