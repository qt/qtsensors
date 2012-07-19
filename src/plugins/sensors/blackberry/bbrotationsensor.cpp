/****************************************************************************
**
** Copyright (C) 2012 Research In Motion
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
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbrotationsensor.h"

#include "bbguihelper.h"
#include "bbutil.h"
#include <QtCore/qmath.h>

using namespace BbUtil;

BbRotationSensor::BbRotationSensor(QSensor *sensor)
    : BbSensorBackend<QRotationReading>(devicePath(), SENSOR_TYPE_ROTATION_MATRIX, sensor)
{
    setDescription(QLatin1String("Device rotation in degrees"));
    m_mappingMatrix[0] = m_mappingMatrix[2] = 1;
    m_mappingMatrix[1] = m_mappingMatrix[3] = 0;
}

QString BbRotationSensor::devicePath()
{
    return QLatin1String("/dev/sensor/rotMatrix");
}

void BbRotationSensor::setGuiHelper(BbGuiHelper *guiHelper)
{
    BbSensorBackend<QRotationReading>::setGuiHelper(guiHelper);
    connect(guiHelper, SIGNAL(orientationChanged()), this, SLOT(updateOrientation()));
    updateOrientation();
}

void BbRotationSensor::additionalDeviceInit()
{
    addOutputRange(-180, 180, 0 /* ? */);
}

bool BbRotationSensor::addDefaultRange()
{
    // The range we get from the OS service is only -1 to 1, which are the values of the matrix.
    // We need the values of the axes in degrees.
    return false;
}

static void remapMatrix(const float inputMatrix[3*3],
                        const float mappingMatrix[4],
                        float outputMatrix[3*3])
{
    int i,j,k;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) { //only goto 2 because last column stays unchanged

            outputMatrix[i*3+j] = 0;

            for (k = 0; k < 2; k++) { //only goto 2 because we know rotation matrix is zero in bottom row
                outputMatrix[i*3+j] += inputMatrix[i*3+k] * mappingMatrix[k*2+j];
            }
        }

        outputMatrix[i*3+2] = inputMatrix[i*3+2];
    }
}

bool BbRotationSensor::updateReadingFromEvent(const sensor_event_t &event, QRotationReading *reading)
{
    // sensor_event_t has euler angles for a Z-Y'-X'' system, but the QtMobility API
    // uses Z-X'-Y''.
    // So extract the euler angles using the Z-X'-Y'' system from the matrix.
    float xRad, yRad, zRad;

    if (isAutoAxisRemappingEnabled() && guiHelper()->currentOrientation() != 0) {
        float mappedRotationMatrix[3*3];
        remapMatrix(event.rotation_matrix, m_mappingMatrix, mappedRotationMatrix);
        matrixToEulerZXY(mappedRotationMatrix, xRad, yRad, zRad);
    } else {
        matrixToEulerZXY(event.rotation_matrix, xRad, yRad, zRad);
    }

    reading->setFromEuler(radiansToDegrees(xRad),
                          radiansToDegrees(yRad),
                          radiansToDegrees(zRad));

    return true;
}

qreal BbRotationSensor::convertValue(float bbValueInRad)
{
    return radiansToDegrees(bbValueInRad);
}

bool BbRotationSensor::isAutoAxisRemappingEnabled() const
{
    return sensor()->property("automaticAxisRemapping").toBool();
}

void BbRotationSensor::updateOrientation()
{
    // ### I can't really test this, the rotation matrix has too many glitches and drifts over time,
    // making any measurement quite hard
    const int rotationAngle = guiHelper()->currentOrientation();

    m_mappingMatrix[0] = cos(rotationAngle*M_PI/180);
    m_mappingMatrix[1] = sin(rotationAngle*M_PI/180);
    m_mappingMatrix[2] = -sin(rotationAngle*M_PI/180);
    m_mappingMatrix[3] = cos(rotationAngle*M_PI/180);
}
