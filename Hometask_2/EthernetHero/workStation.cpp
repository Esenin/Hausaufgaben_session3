#include "workStation.h"



WorkStation::WorkStation(StationType const stationType)
{
    switch (stationType) {
    case hacker:
    {
        mName = "Double Agent";
        mOperationSystem = backTrack;
        mBasesActuality = 0;
        mInfected = true;
        break;
    }
    case target:
    {
        mName = "R&D department";
        mOperationSystem = debian;
        mBasesActuality = 100;
        mInfected = false;
        break;
    }
    default:
        break;
    }
    if (mName.size() != 0)
        return;

    QStringList nameList;


}

QRectF WorkStation::boundingRect() const
{

}

void WorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void WorkStation::loadFromFile(QStringList *list)
{
    QFile namesFile()


}
