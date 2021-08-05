#####################################################################
## QtSensorGesturePlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtSensorGesturePlugin
    OUTPUT_NAME qtsensorgestures_plugin
    PLUGIN_TYPE sensorgestures
    DEFAULT_IF FALSE
    SOURCES
        qcoversensorgesturerecognizer.cpp qcoversensorgesturerecognizer.h
        qdoubletapsensorgesturerecognizer.cpp qdoubletapsensorgesturerecognizer.h
        qfreefallsensorgesturerecognizer.cpp qfreefallsensorgesturerecognizer.h
        qhoversensorgesturerecognizer.cpp qhoversensorgesturerecognizer.h
        qpickupsensorgesturerecognizer.cpp qpickupsensorgesturerecognizer.h
        qshake2recognizer.cpp qshake2recognizer.h
        qslamgesturerecognizer.cpp qslamgesturerecognizer.h
        qtsensorgestureplugin.cpp qtsensorgestureplugin.h
        qtsensorgesturesensorhandler.cpp qtsensorgesturesensorhandler.h
        qturnoversensorgesturerecognizer.cpp qturnoversensorgesturerecognizer.h
        qtwistsensorgesturerecognizer.cpp qtwistsensorgesturerecognizer.h
        qwhipsensorgesturerecognizer.cpp qwhipsensorgesturerecognizer.h
    LIBRARIES
        Qt::Core
        Qt::Sensors
)

#### Keys ignored in scope 1:.:.:qtsensors.pro:<TRUE>:
# OTHER_FILES = "plugin.json"
# PLUGIN_EXTENDS = "-"
