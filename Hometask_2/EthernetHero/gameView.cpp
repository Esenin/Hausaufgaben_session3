#include "gameView.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    initGraphicsOutput();
}

void GameView::startGame()
{

}

void GameView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF sceneRect = this->sceneRect();
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::darkGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::NoPen);
    painter->drawRect(sceneRect);

}

void GameView::resizeEvent(QResizeEvent *event)
{
    qreal const accuracy = 0.98;
    QMatrix defaultMatrix;
    setMatrix(defaultMatrix);
    scale((rect().width() / mScene->width()) * accuracy
                , (rect().height() / mScene->height()) * accuracy);
    Q_UNUSED(event);
}

void GameView::initGraphicsOutput()
{
    mScene = new QGraphicsScene(this);
    mScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    mScene->setSceneRect(-220, -20, 1340, 980);
    setScene(mScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(960, 520);



    setWindowTitle("EthernetHero the Game");

//    catapult = new GunMachine;
//    mScene->addItem(catapult);
//    catapult->setPos(catapultPosition);

//    QString helpInfo = QString("Control:\n Left-right arrows to change gun power\n") +
//            QString(" Up-down to change gun angle\n And spacebar to shoot\n 'God' Luck!");
//    infoMessage = new QGraphicsTextItem(helpInfo);
//    infoMessage->setFont(QFont("Arial", 10));
//    mScene->addItem(infoMessage);
//    infoMessage->setPos(mScene->sceneRect().topLeft());
}

void GameView::stepTimerEvent()
{

}
