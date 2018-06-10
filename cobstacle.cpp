#include "cobstacle.h"
#include <QRandomGenerator>
#include "cmap.h"
#include "cnonmovable.h"

CObstacle::CObstacle(qreal xv, qreal yv, CMap *m)
    :CMovable(xv, yv, 0, 0, m)
{
    objectShape = Rect;
    width = robot_width;
    height = robot_height;
}

CObstacle::CObstacle(CMap *m)
    :CMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              0,
              50, m)
{
    angle=QRandomGenerator::global()->bounded(0, 3)*M_PI/2;
    objectShape = Rect;
    width = robot_width;
    height = robot_height;
}

CObstacle::~CObstacle()
{
    map->deleteFromMap(this);
}

void CObstacle::move()
{
    x += obstacle_speed*cos(angle);
    y += obstacle_speed*sin(angle);
}

void CObstacle::turn()
{
    angle+=M_PI;
    if(angle>=2*M_PI)
        angle-=2*M_PI;
}

void CObstacle::update()
{

    std::vector<CObstacle*> obstacles;
    //check neigboorhood
    //if colliding with nonmovable object, delete it
    //if there are any other obstacles nearby, get them into vector
    for(unsigned int i = 0; i<map->getNeighboorsList(this).size(); i++)
    {
        CNonMovable *toErase = dynamic_cast<CNonMovable*>(map->getNeighboorsList(this)[i]);
        if(toErase)
        {
            if(collidesWith(toErase))
            {
                map->deleteFromMap(toErase);
                delete toErase;
            }
        }
        else
        {
            CMovable *mobject = dynamic_cast<CMovable*>(map->getNeighboorsList(this)[i]);
            if(mobject)
            {
                CObstacle *obstacle = dynamic_cast<CObstacle*>(mobject);
                if(obstacle)
                    obstacles.push_back(obstacle);
            }
        }
    }

    //check if there are any obstacles that may cause collision
    bool stay = 0;
    if(obstacles.size() != 0)
    {
        for(unsigned int i = 0; i<obstacles.size(); i++)
        {
            if(willCollide(obstacles[i], obstacle_speed, obstacle_speed))
            {
                if(std::abs(obstacles[i]->getAngle()-angle) != M_PI)
                    if(obstacles[i]->getAngle() >= angle)
                        stay = true;
            }
        }
    }
    if(stay)
        return;

    //check if object will not go outside the map
    else if((x+obstacle_speed*cos(angle) <= map_size/2)
            && (x+obstacle_speed*cos(angle) >= -map_size/2)
            && (y+obstacle_speed*sin(angle) <= map_size/2)
            && (y+obstacle_speed*sin(angle) >= -map_size/2))
        move();
    else
        turn();
}
