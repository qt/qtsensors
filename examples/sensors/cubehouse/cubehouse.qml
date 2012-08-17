/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import Qt3D 1.0
import Qt3D.Shapes 1.0

//! [0]
import QtSensors 5.0
//! [0]

import "."

Item {
    id: mainWindow
    width: 320
    height: 480

    Viewport {
        id: view
        anchors.top: parent.top
        width: parent.width
        height: parent.height
        fillColor: "darkblue"
        objectName: "cube viewport"
        camera: Camera { eye: Qt.vector3d(0, 3, 1.6 * room.scale - 4)}

        Room{
            id: room
            scale: 7.0
        }

        function rotateY(y)
        {
            room.rotateY(y);
        }

        function rotateX(x)
        {
            room.rotateX(x);
        }
    }

//! [1]
    Accelerometer {
        id: accel
        active: true
        dataRate: 20
//! [1]

//! [2]
        property double pitch: 0.0
        property double roll: 0.0
//! [2]

//! [3]
        onReadingChanged: {
            pitch = -(Math.atan2(reading.x, Math.sqrt(reading.y * reading.y + reading.z * reading.z)) * 180) / Math.PI;
            roll = (Math.atan2(reading.y, Math.sqrt(reading.x * reading.x + reading.z * reading.z)) * 180) / Math.PI;
        }
    }
//! [3]


    //Timer to read out the x and y rotation of the TiltSensor
//! [4]
    Timer {
        interval: 50; running: true; repeat: true

        onTriggered: {
            view.rotateY(accel.pitch);
            view.rotateX(accel.roll);
        }
    }
//! [4]
}
