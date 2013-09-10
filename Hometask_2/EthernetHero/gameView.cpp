#include "gameView.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    initGraphicsOutput();
}

void GameView::setItemToScene(QGraphicsItem *item)
{
    mScene->addItem(item);
    item->setZValue(item->zValue() + 1);
}

void GameView::drawLinks(WorkStation *start, QSet<WorkStation *> const connected)
{
    QPen color(Qt::yellow);
    foreach (WorkStation *station, connected)
    {
        if (start->pos().y() != station->pos().y())
        {
            QLineF link(start->portPos(), station->portPos());
            mScene->addLine(link, color);
            continue;
        }

        WorkStation const *leftSide = (start->pos().x() < station->pos().x())? start : station;
        WorkStation const *rightSide = (station == leftSide)? start : station;
        qreal curPool = calcPoolLevel(leftSide, rightSide);
        qreal horShift = calcPortXShift(leftSide, rightSide);
        QPointF startPoint(leftSide->portPos().x() + horShift, leftSide->portPos().y());
        QPointF finishPoint(rightSide->portPos().x() - horShift, rightSide->portPos().y());


        QLineF toPool(startPoint, QPointF(startPoint.x(), curPool));
        QLineF horizontPool(toPool.p2(), QPointF(finishPoint.x(), curPool));
        QLineF toTarget(horizontPool.p2(), finishPoint);

        mScene->addLine(toPool);
        mScene->addLine(horizontPool);
        mScene->addLine(toTarget);
    }
}

void GameView::showGameOverMsg()
{
    mScene->addItem(mGameOverText);
}

void GameView::clear()
{
    foreach (QGraphicsItem *item, mScene->items())
    {
        QGraphicsLineItem *curLine = qgraphicsitem_cast<QGraphicsLineItem *>(item);
        if (curLine == NULL) {
            continue;
        }
        mScene->removeItem(curLine);
    }
    mScene->removeItem(mGameOverText);
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
    scale((rect().width() / mScene->width()) * accuracy, (rect().height() / mScene->height()) * accuracy);
    Q_UNUSED(event);
}

void GameView::initGraphicsOutput()
{
    mScene = new QGraphicsScene(this);
    mScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    mScene->setSceneRect(-220, -100, 1340, 600);
    setScene(mScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(960, 520);

    mGameOverText = new QGraphicsTextItem("Game Over! \nYou can restart game by pressing Esc");
    mGameOverText->setFont(QFont("Tahoma"));
    mGameOverText->setPos(mScene->sceneRect().center());

    QString helpInfo = QString("Prevent hackers attack to main server!\n") +
            QString("Use mouse double click to heal computer!\n 'God' Luck!");
    mInfoMessage = new QGraphicsTextItem(helpInfo);
    mInfoMessage->setFont(QFont("Tahoma", 10));
    mScene->addItem(mInfoMessage);
    mInfoMessage->setPos(mScene->sceneRect().topLeft());
}

qreal GameView::calcPoolLevel(WorkStation const *first, WorkStation const *second) const
{
    int const stepPx = 10;
    qreal const shift = second->pos().x() / (first->pos().x() + first->boundingRect().width());
    qreal const startPoolHeight = mScene->sceneRect().center().y() - stepPx;
    return startPoolHeight + stepPx * shift;

}

qreal GameView::calcPortXShift(WorkStation const *first, WorkStation const *second) const
{
    int const shiftStep = 5;
    qreal const shift = second->pos().x() / (first->pos().x() + first->boundingRect().width());
    return shift * shiftStep;
}

