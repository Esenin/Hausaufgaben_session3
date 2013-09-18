#pragma once

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QRegExp>

//!
//! \brief The Graph class
//! container of graph due adjacency list
class Graph
{
public:
    class InputError{};

    //!
    //! \brief Graph
    //! \param filename file must be formated as in example
    explicit Graph(QString const filename);
    //!
    //! \brief Graph
    //! \param stringList text must be formated as in example file
    Graph(QStringList stringList);
    //!
    //! \brief findMeetProbability
    //! \return  "true" in case all robots can blow up, "false" otherwise
    bool findMeetProbability();

protected:
    void clearResult();
    void loadMatrixFromFile(QString const filename);
    void setupMatrix(QStringList stringList);
    //!
    //! \brief parseLine
    //! \return list of numbers from string
    QList<int> parseLine(QString const string) throw(InputError);
    //!
    //! \brief dfsModified
    //! finds robots path decomposition from fix point of view
    void dfsModified(int const startVertex, QList<int> used, int const deepLevel = 0);
    void correction(int &even, int &odd);

private:
    static int const evenBit = 1;
    static int const oddBit = 2;
    QList<QList<int> > mAdjacencyList;
    QList<int> mRobots;
    QList<char> mRobotsDecomposition;
    int mVertexCount;
};
