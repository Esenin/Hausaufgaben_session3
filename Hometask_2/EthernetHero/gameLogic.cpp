#include "gameLogic.h"

GameLogic::GameLogic()
{
}

void GameLogic::loadNewUsers(QList<WorkStation *> const users)
{
    mUsers = users;
}

void GameLogic::makeNextMove()
{
    researchNewViruses();
}

void GameLogic::researchNewViruses() const
{
    int const maxVirusesPercentage = 8;
    for (int i = 0; i < mUsers.count(); i++)
    {
        mUsers.at(i)->decBases(qrand() % maxVirusesPercentage);
    }
}
