cmake_minimum_required(VERSION 3.14)
project(gruesensor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/grue")

find_package(Qt6 COMPONENTS Core Sensors)

qt_add_executable(gruesensor
    gruesensor.cpp gruesensor.h gruesensor_p.h
)
set_target_properties(gruesensor PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_compile_definitions(gruesensor PUBLIC
    QT_BUILD_GRUE_LIB
)

target_link_libraries(gruesensor PUBLIC
    Qt::Core
    Qt::Sensors
)

install(TARGETS gruesensor
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
