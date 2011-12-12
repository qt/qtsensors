/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
//! [0]
import QtMobility.sensors 1.2
//! [0]


Rectangle {
    width: 360
    height: 360
    id: mainPage

//! [1]
    Accelerometer {
        id: accel
//! [1]
//! [3]
        active:true
//! [3]
        property real accelY;
        property real accelX;
    }

//! [2]
    Timer {
         interval: 500; running: true; repeat: true

         property real xdiff;
         property real ydiff;

         onTriggered: {
             xdiff = accel.reading.x - accel.accelX;
             ydiff = accel.reading.y - accel.accelY;

             if (Math.abs(xdiff) > 0.3) {
                 accel.accelX = -accel.reading.x
             }
             if (Math.abs(ydiff) > 0.3) {
                 accel.accelY = accel.reading.y
             }
         }
     }
//! [2]

    Image {
        id: bubble
        source: "images/Bluebubble2.png"
        property real centerX: parent.width / 2
        property real centerY: parent.height / 2;
        property real bubbleCenter: bubble.width / 2

        function calX() {
            var newX = centerX + accel.accelX  / -1 * centerX

            if ((newX - bubbleCenter) < 0) {
                return 0
            }
            else if ((newX + bubbleCenter) > parent.width) {
                return parent.width - 2 * bubbleCenter
            }
            return newX - bubbleCenter;
        }
        x: calX();

        function calY() {
            var newY = centerY + accel.accelY / -1 * centerY

            if ((newY - bubbleCenter) < 0) {
                return 0
            }
            else if ((newY + bubbleCenter) > parent.height) {
                return parent.height - 2 * bubbleCenter
            }
            return newY - bubbleCenter;
        }
        y: calY();

        smooth: true

        Behavior on y {
            SmoothedAnimation {
                easing.type: Easing.Linear
                duration: 2500
            }
        }
        Behavior on x {
            SmoothedAnimation {
                easing.type: Easing.Linear
                duration: 2500
            }
        }
    }
}
