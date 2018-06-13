#include "cprogram.h"
#include <QGraphicsView>
#include <QRandomGenerator>
#include "cmap.h"

CProgram::CProgram()
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(-map_size/2, -map_size/2, map_size, map_size);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    CMap *m = new CMap(scene);
    map = m;

    QGraphicsView *view = new QGraphicsView(scene);

    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setFixedWidth(map_size);
    view->setFixedHeight(map_size);
    view->autoFillBackground();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "RobotSimulation"));
    view->show();

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->start(30);
}

void CProgram::step()
{
    for(unsigned int i=0; i<map->getObjectList().size(); i++)
    {
        map->getObjectList()[i]->update();
    }
    for(unsigned int i=0; i<map->getGObjectList().size(); i++)
    {
        map->getGObjectList()[i]->advance();
    }

    //in every step, randomly spawn objects
    map->spawn<CTreasure, CGTreasure>(100);
    map->spawn<CDirt, CGDirt>(100);
    map->spawn<CMine, CGMine>(1000);
    map->spawn<CCleaningRobot, CGCleaningRobot>(200);
    map->spawn<CSearchingRobot, CGSearchingRobot>(200);
    map->spawn<CFightingRobot, CGFightingRobot>(500);
}
