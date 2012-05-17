TEMPLATE = aux

app.files = \
    components \
    info.json \
    Congratulation.qml \
    LabyrinthSquare.qml \
    lib.js \
    QtSensors_maze.qml \
    Mouse.qml \
    icon.png \
    content

MT_SYSROOT=$$(MT_SYSROOT)
!isEmpty(MT_SYSROOT):EXAMPLES_PREFIX=/opt/mt/applications
!isEmpty(EXAMPLES_PREFIX) {
    app.path = $$EXAMPLES_PREFIX/com.nokia.mt.maze
    INSTALLS = app
}

