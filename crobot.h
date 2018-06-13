#ifndef CROBOT_H
#define CROBOT_H
#include "cmovable.h"
#include "cnonmovable.h"
#include "cobstacle.h"

/// Stała określająca szerokość robota
const int robot_width = 30;
/// Stała określająca wysokość robota
const int robot_height = 20;
/// Stała określająca prędkość robota
const int robot_speed = 10;

/// \brief Klasa reprezentująca robota
class CRobot :public CMovable
{
protected:
    /// Lista nieruchomych obiektów zebranych przez robota
    std::vector<CNonMovable*> items;
public:
    /**
     * @brief Umieszcza robota na mapie w losowym miejscu z losowymi parametrami
     */
    CRobot(CMap *m);
    /**
     * @brief Umieszcza robota w konrektnym miejscu z losowymi parametrami
     * @param xv Współrzędna x
     * @param yv Współrzędna y     
    */
    CRobot(qreal xv, qreal yv, CMap *m);
    /**
     * @brief Umieszcza robota w konkretnym miejscu z konkretnymi parametrami
     * @param xv Współrzędna x
     * @param yv Współrzędna y
     * @param anglev Orientacja
     * @param rangev Zasięg
     */
    CRobot(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    virtual void update()=0;
    virtual void move()=0;
    //update x and y depending on angle and randomly change angle
    //if collecting some items - add them to the objects
    /**
     * @brief Funkcja dodająca nieruchomy obiekt do listy obiektów przechowywanych przez robota
     * @param item Obiekt, który jest dodawany
     */
    void addItem(CNonMovable *item);
    /**
     * @brief Funkcja zmieniająca położenie robota o jego prędkość
     * w kierunku określonym przez orientację;
     * losowo zmienia kąt o niewielką wartość, aby roboty nie jeździły cały czas po prostej
     */

    void moveRandomly();
    //if outside the map - try to come back
    /**
     * @brief Funkcja, która obraca robota tak, aby wrócił on na planszę
     */
    void returnToMap();

    //if seeking something - move in its direction
    /**
     * @brief Robot porusza się tak, aby zbliżyć się do podanego obiektu
     * @param o Obiekt, w którego kierunku robot ma się poruszać
     */
    void goTo(CObject *o);
    //try to avoid collision with given objects
    /**
     * @brief Robot porusza się tak, aby oddalić się od podanych obiektów i uniknąć zderzeń z nimi
     * @param o Nieruchome obiekty, które należy omijać
     * @param r Roboty, które należy omijać lub przepuszczać
     * @param ob Przeszkody, które należy omijać lub przepuszczać
     */
    void avoid(std::vector<CNonMovable*> o, std::vector<CRobot*> r, std::vector<CObstacle *> ob);
};
#endif // CROBOT_H
