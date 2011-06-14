/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "dummycommon.h"

#ifdef Q_OS_WINCE
#include <windows.h>
// WINCE has <time.h> but using clock() gives a link error because
// the function isn't actually implemented.
#else
#include <time.h>
#ifdef Q_OS_MAC
#include <mach/mach_time.h>
#endif
#endif

dummycommon::dummycommon(QSensor *sensor)
    : QSensorBackend(sensor)
    , m_timerid(0)
{
}

void dummycommon::start()
{
    if (m_timerid)
        return;

    int dataRate = sensor()->dataRate();
    if (dataRate == 0) {
        if (sensor()->availableDataRates().count())
            // Use the first available rate when -1 is chosen
            dataRate = sensor()->availableDataRates().first().first;
        else
            dataRate = 1;
    }

    int interval = 1000 / dataRate;

    if (interval)
        m_timerid = startTimer(interval);
}

void dummycommon::stop()
{
    if (m_timerid) {
        killTimer(m_timerid);
        m_timerid = 0;
    }
}

void dummycommon::timerEvent(QTimerEvent * /*event*/)
{
    poll();
}

#ifdef Q_OS_MAC
//taken from qelapsedtimer_mac.cpp
static mach_timebase_info_data_t info = {0,0};
static qint64 absoluteToNSecs(qint64 cpuTime)
{
    if (info.denom == 0)
        mach_timebase_info(&info);
    qint64 nsecs = cpuTime * info.numer / info.denom;
    return nsecs;
}
#endif

quint64 dummycommon::getTimestamp()
{
#ifdef Q_OS_WINCE
    // This implementation is based on code found here:
    // http://social.msdn.microsoft.com/Forums/en/vssmartdevicesnative/thread/74870c6c-76c5-454c-8533-812cfca585f8
    HANDLE currentThread = GetCurrentThread();
    FILETIME creationTime, exitTime, kernalTime, userTime;
    GetThreadTimes(currentThread, &creationTime, &exitTime, &kernalTime, &userTime);

    ULARGE_INTEGER uli;
    uli.LowPart = userTime.dwLowDateTime;
    uli.HighPart = userTime.dwHighDateTime;
    ULONGLONG systemTimeInMS = uli.QuadPart/10000;
    return static_cast<quint64>(systemTimeInMS);
#elif Q_OS_MAC
    uint64_t cpu_time = mach_absolute_time();
    uint64_t nsecs = absoluteToNSecs(cpu_time);

    quint64 result = (nsecs * 0.001); //scale to microseconds
    return result;
#else
    struct timespec tv;
    int ok;
    ok = clock_gettime(CLOCK_MONOTONIC, &tv);
    Q_ASSERT(ok == 0);

    quint64 result = (tv.tv_sec * 1000000ULL) + (tv.tv_nsec * 0.001); // scale to microseconds
    return result;
#endif
}

