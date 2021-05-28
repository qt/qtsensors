/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "sensormodels.h"
#include "qsensor.h"
#include "qorientationsensor.h"
#include <QtCore/QDebug>
#include <qsensor.h>
#include <QMetaObject>
#include <QMetaProperty>

QT_BEGIN_NAMESPACE

QByteArray rangelistToByteArray(const qrangelist& list)
{
    QStringList ranges;
    for (const qrange &r : list) {
        if (r.first == r.second)
            ranges << QString("%1 Hz").arg(r.first);
        else
            ranges << QString("%1-%2 Hz").arg(r.first).arg(r.second);
    }
    if (ranges.count() > 0)
        return ranges.join(", ").toLatin1();
    return "-";
}

QByteArray outputrangelistToByteArray(const qoutputrangelist& list)
{
    QStringList ranges;
    for (const qoutputrange &r : list) {
        ranges << QString("(%1, %2) += %3").arg(r.minimum).arg(r.maximum).arg(r.accuracy);
    }
    if (ranges.count() > 0)
        return ranges.join(", ").toLatin1();
    return "-";
}

AvailableSensorsModel::AvailableSensorsModel(QObject* parent) : QAbstractListModel(parent)
{
    // Some valuetypes do not convert nicely to presentable strings, add converters for them
    QMetaType::registerConverter<qrangelist, QByteArray>(rangelistToByteArray);
    QMetaType::registerConverter<qoutputrangelist, QByteArray>(outputrangelistToByteArray);

    // Populate the available sensors list
    loadSensors();
}

/*
    Load all available sensors and store them in a list.
*/
void AvailableSensorsModel::loadSensors()
{
    //! [0]
    beginResetModel();
    m_availableSensors.clear();

    for (const QByteArray &type : QSensor::sensorTypes()) {
        for (const QByteArray &identifier : QSensor::sensorsForType(type)) {
            QSensor* sensor = new QSensor(type, this);
            sensor->setIdentifier(identifier);
            // Don't put in sensors we can't connect to
            if (!sensor->connectToBackend())
                continue;
            m_availableSensors.append(sensor);
        }
    }
    endResetModel();
    //! [0]
}

int AvailableSensorsModel::rowCount(const QModelIndex&) const
{
    return m_availableSensors.count();
}

//! [1]
QVariant AvailableSensorsModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    return QVariant::fromValue<QSensor*>(m_availableSensors.at(index.row()));
}
//! [1]

QSensor* AvailableSensorsModel::get(int index) const
{
    if (index < 0 || index >= m_availableSensors.count())
        return nullptr;
    return m_availableSensors[index];
}

// -- SensorPropertyModel

static QSet<QByteArray> ignoredProperties = {"reading", "identifier", "active",
                                             "connectedToBackend", "busy"};

SensorPropertyModel::SensorPropertyModel(QObject* parent) : QAbstractTableModel(parent)
{
}

int SensorPropertyModel::rowCount(const QModelIndex&) const
{
    if (!m_sensor)
        return 0;
    return m_values.count();
}

int SensorPropertyModel::columnCount(const QModelIndex&) const
{
    return 2; // 2 = property name + value columns
}

QVariant SensorPropertyModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    return (index.column() == 0) ? std::get<0>(m_values.at(index.row()))
                                 : std::get<1>(m_values.at(index.row()));
}

void SensorPropertyModel::setSensor(QSensor *sensor)
{
    if (m_sensor == sensor)
        return;
    if (m_sensor)
        m_sensor->disconnect(this);
    m_sensor = sensor;

    beginResetModel();
    m_values.clear();
    if (m_sensor) {
        // Use metobject to read the available properties. This allows the model to support all
        // available sensors without knowing their properties in advance / compile-time.

        // 1. Read properties of the 'reading' object if available
        //! [2]
        int firstProperty = QSensorReading::staticMetaObject.propertyOffset();
        QSensorReading *reading = m_sensor->reading();
        if (reading) {
            const QMetaObject *mo = reading->metaObject();
            for (int i = firstProperty; i < mo->propertyCount(); ++i) {
                QByteArray name = mo->property(i).name();
                m_values.append(std::tuple<QByteArray, QByteArray>
                                (name, reading->property(name).toByteArray()));
            }
        }
        //! [2]

        // 2. Read properties of the 'sensor' object
        const QMetaObject *mo1 = m_sensor->metaObject();
        firstProperty = QSensorReading::staticMetaObject.propertyOffset();
        for (int i = firstProperty; i < mo1->propertyCount(); ++i) {
            QByteArray name = mo1->property(i).name();
            if (ignoredProperties.contains(name))
                continue;
            m_values.append(std::tuple<QByteArray, QByteArray>
                            (name, m_sensor->property(name).toByteArray()));
        }
        QObject::connect(m_sensor, &QSensor::readingChanged,
                         this, &SensorPropertyModel::onReadingChanged);
    }
    endResetModel();
    emit sensorChanged();
}

QSensor* SensorPropertyModel::sensor() const
{
    return m_sensor;
}

void SensorPropertyModel::onReadingChanged()
{
    QSensorReading *reading = m_sensor->reading();
    const QMetaObject *mo = reading->metaObject();
    int firstProperty = QSensorReading::staticMetaObject.propertyOffset();

    int valueMapIndex = 0;
    for (int i = firstProperty; i < mo->propertyCount(); ++i) {
        QByteArray name = mo->property(i).name();
        // Update the value and signal the change. Note: here we rely that the "reading"
        // properties are first on the m_values, and in same order as after the initial
        // population. This should be true as we access the static metabobject (dynamic
        // property changes shouldn't impact)
        m_values[valueMapIndex++] = std::tuple<QByteArray, QByteArray>
                (name, reading->property(name).toByteArray());
    }
    emit dataChanged(createIndex(0,1), createIndex(valueMapIndex,1), {Qt::DisplayRole});
}

QT_END_NAMESPACE
