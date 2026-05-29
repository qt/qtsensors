# Copyright (C) 2026 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## QOhosSensorPlugin Plugin:
#####################################################################

qt_find_package(NodeAddonApi MODULE)

qt_internal_add_plugin(QOhosSensorPlugin
    OUTPUT_NAME qtsensors_ohos
    PLUGIN_TYPE sensors
    EXCEPTIONS
    SOURCES
        main.cpp
        ohosaccelerometerbackend.cpp ohosaccelerometerbackend.h
        ohosgyroscopebackend.cpp ohosgyroscopebackend.h
        ohoslightsensorbackend.cpp ohoslightsensorbackend.h
        ohosmagnetometerbackend.cpp ohosmagnetometerbackend.h
        ohosrotationsensorbackend.cpp ohosrotationsensorbackend.h
        ohossensorbackendbase.h
        ohossensorsmanager.cpp ohossensorsmanager.h
        ohossensorutils.cpp ohossensorutils.h
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINES
        NODE_ADDON_API_ENABLE_TYPE_CHECK_ON_AS
        NAPI_CPP_EXCEPTIONS
    LIBRARIES
        NodeAddonApi::NodeAddonApi
        Qt::CorePrivate
        Qt::Sensors
        ace_napi.z
        ohsensor
)
