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

qt_add_plugin(qtsensors_grue
    PLUGIN_TYPE sensors
)

target_sources(qtsensors_grue PRIVATE
    gruesensorimpl.cpp gruesensorimpl.h
    gruesensor.cpp gruesensor.h gruesensor_p.h
    main.cpp
)

set_target_properties(qtsensors_grue PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

if(WIN32 OR (UNIX AND NOT APPLE))
    set_target_properties(qtsensors_grue PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../sensors
    )
endif()

if(APPLE AND QT6_IS_SHARED_LIBS_BUILD)
    set_target_properties(qtsensors_grue PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../grue_app.app/Contents/Plugins/sensors
    )
endif()

target_link_libraries(qtsensors_grue PUBLIC
    Qt::Core
    Qt::Sensors
)

if(ANDROID)
    add_custom_target(gruesensorplugin_android_copy ALL
            COMMAND "${CMAKE_COMMAND}"
                -E copy_if_different
                "$<TARGET_FILE:qtsensors_grue>"
                "${CMAKE_CURRENT_BINARY_DIR}/../android-build/libs/${CMAKE_ANDROID_ARCH_ABI}/$<TARGET_FILE_NAME:qtsensors_grue>"
            COMMENT "Copying sensor plugin lib to grue_app android libs folder.")

    add_dependencies(gruesensorplugin_android_copy qtsensors_grue)
endif()

install(TARGETS qtsensors_grue
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
