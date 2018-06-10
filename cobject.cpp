#include "cobject.h"
#include "cmap.h"

//CObject constructor
CObject::CObject(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
{
    x=xv;
    y=yv;
    angle=anglev;
    range=rangev;
    map = m;
}

qreal CObject::getX()
{
    return x;
}

qreal CObject::getY()
{
    return  y;
}

qreal CObject::getAngle()
{
    return angle;
}

qreal CObject::getRange()
{
    return range;
}

CMap* CObject::getMap()
{
    return map;
}

qreal CObject::getWidth()
{
    return width;
}

qreal CObject::getHeight()
{
    return height;
}

int CObject::getShape()
{
    switch (objectShape)
    {
    case Rect:
        return 1;
    case Square:
        return 2;
    case Circle:
        return 3;
    }
}

qreal CObject::distance(CObject *o)
{
    return sqrt((o->getX()-x)*(o->getX()-x)+(o->getY()-y)*(o->getY()-y));
}

qreal CObject::collisionDistance(CObject *o)
{
    qreal thresh = 0;
    switch(objectShape)
    {
    case Rect:
        thresh += 1.5*((width+height)/4);
        break;
    case Square:
        thresh += 1.4*((width+height)/4);
        break;
    case Circle:
        thresh += width+height/4;
        break;
    }

    switch(o->getShape())
    {
    case Rect:
        thresh += 1.5*((o->getWidth()+o->getHeight())/2);
        break;
    case Square:
        thresh += 1.4*((o->getWidth()+o->getHeight())/2);
        break;
    case Circle:
        thresh += (o->getWidth()+o->getHeight())/4;
        break;
    }
    return thresh;
}

bool CObject::collidesWith(CObject *o)
{
    if(distance(o) < collisionDistance(o))
        return 1;
    else
        return 0;
}

bool CObject::willCollide(CObject *o, qreal thisSpeed, qreal oSpeed)
{
    qreal x1 = x + thisSpeed * cos(angle);
    qreal y1 = y + thisSpeed * sin(angle);

    qreal x2 = o->getX() + oSpeed * cos(o->getAngle());
    qreal y2 = o->getY() + oSpeed * sin(o->getAngle());

    qreal distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(distance < collisionDistance(o))
        return 1;
    else
        return 0;
}
