qt_internal_add_test(tst_sensors_qmlcpp
    SOURCES
        ../../common/test_backends.cpp ../../common/test_backends.h
        qtemplategestureplugin.cpp qtemplategestureplugin.h
        qtemplaterecognizer.cpp qtemplaterecognizer.h
        tst_sensors_qmlcpp.cpp
    LIBRARIES
        Qt::Qml
        Qt::SensorsPrivate
        Qt::SensorsQuickPrivate
        Qt::TestPrivate
)
