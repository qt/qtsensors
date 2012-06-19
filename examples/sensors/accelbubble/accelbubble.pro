TEMPLATE = app
TARGET = accelbubble
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    content \
    images

target.path = $$[QT_INSTALL_EXAMPLES]/sensors/accelbubble
app.path = $$[QT_INSTALL_EXAMPLES]/sensors/accelbubble
INSTALLS += target app
