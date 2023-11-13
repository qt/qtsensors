// Copyright (C) 2016 Canonical, Ltd
// SPDX-License-Identifier: LicenseRef-Qt-Commercial
#ifndef QLIDSENSOR_P_H
#define QLIDSENSOR_P_H

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

#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QLidReadingPrivate
{
public:
    QLidReadingPrivate()
        : backLidClosed(false),frontLidClosed(false)
    {
    }

    bool backLidClosed;
    bool frontLidClosed;
};

QT_END_NAMESPACE

#endif
