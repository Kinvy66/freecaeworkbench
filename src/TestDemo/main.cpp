#include "MainWindow.h"

#include <QApplication>
#include "gmsh.h"
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    gmsh::initialize();
    
    int p1 = gmsh::model::occ::addPoint(0, 0, 0);
    int p2 = gmsh::model::occ::addPoint(1, 0, 0);
    int p3 = gmsh::model::occ::addPoint(0, 1, 0);
    int p4 = gmsh::model::occ::addPoint(0, 0, 1, 0);
    
    std::cout << p1 << " " << p2 << " " << p3 << " " << p4 << std::endl;
    gmsh::model::occ::synchronize();
    
    w.show();
    return a.exec();
}

