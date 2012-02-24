TEMPLATE = aux

app.files = \
    icon.png \
    info.json \
    main.qml

!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.grue
    INSTALLS = app
}

