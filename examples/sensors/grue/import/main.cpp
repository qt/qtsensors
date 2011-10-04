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

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>

#include <gruesensor.h>

QT_BEGIN_NAMESPACE

class GrueSensorQmlImport : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        char const * const package = "Grue";
        if (QLatin1String(uri) != QLatin1String(package)) return;
        int major;
        int minor;

        // Register the 1.0 interfaces
        major = 1;
        minor = 0;
        qmlRegisterType           <GrueSensor       >(package, major, minor, "GrueSensor");
        qmlRegisterUncreatableType<GrueSensorReading>(package, major, minor, "GrueSensorReading", QLatin1String("Cannot create GrueSensorReading"));
    }
};

QT_END_NAMESPACE

#include "main.moc"

Q_EXPORT_PLUGIN2(gruesensorqmlimport, QT_PREPEND_NAMESPACE(GrueSensorQmlImport));

/*!
    \qmlclass GrueSensor GrueSensor
    \inqmlmodule Grue 1
    \brief The GrueSensor element reports on your chance of being eaten by a Grue.

    The GrueSensor element reports on your chance of being eaten by a Grue.

    This element wraps the GrueSensor class. Please see the documentation for
    GrueSensor for details.

    \sa {QtMobility.sensors QML Limitations}
*/

/*!
    \qmlproperty GrueSensorReading Grue1::GrueSensor::reading
    Holds the most recent Grue sensor reading.
    Please see QSensor::reading for information about this property.
*/

/*!
    \qmlsignal Grue1::GrueSensor::onReadingChanged()
    Called when the reading object changes.
    Please see QSensor::readingChanged() for information about this signal.
*/

/*!
    \qmlclass GrueSensorReading GrueSensorReading
    \inqmlmodule Grue 1
    \inherits QtMobility.sensors1::SensorReading
    \brief The GrueSensorReading element holds the most recent GrueSensor reading.

    The GrueSensorReading element holds the most recent GrueSensor reading.

    This element wraps the GrueSensorReading class. Please see the documentation for
    GrueSensorReading for details.

    This element cannot be directly created.
*/

/*!
    \qmlproperty qreal Grue1::GrueSensorReading::chanceOfBeingEaten
    Please see GrueSensorReading::chanceOfBeingEaten for information about this property.
*/

