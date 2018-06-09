#ifndef CGMINE_H
#define CGMINE_H
#include "cgobject.h"
#include "cmine.h"

class CGMine :public CGObject
{
public:
    CGMine(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGMINE_H
