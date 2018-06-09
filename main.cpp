#include <QApplication>
#include <QWidget>
#include "cprogram.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    CProgram *program = new CProgram();

    return app.exec();
}
