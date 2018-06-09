#ifndef CNONMOVABLE_H
#define CNONMOVABLE_H
#include "cobject.h"

class CNonMovable :public CObject
{
protected:
    qreal value;
public:
    CNonMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, qreal valuev, CMap *m);
    qreal getvalue();
    virtual void update()=0;
};

#endif // CNONMOVABLE_H
