#include "gameLogic.h"

GameLogic::GameLogic(GameView *viewport)
    : mView(viewport)
    , mAgent(NULL)
    , mDevelopers(NULL)
    , mUsersCount(0)
    , mTimeForReload(0)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    connect(&stepTimer, SIGNAL(timeout()), this, SLOT(stepTimerEvent()));
}

void GameLogic::setupNewNetwork()
{
    if (mAgent)
    {
        delete mAgent;
        delete mDevelopers;
        deletePreviousStations();
    }
    QRectF const scene = mView->sceneRect();
    mAgent = new WorkStation(hacker);
    mView->setItemToScene(mAgent);
    mAgent->setPos(scene.left() + 10, scene.center().y());

    mDevelopers = new WorkStation(target);
    mView->setItemToScene(mDevelopers);
    mDevelopers->setPos(scene.right() - 110, scene.center().y());

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

    setUsersToGrid();
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

    qDebug() << "deployed to grid";
}

void GameLogic::createNetworkConnection()
{

}

void GameLogic::deletePreviousStations()
{
    foreach (WorkStation *station, mUsers)
    {
        delete station;
    }
    mUsers.clear();
}

void GameLogic::makeNextMove()
{
    researchNewViruses();
    emit newWorkingDay();
}

void GameLogic::startGame()
{
    qDebug() << "start new session";
    setupNewNetwork();
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

void GameLogic::researchNewViruses()
{
    int const maxVirusesPercentage = 8;
    for (int i = 0; i < mUsers.count(); i++)
    {
        mUsers.at(i)->decBases(qrand() % maxVirusesPercentage);
    }
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

