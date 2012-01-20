/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
//! [0]
import QtSensors 5.0
//! [0]

Rectangle {
    id: window

    Text {
        text: qsTr("Shake to rotate triangles")
        y: parent.height / 4
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: triangle1
        smooth: true
        source: "images/triangle.png"
        y: parent.height / 2 - (triangle1.height);
        x: parent.width / 2 - (triangle1.width / 2)
    }
    Image {
        id: triangle2
        smooth: true
        source: "images/triangle2.png"
        anchors.right: triangle1.left; anchors.top: triangle1.bottom
    }
    Image {
        id: triangle3
        smooth: true
        source: "images/triangle3.png"
        anchors.left: triangle1.right; anchors.top: triangle1.bottom
    }

    states: [
        State {
            name: "rotated"
            PropertyChanges { target: triangle1; rotation: 180 }
            PropertyChanges { target: triangle2; rotation: 90 }
            PropertyChanges { target: triangle3; rotation: 270 }
        },
        State {
            name: "unrotated"
            PropertyChanges { target: triangle1; rotation: 0 }
            PropertyChanges { target: triangle2; rotation: 0 }
            PropertyChanges { target: triangle3; rotation: 0 }
        }
    ]
    transitions: Transition {
        RotationAnimation { id: t1Rotation; target: triangle1; duration: 1000; direction: RotationAnimation.Clockwise }
        RotationAnimation { id: t2Rotation; target: triangle2; duration: 3000; direction: RotationAnimation.Counterclockwise }
        RotationAnimation { id: t3Rotation; target: triangle3; duration: 3000; direction: RotationAnimation.Clockwise }
    }

//! [1]
    SensorGesture {
//! [1]
        id: sensorGesture
//! [3]
        enabled: true
//! [3]
//! [2]
        gestures : ["QtSensors.shake"]
//! [2]
//! [4]
        onDetected:{
            if (gesture == "shake") {
                window.state == "rotated" ? window.state = "unrotated" : window.state = "rotated"
            }
        }
//! [4]
    }
}
