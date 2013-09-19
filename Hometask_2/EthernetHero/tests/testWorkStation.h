#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>

#include "liveRandGenerator.h"
#include "workStation.h"

class WorkStationTest : public QObject
{
    Q_OBJECT

private:
    LiveRandomGenerator *mGenerator;
    WorkStation *mStation;
    WorkStation *mMainServer;

private slots:
    void initTestCase()
    {
        mGenerator = new LiveRandomGenerator();
        mStation = new WorkStation(mGenerator);
        mMainServer = new WorkStation(mGenerator, stations::target);
        QVERIFY(mStation != 0 && mMainServer != 0);
    }

    void antivirusBasesTest()
    {
        int const startBasesLevel = mStation->basesActuality();
        mStation->decBases(1);
        QCOMPARE(startBasesLevel - 1, mStation->basesActuality());
    }

    void hasNameTest()
    {
        QVERIFY(mStation->name().size() > 0);
    }

    void connectionTest()
    {
        QSet<WorkStation *> set;
        set << mStation;
        mMainServer->connectWith(set);
        QCOMPARE(mStation->connected().size(), 1);
    }

    void cleanupTestCase()
    {
        delete mStation;
        delete mMainServer;
        delete mGenerator;
    }
};


