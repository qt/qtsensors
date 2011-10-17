TEMPLATE = lib
CONFIG += plugin

TARGET  = qtsensorgestures_testplugin1

QT += sensors   sensorgestures
DESTDIR = $$QT.sensorgestures.plugins/sensorgestures

# Input
HEADERS +=  qtestsensorgestureplugindup_p.h \
                  qtestrecognizerdup.h \
                  qtest2recognizerdup.h
SOURCES += qtestsensorgestureplugindup.cpp \
                  qtestrecognizerdup.cpp \
                  qtest2recognizerduo.cpp

target.path += $$[QT_INSTALL_PLUGINS]/sensorgestures
INSTALLS += target
