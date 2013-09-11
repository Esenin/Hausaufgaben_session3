#include "mainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(&mViewport);
    showMaximized();
    setWindowTitle("EthernetHero the Game");

    mGameKernel = new GameLogic(&mViewport);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    mGameKernel->startGame();
    mViewport.setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        mGameKernel->startGame();
    }
}
