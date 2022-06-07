// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qsensorgesturemanager.h"
#include "qsensorgesturemanagerprivate_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QSensorGestureManager
    \ingroup sensorgestures_main
    \inmodule QtSensors
    \since 5.1

    \brief The QSensorGestureManager class manages sensor gestures, registers and creates sensor gesture plugins.

    Sensor Gesture plugins register their recognizers using the registerSensorGestureRecognizer() function.

    \snippet sensorgestures/creating.cpp Receiving sensor gesture signals
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
    QSensorGestureManagerPrivate *d = QSensorGestureManagerPrivate::instance();
    if (!d) return; // hardly likely but just in case...
    connect(d,SIGNAL(newSensorGestureAvailable()),
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
     QSensorGestureManagerPrivate *d = QSensorGestureManagerPrivate::instance();
     if (!d) { // hardly likely but just in case...
         delete recognizer;
         return false;
     }
     bool ok = d->registerSensorGestureRecognizer(recognizer);
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
      QSensorGestureManagerPrivate *d = QSensorGestureManagerPrivate::instance();
      if (!d) return QStringList(); // hardly likely but just in case...
      return d->gestureIds();
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
    QSensorGestureManagerPrivate *d = QSensorGestureManagerPrivate::instance();
    if (!d) return 0; // hardly likely but just in case...
    return d->sensorGestureRecognizer(id);
}

QT_END_NAMESPACE
