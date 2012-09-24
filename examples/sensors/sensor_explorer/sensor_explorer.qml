/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

//Import the declarative plugins
import QtQuick 2.0
import "components"

//! [0]
import Explorer 1.0
//! [0]

ApplicationWindow {
    id: mainWnd

//! [1]
    SensorExplorer {
        id: explorer
    }
//! [1]

    SensorList {
        id: sensorList
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.right: parent.right
        height: 170
        title: "sensor explorer"

//! [2]
        listmodel: explorer.availableSensors
//! [2]

        onSelectedItemChanged: {
            explorer.selectedSensorItem = sensorList.selectedItem;
            startstopButton.text=(explorer.selectedSensorItem !== null ?
                   (explorer.selectedSensorItem.start === true ? "Stop" : "Start") : "Start")
            if (sensorList.selectedItem !== null)

//! [3]
                propertyList.listmodel = sensorList.selectedItem.properties;
//! [3]
        }
    }

    Rectangle {
        id: listSplitLine
        anchors.top: sensorList.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        height: 1
        border.width: 1
        border.color: "#999999"
    }

    PropertyList {
        id: propertyList
        anchors.top: listSplitLine.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: listPropertyEndLine.top
        anchors.bottomMargin: 5

        onSelectedItemChanged: {
            textfield.enabled = (propertyList.selectedItem === null ?
                                            false : propertyList.selectedItem.isWriteable);
        }
    }

    Rectangle {
        id: listPropertyEndLine
        anchors.bottom: startstopButton.top
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        height: 1
        border.width: 1
        border.color: "#999999"
    }


    Button {
        id: startstopButton
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 5
        text: (explorer.selectedSensorItem !== null ?
                   (explorer.selectedSensorItem.start === true ? "Stop" : "Start") : "Start")
        enabled: true
        height: 30
        width: 80

        onClicked: {
            if (explorer.selectedSensorItem !== null) {
//! [5]
                if (text === "Start") {
                    explorer.selectedSensorItem.start = true;
                    text = "Stop";
                }
                else {
                    explorer.selectedSensorItem.start = false;
                    text = "Start";
                }
//! [5]
            }

            textfield.text = "";
        }
    }

    TextField {
        id: textfield
        anchors.top: parent.bottom
        anchors.topMargin: -35
        anchors.left: startstopButton.right
        anchors.right: parent.right
        anchors.margins: 5
        height: 30
        enabled: false

        onEnabledChanged: {
            if (!textfield.enabled) {
                textfield.closeSoftwareInputPanel();
                textfield.anchors.top= parent.bottom;
                textfield.anchors.topMargin= -35;
                textfield.text = "";
            }
        }

        onFocusChanged: {
            if (textfield.focus) {
                textfield.anchors.top= sensorList.bottom
                textfield.anchors.topMargin= -15
            }
            else {
                textfield.closeSoftwareInputPanel();
                textfield.anchors.top= parent.bottom;
                textfield.anchors.topMargin= -35;
            }
        }

        onAccepted: {

            if (explorer.selectedSensorItem !== null
                && propertyList.selectedItem !== null) {
//! [4]
                explorer.selectedSensorItem.changePropertyValue(propertyList.selectedItem, textfield.text);
//! [4]
                propertyList.focus=true;
            }
            textfield.text = "";
        }
    }
}

