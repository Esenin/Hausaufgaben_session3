#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>

#include "workStation.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    void setItemToScene(QGraphicsItem *item);
    void drawLinks(WorkStation *start, QSet<WorkStation *> const connected);
    void showGameOverMsg();
    void clear();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void initGraphicsOutput();
    void setUsersToGrid();
    qreal calcPoolLevel(WorkStation const *first, WorkStation const *second) const;
    qreal calcPortXShift(WorkStation const *first, WorkStation const *second) const;

    void addLineToScene(QLineF line, QPen const &pen = QPen());

private:
    QGraphicsTextItem *mGameOverText;
    QGraphicsTextItem *mInfoMessage;
    QGraphicsTextItem *mScoreText;
    QGraphicsScene *mScene;
};

