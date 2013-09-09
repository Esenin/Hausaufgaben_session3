#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>

#include "workStation.h"
#include "gameLogic.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);


public slots:
    void startGame();
    void stopGame();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void initGraphicsOutput();
    void setupNewNetwork();
    void setUsersToGrid();
    bool eventFilter(QObject *, QEvent *event);

private:
    //! Time for step in ms
    static const int stepTime = 1000;
    //! Time to reload updates ability
    static const int trafficReloadTime = 8;
    static const int maxUsers = 12;
    static const int minUsers = 5;
    GameLogic *gameKernel;
    QTimer stepTimer;
    QGraphicsScene *mScene;
    WorkStation *mAgent;
    WorkStation *mDevelopers;
    QList <WorkStation *> mUsers;
    int mUsersCount;
    int mTimeForReload;

private slots:
    void stepTimerEvent();


};

