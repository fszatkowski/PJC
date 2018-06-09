#ifndef CSEARCHINGROBOT_H
#define CSEARCHINGROBOT_H
#include "crobot.h"
#include "ctreasure.h"

class CSearchingRobot :public CRobot
{
public:
    CSearchingRobot(CMap *m);
    CSearchingRobot(qreal xv, qreal yv, CMap *m);
    CSearchingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    ~CSearchingRobot();
    void move();
    void update();
    void collect(CTreasure *treasure);
};
#endif // CSEARCHINGROBOT_H
