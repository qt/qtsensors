load(qt_module)

TARGET = qtsensors_generic
QT = core sensors

load(qt_plugin)

DESTDIR = $$QT.sensors.plugins/sensors

include(generic.pri)


symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.UID3 = 0x2002BFC3
    TARGET.CAPABILITY = ALL -TCB

    pluginDep.sources = $${TARGET}.dll
    pluginDep.path = $${QT_PLUGINS_BASE_DIR}/$${PLUGIN_TYPE}
    DEPLOYMENT += pluginDep
}

target.path += $$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target
