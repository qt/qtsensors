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
