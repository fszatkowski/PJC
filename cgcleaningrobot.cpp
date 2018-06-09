#include "cgcleaningrobot.h"

CGCleaningRobot::CGCleaningRobot(CObject *o)
    :CGObject(o)
{
}

QRectF CGCleaningRobot::boundingRect() const
{
    return QRect(-(robot_width/2+5), -(robot_height/2+5), robot_width+10, robot_height+10);
}

//boundingRect is larger than actual object, so that the painting doesnt leave any artifacts while updating

QPainterPath CGCleaningRobot::shape() const
{
    QPainterPath path;
    path.addRect(QRect(-(robot_width/2), -(robot_height/2), robot_width, robot_height));
    return path;
}

void CGCleaningRobot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::lightGray);
    painter->rotate(object->getAngle()*180/M_PI);
    painter->drawRect(-robot_width/2, -robot_height/2, robot_width, robot_height);
}

void CGCleaningRobot::advance()
{
    setPos(object->getX(), object->getY());
    update(boundingRect());
}
