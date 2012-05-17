TEMPLATE = subdirs

SUBDIRS += \
    accel \
    accelbubble \
    cubehouse \
    grue \
    qmlsensorgestures \
    QtSensors_maze \
    QtSensors_qmlqtsensors \
    QtSensors_sensor_explorer \
    QtSensors_shakeit

!isEmpty(QT.widgets.name):SUBDIRS += \
    sensorgestures

