qt_internal_add_qml_module(declarative_sensors
    URI "QtSensors"
    VERSION "${PROJECT_VERSION}"
    CLASSNAME QtSensorsDeclarativeModule
    SKIP_TYPE_REGISTRATION
    PLUGIN_OPTIONAL
    SOURCES
        sensors.cpp
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Qml
    LIBRARIES
        Qt::SensorsQuickPrivate
)
