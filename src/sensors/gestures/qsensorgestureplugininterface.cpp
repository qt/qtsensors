/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

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
