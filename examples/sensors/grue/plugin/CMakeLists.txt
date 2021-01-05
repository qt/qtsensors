# Generated from plugin.pro.

cmake_minimum_required(VERSION 3.14)
project(qtsensors_grue LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/grue/sensors")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Sensors)

qt_add_plugin(qtsensors_grue)
target_sources(qtsensors_grue PRIVATE
    gruesensorimpl.cpp gruesensorimpl.h
    main.cpp
)
set_target_properties(qtsensors_grue PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_include_directories(qtsensors_grue PUBLIC
    ../lib
)

target_link_libraries(qtsensors_grue PUBLIC
    Qt::Core
    Qt::Sensors
    gruesensor
)

if(MACOS)
    target_link_libraries(qtsensors_grue PUBLIC
        # Remove: L${CMAKE_CURRENT_BINARY_DIR}/../grue_app.app/Contents/Frameworks
    )
endif()

if(NOT MACOS)
    target_link_libraries(qtsensors_grue PUBLIC
        # Remove: L${CMAKE_CURRENT_BINARY_DIR}/..
    )
endif()

install(TARGETS qtsensors_grue
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
