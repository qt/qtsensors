TEMPLATE = aux

app.files = \
    info.json \
    notions.json \
    settings.json \
    main.qml \
    icon.png \
    components

!isEmpty(EXAMPLES_PREFIX) {
    TARGET_DIR = $$EXAMPLES_PREFIX/com.nokia.mt.qmlqtsensors
    app.path = $$TARGET_DIR
    INSTALLS = app
}

