#include "cgobstacle.h"

CGObstacle::CGObstacle(CObject *o)
    :CGObject(o)
{
}

QRectF CGObstacle::boundingRect() const
{
    return QRect(-(obstacle_width/2+10), -(obstacle_height/2+10),
                             obstacle_width+10, obstacle_height+10);
}
QPainterPath CGObstacle::shape() const
{
    QPainterPath path;
    path.addRect(QRect(-(obstacle_width/2), -(obstacle_height/2),
                       obstacle_width, obstacle_height));
    return path;
}

void CGObstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::darkGray);
    painter->rotate(object->getangle()*180/M_PI + 90);
    painter->drawRect(QRect(-(obstacle_width/2), -(obstacle_height/2),
                            obstacle_width, obstacle_height));
}

void CGObstacle::advance()
{
    setPos(object->getx(), object->gety());
    update(boundingRect());
}
