/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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

//Import the declarative plugins
import QtQuick 2.0

//Import the javascript functions for this game
import "lib.js" as Lib

//Implementation of the Mouse control.
Item {
    id: mouse
    x: 0
    y: 0
    width: Lib.cellDimension
    height: Lib.cellDimension
    state: 'right'

    AnimatedImage {
        id: img
        anchors.fill: parent
        visible:  true
    }

    //for different moves we have different gif animations
    states: [
        State {
           name: "up"
           PropertyChanges { target: img; source: "images/mouse_up.gif" }
        },
        State {
           name: "down"
           PropertyChanges { target: img; source: "images/mouse_down.gif" }
        },
        State {
           name: "left"
           PropertyChanges { target: img; source: "images/mouse_left.gif" }
        },
        State {
           name: "right"
           PropertyChanges { target: img; source: "images/mouse_right.gif" }
        },

        State {
           name: "rightup"
           PropertyChanges { target: img; source: "images/mouse_rightup.gif" }
        },
        State {
           name: "rightdown"
           PropertyChanges { target: img; source: "images/mouse_rightdown.gif" }
        },
        State {
           name: "leftup"
           PropertyChanges { target: img; source: "images/mouse_leftup.gif" }
        },
        State {
           name: "leftdown"
           PropertyChanges { target: img; source: "images/mouse_leftdown.gif" }
        }

    ]

    //Function for moving the mouse
    function move(newx, newy)
    {
        var newstatus = "";
        if (mouse.x < newx)
            newstatus += "right";
        else if (mouse.x > newx)
            newstatus += "left";
        if (mouse.y < newy)
            newstatus += "down";
        else if (mouse.y > newy)
            newstatus += "up";
        mouse.state = newstatus;
        mouse.x = newx;
        mouse.y = newy;
    }
}
