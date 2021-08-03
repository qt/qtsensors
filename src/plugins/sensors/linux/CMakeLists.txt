#####################################################################
## LinuxSensorPlugin Plugin:
#####################################################################

qt_internal_add_plugin(LinuxSensorPlugin
    OUTPUT_NAME qtsensors_linuxsys
    TYPE sensors
    SOURCES
        linuxsysaccelerometer.cpp linuxsysaccelerometer.h
        main.cpp
    LIBRARIES
        Qt::Core
        Qt::Sensors
)

#### Keys ignored in scope 1:.:.:linux.pro:<TRUE>:
# OTHER_FILES = "plugin.json"

## Scopes:
#####################################################################

qt_internal_extend_target(LinuxSensorPlugin CONDITION NOT ANDROID
    PUBLIC_LIBRARIES
        rt
)
