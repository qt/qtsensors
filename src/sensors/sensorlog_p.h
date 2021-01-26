/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#ifndef QSENSORLOG_P_H
#define QSENSORLOG_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

#ifdef ENABLE_RUNTIME_SENSORLOG

static bool logEnabled()
{
    static int state = -1;

    if (state == -1) {
        QByteArray sensorlog = qgetenv("SENSORLOG");
        if (sensorlog == "1")
            state = 1;
        else
            state = 0;
    }

    return state;
}

#define SENSORLOG() if (!logEnabled()); else qDebug()

#else

// Do nothing (compiles to almost nothing)
#define SENSORLOG() if (1); else qDebug()

#endif

QT_END_NAMESPACE

#endif

