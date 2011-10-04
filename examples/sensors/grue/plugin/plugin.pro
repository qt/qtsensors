TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtsensors_grue)
PLUGIN_TYPE = sensors

QT = core sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$QT.sensors.libs -lgruesensor

HEADERS += gruesensorimpl.h\

SOURCES += gruesensorimpl.cpp\
           main.cpp\

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = ALL -TCB
}

