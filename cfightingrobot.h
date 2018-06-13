#ifndef CFIGHTINGROBOT_H
#define CFIGHTINGROBOT_H
#include "crobot.h"

/// \brief Robot atakujący inne roboty
class CFightingRobot :public CRobot
{
public:
    CFightingRobot(CMap *m);
    CFightingRobot(qreal xv, qreal yv, CMap *m);
    CFightingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual ~CFightingRobot();
    /**
     * @brief Funkcja stara się w pierwszej kolejności uniknąć kolizji z innymi obiektami;
     * jeśli nie wystąpi kolizja, sprawdzane jest, czy robot jest na mapie;
     * jeśli nie jest na mapie, próbuje wrócić i kończy ruch;
     * w przeciwnym wypadku kieruje się w stronę najbliższego robota, o ile jakieś są w zasięgu;
     * jeśli w pobliżu nie ma żadnych brudów, robot porusza się losowo
     */
    void move();
    /**
     * @brief Funkcja sprawdza, czy w pobliżu są jakieś roboty, które można zaatakować
     * i wywołuje funkcję attack() na ewentualnych robotach;
     * następnie wywoływana jest funkcja move()
    */
    void update();
    /**
     * @brief Tworzy pocisk i wysyła go w kierunku podanego robota
     * @param robot Robot, którego należy zaatakować
     */
    void attack(CRobot *robot);
};

#endif // CFIGHTINGROBOT_H
