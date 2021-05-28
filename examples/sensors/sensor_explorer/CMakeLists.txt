cmake_minimum_required(VERSION 3.14)
project(sensor_explorer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/sensor_explorer")

find_package(Qt6 COMPONENTS Qml Quick Sensors)

qt_add_executable(sensor_explorer
    main.cpp
    sensormodels.cpp sensormodels.h
)

set_target_properties(sensor_explorer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(sensor_explorer PUBLIC
    Qt::Qml
    Qt::Quick
    Qt::Sensors
)

# Resources:
set(qml_resource_files
    "sensor_explorer.qml"
)

qt6_add_resources(sensor_explorer "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

install(TARGETS sensor_explorer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

set_target_properties(sensor_explorer PROPERTIES
    QT_QML_MODULE_VERSION 1.0
    QT_QML_MODULE_URI SensorModels
)

qt_qml_type_registration(sensor_explorer)
