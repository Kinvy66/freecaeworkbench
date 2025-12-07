#include "MainWindow.h"

#include <QApplication>
#include "gmsh.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    gmsh::initialize(argc, argv);
    w.show();
    return a.exec();
}

