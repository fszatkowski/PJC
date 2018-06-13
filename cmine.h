#ifndef CMINE_H
#define CMINE_H
#include "cnonmovable.h"
#include "crobot.h"

/// \brief Mina niszcząca roboty, które na nią wpadną
class CMine :public CNonMovable
{
public:
    CMine(CMap *m);
    virtual ~CMine();
    /**
     * @brief Sprawdza, czy z miną kolidują jakieś roboty
     */
    void update();
    /**
     * @brief Niszczy robota kolidującego z miną
     * @param robots Robot, którego należy usunąć
     */
    void destroy(std::vector<CRobot*> robots);
};

#endif // CMINE_H
