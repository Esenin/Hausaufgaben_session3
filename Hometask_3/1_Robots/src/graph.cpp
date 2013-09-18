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

    used.append(mRobots.first());
    dfsModified(mRobots.first(), used);

    int even = 0;
    int odd = 0;
    foreach (int const configuration, mResult)
    {
        even += configuration & evenBit;
        odd += (configuration & oddBit) / 2;
    }
    correction(even, odd);
    return (even != 1) && (odd != 1);
}

void Graph::clearResult()
{
    mResult.clear();
    for (int i = 0; i < mRobots.size(); i++)
    {
        mResult.append(0);
    }
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
    if (mRobots.contains(startVertex))
    {
        int const resultIndex = mRobots.indexOf(startVertex);
        if (deepLevel % 2 == 0)
        {
            if ((mResult[resultIndex] & evenBit) == 0)
                mResult[resultIndex] = mResult[resultIndex] | evenBit;
        }
        else
        {
            if ((mResult[resultIndex] & oddBit) == 0)
                mResult[resultIndex] = mResult[resultIndex] | oddBit;
        }
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

void Graph::correction(int &even, int &odd)
{
    if (even != 1 && odd != 1)
        return;

    foreach (int const config, mResult)
    {
        if ((even == 1) && (config & evenBit))
        {
            if ((config) & (oddBit))
                even--;
            break;
        }
        if ((odd == 1) && (config & oddBit))
        {
            if ((config) & (evenBit))
                odd--;
            break;
        }
    }
}
