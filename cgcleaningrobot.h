#ifndef CGCLEANINGROBOT_H
#define CGCLEANINGROBOT_H
#include "cgobject.h"
#include "ccleaningrobot.h"

/// \brief Graficzna reprezentacja robota czyszczącego
class CGCleaningRobot :public CGObject
{
public:
    CGCleaningRobot(CObject *o);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QRectF boundingRect() const override;
    void advance() override;
    QPainterPath shape() const override;
};

#endif // CGCLEANINGROBOT_H
