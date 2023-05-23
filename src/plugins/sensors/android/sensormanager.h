// Copyright (C) 2021 The Qt Company Ltd.
// Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only
// Qt-Security score:significant reason:default

#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QtCore/qthread.h>
#include <QtCore/private/qlatch_p.h>
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
    QLatch m_waitForStart{1};
    QJniObject m_sensorManager;
};

#endif // SENSORMANAGER_H
