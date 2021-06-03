
qt_internal_add_test(tst_sensors_qmlcpp
    SOURCES
        qtemplategestureplugin.cpp qtemplategestureplugin.h
        qtemplaterecognizer.cpp qtemplaterecognizer.h
        tst_sensors_qmlcpp.cpp
    PUBLIC_LIBRARIES
        Qt::Qml
    LIBRARIES
        Qt::SensorsPrivate
        Qt::SensorsQuickPrivate
)
