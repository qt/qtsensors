/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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

#include "qsensorgesturemanager.h"
#include "qsensorgesturemanagerprivate_p.h"

Q_GLOBAL_STATIC(QSensorGestureManagerPrivate, sensorGestureManagerPrivate)

QT_BEGIN_NAMESPACE

/*!
  \class QSensorGestureManager
  \ingroup sensorgestures_main
  \inmodule QtSensors

  \brief The QSensorGestureManager class manages sensor gestures, registers and creates sensor gesture plugins.

   Sensor Gesture plugins register their recognizers using the registerSensorGestureRecognizer() function.

    \snippet snippets/sensorgestures/creating.cpp Receiving sensor gesture signals

  */

/*!
  \fn QSensorGestureManager::newSensorGestureAvailable()
  Signals when a new sensor gesture becomes available for use.
  */

/*!
  Constructs the QSensorGestureManager as a child of \a parent
  */
QSensorGestureManager::QSensorGestureManager(QObject *parent)
    : QObject(parent)
{
    connect(sensorGestureManagerPrivate(),SIGNAL(newSensorGestureAvailable()),
            this,SIGNAL(newSensorGestureAvailable()));
}

/*!
    Destroy the QSensorGestureManager
*/
QSensorGestureManager::~QSensorGestureManager()
{
}

/*!
  Registers the sensor recognizer \a recognizer for use.
  QSensorGestureManager retains ownership of the recognizer object.
  Returns true unless the gesture has already been registered, in
  which case the object is deleted.

  */

 bool QSensorGestureManager::registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer)
 {
     bool ok = sensorGestureManagerPrivate()->registerSensorGestureRecognizer(recognizer);
     if (!ok)
         delete recognizer;

     return ok;
 }


 /*!
   Returns the list of the currently registered gestures.
   Includes all the standard built-ins as well as available plugins.
   */
  QStringList QSensorGestureManager::gestureIds() const
 {
      return sensorGestureManagerPrivate()->gestureIds();
 }

  /*!
    Returns the list of all the gesture signals for the registered \a gestureId gesture recognizer id.
    */
  QStringList QSensorGestureManager::recognizerSignals(const QString &gestureId) const
  {
      QSensorGestureRecognizer *recognizer = sensorGestureRecognizer(gestureId);
      if (recognizer != 0)
          return recognizer->gestureSignals();
      else
          return QStringList();
  }

/*!
  Returns the sensor gesture object for the recognizer \a id.
  */
QSensorGestureRecognizer *QSensorGestureManager::sensorGestureRecognizer(const QString &id)
{
    return sensorGestureManagerPrivate()->sensorGestureRecognizer(id);
}

QT_END_NAMESPACE
