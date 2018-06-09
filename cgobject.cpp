#include "cgobject.h"

CGObject::CGObject(CObject *o)
{
    object=o;
    map=o->getMap();
    setPos(o->getX(), o->getY());
}

CObject* CGObject::getCObject()
{
    return object;
}

