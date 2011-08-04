/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "qsensorpluginloader_p.h"
#include <QtCore/qcoreapplication.h>
#include <QtCore/qdir.h>
#include <QtCore/qdebug.h>

#include "qsensorplugin.h"
#include "qmobilitypluginsearch.h"

QT_BEGIN_NAMESPACE

QSensorPluginLoader::QSensorPluginLoader()
{
    load();
}

QSensorPluginLoader::~QSensorPluginLoader()
{
    Q_FOREACH (QPluginLoader *loader, m_loaders) {
        bool ok = loader->unload();
        if (!ok) qWarning() << "Cannot unload" << loader->fileName();
        delete loader;
    }
}

QList<QObject*> QSensorPluginLoader::plugins() const
{
    return m_plugins;
}

void QSensorPluginLoader::load()
{
    if (!m_plugins.isEmpty())
        return;

    QStringList plugins = mobilityPlugins(QLatin1String("sensors"));
    bool reportErrors = (qgetenv("QT_DEBUG_PLUGINS") == "1");

    /* Now discover the dynamic plugins */
    for (int i = 0; i < plugins.count(); i++) {
        QPluginLoader *loader = new QPluginLoader(plugins.at(i));

        QObject *o = loader->instance();
        if (o != 0) {
            QSensorPluginInterface *p = qobject_cast<QSensorPluginInterface*>(o);
            if (p != 0) {
                m_plugins << o;
                m_loaders << loader;
            } else {
                if (reportErrors) {
                    qWarning() << plugins.at(i) << "is not a QSensorPluginInterface";
                }
                loader->unload();
                delete loader;
            }

            continue;
        } else {
            if (reportErrors) {
                qWarning() << loader->errorString();
            }
        }
        delete o;
        loader->unload();
        delete loader;
    }
}

QT_END_NAMESPACE

