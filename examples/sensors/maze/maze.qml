// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

/* Layout
                                mainWnd
                               /
------------------------------/ gameRect
|                              /
|-----------------------------/
||---------------------------|
||||M|                      ||
|||   \                     ||
|||    mouseCtrl            ||
|||                         ||
|||                         ||
|||     Labyrinth           ||
|||                         ||
|||                         ||
|||        cheeseSquare     ||
|||                     \   ||
|||                      |C|||
||---------------------------|
|-----------------------------
|
|-----------------------------
||             ||            |
|-----------------------------
|       \          \
|        \          timePlayingLabel
|         newGameButton
------------------------------

*/
//Import the declarative plugins
import QtQuick
import "components"

//! [0]
import QtSensors
//! [0]

//Import the javascript functions for this game
import "lib.js" as Lib

ApplicationWindow {
    id: mainWnd
    property bool gameRunning: false

    Component.onCompleted: {
        initializeMaze()
        newGame()
    }

    function initializeMaze() {
        Lib.objectArray = new Array(Lib.dimension * Lib.dimension);
        Lib.createLabyrinth();
        var idx = 0;
        var component = Qt.createComponent("LabyrinthSquare.qml");
        for (var y = 0; y < Lib.dimension; y++ ) {
            for (var x = 0; x < Lib.dimension; x++ ) {
                var square = component.createObject(gameRect);
                if (!square) {
                    console.log("error loading labyrinth square: " + component.errorString())
                    return
                }
                square.x = x * square.width;
                square.y = y * square.height;
                square.val = Lib.labyrinth[x][y];
                Lib.objectArray[idx] = square;
                idx++;
            }
        }
    }

    function newGame() {
        congratulation.visible = false;

        // Reset game time
        timePlayingLabel.text = "--";
        Lib.sec = 0.0;

        // Create new labyrinth
        Lib.createLabyrinth();
        // Update maze tiles to match the new labyrinth
        var idx = 0;
        for (var y = 0; y < Lib.dimension; y++ ) {
            for (var x = 0; x < Lib.dimension; x++ ) {
                Lib.objectArray[idx].val = Lib.labyrinth[x][y];
                Lib.objectArray[idx].updateImage();
                idx++;
            }
        }
        // Reset mouse position and start the game
        mouseCtrl.x = 0;
        mouseCtrl.y = 0;
        mainWnd.gameRunning = true;
    }

    function gameWon() {
        // Update the cheese square at the bottom right (win animation)
        Lib.objectArray[Lib.dimension * Lib.dimension - 1].val = 4
        Lib.objectArray[Lib.dimension * Lib.dimension - 1].updateImage()
        congratulation.visible = true;
        mainWnd.gameRunning = false;
    }

    Rectangle {
        id: gameRect
        x: (mainWnd.width - width) / 2
        y: 5
        width: Lib.dimension * Lib.cellDimension
        height: Lib.dimension * Lib.cellDimension
        color: "transparent"
        border.width: 2
    }

    Mouse {
        id: mouseCtrl
    }

    Congratulation {
        id: congratulation
        visible: false
    }

//! [1]
    TiltSensor {
        id: tiltSensor
        active: true
    }
//! [1]

    //Timer to read out the x and y rotation of the TiltSensor
    Timer {
        id: tiltTimer
        interval: 50
        repeat: true
        running: tiltSensor.active && mainWnd.gameRunning

        onTriggered: {
            // Update the maze unless game is already won
            if (Lib.won === true) {
                gameWon()
                return
            }
            Lib.sec += 0.05;
            timePlayingLabel.text = Math.floor(Lib.sec) + " seconds";

            //check if we can move the mouse
            var xval = -1;
            var yval = -1;

//! [2]
            var xstep = 0;
            xstep = tiltSensor.reading.yRotation * 0.1 //acceleration

            var ystep = 0;
            ystep = tiltSensor.reading.xRotation * 0.1 //acceleration
//! [2]
//! [3]
            if (xstep < 1 && xstep > 0)
                xstep = 0
            else if (xstep > -1 && xstep < 0)
                xstep = 0

            if (ystep < 1 && ystep > 0)
                ystep = 0;
            else if (ystep > -1 && ystep < 0)
                ystep = 0;

            if ((xstep < 0 && mouseCtrl.x > 0
                 && Lib.canMove(mouseCtrl.x + xstep,mouseCtrl.y))) {
                xval = mouseCtrl.x + xstep;

            } else if (xstep > 0 && mouseCtrl.x < (Lib.cellDimension * (Lib.dimension - 1))
                       && Lib.canMove(mouseCtrl.x + xstep,mouseCtrl.y)) {
                xval = mouseCtrl.x + xstep;
            } else
                xval = mouseCtrl.x;

            if (ystep < 0 && mouseCtrl.y > 0
                    && Lib.canMove(mouseCtrl.x, mouseCtrl.y + ystep)) {
                yval = mouseCtrl.y + ystep;
            } else if (ystep > 0 && (mouseCtrl.y < (Lib.cellDimension * (Lib.dimension - 1)))
                       && Lib.canMove(mouseCtrl.x, mouseCtrl.y + ystep)) {
                yval = mouseCtrl.y + ystep;
            } else
                yval = mouseCtrl.y
            mouseCtrl.move(xval, yval);
//! [3]
        }
    }

    //Button to start a new Game
    Button{
        id: newGameButton
        anchors.left: gameRect.left
        anchors.top: gameRect.bottom
        anchors.topMargin: 5
        height: 30
        width: 100
        text: qsTr("New game")
        onClicked: newGame()
    }
    Button{
        id: calibrateButton
        anchors.left: gameRect.left
        anchors.top: newGameButton.bottom
        anchors.topMargin: 5
        height: 30
        width: 100
        text: qsTr("Calibrate")
        onClicked: tiltSensor.calibrate();
    }

    Text {
        id: tiltSensorInfo
        visible: tiltSensor.active
        anchors.left: gameRect.left
        anchors.top: calibrateButton.bottom
        anchors.topMargin: 5
        text: qsTr("Tilt sensor ID: ") + tiltSensor.identifier
    }

    //Label to print out the game time
    Text{
        id: timePlayingLabel
        anchors.right: gameRect.right
        anchors.top: gameRect.bottom
        anchors.topMargin: 5
    }

    Rectangle {
        id: tiltSensorMissing
        visible: !tiltSensor.active
        anchors.fill: parent
        color: "#AACCCCCC" // slightly transparent
        Text {
            anchors.centerIn: parent
            text: qsTr("Tilt sensor\nnot found")
            font.pixelSize: 24
            font.bold: true
            color: "black"
        }
        MouseArea {
            // prevent interaction with the game
            anchors.fill: parent
        }
    }
}

