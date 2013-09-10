#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    void setItemToScene(QGraphicsItem *item);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void initGraphicsOutput();
    void setUsersToGrid();

private:

    QGraphicsScene *mScene;
};

