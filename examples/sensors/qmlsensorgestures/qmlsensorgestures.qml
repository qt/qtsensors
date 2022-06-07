// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick
import QtSensors

/* Layout
--------------------------------------------------
| ---------------------------------------------- |
| |                                            | |
| |                                            | |
| |                                            | |
| |                 gestureList                | |
| |                                            | |
| |                                            | |
| |                                            | |
| |                                            | |
| |                                            | |
| |                                            | |
| |                                            | |
| |                                            | |
| ---------------------------------------------- |
| ---------------------------------------------- |
| |                                            | |
| |               gesture                      | |
| |                                            | |
| |                                            | |
| ---------------------------------------------- |
| ---------------------------------------------- |
| |                                            | |
| |               gestures                     | |
| |                                            | |
| |                                            | |
| ---------------------------------------------- |
--------------------------------------------------
*/

Rectangle {
    id: viewArea
    width: 320
    height: 460
    color: '#d6d6d6'

    GestureList {
        id: gestureList
        parent: viewArea
        anchors.left: viewArea.left
        anchors.top: viewArea.top
        anchors.right: viewArea.right
        height: viewArea.height / 2
//! [3]
        onSelectedGestureChanged: {
            gesture.enabled = false;
            gesture.gestureId = gestureList.selectedGesture;
//! [3]
            gesture.gestureTitle = gestureList.selectedGesture;
//! [4]
        }
//! [4]
    }

    GestureView {
        id: gesture
        parent: viewArea
        anchors.left: viewArea.left
        anchors.top: gestureList.bottom
        anchors.right: viewArea.right
        height: 100
    }

    GesturesView {
        id: gestures
        parent: viewArea
        anchors.left: viewArea.left
        anchors.top: gesture.bottom
        anchors.right: viewArea.right
        height: 100
    }
}
