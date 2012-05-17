TEMPLATE = aux

app.files = \
    info.json \
    QtSensors_shakeit.qml \
    icon.png \
    audio \
    content

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.shakeit
    INSTALLS = app
}

