#include "cgobject.h"

CGObject::CGObject(CObject *o)
{
    object=o;
    map=o->getmap();
    setPos(o->getx(), o->gety());
}

CObject* CGObject::getCObject()
{
    return object;
}

