TEMPLATE = aux

app.files = \
    info.json \
    main.qml \
    icon.png \
    components

!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.qmlqtsensors
    INSTALLS = app
}

