#ifndef COBJECT_H
#define COBJECT_H
#include <QGraphicsItem>
#include "cmap.h"

class CMap;

class CObject
{
protected:
    qreal x;
    qreal y;
    qreal angle;
    qreal range;
    CMap *map;
public:
    CObject(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    qreal getx();
    qreal gety();
    qreal getangle();
    qreal getrange();
    CMap *getmap();
    virtual void update()=0;
};

#endif // COBJECT_H
