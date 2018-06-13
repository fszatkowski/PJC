#ifndef CGBULLET_H
#define CGBULLET_H
#include "cgobject.h"
#include "cbullet.h"

/// \brief Graficzna reprezentacja pocisku
class CGBullet :public CGObject
{
public:
    CGBullet(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGBULLET_H
