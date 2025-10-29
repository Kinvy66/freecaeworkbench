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
#include "AppMainWindow.h"
// stl
#include <iostream>
// windows system only
#ifdef Q_OS_WIN
#include <windows.h>
#endif
// Qt
#include <QCommandLineParser>
#include <QProcess>
#include <QObject>
#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
// FC
#include "FCAppCore.h"

// SARibbon
#include "SARibbonBar.h"

void enableHDPIScaling();

int main(int argc, char* argv[])
{
    // 高清屏的适配
    enableHDPIScaling();
    QApplication app(argc, argv);
    
    // 接口初始化
    FC::FCAppCore& core = FC::FCAppCore::getInstance();
    
    if (!core.initialized()) {
        qCritical() << QObject::tr("Kernel initialization failed");  // cn:内核初始化失败
        return -1;
    }
    
    FC::AppMainWindow w;
    w.show();
    
    std::cout << "FreeCAE Workbench Application Started." << std::endl;
    
   int r = app.exec();

   return r;
}


/**
 * @brief 开启高dpi适配
 */
void enableHDPIScaling()
{
    SARibbonBar::initHighDpi();
}
