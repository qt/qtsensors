/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
** Contact: http://www.qt-project.org/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbguihelper.h"

#include <QtCore/QAbstractEventDispatcher>
#include <QtCore/QCoreApplication>
#include <bps/navigator.h>

BbGuiHelper::BbGuiHelper(QObject *parent)
    : QObject(parent),
      m_currentOrientation(0),
      m_applicationActive(true)
{
    // There is no API to get the current orientation or application active state at the moment.
    // Therefore, we assume the application is active when this is called, and that the inital
    // orientation that is set in the environment variable hasn't changed yet.
    // These assumptions don't always hold, but it is the best we got so far.
    // The navigator will at least inform us about updates.
    const QByteArray orientationText = qgetenv("ORIENTATION");
    if (!orientationText.isEmpty())
        m_currentOrientation = orientationText.toInt();

    QCoreApplication::eventDispatcher()->installNativeEventFilter(this);
}

BbGuiHelper::~BbGuiHelper()
{
    QCoreApplication::eventDispatcher()->removeNativeEventFilter(this);
}

int BbGuiHelper::currentOrientation() const
{
    return m_currentOrientation;
}

bool BbGuiHelper::applicationActive() const
{
    return m_applicationActive;
}

bool BbGuiHelper::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(result);
    Q_UNUSED(eventType);

    bps_event_t * const event = static_cast<bps_event_t *>(message);
    if (event && bps_event_get_domain(event) == navigator_get_domain()) {
        const int code = bps_event_get_code(event);
        if (code == NAVIGATOR_ORIENTATION) {
            const int newOrientation = navigator_event_get_orientation_angle(event);
            if (newOrientation != m_currentOrientation) {
                m_currentOrientation = newOrientation;
                emit orientationChanged();
            }
        } else if (code == NAVIGATOR_WINDOW_STATE) {
            const bool appActive =
                    (navigator_event_get_window_state(event) == NAVIGATOR_WINDOW_FULLSCREEN);
            if (m_applicationActive != appActive) {
                m_applicationActive = appActive;
                emit applicationActiveChanged();
            }
        }
    }

    return false;
}
