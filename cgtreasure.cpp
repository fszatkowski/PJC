#include "cgtreasure.h"

CGTreasure::CGTreasure(CObject *o)
    :CGObject(o)
{
}

QPainterPath CGTreasure::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF CGTreasure::boundingRect() const
{
    CNonMovable *nmobject = dynamic_cast<CNonMovable*>(object);
    int diameter = nmobject->getvalue();
    return QRect(-diameter/2, -diameter/2, diameter, diameter);
}

void CGTreasure::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::darkYellow);
    painter->drawRect(boundingRect());
}

void CGTreasure::advance()
{
    setPos(object->getX(), object->getY());
    update(boundingRect());
}
