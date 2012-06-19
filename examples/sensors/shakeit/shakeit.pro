TEMPLATE = app
TARGET = shakeit
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    audio \
    content

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/shakeit
app.path = $$[QT_INSTALL_EXAMPLES]/sensors/shakeit
INSTALLS += target app
