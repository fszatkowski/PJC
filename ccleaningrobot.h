#ifndef CCLEANINGROBOT_H
#define CCLEANINGROBOT_H
#include "crobot.h"
#include "cdirt.h"

class CCleaningRobot :public CRobot
{
public:
    CCleaningRobot(CMap *m);
    CCleaningRobot(qreal xv, qreal yv, CMap *m);
    CCleaningRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    ~CCleaningRobot();
    void move();
    void update();
    void clean(CDirt *dirt);
};

#endif // CCLEANINGROBOT_H
