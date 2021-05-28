TEMPLATE = app
TARGET = sensor_explorer
QT += qml quick sensors

# Avoid going to release/debug subdirectory
win32: DESTDIR = ./

SOURCES = main.cpp sensormodels.cpp
HEADERS = sensormodels.h

CONFIG += qmltypes
QML_IMPORT_NAME = SensorModels
QML_IMPORT_MAJOR_VERSION = 1

OTHER_FILES = \
    sensor_explorer.qml

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensor_explorer
INSTALLS += target

RESOURCES += \
    qml.qrc
