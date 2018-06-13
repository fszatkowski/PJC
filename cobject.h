#ifndef COBJECT_H
#define COBJECT_H
#include <QGraphicsItem>

class CMap;

//shape is used to determine collisions between objects
/// \brief Możliwy kształt obiektu
enum shape
{
    Rect = 1,
    Square = 2,
    Circle = 3
};

/// \brief Klasa reprezentująca każdy obiekt na mapie
class CObject
{
protected:
    //coordinates
    /// Współrzędna x
    qreal x;
    /// Współrzędna y
    qreal y;
    //orientation
    /// Orientacja obiektu
    qreal angle;
    //region 'seen' by object
    /// Promień, w jakim obiekt może zauważać inne obiekty
    qreal range;
    //map that object occupies
    /// Wskaźnik na mapę, na której znajduje się obiekt
    CMap *map;
    //width, height and shape used for collision detection
    /// Kształt obiektu używany przy obliczaniu kolizji
    shape objectShape;
    /// Szerokość obiektu
    qreal width;
    /// Wysokość obiektu
    qreal height;
public:
    //constructor
    /**
     * @brief Konstruktor pozwala tylko na stworzenie obiektu o konkretnych parametrach;
     * kształt obiektu określany jest przez konstruktory klas dziedziczących
     * w zależności od rodzaju obiektu 
     * @param xv Współrzędna x
     * @param yv Współrzędna y
     * @param anglev Orientacja obiektu
     * @param rangev Zasięg obiektu
     * @param m Wskaźnik na mapę, na której znajduje się obiekt
     */
    CObject(qreal xv, qreal yv, qreal anglev, qreal rangev, CMap *m);
    /**
     * @brief Funkcja wywoływana przy każdym kroku programu dla wszystkich obiektów,
     * oddziaływuje na otoczenie oraz podejmuje decyzje na podstawie tego otoczenia,
     * implementacja jest różna dla każdej z podklas na najniższym szczeblu hierarchii dziedziczenia
     */
    virtual void update()=0;
    /**
     * @brief Zwraca wartość współrzędnej x obiektu
     * @return x
     */
    qreal getX();
    /**
     * @brief Zwraca wartość współrzędnej y obiektu
     * @return y
     */
    qreal getY();
    /**
     * @brief Zwraca kąt, pod jakim znajduje się obiekt(w radianach)
     * @return angle
     */
    qreal getAngle();
    /**
     * @brief Zwraca zasięg obiektu
     * @return range
     */
    qreal getRange();
    /**
     * @brief Zwraca wskaźnik do mapy, na której znajduje się obiekt
     * @return map
     */
    CMap *getMap();
    /**
     * @brief Zwraca szerokość obiektu
     * @return width
     */
    qreal getWidth();
    /**
     * @brief Zwraca wysokość obiektu
     * @return height
     */
    qreal getHeight();
    /**
     * @brief Zwraca kształt obiektu
     * @return shape
     */
    shape getShape();
    //calculate distance between two objects
    /**
     * @brief Zwraca odległość między obiektem, 
     * dla którego wywoływana jest metoda
     * oraz obiektem, do którego przyjmuje wskaźnik
     * @param o Obiekt, dla którego liczona jest odległość
     * @return Dystans między obiektami w metryce euklidesowej
     */    
    qreal distance(CObject *o);
    //calculate maximum distance at which robots collide
    /**
     * @brief Na podstawie kształtu obiektów oblicza maksymalną 
     * odległość, przy której nie kolidują one ze sobą
     * @param o Obiekt, dla którego liczona jest odległość
     * @return Dystans w metryce euklidesowej
     */    
    qreal collisionDistance(CObject *o);
    //check if two objects collide
    /**
     * @brief Zwraca informację o tym, czy dany obiekt koliduje 
     * z obiektem, dla którego wywoływana jest metoda
     * @param o Obiekt, dla którego sprawdzana jest kolizja
     * @return 1 oznacza kolizję, 0 brak kolizji
     */
    bool collidesWith(CObject *o);
    //check if two objects will collide after their move
    /**
     * @brief Zwraca informację o tym, czy dwa obiekty o różnych prędkościach
     * po wykonaniu ruchu będą ze sobą kolidować
     * @param o Obiekt, dla którego sprawdzana jest ewentualna kolizja
     * @param thisSpeed Prędkość, z jaką porusza się obiekt, 
     * dla którego wywoływana jest metoda
     * @param oSpeed Prędkość obiektu, dla którego sprawdazana jest kolizja
     * @return 1 oznacza kolizję w następnej turze, 0 oznacza jej brak
     */
    bool willCollide(CObject *o, qreal thisSpeed, qreal oSpeed);
};

#endif // COBJECT_H
