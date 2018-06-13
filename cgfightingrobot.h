#ifndef CGFIGHTINGROBOT_H
#define CGFIGHTINGROBOT_H
#include "cgobject.h"
#include "cfightingrobot.h"

/// \brief Graficzna reprezentacja robota walczącego
class CGFightingRobot :public CGObject
{
public:
    CGFightingRobot(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGFIGHTINGROBOT_H
