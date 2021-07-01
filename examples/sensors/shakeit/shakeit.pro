TEMPLATE = app
TARGET = shakeit
QT += quick sensors
qtConfig(static):QTPLUGIN += qtsensorgestures_plugin qtsensorgestures_shakeplugin

SOURCES = main.cpp

RESOURCES += \
    shakeit.qrc

OTHER_FILES = \
    $$files(*.qml) \
    audio \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/shakeit
INSTALLS += target
