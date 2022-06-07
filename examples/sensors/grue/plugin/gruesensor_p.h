// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GRUESENSOR_P_H
#define GRUESENSOR_P_H

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

class GrueSensorReadingPrivate
{
public:
    GrueSensorReadingPrivate()
        : chanceOfBeingEaten(-1)
    {
    }

    int chanceOfBeingEaten;
};

#endif
