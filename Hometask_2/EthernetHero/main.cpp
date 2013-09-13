#include <QtWidgets/QApplication>
#include <QtTest/QTest>

#include "tests/testGameLogic.h"
#include "tests/testGameViewport.h"
#include "tests/testWorkStation.h"

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    GameLogicTest logicTest;
    WorkStationTest stationTest;
    GameViewportTest viewTest;

    QTest::qExec(&logicTest);
    QTest::qExec(&stationTest);
    QTest::qExec(&viewTest);


    MainWindow gameWindow;
    gameWindow.show();

    return application.exec();
}
