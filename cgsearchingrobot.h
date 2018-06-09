#ifndef CGSEARCHINGROBOT_H
#define CGSEARCHINGROBOT_H
#include "cgobject.h"
#include "csearchingrobot.h"

class CGSearchingRobot :public CGObject
{
public:
    CGSearchingRobot(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGSEARCHINGROBOT_H
