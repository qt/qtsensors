/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSensors module of the Qt Toolkit.
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
    Q_ENUMS(Unit)
    Q_PROPERTY(qreal yRotation READ yRotation NOTIFY yRotationChanged)
    Q_PROPERTY(qreal xRotation READ xRotation NOTIFY xRotationChanged)
    Q_PROPERTY(Unit unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(qreal accuracy READ accuracy WRITE setAccuracy NOTIFY accuracyChanged)
    Q_PROPERTY(QByteArray settings READ settings WRITE setSettings)

public:
    QSensor2Tilt(QObject* parent = 0);
    virtual ~QSensor2Tilt();
    Q_INVOKABLE void calibrate();

    enum Unit{
        Radians = 0
        , Degrees
    };

Q_SIGNALS:
    void unitChanged();
    void yRotationChanged();
    void xRotationChanged();
    void dataRateChanged();
    void enabledChanged();
    void tiltChanged(qreal deltaX, qreal deltaY);
    void accuracyChanged();

private:
    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* reading);
    qreal yRotation();
    qreal xRotation();
    Unit unit();
    void setUnit(const Unit val);
    int dataRate();
    void setDataRate(const int val);
    bool enabled();
    void setEnabled(bool val);
    qreal accuracy();
    void setAccuracy(const qreal val);
    QByteArray settings() const;
    void setSettings(const QByteArray val);

    QAccelerometer* _accel;
    qreal _yRotation;
    qreal _xRotation;
    qreal _radAccuracy;
    Unit _unit;
    qreal _pitch;
    qreal _roll;
    qreal _calibratedPitch;
    qreal _calibratedRoll;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QSensor2Tilt)

#endif // QSEONSOR2TILT_H
