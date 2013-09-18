#pragma once

#include <QtCore/QTime>

#include "pseudoRandomGenerator.h"

class LiveRandomGenerator : public PseudoRandomGenerator
{
public:
    LiveRandomGenerator()
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    }

    int rand()
    {
        return qrand();
    }
};
