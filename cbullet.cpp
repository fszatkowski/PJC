#include "cbullet.h"
#include "cmap.h"

CBullet::CBullet(CMap *m, CFightingRobot *r)
    :CMovable(r->getX()+cos(r->getAngle())*robot_height/2,
              r->getY()+sin(r->getAngle())*robot_width/2,
              r->getAngle(),
              50, m)
{
    creator = r;
    size = bulletSize;
    life = bulletLifetime;
    objectShape = Circle;
    width = bulletSize;
    height = bulletSize;
}

CBullet::~CBullet()
{
    map->deleteFromMap(this);
}

//bullets accelerate
void CBullet::move()
{
    x += bulletSpeed * (1+(bulletLifetime-life)/bulletLifetime) * cos(angle);
    y += bulletSpeed * (1+(bulletLifetime-life)/bulletLifetime) * sin(angle);
}

void CBullet::update()
{
    move();
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    for(unsigned int i = 0; i<neighboors.size(); i++)
    {
        CMovable* mobject = dynamic_cast<CMovable*>(neighboors[i]);
        if(mobject)
        {
            CRobot *robot = dynamic_cast<CRobot*>(mobject);
            if(robot)
            {
                CCleaningRobot *crobot = dynamic_cast<CCleaningRobot*>(robot);
                if(crobot)
                {
                    if(collidesWith(crobot))
                        delete crobot;
                }
                else
                {
                    CSearchingRobot *srobot = dynamic_cast<CSearchingRobot*>(robot);
                    if(srobot)
                    {
                        if(collidesWith(srobot))
                            delete srobot;
                    }
                    else
                    {
                        CFightingRobot *frobot = dynamic_cast<CFightingRobot*>(robot);
                        if(frobot)
                        {
                            if(collidesWith(frobot))
                            {
                                if(frobot != creator)
                                    delete frobot;
                            }
                        }
                    }
                }
            }
        }

    }
    life --;
    size -= bulletSize / 5;
    width = size;
    height = size;
    if(!life)
    {
        delete this;
    }
}
