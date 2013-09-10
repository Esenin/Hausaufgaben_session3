#pragma once

#include <QMainWindow>

#include "gameView.h"
#include "gameLogic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameLogic *gameKernel;
    GameView viewport;
};

