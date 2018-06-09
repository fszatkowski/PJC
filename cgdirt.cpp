#include "cgdirt.h"

CGDirt::CGDirt(CObject *o)
    :CGObject(o)
{
}

QPainterPath CGDirt::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF CGDirt::boundingRect() const
{
    CNonMovable *nmobject = dynamic_cast<CNonMovable*>(object);
    int diameter = nmobject->getvalue();
    return QRect(-diameter/2, -diameter/2, diameter, diameter);
}

void CGDirt::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(boundingRect());
}

void CGDirt::advance()
{
    setPos(object->getX(), object->getY());
    update(boundingRect());
}
