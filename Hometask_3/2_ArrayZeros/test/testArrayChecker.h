#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "arrayChecker.h"


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
        bool result = false;
        for (int i = 0; i < size; i++)
        {
            int newElement = qrand() % INT_MAX;
            mArray[i] = newElement;
            if (newElement == 0)
                result = true;
        }

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.hasZeros(), result);
    }

    void nonZerosTest()
    {
        for (int i = 0; i < size; i++)
            mArray[i] = i + 1;

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.hasZeros(), false);
    }

    void zerosTest()
    {
        for (int i = 0; i < size; i++)
            mArray[i] = i + 1;

        mArray[size / 2] = 0;

        ArrayChecker<int> checker(mArray, size);
        QCOMPARE(checker.hasZeros(), true);
    }

    void cleanup()
    {
        delete mArray;
    }
};


