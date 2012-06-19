TEMPLATE = subdirs

SUBDIRS += \
    accel \
    accelbubble \
    cubehouse \
    grue \
    qmlsensorgestures \
    maze \
    qmlqtsensors \
    sensor_explorer \
    shakeit

!isEmpty(QT.widgets.name):SUBDIRS += \
    sensorgestures

