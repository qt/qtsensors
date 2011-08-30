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

#ifndef PAINTER_H
#define PAINTER_H

#include <QtOpenGL/qgl.h>
#include <QtGui/qmatrix4x4.h>

class Light;
class LightModel;
class Material;
class QGLShaderProgram;

class Painter
{
public:
    Painter() : light(0), lightModel(0) {}
    virtual ~Painter() {}

    virtual void setMatrices(const QMatrix4x4 &mv, const QMatrix4x4 &proj) = 0;
    virtual void selectMaterial(Material *material) = 0;
    virtual void selectTexturedMaterial(Material *material) = 0;
    virtual void setVertices(const float *array, int stride) = 0;
    virtual void setTexCoords(const float *array, int stride) = 0;
    virtual void setNormals(const float *array, int stride) = 0;

    void drawQuad(const QVector3D &c1, const QVector3D &c2,
                  const QVector3D &c3, const QVector3D &c4,
                  const QVector3D &normal);

    void setLight(Light *value) { light = value; }
    void setLightModel(LightModel *value) { lightModel = value; }

protected:
    Light *light;
    LightModel *lightModel;
};

class FixedFunctionPainter : public Painter
{
public:
    FixedFunctionPainter();

    void setMatrices(const QMatrix4x4 &mv, const QMatrix4x4 &proj);
    void selectMaterial(Material *material);
    void selectTexturedMaterial(Material *material);
    void setVertices(const float *array, int stride);
    void setTexCoords(const float *array, int stride);
    void setNormals(const float *array, int stride);
};

class ShaderPainter : public Painter
{
public:
    ShaderPainter();
    ~ShaderPainter();

    void setMatrices(const QMatrix4x4 &mv, const QMatrix4x4 &proj);
    void selectMaterial(Material *material);
    void selectTexturedMaterial(Material *material);
    void setVertices(const float *array, int stride);
    void setTexCoords(const float *array, int stride);
    void setNormals(const float *array, int stride);

private:
    QGLShaderProgram *materialProgram;
    QGLShaderProgram *textureProgram;
    QGLShaderProgram *currentProgram;
    QMatrix4x4 combinedMatrix;
    QMatrix4x4 modelViewMatrix;
    QMatrix3x3 normalMatrix;
    bool matricesChanged;

    void updateMaterials(QGLShaderProgram *program, Material *material);
};

#endif
