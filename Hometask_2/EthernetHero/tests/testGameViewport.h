#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtCore/QObject>
#include <QtTest/QTest>

#include "gameView.h"

class GameViewportTest : public QObject
{
    Q_OBJECT

private:
    GameView *mView;

private slots:
    void initTestCase()
    {
        mView = new GameView();
    }

    void addItemTest()
    {
        QGraphicsLineItem *item = new QGraphicsLineItem();
        mView->setItemToScene(item);
        QVERIFY(mView->items().indexOf(item) > -1);
    }

    void cleanupTestCase()
    {
        delete mView;
    }
};
