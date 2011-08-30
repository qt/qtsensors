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

#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtGui/qcolor.h>

class LightModelPrivate;

class LightModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(Model)
    Q_ENUMS(ColorControl)
    Q_ENUMS(ViewerPosition)
    Q_PROPERTY(Model model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(ColorControl colorControl READ colorControl WRITE setColorControl NOTIFY colorControlChanged)
    Q_PROPERTY(ViewerPosition viewerPosition READ viewerPosition WRITE setViewerPosition NOTIFY viewerPositionChanged)
    Q_PROPERTY(QColor ambientSceneColor READ ambientSceneColor WRITE setAmbientSceneColor NOTIFY ambientSceneColorChanged)
public:
    explicit LightModel(QObject *parent = 0);
    ~LightModel();

    enum Model
    {
        OneSided,
        TwoSided
    };

    enum ColorControl
    {
        SingleColor,
        SeparateSpecularColor
    };

    enum ViewerPosition
    {
        ViewerAtInfinity,
        LocalViewer
    };

    LightModel::Model model() const;
    void setModel(LightModel::Model value);

    LightModel::ColorControl colorControl() const;
    void setColorControl(LightModel::ColorControl value);

    LightModel::ViewerPosition viewerPosition() const;
    void setViewerPosition(LightModel::ViewerPosition value);

    QColor ambientSceneColor() const;
    void setAmbientSceneColor(const QColor& value);

Q_SIGNALS:
    void modelChanged();
    void colorControlChanged();
    void viewerPositionChanged();
    void ambientSceneColorChanged();
    void lightModelChanged();

private:
    QScopedPointer<LightModelPrivate> d_ptr;

    Q_DECLARE_PRIVATE(LightModel)
    Q_DISABLE_COPY(LightModel)
};

#endif
