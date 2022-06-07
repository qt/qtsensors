// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QMLSENSORGESTURE_P_H
#define QMLSENSORGESTURE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QQmlParserStatus>
#include <QtQml/qqml.h>
#include <QStringList>

#include "qsensorsquickglobal_p.h"

QT_BEGIN_NAMESPACE

class QSensorGesture;
class QSensorGestureManager;

class Q_SENSORSQUICK_PRIVATE_EXPORT QmlSensorGesture : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QStringList availableGestures READ availableGestures NOTIFY availableGesturesChanged)
    Q_PROPERTY(QStringList gestures READ gestures WRITE setGestures NOTIFY gesturesChanged)
    Q_PROPERTY(QStringList validGestures READ validGestures NOTIFY validGesturesChanged)
    Q_PROPERTY(QStringList invalidGestures READ invalidGestures NOTIFY invalidGesturesChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_INTERFACES(QQmlParserStatus)
    QML_NAMED_ELEMENT(SensorGesture)
    QML_ADDED_IN_VERSION(5,0)

public:
    explicit QmlSensorGesture(QObject* parent = 0);
    ~QmlSensorGesture();
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void detected(const QString &gesture);
    void availableGesturesChanged();
    void gesturesChanged();
    void validGesturesChanged();
    void invalidGesturesChanged();
    void enabledChanged();

public:
    QStringList availableGestures();
    QStringList gestures() const;
    void setGestures(const QStringList& value);
    bool enabled() const;
    void setEnabled(bool value);
    QStringList validGestures() const;
    QStringList invalidGestures() const;

private:
    void deleteGesture();
    void createGesture();

private:
    QStringList gestureIds;
    bool isEnabled;
    bool initDone;
    QStringList gestureList;

    QSensorGesture* sensorGesture;
    QSensorGestureManager* sensorGestureManager;
};

QT_END_NAMESPACE

#endif
