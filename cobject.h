#ifndef COBJECT_H
#define COBJECT_H
#include <QGraphicsItem>

class CMap;

//shape is used to determine collisions between objects
enum shape
{
    Rect = 1,
    Square = 2,
    Circle = 3
};

class CObject
{
protected:
    //coordinates
    qreal x;
    qreal y;
    //orientation
    qreal angle;
    //region 'seen' by object
    qreal range;
    //map that object occupies
    CMap *map;
    //width, height and shape used for collision detection
    qreal width;
    qreal height;
    shape objectShape;
public:
    //constructor
    CObject(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual void update()=0;
    qreal getX();
    qreal getY();
    qreal getAngle();
    qreal getRange();
    CMap *getMap();
    qreal getWidth();
    qreal getHeight();
    int getShape();
    //calculate maximum distance at which robots collide
    qreal collisionDistance(CObject *o);
    //check if two objects collide
    bool collidesWith(CObject *o);
    //check if two objects will collide after their move
    bool willCollide(CObject *o, qreal thisSpeed, qreal oSpeed);
};

#endif // COBJECT_H
