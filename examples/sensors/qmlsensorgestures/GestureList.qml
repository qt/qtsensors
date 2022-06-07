// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick
import QtSensors

/* Layout
                                         gesturerect
                                        /
---------------------------------------/
|-------------------------------------|
||          labelGesture             ||
|-------------------------------------|
|-------------------------------------|
||                                   |<---- gestureListRect
||                                   ||
||                                   ||
||           gestureList             ||
||                                   ||
||                                   ||
||                                   ||
||                                   ||
||                                   ||
||                                   ||
|-------------------------------------|
*/

Rectangle {
    id: gesturerect
    border.width: 1
    anchors.margins: 5

    property string selectedGesture: ""

    SensorGesture {
        id: gesture
    }

    Text {
        id: labelGesture
        anchors.top: gesturerect.top
        anchors.left: gesturerect.left
        anchors.right: gesturerect.right
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 30
        font.bold: true
        text: "Gestures"
    }

    Rectangle {
        id: gestureListRect
        border.width: 1
        anchors.top: labelGesture.bottom
        anchors.left: gesturerect.left
        anchors.right: gesturerect.right
        anchors.bottom: gesturerect.bottom
        anchors.margins: 5

//! [4]
        ListView {
            id: gestureList
//! [4]
            anchors.fill: gestureListRect
            anchors.margins: 5
//! [5]
            model: gesture.availableGestures
//! [5]
            focus: true
            currentIndex: -1
            delegate: gestureListDelegate
            clip: true
//! [6]
        }
//! [6]

        Component {
            id: gestureListDelegate

            Rectangle {
                width: gestureList.width
                height: itemText.height
                color: (index === gestureList.currentIndex ? "#999933" : "#FFFFFF")

                Text {
                    id: itemText
                    text: model.modelData
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        gestureList.currentIndex = index
                        selectedGesture = model.modelData
                    }
                }
            }
        }
    }
}
