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

#include "view.h"
#include "teapot.h"
#include "cube.h"
#include <QtCore/qdebug.h>
#include <QtCore/qtimer.h>
#include <stdio.h>
#include "qaccelerometer.h"

#if defined(QT_OPENGL_ES)
#define USE_BUFFERS 1
#endif

//! [smoothed]
class smoothedaccelerometerfilter : public QObject, public QAccelerometerFilter
{
    qreal prevX;
    qreal prevY;
    qreal prevZ;
    bool havePrev;

public:
    smoothedaccelerometerfilter(QObject *parent = 0)
        : QObject(parent)
        , QAccelerometerFilter()
        , prevX(0)
        , prevY(0)
        , prevZ(0)
        , havePrev(false)
    {
    }

    bool filter(QAccelerometerReading *reading)
    {
        // Smooth out the reported values.  Large changes are applied as-is,
        // and small jitters smooth to the rest position.
        if (havePrev) {
            qreal xdiff = reading->x() - prevX;
            qreal ydiff = reading->y() - prevY;
            qreal zdiff = reading->z() - prevZ;
#define threshold 0.196133f
            if (qAbs(xdiff) < threshold && qAbs(ydiff) < threshold && qAbs(zdiff) < threshold) {
                reading->setX(prevX + xdiff * 0.1f);
                reading->setY(prevY + ydiff * 0.1f);
                reading->setZ(prevZ + zdiff * 0.1f);
            }
        }
        prevX = reading->x();
        prevY = reading->y();
        prevZ = reading->z();
        havePrev = true;
        return true;
    }
};
//! [smoothed]

View::View(QWidget *parent)
    : QGLWidget(parent),
      sensitivity(0.1f),
      painter(0),
      showFrameRate(false)
{
#if (QT_VERSION >= QT_VERSION_CHECK(4, 7, 2))
    setAttribute(Qt::WA_LockPortraitOrientation);
#endif

    mainCamera = new Camera(this);

    roomCamera = new Camera(this);
    roomCamera->setAdjustForAspectRatio(false);

//! [accelerometer]
    sensor = new QAccelerometer(this);
    connect(sensor, SIGNAL(readingChanged()), this, SLOT(accelerometerTimeout()));
    sensor->addFilter(new smoothedaccelerometerfilter(this));
    sensor->start();
//! [accelerometer]

    time.start();

    vertexBuffer = 0;
    indexBuffer = 0;
}

View::~View()
{
    delete painter;
}

void View::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void View::initializeGL()
{
#if defined(QT_OPENGL_ES_2)
    painter = new ShaderPainter();
#else
    painter = new FixedFunctionPainter();
#endif

    glEnable(GL_DEPTH_TEST);

    roomMaterialBack = new Material();
    roomMaterialBack->setDiffuseColor(QColor(128, 100, 0));

    roomMaterialLeftRight = new Material();
    roomMaterialLeftRight->setDiffuseColor(Qt::cyan);

    roomMaterialTopBottom = new Material();
    roomMaterialTopBottom->setDiffuseColor(Qt::yellow);

    cubeMaterial = new Material();
    cubeMaterial->setColor(QColor(170, 202, 0));

    teapotMaterial = new Material();
    teapotMaterial->setAmbientColor(QColor(192, 150, 128));
    teapotMaterial->setSpecularColor(QColor(60, 60, 60));
    teapotMaterial->setShininess(128);

    roomModel = new LightModel(this);
    roomModel->setAmbientSceneColor(Qt::white);
    roomModel->setViewerPosition(LightModel::LocalViewer);

    normalModel = new LightModel(this);

    Light *light = new Light(this);
    light->setPosition(QVector3D(0.0f, 0.0f, 3.0f));
    painter->setLight(light);

    texture = bindTexture(QImage(QLatin1String(":/qtlogo.png")));

#ifdef USE_BUFFERS
    // Upload the teapot data into GL buffers for quicker rendering.
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 teapotVertexCount * teapotVertexStride * sizeof(float),
                 teapotVertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 teapotTriangleCount * 3 * sizeof(ushort),
                 teapotTriangleData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
}

