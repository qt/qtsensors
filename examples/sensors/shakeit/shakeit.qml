/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
//! [0]
import QtSensors 5.0
//! [0]
//import QtMultimedia 4.0
import Qt.multimediakit 4.0



Rectangle {
    id: window

    state: "default"

    Audio {
        id :phone
        source: "audio/phone.wav" //mono
    }
    Audio {
        id :loopy2a_mono
        source: "audio/loopy2a_mono.wav" //mono
    }

    Text {
        id: label
        text: qsTr("Shake to rotate triangles")
        y: parent.height / 4
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: triangle1
        smooth: true
        source: "images/triangle.png"
        x: parent.width / 2 - (triangle1.width / 2)
        y: parent.height / 2 - (triangle1.height);
        Behavior on x { SmoothedAnimation { velocity: 200 } }
        Behavior on y { SmoothedAnimation { velocity: 200 } }
    }
    Image {
        id: triangle2
        smooth: true
        source: "images/triangle2.png"
        x: parent.width / 2 - (triangle1.width + triangle2.width / 2)
        y: parent.height / 2 + (triangle2.height / 2);
        Behavior on x { SmoothedAnimation { velocity: 200 } }
        Behavior on y { SmoothedAnimation { velocity: 200 } }
    }
    Image {
        id: triangle3
        smooth: true
        source: "images/triangle3.png"
        x: parent.width / 2 + (triangle1.width / 2)
        y: parent.height / 2 + (triangle3.height / 2);

        Behavior on x { SmoothedAnimation { velocity: 200 } }
        Behavior on y { SmoothedAnimation { velocity: 200 } }
    }

    states: [
        State {
            name: "rotated"
            PropertyChanges { target: triangle1; rotation: 180 }
            PropertyChanges { target: triangle2; rotation: 90 }
            PropertyChanges { target: triangle3; rotation: 270 }
        },
        State {
            name: "default"
            PropertyChanges { target: triangle1; rotation: 0;
                x: parent.width / 2 - (triangle1.width / 2)
                y: parent.height / 2 - (triangle1.height);
            }
            PropertyChanges { target: triangle2; rotation: 0;
                x: parent.width / 2 - (triangle1.width + triangle2.width / 2)
                y: parent.height / 2 + (triangle2.height / 2);
            }
            PropertyChanges { target: triangle3; rotation: 0;
                x: parent.width / 2 + (triangle1.width / 2)
                y: parent.height / 2 + (triangle3.height / 2);
            }
        },
        State {
            name: "whipped"
            PropertyChanges { target: triangle1; rotation: 0; x:0;
            }
            PropertyChanges { target: triangle2; rotation: 0; x:0;
            }
            PropertyChanges { target: triangle3; rotation: 0; x:0;
                y: triangle2.y + triangle2.height;
            }
        },
        State {
            name: "twisted"
            PropertyChanges { target: triangle1; rotation: 270;
                x:window.width - triangle1.width;
            }
            PropertyChanges { target: triangle2; rotation: 180;
                x:window.width - triangle2.width;
            }
            PropertyChanges { target: triangle3; rotation: 90;
                x:window.width - triangle3.width;
                y:triangle2.y + triangle2.height;
            }
        },
        State {
            name: "covered"
            PropertyChanges { target: triangle1; rotation: 0;
                x: window.width / 3 - triangle1.width / 2;
                y: window.height - triangle1.height;
            }
            PropertyChanges { target: triangle2; rotation: 0;
                x: window.width / 2 - triangle2.width / 2; // middle
                y: window.height - triangle2.height;
            }
            PropertyChanges { target: triangle3; rotation: 0;
                x: (window.width / 3 + window.width / 3) - triangle3.width / 2;
                y: window.height - triangle3.height;
            }
        },
        State {
            name: "hovered"
            PropertyChanges { target: triangle1; rotation: 90;
                x: window.width / 3 - triangle1.width / 2;
                y: triangle1.height;
            }
            PropertyChanges { target: triangle2; rotation: 270;
                x: window.width / 2 - triangle2.width / 2; // middle
                y: triangle2.height;
            }
            PropertyChanges { target: triangle3; rotation: 180;
                x: (window.width / 3 + window.width / 3) - triangle3.width / 2;
                y: triangle3.height
            }
        }/*,
        State {
            name :"turnedover"
        }*/
    ]


    transitions: Transition {
        ParallelAnimation {
            running: true
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutBounce;duration: 3000; }
            RotationAnimation { id: t1Rotation; target: triangle1; duration: 1000;
                direction: RotationAnimation.Clockwise }
            RotationAnimation { id: t2Rotation; target: triangle2; duration: 3000;
                direction: RotationAnimation.Counterclockwise }
            RotationAnimation { id: t3Rotation; target: triangle3; duration: 3000;
                direction: RotationAnimation.Clockwise }
        }
    }

//! [1]
    SensorGesture {
//! [1]
        id: sensorGesture
//! [3]
        enabled: true
//! [3]
//! [2]
        gestures : ["QtSensors.shake", "QtSensors.whip", "QtSensors.twist", "QtSensors.cover",
            "QtSensors.hover", "QtSensors.turnover", "QtSensors.pickup"]
//! [2]
//! [4]
        onDetected:{
            console.debug(gesture)
            label.text = gesture

            if (gesture == "shake") {
                window.state == "rotated" ? window.state = "default" : window.state = "rotated"
            }
            if (gesture == "whip") {
                window.state == "whipped" ? window.state = "default" : window.state = "whipped"
            }
            if (gesture == "twistRight") {
                window.state == "twisted" ? window.state = "default" : window.state = "twisted"
            }
            if (gesture == "cover") {
                window.state == "covered" ? window.state = "default" : window.state = "covered"
            }
            if (gesture == "hover") {
                window.state == "hovered" ? window.state = "default" : window.state = "hovered"
            }
            if (gesture == "turnover") {
                window.state = "default"
                loopy2a_mono.play();
            }
            if (gesture == "pickup") {
                window.state = "default"
                phone.play()
            }
        }
//! [4]
    }
}
