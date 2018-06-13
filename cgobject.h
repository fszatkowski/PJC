#ifndef CGOBJECT_H
#define CGOBJECT_H
#include <QGraphicsItem>
#include <QPainter>
#include "cobject.h"

class CObject;
class CMap;

/// \brief Klasa służąca do wyświetlania na mapie obiektów logicznych
class CGObject :public QGraphicsItem
{
protected:
    /// Obiekt logiczny, którego reprezentacją jest dany obiekt graficzny
    CObject *object;
    /// Wskaźnik na mapę, na której znajduje się obiekt graficzny
    CMap *map;
public:
    /**
     * @brief Obiekt graficzny zawsze inicjalizowany jest
     * wskaźnikiem na obiekt logiczny, który reprezentuje;
     * wskaźnik na mapę pobierany jest z obiektu logicznego
     * @param o Obiekt logiczny, który ma być reprezentowany
     */
    CGObject(CObject *o);
    /**
     * @brief Zwraca wskaźnik do obiektu logicznego reprezentowanego przez
     * dany obiekt graficzny
     * @return object
     */
    CObject* getCObject();
    /**
     * @brief Funkcja rysująca obiekt na mapie na podstawie parametrów
     * obiektu logicznego
     */
    virtual void advance() = 0;
    /**
     * @brief Zwraca prostokąt reprezentujący obrys obiektu;
     * potrzebne do prawidłowego odświeżania obiektu na mapie;
     * implementacja różna dla klas pochodnych
     * @return QRecF reprezentujący obrys obiektu
     */
    virtual QRectF boundingRect() const = 0;
    /**
     * @brief Funkcja określająca kształt obiektu, jej implementacja zależy od rodzaju klasy pochodnej
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) = 0;
};

#endif // CGOBJECT_H
