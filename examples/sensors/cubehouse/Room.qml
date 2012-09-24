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

import QtQuick 2.0
import Qt3D 1.0
import Qt3D.Shapes 1.0
import "."

Item3D{
    id: room
    property double scale: 1.0
    property bool yspin: false
    property bool xspin: false
    property int yrot: 0
    property int xrot: 0
    property double distanceCorrection: 3.7

    transform: [
        Rotation3D {
            id: yRT
            angle: 0
            axis: Qt.vector3d(0, -1, 0)
        },
        Rotation3D {
            id: xRT
            angle: 0
            axis: Qt.vector3d(-1, 0, 0)
        }
    ]

    SequentialAnimation {
        running: yspin
        NumberAnimation {
            target: yRT
            property: "angle"
            to: yrot
            easing.type:"Linear"
            duration: 50
        }
        onCompleted: yspin = false
    }

    SequentialAnimation {
        running: xspin
        NumberAnimation {
            target: xRT
            property: "angle"
            to: xrot
            easing.type:"Linear"
            duration: 50
        }
        onCompleted: xspin = false
    }

    function rotateY(y)
    {
        room.yrot=y;
        room.yspin = true;
    }

    function rotateX(x)
    {
        room.xrot=x;
        room.xspin = true;
    }

    Quad {
        id: frontWall
        scale: room.scale
        effect: Effect {
            texture: "content/wall.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -frontWall.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: 0
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 0
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Quad {
        id: ground
        scale: room.scale
        effect: Effect {
            texture: "content/ground.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -ground.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Quad {
        id: leftWall
        scale: room.scale
        effect: Effect {
            texture: "content/wall.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -leftWall.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: 0
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Quad {
        id: rightWall
        scale: room.scale
        effect: Effect {
            texture: "content/wall.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -rightWall.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: 180
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Quad {
        id: roof
        scale: room.scale
        effect: Effect {
            texture: "content/roof.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -roof.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: -90
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Quad {
        id: backWall
        scale: room.scale
        effect: Effect {
            texture: "content/wall.jpg"
        }
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -backWall.scale + room.distanceCorrection, 0)
            },
            Rotation3D {
                angle: -90
                axis: Qt.vector3d(1, 0, 0)
            },
            Rotation3D {
                angle: 0
                axis: Qt.vector3d(0, 1, 0)
            },
            Rotation3D {
                angle: 0
                axis: Qt.vector3d(0, 0, 1)
            }
        ]
    }

    Cube {
        id: cube
        scale: 0.5

        transform: [
            Translation3D {
                translate: Qt.vector3d(0.0, 0.0, 0.0)
            }
        ]
    }

    Table {
        scale: 0.025
        transform: [
            Translation3D {
                translate: Qt.vector3d(0, -7 + room.distanceCorrection, 0)
            }
        ]
    }

    Teapot {
        scale: 0.5

        effect: Effect {
            color: "#ffffaa"
            decal: true
        }

        transform: [
            Translation3D {
                translate: Qt.vector3d(0.0, -4.50 + room.distanceCorrection, 0.0)
            }
        ]
    }
}
