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
    void setupNewComputers();
    void setUsersToGrid();
    void createNetworkConnection();
    void makeLinks();
    void deletePreviousStations();
    void researchNewViruses();
    void addScores();
    int scoresRate();
    void clearField();
    QSet<WorkStation *> getNeighbours(int const count, WorkStation *self);



private:
    //! Time for step in ms
    static const int stepTime = 1500;

    static int const maxUsers = 12;
    static int const minUsers = 4;
    static int const mainConnectionCount = 3;
    //! Time to reload updates ability
    int trafficReloadTime;
    QTimer stepTimer;
    GameView *mView;
    QList<WorkStation *> mUsers;
    WorkStation *mAgent;
    WorkStation *mDevelopers;
    unsigned int mScores;


    int mUsersCount;
    int mTimeForReload;

private slots:
    void stepTimerEvent();
};


