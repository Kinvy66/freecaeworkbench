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

// docking ui
#include "FCModelBuilderWidget.h"
#include "FCSettingParametersWidget.h"
#include "FCGraphicOperateWidget.h"
#include "FCMessageLogViewWidget.h"


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
    buildDockingArea();   // error: 创建dock后无法运行
    
    
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

/**
 * @brief 获取模型构建窗口
 * @return 
 */
FCModelBuilderWidget *FCAppDockingArea::getModelBuilderWidge() const
{
    return mModelBuilderWidget;   
}

/**
 * @brief 获取参数设置构建窗口
 * @return 
 */
FCSettingParametersWidget *FCAppDockingArea::getSettingParametersWidget() const
{
    return mSettingParametersWidget;       
}

/**
 * @brief 获取图形操作窗口
 * @return 
 */
FCGraphicOperateWidget *FCAppDockingArea::getGraphicOperateWidget() const
{
    return mGraphicOperateWidget;       
}

/**
 * @brief 获取日志窗口
 * @return 
 */
FCMessageLogViewWidget *FCAppDockingArea::getMessageLogViewWidget() const
{
    return mMessageLogViewWidget;       
}

/**
 * @brief 构建dockwidget
 *
 * 可以通过dockManager()->findDockWidget(objname:QString)函数来找到对应的dockwidget并进行操作
 *
 * 所有本APP相关的关键object name都以fc打头:
 *
 * fc_modelBuilderWidgetDock
 * fc_settingParameterWidgetDock
 * fc_graphicOperateWidgetDock
 * fc_messageLogViewWidgetDock
 *
 */
void FCAppDockingArea::buildDockingArea()
{
    buildModelBuilderWidget();
    buildSettingParameterWidget();
    buildGraphicOperateWidget();
    buildMessageLogViewWidget();
    

    
    // mWorkFlowOperateDock->setIcon(QIcon(":/app/bright/Icon/showWorkFlow.svg"));
    
    mModelBuilderDock = createDockWidget(mModelBuilderWidget,
                                         ads::LeftDockWidgetArea,
                                         tr("模型"));
    
    mSettingParametersDock = createDockWidget(mSettingParametersWidget,
                                              ads::RightDockWidgetArea,
                                              tr("设置"),
                                              mModelBuilderDock->dockAreaWidget());
    
    mGraphicOperateDock = createDockWidget(mGraphicOperateWidget,
                                           ads::RightDockWidgetArea,
                                           tr("图形"),
                                           mSettingParametersDock->dockAreaWidget());
    
    mGraphicOperateDock->setIcon(QIcon(":/icon/icon/help.svg"));
    // mGraphicOperateDock->setFeature(ads::CDockWidget::DockWidgetClosable, false);
    
    mMessageLogDock = createDockWidget(mMessageLogViewWidget,
                                       ads::BottomDockWidgetArea,
                                       tr("消息"),
                                       mGraphicOperateDock->dockAreaWidget());
    
    resetDefaultSplitterSizes();

    resetText();
}

/**
 * @brief FCAppDockingArea::buildModelBuilderWidget
 */
void FCAppDockingArea::buildModelBuilderWidget()
{
    mModelBuilderWidget = new FCModelBuilderWidget();
    mModelBuilderWidget->setObjectName("fc_modelBuilderWidgetDock");
}

/**
 * @brief FCAppDockingArea::buildSettingParameterWidget
 */
void FCAppDockingArea::buildSettingParameterWidget()
{
    mSettingParametersWidget = new FCSettingParametersWidget(mApp);
    mSettingParametersWidget->setObjectName("fc_settingParameterWidgetDock");
}

/**
 * @brief FCAppDockingArea::buildGraphicOperateWidget
 */
void FCAppDockingArea::buildGraphicOperateWidget()
{
    mGraphicOperateWidget = new FCGraphicOperateWidget(mApp);
    mGraphicOperateWidget->setObjectName("fc_graphicOperateWidgetDock");
}

/**
 * @brief FCAppDockingArea::buildMessageLogViewWidget
 */
void FCAppDockingArea::buildMessageLogViewWidget()
{
    mMessageLogViewWidget = new FCMessageLogViewWidget(mApp);
    mMessageLogViewWidget->setObjectName("fc_messageLogViewWidgetDock");
    
}

void FCAppDockingArea::initConnection()
{
    
}

/**
	 * @brief 模型构建dock
	 * @return
	 */
ads::CDockWidget* FCAppDockingArea::getModelBuilderDock() const
{
    return mMessageLogDock;
}

/**
	 * @brief 参数设置窗口dock
	 * @return
	 */
ads::CDockWidget* FCAppDockingArea::getSettingParametersDock() const
{
    return mSettingParametersDock;
}

/**
	 * @brief 图形操作窗口dock
	 * @return
	 */
ads::CDockWidget* FCAppDockingArea::getGraphicOperateDock() const
{
    return mGraphicOperateDock;
}
/**
	 * @brief 信息窗口dock
	 * @return
	 */
ads::CDockWidget* FCAppDockingArea::getMessageLogDock() const
{
    return mMessageLogDock;    
}





