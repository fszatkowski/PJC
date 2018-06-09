#include "cdirt.h"
#include <QRandomGenerator>
#include "cmap.h"

CDirt::CDirt(CMap *m)
    :CNonMovable(QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        QRandomGenerator::global()->bounded(-map_size/2, map_size/2),
                        0,
                        0,
                        QRandomGenerator::global()->bounded(20, 50),
                        m)
{
    objectShape = Circle;
    width = value;
    height = value;
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
    width = value;
    height = value;
}

void CDirt::getCleaned()
{
    delete this;
}
