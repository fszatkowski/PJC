#ifndef CTREASURE_H
#define CTREASURE_H
#include "cnonmovable.h"

/// \brief Obiekty zbierane przez roboty zajmujące się ich szukaniem
class CTreasure :public CNonMovable
{
public:
    CTreasure(CMap *m);
    virtual ~CTreasure();
    /**
     * @brief Wartość skarbu wraz z upływem czasu maleje
     */
    void update();
    /**
     * @brief Funkcja usuwająca obiekt z mapy
     */
    void getCollected();
};

#endif // CTREASURE_H
