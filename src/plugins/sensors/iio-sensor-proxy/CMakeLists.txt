#####################################################################
## IIOSensorProxySensorPlugin Plugin:
#####################################################################

qt_internal_add_plugin(IIOSensorProxySensorPlugin
    OUTPUT_NAME qtsensors_iio-sensor-proxy
    TYPE sensors
    SOURCES
        iiosensorproxycompass.cpp iiosensorproxycompass.h
        iiosensorproxylightsensor.cpp iiosensorproxylightsensor.h
        iiosensorproxyorientationsensor.cpp iiosensorproxyorientationsensor.h
        iiosensorproxysensorbase.cpp iiosensorproxysensorbase.h
        main.cpp
    DBUS_INTERFACE_SOURCES
        org.freedesktop.DBus.Properties.xml
        net.hadess.SensorProxy.xml
        net.hadess.SensorProxy.Compass.xml
    DBUS_INTERFACE_FLAGS
        "-N"
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::DBus
        Qt::Sensors
)

#### Keys ignored in scope 1:.:.:iio-sensor-proxy.pro:<TRUE>:
# OTHER_FILES = "plugin.json" "$$DBUS_INTERFACES"
# dbus_properties.files = "org.freedesktop.DBus.Properties.xml"
# dbus_properties.header_flags = "-N"
# sensor_proxy.files = "net.hadess.SensorProxy.xml"
# sensor_proxy.header_flags = "-N"
# sensor_proxy_compass.files = "net.hadess.SensorProxy.Compass.xml"
# sensor_proxy_compass.header_flags = "-N"

## Scopes:
#####################################################################

qt_internal_extend_target(IIOSensorProxySensorPlugin CONDITION NOT ANDROID
    PUBLIC_LIBRARIES
        rt
)
