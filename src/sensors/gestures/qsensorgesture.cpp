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

#include <QDir>
#include <QPluginLoader>
#include <QDebug>

#include "qsensorgesture.h"
#include "qsensorgesture_p.h"
#include "qsensorgesturemanager.h"

#include <private/qmetaobjectbuilder_p.h>

/*!
    \class QSensorGesture
    \ingroup sensorgestures_main
    \inmodule QtSensors
    \since 5.1

    \brief The QSensorGesture class represents one or more sensor gesture recognizers.

    In addition to the QSensorGesture::detected() signal, Sensor Gesture Recognizers can
    have their own specific signals, and may be discovered through
    QSensorGesture::gestureSignals().

    \b {Note that QSensorGesture uses a custom meta-object in order to provide
    recognizer-specific signals. This means it is not possible to sub-class
    QSensorGesture and use Q_OBJECT. Also qobject_cast<QSensorGesture*>(ptr) will
    not work.}

    \sa QSensorGestureRecognizer

    You may use QSensorGestureManager to obtain the systems known sensor gesture ids.

    \sa QSensorGestureManager
  */

/*!
  \fn void QSensorGesture::detected(QString)
  Signals when the gesture has been recognized.
  */

/*!
  Constructs the sensor gesture, and initializes the \a ids list of recognizers,
  with parent \a parent
  */
QSensorGesture::QSensorGesture(const QStringList &ids, QObject *parent) :
    QObject(parent)
{
    d_ptr = new QSensorGesturePrivate();
    for (const QString &id : ids) {
        QSensorGestureRecognizer * rec = QSensorGestureManager::sensorGestureRecognizer(id);
        if (rec != 0) {
            d_ptr->m_sensorRecognizers.append(rec);
            d_ptr->availableIds.append(id);
        } else {
            d_ptr->invalidIds.append(id);
            //add to not available things
        }
    }

    d_ptr->meta = 0;

    QMetaObjectBuilder builder;
    builder.setSuperClass(&QObject::staticMetaObject);
    builder.setClassName("QSensorGesture");

    for (QSensorGestureRecognizer *recognizer : d_ptr->m_sensorRecognizers) {
        for (const QString &gesture : recognizer->gestureSignals()) {
            QMetaMethodBuilder b =  builder.addSignal(gesture.toLatin1());
            if (!d_ptr->localGestureSignals.contains(QLatin1String(b.signature())))
                d_ptr->localGestureSignals.append(QLatin1String(b.signature()));
        }
        recognizer->createBackend();
    }
    d_ptr->meta = builder.toMetaObject();

    if (d_ptr->m_sensorRecognizers.count() > 0) {
        d_ptr->valid = true;
    }
}

/*!
  Destroy the QSensorGesture
  */
QSensorGesture::~QSensorGesture()
{
    stopDetection();
    if (d_ptr->meta)
        free(d_ptr->meta);
    delete d_ptr;
}

/*!
    Returns the gesture recognizer ids that were found.
  */
QStringList QSensorGesture::validIds() const
{
    return d_ptr->availableIds;
}

/*!
   Returns the gesture recognizer ids that were not found.
  */
QStringList QSensorGesture::invalidIds() const
{
    return d_ptr->invalidIds;
}

/*!
  Starts the gesture detection routines in the recognizer.
  */
void QSensorGesture::startDetection()
{
    if (d_ptr->m_sensorRecognizers.count() < 1)
        return;
    if (d_ptr->isActive)
        return;

    for (QSensorGestureRecognizer *recognizer : d_ptr->m_sensorRecognizers) {

        Q_ASSERT(recognizer !=0);

        connect(recognizer,SIGNAL(detected(QString)),
                this,SIGNAL(detected(QString)),Qt::UniqueConnection);

        //connect recognizer signals
        for (QString method : recognizer->gestureSignals()) {
            method.prepend(QLatin1String("2"));
            connect(recognizer, method.toLatin1(),
                    this, method.toLatin1(), Qt::UniqueConnection);
        }

        recognizer->startBackend();
    }
    d_ptr->isActive = true;
}

/*!
  Stops the gesture detection routines.
  */
void QSensorGesture::stopDetection()
{
    if (d_ptr->m_sensorRecognizers.count() < 1)
        return;

    if (!d_ptr->isActive)
        return;

    for (QSensorGestureRecognizer *recognizer : d_ptr->m_sensorRecognizers) {
        disconnect(recognizer,SIGNAL(detected(QString)),
                   this,SIGNAL(detected(QString)));
        //disconnect recognizer signals
        for (QString method : recognizer->gestureSignals()) {
            method.prepend(QLatin1String("2"));
            disconnect(recognizer, method.toLatin1(),
                       this, method.toLatin1());
        }

        recognizer->stopBackend();
    }
    d_ptr->isActive = false;
}

/*!
  Returns all the possible gestures signals that may be emitted.
  */
QStringList QSensorGesture::gestureSignals() const
{
    if (d_ptr->m_sensorRecognizers.count() > 0) {
        return  d_ptr->localGestureSignals;
    }
    return QStringList();
}

/*!
  Returns whether this gesture is active or not.
  */

bool QSensorGesture::isActive()
{
    return d_ptr->isActive;
}

/*!
  \internal
*/
const QMetaObject* QSensorGesture::metaObject() const
{
    return d_ptr->meta;
}
/*!
  \internal
*/
int QSensorGesture::qt_metacall(QMetaObject::Call c, int id, void **a)
{
    id = QObject::qt_metacall(c, id, a);

    if (id < 0 || !d_ptr->meta)
        return id;

    QMetaObject::activate(this, d_ptr->meta, id, a);
    return id;
}

QSensorGesturePrivate::QSensorGesturePrivate(QObject *parent)
    : QObject(parent),isActive(0), valid(0)
{
}

QSensorGesturePrivate::~QSensorGesturePrivate()
{

}
