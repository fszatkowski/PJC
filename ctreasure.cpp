#include "ctreasure.h"
#include <QRandomGenerator>

CTreasure::CTreasure(CMap *m)
    :CNonMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        0,
                        0,
                        QRandomGenerator::global()->bounded(20, 50),
                        m)
{
}

CTreasure::~CTreasure()
{
}

//treasures are worth less with time
void CTreasure::update()
{
    int decrease = (QRandomGenerator::global()->bounded(50));
    if(!decrease)
    {
        value-=(QRandomGenerator::global()->bounded(1, 2));
        if(value<10)value=10;
    }
}

//when treasure is collected, remove it from the map
void CTreasure::getCollected()
{
    map->deleteFromMap(this);
}
