// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTESTRECOGNIZER_H
#define QTESTRECOGNIZER_H

#include <qsensorgesturerecognizer.h>

class QTestRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
    Q_PROPERTY(int thresholdTime READ thresholdTime WRITE setThresholdTime)

public:

    QTestRecognizer(QObject *parent = 0);
    ~QTestRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

    int thresholdTime() const;
    void setThresholdTime(int msec);

Q_SIGNALS:
    void tested();

private:
    int timerTimeout;
    QTimer *timer;
    bool active;

public slots:
    void timeout();
};

#endif // QTESTRECOGNIZER_H
