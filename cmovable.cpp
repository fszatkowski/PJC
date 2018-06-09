#include "cmovable.h"


//CMovable and CNonMovable constructors
CMovable::CMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CObject(xv, yv, anglev, rangev, m)
{
}
