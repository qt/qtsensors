TEMPLATE = aux

app.files = \
    info.json \
    QtSensors_sensor_explorer.qml \
    PropertyList.qml \
    SensorList.qml \
    icon.png \
    components \
    content

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.sensor_explorer
    INSTALLS = app
}

