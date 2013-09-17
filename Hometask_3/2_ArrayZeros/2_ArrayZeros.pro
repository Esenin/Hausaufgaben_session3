TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT += testlib

SOURCES += src/main.cpp

HEADERS += \
    src/arrayChecker.h \
    test/testArrayChecker.h

