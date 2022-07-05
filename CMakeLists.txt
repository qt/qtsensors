# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0


cmake_minimum_required(VERSION 3.16)

include(.cmake.conf)

project(QtSensors
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt Sensors Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core)
find_package(Qt6 ${PROJECT_VERSION} CONFIG OPTIONAL_COMPONENTS
             Xml Gui Widgets Quick Qml Svg DBus QuickTest
)

qt_build_repo()
