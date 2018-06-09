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
    qreal dx=obstacle_speed*cos(angle);
    qreal dy=obstacle_speed*sin(angle);

    if(x+dx<=map_size/2 && x+dx>=-map_size/2 && y+dy<=map_size/2 && y+dy >= -map_size/2)
    {
        x+=dx;
        y+=dy;
    }
    else
    {
        angle+=M_PI;
        if(angle>=2*M_PI)
            angle-=2*M_PI;
        dx=obstacle_speed*cos(angle);
        dy=obstacle_speed*sin(angle);
        x+=dx;
        y+=dy;
    }
}

void CObstacle::update()
{
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
    }
    move();    
}
