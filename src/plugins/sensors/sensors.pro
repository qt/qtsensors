TEMPLATE = subdirs

isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, dummy):SUBDIRS += dummy
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, generic):SUBDIRS += generic
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, simulator):simulator:SUBDIRS += simulator
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, blackberry):blackberry:SUBDIRS += blackberry
isEmpty(SENSORS_PLUGINS)|contains(SENSORS_PLUGINS, linux):linux:SUBDIRS += linux
