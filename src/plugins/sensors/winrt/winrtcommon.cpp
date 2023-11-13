// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "winrtcommon.h"

#include <windows.foundation.h>

QT_USE_NAMESPACE

Q_LOGGING_CATEGORY(lcWinRtSensors, "qt.sensors.winrt")

quint64 dateTimeToMsSinceEpoch(const ABI::Windows::Foundation::DateTime &dateTime)
{
    // Convert 100-ns units since 01-01-1601 to ms since 01-01-1970
    return dateTime.UniversalTime / 10000 - 11644473600000LL;
}
