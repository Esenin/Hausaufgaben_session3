#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "testRandomGenerator.h"
#include "gameLogic.h"
#include "gameView.h"

class GameLogicTest : public QObject
{
    Q_OBJECT

public:
    GameLogicTest()
        : isPlaying(false)
    {
    }

public slots:
    void logInfected(QString name)
    {
        mInfected << name;
    }

    void startWayching()
    {
        isPlaying = true;
    }

    void stopWatching()
    {
        isPlaying = false;
    }

private:
    void connectComputers(QList<WorkStation *> stations)
    {
        foreach (WorkStation *station, stations)
        {
            connect(station, SIGNAL(infected(QString)), this, SLOT(logInfected(QString)));
        }
    }

    void makeTestNetwork(QList<WorkStation *> stations)
    {
        for (int i = 1; i < stations.size() - 1; i++)
        {
            stations.at(i)->disconnectAll();
            stations.at(i)->connectWith(stations.at(i + 1));
        }
    }

    GameView *mView;
    GameLogic *mLogic;
    TestRandomGenerator *mGenerator;
    QStringList mInfected;
    bool isPlaying;

private slots:
    void initTestCase()
    {
        mGenerator = new TestRandomGenerator();
        mView = new GameView();
        mLogic = new GameLogic(mView, mGenerator);
        connect(mLogic, SIGNAL(gameStarted()), this, SLOT(startWayching()));
        connect(mLogic, SIGNAL(gameWasOver()), this, SLOT(stopWatching()));
    }

    void greatInfectionSequenceTest()
    {
        mLogic->startGame();
        while (!isPlaying)
            QTest::qSleep(10);

        connectComputers(mLogic->workstations());
        makeTestNetwork(mLogic->workstations());

        while (mInfected.size() < 5)
        {
            mLogic->stepTimerEvent();
        }

        QStringList answers;
        answers << "obama" << "adam" << "Newton" << "Tesla" << "R&D server";

        for (int i = 0; i < answers.size(); i++)
            QCOMPARE(mInfected.at(i), answers.at(i));

        mLogic->stopGame();
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
