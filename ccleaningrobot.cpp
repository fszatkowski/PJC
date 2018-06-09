#include "ccleaningrobot.h"
#include <QRandomGenerator>

CCleaningRobot::CCleaningRobot(CMap *m)
    :CRobot(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(0, 2*M_PI),
              100, m)
{
}

CCleaningRobot::CCleaningRobot(qreal xv, qreal yv, CMap *m)
    :CRobot(xv, yv, 0, 100, m)
{
}

CCleaningRobot::CCleaningRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m)
    :CRobot(xv, yv, anglev, rangev, m)
{
}

CCleaningRobot::~CCleaningRobot()
{
    map->deleteFromMap(this);
}

//movement - seeking dirts
void CCleaningRobot::move()
{
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CDirt*> dirts;
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CNonMovable *nmobject = dynamic_cast<CNonMovable*>(neighboors.at(i));
        CDirt *dirt = dynamic_cast<CDirt*>(nmobject);
        if(dirt)
        {
            dirts.push_back(dirt);
        }
    }

    if(dirts.size() != 0)
    {
        unsigned int closest = 0;
        qreal closest_distance = range;
        for(unsigned int i=0; i<dirts.size(); i++)
        {
            qreal distance = (dirts.at(i)->getx()-x)*(dirts.at(i)->getx()-x)+(dirts.at(i)->gety()-y)*(dirts.at(i)->gety()-y);
            if(distance < closest_distance)
            {
                closest = i;
                closest_distance = distance;
            }
        }

        go_to(dirts.at(closest));
    }

    else
    {
        move_randomly();
    }
}

//check your neighboorhood
//if colliding with dirt - clean it
//if obstacle on path - wait
//if there is possible collision with other things - move to avoid it
//if out of the map - come back
//else move randomly

void CCleaningRobot::update()
{
    //check if there are dirts or obstacles nearby
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CDirt*> dirts;
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
                CDirt *dirt = dynamic_cast<CDirt*>(nmobject);
                if(dirt)
                {
                    qreal distance = (dirt->getx()-x)*(dirt->getx()-x)+(dirt->gety()-y)*(dirt->gety()-y);
                    distance = sqrt(distance);
                    if(distance < (robot_height+robot_width)/4+dirt->getvalue()/2)
                    dirts.push_back(dirt);
                }
                else
                {
                    others.push_back(nmobject);
                }
            }
        }
    }

    if(dirts.size() != 0)
    {
        for(unsigned i=0; i<dirts.size(); i++)
        {
            clean(dirts.at(i));
        }
    }

    if(obstacles.size() !=0)
    {
        return;
    }

    else if(others.size() != 0)
    {
        avoid(others, robots);
    }

    else if(!(x <= map_size/2 && x >= -map_size/2 && y <= map_size/2 && y >= -map_size/2))
    {
        avoid_boundaries();
    }

    else
    {
        move();
    }
}


void CCleaningRobot::clean(CDirt *dirt)
{
    dirt->getCleaned();
}
