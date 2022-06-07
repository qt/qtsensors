// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QObject>
#include <QString>
#include <QSensorGestureManager>

class MyObject : public QObject
{
    void create();
public slots:
    void gestureDetected(const QString &);
};

void MyObject::create()
{
//! [Receiving sensor gesture signals]

// Create a QSensorGestureManager
    QSensorGestureManager gestureManager;

// Get a list of known recognizers
    QStringList recognizersList = gestureManager.gestureIds();

// Create a QSensorGeture object for each of those gesture recognizers
        QSensorGesture *gesture = new QSensorGesture( gestureManager.gestureIds(), this);
// Connect the known signals up.
        connect(gesture, SIGNAL(detected(QString)), this, SLOT(gestureDetected(QString)));
//! [Receiving sensor gesture signals]
}

void MyObject::gestureDetected(const QString &gesture)
{
    Q_UNUSED(gesture);
}

