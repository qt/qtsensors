cmake_minimum_required(VERSION 3.16)
project(qmlqtsensors LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/qmlqtsensors")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

qt_add_executable(qmlqtsensors
    main.cpp
)

set_target_properties(qmlqtsensors PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlqtsensors PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
)

# Resources:
set(qmlqtsensors_resource_files
    "components/ApplicationWindow.qml"
    "components/Button.qml"
    "components/Divider.qml"
    "components/images/button_background_disabled.png"
    "components/images/button_background_normal.png"
    "components/images/button_background_pressed.png"
    "qmlqtsensors.qml"
)

qt6_add_resources(qmlqtsensors "qmlqtsensors"
    PREFIX
        "/"
    FILES
        ${qmlqtsensors_resource_files}
)

install(TARGETS qmlqtsensors
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
