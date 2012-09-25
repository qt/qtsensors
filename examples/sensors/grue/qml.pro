TEMPLATE = app
TARGET = grue
QT += quick
SOURCES = main.cpp

app.files = \
    icon.png \
    $$files(*.qml) \
    grue.png

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/grue
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/grue
INSTALLS += target app
