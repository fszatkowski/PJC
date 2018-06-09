#ifndef CDIRT_H
#define CDIRT_H
#include "cnonmovable.h"

class CDirt :public CNonMovable
{
public:
    CDirt(CMap *m);
    ~CDirt();
    void update();
    void getCleaned();
};

#endif // CDIRT_H
