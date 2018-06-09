#ifndef CGDIRT_H
#define CGDIRT_H
#include "cgobject.h"
#include "cdirt.h"

class CGDirt :public CGObject
{
public:
    CGDirt(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGDIRT_H
