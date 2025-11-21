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
#include "FCMessageHandler.h"
#include "FCDumpCapture.h"
#include "FCDir.h"

// SARibbon
#include "SARibbonBar.h"

void setAppFont();
QString appPreposeDump();
void enableHDPIScaling();

int main(int argc, char* argv[])
{
    // 进行dump捕获
    FC::FCDumpCapture::initDump([]() -> QString { return appPreposeDump(); });
    //
    
    // 注册旋转文件消息捕获
    FC::fcRegisterRotatingMessageHandler(FC::FCDir::getLogFilePath());
    // DA::daRegisterConsolMessageHandler();
    for (int i = 0; i < argc; ++i) {
        qDebug() << "argv[" << i << "]" << argv[ i ];
    }
    // 高清屏的适配
    enableHDPIScaling();
    // 打印程序默认路径
    qDebug() << FC::FCDir();
    
    
    QApplication app(argc, argv);
    
    // 接口初始化
    FC::FCAppCore& core = FC::FCAppCore::getInstance();
    
    if (!core.initialized()) {
        qCritical() << QObject::tr("Kernel initialization failed");  // cn:内核初始化失败
        return -1;
    }
    
    FC::AppMainWindow w;
    w.show();
    
    // std::cout << "FreeCAE Workbench Application Started." << std::endl;
    qDebug() << "FreeCAE Workbench Application Started.";
    
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

/**
 * @brief 设置字体
 */
void setAppFont()
{
#ifdef Q_OS_WIN
    QFont font = QApplication::font();
    font.setFamily(QStringLiteral(u"微软雅黑"));
    QApplication::setFont(font);
#endif
}

/**
 * @brief dump前处理，设置dump文件名，同时生成一个系统信息记录
 *
 * 这里会生成一个dumpxxx.sysinfo的文件，记录了da的必要信息
 * @return
 */
QString appPreposeDump()
{
    QString dumpFileDir = FC::FCDir::getDumpFilePath();
    if (dumpFileDir.isEmpty()) {
        dumpFileDir = QDir::toNativeSeparators(QApplication::applicationDirPath() + "/dumps");
        QDir().mkpath(dumpFileDir);
    }
    
    QString baseName     = QDateTime::currentDateTime().toString("yyyyMMddhhmmss.zzz");
    QString dumpfileName = QString("dump%1.dmp").arg(baseName);
    return QDir::toNativeSeparators(dumpFileDir + "/" + dumpfileName);
}
