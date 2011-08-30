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

#include "material.h"

/*!
    \class Material
    \brief The Material class describes material properties for OpenGL drawing.
    \since 4.7
    \ingroup qt3d
    \ingroup qt3d::painting
*/

class MaterialPrivate
{
public:
    explicit MaterialPrivate();

    QColor basicColor;
    QColor ambientColor;
    QColor diffuseColor;
    QColor specularColor;
    QColor emittedLight;
    qreal shininess;
};

MaterialPrivate::MaterialPrivate()
    : basicColor(255, 255, 255, 255),
      specularColor(0, 0, 0, 255),
      emittedLight(0, 0, 0, 255),
      shininess(0)
{
    ambientColor.setRgbF(0.2f, 0.2f, 0.2f, 1.0f);
    diffuseColor.setRgbF(0.8f, 0.8f, 0.8f, 1.0f);
}

/*!
    Constructs a Material object with its default values,
    and attaches it to \a parent.
*/
Material::Material(QObject *parent)
    : QObject(parent), d_ptr(new MaterialPrivate)
{
}

/*!
    Destroys this Material object.
*/
Material::~Material()
{
}

/*!
    \property Material::basicColor
    \brief the basic color of the material.  The default value
    is (1.0, 1.0, 1.0, 1.0).

    The basic color is used by effects that don't implement
    material-based lighting.  It is ignored by material-based
    lighting effects.

    \sa ambientColor(), diffuseColor(), basicColorChanged(), setColor()
*/
QColor Material::basicColor() const
{
    Q_D(const Material);
    return d->basicColor;
}

void Material::setBasicColor(const QColor& value)
{
    Q_D(Material);
    if (d->basicColor != value) {
        d->basicColor = value;
        emit basicColorChanged();
        emit materialChanged();
    }
}

/*!
    \property Material::ambientColor
    \brief the ambient color of the material.  The default value
    is (0.2, 0.2, 0.2, 1.0).

    \sa diffuseColor(), specularColor(), ambientColorChanged()
*/
QColor Material::ambientColor() const
{
    Q_D(const Material);
    return d->ambientColor;
}

void Material::setAmbientColor(const QColor& value)
{
    Q_D(Material);
    if (d->ambientColor != value) {
        d->ambientColor = value;
        emit ambientColorChanged();
        emit materialChanged();
    }
}

/*!
    \property Material::diffuseColor
    \brief the diffuse color of the material.  The default value
    is (0.8, 0.8, 0.8, 1.0).

    \sa ambientColor(), specularColor(), diffuseColorChanged()
*/
QColor Material::diffuseColor() const
{
    Q_D(const Material);
    return d->diffuseColor;
}

void Material::setDiffuseColor(const QColor& value)
{
    Q_D(Material);
    if (d->diffuseColor != value) {
        d->diffuseColor = value;
        emit diffuseColorChanged();
        emit materialChanged();
    }
}

/*!
    \property Material::specularColor
    \brief the specular color of the material.  The default value
    is (0, 0, 0, 1).

    \sa ambientColor(), diffuseColor(), specularColorChanged()
*/
QColor Material::specularColor() const
{
    Q_D(const Material);
    return d->specularColor;
}

void Material::setSpecularColor(const QColor& value)
{
    Q_D(Material);
    if (d->specularColor != value) {
        d->specularColor = value;
        emit specularColorChanged();
        emit materialChanged();
    }
}

/*!
    \property Material::emittedLight
    \brief the emitted light intensity of the material.
    The default value is (0.0, 0.0, 0.0, 1.0), which indicates
    that the material does not emit any light.

    \sa emittedLightChanged()
*/
QColor Material::emittedLight() const
{
    Q_D(const Material);
    return d->emittedLight;
}

void Material::setEmittedLight(const QColor& value)
{
    Q_D(Material);
    if (d->emittedLight != value) {
        d->emittedLight = value;
        emit emittedLightChanged();
        emit materialChanged();
    }
}

/*!
    \property Material::color
    \brief the overall color of the material.  The default value
    is (1.0, 1.0, 1.0, 1.0).

    This is a convenience property.  When read it returns basicColor().
    When written, it sets basicColor() to the value, ambientColor()
    to 20% of the value, and diffuseColor() to 80% of the value.
    The result is that regardless of whether lighting is used or not,
    the material will appear to have a similar color.

    \sa basicColor(), ambientColor(), diffuseColor()
*/
QColor Material::color() const
{
    Q_D(const Material);
    return d->basicColor;
}

void Material::setColor(const QColor& value)
{
    Q_D(Material);
    d->basicColor = value;
    d->ambientColor.setRgbF
        (value.redF() * 0.2f, value.greenF() * 0.2f,
         value.blueF() * 0.2f, value.alphaF());
    d->diffuseColor.setRgbF
        (value.redF() * 0.8f, value.greenF() * 0.8f,
         value.blueF() * 0.8f, value.alphaF());
    emit basicColorChanged();
    emit ambientColorChanged();
    emit diffuseColorChanged();
    emit materialChanged();
}

/*!
    \property Material::shininess
    \brief the specular exponent of the material, or how shiny it is.
    Must be between 0 and 128.  The default value is 0.  A value outside
    this range will be clamped to the range when the property is set.

    \sa shininessChanged()
*/
qreal Material::shininess() const
{
    Q_D(const Material);
    return d->shininess;
}

void Material::setShininess(qreal value)
{
    Q_D(Material);
    if (value < 0)
        value = 0;
    else if (value > 128)
        value = 128;
    if (d->shininess != value) {
        d->shininess = value;
        emit shininessChanged();
        emit materialChanged();
    }
}

/*!
    \fn void Material::basicColorChanged()

    This signal is emitted when basicColor() changes.

    \sa basicColor(), setBasicColor(), materialChanged()
*/

/*!
    \fn void Material::ambientColorChanged()

    This signal is emitted when ambientColor() changes.

    \sa ambientColor(), setAmbientColor(), materialChanged()
*/

/*!
    \fn void Material::diffuseColorChanged()

    This signal is emitted when diffuseColor() changes.

    \sa diffuseColor(), setDiffuseColor(), materialChanged()
*/

/*!
    \fn void Material::specularColorChanged()

    This signal is emitted when specularColor() changes.

    \sa specularColor(), setSpecularColor(), materialChanged()
*/

/*!
    \fn void Material::emittedLightChanged()

    This signal is emitted when emittedLight() changes.

    \sa emittedLight(), setEmittedLight(), materialChanged()
*/

/*!
    \fn void Material::shininessChanged()

    This signal is emitted when shininess() changes.

    \sa shininess(), setShininess(), materialChanged()
*/

/*!
    \fn void Material::materialChanged()

    This signal is emitted when one of basicColor(), ambientColor(),
    diffuseColor(), specularColor(), emittedLight(), shiniess(),
    or texture() changes.

    \sa basicColorChanged(), ambientColorChanged(), diffuseColorChanged()
    \sa specularColorChanged(), emittedLightChanged(), shininessChanged()
    \sa texturesChanged()
*/
