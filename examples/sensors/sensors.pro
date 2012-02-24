TEMPLATE = subdirs

SUBDIRS += \
    accel \
    accelbubble \
    cubehouse \
    grue \
    maze \
    qmlqtsensors \
    qmlsensorgestures \
    sensor_explorer \
    shakeit

!isEmpty(QT.widgets.name):SUBDIRS += \
    sensorgestures

