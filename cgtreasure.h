#ifndef CGTREASURE_H
#define CGTREASURE_H
#include "cgobject.h"
#include "ctreasure.h"

class CGTreasure :public CGObject
{
public:
    CGTreasure(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGTREASURE_H
