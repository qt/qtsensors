#####################################################################
## sensor_explorer Binary:
#####################################################################

qt_internal_add_manual_test(sensor_explorer
    GUI
    SOURCES
        explorer.cpp explorer.h explorer.ui
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Sensors
        Qt::Widgets
    ENABLE_AUTOGEN_TOOLS
        uic
)
