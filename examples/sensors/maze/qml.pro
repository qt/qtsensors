TEMPLATE = aux

app.files = \
    info.json \
    notions.json \
    settings.json \
    Congratulation.qml \
    LabyrinthSquare.qml \
    lib.js \
    Maze.qml \
    Mouse.qml \
    icon.png \
    components \
    images

!isEmpty(EXAMPLES_PREFIX) {
    TARGET_DIR = $$EXAMPLES_PREFIX/com.nokia.mt.maze
    app.path = $$TARGET_DIR
    INSTALLS += app
}
