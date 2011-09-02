import QtQuick 2.0

Rectangle {
    id: button
    width: 100
    height: 25
    property alias text: t.text
    property bool checked
    signal clicked

    Image{
        id: image
        x: 0
        width: 15
        height: 15
        source: (button.checked == true ? "checked.gif" : "unchecked.gif")
    }

    Text{
        x: image.x + image.width + 10
        id: t
    }

    MouseArea{
        anchors.fill: button
        onClicked: {
            setCheck(true);
            button.clicked();
        }
    }

    function setCheck(val)
    {
        checked = val;
        image.source = (button.checked == true ? "checked.gif" : "unchecked.gif");
    }
}
