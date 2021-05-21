#####################################################################
## tst_sensors2qmlapi Test:
#####################################################################

qt_internal_add_test(tst_sensors2qmlapi
    SOURCES
        qtemplategestureplugin.cpp qtemplategestureplugin.h
        qtemplaterecognizer.cpp qtemplaterecognizer.h
        tst_sensors2qmlapi.cpp
    PUBLIC_LIBRARIES
        Qt::Qml
    LIBRARIES
        Qt::SensorsPrivate
        Qt::SensorsQuickPrivate
)
