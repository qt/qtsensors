TEMPLATE = aux

app.files = \
    PropertyList.qml \
    components \
    images \
    info.json \
    SensorList.qml \
    icon.png \
    main.qml

!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.sensor_explorer
    INSTALLS = app
}

