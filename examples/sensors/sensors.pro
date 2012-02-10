TEMPLATE = subdirs

SUBDIRS += \
    accel \
    grue \
    qmlsensorgestures \
    sensor_explorer

!isEmpty(QT.widgets.name): SUBDIRS += \
    sensorgestures

