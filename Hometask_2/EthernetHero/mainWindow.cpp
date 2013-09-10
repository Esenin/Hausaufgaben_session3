#include "mainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(&viewport);
    showMaximized();
    setWindowTitle("EthernetHero the Game");
    gameKernel = new GameLogic(&viewport);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    gameKernel->startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}
