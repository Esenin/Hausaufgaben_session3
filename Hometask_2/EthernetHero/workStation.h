#pragma once

#include <QGraphicsItem>
#include <QFile>

enum StationType
{
    hacker = 0
    , user
    , target
};


class WorkStation : public QGraphicsItem
{
public:
    explicit WorkStation(StationType const stationType = 1);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void loadFromFile(QStringList* list);

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
    qreal mBasesActuality;
    bool mInfected;
    QString mName;
};


