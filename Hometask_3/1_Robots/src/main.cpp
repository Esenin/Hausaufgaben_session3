#include <iostream>

#include "graph.h"

using namespace std;

int main()
{
    Graph graph("://data.txt");
    cout << "result: "
            << ((graph.findMeetProbability())? "We've killed all robots" : "Some robots still alive")
            << endl;
    return 0;
}

