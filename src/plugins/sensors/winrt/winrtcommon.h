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

