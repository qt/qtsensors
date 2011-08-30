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

#ifndef MATERIAL_H
#define MATERIAL_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtGui/qcolor.h>

class MaterialPrivate;

class Material : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor basicColor READ basicColor WRITE setBasicColor NOTIFY basicColorChanged)
    Q_PROPERTY(QColor ambientColor READ ambientColor WRITE setAmbientColor NOTIFY ambientColorChanged)
    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
    Q_PROPERTY(QColor specularColor READ specularColor WRITE setSpecularColor NOTIFY specularColorChanged)
    Q_PROPERTY(QColor emittedLight READ emittedLight WRITE setEmittedLight NOTIFY emittedLightChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY basicColorChanged)
    Q_PROPERTY(qreal shininess READ shininess WRITE setShininess NOTIFY shininessChanged)
public:
    explicit Material(QObject *parent = 0);
    ~Material();

    QColor basicColor() const;
    void setBasicColor(const QColor& value);

    QColor ambientColor() const;
    void setAmbientColor(const QColor& value);

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor& value);

    QColor specularColor() const;
    void setSpecularColor(const QColor& value);

    QColor emittedLight() const;
    void setEmittedLight(const QColor& value);

    QColor color() const;
    void setColor(const QColor& value);

    qreal shininess() const;
    void setShininess(qreal value);

Q_SIGNALS:
    void basicColorChanged();
    void ambientColorChanged();
    void diffuseColorChanged();
    void specularColorChanged();
    void emittedLightChanged();
    void shininessChanged();
    void materialChanged();

private:
    QScopedPointer<MaterialPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Material)
    Q_DISABLE_COPY(Material)
};

#endif
