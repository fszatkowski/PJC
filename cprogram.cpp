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

    //in every step, add with random chance objects
    //if some robots get deleted, add new ones so that simulation keeps on going

    int spawn = (QRandomGenerator::global()->bounded(0, 100));
    if(!spawn)
    {
        map->add<CDirt, CGDirt>(1);
        return;
    }
    spawn--;
    if(!spawn)
    {
        map->add<CTreasure, CGTreasure>(1);
        return;
    }
    spawn *= 5;
    spawn--;
    if(!spawn)
    {
        map->add<CMine, CGMine>(1);
        return;
    }
}
