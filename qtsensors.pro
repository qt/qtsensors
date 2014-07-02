load(configure)
blackberry {
    qtCompileTest(bbsensor_header)
    qtCompileTest(bbsensor_compass)
    qtCompileTest(bbsensor_holster)
}
tizen {
    qtCompileTest(tizensensor_header)
}

load(qt_parts)
