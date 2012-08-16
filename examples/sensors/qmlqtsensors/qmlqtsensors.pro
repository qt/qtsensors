TEMPLATE = app
TARGET = qmlqtsensors
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    components

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/qmlqtsensors
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/qmlqtsensors
INSTALLS += target app
