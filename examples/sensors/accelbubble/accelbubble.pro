TEMPLATE = app
TARGET = accelbubble
QT += quick
SOURCES = main.cpp

app.files = \
    $$files(*.qml) \
    icon.png \
    content \
    images

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/accelbubble
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/accelbubble
INSTALLS += target app
