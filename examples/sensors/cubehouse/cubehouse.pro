TEMPLATE = app
TARGET = cubehouse
QT += quick
SOURCES = main.cpp

OTHER_FILES = \
    $$files(*.qml) \
    content \
    mesh

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/cubehouse
INSTALLS += target

RESOURCES += \
    cubehouse.qrc
