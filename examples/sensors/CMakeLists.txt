# TODO Qt 6.2 enable grue example, requires work
# add_subdirectory(grue)

if(TARGET Qt::Quick)
    add_subdirectory(maze)
    # TODO Qt 6.2 enable qmlsensorgestures, requires work
    # add_subdirectory(qmlsensorgestures)
    add_subdirectory(qmlqtsensors)
    # TODO Qt 6.2 enable sensor_explorer, requires work
    # add_subdirectory(sensor_explorer)
    if (TARGET Qt::Multimedia)
        add_subdirectory(shakeit)
    endif()
    if(TARGET Qt::Svg)
        add_subdirectory(accelbubble)
    endif()
endif()
if(TARGET Qt::Widgets)
    add_subdirectory(sensorgestures)
endif()
