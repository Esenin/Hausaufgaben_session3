#pragma once

#include <QtCore/QObject>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QDebug>


class Graph : public QObject
{
    Q_OBJECT
public:class InputError{};
    explicit Graph(QString const filename);
    bool findMeetProbability();

protected:
    void loadMatrixFromFile(QString const filename);
    QList<int> parseLine(QString const string) throw(InputError);
    void dfsModified(int const startVertex, QList<int> used, int const deepLevel = 0);

private:
    QList<QList<int> > mAdjacencyList;
    QList<int> mRobots;
    QList<bool> mResult;
    int mVertexCount;

};


