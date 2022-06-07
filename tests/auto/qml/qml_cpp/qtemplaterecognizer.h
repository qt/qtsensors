// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#ifndef QTEMPLATERECOGNIZER_H
#define QTEMPLATERECOGNIZER_H

#include <QDebug>
#include <QtCore/QTimer>
#include <qsensorgesturerecognizer.h>

class QTemplateGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:

    QTemplateGestureRecognizer(QObject *parent = 0);
    ~QTemplateGestureRecognizer();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

private slots:
    void timeout();

private:
    QTimer _timer;
};

class QTemplateGestureRecognizer1 : public QSensorGestureRecognizer
{
    Q_OBJECT
public:

    QTemplateGestureRecognizer1(QObject *parent = 0);
    ~QTemplateGestureRecognizer1();

    void create() override;

    QString id() const override;
    bool start() override;
    bool stop() override;
    bool isActive() override;

private slots:
    void timeout();

private:
    QTimer _timer;
};

#endif // QTEMPLATERECOGNIZER_H
