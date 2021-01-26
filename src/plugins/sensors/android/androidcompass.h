/****************************************************************************
**
** Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef ANDROIDCOMPASS_H
#define ANDROIDCOMPASS_H

#include <QMutex>
#include <qcompass.h>

#include "sensoreventqueue.h"

class AndroidCompass : public ThreadSafeSensorBackend
{
    Q_OBJECT

public:
    AndroidCompass(QSensor *sensor, QObject *parent = nullptr);
    ~AndroidCompass() override;

    void start() override;
    void stop() override;
private:
    void readAllEvents();
    static int looperCallback(int /*fd*/, int /*events*/, void* data);

private:
    QCompassReading m_reading;
    const ASensor *m_accelerometer = nullptr;
    const ASensor *m_magnetometer = nullptr;
    ASensorEventQueue* m_sensorEventQueue = nullptr;
    ASensorVector m_accelerometerEvent;
    ASensorVector m_magneticEvent;
    QMutex m_sensorsMutex;
};

#endif // ANDROIDCOMPASS_H
