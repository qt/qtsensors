cmake_minimum_required(VERSION 3.16)
project(qmlsensorgestures LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/qmlsensorgestures")

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(qmlsensorgestures
    main.cpp
)

set_target_properties(qmlsensorgestures PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlsensorgestures PUBLIC
    Qt::Quick
)

# Resources:
set(qml_resource_files
    "Button.qml"
    "GestureList.qml"
    "GestureView.qml"
    "GesturesView.qml"
    "qmlsensorgestures.qml"
)

qt6_add_resources(qmlsensorgestures "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

install(TARGETS qmlsensorgestures
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

add_subdirectory(plugin)
