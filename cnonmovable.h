#ifndef CNONMOVABLE_H
#define CNONMOVABLE_H
#include "cobject.h"

/// \brief Klasa reprezentująca nieruchome obiekty na mapie
class CNonMovable :public CObject
{
protected:
    /// Zmienna reprezentująca wielkość danego obiektu lub jego wartość
    qreal value;
public:
    CNonMovable(qreal xv, qreal yv, qreal anglev, qreal rangev, qreal valuev, CMap *m);
    /**
     * @brief Funkcja zwracająca wartość value
     * @return value
     */
    qreal getvalue();
    virtual void update()=0;
};

#endif // CNONMOVABLE_H
