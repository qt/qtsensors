QT.sensors.VERSION = 5.0.0
QT.sensors.MAJOR_VERSION = 5
QT.sensors.MINOR_VERSION = 0
QT.sensors.PATCH_VERSION = 0

QT.sensors.name = QtSensors
QT.sensors.bins = $$QT_MODULE_BIN_BASE
QT.sensors.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtSensors
QT.sensors.private_includes = $$QT_MODULE_INCLUDE_BASE/QtSensors/$$QT.sensors.VERSION
QT.sensors.sources = $$QT_MODULE_BASE/src/sensors
QT.sensors.libs = $$QT_MODULE_LIB_BASE
QT.sensors.plugins = $$QT_MODULE_PLUGIN_BASE
QT.sensors.imports = $$QT_MODULE_IMPORT_BASE
QT.sensors.depends = core
QT.sensors.DEFINES = QT_SENSORS_LIB

QT_CONFIG += sensors

QT.qtmsensors.VERSION = 5.0.0
QT.qtmsensors.MAJOR_VERSION = 5
QT.qtmsensors.MINOR_VERSION = 0
QT.qtmsensors.PATCH_VERSION = 0

QT.qtmsensors.name = QtmSensors
QT.qtmsensors.bins = $$QT_MODULE_BIN_BASE
QT.qtmsensors.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtmSensors
QT.qtmsensors.private_includes = $$QT_MODULE_INCLUDE_BASE/QtmSensors/$$QT.qtmsensors.VERSION
QT.qtmsensors.sources = $$QT_MODULE_BASE/src/qtmsensors
QT.qtmsensors.libs = $$QT_MODULE_LIB_BASE
QT.qtmsensors.plugins = $$QT_MODULE_PLUGIN_BASE
QT.qtmsensors.imports = $$QT_MODULE_IMPORT_BASE
QT.qtmsensors.depends = sensors
QT.qtmsensors.DEFINES = QTM_SENSORS_LIB

QT_CONFIG += qtmsensors
