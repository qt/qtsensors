# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(Sensorfw sensord-qt5 IMPORTED_TARGET)
    if (NOT TARGET PkgConfig::Sensorfw)
        set(Sensorfw_FOUND 0)
    endif()
else()
    message("Sensorfw pkg not found. Looking for library")
    find_library(Sensorfw sensorfw)
endif()
