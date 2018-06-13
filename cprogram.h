#ifndef CPROGRAM_H
#define CPROGRAM_H
#include <QTimer>
#include <QWidget>
#include "cmap.h"

/// Klasa zarządzająca działaniem programu
class CProgram :public QWidget
{
    Q_OBJECT
private:
    //no user control yet
    //CUser *user;
    /// Wskaźnik na mapę, na której znajdują się wszystkie obiekty, którymi zarządza program
    CMap *map;
public:
    /**
     * @brief Konstruktor programu tworzy scenę oraz widok,
     * ustawia ich paramtery oraz tworzy mapę,
     * a następnie inicjalizuje timer wywołujący co pewien okres czasu funkcję step()
     */
    CProgram();
public slots:
    /**
     * @brief W każdym kroku wywoływana jest funkcja update()
     * dla wszystkich obiektów logicznych na mapie,
     * następnie dla wszystkich obiektów graficznych wywoływana jest funkcja advance(),
     * na koniec każdego kroku losowo dodawane są do mapy obiekty różnego typu
     * aby w programie cały czas coś się działo
     */
    void step();
};

#endif // CPROGRAM_H
