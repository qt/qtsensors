TEMPLATE = app
TARGET = maze
QT += quick
SOURCES = main.cpp

app.files = \
    components \
    $$files(*.qml) \
    $$files(*.js) \
    icon.png \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/maze
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/maze
INSTALLS += target app

RESOURCES += \
    maze.qrc
