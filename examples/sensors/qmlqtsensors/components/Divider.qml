// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick

Column {
    spacing: 5
    width: parent.width
    property alias label: textLabel.text

    Rectangle {
        border.width: 1
        height: 2
        width: parent.width
        anchors.margins: 20
        border.color: "#2d2b19"
    }
    Text {
        id: textLabel
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
    }
}
