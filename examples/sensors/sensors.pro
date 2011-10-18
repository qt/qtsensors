TEMPLATE = subdirs

SUBDIRS += \
    accel\
    grue

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensor_explorer
