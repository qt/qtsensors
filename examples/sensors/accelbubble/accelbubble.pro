TEMPLATE = app
TARGET = accelbubble
QT += quick sensors svg xml
SOURCES = main.cpp

RESOURCES += \
    accelbubble.qrc

app.files = \
    $$files(*.qml) \
    icon.png \
    content \
    images

target.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/accelbubble
app.path = $$[QT_INSTALL_EXAMPLES]/qtsensors/accelbubble
INSTALLS += target app
