/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QSEONSOR2TILT_H
#define QSEONSOR2TILT_H

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>
#include <qaccelerometer.h>

QT_BEGIN_NAMESPACE

class QSensor2Tilt : public QObject, public QAccelerometerFilter
{
    Q_OBJECT
    Q_ENUMS(TiltReference)
    Q_PROPERTY(TiltReference measureFrom READ measureFrom WRITE setMeasureFrom NOTIFY measureFromChanged)
    Q_PROPERTY(float yRotation READ yRotation NOTIFY yRotationChanged)
    Q_PROPERTY(float xRotation READ xRotation NOTIFY xRotationChanged)
    Q_PROPERTY(bool radian READ radian WRITE setRadian)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    QSensor2Tilt(QObject* parent = 0);
    virtual ~QSensor2Tilt();

    enum TiltReference{
        TopUp = 0,
        TopDown,
        LeftUp,
        RightUp,
        FaceUp,
        FaceDown
    };

Q_SIGNALS:
    void measureFromChanged();
    void yRotationChanged();
    void xRotationChanged();
    void dataRateChanged();
    void runningChanged();

private:
    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);

    TiltReference measureFrom();
    void setMeasureFrom(TiltReference val);
    float yRotation();
    float xRotation();
    bool radian();
    void setRadian(bool val);
    int dataRate();
    void setDataRate(int val);
    bool running();
    void setRunning(bool val);

    QAccelerometer* _accel;
    TiltReference _measureFrom;
    float _yRotation;
    float _xRotation;
    bool _useRadian;
    bool _init;
};

QML_DECLARE_TYPE(QT_PREPEND_NAMESPACE(QSensor2Tilt))

QT_END_NAMESPACE

#endif // QSEONSOR2TILT_H
