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

#include "winrtcommon.h"

#include <windows.foundation.h>

QT_USE_NAMESPACE

Q_LOGGING_CATEGORY(lcWinRtSensors, "qt.sensors.winrt")

quint64 dateTimeToMsSinceEpoch(const ABI::Windows::Foundation::DateTime &dateTime)
{
    // Convert 100-ns units since 01-01-1601 to ms since 01-01-1970
    return dateTime.UniversalTime / 10000 - 11644473600000LL;
}
