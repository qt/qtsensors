TEMPLATE = app
TARGET = sensor_explorer
QT += qml quick

qtHaveModule(widgets) {
    QT += widgets
}
SOURCES = main.cpp

app.files = \
    sensor_explorer.qml \
    icon.png

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensor_explorer
app.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensor_explorer
INSTALLS += target app

RESOURCES += \
    qml.qrc
