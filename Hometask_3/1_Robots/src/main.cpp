#include <iostream>
#include <QtTest/QTest>

#include "test/testPack.h"

using std::cout;
using std::endl;

void tryUserTest()
{
    cout << "Processing 'input.txt'...\n";
    try
    {
        Graph graph("://input.txt");
        cout << "\nresult: "
                << ((graph.findMeetProbability())? "We've killed all robots" : "Some robots still alive")
                << endl;
    }
    catch(Graph::InputError)
    {
        cout << "graph in file is incorrect. Repair it and try again\n";
    }
}

int main()
{
    GraphProblemTest test;
    QTest::qExec(&test);

    tryUserTest();

    return 0;
}

