load(configure)
blackberry {
    qtCompileTest(bbsensor_header)
    qtCompileTest(bbsensor_compass)
}

load(qt_parts)

# QtCreator 2.5 doesn't understand load(qt_parts)
#qtcreator25 {
    TEMPLATE = subdirs
    SUBDIRS *= examples src tests
    OTHER_FILES *= \
        doc/src/*.qdoc doc/src/*.dia \
        doc/src/examples/* \
        doc/src/imports/*
#}

SUBDIRS += module_qtsensors_snippets
module_qtsensors_snippets.subdir = doc/src/snippets
module_qtsensors_snippets.target = sub-snippets
module_qtsensors_snippets.depends = sub_src

# Commands to rebuild the plugin.qmltypes files for our imports
# Run "make rebuild_qmltypes" after completing a build
sensors_qmltypes.commands = qmlplugindump QtMobility.sensors 1.3 $$QT.sensors.imports > $$PWD/src/imports/sensors/plugins.qmltypes
sensors2_qmltypes.commands = qmlplugindump QtSensors 5.0 $$QT.sensors.imports > $$PWD/src/imports/sensors2/plugins.qmltypes
TYPES = sensors_qmltypes sensors2_qmltypes
rebuild_qmltypes.depends = $$TYPES
QMAKE_EXTRA_TARGETS += rebuild_qmltypes $$TYPES
