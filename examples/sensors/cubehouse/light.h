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

#ifndef LIGHT_H
#define LIGHT_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtGui/qcolor.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qvector4d.h>

class LightPrivate;
QT_BEGIN_NAMESPACE
class QMatrix4x4;
QT_END_NAMESPACE

class Light : public QObject
{
    Q_OBJECT
    Q_ENUMS(LightType)
    Q_PROPERTY(LightType type READ type)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(QVector3D direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(QColor ambientColor READ ambientColor WRITE setAmbientColor NOTIFY ambientColorChanged)
    Q_PROPERTY(QColor diffuseColor READ diffuseColor WRITE setDiffuseColor NOTIFY diffuseColorChanged)
    Q_PROPERTY(QColor specularColor READ specularColor WRITE setSpecularColor NOTIFY specularColorChanged)
    Q_PROPERTY(QVector3D spotDirection READ spotDirection WRITE setSpotDirection NOTIFY spotDirectionChanged)
    Q_PROPERTY(qreal spotExponent READ spotExponent WRITE setSpotExponent NOTIFY spotExponentChanged)
    Q_PROPERTY(qreal spotAngle READ spotAngle WRITE setSpotAngle NOTIFY spotAngleChanged)
    Q_PROPERTY(qreal constantAttenuation READ constantAttenuation WRITE setConstantAttenuation NOTIFY constantAttenuationChanged)
    Q_PROPERTY(qreal linearAttenuation READ linearAttenuation WRITE setLinearAttenuation NOTIFY linearAttenuationChanged)
    Q_PROPERTY(qreal quadraticAttenuation READ quadraticAttenuation WRITE setQuadraticAttenuation NOTIFY quadraticAttenuationChanged)
public:
    enum LightType {
        Directional,
        Positional
    };

    Light(QObject *parent = 0);
    ~Light();

    Light::LightType type() const;

    QVector3D position() const;
    void setPosition(const QVector3D& value);

    QVector3D direction() const;
    void setDirection(const QVector3D& value);

    QColor ambientColor() const;
    void setAmbientColor(const QColor& value);

    QColor diffuseColor() const;
    void setDiffuseColor(const QColor& value);

    QColor specularColor() const;
    void setSpecularColor(const QColor& value);

    QVector3D spotDirection() const;
    void setSpotDirection(const QVector3D& value);

    qreal spotExponent() const;
    void setSpotExponent(qreal value);

    qreal spotAngle() const;
    void setSpotAngle(qreal value);

    qreal spotCosAngle() const;

    qreal constantAttenuation() const;
    void setConstantAttenuation(qreal value);

    qreal linearAttenuation() const;
    void setLinearAttenuation(qreal value);

    qreal quadraticAttenuation() const;
    void setQuadraticAttenuation(qreal value);

    QVector4D eyePosition(const QMatrix4x4& transform) const;
    QVector3D eyeSpotDirection(const QMatrix4x4& transform) const;

Q_SIGNALS:
    void positionChanged();
    void directionChanged();
    void ambientColorChanged();
    void diffuseColorChanged();
    void specularColorChanged();
    void spotDirectionChanged();
    void spotExponentChanged();
    void spotAngleChanged();
    void constantAttenuationChanged();
    void linearAttenuationChanged();
    void quadraticAttenuationChanged();
    void lightChanged();

private:
    QScopedPointer<LightPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Light)
    Q_DISABLE_COPY(Light)
};

#endif
