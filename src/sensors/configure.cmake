

#### Inputs



#### Libraries
# special case begin
if (LINUX)
    qt_find_package(Sensorfw PROVIDED_TARGETS Sensorfw::Sensorfw MODULE_NAME sensors QMAKE_LIB sensorfw)
endif()
# special case end

#### Tests



#### Features

# special case begin
qt_feature("sensorfw" PRIVATE
    LABEL "sensorfw"
    CONDITION Sensorfw_FOUND
)
# special case end

qt_configure_add_summary_section(NAME "Qt Sensors")
if (LINUX)
    # At the moment there is no Qt6 version of sensorfw, and while the
    # FindSensorfw.cmake in this repo would find the package using pkg-config,
    # it would not work. Once the Qt6 version exists, remove the
    # "sensorfw_enabled_with_cmake" entry, enable build in
    # src/plugins/sensors/CMakeLists.txt and fix any potential errors.
    qt_configure_add_summary_entry(ARGS "sensorfw")
    qt_configure_add_summary_entry(ARGS "sensorfw_enabled_with_cmake")
    qt_configure_add_report(MESSAGE "SensorFW support currently not enabled with cmake")
endif()
qt_configure_end_summary_section() # end of "Qt Sensors" section
