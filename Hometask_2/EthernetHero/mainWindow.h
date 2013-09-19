#pragma once

#include <QtWidgets/QMainWindow>

#include "liveRandGenerator.h"
#include "gameView.h"
#include "gameLogic.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void keyPressEvent(QKeyEvent *event);
    Ui::MainWindow *ui;
    LiveRandomGenerator *mGenerator;
    GameLogic *mGameKernel;
    GameView mViewport;
};

