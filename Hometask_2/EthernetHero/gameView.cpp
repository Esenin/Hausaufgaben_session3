#include "gameView.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
    , mUsersCount(0)
    , mAgent(NULL)
    , mDevelopers(NULL)
    , mTimeForReload(0)
{
    initGraphicsOutput();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    gameKernel = new GameLogic();

    connect(&stepTimer, SIGNAL(timeout()), this, SLOT(stepTimerEvent()));
    installEventFilter(this);
}

void GameView::startGame()
{
    qDebug() << "start new session";
    setupNewNetwork();
    gameKernel->loadNewUsers(mUsers);
    stepTimer.start(stepTime);

}

void GameView::stopGame()
{
    stepTimer.stop();
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
    mScene->setSceneRect(-220, -20, 1340, 600);
    setScene(mScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(960, 520);

}

void GameView::setupNewNetwork()
{
    if (mAgent)
    {
        delete mAgent;
        delete mDevelopers;
        mUsers.clear();
    }
    mAgent = new WorkStation(hacker);
    mScene->addItem(mAgent);
    mAgent->setPos(sceneRect().left() + 10, mScene->sceneRect().center().y());

    mDevelopers = new WorkStation(target);
    mScene->addItem(mDevelopers);
    mDevelopers->setPos(mScene->sceneRect().right() - 110, mScene->sceneRect().center().y());

    mUsersCount = (qrand() % (maxUsers - minUsers + 1)) + minUsers;
    for (int i = 0; i < mUsersCount; i++)
    {
        mUsers.append(new WorkStation());
    }

    setUsersToGrid();
}

void GameView::setUsersToGrid()
{
    int const shift = 50;
    qreal xPos = 0;
    qreal yPos = 0;
    foreach (WorkStation *station, mUsers)
    {
        station->setPos(xPos, yPos);
        mScene->addItem(station);

        xPos += station->boundingRect().width() + shift;
        if (xPos > mDevelopers->x() - station->boundingRect().width())
        {
            xPos = 0;
            yPos += station->boundingRect().height() + shift;
        }
    }

    qDebug() << "deployed to grid";

}

bool GameView::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        if (mTimeForReload == 0)
        {
            mTimeForReload = trafficReloadTime;
        }
        else
        {
            return false;
        }
    }
    return false;

}


void GameView::stepTimerEvent()
{
    gameKernel->makeNextMove();
    if (mTimeForReload)
        mTimeForReload--;
}
