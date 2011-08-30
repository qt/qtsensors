TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtsensors_grueplugin)
PLUGIN_TYPE = sensors

QT = core sensors

include(version.pri)
include(grueplugin.pri)

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

