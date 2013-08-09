/****************************************************************************
**
** Copyright (C) 2013 Tomasz Olszak
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

#ifndef TIZENSENSORBASE_H
#define TIZENSENSORBASE_H
#include <qsensorbackend.h>
#include <qdebug.h>
#include <system/sensors.h>

#ifdef TIZEN_SENSORS_DEBUG
#define TIZENSENSORLOG() if (0); else qDebug()
#else
#define TIZENSENSORLOG() while (0) qDebug()
#endif

class TizenSensorBase : public QSensorBackend
{
    Q_OBJECT
public:
    explicit TizenSensorBase(QSensor * sensor, sensor_type_e sensorType, QObject *parent = 0);
    virtual ~TizenSensorBase();
    virtual void start() Q_DECL_OVERRIDE;
    virtual void stop() Q_DECL_OVERRIDE;
    static bool isTizenSensorSupported(sensor_type_e type);
    bool isSupported();
protected slots:
    virtual void onDataRateChanged();
protected:
    virtual sensor_h createSensor();
    virtual void destroySensor();
    static bool wasError(sensor_error_e result){ return result != SENSOR_ERROR_NONE;}
    static void printErrorMessage(QString prefix, sensor_error_e error);
    static QString sensorDescription(sensor_type_e type);
    sensor_h m_sensor;
    sensor_type_e m_sensorType;
    qint8 m_supported;
    QString m_sensorDescription;
};

#endif // TIZENSENSORBASE_H
