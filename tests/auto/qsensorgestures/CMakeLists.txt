#####################################################################
## tst_qsensorgesturetest Test:
#####################################################################

qt_internal_add_test(tst_qsensorgesturetest
    SOURCES
        plugins/test/qtest2recognizer.cpp plugins/test/qtest2recognizer.h
        plugins/test/qtestrecognizer.cpp plugins/test/qtestrecognizer.h
        plugins/test/qtestsensorgestureplugin.cpp plugins/test/qtestsensorgestureplugin_p.h
        plugins/test1/qtest2recognizerdup.cpp plugins/test1/qtest2recognizerdup.h
        plugins/test1/qtestrecognizerdup.cpp plugins/test1/qtestrecognizerdup.h
        plugins/test1/qtestsensorgestureplugindup.cpp plugins/test1/qtestsensorgestureplugindup.h
        tst_qsensorgesturetest.cpp
    DEFINES
        QT_STATICPLUGIN
    PUBLIC_LIBRARIES
        Qt::Sensors
)
