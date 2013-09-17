#include "test/testArrayChecker.h"

int main()
{
    ArrayCheckerTest test;
    QTest::qExec(&test);
    return 0;
}

