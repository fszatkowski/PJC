#ifndef CGOBJECT_H
#define CGOBJECT_H
#include <QGraphicsItem>
#include <QPainter>
#include "cobject.h"

class CObject;
class CMap;

class CGObject :public QGraphicsItem
{
protected:
    CObject *object;
    CMap *map;
public:
    CGObject(CObject *o);
    CObject* getCObject();
    virtual void advance() = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) = 0;
};

#endif // CGOBJECT_H
