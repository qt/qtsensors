//Import the declarative plugins
import QtQuick 2.0

//Import the javascript functions for this game
import "lib.js" as Lib

//Implementation of the Congratulation control
Item {
    x: Lib.cellDimension
    y: Lib.cellDimension
    width: Lib.cellDimension * (Lib.dimension - 2)
    height: Lib.cellDimension * (Lib.dimension - 2)

    //Containing a animated gif image
    AnimatedImage {
        id: img
        anchors.fill: parent
        visible:  true
        source: "images/congratulations.gif"
    }
}
