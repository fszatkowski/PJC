#ifndef CMAP_H
#define CMAP_H
#include "cgobject.h"
#include "cobject.h"
#include <QGraphicsScene>

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
    //get list of the objects near given object
    std::vector<CObject*> getNeighboorsList(CObject *o);
    std::vector<CGObject*> getNeighboorsGList(CGObject *go);
    //method for adding the object
    void addObject(CObject *object);
    void addGObject(CGObject *gobject);
    //method for releasing object from the vector containers
    void deleteFromMap(CObject *o);

    friend class CProgram;
};
#endif // CMAP_H
