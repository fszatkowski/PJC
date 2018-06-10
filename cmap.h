#ifndef CMAP_H
#define CMAP_H
#include "cgobject.h"
#include "cobject.h"
#include <QGraphicsScene>
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
#include <QRandomGenerator>

const int map_size = 1000;

class CObject;
class CGObject;

class CMap
{
private:
    QGraphicsScene *scene;
    //contains every objects in program
    std::vector<CObject*> ObjectList;
    std::vector<CGObject*> GObjectList;
public:
    CMap(QGraphicsScene *scene);
    QGraphicsScene* getScene();
    //get list of every object
    std::vector<CObject*> getObjectList();
    std::vector<CGObject*> getGObjectList();
    //get list of the objects near given object
    std::vector<CObject*> getNeighboorsList(CObject *o);
    std::vector<CGObject*> getNeighboorsGList(CGObject *go);
    //method for adding the object to lists
    void addObject(CObject *object);
    void addGObject(CGObject *gobject);
    //method for releasing object from the vector containers
    void deleteFromMap(CObject *o);
    //templates defined in header, because otherwise compiler returns an error
    //method for adding n objects to the map
    template <class object_type, class gobject_type> void add(int n)
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
    //method for adding object with probability 1/x
    template <class object_type, class gobject_type> void spawn(int x)
    {
        if(!QRandomGenerator::global()->bounded(0, x))
        {
            object_type *no = new object_type(this);
            addObject(no);
            gobject_type *ngo = new gobject_type(no);
            addGObject(ngo);
            scene->addItem(ngo);
        }
    }

};
#endif // CMAP_H
