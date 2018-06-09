#ifndef CTREASURE_H
#define CTREASURE_H
#include "cnonmovable.h"

const int treasure_size = 20;

class CTreasure :public CNonMovable
{
public:
    CTreasure(CMap *m);
    ~CTreasure();
    void update();
    void getCollected();
};

#endif // CTREASURE_H
