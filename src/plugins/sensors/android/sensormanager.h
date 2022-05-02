/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QtCore/qthread.h>
#include <QtCore/qsemaphore.h>
#include <QtCore/qmutex.h>
#include <QtCore/qwaitcondition.h>
#include <QtCore/qjniobject.h>

#include <android/sensor.h>

class SensorManager : public QThread
{
public:
    ~SensorManager() override;
    static QSharedPointer<SensorManager> &instance();
    ALooper *looper() const;
    ASensorManager *manager() const;

    QJniObject javaSensor(const ASensor *sensor) const;
    QString description(const ASensor *sensor) const;
    double getMaximumRange(const ASensor *sensor) const;

private:
    SensorManager();
    // QThread interface
    void run() override;

private:
    QAtomicInt m_quit{0};
    ALooper *m_looper = nullptr;
    QSemaphore m_waitForStart;
    QJniObject m_sensorManager;
};

#endif // SENSORMANAGER_H
