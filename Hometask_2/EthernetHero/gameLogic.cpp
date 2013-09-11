#include "gameLogic.h"

GameLogic::GameLogic(GameView *viewport)
    : mView(viewport)
    , mAgent(NULL)
    , mDevelopers(NULL)
    , mUsersCount(0)
    , mTimeForReload(0)
    , trafficReloadTime(1)
    , mScores(0)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    connect(&stepTimer, SIGNAL(timeout()), this, SLOT(stepTimerEvent()));
}

void GameLogic::setupNewComputers()
{
    QRectF const scene = mView->sceneRect();
    mAgent = new WorkStation(hacker);
    mView->setItemToScene(mAgent);
    mAgent->setPos(scene.left() + 10, scene.center().y());
    connect(this, SIGNAL(newWorkingDay()), mAgent, SLOT(dataTransfer()));

    mDevelopers = new WorkStation(target);
    mView->setItemToScene(mDevelopers);
    mDevelopers->setPos(scene.right() - 110, scene.center().y());
    connect(mDevelopers, SIGNAL(secretDepartInfected()), this, SLOT(gameOver()));

    mUsersCount = (qrand() % (maxUsers - minUsers + 1)) + minUsers;
    for (int i = 0; i < mUsersCount; i++)
    {
        WorkStation *newStation = new WorkStation();
        mView->setItemToScene(newStation);
        mUsers.append(newStation);
        connect(this, SIGNAL(newWorkingDay()), newStation, SLOT(dataTransfer()));

        // dbl click event filter doesnt work on graphicsview items
        connect(this, SIGNAL(energyChanged(bool)), newStation, SLOT(energyChange(bool)));
        connect(newStation, SIGNAL(updated()), this, SLOT(setReloadTime()));
    }

    trafficReloadTime = (mUsersCount < maxUsers / 2)? 2 : 1;
}

void GameLogic::setUsersToGrid()
{
    int const hSpace = 70;
    int const vSpace = 100;
    qreal xPos = 0;
    qreal yPos = 0;
    foreach (WorkStation *station, mUsers)
    {
        station->setPos(xPos, yPos);

        xPos += station->boundingRect().width() + hSpace;
        if (xPos > mDevelopers->x() - station->boundingRect().width())
        {
            xPos = 0;
            yPos += station->boundingRect().height() + vSpace;
        }
    }
}

void GameLogic::createNetworkConnection()
{
    QSet<WorkStation *> neighbours = getNeighbours(mainConnectionCount, mAgent);
    mAgent->connectWith(neighbours);

    neighbours = getNeighbours(mainConnectionCount, mDevelopers);
    mDevelopers->connectWith(neighbours);

    foreach (WorkStation *station, mUsers)
    {
        neighbours = getNeighbours(mainConnectionCount - 1, station);
        station->connectWith(neighbours);
    }
}

void GameLogic::deletePreviousStations()
{
    foreach (WorkStation *station, mUsers)
    {
        delete station;
    }
    mUsers.clear();
}

QSet<WorkStation *> GameLogic::getNeighbours(int const count, WorkStation *self)
{
    QList<WorkStation *> computers = mUsers;
    QSet<WorkStation *> result;
    while (result.size() < count)
    {
        WorkStation* const station = computers.at(qrand() % computers.size());
        if (station != self)
            result << station;
    }
    return result;
}

void GameLogic::makeLinks()
{
    foreach (WorkStation *station, mUsers)
    {
        mView->drawLinks(station, station->connected());
    }
}

void GameLogic::makeNextMove()
{
    researchNewViruses();
    addScores();
    emit newWorkingDay();
}

void GameLogic::startGame()
{
    clearField();
    mScores = 0;
    setupNewComputers();
    setUsersToGrid();
    createNetworkConnection();
    makeLinks();
    stepTimer.start(stepTime);
}

void GameLogic::stopGame()
{
    stepTimer.stop();
}

void GameLogic::setReloadTime()
{
    mTimeForReload = trafficReloadTime;
    emit energyChanged(false);
}

void GameLogic::gameOver()
{
    stopGame();
    mView->showGameOverMsg();
}

void GameLogic::researchNewViruses()
{
    int const maxVirusesPercentage = 4;
    for (int i = 0; i < mUsers.count(); i++)
    {
        mUsers.at(i)->decBases(qrand() % maxVirusesPercentage);
    }
}

void GameLogic::addScores()
{
    int const newRoundRate = scoresRate();
    mScores += newRoundRate;
    QString scoresText = "Scores per step: " + QString::number(newRoundRate)
            + "\nTotal scores: " + QString::number(mScores)
            + "\nReloading time: " + QString::number(trafficReloadTime) + " steps!";
    mView->setScoresText(scoresText);
}

int GameLogic::scoresRate()
{
    int const maxActuality = 100;
    bool noInfected = true;
    int rate = 0;
    foreach (WorkStation *station, mUsers)
    {
        if (station->isInfected())
            noInfected = false;
        rate += (maxActuality - station->basesActuality()) / 2;
    }
    rate += (maxActuality - mDevelopers->basesActuality()) * 2;
    if (noInfected)
        rate += 5 * maxActuality;

    return rate;
}

void GameLogic::clearField()
{
    if (mAgent)
    {
        delete mAgent;
        delete mDevelopers;
        deletePreviousStations();

    }
    mView->clear();
}

void GameLogic::stepTimerEvent()
{
    makeNextMove();
    if (mTimeForReload)
    {
        mTimeForReload--;
        if (mTimeForReload == 0)
            emit energyChanged(true);
    }
}

