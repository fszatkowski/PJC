#ifndef CROBOT_H
#define CROBOT_H
#include "cmovable.h"
#include "cnonmovable.h"
#include "cobstacle.h"

const int robot_width = 30;
const int robot_height = 20;
const int robot_speed = 10;

class CRobot :public CMovable
{
protected:
    std::vector<CNonMovable*> items;
public:
    CRobot(CMap *m);
    CRobot(qreal xv, qreal yv, CMap *m);
    CRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual void update()=0;
    virtual void move()=0;
    void moveRandomly();
    void returnToMap();
    void addItem(CNonMovable *item);
    void goTo(CObject *o);
    void avoid(std::vector<CNonMovable*> o, std::vector<CRobot*> r, std::vector<CObstacle *> ob);
    void follow(CRobot *robot);
};
#endif // CROBOT_H
