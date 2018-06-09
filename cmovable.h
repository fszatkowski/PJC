#ifndef CMOVABLE_H
#define CMOVABLE_H
#include "cobject.h"

class CMovable :public CObject
{
public:
    CMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual void update()=0;
    virtual void move()=0;
};

#endif // CMOVABLE_H
