// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick

//Import the javascript functions for this game
import "lib.js" as Lib

//Implementation of the Mouse control.
Item {
    id: mouse
    x: 0
    y: 0
    width: Lib.cellDimension
    height: Lib.cellDimension
    property int angle
    readonly property double radians_to_degrees: 180 / Math.PI

    AnimatedImage {
        id: img
        source: "content/mouse_down.gif"
        anchors.fill: parent
        visible:  true
    }

    //Function for moving the mouse
    function move(newx, newy)
    {
        if (mouse.x === newx && mouse.y === newy)
            return
        // somehow this actually works
//! [0]
        var a = newy - mouse.y
        var b = newx - mouse.x
        angle = Math.atan2(-b, a) * mouse.radians_to_degrees
        if (angle < 0)
            angle = 360 + angle

        img.rotation = angle
        mouse.x = newx;
        mouse.y = newy;
//! [0]
    }
}
