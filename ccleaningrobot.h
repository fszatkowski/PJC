#ifndef CCLEANINGROBOT_H
#define CCLEANINGROBOT_H
#include "crobot.h"
#include "cdirt.h"

/// \brief Robot zajmujący się sprzątaniem brudów z mapy
class CCleaningRobot :public CRobot
{
public:
    CCleaningRobot(CMap *m);
    CCleaningRobot(qreal xv, qreal yv, CMap *m);
    CCleaningRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual ~CCleaningRobot();
    /**
     * @brief Funkcja stara się w pierwszej kolejności uniknąć kolizji z innymi obiektami;
     * jeśli nie wystąpi kolizja, sprawdzane jest, czy robot jest na mapie;
     * jeśli nie jest na mapie, próbuje wrócić i kończy ruch;
     * w przeciwnym wypadku kieruje się w stronę najbliższego brudu, o ile jakieś są w zasięgu;
     * jeśli w pobliżu nie ma żadnych brudów, robot porusza się losowo
     */
    void move();
    /**
     * @brief Funkcja sprawdza, czy występują kolizje z jakimiś brudami
     * i usuwa ewentualne kolidujące brudy;
     * następnie wywoływana jest funkcja move()
     */
    void update();
    /**
     * @brief Funkcja usuwa podany obiekt
     * @param Brud, który chcemy usunąć
     */
    void clean(CDirt *dirt);
};

#endif // CCLEANINGROBOT_H
