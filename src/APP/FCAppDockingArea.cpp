/******************************************************************************
 * File     : FCAppDockingArea.h
 * Brief    : 负责docking窗口区域的管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppDockingArea.h"
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include "AppMainWindow.h"
// Qt-Advanced-Docking-System
#include "DockManager.h"
#include "DockAreaWidget.h"
// API相关
#include "FCAppCore.h"
// #include "FCAppProject.h"
#include "FCUIInterface.h"
#include "FCCommandInterface.h"
#include "FCAppCommand.h"
// #include "FCAppDataManager.h"

// message相关
// #include "FCMessageLogViewWidget.h"



//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

//===================================================
// FCAppDockingArea
//===================================================
FCAppDockingArea::FCAppDockingArea(FCUIInterface* u) : FCDockingAreaInterface(u)
{
    mApp     = qobject_cast< AppMainWindow* >(u->mainWindow());
    mAppCmd  = qobject_cast< FCAppCommand* >(u->getCommandInterface());
    // mDataMgr = qobject_cast< FCAppDataManager* >(core()->getDataManagerInterface());
    buildDockingArea();
}

FCAppDockingArea::~FCAppDockingArea()
{
    
}

void FCAppDockingArea::retranslateUi()
{
    resetText();
}


void FCAppDockingArea::resetText()
{
    // mWorkflowNodeListDock->setWindowTitle(tr("workflow node"));    // cn:节点
    // mChartManageDock->setWindowTitle(tr("charts manager"));        // cn:绘图管理
    // mDataManageDock->setWindowTitle(tr("datas manager"));          // cn:数据管理
    // mWorkFlowOperateDock->setWindowTitle(tr("workflow operate"));  // cn:工作流操作
    // mChartOperateDock->setWindowTitle(tr("chart operate"));        // cn:绘图操作
    // mDataOperateDock->setWindowTitle(tr("data operate"));          // cn:数据操作
    // mSettingContainerDock->setWindowTitle(tr("setting"));          // cn:设置
    // mMessageLogDock->setWindowTitle(tr("log"));                    // cn:消息
}

FCMessageLogViewWidget *FCAppDockingArea::getMessageLogViewWidget() const
{
    return mMessageLogViewWidget;
    
}

ads::CDockWidget *FCAppDockingArea::getMessageLogDock() const
{
    return mMessageLogDock;
}

void FCAppDockingArea::buildDockingArea()
{
    // 日志窗口
    // mMessageLogDock = createDockWidget(mMessageLogViewWidget,
    //                                    ads::BottomDockWidgetArea,
    //                                    QStringLiteral("da_messageLogViewWidgetDock"),
    //                                    mSettingContainerDock->dockAreaWidget());
    // mMessageLogDock->setIcon(QIcon(":/app/bright/Icon/showInfomation.svg"));
    
    resetDefaultSplitterSizes();
    
    initConnection();
    resetText();
}

void FCAppDockingArea::initConnection()
{
    
}

