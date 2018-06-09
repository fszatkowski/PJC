#include "cgbullet.h"

CGBullet::CGBullet(CObject *o)
    :CGObject(o)
{
}

QRectF CGBullet::boundingRect() const
{
    return QRect(-object->getWidth()/2, -object->getHeight()/2,
                 object->getWidth(), object->getHeight());
}
QPainterPath CGBullet::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CGBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::darkRed);
    painter->drawEllipse(boundingRect());
}

void CGBullet::advance()
{
    setPos(object->getX(), object->getY());
    update(boundingRect());
}
