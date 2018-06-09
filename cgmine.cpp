#include "cgmine.h"

CGMine::CGMine(CObject *o)
    :CGObject(o)
{
}

QPainterPath CGMine::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF CGMine::boundingRect() const
{
    CNonMovable *nmobject = dynamic_cast<CNonMovable*>(object);
    int diameter = nmobject->getvalue();
    return QRect(-diameter/2, -diameter/2, diameter, diameter);
}

void CGMine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

void CGMine::advance()
{
    setPos(object->getX(), object->getY());
    update(boundingRect());
}
