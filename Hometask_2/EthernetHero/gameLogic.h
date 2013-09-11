#pragma once

#include "gameView.h"
#include "workStation.h"

//! @class GameLogic provides action control and checks current game status
class GameLogic : public QObject
{
    Q_OBJECT
public:
    //! @arg viewport game field
    explicit GameLogic(GameView  *viewport);

public slots:
    void startGame();
    void stopGame();
    void startReloadTime();
    void gameOver();

signals:
    //! says its time to transfer information
    void newWorkingDay();
    void energyChanged(bool);

protected:
    //! starts new session and updates scores
    void makeNextMove();
    //! creates new workstations
    void setupNewComputers();
    //! set workstation to their right positions
    void setUsersToGrid();
    //! creates random connection between stations
    void createNetworkConnection();
    //! want to draw links
    void makeLinks();
    void deletePreviousStations();
    //! new viruses make databases not actual anymore
    void researchNewViruses();

    void updateScores();
    //! calculates new score rate at this step-session
    int scoresRate();
    void clearField();
    //! finds several random computers
    QSet<WorkStation *> findNewNeighbours(int const count, WorkStation *self);

private:
    //! Time for step in ms
    static const int stepTime = 1500;
    static int const maxUsers = 12;
    static int const minUsers = 4;
    //! connection ability for any computer
    static int const mainConnectionCount = 3;
    //! Time to reload updates ability
    int trafficReloadTime;
    QTimer stepTimer;
    GameView *mView;
    QList<WorkStation *> mUsers;
    //! starts infection
    WorkStation *mAgent;
    //! target for hackers
    WorkStation *mDevelopers;
    //! current scores
    unsigned int mScores;

    int mUsersCount;
    int mTimeForReload;

private slots:
    void stepTimerEvent();
};


