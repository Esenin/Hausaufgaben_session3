#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "../src/arrayChecker.h"


class ArrayCheckerTest : public QObject
{
    Q_OBJECT

private:
    int *mArray;
    static int const size = 150;

private slots:
    void init()
    {
        mArray = new int[size];
    }

    void randomTest()
    {
        int answer = 0;
        for (int i = 0; i < size; i++)
        {
            int newElement = qrand() % INT_MAX;
            mArray[i] = newElement;
            if (newElement == 0)
                answer++;
        }

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.zerosCount(), answer);
    }

    void nonZerosTest()
    {
        for (int i = 0; i < size; i++)
            mArray[i] = i + 1;

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.zerosCount(), 0);
    }

    void oneZeroTest()
    {
        for (int i = 0; i < size; i++)
            mArray[i] = i + 1;

        mArray[size / 2] = 0;

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.zerosCount(), 1);
    }

    void cleanup()
    {
        delete mArray;
    }
};


