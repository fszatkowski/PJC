#ifndef CGOBSTACLE_H
#define CGOBSTACLE_H
#include "cgobject.h"
#include "cobstacle.h"

class CGObstacle :public CGObject
{
public:
    CGObstacle(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGOBSTACLE_H
