TEMPLATE = subdirs

SUBDIRS += \
    QtSensors_accel \
    QtSensors_accelbubble \
    QtSensors_cubehouse \
    QtSensors_grue \
    QtSensors_qmlsensorgestures \
    QtSensors_maze \
    QtSensors_qmlqtsensors \
    QtSensors_sensor_explorer \
    QtSensors_shakeit

!isEmpty(QT.widgets.name):SUBDIRS += \
    QtSensors_sensorgestures

