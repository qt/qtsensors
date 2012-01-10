TEMPLATE = subdirs

SUBDIRS += \
    accel \
    grue \
    qmlsensorgestures \
    sensor_explorer \
    shakeit

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensorgestures

