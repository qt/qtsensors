/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
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
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qsensorplugin.h"

/*!
    \class QSensorPluginInterface
    \ingroup sensors_backend
    \inmodule QtSensors
    \brief The QSensorPluginInterface class is the pure virtual interface to sensor plugins.

    The QSensorPluginInterface class is implemented in sensor plugins to register sensor
    backends with QSensorManager.

    \sa {Creating a sensor plugin}
*/

/*!
    \fn QSensorPluginInterface::~QSensorPluginInterface()
    \internal
*/

/*!
    \fn QStringList QSensorPluginInterface::keys() const

    Returns a stringlist with one entry that contains a unique name for this plugin.
    Required as an artifact of the factory loader.
*/

/*!
    \fn QSensorPluginInterface::registerSensors()

    This function is called when the plugin is loaded. The plugin should register
    sensor backends by calling QSensorManager::registerBackend(). Any backends
    that utilise other sensors should be registered in the
    QSensorPluginInterface::sensorsChanged() method instead.

    \sa {Creating a sensor plugin}
*/

/*!
    \class QSensorChangesInterface
    \ingroup sensors_backend
    \inmodule QtSensors
    \brief The QSensorChangesInterface class is the pure virtual interface to sensor plugins.

    The QSensorChangesInterface class is implemented in sensor plugins to receive notification
    that registered sensor backends have changed.

    \sa {Creating a sensor plugin}
*/

/*!
    \fn QSensorChangesInterface::~QSensorChangesInterface()
    \internal
*/
/*!
    \fn QSensorChangesInterface::sensorsChanged()

    This function is called when the registered backends have changed.
    Any backends that depend on the presence of other sensors should be
    registered or unregistered in here.

    \sa {Creating a sensor plugin}
*/
