/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtPositioning module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <functional>
#include <windows.system.h>

#include <windows.devices.sensors.h>
#include <windows.foundation.h>
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Devices::Sensors;

typedef ITypedEventHandler<Accelerometer *, AccelerometerReadingChangedEventArgs *> AccelerometerReadingHandler;

int main(int, char**)
{
    HStringReference classId(RuntimeClass_Windows_Devices_Sensors_Accelerometer);
    ComPtr<IAccelerometer> sensor;
    ComPtr<IAccelerometerStatics> factory;
    HRESULT hr = RoGetActivationFactory(classId.Get(), IID_PPV_ARGS(&factory));
    hr = factory->GetDefault(&sensor);
    return 0;
}
