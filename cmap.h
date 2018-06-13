#ifndef CMAP_H
#define CMAP_H
#include "cgobject.h"
#include "cobject.h"
#include <QGraphicsScene>
#include "ccleaningrobot.h"
#include "cgcleaningrobot.h"
#include "csearchingrobot.h"
#include "cgsearchingrobot.h"
#include "cfightingrobot.h"
#include "cgfightingrobot.h"
#include "cobstacle.h"
#include "cgobstacle.h"
#include "cdirt.h"
#include "cgdirt.h"
#include "cmine.h"
#include "cgmine.h"
#include "ctreasure.h"
#include "cgtreasure.h"
#include <QRandomGenerator>

/// Stała definiująca wielkość mapy
const int map_size = 1000;

class CObject;
class CGObject;

/// \brief Mapa, na której poruszają się wszystkie obiekty
class CMap
{
private:
    /// Wskaźnik na scenę, na której umieszczane są obiekty
    QGraphicsScene *scene;
    //contains every objects in program
    /// Lista wszystkich obiektów logicznych na mapie
    std::vector<CObject*> ObjectList;
    /// Lista wszystkich obiektów graficznych na mapie
    std::vector<CGObject*> GObjectList;
public:
    /**
     * @brief Konstruktor wymaga podania wskaźnika do sceny
     * oraz tworzy określoną ilość obiektów różnego typu na mapie
     * @param scene Scena, na której umieszczone zostaną wszystkie obiekty
     */
    CMap(QGraphicsScene *scene);
    /**
     * @brief Funkcja zwracająca wskaźnik do sceny
     * @return scene
     */
    QGraphicsScene* getScene();
    //get list of every object
    /**
     * @brief Funkcja zwracająca wskaźnik na wszystkie obiekty logiczne
     * przypisane do mapy
     * @return ObjectList
     */
    std::vector<CObject*> getObjectList();
    /**
     * @brief Funkcja zwracająca wskaźnik na wszystkie obiekty graficzne
     * przypisane do mapy
     * @return GObjectList
     */
    std::vector<CGObject*> getGObjectList();
    //get list of the objects near given object
    /**
     * @brief Funkcja zwracająca wektor innych obiektów znajdujących się w zasięgu wskazanego obiektu
     * @param o Obiekt, dla którego sprawdzane jest otoczenie
     * @return Wektor obiektów, dla których odległość od o jest mniejsza od o.range
     */
    std::vector<CObject*> getNeighboorsList(CObject *o);
    /**
     * @brief Dodaje wskazany obiekt logiczny do listy obiektów znajdujących się na mapie
     * @param object Obiekt, który należy dodać do mapy
     */
    void addObject(CObject *object);
    /**
     * @brief Dodaje wskazany obiekt graficzny do listy obiektów znajdujących się na mapie
     * @param object Obiekt, który należy dodać do mapy
     */
    void addGObject(CGObject *gobject);
    //method for releasing object from the vector containers
    /**
     * @brief Usuwa z listy obiektów na mapie obiekt graficzny oraz odpowiadający mu obiekt logiczny
     * @param o Obiekt, który chcemy usunąc z mapy
     */
    void deleteFromMap(CObject *o);
    //templates defined in header, because otherwise compiler returns an error
    //method for adding n objects to the map
    /**
     * \brief Szablon służący do tworzenia na mapie nowych obiektów o podanym typie
     * param n Ilość obiektów danego typu, które chcemy utworzyć
     */
    template <class object_type, class gobject_type> void add(int n)
    {
        for(int i = 0; i<n; i++)
        {
            object_type *no = new object_type(this);
            addObject(no);
            gobject_type *ngo = new gobject_type(no);
            addGObject(ngo);
            scene->addItem(ngo);
        }
    }
    //method for adding object with probability 1/x
    /**
     * \brief Szablon służący do tworzenia obiektu danego typu
     * z prawdopodobieństwem 1/x, wywoływany przy każdym kroku programu
     * param x Określa prawdopodobieństwo, z jakim dodany zostanie obiekt
    */
    template <class object_type, class gobject_type> void spawn(int x)
    {
        if(!QRandomGenerator::global()->bounded(0, x))
        {
            object_type *no = new object_type(this);
            addObject(no);
            gobject_type *ngo = new gobject_type(no);
            addGObject(ngo);
            scene->addItem(ngo);
        }
    }

};
#endif // CMAP_H
