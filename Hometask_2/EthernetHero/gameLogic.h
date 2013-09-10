#pragma once

#include "gameView.h"
#include "workStation.h"

class GameLogic : public QObject
{
    Q_OBJECT
public:
    explicit GameLogic(GameView  *viewport);
    void makeNextMove();

public slots:
    void startGame();
    void stopGame();
    void setReloadTime();

signals:
    void newWorkingDay();
    void energyChanged(bool);

protected:
    void researchNewViruses();
    void setupNewNetwork();
    void setUsersToGrid();
    void createNetworkConnection();
    void deletePreviousStations();

private:
    //! Time for step in ms
    static const int stepTime = 1000;

    //! Time to reload updates ability
    static const int trafficReloadTime = 8;
    static const int maxUsers = 12;
    static const int minUsers = 5;
    QTimer stepTimer;
    GameView *mView;
    QList<WorkStation *> mUsers;
    WorkStation *mAgent;
    WorkStation *mDevelopers;


    int mUsersCount;
    int mTimeForReload;

private slots:
    void stepTimerEvent();
};


