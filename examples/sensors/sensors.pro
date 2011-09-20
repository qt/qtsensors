TEMPLATE = subdirs

SUBDIRS += \
    accel\
    cubehouse\
    grueapp\
    grueplugin

contains(QT_CONFIG,widgets):SUBDIRS += \
    sensor_explorer
