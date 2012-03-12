TEMPLATE = app
TARGET = tst_qsensorgesturepluginstest
!no_system_tests:CONFIG += testcase

QT += core testlib sensors
QT -= gui

SOURCES += tst_qsensorgesturepluginstest.cpp

