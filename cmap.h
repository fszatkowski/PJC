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
    //method of adding n objects
    template <class object_type, class gobject_type> void add(int n);
    //method for adding the object to lists
    void addObject(CObject *object);
    void addGObject(CGObject *gobject);
    //method for releasing object from the vector containers
    void deleteFromMap(CObject *o);
};
#endif // CMAP_H
