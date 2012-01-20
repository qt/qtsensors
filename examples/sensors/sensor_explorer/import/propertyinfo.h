/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QPROPERTYINFO_H
#define QPROPERTYINFO_H

#include <QtDeclarative/qdeclarative.h>
#include <QtCore/QString>

QT_BEGIN_NAMESPACE

class QPropertyInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString typeName READ typeName CONSTANT)
    Q_PROPERTY(QString value READ value NOTIFY valueChanged)
    Q_PROPERTY(bool isWriteable READ isWriteable CONSTANT)

public:
    QPropertyInfo(QObject* parent = 0);
    QPropertyInfo(const QString& name, int index, bool writeable, const QString& typeName, const QString& value, QObject* parent=0);
    QString name();
    QString typeName();
    QString value();
    void setValue(const QString& value);
    int index();
    bool isWriteable();

Q_SIGNALS:
    void valueChanged();

private:
    int _index;
    bool _isWriteable;
    QString _name;
    QString _typeName;
    QString _value;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QPropertyInfo)

#endif // QPROPERTYINFO_H
