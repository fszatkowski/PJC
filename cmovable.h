#ifndef CMOVABLE_H
#define CMOVABLE_H
#include "cobject.h"

/// \brief Klasa reprezentująca obiekty z możliwością poruszania się po mapie
class CMovable :public CObject
{
public:
    CMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual void update()=0;
    /**
     * @brief Funkcja zmieniająca położenie obiektu przy każdym kroku;
     * implementacja zależy od typu obieku
     */
    virtual void move()=0;
};

#endif // CMOVABLE_H
