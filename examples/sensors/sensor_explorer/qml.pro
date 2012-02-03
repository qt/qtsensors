TEMPLATE = aux

app.files = \
    info.json \
    notions.json \
    settings.json \
    main.qml \
    PropertyList.qml \
    SensorList.qml \
    icon.png \
    components \
    images

!isEmpty(EXAMPLES_PREFIX) {
    TARGET_DIR = $$EXAMPLES_PREFIX/com.nokia.mt.sensorexplorer
    app.path = $$TARGET_DIR
    INSTALLS = app
}

