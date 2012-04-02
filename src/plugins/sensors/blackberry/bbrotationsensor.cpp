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

#include "bbutil.h"
#include <QtCore/qmath.h>

BbRotationSensor::BbRotationSensor(QSensor *sensor)
    : BbSensorBackend<QRotationReading>(devicePath(), SENSOR_TYPE_ROTATION_MATRIX, sensor)
{
    setDescription(QLatin1String("Device rotation in degrees"));
}

QString BbRotationSensor::devicePath()
{
    return QLatin1String("/dev/sensor/rotMatrix");
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

static float getMatrixElement(const float matrix[3*3], int index0, int index1)
{
    return matrix[index0 * 3 + index1];
}

static void matrixToEulerZXY(const float matrix[3*3],
                             float &thetaX, float &thetaY, float& thetaZ)
{
    thetaX = asin( getMatrixElement(matrix, 2, 1));
    if ( thetaX < M_PI_2 ) {
        if ( thetaX > -M_PI_2 ) {
            thetaZ = atan2( -getMatrixElement(matrix, 0, 1),
                             getMatrixElement(matrix, 1, 1) );
            thetaY = atan2( -getMatrixElement(matrix, 2, 0),
                             getMatrixElement(matrix, 2, 2) );
        } else {
            // Not a unique solution
            thetaZ = -atan2( getMatrixElement(matrix, 0, 2),
                             getMatrixElement(matrix, 0, 0) );
            thetaY = 0.0;
        }
    } else {
        // Not a unique solution
        thetaZ = atan2( getMatrixElement(matrix, 0, 2),
                        getMatrixElement(matrix, 0, 0) );
        thetaY = 0.0;
    }
}

bool BbRotationSensor::updateReadingFromEvent(const sensor_event_t &event, QRotationReading *reading)
{
    // sensor_event_t has euler angles for a Z-Y'-X'' system, but the QtMobility API
    // uses Z-X'-Y''.
    // So extract the euler angles using the Z-X'-Y'' system from the matrix.
    float xRad, yRad, zRad;
    matrixToEulerZXY(event.rotation_matrix, xRad, yRad, zRad);
    reading->setX(radiansToDegrees(xRad));
    reading->setY(radiansToDegrees(yRad));
    reading->setZ(radiansToDegrees(zRad));
    return true;
}

qreal BbRotationSensor::convertValue(float bbValueInRad)
{
    return radiansToDegrees(bbValueInRad);
}
