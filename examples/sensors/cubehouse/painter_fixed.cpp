/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Mobility Components.
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

#include "painter.h"
#include "light.h"
#include "lightmodel.h"
#include "material.h"

FixedFunctionPainter::FixedFunctionPainter()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_CULL_FACE);
}

static void setMatrix(GLenum type, const QMatrix4x4 &matrix)
{
    glMatrixMode(type);
    if (sizeof(qreal) == sizeof(GLfloat)) {
        glLoadMatrixf(reinterpret_cast<const GLfloat *>(matrix.constData()));
    } else {
        GLfloat mat[16];
        const qreal *m = matrix.constData();
        for (int index = 0; index < 16; ++index)
            mat[index] = m[index];
        glLoadMatrixf(mat);
    }
}

void FixedFunctionPainter::setMatrices
    (const QMatrix4x4 &mv, const QMatrix4x4 &proj)
{
    setMatrix(GL_PROJECTION, proj);
    setMatrix(GL_MODELVIEW, mv);
}

static void setLight(int light, const Light *parameters,
                     const QMatrix4x4& transform = QMatrix4x4())
{
    GLfloat params[4];

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    QColor color = parameters->ambientColor();
    params[0] = color.redF();
    params[1] = color.greenF();
    params[2] = color.blueF();
    params[3] = color.alphaF();
    glLightfv(light, GL_AMBIENT, params);

    color = parameters->diffuseColor();
    params[0] = color.redF();
    params[1] = color.greenF();
    params[2] = color.blueF();
    params[3] = color.alphaF();
    glLightfv(light, GL_DIFFUSE, params);

    color = parameters->specularColor();
    params[0] = color.redF();
    params[1] = color.greenF();
    params[2] = color.blueF();
    params[3] = color.alphaF();
    glLightfv(light, GL_SPECULAR, params);

    QVector4D vector = parameters->eyePosition(transform);
    params[0] = vector.x();
    params[1] = vector.y();
    params[2] = vector.z();
    params[3] = vector.w();
    glLightfv(light, GL_POSITION, params);

    QVector3D spotDirection = parameters->eyeSpotDirection(transform);
    params[0] = spotDirection.x();
    params[1] = spotDirection.y();
    params[2] = spotDirection.z();
    glLightfv(light, GL_SPOT_DIRECTION, params);

    params[0] = parameters->spotExponent();
    glLightfv(light, GL_SPOT_EXPONENT, params);

    params[0] = parameters->spotAngle();
    glLightfv(light, GL_SPOT_CUTOFF, params);

    params[0] = parameters->constantAttenuation();
    glLightfv(light, GL_CONSTANT_ATTENUATION, params);

    params[0] = parameters->linearAttenuation();
    glLightfv(light, GL_LINEAR_ATTENUATION, params);

    params[0] = parameters->quadraticAttenuation();
    glLightfv(light, GL_QUADRATIC_ATTENUATION, params);

    glPopMatrix();
}

static void setLightModel(const LightModel *lightModel)
{
    GLfloat values[4];
#ifdef GL_LIGHT_MODEL_TWO_SIDE
    if (lightModel->model() == LightModel::TwoSided)
        values[0] = 1.0f;
    else
        values[0] = 0.0f;
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, values);
#endif
#ifdef GL_LIGHT_MODEL_COLOR_CONTROL
    if (lightModel->colorControl() == LightModel::SeparateSpecularColor)
        values[0] = GL_SEPARATE_SPECULAR_COLOR;
    else
        values[0] = GL_SINGLE_COLOR;
    glLightModelfv(GL_LIGHT_MODEL_COLOR_CONTROL, values);
#endif
#ifdef GL_LIGHT_MODEL_LOCAL_VIEWER
    if (lightModel->viewerPosition() == LightModel::LocalViewer)
        values[0] = 1.0f;
    else
        values[0] = 0.0f;
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, values);
#endif
#ifdef GL_LIGHT_MODEL_AMBIENT
    QColor color = lightModel->ambientSceneColor();
    values[0] = color.redF();
    values[1] = color.blueF();
    values[2] = color.greenF();
    values[3] = color.alphaF();
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, values);
#endif
}

static void setMaterial(int face, const Material *parameters)
{
    GLfloat params[17];

    QColor mcolor = parameters->ambientColor();
    params[0] = mcolor.redF();
    params[1] = mcolor.greenF();
    params[2] = mcolor.blueF();
    params[3] = mcolor.alphaF();

    mcolor = parameters->diffuseColor();
    params[4] = mcolor.redF();
    params[5] = mcolor.greenF();
    params[6] = mcolor.blueF();
    params[7] = mcolor.alphaF();

    mcolor = parameters->specularColor();
    params[8] = mcolor.redF();
    params[9] = mcolor.greenF();
    params[10] = mcolor.blueF();
    params[11] = mcolor.alphaF();

    mcolor = parameters->emittedLight();
    params[12] = mcolor.redF();
    params[13] = mcolor.greenF();
    params[14] = mcolor.blueF();
    params[15] = mcolor.alphaF();

    params[16] = parameters->shininess();

    glMaterialfv(face, GL_AMBIENT, params);
    glMaterialfv(face, GL_DIFFUSE, params + 4);
    glMaterialfv(face, GL_SPECULAR, params + 8);
    glMaterialfv(face, GL_EMISSION, params + 12);
    glMaterialfv(face, GL_SHININESS, params + 16);
}

void FixedFunctionPainter::selectMaterial(Material *material)
{
    ::setLight(GL_LIGHT0, light);
    ::setLightModel(lightModel);
    ::setMaterial(GL_FRONT_AND_BACK, material);
    glDisable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void FixedFunctionPainter::selectTexturedMaterial(Material *material)
{
    ::setLight(GL_LIGHT0, light);
    ::setLightModel(lightModel);
    ::setMaterial(GL_FRONT_AND_BACK, material);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void FixedFunctionPainter::setVertices(const float *array, int stride)
{
    glVertexPointer(3, GL_FLOAT, stride * sizeof(float), array);
}

void FixedFunctionPainter::setTexCoords(const float *array, int stride)
{
    glTexCoordPointer(2, GL_FLOAT, stride * sizeof(float), array);
}

void FixedFunctionPainter::setNormals(const float *array, int stride)
{
    glNormalPointer(GL_FLOAT, stride * sizeof(float), array);
}
