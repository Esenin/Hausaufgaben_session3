TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

SOURCES += src/main.cpp \
    src/graph.cpp

OTHER_FILES += \
    res/data.txt

HEADERS += \
    src/graph.h

RESOURCES += \
    res/resources.qrc

