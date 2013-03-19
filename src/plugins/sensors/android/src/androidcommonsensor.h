/****************************************************************************
**
** Copyright (C) 2013 BogDan Vatra <bogdan@kde.org>
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

#ifndef ANDROIDCOMMONSENSOR_H
#define ANDROIDCOMMONSENSOR_H

#include <qsensorbackend.h>
#include <qsensor.h>
#include "androidjnisensors.h"

template <typename ReaderType>
class AndroidCommonSensor : public QSensorBackend, protected AndroidSensors::AndroidSensorsListenerInterface
{
public:
    AndroidCommonSensor(AndroidSensors::AndroidSensorType type, QSensor *sensor) : QSensorBackend(sensor)
    {
        setDescription(AndroidSensors::sensorDescription(type));
        setReading<ReaderType>(&m_reader);
        m_type = type;
        m_isStarted = false;
    }

    virtual ~AndroidCommonSensor()
    {
        if (m_isStarted)
            stop();
    }
    virtual void start()
    {
        if (AndroidSensors::registerListener(m_type, this, sensor()->dataRate()))
            m_isStarted = true;
    }

    virtual void stop()
    {
        if (m_isStarted) {
            m_isStarted = false;
            AndroidSensors::unregisterListener(m_type, this);
        }
    }

protected:
    ReaderType m_reader;

private:
    AndroidSensors::AndroidSensorType m_type;
    bool m_isStarted;
};

#endif // ANDROIDCOMMONSENSOR_H
