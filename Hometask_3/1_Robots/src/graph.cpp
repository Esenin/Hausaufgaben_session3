#include "graph.h"

Graph::Graph(QString const filename)
    : mVertexCount(-1)
{
    loadMatrixFromFile(filename);
    clearResult();
}

Graph::Graph(QStringList stringList)
    : mVertexCount(-1)
{
    setupMatrix(stringList);
    clearResult();
}

bool Graph::findMeetProbability()
{
    QList<int> used;
    foreach (int const start, mRobots)
    {
        used.clear();
        used.append(start);
        dfsModified(start, used);
    }

    return !mResult.contains(false);
}

void Graph::clearResult()
{
    for (int i = 0; i < mRobots.size(); i++)
        mResult.append(false);
}

void Graph::setupMatrix(QStringList stringList)
{
    bool hasFoundSize = false;
    int rowNum = 0;
    QList<int> buff;

    while (!stringList.isEmpty())
    {
        buff = parseLine(stringList.first().simplified());
        stringList.removeFirst();

        if (buff.size() == 0)
            continue;

        if (!hasFoundSize)
        {
            hasFoundSize = true;
            mVertexCount = buff.first();
            continue;
        }

        if (rowNum < mVertexCount)
        {
            mAdjacencyList.append(buff);
            rowNum++;
        }
        else
        {
            mRobots = buff;
            break;
        }
    }
}

void Graph::loadMatrixFromFile(QString const filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inputText(&file);
    QStringList buffer;
    while (!inputText.atEnd())
    {
        buffer << inputText.readLine();
    }
    file.close();
    setupMatrix(buffer);
}

QList<int> Graph::parseLine(QString const string) throw(InputError)
{
    if (string.size() == 0 || string[0] == QChar('#'))
        return QList<int>();

    QRegExp regExp("(\\d+)");
    QList<int> numList;

    int pos = 0;
    while ((pos = regExp.indexIn(string, pos)) != -1) {
         numList << regExp.cap(1).toInt();
         pos += regExp.matchedLength();

         if (mVertexCount >= 0 && numList.last() >= mVertexCount)
             throw(InputError());
     }

    return numList;
}

void Graph::dfsModified(int const startVertex, QList<int> used, int const deepLevel)
{
    if (deepLevel > 0 && (deepLevel % 2 == 0) && mRobots.contains(startVertex))
    {
        mResult[mRobots.indexOf(startVertex)] = true;
    }

    foreach (int const next, mAdjacencyList[startVertex])
    {
        if (used.contains(next))
            continue;
        used << next;
        dfsModified(next, used, deepLevel + 1);
        used.removeOne(next);
    }
}
