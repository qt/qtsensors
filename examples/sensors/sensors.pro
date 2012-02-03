TEMPLATE = subdirs

SUBDIRS += \
    accel \
    grue \
    qmlsensorgestures \
    sensor_explorer \
    maze \
    qmlqtsensors \
    shakeit

!isEmpty(QT.widgets.name): SUBDIRS += \
    sensorgestures

