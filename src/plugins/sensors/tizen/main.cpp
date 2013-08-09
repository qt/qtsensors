/****************************************************************************
**
** Copyright (C) 2013 Tomasz Olszak.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qsensorplugin.h>
#include <qsensorbackend.h>
#include <qsensormanager.h>
#include "tizenaccelerometer.h"
#include "tizendeviceorientation.h"
#include "tizencompass.h"
#include "tizenlight.h"
#include "tizengravity.h"
#include "tizenmagnetometer.h"
#include "tizengyroscope.h"
#include "tizenproximity.h"

class TizenSensorPlugin : public QObject, public QSensorPluginInterface, public QSensorBackendFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qt-project.Qt.QSensorPluginInterface/1.0" FILE "plugin.json")
    Q_INTERFACES(QSensorPluginInterface)
public:
    void registerSensors()
    {
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_ACCELEROMETER)) {
            QSensorManager::registerBackend(QAccelerometer::type, TizenAccelerometer::id, this);
            QSensorManager::setDefaultBackend(QAccelerometer::type, TizenAccelerometer::id);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_DEVICE_ORIENTATION)) {
            QSensorManager::registerBackend(QRotationSensor::type, TizenDeviceOrientation::id, this);
            QSensorManager::setDefaultBackend(QRotationSensor::type, TizenDeviceOrientation::id);
            QSensorManager::registerBackend(QCompass::type, TizenCompass::id, this);
            QSensorManager::setDefaultBackend(QCompass::type, TizenCompass::id);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_LIGHT)) {
            QSensorManager::registerBackend(QLightSensor::type, TizenLight::id, this);
            QSensorManager::setDefaultBackend(QLightSensor::type, TizenLight::id);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_GRAVITY)) {
            QSensorManager::registerBackend(QAccelerometer::type, TizenGravity::id, this);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_MAGNETIC)) {
            QSensorManager::registerBackend(QMagnetometer::type, TizenMagnetometer::id, this);
            QSensorManager::setDefaultBackend(QMagnetometer::type, TizenMagnetometer::id);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_GYROSCOPE)) {
            QSensorManager::registerBackend(QGyroscope::type, TizenGyroscope::id, this);
            QSensorManager::setDefaultBackend(QGyroscope::type, TizenGyroscope::id);
        }
        if (TizenSensorBase::isTizenSensorSupported(SENSOR_PROXIMITY)) {
            QSensorManager::registerBackend(QProximitySensor::type, TizenProximity::id, this);
            QSensorManager::setDefaultBackend(QProximitySensor::type, TizenProximity::id);
        }
    }

    QSensorBackend *createBackend(QSensor *sensor)
    {
        if (sensor->identifier() == TizenAccelerometer::id) {
            return new TizenAccelerometer(sensor);
        } else if (sensor->identifier() == TizenDeviceOrientation::id) {
            return new TizenDeviceOrientation(sensor);
        } else if (sensor->identifier() == TizenCompass::id) {
            return new TizenCompass(sensor);
        } else if (sensor->identifier() == TizenLight::id) {
            return new TizenLight(sensor);
        } else if (sensor->identifier() == TizenGravity::id) {
            return new TizenGravity(sensor);
        } else if (sensor->identifier() == TizenMagnetometer::id) {
            return new TizenMagnetometer(sensor);
        } else if (sensor->identifier() == TizenGyroscope::id) {
            return new TizenGyroscope(sensor);
        } else if (sensor->identifier() == TizenProximity::id) {
            return new TizenProximity(sensor);
        }
        return 0;
    }
};

#include "main.moc"
