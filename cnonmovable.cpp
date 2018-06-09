#include "cnonmovable.h"

CNonMovable::CNonMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, qreal valuev, CMap *m)
    :CObject(xv, yv, anglev, rangev, m)
{
    value=valuev;
}

qreal CNonMovable::getvalue()
{
    return value;
}
