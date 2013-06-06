/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSensors module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "sensorfwmagnetometer.h"
#include <QSensor>


char const * const SensorfwMagnetometer::id("sensorfw.magnetometer");
bool SensorfwMagnetometer::m_initDone = false;
const float SensorfwMagnetometer::NANO = 0.000000001;


SensorfwMagnetometer::SensorfwMagnetometer(QSensor *sensor)
    : SensorfwSensorBase(sensor)
{
    initSensor<MagnetometerSensorChannelInterface>(m_initDone);
    setDescription(QLatin1String("magnetic flux density in teslas (T)"));
    setRanges(NANO);
    setReading<QMagnetometerReading>(&m_reading);
    sensor->setDataRate(50);//set a default rate
}

void SensorfwMagnetometer::start()
{
    QMagnetometer *const magnetometer = qobject_cast<QMagnetometer *>(sensor());
    if (magnetometer)
        m_isGeoMagnetometer = magnetometer->returnGeoValues();
    SensorfwSensorBase::start();
}

void SensorfwMagnetometer::slotDataAvailable(const MagneticField& data)
{
    //nanoTeslas given, divide with 10^9 to get Teslas
    m_reading.setX( NANO * (m_isGeoMagnetometer?data.x():data.rx()));
    m_reading.setY( NANO * (m_isGeoMagnetometer?data.y():data.ry()));
    m_reading.setZ( NANO * (m_isGeoMagnetometer?data.z():data.rz()));
    m_reading.setCalibrationLevel(m_isGeoMagnetometer?((float) data.level()) / 3.0 :1);
    m_reading.setTimestamp(data.timestamp());
    newReadingAvailable();
}


void SensorfwMagnetometer::slotFrameAvailable(const QVector<MagneticField>& frame)
{
    for (int i=0, l=frame.size(); i<l; i++) {
        slotDataAvailable(frame.at(i));
    }
}

bool SensorfwMagnetometer::doConnect()
{
    if (m_bufferSize==1)
        return QObject::connect(m_sensorInterface, SIGNAL(dataAvailable(const MagneticField&)),
                                this, SLOT(slotDataAvailable(const MagneticField&)));
     return QObject::connect(m_sensorInterface, SIGNAL(frameAvailable(const QVector<MagneticField>& )),
                             this, SLOT(slotFrameAvailable(const QVector<MagneticField>& )));
}

QString SensorfwMagnetometer::sensorName() const
{
    return "magnetometersensor";
}

qreal SensorfwMagnetometer::correctionFactor() const
{
    return SensorfwMagnetometer::NANO;
}
