#include "cmap.h"
#include <QApplication>
#include <QGraphicsView>
#include <QRandomGenerator>
#include "math.h"
#include "ccleaningrobot.h"
#include "cgcleaningrobot.h"
#include "csearchingrobot.h"
#include "cgsearchingrobot.h"
#include "cfightingrobot.h"
#include "cgfightingrobot.h"
#include "cobstacle.h"
#include "cgobstacle.h"
#include "cdirt.h"
#include "cgdirt.h"
#include "cmine.h"
#include "cgmine.h"
#include "ctreasure.h"
#include "cgtreasure.h"

using namespace std;

CMap::CMap(QGraphicsScene *s)
{
    scene = s;
    //initialization of the objects
    qreal obstaclecount = 1;

    for(int i=0; i<obstaclecount; i++)
    {
        CObstacle *obstacle = new CObstacle(this);
        addObject(obstacle);
        CGObstacle *gobstacle = new CGObstacle(obstacle);
        addGObject(gobstacle);
        scene->addItem(gobstacle);
    }

    qreal dirtcount = 15;

    for(int i=0; i<dirtcount; i++)
    {
        CDirt *dirt = new CDirt(this);
        addObject(dirt);
        CGDirt *gdirt = new CGDirt(dirt);
        addGObject(gdirt);
        scene->addItem(gdirt);
    }

    qreal crobotcount = 15;

    for(int i=0; i<crobotcount; i++)
    {
        CCleaningRobot *crobot = new CCleaningRobot(this);
        addObject(crobot);
        CGCleaningRobot *gcrobot = new CGCleaningRobot(crobot);
        addGObject(gcrobot);
        scene->addItem(gcrobot);
    }

    qreal srobotcount = 3;

    for(int i=0; i<srobotcount; i++)
    {
        CSearchingRobot *srobot = new CSearchingRobot(this);
        addObject(srobot);
        CGSearchingRobot *gsrobot = new CGSearchingRobot(srobot);
        addGObject(gsrobot);
        scene->addItem(gsrobot);
    }

    qreal frobotcount = 0;

    for(int i=0; i<frobotcount; i++)
    {
        CFightingRobot *frobot = new CFightingRobot(this);
        addObject(frobot);
        CGFightingRobot *gfrobot = new CGFightingRobot(frobot);
        addGObject(gfrobot);
        scene->addItem(gfrobot);
    }

    qreal treasurecount = 5;
    for(int i=0; i<treasurecount; i++)
    {
        CTreasure *treasure = new CTreasure(this);
        addObject(treasure);
        CGTreasure *gtreasure = new CGTreasure(treasure);
        addGObject(gtreasure);
        scene->addItem(gtreasure);
    }


    qreal minecount = 1;
    for(int i=0; i<minecount; i++)
    {
        CMine *mine = new CMine(this);
        addObject(mine);
        CGMine *gmine = new CGMine(mine);
        addGObject(gmine);
        scene->addItem(gmine);
    }
}

vector<CObject*> CMap::getNeighboorsList(CObject *o)
{
    vector<CObject*> neighboors;
    for(unsigned int i=0; i<ObjectList.size(); i++){
        qreal distance = ((ObjectList.at(i)->getx()-o->getx())*(ObjectList.at(i)->getx()-o->getx()))+((ObjectList.at(i)->gety()-o->gety())*(ObjectList.at(i)->gety()-o->gety()));
        distance = sqrt(distance);
        if(distance <= o->getrange()){
            if(o != ObjectList.at(i))
                neighboors.push_back(ObjectList.at(i));
        }
        distance = 0;
    }
    return neighboors;
}

void CMap::addObject(CObject *object)
{
    ObjectList.push_back(object);
}

void CMap::addGObject(CGObject *gobject)
{
    GObjectList.push_back(gobject);
}

void CMap::deleteFromMap(CObject *o)
{
    unsigned int size=GObjectList.size();
    for(unsigned int i=0; i<size; i++){
        CGObject *gobject = GObjectList.at(i);
        if(gobject->getCObject() == o)
        {
            gobject->scene()->removeItem(gobject);
            GObjectList.erase(GObjectList.begin()+i);
            delete gobject;
            break;
        }
    }
    size=ObjectList.size();
    for(unsigned int i=0; i<size; i++)
    {
        CObject *object = ObjectList.at(i);
        if(object == o)
        {
            ObjectList.erase(ObjectList.begin()+i);
            break;
        }
    }
}
