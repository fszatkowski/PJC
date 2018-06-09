#ifndef CFIGHTINGROBOT_H
#define CFIGHTINGROBOT_H
#include "crobot.h"

class CFightingRobot :public CRobot
{
public:
    CFightingRobot(CMap *m);
    CFightingRobot(qreal xv, qreal yv, CMap *m);
    CFightingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    ~CFightingRobot();
    void move();
    void attack(CRobot *robot);
    void update();
};

#endif // CFIGHTINGROBOT_H
