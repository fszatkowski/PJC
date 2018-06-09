#include "cprogram.h"
#include <QGraphicsView>
#include <QRandomGenerator>
#include "cdirt.h"
#include "cgdirt.h"

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
    for(unsigned int i=0; i<map->ObjectList.size(); i++)
    {
        map->ObjectList.at(i)->update();
    }
    for(unsigned int i=0; i<map->GObjectList.size(); i++)
    {
        map->GObjectList.at(i)->advance();
    }
    /*
    int spawn_dirt = (QRandomGenerator::global()->bounded(100));
    if(!spawn_dirt)
    {
        CDirt *dirt = new CDirt(map);
        map->addObject(dirt);
        CGDirt *gdirt = new CGDirt(dirt);
        map->addGObject(gdirt);
        map->scene->addItem(gdirt);
    }
    */
}
