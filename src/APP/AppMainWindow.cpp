/******************************************************************************
 * File     : AppMainWindow.cpp
 * Brief    : 主窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/

#include "AppMainWindow.h"

// Qt 相关
#include <QMessageBox>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QVector>
#include <QDataStream>
#include <QCloseEvent>
#include <QFile>
#include <QBuffer>

// SARibbonBar
#include "SARibbonBar.h"

// Qt-Advanced-Docking-System
#include "DockManager.h"

namespace FC {

AppMainWindow::AppMainWindow(QWidget *parent)
    : SARibbonMainWindow(parent)
{
    
}

AppMainWindow::~AppMainWindow()
{
    
}

} // namespace FC
