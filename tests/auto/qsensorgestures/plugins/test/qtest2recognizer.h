// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTEST2RECOGNIZER_H
#define QTEST2RECOGNIZER_H

#include <qsensorgesturerecognizer.h>

class QTest2Recognizer : public QSensorGestureRecognizer
{
    Q_OBJECT

public:
    QTest2Recognizer(QObject *parent = 0);
    ~QTest2Recognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

    int thresholdTime() const;
    void setThresholdTime(int msec);

Q_SIGNALS:
    void test2();
    void test3(bool);

private:
    int timerTimeout;
    QTimer *timer;
    bool active;
};


#endif // QTEST2RECOGNIZER_H
