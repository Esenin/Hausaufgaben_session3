#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "testRandomGenerator.h"
#include "gameLogic.h"
#include "gameView.h"

class GameLogicTest : public QObject
{
    Q_OBJECT

private:
    GameView *mView;
    GameLogic *mLogic;
    TestRandomGenerator *mGenerator;

private slots:
    void initTestCase()
    {
        mGenerator = new TestRandomGenerator();
        mView = new GameView();
        mLogic = new GameLogic(mView, mGenerator);
    }

    void commonTest()
    {
        mLogic->startGame();
        QVERIFY(mView->items().size() > 0);
    }

    void newGameTest()
    {
        bool flag = false;
        int itemsCount = -1;
        for (int i = 0; i < 10; i++)
        {
            if (itemsCount < 0)
                itemsCount = mView->items().size();
            mLogic->stopGame();
            mLogic->startGame();
            if (itemsCount != mView->items().size())
                flag = true;
        }

        QVERIFY(flag);
    }

    void cleanupTestCase()
    {
        mLogic->stopGame();
        delete mLogic;
        delete mView;
        delete mGenerator;
    }
};
