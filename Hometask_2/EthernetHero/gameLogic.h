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
    void gameOver();

signals:
    void newWorkingDay();
    void energyChanged(bool);

protected:
    void researchNewViruses();
    void setupNewComputers();
    void setUsersToGrid();
    void createNetworkConnection();
    void deletePreviousStations();
    QSet<WorkStation *> getNeighbours(int const count, WorkStation *self);
    void makeLinks();


private:
    //! Time for step in ms
    static const int stepTime = 1500;

    //! Time to reload updates ability
    static int const trafficReloadTime = 1;
    static int const maxUsers = 6;
    static int const minUsers = 4;
    static int const mainConnectionCount = 3;
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


