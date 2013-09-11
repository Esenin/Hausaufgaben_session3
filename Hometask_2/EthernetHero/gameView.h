#pragma once

#include <QtWidgets/QGraphicsView>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtGui/QMouseEvent>

#include "workStation.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    //! sets item higher than default
    void setItemToScene(QGraphicsItem *item);
    //! draw links between @arg start and @arg connected stations
    void drawLinks(WorkStation *start, QSet<WorkStation *> const connected);
    void showGameOverMsg();
    //! deletes links from scene
    void clear();
    void setScoresText(QString const scoresText);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void initGraphicsOutput();
    //! @return Y-coord of common communication pool
    qreal calcPoolLevel(WorkStation const *first, WorkStation const *second) const;
    //! @returns X-shift of station's port, depends on distance between computers
    qreal calcPortXShift(WorkStation const *first, WorkStation const *second) const;

private:
    QGraphicsTextItem *mGameOverText;
    QGraphicsTextItem *mInfoMessage;
    QGraphicsTextItem *mScoreText;
    QGraphicsScene *mScene;
};

