#pragma once

#include <QGraphicsItem>
#include <QFile>
#include <QTextStream>
#include <QPainter>

enum StationType
{
    hacker = 0
    , user
    , target
};


class WorkStation : public QGraphicsItem
{
public:
    explicit WorkStation(StationType const stationType = user);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPointF incomingPort() const;
    QPointF outcomingPort() const;

    void decBases(int const outdated);


public slots:
    void energyChange(bool const canUpdate);

protected:
    void loadFromFile(QStringList* list);
    void initSocialPos(StationType const stationType);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    enum OperationSystems
    {
        backTrack = 0
        ,debian
        ,ubuntu
        ,windows7
        ,winXP
    };

    OperationSystems mOperationSystem;
    StationType mStationType;
    qreal mBasesActuality;
    bool mInfected;
    QString mName;
    QRectF mBoundingRect;
    bool mCouldBeUpdated;
};


