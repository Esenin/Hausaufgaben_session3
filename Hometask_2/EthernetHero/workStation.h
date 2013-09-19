#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QPainter>
#include <QtCore/QSet>

#include "pseudoRandomGenerator.h"

namespace stations
{
enum StationType
{
    hacker = 0
    , user
    , target
};
}

//! @class WorkStation is model of desktop workstation in local network
class WorkStation : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit WorkStation(PseudoRandomGenerator *generator, stations::StationType const stationType = stations::user);

    QRectF boundingRect() const;
    void paint(QPainter *painter, QStyleOptionGraphicsItem const *option, QWidget *widget);
    //! on-scene position of station's incoming,outcoming port
    QPointF portPos() const;

    //! decrease database actuality
    void decBases(int const outdated);
    //! feedback-connection
    void connectWith(WorkStation *station);
    //! connects this station with @arg list stations
    void connectWith(QSet<WorkStation *> const list);
    //! drops all connections
    void disconnectAll();

    QSet<WorkStation *> connected() const;
    bool isInfected() const;
    int basesActuality() const;
    QString name() const;

public slots:
    void energyChange(bool const canUpdate);
    void dataTransfer();

signals:
    void updated();
    void infected(QString name);
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
    //! configures stations params
    void initSocialPos(stations::StationType const stationType);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //! makes station infected
    void getVirus();
    int calcDefenceRate(OperationSystems const osType, int const basesRate);

private:
    PseudoRandomGenerator *mGenerator;
    OperationSystems mOperationSystem;
    stations::StationType mStationType;
    int mBasesActuality;
    bool mInfected;
    QString mName;
    QRectF mBoundingRect;
    QPointF mPort;
    bool mCouldBeUpdated;
    bool mSkipOneDay;
    QSet<WorkStation *> mConnected;
};


