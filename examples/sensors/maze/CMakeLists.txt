cmake_minimum_required(VERSION 3.14)
project(maze LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
  set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/maze")

find_package(Qt6 COMPONENTS Core Gui Quick Sensors)

qt_add_executable(maze
    main.cpp
)
set_target_properties(maze PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(maze PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Sensors
)


# Resources:
set(maze_resource_files
    "Congratulation.qml"
    "LabyrinthSquare.qml"
    "Mouse.qml"
    "components/ApplicationWindow.qml"
    "components/Button.qml"
    "components/images/button_background_disabled.png"
    "components/images/button_background_normal.png"
    "components/images/button_background_pressed.png"
    "content/00.png"
    "content/01.png"
    "content/cheese.png"
    "content/cheeseeating.gif"
    "content/congratulations.gif"
    "content/mouse_down.gif"
    "content/start.png"
    "lib.js"
    "maze.qml"
)

qt6_add_resources(maze "maze"
    PREFIX
        "/"
    FILES
        ${maze_resource_files}
)

install(TARGETS maze
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
