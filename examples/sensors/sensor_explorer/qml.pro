TEMPLATE = app
TARGET = sensor_explorer
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    components \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensor_explorer
app.path = $$[QT_INSTALL_EXAMPLES]/sensors/sensor_explorer
INSTALLS += target app
