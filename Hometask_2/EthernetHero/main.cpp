#include <QtWidgets/QApplication>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow gameWindow;
    gameWindow.show();

    return application.exec();
}
