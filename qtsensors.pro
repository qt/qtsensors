TEMPLATE = subdirs

SUBDIRS += module_qtsensors_src
module_qtsensors_src.subdir = src
module_qtsensors_src.target = module-qtsensors-src

SUBDIRS += module_qtsensors_tests
module_qtsensors_tests.subdir = tests
module_qtsensors_tests.target = module-qtsensors-tests
module_qtsensors_tests.depends = module_qtsensors_src
!contains(QT_BUILD_PARTS,tests) {
    module_qtsensors_tests.CONFIG += no_default_target no_default_install
}

SUBDIRS += module_qtsensors_examples
module_qtsensors_examples.subdir = examples
module_qtsensors_examples.target = module-qtsensors-examples
module_qtsensors_examples.depends = module_qtsensors_src
!contains(QT_BUILD_PARTS,examples) {
    module_qtsensors_examples.CONFIG = no_default_target no_default_install
}

SUBDIRS += module_qtsensors_snippets
module_qtsensors_snippets.subdir = doc/src/snippets
module_qtsensors_snippets.target = module-qtsensors-snippets
module_qtsensors_snippets.depends = module_qtsensors_src

include(doc/config/qtsensors_doc.pri)

!isEmpty(MIDDLEWARE):exists($$MIDDLEWARE/$$MIDDLEWARE.pro) {
    SUBDIRS += module_qtsensors_middleware
    module_qtsensors_middleware.subdir = $$MIDDLEWARE
    module_qtsensors_middleware.target = module-qtsensors-middleware
    module_qtsensors_middleware.depends = module_qtsensors_src
}

# Commands to rebuild the plugin.qmltypes files for our imports
# Run "make rebuild_qmltypes" after completing a build
sensors_qmltypes.commands = qmlplugindump QtMobility.sensors 1.3 $$QT.sensors.imports > $$PWD/src/imports/sensors/plugin.qmltypes
sensors2_qmltypes.commands = qmlplugindump QtSensors 5.0 $$QT.sensors.imports > $$PWD/src/imports/sensors2/plugin.qmltypes
TYPES = sensors_qmltypes sensors2_qmltypes
rebuild_qmltypes.depends = $$TYPES
QMAKE_EXTRA_TARGETS += rebuild_qmltypes $$TYPES
