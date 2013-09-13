#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T19:30:29
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EthernetHero
TEMPLATE = app


SOURCES += main.cpp\
    workStation.cpp \
    gameView.cpp \
    gameLogic.cpp \
    mainWindow.cpp

HEADERS  += \
    workStation.h \
    gameView.h \
    gameLogic.h \
    mainWindow.h \
    tests/testWorkStation.h \
    tests/testGameLogic.h \
    tests/testGameViewport.h

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc
