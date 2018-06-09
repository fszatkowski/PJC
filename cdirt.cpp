#include "cdirt.h"
#include <QRandomGenerator>

CDirt::CDirt(CMap *m)
    :CNonMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        0,
                        0,
                        QRandomGenerator::global()->bounded(20, 50),
                        m)
{
}

CDirt::~CDirt()
{
    map->deleteFromMap(this);
}

//dirts are getting larger with time
void CDirt::update()
{
    int change_size = (QRandomGenerator::global()->bounded(4));
    if(!change_size)
    {
        value+=(QRandomGenerator::global()->bounded(1, 2));
        if(value>50)value=50;
    }
}

void CDirt::getCleaned()
{
    delete this;
}
