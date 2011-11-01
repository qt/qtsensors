TEMPLATE = subdirs

SUBDIRS += \
    accel \
    grue \
    qmlsensorgestures

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensor_explorer \
    sensorgestures

