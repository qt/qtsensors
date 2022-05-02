/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

