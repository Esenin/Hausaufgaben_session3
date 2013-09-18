#pragma once

#include <QtCore/QObject>
#include <QtTest/QTest>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

#include "../src/graph.h"

//!
//! \brief The GameViewportTest class
//! runs Graph on all tests in data file
class GraphProblemTest : public QObject
{
    Q_OBJECT
private:
    bool tryTest(QStringList &list)
    {
        bool result = false;
        try
        {
            Graph testGraph(list);
            result = testGraph.findMeetProbability();
        }
        catch (Graph::InputError)
        {
            qDebug() << "incorrect input";
        }
        return result;
    }

private slots:
    void allTestPack()
    {
        QFile file("://data.txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream mStream(&file);

        Q_ASSERT(!mStream.atEnd());
        QString line;

        do
        {
            line.clear();
            QStringList singleTestList;
            do
            {
                line = mStream.readLine().simplified();
                if (line.size() != 0 && line[0] != '#')
                    singleTestList << line;
            }
            while(!line.contains("_"));
            QCOMPARE(tryTest(singleTestList), (line.toLower().contains("true")));
        }
        while (!line.contains("EOTestPack"));
        file.close();
    }
};
