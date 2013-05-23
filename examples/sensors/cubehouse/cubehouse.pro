TEMPLATE = app
TARGET = cubehouse
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    content \
    mesh

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/cubehouse
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/cubehouse
INSTALLS += target app

RESOURCES += \
    cubehouse.qrc
