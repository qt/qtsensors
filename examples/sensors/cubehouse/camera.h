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

#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore/qobject.h>
#include <QtCore/qsize.h>
#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qquaternion.h>

class CameraPrivate;
class QGLPainter;

class Camera : public QObject
{
    Q_OBJECT
    Q_ENUMS(ProjectionType)
    Q_PROPERTY(ProjectionType projectionType READ projectionType WRITE setProjectionType NOTIFY projectionChanged)
    Q_PROPERTY(qreal fieldOfView READ fieldOfView WRITE setFieldOfView NOTIFY projectionChanged)
    Q_PROPERTY(qreal nearPlane READ nearPlane WRITE setNearPlane NOTIFY projectionChanged)
    Q_PROPERTY(qreal farPlane READ farPlane WRITE setFarPlane NOTIFY projectionChanged)
    Q_PROPERTY(QSizeF viewSize READ viewSize WRITE setViewSize NOTIFY projectionChanged)
    Q_PROPERTY(QSizeF minViewSize READ minViewSize WRITE setMinViewSize NOTIFY projectionChanged)
    Q_PROPERTY(int screenRotation READ screenRotation WRITE setScreenRotation NOTIFY projectionChanged)
    Q_PROPERTY(qreal xEye READ xEye WRITE setXEye NOTIFY viewChanged)
    Q_PROPERTY(qreal yEye READ yEye WRITE setYEye NOTIFY viewChanged)
    Q_PROPERTY(qreal zEye READ zEye WRITE setZEye NOTIFY viewChanged)
    Q_PROPERTY(QVector3D eye READ eye WRITE setEye NOTIFY viewChanged)
    Q_PROPERTY(QVector3D upVector READ upVector WRITE setUpVector NOTIFY viewChanged)
    Q_PROPERTY(qreal xCentre READ xCentre WRITE setXCentre NOTIFY viewChanged)
    Q_PROPERTY(qreal yCentre READ yCentre WRITE setYCentre NOTIFY viewChanged)
    Q_PROPERTY(qreal zCentre READ zCentre WRITE setZCentre NOTIFY viewChanged)
    Q_PROPERTY(QVector3D center READ center WRITE setCenter NOTIFY viewChanged)
    Q_PROPERTY(qreal eyeSeparation READ eyeSeparation WRITE setEyeSeparation NOTIFY viewChanged)
    Q_PROPERTY(QVector3D motionAdjustment READ motionAdjustment WRITE setMotionAdjustment DESIGNABLE false NOTIFY viewChanged)
    Q_PROPERTY(bool adjustForAspectRatio READ adjustForAspectRatio WRITE setAdjustForAspectRatio NOTIFY viewChanged)
public:
    explicit Camera(QObject *parent = 0);
    ~Camera();

    enum ProjectionType
    {
        Perspective,
        Orthographic
    };

    Camera::ProjectionType projectionType() const;
    void setProjectionType(Camera::ProjectionType value);

    qreal fieldOfView() const;
    void setFieldOfView(qreal angle);

    qreal nearPlane() const;
    void setNearPlane(qreal value);

    qreal farPlane() const;
    void setFarPlane(qreal value);

    QSizeF viewSize() const;
    void setViewSize(const QSizeF& size);

    QSizeF minViewSize() const;
    void setMinViewSize(const QSizeF& size);

    int screenRotation() const;
    void setScreenRotation(int angle);

    qreal xEye() const;
    void setXEye(qreal value);
    qreal yEye() const;
    void setYEye(qreal value);
    qreal zEye() const;
    void setZEye(qreal value);

    QVector3D eye() const;
    void setEye(const QVector3D& vertex);

    QVector3D upVector() const;
    void setUpVector(const QVector3D& vector);

    qreal xCentre() const;
    void setXCentre(qreal value);
    qreal yCentre() const;
    void setYCentre(qreal value);
    qreal zCentre() const;
    void setZCentre(qreal value);

    QVector3D center() const;
    void setCenter(const QVector3D& vertex);

    qreal eyeSeparation() const;
    void setEyeSeparation(qreal value);

    QVector3D motionAdjustment() const;
    void setMotionAdjustment(const QVector3D& vector);

    bool adjustForAspectRatio() const;
    void setAdjustForAspectRatio(bool value);

    QQuaternion tilt(qreal angle) const;
    QQuaternion pan(qreal angle) const;
    QQuaternion roll(qreal angle) const;

    void rotateEye(const QQuaternion& q);
    void rotateCenter(const QQuaternion& q);

    QVector3D translation(qreal x, qreal y, qreal z) const;

    void translateEye(const QVector3D& vector);
    void translateCenter(const QVector3D& vector);

    QMatrix4x4 projectionMatrix(qreal aspectRatio) const;
    QMatrix4x4 modelViewMatrix() const;

Q_SIGNALS:
    void projectionChanged();
    void viewChanged();

private:
    CameraPrivate *d_ptr;

    CameraPrivate *d_func() const { return d_ptr; }

    Q_DISABLE_COPY(Camera)
};

#endif
