//Import the declarative plugins
import QtQuick 2.0
import QtSensors 5.0

//Import the javascript functions for this game
import "lib.js" as Lib

/* Layout
                                mainWnd
                               /
------------------------------/
|
|-----------------------------
|||M|                        |
||   \                       |
||    mouseCtrl              |
||                           |
||                           |
||     Labyrinth             |
||                           |
||                           |
||          cheeseSquare     |
||                       \   |
||                        |C||
|-----------------------------
|
|---------- --------------
||        | |            |
|---------- --------------
|       \      \
|        \      timePlayingLabel
|         newGameButton
------------------------------

*/

Rectangle {
    id: mainWnd
    x: 0
    y: 30
    width: 320
    height: 440
    color: "white"

    property Mouse mouseCtrl;
    property LabyrinthSquare cheeseSquare;
    property Congratulation congratulation;

    //timer for starting the labyrinth game
    Timer {
        id: startTimer
        interval: 50; running: true; repeat: false
        onTriggered: {

            //reset game time
            timePlayingLabel.text = "--";
            Lib.sec = 0.0;
            Lib.createLabyrinth();

            //create labyrinth elements (only at the first time)
            var needloadcomponent = false;
            if (Lib.objectArray === null){
                needloadcomponent = true;
                Lib.objectArray = new Array(Lib.dimension * Lib.dimension);
            }
            var idx = 0;
            for (var y = 0; y < Lib.dimension; y++ ){
                for (var x = 0; x < Lib.dimension; x++ ){
                    var component = null;

                    //create labyrinth components (only at the first time)
                    if (needloadcomponent){
                        component = Qt.createComponent("LabyrinthSquare.qml");
                        if (component.status == Component.Ready) {
                            var square = component.createObject(parent);
                            square.x = x * square.width;
                            square.y = y * square.height;
                            square.val = Lib.labyrinth[x][y];
                            square.updateImage();
                            Lib.objectArray[idx] = square;
                            if (x == (Lib.dimension - 1) && y == (Lib.dimension - 1)){
                                cheeseSquare = square;
                                var component1 = Qt.createComponent("Congratulation.qml");
                                if (component1.status == Component.Ready) {
                                    congratulation = component1.createObject(parent);
                                    congratulation.visible = false;
                                }
                            }
                        }
                    }
                    else{
                        Lib.objectArray[idx].val = Lib.labyrinth[x][y];
                        Lib.objectArray[idx].updateImage();
                        if (x == (Lib.dimension - 1) && y == (Lib.dimension - 1)){
                            cheeseSquare = Lib.objectArray[idx];
                            congratulation.visible = false;
                        }
                    }
                    idx++;
                }
            }

            //Lib.printLab(); //this is for debug. Labyrinth will be printed out in the console

            //Create the mouse control  (only at the first time)
            if (mouseCtrl === null){
                var component = Qt.createComponent("Mouse.qml");
                if (component.status == Component.Ready) {
                    mouseCtrl = component.createObject(parent);
                }
            }
            mouseCtrl.x = 0;
            mouseCtrl.y = 0;
            newGameButton.enabled = true;

            //Start the Tilt reader timer
            tiltTimer.running = true;
        }
    }

    TiltSensor{
        id: tiltSensor
        radian: false
        measureFrom: TiltSensor.FaceUp
        running: true
    }

    //Timer to read out the x and y rotation of the TiltSensor
    Timer {
        id: tiltTimer
        interval: 50; running: false; repeat: true
        onTriggered: {
            if (!tiltSensor.running)
                tiltSensor.running = true;

            if (mouseCtrl === null)
                return;

            //check if already solved
            if (Lib.won !== true){
                Lib.sec += 0.05;
                timePlayingLabel.text = Math.floor(Lib.sec) + " secounds";

                //check if we can move the mouse
                var xval = -1;
                var yval = -1;
                var xstep = 0;
                if (tiltSensor.yRotation > 0)
                    xstep = 1;
                else if (tiltSensor.yRotation < 0)
                    xstep = -1;
                var ystep = 0;
                if (tiltSensor.xRotation > 0)
                    ystep = 1;
                else if (tiltSensor.xRotation < 0)
                    ystep = -1;

                if (xstep < 0){
                    if (mouseCtrl.x > 0){
                        if (Lib.canMove(mouseCtrl.x + xstep, mouseCtrl.y)){
                            xval = mouseCtrl.x + xstep;
                        }
                    }
                }
                else if (xstep > 0){
                    if (mouseCtrl.x < (Lib.cellDimension * (Lib.dimension - 1))){
                        if (Lib.canMove(mouseCtrl.x + xstep, mouseCtrl.y)){
                            xval = mouseCtrl.x + xstep;
                        }
                    }
                }
                if (ystep < 0){
                    if (mouseCtrl.y > 0){
                        if (Lib.canMove(mouseCtrl.x, mouseCtrl.y + ystep)){
                            yval = mouseCtrl.y + ystep;
                        }
                    }
                }
                else if (ystep > 0){
                    if (mouseCtrl.y < (Lib.cellDimension * (Lib.dimension - 1))){
                        if (Lib.canMove(mouseCtrl.x, mouseCtrl.y + ystep)){
                            yval = mouseCtrl.y + ystep;
                        }
                    }
                }
                if (xval >= 0 && yval >= 0)
                    mouseCtrl.move(xval, yval);

                //move the mouse in the allwed position
                else{
                    if (xval >= 0){
                        mouseCtrl.move(xval, mouseCtrl.y);
                    }
                    if (yval >= 0){
                        mouseCtrl.move(mouseCtrl.x, yval);
                    }
                }
            }
            else{

                //game won, stop the tilt meter
                mainWnd.cheeseSquare.val = 4;
                mainWnd.cheeseSquare.updateImage();
                mainWnd.congratulation.visible = true;
                newGameButton.enabled = true;
                tiltTimer.running = false;
            }
        }
    }

    //Button to start a new Game
    Button{
        id: newGameButton
        x: 0
        y: mainWnd.x + (Lib.dimension * Lib.cellDimension) + 10
        height: 30
        width: 100
        buttonText: "new game"
        enabled: false;
        onClicked: {
            newGameButton.enabled = false;
            startTimer.start();
        }
    }

    //Label to print out the game time
    Text{
        id: timePlayingLabel
        x: newGameButton.x + newGameButton.width + 20
        y: newGameButton.y + 10
    }
}

