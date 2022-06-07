// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
//! [0]
import QtSensors
//! [0]

Rectangle {
    id: window
    anchors.fill: parent

    state: "default"

    Text {
        id: label
        text: qsTr("Shake to rotate triangles")
        y: parent.height / 4
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Image {
        id: triangle1
        smooth: true
        source: "content/triangle.png"
        x: parent.width / 2 - (triangle1.width / 2)
        y: parent.height / 2 - (triangle1.height);
        Behavior on x { SmoothedAnimation { velocity: 200 } }
        Behavior on y { SmoothedAnimation { velocity: 200 } }
        transform: Rotation {
             id: myRot
        }
    }
    Image {
        id: triangle2
        smooth: true
        source: "content/triangle2.png"
        x: parent.width / 2 - (triangle1.width + triangle2.width / 2)
        y: parent.height / 2 + (triangle2.height / 2);
        Behavior on x { SmoothedAnimation { velocity: 200 } }
        Behavior on y { SmoothedAnimation { velocity: 200 } }
    }
    Image {
        id: triangle3
        smooth: true
        source: "content/triangle3.png"
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
                y: parent.height / 2 - (triangle1.height)
                scale: 1;

            }
            PropertyChanges { target: triangle2; rotation: 0;
                x: parent.width / 2 - (triangle1.width + triangle2.width / 2)
                y: parent.height / 2 + (triangle2.height / 2);
                scale: 1;
            }
            PropertyChanges { target: triangle3; rotation: 0;
                x: parent.width / 2 + (triangle1.width / 2)
                y: parent.height / 2 + (triangle3.height / 2);
                scale: 1;
            }
        },
        State {
            name: "whipped"
            PropertyChanges { target: triangle1; rotation: 0; x:0; }
            PropertyChanges { target: triangle2; rotation: 0; x:0;
                y: triangle1.x + triangle1.height; }
            PropertyChanges { target: triangle3; rotation: 0; x:0;
                y: triangle2.y + triangle2.height; }
        },
        State {
            name: "twistedR"
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
            name: "twistedL"
            PropertyChanges { target: triangle1; rotation: 270;
                x:0;
            }
            PropertyChanges { target: triangle2; rotation: 180;
                x:0;
            }
            PropertyChanges { target: triangle3; rotation: 90;
                x:0;
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
            PropertyChanges { target: triangle3; rotation: 195;
                x: (window.width / 3 + window.width / 3) - triangle3.width / 2;
                y: triangle3.height
            }
        },
        State {
            name :"slammed"
            PropertyChanges { target: triangle1; rotation: 0;
                x: 0;
                y: 0 + 30
            }
            PropertyChanges { target: triangle2; rotation: 0;
                x: window.width - triangle2.width;
                y: 0 + 30
                ;}
            PropertyChanges { target: triangle3; rotation: 0;
                x: window.width / 2 - triangle3.width / 2;
                y:window.height - triangle3.height;
            }
        },
        State {
            name: "doubletapped"
            PropertyChanges { target: triangle1; rotation: 114;
                 transformOrigin: Item.BottomLeft
            }
            PropertyChanges { target: triangle2; rotation: 120;
                transformOrigin: Item.BottomLeft
            }
        },
        State {
            name: "turnedover"
            PropertyChanges { target: triangle1; rotation: 180;
            }
            PropertyChanges { target: triangle2; rotation: 180;
            }
            PropertyChanges { target: triangle3; rotation: 180;
            }
        },
        State {
            name: "pickedup"
            PropertyChanges { target: triangle1; scale: 1.5;
            }
            PropertyChanges { target: triangle2; scale: 1.5;
            }
            PropertyChanges { target: triangle3; scale: 1.5;
            }
        }
    ]


    transitions: [
        Transition {

        ParallelAnimation {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutBounce;
                duration: 2000; }
            RotationAnimation { id: t1Rotation; target: triangle1; duration: 1000;
                direction: RotationAnimation.Clockwise }
            RotationAnimation { id: t2Rotation; target: triangle2; duration: 2000;
                direction: RotationAnimation.Counterclockwise }
            RotationAnimation { id: t3Rotation; target: triangle3; duration: 2000;
                direction: RotationAnimation.Clockwise }
        }

    }, Transition {
            to: "slammed"
            SequentialAnimation {
                NumberAnimation { properties: "x"; easing.type: Easing.OutBounce;duration: 500; }

            }
        }, Transition {
            to: "doubletapped"
            SequentialAnimation {
                PropertyAction { target: triangle1; property: "transformOrigin" }
                PropertyAction { target: triangle2; property: "transformOrigin" }
                NumberAnimation {  target: triangle1; properties: "rotation";
                    easing.type: Easing.OutBounce;duration: 500; }
                NumberAnimation {  target: triangle2; properties: "rotation";
                    easing.type: Easing.OutBounce;duration: 1500; }
            }
        }, Transition {
            from: "doubletapped"
            SequentialAnimation {
                NumberAnimation { properties: "rotation";
                    easing.type: Easing.OutBounce;duration: 1500; }
                PropertyAction { target: triangle1; property: "transformOrigin" }
                PropertyAction { target: triangle2; property: "transformOrigin" }
            }
        }, Transition {
            to: "turnedover"
            SequentialAnimation {
                NumberAnimation { properties: "rotation";
                    easing.type: Easing.OutBounce;duration: 750; }
                PropertyAction { target: triangle1; property: "transformOrigin" }
                PropertyAction { target: triangle2; property: "transformOrigin" }
            }
        }, Transition {
            from: "turnedover"
            SequentialAnimation {
                NumberAnimation { properties: "rotation";
                    easing.type: Easing.OutBounce;duration: 750; }
                PropertyAction { target: triangle1; property: "transformOrigin" }
                PropertyAction { target: triangle2; property: "transformOrigin" }
            }
        }, Transition {
            to: "pickedup"
            SequentialAnimation {
                NumberAnimation { properties: "scale";
                easing.type: Easing.OutBounce;duration: 750; }
            }
        }, Transition {
            from: "pickedup"
            SequentialAnimation {
                NumberAnimation { properties: "scale";
                easing.type: Easing.OutBounce;duration: 750; }
            }
        }
    ]

