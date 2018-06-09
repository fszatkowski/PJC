#ifndef CPROGRAM_H
#define CPROGRAM_H
#include <QTimer>
#include <QWidget>
#include "cuser.h"
#include "cmap.h"

class CProgram :public QWidget
{
    Q_OBJECT
private:
    CUser *user;
    CMap *map;
public:
    CProgram();
public slots:
    void step();
};

#endif // CPROGRAM_H
