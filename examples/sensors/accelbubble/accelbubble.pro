TEMPLATE = aux

app.files = \
    info.json \
    main.qml \
    icon.png \
    images

!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.accelbubble
    INSTALLS = app
}

