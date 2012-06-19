TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtsensors_grue)
PLUGIN_TYPE = sensors

QT = core sensors

INCLUDEPATH += $$PWD/../lib
LIBS += -L$$OUT_PWD/../lib -lgruesensor

HEADERS += gruesensorimpl.h\

SOURCES += gruesensorimpl.cpp\
           main.cpp\

target.path=$$[QT_INSTALL_PLUGINS]/sensors
INSTALLS += target

OTHER_FILES += \
    plugin.json
