#include "cmap.h"
#include <QApplication>
#include <QGraphicsView>
#include <QRandomGenerator>
#include "math.h"


using namespace std;

CMap::CMap(QGraphicsScene *s)
{
    scene = s;

    int obstaclecount = 3;
    add<CObstacle, CGObstacle>(obstaclecount);

    int dirtcount = 4;
    add<CDirt, CGDirt>(dirtcount);

    int crobotcount = 4;
    add<CCleaningRobot, CGCleaningRobot>(crobotcount);

    int srobotcount = 4;
    add<CSearchingRobot, CGSearchingRobot>(srobotcount);

    int frobotcount = 8;
    add<CFightingRobot, CGFightingRobot>(frobotcount);

    int treasurecount = 4;
    add<CTreasure, CGTreasure>(treasurecount);

    int minecount = 4;
    add<CMine, CGMine>(minecount);
}

QGraphicsScene* CMap::getScene()
{
    return scene;
}

template <class object_type, class gobject_type> void CMap::add(int n)
{
    for(int i = 0; i<n; i++)
    {
        object_type *no = new object_type(this);
        addObject(no);
        gobject_type *ngo = new gobject_type(no);
        addGObject(ngo);
        scene->addItem(ngo);
    }
}

std::vector<CObject*> CMap::getObjectList()
{
    return ObjectList;
}

std::vector<CGObject*> CMap::getGObjectList()
{
    return GObjectList;
}

vector<CObject*> CMap::getNeighboorsList(CObject *o)
{
    vector<CObject*> neighboors;
    for(unsigned int i=0; i<ObjectList.size(); i++){
        qreal distance = ((ObjectList.at(i)->getX()-o->getX())*(ObjectList.at(i)->getX()-o->getX()))+((ObjectList.at(i)->getY()-o->getY())*(ObjectList.at(i)->getY()-o->getY()));
        distance = sqrt(distance);
        if(distance <= o->getRange()){
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
