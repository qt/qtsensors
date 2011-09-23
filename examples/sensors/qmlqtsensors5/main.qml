//Import the declarative plugins
import QtQuick 2.0
import QtSensors 5.0

/* Layout
                                tiltrect
                               /
------------------------------/
| @ Facing Up  <-------------------- selButtonFacingUp
| O Left Up    <-------------------- selButtonLeftUp
| O Top Down   <-------------------- selButtonTopDown
| O Face Down  <-------------------- selButtonFaceDown
| O Right Up   <-------------------- selButtonRightUp
| O Top Up     <-------------------- selButtonTopUp
| ---------
| |degree |    <-------------------- useRadian
| ---------
| X Rotation: 0  <------------------ xrottext
| Y Rotation: 0  <------------------ yrottext
| ---------
| |start  |    <-------------------- tiltStart
| ---------                     ablrect
------------------------------ /
------------------------------/
| Ambient light: -  <--------------- abltext
| ---------
| |start  |    <-------------------- ablStart
| ---------                     proxirect
------------------------------ /
------------------------------/
| Proximity: false  <--------------- proxitext
| ---------
| |start  |    <-------------------- proxiStart
| ---------
------------------------------

*/

Rectangle {
    width: 320
    height: 480

    Rectangle {
        id: tiltrect
        x: 2
        y: 22
        width: 315
        height: 270
        border.width: 1

        TiltSensor {
            id: tilt
            radian: false
            measureFrom: TiltSensor.FaceUp
            running: false
        }

        SelectionButton{
            id: selButtonFacingUp
            x: 5
            y: 20
            checked: true
            text: "Facing Up"
            onClicked:{
                selButtonLeftUp.setCheck(false);
                selButtonTopDown.setCheck(false);
                selButtonFaceDown.setCheck(false);
                selButtonRightUp.setCheck(false);
                selButtonTopUp.setCheck(false);
                tilt.measureFrom=TiltSensor.FaceUp;
            }
        }
        SelectionButton{
            id: selButtonLeftUp
            x: 5
            y: 45
            checked: false
            text: "Left Up"
            onClicked:{
                selButtonFacingUp.setCheck(false);
                selButtonTopDown.setCheck(false);
                selButtonFaceDown.setCheck(false);
                selButtonRightUp.setCheck(false);
                selButtonTopUp.setCheck(false);
                tilt.measureFrom=TiltSensor.LeftUp;
            }
        }
        SelectionButton{
            id: selButtonTopDown
            x: 5
            y: 70
            checked: false
            text: "Top Down"
            onClicked:{
                selButtonFacingUp.setCheck(false);
                selButtonLeftUp.setCheck(false);
                selButtonFaceDown.setCheck(false);
                selButtonRightUp.setCheck(false);
                selButtonTopUp.setCheck(false);
                tilt.measureFrom=TiltSensor.TopDown;
            }
        }
        SelectionButton{
            id: selButtonFaceDown
            x: 5
            y: 95
            checked: false
            text: "Face Down"
            onClicked:{
                selButtonFacingUp.setCheck(false);
                selButtonLeftUp.setCheck(false);
                selButtonTopDown.setCheck(false);
                selButtonRightUp.setCheck(false);
                selButtonTopUp.setCheck(false);
                tilt.measureFrom=TiltSensor.FaceDown;
            }
        }
        SelectionButton{
            id: selButtonRightUp
            x: 5
            y: 120
            checked: false
            text: "Right Up"
            onClicked:{
                selButtonFacingUp.setCheck(false);
                selButtonLeftUp.setCheck(false);
                selButtonTopDown.setCheck(false);
                selButtonFaceDown.setCheck(false);
                selButtonTopUp.setCheck(false);
                tilt.measureFrom=TiltSensor.RightUp;
            }
        }
        SelectionButton{
            id: selButtonTopUp
            x: 5
            y: 145
            checked: false
            text: "Top Up"
            onClicked:{
                selButtonFacingUp.setCheck(false);
                selButtonLeftUp.setCheck(false);
                selButtonTopDown.setCheck(false);
                selButtonFaceDown.setCheck(false);
                selButtonRightUp.setCheck(false);
                tilt.measureFrom=TiltSensor.TopUp;
            }
        }

        Button{
            id: useRadian
            x: 5
            y: 170
            text: "degree"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: tilt.radian
            color: "lightyellow"

            onClicked:{
                tilt.radian = useRadian.checked;
                if (useRadian.checked)
                    useRadian.text = "radian";
                else
                    useRadian.text = "degree";
            }
        }

        Text {
            id: xrottext
            x:5
            y:195
            text: "X Rotation: " + tilt.xRotation
        }
        Text {
            id: yrottext
            x:5
            y:220
            text: "Y Rotation: " + tilt.yRotation
        }
        Button{
            id: tiltStart
            x: 5
            y: 245
            text: "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: tilt.running
            color: "lightyellow"

            onClicked:{
                tilt.running = tiltStart.checked;
                if (tiltStart.checked)
                    tiltStart.text = "running";
                else
                    tiltStart.text = "stopped";
            }
        }
    }

    Rectangle {
        id: ablrect
        x: 2
        y: tiltrect.y + tiltrect.height + 10
        width: 315
        height: 70
        border.width: 1

        AmbientLightSensor {
            id: abl
            running: false
            onLightLevelChanged:{
                if (abl.lightLevel == AmbientLightSensor.Undefined)
                    abltext.text = "Ambient light: Undefined";
                else if (abl.lightLevel == AmbientLightSensor.Dark)
                    abltext.text = "Ambient light: Dark";
                else if (abl.lightLevel == AmbientLightSensor.Twilight)
                    abltext.text = "Ambient light: Twilight";
                else if (abl.lightLevel == AmbientLightSensor.Light)
                    abltext.text = "Ambient light: Light";
                else if (abl.lightLevel == AmbientLightSensor.Bright)
                    abltext.text = "Ambient light: Bright";
                else if (abl.lightLevel == AmbientLightSensor.Sunny)
                    abltext.text = "Ambient light: Sunny";
            }
        }
        Text {
            id: abltext
            x: 5
            y: 10
            text: "Ambient light: -"
        }
        Button{
            id: ablStart
            x: 5
            y: 35
            text: "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: abl.running
            color: "lightyellow"

            onClicked:{
                abl.running = ablStart.checked;
                if (ablStart.checked)
                    ablStart.text = "running";
                else
                    ablStart.text = "stopped";
            }
        }
    }

    Rectangle {
        id: proxirect
        x: 2
        y: ablrect.y + ablrect.height + 10
        width: 315
        height: 70
        border.width: 1

        ProximitySensor {
            id: proxi
            running: true
        }
        Text {
            id: proxitext
            x: 5
            y: 10
            text: "Proximity: " + proxi.close
        }
        Button{
            id: proxiStart
            x: 5
            y: 35
            text: "start"
            checkColor: "lightblue"
            unCheckColor: "lightyellow"
            checked: proxi.running
            color: "lightyellow"

            onClicked:{
                proxi.running = proxiStart.checked;
                if (proxiStart.checked)
                    proxiStart.text = "running";
                else
                    proxiStart.text = "stopped";
            }
        }
    }
}

