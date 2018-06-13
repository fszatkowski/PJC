#ifndef COBSTACLE_H
#define COBSTACLE_H
#include "cmovable.h"

/// Stała określająca szerokość przeszkody
const int obstacle_width=30;
/// Stała określająca wysokość przeszkody
const int obstacle_height=50;
/// Stała określająca prędkość przeszkody
const int obstacle_speed=5;

/// \brief Przeszkody poruszające się po mapie po linii prostej
class CObstacle :public CMovable
{
public:
    CObstacle(qreal xv, qreal yv, CMap *m);
    CObstacle(CMap *m);
    virtual ~CObstacle();
    /**
     * @brief Sprawdza, czy zajdzie kolizja z inną przeszkodą,
     * jeśli tak, próbuje uniknąć kolizji(jedna z przeszkód zatrzymuje się);
     * jeśli nastąpi kolizja z nieruchomym obiektem, obiekt ten jest niszczony;
     * jeśli przeszkoda wyjdzie poza mapę, wywoływana jest funkcja turn();
     * jeśli nie nastąpi kolizja z inną przeszkodą lub wyjście poza mapę, move()
     */
    void update();
    /**
     * @brief Zmienia współrzędne obiektu o odpowiednią prędkość
     * w kierunku określonym przez jego orientację
     */
    void move();
    /**
     * @brief Odwraca obiekt o 180*
     */
    void turn();
};

#endif // COBSTACLE_H
