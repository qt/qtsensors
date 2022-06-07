// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QDir>
#include <QLibraryInfo>

#include <QtCore/private/qfactoryloader_p.h>

#include "qsensorgesturerecognizer.h"
#include "qsensorgesturemanagerprivate_p.h"
#include "qsensorgestureplugininterface.h"

Q_GLOBAL_STATIC(QSensorGestureManagerPrivate, sensorGestureManagerPrivate)

QT_BEGIN_NAMESPACE

QSensorGestureManagerPrivate::QSensorGestureManagerPrivate(QObject *parent) :
    QObject(parent)
{
    loader = new QFactoryLoader("org.qt-project.QSensorGesturePluginInterface", QLatin1String("/sensorgestures"));
    loadPlugins();
}

QSensorGestureManagerPrivate::~QSensorGestureManagerPrivate()
{
//    qDeleteAll(registeredSensorGestures);
//    delete loader;
}


 void QSensorGestureManagerPrivate::initPlugin(QObject *plugin)
{
    if (QSensorGesturePluginInterface *pInterface
            = qobject_cast<QSensorGesturePluginInterface *>(plugin)) {
        for (const QString& id : pInterface->supportedIds()) {
            if (!knownIds.contains(id))
                knownIds.append(id);
            else
                qWarning() << id <<"from the plugin" << pInterface->name() << "is already known.";
        }
        plugins << plugin;
    } else {
        qWarning() << "Could not load "<< plugin;
    }
}


/*!
  Internal
  Loads the sensorgesture plugins.
  */
void QSensorGestureManagerPrivate::loadPlugins()
{
    for (QObject *plugin : QPluginLoader::staticInstances())
        initPlugin(plugin);

    QList<QPluginParsedMetaData> meta = loader->metaData();
    for (int i = 0; i < meta.count(); i++) {
        QObject *plugin = loader->instance(i);
        initPlugin(plugin);
    }
}


/*!
  Internal
  creates the requested  recognizer.
  */

bool QSensorGestureManagerPrivate::loadRecognizer(const QString &recognizerId)
{
    //if no plugin is used return true if this is a registered recognizer

    if (registeredSensorGestures.contains(recognizerId))
        return true;

    for (int i= 0; i < plugins.count(); i++) {

        if (QSensorGesturePluginInterface *pInterface
                = qobject_cast<QSensorGesturePluginInterface *>(plugins.at(i))) {

            if (pInterface->supportedIds().contains(recognizerId)) {

                if (!registeredSensorGestures.contains(recognizerId)) {
                    //create these recognizers
                    QList <QSensorGestureRecognizer *> recognizers = pInterface->createRecognizers();

                    for (QSensorGestureRecognizer *recognizer : recognizers) {
                        if (registeredSensorGestures.contains(recognizer->id())) {
                           qWarning() << "Ignoring recognizer " << recognizer->id() << "from plugin" << pInterface->name() << "because it is already registered";
                            delete recognizer;
                        } else {
                            registeredSensorGestures.insert(recognizer->id(),recognizer);
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool QSensorGestureManagerPrivate::registerSensorGestureRecognizer(QSensorGestureRecognizer *recognizer)
{
    if (!knownIds.contains(recognizer->id())) {
        knownIds.append(recognizer->id());
        Q_ASSERT (!registeredSensorGestures.contains(recognizer->id()));
        recognizer->setParent(0);
        registeredSensorGestures.insert(recognizer->id(),recognizer);
        Q_EMIT newSensorGestureAvailable();

        return true;
    }
    return false;
}

QSensorGestureRecognizer *QSensorGestureManagerPrivate::sensorGestureRecognizer(const QString &id)
{
    QSensorGestureRecognizer *recognizer = 0;

    if (loadRecognizer(id)) {
        recognizer= registeredSensorGestures.value(id);
    }

    return recognizer;
}

QStringList QSensorGestureManagerPrivate::gestureIds()
{
    return knownIds;
}

QSensorGestureManagerPrivate * QSensorGestureManagerPrivate::instance()
{
    QSensorGestureManagerPrivate *priv = sensorGestureManagerPrivate();
    // It's safe to return 0 because this is checked when used
    //if (!priv) qFatal("Cannot return from QSensorGestureManagerPrivate::instance() because sensorGestureManagerPrivate() returned 0.");
    return priv;
}


QT_END_NAMESPACE
