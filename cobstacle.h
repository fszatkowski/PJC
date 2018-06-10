#ifndef COBSTACLE_H
#define COBSTACLE_H
#include "cmovable.h"

const int obstacle_width=30;
const int obstacle_height=50;
const int obstacle_speed=5;

class CObstacle :public CMovable
{
public:
    CObstacle(qreal xv, qreal yv, CMap *m);
    CObstacle(CMap *m);
    ~CObstacle();
    void update();
    void move();
    void turn();
};

#endif // COBSTACLE_H
