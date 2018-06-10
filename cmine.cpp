#include "cmine.h"
#include <QRandomGenerator>
#include "ccleaningrobot.h"
#include "csearchingrobot.h"
#include "cfightingrobot.h"
#include "cmap.h"

CMine::CMine(CMap *m)
    :CNonMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        0,
                        100,
                        QRandomGenerator::global()->bounded(20, 50),
                        m)
{
    objectShape = Circle;
    width = value;
    height = value;
}

CMine::~CMine()
{
    map->deleteFromMap(this);
}

void CMine::update()
{
    std::vector<CRobot*> robots;
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CMovable *mobject = dynamic_cast<CMovable*>(neighboors[i]);
        CRobot *robot = dynamic_cast<CRobot*>(mobject);
        //if object is a robot, push it back
        if(robot)
        {
            robots.push_back(robot);
        }
    }
    if(robots.size() != 0)
    {
        destroy(robots);
    }
}

void CMine::destroy(std::vector<CRobot*> robots)
{
    for(unsigned int i=0; i<robots.size(); i++)
    {
        if(distance(robots[i]) < collisionDistance(robots[i]))
        {
            CCleaningRobot *crobot = dynamic_cast<CCleaningRobot*>(robots.at(i));
            if(crobot)
            {
                delete crobot;
                delete this;
            }
            else
            {
                CSearchingRobot *srobot = dynamic_cast<CSearchingRobot*>(robots.at(i));
                if(srobot)
                {
                    delete srobot;
                    delete this;
                }
                else
                {
                    CFightingRobot *frobot = dynamic_cast<CFightingRobot*>(robots.at(i));
                    if(frobot)
                    {
                        delete frobot;
                        delete this;
                    }
                }
            }
        }
    }
}
