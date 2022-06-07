// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qsensorgestureplugininterface.h"

QT_BEGIN_NAMESPACE

/*!
    \class QSensorGesturePluginInterface
    \ingroup  sensorgestures_recognizer
    \inmodule QtSensors

    \brief The QSensorGesturePluginInterface class is the pure virtual interface to sensor gesture
    plugins.

    \since 5.1

    The QSensorGesturePluginInterface class is implemented in sensor gesture plugins to register
    sensor gesture recognizers with QSensorGestureManager.

    \sa {QtSensorGestures Plugins}
*/

/*!
  \fn QSensorGesturePluginInterface::createRecognizers()

  Called by the manager to create the recognizers.
  Plugins should initialize and register their recognizers using
  QSensorGestureManager::registerSensorGestureRecognizer() here.

  \sa QSensorGestureManager
*/

/*!
  \fn QSensorGesturePluginInterface::supportedIds() const

  Returns a list of the recognizer Id's that this plugin supports.
  */


/*!
  \fn QSensorGesturePluginInterface::name() const

  Returns this plugins name.
  */

/*!
    Construct the QSensorGesturePluginInterface.
*/
QSensorGesturePluginInterface::QSensorGesturePluginInterface()
{
}

/*!
    Destroy the QSensorGesturePluginInterface.
*/
QSensorGesturePluginInterface::~QSensorGesturePluginInterface()
{
}

QT_END_NAMESPACE
