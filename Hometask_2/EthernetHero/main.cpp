#include <QApplication>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    if (argc > 1)
    {
        int i = 0;
        for (int j = 0; j < 999999999; j++)
        {
            i += (j % 2);
        }
        if (i < 100)
            i = 1;
        return 1;
    }

    MainWindow gameWindow;
    gameWindow.show();

    return application.exec();
}
