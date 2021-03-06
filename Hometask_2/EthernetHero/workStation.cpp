#include "workStation.h"

using namespace stations;

WorkStation::WorkStation(PseudoRandomGenerator *generator, stations::StationType const stationType)
    : mGenerator(generator)
    , mStationType(stationType)
    , mBoundingRect(QRectF(0,0, 100, 160))
    , mCouldBeUpdated(true)
    , mSkipOneDay(false)
{
    initSocialPos(stationType);
    mConnected.clear();
    mPort = mBoundingRect.center();
}

QRectF WorkStation::boundingRect() const
{
    return mBoundingRect;
}

void WorkStation::paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget)
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
    painter->drawText(xPos, yPos, QString("OS: " + osNames.at(mOperationSystem - backTrack)));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPointF WorkStation::portPos() const
{
    return mapToScene(mPort);
}

void WorkStation::decBases(const int outdated)
{
    if (mBasesActuality - outdated < 0)
        return;
    mBasesActuality -= outdated;
    update(mBoundingRect);
}

void WorkStation::connectWith(WorkStation *station)
{
    mConnected << station;
}

void WorkStation::connectWith(QSet<WorkStation *> const list)
{
    foreach (WorkStation *station, list)
    {
        mConnected << station;
        station->connectWith(this);
    }
}

void WorkStation::disconnectAll()
{
    mConnected.clear();
}

QSet<WorkStation *> WorkStation::connected() const
{
    return mConnected;
}

bool WorkStation::isInfected() const
{
    return mInfected;
}

int WorkStation::basesActuality() const
{
    return mBasesActuality;
}

QString WorkStation::name() const
{
    return mName;
}

void WorkStation::energyChange(const bool canUpdate)
{
    mCouldBeUpdated = canUpdate;
}

void WorkStation::dataTransfer()
{
    if (!mInfected)
        return;

    if (mSkipOneDay)
    {
        mSkipOneDay = false;
        return;
    }

    int const damagePerAttak = 1;
    foreach (WorkStation *station, mConnected)
    {
        int const attackPerfomance = mGenerator->rand() % 100;
        if (attackPerfomance > calcDefenceRate(station->mOperationSystem, station->mBasesActuality))
            station->getVirus();
        else
            station->decBases(damagePerAttak);
    }
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
    if (mName.size() > 0)
        return;

    int const osCount = 4;

    QStringList nameList;
    loadFromFile(&nameList);
    mName = nameList.at(mGenerator->rand() % nameList.size());
    mOperationSystem = (OperationSystems) ((mGenerator->rand() % osCount) + debian);
    mBasesActuality = 100 - (mGenerator->rand() % 10);
    mInfected = false;
}

void WorkStation::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
    if (!mCouldBeUpdated || mStationType != user)
        return;

    mInfected = false;
    mBasesActuality = 99;
    update(mBoundingRect);
    emit updated();
}

void WorkStation::getVirus()
{
    if (mInfected)
        return;

    if (mName == "R&D server") // only R&D departmant
        emit secretDepartInfected();

    mInfected = true;
    mSkipOneDay = true;
    mBasesActuality = 0;
    emit infected(mName);
    update(mBoundingRect);
}

int WorkStation::calcDefenceRate(const WorkStation::OperationSystems osType, const int basesRate)
{
    int const maxOSDefence = 97;
    qreal const maxOS = (double) 1 / debian;
    qreal const osDefenceRate = ((double) 1 / osType) * maxOSDefence / maxOS;
    return (int) ((2 * basesRate + osDefenceRate) / 3);
}
