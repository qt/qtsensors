cmake_minimum_required(VERSION 3.14)
project(grue_app LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/grue")

find_package(Qt6 COMPONENTS Quick)

qt_add_executable(grue_app
    main.cpp
)
set_target_properties(grue_app PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(TARGET Qt::Quick)
    target_link_libraries(grue_app PUBLIC
        Qt::Quick
    )
endif()

# Resources:
set(qml_resource_files
    "grue.png"
    "grue.qml"
)

qt6_add_resources(grue_app "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)

install(TARGETS grue_app
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

add_subdirectory(lib)
add_subdirectory(plugin)
add_subdirectory(console_app)
if(TARGET Qt::Quick)
    add_subdirectory(import)
endif()
