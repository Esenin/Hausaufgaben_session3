#pragma once

#include <QtCore/QList>
#include <QDebug>

#include "pseudoRandomGenerator.h"

class TestRandomGenerator : public PseudoRandomGenerator
{
public:
    TestRandomGenerator()
        : mCase(0)
    {
        mSequence << 0;
        for (int i = 0; i < 5; i++)
        {
            mSequence << 0 << 1 << 2;
        }

        for (int i = 0; i < 100; i++)
            mSequence << 99;
    }

    ~TestRandomGenerator(){}

    int rand()
    {
        int result = mSequence.at(mCase % mSequence.size());
        mCase++;
        if (mCase == INT_MAX - 1)
            mCase = 0;

        qDebug() << result;
        return result;
    }

private:
    QList<int> mSequence;
    int mCase;
};
