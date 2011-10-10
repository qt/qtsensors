/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
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
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef VIEW_H
#define VIEW_H

#include <QtOpenGL/qgl.h>
#include <QtGui/qvector3d.h>
#include <QtCore/qdatetime.h>
#include "camera.h"
#include "light.h"
#include "lightmodel.h"
#include "material.h"
#include "painter.h"

class QAccelerometer;

class View : public QGLWidget
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    ~View();

    void setShowFrameRate(bool value) { showFrameRate = value; }

protected:
    void resizeGL(int width, int height);
    void initializeGL();
    void paintGL();

private slots:
    void accelerometerTimeout();

private:
    GLuint texture;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    Camera *mainCamera;
    Camera *roomCamera;
    qreal sensitivity;
    LightModel *roomModel;
    LightModel *normalModel;
    Material *cubeMaterial;
    Material *teapotMaterial;
    Material *roomMaterialBack;
    Material *roomMaterialLeftRight;
    Material *roomMaterialTopBottom;
    Painter *painter;
    QTime time;
    bool showFrameRate;
    QAccelerometer *sensor;

    QVector3D gravity() const;
};

#endif
