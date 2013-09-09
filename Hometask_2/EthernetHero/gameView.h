#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QDebug>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);


public slots:
    void startGame();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void initGraphicsOutput();

private:
    QTimer stepTimer;
    QGraphicsScene *mScene;

private slots:
    void stepTimerEvent();


};

