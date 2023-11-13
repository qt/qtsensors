// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef WINRTCOMMON_H
#define WINRTCOMMON_H

#include <QtCore/QLoggingCategory>

namespace ABI {
    namespace Windows {
        namespace Foundation {
            struct DateTime;
        }
    }
}

QT_USE_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcWinRtSensors)

quint64 dateTimeToMsSinceEpoch(const ABI::Windows::Foundation::DateTime &dateTime);

#endif // WINRTCOMMON_H