void View::paintGL()
{
    if (showFrameRate)
        qWarning("time since last frame: %d ms", time.restart());

    qreal aspectRatio = qreal(width()) / qreal(height());
    QMatrix4x4 mv, mv2;
    QMatrix4x4 proj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mv = roomCamera->modelViewMatrix();
    proj = roomCamera->projectionMatrix(aspectRatio);
    painter->setLightModel(roomModel);
    painter->setMatrices(mv, proj);

    painter->selectMaterial(roomMaterialBack);
    painter->drawQuad(QVector3D(-3.0f, -3.0f, -15.0f),
                      QVector3D( 3.0f, -3.0f, -15.0f),
                      QVector3D( 3.0f,  3.0f, -15.0f),
                      QVector3D(-3.0f,  3.0f, -15.0f),
                      QVector3D(0.0f, 0.0f, 1.0f));

    painter->selectMaterial(roomMaterialLeftRight);
    painter->drawQuad(QVector3D(-3.0f, -3.0f, -15.0f),
                      QVector3D(-3.0f,  3.0f, -15.0f),
                      QVector3D(-3.0f,  3.0f, 0.0f),
                      QVector3D(-3.0f, -3.0f, 0.0f),
                      QVector3D(1.0f, 0.0f, 0.0f));
    painter->drawQuad(QVector3D(3.0f,  3.0f, -15.0f),
                      QVector3D(3.0f, -3.0f, -15.0f),
                      QVector3D(3.0f, -3.0f, 0.0f),
                      QVector3D(3.0f,  3.0f, 0.0f),
                      QVector3D(-1.0f, 0.0f, 0.0f));

    painter->selectMaterial(roomMaterialTopBottom);
    painter->drawQuad(QVector3D(-3.0f,  3.0f, -15.0f),
                      QVector3D( 3.0f,  3.0f, -15.0f),
                      QVector3D( 3.0f,  3.0f, 0.0f),
                      QVector3D(-3.0f,  3.0f, 0.0f),
                      QVector3D(0.0f, -1.0f, 0.0f));
    painter->drawQuad(QVector3D(-3.0f, -3.0f, -15.0f),
                      QVector3D(-3.0f, -3.0f, 0.0f),
                      QVector3D( 3.0f, -3.0f, 0.0f),
                      QVector3D( 3.0f, -3.0f, -15.0f),
                      QVector3D(0.0f, 1.0f, 0.0f));

    mv = mv2 = mainCamera->modelViewMatrix();
    proj = mainCamera->projectionMatrix(aspectRatio);
    mv.translate(1.0f, -0.5f, 0.0f);
    mv.rotate(45.0f, 1.0f, 1.0f, 1.0f);
    painter->setMatrices(mv, proj);
    painter->setLightModel(normalModel);
    painter->selectTexturedMaterial(cubeMaterial);
    painter->setVertices(cubeVertices, 8);
    painter->setNormals(cubeVertices + 3, 8);
    painter->setTexCoords(cubeVertices + 6, 8);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    mv2.translate(-0.8f, -1.5f, -3.0f);
    painter->setMatrices(mv2, proj);
    painter->selectMaterial(teapotMaterial);
#ifdef USE_BUFFERS
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    painter->setVertices(0, 8);
    painter->setNormals(reinterpret_cast<float *>(3 * sizeof(float)), 8);
    painter->setTexCoords(reinterpret_cast<float *>(6 * sizeof(float)), 8);
    glDrawElements(GL_TRIANGLES, teapotTriangleCount * 3,
                   GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#else
    painter->setVertices(teapotVertexData, 8);
    painter->setNormals(teapotVertexData + 3, 8);
    painter->setTexCoords(teapotVertexData + 6, 8);
    glDrawElements(GL_TRIANGLES, teapotTriangleCount * 3,
                   GL_UNSIGNED_SHORT, teapotTriangleData);
#endif
}

//! [accelerometer2]
void View::accelerometerTimeout()
{
    QVector3D g = gravity();
    mainCamera->setMotionAdjustment(g);
    roomCamera->setMotionAdjustment(g);
    update();
}

#define ACCEL_TO_G(v) (v / 9.80665)

QVector3D View::gravity() const
{
    qreal x = ACCEL_TO_G(sensor->reading()->x()) * sensitivity;
    qreal y = ACCEL_TO_G(sensor->reading()->y()) * sensitivity;
    qreal z = ACCEL_TO_G(sensor->reading()->z());

    return QVector3D(x, y, z);
}
//! [accelerometer2]
