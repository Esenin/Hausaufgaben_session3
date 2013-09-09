#pragma once

#include "workStation.h"

class GameLogic
{
public:
    explicit GameLogic();
    void loadNewUsers(QList<WorkStation *> const users);

    void makeNextMove();

protected:
    void researchNewViruses() const;

private:
    QList<WorkStation *> mUsers;
};


