TEMPLATE = aux

app.files = \
    Button.qml \
    GestureList.qml \
    GesturesView.qml \
    info.json \
    Gesture.qml \
    GestureView.qml \
    icon.png

!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.qmlsensorgestures
    INSTALLS = app
}

