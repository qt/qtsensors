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
#include <QtOpenGL/qglshaderprogram.h>

ShaderPainter::ShaderPainter()
{
    materialProgram = new QGLShaderProgram();
    materialProgram->addShaderFromSourceFile
        (QGLShader::Vertex, QLatin1String(":/lighting.vsh"));
    materialProgram->addShaderFromSourceFile
        (QGLShader::Fragment, QLatin1String(":/material.fsh"));
    materialProgram->bindAttributeLocation("vertex", 0);
    materialProgram->bindAttributeLocation("normal", 1);
    materialProgram->bindAttributeLocation("texcoord", 2);
    materialProgram->link();

    textureProgram = new QGLShaderProgram();
    textureProgram->addShaderFromSourceFile
        (QGLShader::Vertex, QLatin1String(":/lighting.vsh"));
    textureProgram->addShaderFromSourceFile
        (QGLShader::Fragment, QLatin1String(":/texture.fsh"));
    textureProgram->bindAttributeLocation("vertex", 0);
    textureProgram->bindAttributeLocation("normal", 1);
    textureProgram->bindAttributeLocation("texcoord", 2);
    textureProgram->link();

    currentProgram = 0;
    matricesChanged = false;
}

ShaderPainter::~ShaderPainter()
{
    delete materialProgram;
    delete textureProgram;
}

void ShaderPainter::setMatrices(const QMatrix4x4 &mv, const QMatrix4x4 &proj)
{
    combinedMatrix = proj * mv;
    modelViewMatrix = mv;
    normalMatrix = mv.normalMatrix();
    matricesChanged = true;
}

void ShaderPainter::selectMaterial(Material *material)
{
    if (currentProgram != materialProgram) {
        materialProgram->bind();
        materialProgram->enableAttributeArray(0);
        materialProgram->enableAttributeArray(1);
        materialProgram->disableAttributeArray(2);
        currentProgram = materialProgram;
        matricesChanged = true;
    }
    if (matricesChanged) {
        materialProgram->setUniformValue("matrix", combinedMatrix);
        materialProgram->setUniformValue("modelView", modelViewMatrix);
        materialProgram->setUniformValue("normalMatrix", normalMatrix);
        matricesChanged = false;
    }
    updateMaterials(materialProgram, material);
}

void ShaderPainter::selectTexturedMaterial(Material *material)
{
    if (currentProgram != textureProgram) {
        textureProgram->bind();
        textureProgram->enableAttributeArray(0);
        textureProgram->enableAttributeArray(1);
        textureProgram->enableAttributeArray(2);
        textureProgram->setUniformValue("tex", 0);
        currentProgram = textureProgram;
        matricesChanged = true;
    }
    if (matricesChanged) {
        textureProgram->setUniformValue("matrix", combinedMatrix);
        textureProgram->setUniformValue("modelView", modelViewMatrix);
        textureProgram->setUniformValue("normalMatrix", normalMatrix);
        matricesChanged = false;
    }
    updateMaterials(textureProgram, material);
}

void ShaderPainter::setVertices(const float *array, int stride)
{
    // Doesn't matter which program we use - they have the same locations.
    materialProgram->setAttributeArray(0, array, 3, stride * sizeof(float));
}

void ShaderPainter::setTexCoords(const float *array, int stride)
{
    materialProgram->setAttributeArray(2, array, 2, stride * sizeof(float));
}

void ShaderPainter::setNormals(const float *array, int stride)
{
    materialProgram->setAttributeArray(1, array, 3, stride * sizeof(float));
}

void ShaderPainter::updateMaterials
    (QGLShaderProgram *program, Material *material)
{
    // Set the uniform variables for the light.
    QVector4D pli = light->eyePosition(QMatrix4x4());
    program->setUniformValue("pli", QVector3D(pli.x(), pli.y(), pli.z()));
    program->setUniformValue("pliw", GLfloat(pli.w()));

    // Set the uniform variables for the light model.
    program->setUniformValue("viewerAtInfinity", (int)(lightModel->viewerPosition() == LightModel::ViewerAtInfinity));
    program->setUniformValue("acs", lightModel->ambientSceneColor());

    // Set the uniform variables for the material.
    program->setUniformValue("acm", material->ambientColor());
    program->setUniformValue("dcm", material->diffuseColor());
    program->setUniformValue("scm", material->specularColor());
    program->setUniformValue("srm", (float)(material->shininess()));
}
