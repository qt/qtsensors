TEMPLATE = subdirs

isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, dummy):SUBDIRS += dummy
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, generic):SUBDIRS += generic
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, simulator):simulator:SUBDIRS += simulator
