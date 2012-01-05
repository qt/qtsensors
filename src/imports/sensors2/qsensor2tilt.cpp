/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
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

#include "qsensor2tilt.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <QtCore/QDebug>
#include <QtCore/QStringList>

#define MAXRATE 30

QT_BEGIN_NAMESPACE

/*!
    \qmlclass TiltSensor QSensor2Tilt
    \inqmlmodule QtSensors 5
    \ingroup qml-QtSensors5
    \since QtSensors 5.0
    \brief The TiltSensor element provides tilt datas from x and y rotation of the device using the accelerometer sensor.

    This element is part of the \bold{QtSensors 5} module.
*/
QSensor2Tilt::QSensor2Tilt(QObject* parent)
    : QObject(parent)
    , _yRotation(0)
    , _xRotation(0)
    , _radAccuracy(M_PI / 180)
    , _unit(QSensor2Tilt::Radians)
    , _pitch(0)
    , _roll(0)
    , _calibratedPitch(0)
    , _calibratedRoll(0)
    , _speed(QSensor2Tilt::Slow)
{
    _accel = new QAccelerometer(this);
    _accel->addFilter(this);
}

QSensor2Tilt::~QSensor2Tilt()
{
}

int searchDataRate(const QList<int>& datarates, int value)
{
    int l = 0;
    int r = datarates.count() - 1;
    int m = (l + r) / 2;

    while (l <= r) {
        m = (l + r) / 2;
        if (datarates[m] == value)
          break;
        else if (datarates[m] < value)
          r = m - 1;
        else
          l = m + 1;
    }
    if (m > 0){
        int ddr = datarates[m - 1];
        ddr -= value;
        int ddr1 = datarates[m] - value;
        if (ddr1 < 0) ddr1 = -ddr1;
        if (ddr < ddr1)
            return datarates[m - 1];
    }

    return datarates[m];
}

void QSensor2Tilt::createRunModeDataRateMap()
{
    _dataRate.clear();
    qrangelist rl = _accel->availableDataRates();

    //1. make a list of all available datarates
    QList<int> dr;
    foreach (const qrange &r, rl) {
        for (int i = r.first; i <= r.second; i++){
            if (i <= MAXRATE){
                if (!dr.contains(i))
                   dr.append(i);
            }
        }
    }

    //2. Sort the list
    if (dr.count() > 0){
        qSort(dr.begin(), dr.end(), qGreater<int>());
        _dataRate.insert(QSensor2Tilt::Slow, searchDataRate(dr, 2));
        _dataRate.insert(QSensor2Tilt::Medium, searchDataRate(dr, 10));
        _dataRate.insert(QSensor2Tilt::Fast, searchDataRate(dr, 20));
    }
}

/*!
    \qmlproperty bool QtSensors5::TiltSensor::speed
    Holds the speed that the sensor should be run at.
    Default is Slow.

    \table
    \row
        \o TiltSensor.Slow
        \o The sensor runs in slow mode.
        \o Closest available datarate at 2Hz.
    \row
        \o TiltSensor.Medium
        \o The sensor runs in medium mode.
        \o Closest available datarate at 10Hz.
    \row
        \o TiltSensor.Fast
        \o The sensor runs in fast mode.
        \o Closest available datarate at 20Hz.
    \endtable
*/
QSensor2Tilt::Speed QSensor2Tilt::speed()
{
    return _speed;
}

void QSensor2Tilt::setSpeed(const QSensor2Tilt::Speed val)
{
    if (_dataRate.keys().contains(val)){
        if (_dataRate.value(val) != _accel->dataRate()){
            _accel->setDataRate(_dataRate.value(val));
            emit speedChanged();
        }
    }
    _speed = val;
}

/*!
    \qmlproperty bool QtSensors5::QSensor2Tilt::enabled
    This property can be used to activate or deactivate the sensor.
*/
bool QSensor2Tilt::enabled()
{
    return _accel->isActive();
}

void QSensor2Tilt::setEnabled(const bool val)
{
    bool active = enabled();
    if (active != val){
        if (val){
            bool readDatarateMap = !_accel->isConnectedToBackend();
            bool ret = _accel->start();
            if (!ret)
                qWarning() << "couldn't start the sensor.";
            else if (readDatarateMap){
                 createRunModeDataRateMap();
                 setSpeed(_speed);
             }
        }
        else
            _accel->stop();
        emit enabledChanged();
    }
}

/*!
    \target unit_property
    \qmlproperty enumeration QtSensors5::TiltSensor::unit
    Returns the unit of the rotation which can be one of:
    \table
    \row
        \o TiltSensor.Radians
        \o The unit of the rotation angle is radians.
    \row
        \o TiltSensor.Degrees
        \o The unit of the rotation angle is degrees.
    \endtable
*/
QSensor2Tilt::Unit QSensor2Tilt::unit()
{
    return _unit;
}

void QSensor2Tilt::setUnit(const QSensor2Tilt::Unit val)
{
    if (_unit != val){
        _unit = val;
        emit unitChanged();
    }
}


/*!
    \qmlproperty qreal QtSensors5::TiltSensor::yRotation
    Holds the rotation arround the y axis.

    \table
    \row
        \o
        \image YAngle.gif
        \o
        \image YAngleNegative.gif
    \endtable
*/
qreal QSensor2Tilt::yRotation()
{
    if (_unit == QSensor2Tilt::Degrees)
        return _yRotation * 180 / M_PI;

    return _yRotation;
}

