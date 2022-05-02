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

#include "qsensorplugin.h"

QT_BEGIN_NAMESPACE

/*!
    \class QSensorPluginInterface
    \ingroup sensors_backend
    \inmodule QtSensors
    \since 5.1
    \brief The QSensorPluginInterface class is the pure virtual interface to sensor plugins.

    The QSensorPluginInterface class is implemented in sensor plugins to register sensor
    backends with QSensorManager.

    \sa {Creating a sensor plugin}
*/

/*!
    \internal
*/
QSensorPluginInterface::~QSensorPluginInterface()
{
}

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
    \since 5.1
    \brief The QSensorChangesInterface class is the pure virtual interface to sensor plugins.

    The QSensorChangesInterface class is implemented in sensor plugins to receive notification
    that registered sensor backends have changed.

    \sa {Creating a sensor plugin}
*/

/*!
    \internal
*/
QSensorChangesInterface::~QSensorChangesInterface()
{
}

/*!
    \fn QSensorChangesInterface::sensorsChanged()

    This function is called when the registered backends have changed.
    Any backends that depend on the presence of other sensors should be
    registered or unregistered in here.

    \sa {Creating a sensor plugin}
*/

QT_END_NAMESPACE
