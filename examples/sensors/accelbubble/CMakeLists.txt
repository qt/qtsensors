cmake_minimum_required(VERSION 3.16)
project(accelbubble LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sensors/accelbubble")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Sensors Svg Xml)

qt_add_executable(accelbubble
    main.cpp
)

set_target_properties(accelbubble PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(ANDROID)
    set_property(TARGET accelbubble PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/android)
    endif()
if(APPLE)
    if(IOS)
        set_property(TARGET accelbubble PROPERTY
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
        )
    endif()
endif()

target_link_libraries(accelbubble PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Sensors
    Qt::Svg
    Qt::Xml
)

# Resources:
set(accelbubble_resource_files
    "accelbubble.qml"
    "content/Bluebubble.svg"
)

qt6_add_resources(accelbubble "accelbubble"
    PREFIX
        "/"
    FILES
        ${accelbubble_resource_files}
)

install(TARGETS accelbubble
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
