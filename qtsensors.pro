load(configure)
blackberry {
    qtCompileTest(bbsensor_header)
    qtCompileTest(bbsensor_compass)
}

load(qt_parts)

SUBDIRS += module_qtsensors_snippets
module_qtsensors_snippets.subdir = doc/src/snippets
module_qtsensors_snippets.target = sub-snippets
module_qtsensors_snippets.depends = sub_src

# Commands to rebuild the plugin.qmltypes files for our imports
# Run "make rebuild_qmltypes" after completing a build
sensors_qmltypes.commands = qmlplugindump QtSensors 5.0 $$QT.sensors.imports > $$PWD/src/imports/sensors/plugins.qmltypes
TYPES = sensors_qmltypes
rebuild_qmltypes.depends = $$TYPES
QMAKE_EXTRA_TARGETS += rebuild_qmltypes $$TYPES
