TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt
QT  += testlib

SOURCES += src/main.cpp \
    src/graph.cpp

OTHER_FILES += \
    res/data.txt \
    res/input.txt

HEADERS += \
    src/graph.h \
    test/testPack.h

RESOURCES += \
    res/resources.qrc

