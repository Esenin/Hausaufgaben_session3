#include "mainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(&viewport);
    viewport.startGame();
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}
