#include "cobject.h"

//CObject constructor
CObject::CObject(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
{
    x=xv;
    y=yv;
    angle=anglev;
    range=rangev;
    map = m;
}

qreal CObject::getx()
{
    return x;
}

qreal CObject::gety()
{
    return  y;
}

qreal CObject::getangle()
{
    return angle;
}

qreal CObject::getrange()
{
    return range;
}

CMap *CObject::getmap()
{
    return map;
}
