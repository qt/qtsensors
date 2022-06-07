// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//Import the declarative plugins
import QtQuick

//Import the javascript functions for this game
import "lib.js" as Lib

//Implementation of the Labyrinth square control.
Rectangle {
    id: sq
    x: 0
    y: 0
    width: Lib.cellDimension
    height: Lib.cellDimension
    color: "white"
    property int val: 0
    property AnimatedImage picture: img

    //Dependent of its position and the labyrinth value a square can be the start, cheese, empty or a wall
    AnimatedImage {
        id: img
        anchors.fill: parent
        source: ""
    }

    function updateImage()
    {
        if (sq.val == -1)
            sq.picture.source = "content/start.png";
        else if (sq.val == 3)
            sq.picture.source = "content/cheese.png";
        else if (sq.val == 4){
            sq.picture.source = "content/cheeseeating.gif";
            sq.picture.playing = true;
        }
        else if (sq.val == 1)
            sq.picture.source = "content/01.png";
        else
            sq.picture.source = "content/00.png";
    }
}
