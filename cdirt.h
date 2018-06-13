#ifndef CDIRT_H
#define CDIRT_H
#include "cnonmovable.h"

/// \brief Brudy zbierane przez roboty sprzątające
class CDirt :public CNonMovable
{
public:
    CDirt(CMap *m);
    virtual ~CDirt();
    /**
     * @brief W każdej turze losowo może nastąpić rozrost brudu
     */
    void update();
    /**
     * @brief Funkcja wywoływana w celu usunięcia danego brudu
     */
    void getCleaned();
};

#endif // CDIRT_H
