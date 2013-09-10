#pragma once

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QSet>
#include <QDebug>

enum StationType
{
    hacker = 0
    , user
    , target
};


class WorkStation : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit WorkStation(StationType const stationType = user);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF incomingPort() const;
    QPointF portPos() const;

    void decBases(int const outdated);
    void connectWith(WorkStation *station);
    void connectWith(QSet<WorkStation *> const list);
    QSet<WorkStation *> connected() const;

    QString name();


public slots:
    void energyChange(bool const canUpdate);
    void dataTransfer();

signals:
    void updated();
    void secretDepartInfected();

protected:
    enum OperationSystems
    {
        backTrack = 1
        ,debian
        ,ubuntu
        ,windows7
        ,winXP
    };
    void loadFromFile(QStringList* list);
    void initSocialPos(StationType const stationType);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void getVirus();
    int calcDefenceRate(OperationSystems const osType, int const basesRate);

private:
    OperationSystems mOperationSystem;
    StationType mStationType;
    qreal mBasesActuality;
    bool mInfected;
    QString mName;
    QRectF mBoundingRect;
    QPointF mPort;
    bool mCouldBeUpdated;
    bool mSkipOneDay;
    QSet<WorkStation *> mConnected;
};


