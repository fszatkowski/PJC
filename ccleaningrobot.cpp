#include "ccleaningrobot.h"
#include <QRandomGenerator>
#include "cmap.h"

CCleaningRobot::CCleaningRobot(CMap *m)
    :CRobot(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              (QRandomGenerator::global()->bounded(0, 36)*M_PI/18),
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
    //check objects nearby
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
                    dirts.push_back(dirt);
                }
                else
                {
                    others.push_back(nmobject);
                }
            }
        }
    }

    //if there are objects nearby - try to avoid collisions with them
    unsigned int n_objects = others.size() + obstacles.size() + robots.size();
    if(n_objects!=0)
    {
        avoid(others, robots, obstacles);
        return;
    }

    else if(!(x <= map_size/2 && x >= -map_size/2 && y <= map_size/2 && y >= -map_size/2))
    {
        returnToMap();
        return;
    }

    //if there are dirts nearby - go to the closest one
    if(dirts.size() != 0)
    {
        unsigned int closest = 0;
        qreal closest_distance = range;
        for(unsigned int i=0; i<dirts.size(); i++)
        {
            if(distance(dirts[i]) < closest_distance)
            {
                closest = i;
                closest_distance = distance(dirts[i]);
            }
        }

        goTo(dirts[closest]);
    }

    //if there are none - move at random

    else
    {
        moveRandomly();
    }
}

//check your neighboorhood
//if colliding with dirt - clean it
//then move
void CCleaningRobot::update()
{
    //check if there are dirts
    std::vector<CObject*> neighboors = map->getNeighboorsList(this);
    std::vector<CDirt*> dirts;
    for(unsigned int i=0; i<neighboors.size(); i++)
    {
        CNonMovable *nmobject = dynamic_cast<CNonMovable*>(neighboors.at(i));
        if(nmobject)
        {
            CDirt *dirt = dynamic_cast<CDirt*>(nmobject);
            if(dirt)
            {
                if(distance(dirt) < collisionDistance(dirt))
                dirts.push_back(dirt);
            }
        }
    }

    //delete nearby dirts
    if(dirts.size() != 0)
    {
        for(unsigned i=0; i<dirts.size(); i++)
        {
            clean(dirts.at(i));
        }
    }
    move();
}


void CCleaningRobot::clean(CDirt *dirt)
{
    dirt->getCleaned();
}
