TEMPLATE = app
TARGET = qmlsensorgestures
QT += quick
qtConfig(static):QTPLUGIN += qtsensorgestures_plugin qtsensorgestures_shakeplugin

SOURCES = main.cpp

OTHER_FILES = \
    $$files(*.qml)

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/qmlsensorgestures
INSTALLS += target

RESOURCES += \
    qml.qrc
