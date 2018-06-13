#ifndef CSEARCHINGROBOT_H
#define CSEARCHINGROBOT_H
#include "crobot.h"
#include "ctreasure.h"

/// \brief Robot zajmujący się szukaniem skarbów
class CSearchingRobot :public CRobot
{
public:
    CSearchingRobot(CMap *m);
    CSearchingRobot(qreal xv, qreal yv, CMap *m);
    CSearchingRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual ~CSearchingRobot();
    /**
     * @brief Funkcja stara się w pierwszej kolejności uniknąć kolizji z innymi obiektami;
     * jeśli nie wystąpi kolizja, sprawdzane jest, czy robot jest na mapie;
     * jeśli nie jest na mapie, próbuje wrócić i kończy ruch;
     * w przeciwnym wypadku kieruje się w stronę najbliższego skarbu, o ile jakieś są w zasięgu;
     * jeśli w pobliżu nie ma żadnych brudów, robot porusza się losowo
     */
    void move();
    /**
     * @brief Funkcja sprawdza, czy występują kolizje z jakimiś skarbami
     * i zbiera ewentualne kolidujące skarby;
     * następnie wywoływana jest funkcja move()
     */
    void update();
    /**
     * @brief Funkcja dodająca do listy zebranych obiektów podany skarb
     * @param treasure Skarb, który należy zebrać
     */
    void collect(CTreasure *treasure);
};
#endif // CSEARCHINGROBOT_H
