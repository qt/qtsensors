#####################################################################
## sensorclerk Binary:
#####################################################################

qt_internal_add_manual_test(sensorclerk
    GUI
    SOURCES
        collector.cpp collector.h
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Quick
        Qt::Sensors
)
