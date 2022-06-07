// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef QCOUNTERGESTURERECOGNIZER_H
#define QCOUNTERGESTURERECOGNIZER_H

#include <QDebug>
#include <QtCore/QTimer>
#include <qsensorgesturerecognizer.h>

class QCounterGestureRecognizer : public QSensorGestureRecognizer
{
    Q_OBJECT
public:

    QCounterGestureRecognizer(QObject *parent = 0);
    ~QCounterGestureRecognizer();

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

#endif // QCOUNTERGESTURERECOGNIZER_H
