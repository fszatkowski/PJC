#ifndef CBULLET_H
#define CBULLET_H
#include "cmovable.h"
#include "cfightingrobot.h"
/**
 * \mainpage
 * \par Symulacja robotów mobilnych
 * Program ma za zadanie symulować zachowanie
 * różnych typów robotów mobilnych
 * poruszających się po planszy
 * i wykonujących różne zadania.
 * \author Filip Szatkowski
 * \date 13.06.2018
*/

///Stała określająca prędkość pocisku
const int bulletSpeed = 30;
///Stała określająca czas życia pocisku
const int bulletLifetime = 4;
///Stała określająca wielkość pocisku
const int bulletSize = 10;

/// \brief Pociski wystrzeliwywane przez roboty walczące
class CBullet :public CMovable
{
private:
    /// Życie pocisku
    int life;
    /// Wskaźnik na robota, który wystrzelił pocisk, potrzebny aby uniknąć usuwania go
    CFightingRobot *creator;
public:
    /**
     * @brief Poza dodatkowym wskaźnikiem do robota, konstruktor analogiczny do reszty ruchomych obiektów
     *
     *  @param r wskaźnik na robota, który wystrzelił dany pocisk
     */
    CBullet(CMap *m, CFightingRobot *r);
    virtual ~CBullet();
    /**
     * @brief Przy każdym wywołaniu przesuwa obiekt ze stałą prędkością
     * w kierunku, w którym został wystrzelony
     */
    void move();
    /**
     * @brief Przy każdym wywołaniu sprawdza otoczenie; jeśli koliduje z jakimś robotem,
     * który go nie wystrzelił, usuwa tego robota;
     * jeśli życie pocisku jest równe zero, usuwa pocisk;
     * jeśli nie, wywołuje move() i dekrementuje życie pocisku oraz zmniejsza jego rozmiar
     */
    void update();
};

#endif // CBULLET_H
