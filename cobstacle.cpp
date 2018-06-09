#include "cobstacle.h"
#include <QRandomGenerator>

CObstacle::CObstacle(qreal xv, qreal yv, CMap *m)
    :CMovable(xv, yv, 0, 0, m)
{
}

CObstacle::CObstacle(CMap *m)
    :CMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
              0,
              50, m)
{
    angle=QRandomGenerator::global()->bounded(0, 3)*M_PI/2;
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
    move();
}
