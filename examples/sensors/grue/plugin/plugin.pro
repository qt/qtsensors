TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(plugins_sensors_qtsensors_grue)
PLUGIN_TYPE = sensors

QT = core sensors

macos:!qtConfig(static): DESTDIR = ../grue_app.app/Contents/MacOS/$$PLUGIN_TYPE
else: DESTDIR = ../$$PLUGIN_TYPE

HEADERS += gruesensorimpl.h \
           gruesensor.h \
           gruesensor_p.h

SOURCES += gruesensorimpl.cpp \
           main.cpp \
           gruesensor.cpp


# Install the plugin under Grue example directory
target.path=$$[QT_INSTALL_EXAMPLES]/sensors/grue/$$PLUGIN_TYPE
INSTALLS += target

CONFIG += install_ok  # Do not cargo-cult this!

OTHER_FILES += \
    plugin.json
