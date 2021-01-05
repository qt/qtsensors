#####################################################################
## WinRtSensorPlugin Plugin:
#####################################################################

qt_internal_add_plugin(WinRtSensorPlugin
    OUTPUT_NAME qtsensors_winrt
    TYPE sensors
    SOURCES
        main.cpp
        winrtaccelerometer.cpp winrtaccelerometer.h
        winrtambientlightsensor.cpp winrtambientlightsensor.h
        winrtcommon.cpp winrtcommon.h
        winrtcompass.cpp winrtcompass.h
        winrtgyroscope.cpp winrtgyroscope.h
        winrtorientationsensor.cpp winrtorientationsensor.h
        winrtrotationsensor.cpp winrtrotationsensor.h
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Sensors
    LIBRARIES
        Qt::CorePrivate
        runtimeobject
)

#### Keys ignored in scope 1:.:.:winrt.pro:<TRUE>:
# OTHER_FILES = "plugin.json"
