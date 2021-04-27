cmake_minimum_required(VERSION 3.14)
project(declarative_explorer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/sensor_explorer/Explorer")

find_package(Qt6 COMPONENTS Core Gui Qml Sensors)

# Hack to convince qt6_add_qml_module to respect the shared-ness of a Qt build
# TODO Qt 6.2 FIXME when a proper fix is available
set(BUILD_SHARED_LIBS "${QT6_IS_SHARED_LIBS_BUILD}")

if (APPLE AND NOT IOS)
    set(PLUGIN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../sensor_explorer.app/Contents/MacOS/Explorer")
else()
    set(PLUGIN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../Explorer")
endif()

qt6_add_qml_module(declarative_explorer
    OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_DIRECTORY}"
    VERSION 1.0
    URI "Explorer"
    INSTALL_LOCATION ${INSTALL_EXAMPLEDIR}
)

target_sources(declarative_explorer PRIVATE
    explorer.cpp explorer.h
    main.cpp main.h
    propertyinfo.cpp propertyinfo.h
    sensoritem.cpp sensoritem.h
)

set_target_properties(declarative_explorer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(declarative_explorer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Sensors
)

install(TARGETS declarative_explorer
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
