TEMPLATE = subdirs

SUBDIRS += \
    accel \
    grue \
    qmlsensorgestures \
    sensor_explorer

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensorgestures

