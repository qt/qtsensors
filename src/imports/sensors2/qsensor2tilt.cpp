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

#include "qsensor2tilt.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <errno.h>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmlclass TiltSensor QSensor2Tilt
    \inqmlmodule QtSensors 5
    \ingroup qml-QtSensors5
    \since QtSensors 5.0
    \brief The TiltSensor element provides tilt datas from x and y rotation of the device using the accelerometer sensor.

    This element is part of the \bold{QtSensors 5} module.

    \target tiltreferenceenum
    \section1 Enums
    \section2 TiltSensor::TiltReference

    This enum describes the orientation of the device.

    \table
    \row
        \o TiltSensor::TopUp
        \o The top of the device points up
        \o
        \image TopUp.gif
    \row
        \o TiltSensor::TopDown
        \o The top of the device points down
        \o
        \image TopDown.gif
    \row
        \o TiltSensor::LeftUp
        \o The left site of the device points up
        \o
        \image LeftUp.gif
    \row
        \o TiltSensor::RightUp
        \o The right site of the device points up
        \o
        \image RightUp.gif
    \row
        \o TiltSensor::FaceUp
        \o The screen of the device points up
        \o
        \image FaceUp.gif
    \row
        \o TiltSensor::FaceDown
        \o The screen of the device points down
        \o
        \image FaceDown.gif
    \endtable

*/
QSensor2Tilt::QSensor2Tilt(QObject* parent)
    : QObject(parent)
    , _measureFrom(QSensor2Tilt::FaceUp)
    , _yRotation(0)
    , _xRotation(0)
    , _useRadian(true)
{
    _accel = new QAccelerometer(this);
    _accel->addFilter(this);
}

QSensor2Tilt::~QSensor2Tilt()
{
}

/*!
    \qmlproperty bool QtSensors5::TiltSensor::dataRate
    Holds the data rate that the sensor should be run at.
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::onDataRateChanged()
    This signal is emitted whenever the value of the property dataRate has been changed.
*/
int QSensor2Tilt::dataRate()
{
    return _accel->dataRate();
}

void QSensor2Tilt::setDataRate(int val)
{
    if (val != dataRate()){
        _accel->setDataRate(val);
        emit dataRateChanged();
    }
}

/*!
    \qmlproperty bool QtSensors5::TiltSensor::running
    Holds the identication if the sensor runs or not.
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::onRunningChanged()
    This signal is emitted whenever the value of the property running has been changed.
*/
bool QSensor2Tilt::running()
{
    return _accel->isActive();
}

void QSensor2Tilt::setRunning(bool val)
{
    bool active = running();
    if (active != val){
        if (val){
            bool ret = _accel->start();
            if (!ret)
                qWarning() << "couldn't start the sensor.";
        }
        else
            _accel->stop();
        emit runningChanged();
    }
}

/*!
    \qmlproperty QSensor2Tilt::TiltReference QtSensors5::TiltSensor::measureFrom
    Holds the orientation in which the rotation should be calculated.
    \sa {tiltreferenceenum} {TiltReference::TiltReference}
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::onMeasureFromChanged()
    This signal is emitted whenever the value of the property measureFrom has been changed.
*/
QSensor2Tilt::TiltReference QSensor2Tilt::measureFrom()
{
    return _measureFrom;
}

void QSensor2Tilt::setMeasureFrom(QSensor2Tilt::TiltReference val)
{
    if (val != _measureFrom){
        _measureFrom = val;
        emit measureFromChanged();
    }
}

/*!
    \qmlproperty bool QtSensors5::TiltSensor::radian
    Holds the unit of the rotation. True is rad otherwise deg. true = report values in radians. false = report values in degrees.
*/
bool QSensor2Tilt::radian()
{
    return _useRadian;
}

void QSensor2Tilt::setRadian(bool val)
{
    _useRadian = val;
}


/*!
    \qmlproperty float QtSensors5::TiltSensor::yRotation
    Holds the rotation arround the y axis.

    \table
    \row
        \o
        \image YAngle.gif
        \o
        \image YAngleNegative.gif
    \endtable
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::onYRotationChanged()
    This signal is emitted whenever the value of the property yRotation has been changed.
*/
float QSensor2Tilt::yRotation()
{
    return _yRotation;
}

/*!
    \qmlproperty float QtSensors5::TiltSensor::xRotation
    Holds the rotation arround the x axis.
    \table
    \row
        \o
        \image XAngle.gif
        \o
        \image XAngleNegative.gif
    \endtable
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::onXRotationChanged()
    This signal is emitted whenever the value of the property XRotation has been changed.
*/
float QSensor2Tilt::xRotation()
{
    return _xRotation;
}

/*
  Angle between Ground and X
                |            Ax           |
  pitch = arctan| ----------------------- |
                |  sqrt(Ay * Ay + Az * Az)|
*/
inline float calcPitch(double Ax, double Ay, double Az)
{
    errno = 0;
    float ret = (float)-atan(Ax / (sqrt(Ay * Ay + Az * Az)));
    if (errno == EDOM){
        ret = 0.0;
        errno = 0;
    }
    return ret;
}

/*
  Angle between Ground and Y
                |            Ay           |
  pitch = arctan| ----------------------- |
                |  sqrt(Ax * Ax + Az * Az)|
*/
inline float calcRoll(double Ax, double Ay, double Az)
{
    errno = 0;
    float ret = (float)atan(Ay / (sqrt(Ax * Ax + Az * Az)));
    if (errno == EDOM){
        ret = 0.0;
        errno = 0;
    }
    return ret;
}

bool QSensor2Tilt::filter(QAccelerometerReading* reading)
{
    /*
      z  y
      | /
      |/___ x
    */

    int x = reading->x();
    int y = reading->y();
    int z = reading->z();
    float xrot = 0;
    float yrot = 0;

    switch (_measureFrom)
    {
    case QSensor2Tilt::FaceUp:
        /*
          y
          |        => Ax = x, Ay = y, Az = z
          |___ x
        */
        yrot = calcPitch(x, y, z);
        xrot = calcRoll(x, y, z);
        break;
    case QSensor2Tilt::LeftUp:
        /*
          z
          |        => Ax = y, Ay = z, Az = x
          |___ y
        */
        yrot = calcPitch(y, z, x);
        xrot = -calcRoll(y, z, x);
        break;
    case QSensor2Tilt::TopDown:
        /*
          z
          |        => Ax = -x, Ay = z, Az = y
          |___ -x
        */
        yrot = -calcPitch(x, z, y);
        xrot = -calcRoll(x, z, y);
        break;
    case QSensor2Tilt::FaceDown:
        /*
          -y
          |        => Ax = x, Ay = -y, Az = -z
          |___ x
        */
        yrot = calcPitch(-x, -y, z);
        xrot = -calcRoll(-x, -y, z);
        break;
    case QSensor2Tilt::RightUp:
        /*
          z
          |        => Ax = -y, Ay = z, Az = -x
          |___ -y
        */
        yrot = calcPitch(-y, z, -x);
        xrot = -calcRoll(-y, z, -x);
        break;
    case QSensor2Tilt::TopUp:
        /*
          z
          |        => Ax = x, Ay = z, Az = -y
          |___ x
        */
        yrot = calcPitch(x, z, -y);
        xrot = -calcRoll(x, z, -y);
        break;
    }



    if (!_useRadian){
        yrot = 180 * yrot / M_PI;
        xrot = 180 * xrot / M_PI;
    }

    if (xrot != _xRotation){
        _xRotation = xrot;
        emit xRotationChanged();
    }
    if (yrot != _yRotation){
        _yRotation = yrot;
        emit yRotationChanged();
    }

    return false;
}

QT_END_NAMESPACE
