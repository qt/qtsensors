TEMPLATE = app
TARGET = maze
QT += quick
SOURCES = main.cpp

OTHER_FILES = \
    components \
    $$files(*.qml) \
    $$files(*.js) \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/maze
INSTALLS += target

RESOURCES += \
    maze.qrc