/*!
    \qmlproperty qreal QtSensors5::TiltSensor::xRotation
    Holds the rotation arround the x axis.
    \table
    \row
        \o
        \image XAngle.gif
        \o
        \image XAngleNegative.gif
    \endtable
*/
qreal QSensor2Tilt::xRotation()
{
    if (_unit == QSensor2Tilt::Degrees)
        return _xRotation * 180 / M_PI;

    return _xRotation;
}

/*
  Angle between Ground and X
                |            Ax           |
  pitch = arctan| ----------------------- |
                |  sqrt(Ay * Ay + Az * Az)|
*/
inline qreal calcPitch(double Ax, double Ay, double Az)
{
    return (float)-atan2(Ax, sqrt(Ay * Ay + Az * Az));
}

/*
  Angle between Ground and Y
                |            Ay           |
   roll = arctan| ----------------------- |
                |  sqrt(Ax * Ax + Az * Az)|
*/
inline qreal calcRoll(double Ax, double Ay, double Az)
{
    return (float)atan2(Ay, (sqrt(Ax * Ax + Az * Az)));
}

/*!
    \qmlproperty qreal QtSensors5::TiltSensor::accuracy
    This property contains the accuracy (in degrees) in which the rotation should be measured.
    This can be used to minimize signal emiting and therefore saving of performance.
    Default value is 1 degree.
*/
/*!
    \qmlsignal QtSensors5::TiltSensor::tiltChanged(qreal deltaX, qreal deltaY)
    This signal is emitted whenever the change from at leat one of the rotation values was higher than the accuracy.
    The angle value is based on the specified unit (Degree or Radian).

    \sa {QtSensors5::TiltSensor::unit} {TiltSensor.unit}
*/
qreal QSensor2Tilt::accuracy()
{
    //return in degree
    return 180 * _radAccuracy / M_PI;
}

void QSensor2Tilt::setAccuracy(qreal val)
{
    //save in rad to save convertion calc in filter function
    _radAccuracy = M_PI * val / 180;
}

/*!
    \qmlproperty void QtSensors5::TiltSensor::calibrate
    The call of this function calibrates the tilt from x and y to the current position.
*/
void QSensor2Tilt::calibrate()
{
    _calibratedPitch = _pitch;
    _calibratedRoll = _roll;
#ifdef LOGCALIBRATION
    qDebug() << "--------- calibrate --------";
    qDebug() << "_calibratedPitch: " << _calibratedPitch;
    qDebug() << "_calibratedRoll: " << _calibratedRoll;
    qDebug() << "----------------------------";
#endif
}

/*!
    \qmlproperty qreal QtSensors5::TiltSensor::settings
    This property contains the setting of the current state.
    It can be used for saving and reloading previously saved calibrations.
*/
QByteArray QSensor2Tilt::settings() const
{
    QByteArray arr;
    arr.append(QString::number((double)_calibratedPitch));
    arr.append(";");
    arr.append(QString::number((double)_calibratedRoll));
    return arr;
}

void QSensor2Tilt::setSettings(const QByteArray val)
{
    QString str(val);
    if (str.indexOf(";") > 0){
        QStringList strlist = str.split(";");
        if (strlist.length() == 2){
            _calibratedPitch = strlist.at(0).toDouble();
            _calibratedRoll = strlist.at(1).toDouble();
        }
    }
}

bool QSensor2Tilt::filter(QAccelerometerReading* reading)
{
    /*
      z  y
      | /
      |/___ x
    */

    qreal ax = reading->x();
    qreal ay = reading->y();
    qreal az = reading->z();
#ifdef LOGCALIBRATION
    qDebug() << "------------ new value -----------";
    qDebug() << "old _pitch: " << _pitch;
    qDebug() << "old _roll: " << _roll;
    qDebug() << "_calibratedPitch: " << _calibratedPitch;
    qDebug() << "_calibratedRoll: " << _calibratedRoll;
#endif
    _pitch = calcPitch(ax, ay, az);
    _roll  = calcRoll (ax, ay, az);
#ifdef LOGCALIBRATION
    qDebug() << "_pitch: " << _pitch;
    qDebug() << "_roll: " << _roll;
#endif
    qreal xrot = _roll - _calibratedRoll;
    qreal yrot = _pitch - _calibratedPitch;
    //get angle beteen 0 and 180 or 0 -180
    qreal aG = 1 * sin(xrot);
    qreal aK = 1 * cos(xrot);
    xrot = atan2(aG, aK);
    if (xrot > M_PI_2)
        xrot = M_PI - xrot;
    else if (xrot < -M_PI_2)
        xrot = -(M_PI + xrot);
    aG = 1 * sin(yrot);
    aK = 1 * cos(yrot);
    yrot = atan2(aG, aK);
    if (yrot > M_PI_2)
        yrot = M_PI - yrot;
    else if (yrot < -M_PI_2)
        yrot = -(M_PI + yrot);


#ifdef LOGCALIBRATION
    qDebug() << "new xrot: " << xrot;
    qDebug() << "new yrot: " << yrot;
    qDebug() << "----------------------------------";
#endif
    qreal dxrot = xrot - _xRotation;
    qreal dyrot = yrot - _yRotation;
    if (dxrot < 0) dxrot = -dxrot;
    if (dyrot < 0) dyrot = -dyrot;

    bool change = false;
    if (dxrot >= _radAccuracy){
        _xRotation = xrot;
        emit xRotationChanged();
        change = true;
    }
    if (dyrot >= _radAccuracy){
        _yRotation = yrot;
        emit yRotationChanged();
        change = true;
    }
    if (change){
        if (_unit == QSensor2Tilt::Degrees)
            emit tiltChanged(dxrot * 180 / M_PI, dyrot * 180 / M_PI);
        else
            emit tiltChanged(dxrot, dyrot);
    }
    return false;
}

QT_END_NAMESPACE
