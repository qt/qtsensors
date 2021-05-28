/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

//! [0]
import SensorModels
//! [0]

Window {
    id: window
    width: 400
    height: 600

    AvailableSensorsModel {
        id: availableSensorsModel
    }

    ColumnLayout {

        GroupBox {
            id: availableSensorsModelGroup
            title: qsTr("Available Sensors")
            Layout.preferredWidth: window.width - 4 // 4 = 2x2 margins
            Layout.preferredHeight: window.height * 0.4
            Layout.margins: 2

            ListView {
                id: sensorsView
                anchors.fill: parent
                currentIndex: -1 // no initial selection
                spacing: 1
                clip: true
                model: availableSensorsModel
                delegate: Item {
                    id: sensorRow
                    width: sensorsView.width
                    height: 30
                    property color rowColor: {
                        if (sensorsView.currentIndex == index)
                            return "lightsteelblue" // highlight
                        return (index % 2 == 0) ? "#CCCCCC" : "#AAAAAA"
                    }
                    RowLayout {
                        spacing: 1
                        anchors.fill: parent
                        Rectangle {
                            color: sensorRow.rowColor
                            Layout.preferredWidth:  sensorRow.width * 0.8
                            Layout.preferredHeight: sensorRow.height
                            Text {
                                anchors.centerIn: parent
                                text: display.type + "::" + display.identifier
                            }
                        }
                        Rectangle {
                            color: sensorRow.rowColor
                            Layout.preferredWidth:  sensorRow.width * 0.2
                            Layout.preferredHeight: sensorRow.height
                            Text {
                                anchors.centerIn: parent
                                text: display.active ? qsTr("Active") : qsTr("Inactive")
                            }
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: sensorsView.currentIndex = index
                    }
                }
            }
        }

        //! [1]
        SensorPropertyModel {
            id: propertyModel
            sensor: availableSensorsModel.get(sensorsView.currentIndex)
        }
        //! [1]

        //! [2]
        Button {
            id: activateButton
            Layout.preferredHeight: 30
            Layout.alignment: Qt.AlignCenter
            enabled: propertyModel.sensor
            text: !propertyModel.sensor ? qsTr("Select sensor")
                                        : (propertyModel.sensor.active ? qsTr("Deactivate sensor")
                                                                       : qsTr("Activate sensor"))
            onClicked: propertyModel.sensor.active = !propertyModel.sensor.active
        }
        //! [2]

        GroupBox {
            title: qsTr("Selected sensor's properties")
            Layout.preferredWidth: window.width  - 4 // 4 = 2x2 margins
            Layout.preferredHeight: window.height * 0.55 - activateButton.height
            Layout.margins: 2
            enabled: sensorsView.currentIndex != -1

            //! [3]
            TableView {
                id: propertyView
                anchors.fill: parent
                model: propertyModel
                columnSpacing: 1
                rowSpacing: 1
                boundsMovement: Flickable.StopAtBounds
                clip: true

                delegate: Rectangle {
                    implicitHeight: 30
                    implicitWidth: propertyView.width * 0.5
                    color: (model.row % 2 == 0) ? "#CCCCCC" : "#AAAAAA"
                    Text {
                        anchors.centerIn: parent
                        text: display
                    }
                }
            }
            //! [3]
        }
    }
}
