// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTESTRECOGNIZERDUP_H
#define QTESTRECOGNIZERDUP_H

#include <qsensorgesturerecognizer.h>

class QTestRecognizerDup : public QSensorGestureRecognizer
{
    Q_OBJECT
    Q_PROPERTY(int thresholdTime READ thresholdTime WRITE setThresholdTime)

public:

    QTestRecognizerDup(QObject *parent = 0);
    ~QTestRecognizerDup();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

    int thresholdTime() const;
    void setThresholdTime(int msec);

Q_SIGNALS:
    void test2_dup();

private:
    int timerTimeout;
    QTimer *timer;
    bool active;

};

#endif // QTESTRECOGNIZERDUP_H
