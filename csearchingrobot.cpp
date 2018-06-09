#include "csearchingrobot.h"
#include <QRandomGenerator>

CSearchingRobot::CSearchingRobot(CMap *m)
    :CRobot(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(0, 2*M_PI),
              100, m)
{
}

CSearchingRobot::CSearchingRobot(qreal xv, qreal yv, CMap *m)
    :CRobot(xv, yv, 0, 100, m)
{
}

CSearchingRobot::CSearchingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CRobot(xv, yv, anglev, rangev, m)
{
}

CSearchingRobot::~CSearchingRobot()
{
    map->deleteFromMap(this);
}

//seek treasures
void CSearchingRobot::move()
{
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CTreasure*> treasures;
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CNonMovable *nmobject = dynamic_cast<CNonMovable*>(neighboors.at(i));
        CTreasure *treasure = dynamic_cast<CTreasure*>(nmobject);
        if(treasure)
        {
            treasures.push_back(treasure);
        }
    }

    if(treasures.size() != 0)
    {
        unsigned int closest = 0;
        qreal closest_distance = range;
        for(unsigned int i=0; i<treasures.size(); i++)
        {
            qreal distance = (treasures.at(i)->getx()-x)*(treasures.at(i)->getx()-x)+(treasures.at(i)->gety()-y)*(treasures.at(i)->gety()-y);
            if(distance < closest_distance)
            {
                closest = i;
                closest_distance = distance;
            }
        }
        go_to(treasures.at(closest));
    }

    else if(x <= map_size/2 && x >= -map_size/2 && y <= map_size/2 && y >= -map_size/2)
    {
        move_randomly();
    }
}

//stay if colliding with obstacle
//collect treasures if colliding with treasure
//seek treasures moving randomly else
void CSearchingRobot::update()
{
    //check if there are treasures or obstacles nearby
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CTreasure*> treasures;
    std::vector<CObstacle*> obstacles;
    std::vector<CNonMovable*> others;
    std::vector<CRobot*> robots;
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
                    robots.push_back(robot);
            }
        }
        else
        {
            CNonMovable *nmobject = dynamic_cast<CNonMovable*>(neighboors.at(i));
            if(nmobject)
            {
                CTreasure *treasure = dynamic_cast<CTreasure*>(nmobject);
                if(treasure)
                {
                    qreal distance = (treasure->getx()-x)*(treasure->getx()-x)+(treasure->gety()-y)*(treasure->gety()-y);
                    distance = sqrt(distance);
                    if(distance < (robot_height+robot_width)/4+treasure_size/2)
                    treasures.push_back(treasure);
                }
                else
                {
                    others.push_back(nmobject);
                }
            }
        }
    }

    if(treasures.size() != 0)
    {
        for(unsigned i=0; i<treasures.size(); i++)
        {
            collect(treasures.at(i));
        }
    }

    if(obstacles.size() !=0)
    {
        return;
    }

    else if(others.size()!=0)
        avoid(others, robots);

    else if(!(x <= map_size/2 && x >= -map_size/2 && y <= map_size/2 && y >= -map_size/2))
    {
        avoid_boundaries();
    }

    else
        move();
}

void CSearchingRobot::collect(CTreasure *treasure)
{
    addItem(treasure);
    treasure->getCollected();
}
