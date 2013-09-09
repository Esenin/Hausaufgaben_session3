#include "workStation.h"



WorkStation::WorkStation(StationType const stationType)
    : mBoundingRect(QRectF(0,0, 100, 160))
    , mCouldBeUpdated(true)
    , mStationType(stationType)
{
    initSocialPos(stationType);
}

QRectF WorkStation::boundingRect() const
{
    return mBoundingRect;
}

void WorkStation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = mBoundingRect;
    painter->fillRect(bounds, (mInfected)? Qt::red : Qt::yellow);
    painter->drawRect(bounds);

    QImage face;
    if (mOperationSystem <= ubuntu)
    {
        face = (mInfected)? QImage("://res/linux_pwd.png") : QImage("://res/linux.png");
    }
    else
    {
        face = (mInfected)? QImage("://res/windows_pwd.png") : QImage("://res/windows.png");
    }

    painter->drawImage(0, 0, face);

    int const shiftPx = 10;
    int const fontSize = 11;
    qreal const xPos = 2;
    qreal yPos = face.height() + shiftPx;
    painter->setFont(QFont("Tahoma", fontSize));

    painter->drawText(xPos, yPos, mName);
    yPos += fontSize + shiftPx;

    painter->drawText(xPos, yPos, QString("Antivirus data"));
    yPos += fontSize + shiftPx;

    painter->drawText(xPos, yPos, QString("actuality:" + QString::number(mBasesActuality) + "%"));
    yPos += fontSize + shiftPx;

    QStringList osNames;
    osNames << "backTrack" << "debian" << "ubuntu" << "windows7" << "winXP";
    painter->drawText(xPos, yPos, QString("OS: " + osNames.at(mOperationSystem)));
}

QPointF WorkStation::incomingPort() const
{
    return QPointF(pos().x() + mBoundingRect.width() / 2, pos().y());
}

QPointF WorkStation::outcomingPort() const
{
    return QPointF(pos().x() + mBoundingRect.width() / 2, pos().y() + mBoundingRect.height());
}

void WorkStation::decBases(const int outdated)
{
    if (mBasesActuality - outdated < 0)
        return;
    mBasesActuality -= outdated;
    update(mBoundingRect);
}

void WorkStation::energyChange(const bool canUpdate)
{
    mCouldBeUpdated = canUpdate;
}



void WorkStation::loadFromFile(QStringList *list)
{
    QFile namesFile("://res/names.list");
    namesFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textStream(&namesFile);
    QString curName = textStream.readLine();
    while(!curName.isNull())
    {
        list->append(curName);
        curName = textStream.readLine();
    }

    namesFile.close();
}

void WorkStation::initSocialPos(const StationType stationType)
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
        mName = "R&D server";
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

    int const osCount = 4;

    QStringList nameList;
    loadFromFile(&nameList);
    mName = nameList.at(qrand() % nameList.size());
    mOperationSystem = (OperationSystems) ((qrand() % osCount) + 1);
    mBasesActuality = 99 - (qrand() % 20);
    mInfected = false;
}

void WorkStation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    if (!mCouldBeUpdated || mStationType != user)
        return;

    mInfected = false;
    mBasesActuality = 99;
    this->update(mBoundingRect);
}