//! [1]
    SensorGesture {
//! [1]
        id: sensorGesture
//! [3]
        enabled: true
//! [3]
//! [2]
        gestures : ["QtSensors.shake", "QtSensors.whip", "QtSensors.twist", "QtSensors.cover",
            "QtSensors.hover", "QtSensors.turnover", "QtSensors.pickup", "QtSensors.slam",
            "QtSensors.doubletap"]
//! [2]
//! [4]
        onDetected:{
            console.debug(gesture)

            label.text = gesture

            if (gesture == "shake") {
                window.state == "rotated" ? window.state = "default" : window.state = "rotated"
                timer.start()
            }
            if (gesture == "whip") {
                window.state == "whipped" ? window.state = "default" : window.state = "whipped"
                timer.start()
            }
            if (gesture == "twistRight") {
                window.state == "twistedR" ? window.state = "default" : window.state = "twistedR"
                timer.start()
            }
            if (gesture == "twistLeft") {
                window.state == "twistedL" ? window.state = "default" : window.state = "twistedL"
                timer.start()
            }
            if (gesture == "cover") {
                window.state == "covered" ? window.state = "default" : window.state = "covered"
                timer.start()
            }
            if (gesture == "hover") {
                window.state == "hovered" ? window.state = "default" : window.state = "hovered"
                timer.start()
            }
            if (gesture == "turnover") {
                window.state == "turnedover" ? window.state = "default" : window.state = "hovered"
                timer.start()
            }
            if (gesture == "pickup") {
                window.state == "pickedup" ? window.state = "default" : window.state = "pickedup"
                timer.start()
            }
            if (gesture == "slam") {
                window.state == "slammed" ? window.state = "default" : window.state = "slammed"
                timer.start()
            }
            if (gesture == "doubletap") {
                window.state == "doubletapped" ? window.state = "default" : window.state = "doubletapped"
                timer.start()
            }
        }
//! [4]
    }
    Timer {
        id: timer
        running: false
        repeat: false
        interval: 3000
        onTriggered: {
            console.log("timer triggered")
            window.state = "default"
            label.text = "Try another gesture"
        }
    }
}
