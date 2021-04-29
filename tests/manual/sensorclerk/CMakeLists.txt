#####################################################################
## sensorclerk Binary:
#####################################################################

qt_internal_add_manual_test(tst_manual_sensor_clerk
    GUI
    SOURCES
        collector.cpp collector.h
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Quick
        Qt::Sensors
)

set(qml_files
    "qml/main.qml"
)

qt_internal_add_resource(tst_manual_sensor_clerk "qml_files"
    PREFIX
        "/"
    FILES
        ${qml_files}
)
