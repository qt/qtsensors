import QtQuick 2.0

Rectangle {
    id: button
    width: 100
    height: 20
    property alias text: t.text
    property bool checked
    signal clicked
    property color checkColor;
    property color unCheckColor;
    border.width: 1
    radius:  2

    Text{
        x: 0
        id: t
        anchors.fill: button
    }

    MouseArea{
        anchors.fill: button
        onClicked: {
            setCheck(!button.checked);
            button.clicked();
        }
    }

    function setCheck(val)
    {
        checked = val;
        button.color = (button.checked == true ? checkColor : unCheckColor);
    }
}
