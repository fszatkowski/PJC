#ifndef CBULLET_H
#define CBULLET_H
#include "cmovable.h"
#include "cfightingrobot.h"

const qreal bulletSpeed = 30;
const int bulletLifetime = 4;
const int bulletSize = 10;

class CBullet :public CMovable
{
private:
    int life;
    int size;
    CFightingRobot *creator;
public:
    CBullet(CMap *m, CFightingRobot *r);
    ~CBullet();
    void move();
    void update();
};

#endif // CBULLET_H
