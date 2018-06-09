#include "cfightingrobot.h"
#include <QRandomGenerator>
#include "ccleaningrobot.h"
#include "csearchingrobot.h"

CFightingRobot::CFightingRobot(CMap *m)
    :CRobot(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(0, 2*M_PI),
              100, m)
{
}

CFightingRobot::CFightingRobot(qreal xv, qreal yv, CMap *m)
    :CRobot(xv, yv, 0, 100, m)
{
}

CFightingRobot::CFightingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CRobot(xv, yv, anglev, rangev, m)
{
}

CFightingRobot::~CFightingRobot()
{
    map->deleteFromMap(this);
}

void CFightingRobot::move()
{
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CRobot*> robots;
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CMovable *mobject = dynamic_cast<CMovable*>(neighboors.at(i));
        CRobot *robot = dynamic_cast<CRobot*>(mobject);
        if(robot)
        {
            robots.push_back(robot);
        }
    }

    if(robots.size() != 0)
    {
        unsigned int closest = 0;
        qreal closest_distance = range;
        for(unsigned int i=0; i<robots.size(); i++)
        {
            qreal distance = (robots.at(i)->getx()-x)*(robots.at(i)->getx()-x)+(robots.at(i)->gety()-y)*(robots.at(i)->gety()-y);
            if(distance < closest_distance)
            {
                closest = i;
                closest_distance = distance;
            }
        }
        go_to(robots.at(closest));
    }

    else
        move_randomly();
}

//attack if colliding with robot
//stay if obstacle is nearby
//move randomly if there are none
void CFightingRobot::update()

{
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CRobot*> robots;
    std::vector<CObstacle*> obstacles;
    std::vector<CNonMovable*> others;
    std::vector<CRobot*> empty;
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CMovable *mobject = dynamic_cast<CMovable*>(neighboors.at(i));
        if(mobject)
        {
            CObstacle *obstacle = dynamic_cast<CObstacle*>(mobject);
            if(obstacle)
            {
                qreal distance = (obstacle->getx()-x)*(obstacle->getx()-x)+(obstacle->gety()-y)*(obstacle->gety()-y);
                distance = sqrt(distance);
                if(distance < (robot_height+robot_width)/3 + obstacle_height+obstacle_width/3)
                    obstacles.push_back(obstacle);
            }
            else
            {
                CRobot *robot = dynamic_cast<CRobot*>(mobject);
                if(robot)
                {
                    qreal distance = (robot->getx()-x)*(robot->getx()-x)+(robot->gety()-y)*(robot->gety()-y);
                    distance = sqrt(distance);
                    if(distance < (robot_height+robot_width)/2)
                        robots.push_back(robot);
                }
            }
        }
        else
        {
            CNonMovable *nmobject = dynamic_cast<CNonMovable*>(neighboors.at(i));
            others.push_back(nmobject);
        }
    }

    //if there are any robots colliding - attack
    if(robots.size() != 0)
    {
        for(unsigned i=0; i<robots.size(); i++)
        {
            attack(robots.at(i));
        }
    }

    //if there are obstacles - stay
    if(obstacles.size() !=0)
    {
        return;
    }

    else if(others.size()!=0)
        avoid(others, empty);

    else if(!(x <= map_size/2 && x >= -map_size/2 && y <= map_size/2 && y >= -map_size/2))
    {
        avoid_boundaries();
    }

    else
        move();
}

void CFightingRobot::attack(CRobot *robot)
{
    CCleaningRobot *crobot = dynamic_cast<CCleaningRobot*>(robot);
    if(crobot)
    {
        map->deleteFromMap(crobot);
        delete crobot;
    }
    else
    {
        CSearchingRobot *srobot = dynamic_cast<CSearchingRobot*>(robot);
        if(srobot)
        {
            map->deleteFromMap(srobot);
            delete srobot;
        }
        else
        {
            CFightingRobot *frobot = dynamic_cast<CFightingRobot*>(robot);
            if(frobot)
            {
                map->deleteFromMap(frobot);
                delete frobot;
            }
        }
    }
}
