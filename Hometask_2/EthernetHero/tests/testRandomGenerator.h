#pragma once

#include <QtCore/QList>

#include "pseudoRandomGenerator.h"

class TestRandomGenerator : public PseudoRandomGenerator
{
public:
    TestRandomGenerator()
        : mCase(0)
    {
        mSequence << 0;    // computers count + 4

        for (int i = 0; i < 4; i++)
        {
            mSequence << i << 3 << 5;    // name, OS, bases
        }

        for (int i = 0; i < 14; i++)
        {
            mSequence << 0;    // connection
        }

        for (int i = 0; i < 15; i++)
        {
            mSequence << 0 << 0 << 0 << 0;    //bases actuality
            mSequence << 99 << 99 << 99;    //attack
        }
    }

    ~TestRandomGenerator(){}

    int rand()
    {
        int result = mSequence.at(mCase % mSequence.size());
        mCase++;
        if (mCase == INT_MAX - 1)
            mCase = 0;

        return result;
    }

private:
    QList<int> mSequence;
    int mCase;
};
