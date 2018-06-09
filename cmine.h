#ifndef CMINE_H
#define CMINE_H
#include "cnonmovable.h"
#include "crobot.h"

class CMine :public CNonMovable
{
public:
    CMine(CMap *m);
    ~CMine();
    void update();
    void destroy(std::vector<CRobot*> robots);
};

#endif // CMINE_H
