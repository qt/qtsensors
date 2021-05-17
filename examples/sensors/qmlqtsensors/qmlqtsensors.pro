TEMPLATE = app
TARGET = qmlqtsensors
QT += quick
qtConfig(static):QT += sensors

SOURCES = main.cpp

RESOURCES += \
    qmlqtsensors.qrc

OTHER_FILES = \
    $$files(*.qml) \
    components

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/qmlqtsensors
INSTALLS += target
