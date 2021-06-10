TEMPLATE = app
TARGET = grue_app
QT += qml quick sensors

# Avoid going to release/debug subdirectory
win32: DESTDIR = ./

SOURCES = main.cpp \
    qmlgruesensor.cpp

HEADERS += \
    qmlgruesensor.h

grue_plugin_base_dir = .
include(use_grue_static_plugin.pri)

CONFIG += qmltypes
QML_IMPORT_NAME = QMLGrueSensor
QML_IMPORT_MAJOR_VERSION = 1

RESOURCES += \
    qml.qrc

OTHER_FILES = \
    $$files(*.qml) \
    grue.png

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/grue
INSTALLS += target

EXAMPLE_FILES += \
    grue.xcf \
    icon.xcf

android{
    CONFIG += file_copies
    COPIES += androidPluginCopy
    androidPluginCopy.files = $$OUT_PWD/sensors/libplugins_sensors_qtsensors_grue_armeabi-v7a.so
    androidPluginCopy.path = android-build/libs/armeabi-v7a
}
