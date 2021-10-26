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
import QtQuick.Controls
import QtQuick.Layouts
import QtSensors

Rectangle {
    id: root
    color: "dimgray"
    property real azimuth: 30
    readonly property real buttonHeight: height/8

    Compass {
        id: compass
        active: true
        dataRate: 7
        onReadingChanged: {
            root.azimuth = -reading.azimuth
        }
    }

    ColumnLayout {
        anchors.fill: parent
        id: layout

        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: titleHeight
            Layout.topMargin: titleTopMargin
            verticalAlignment: Text.AlignVCenter
            color: "White"
            text: "Compass"
            font.pixelSize: titleFontSize
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true
            Layout.preferredWidth: root.width
            Layout.preferredHeight: root.height
            id: arrow
            source: "qrc:/images/compass.svg"
            fillMode: Image.PreserveAspectFit
            rotation:root.azimuth
        }
        Text {
            Layout.preferredWidth: root.width
            Layout.preferredHeight: textHeight
            Layout.leftMargin: layout.spacing
            color: "White"
            text: "Azimuth: " + root.azimuth.toFixed(2) + "°"
            font.pixelSize: textFontSize
        }
        Button {
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: root.width
            Layout.preferredHeight: buttonHeight
            text:"Back"
            font.pixelSize: buttonFontSize
            onClicked:stack.pop()
        }
    }
}
