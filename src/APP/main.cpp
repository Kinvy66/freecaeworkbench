/******************************************************************************
 * File     : main.cpp
 * Brief    : app 
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
// #include "AppMainWindow.h"
#include <iostream>
#include <QDebug>
#include <QApplication>


int main(int argc, char* argv[])
{
    std::cout << "FreeCAE Workbench Application Started." << std::endl;
   
    
    // QApplication a(argc, argv);
    qDebug() << "Debug output test.";
    
    return 0;
    
}
