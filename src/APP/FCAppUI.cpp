/******************************************************************************
 * File     : FCAppUI.cpp
 * Brief    : 总体界面接口，负责生成FCAppDockingArea和FCAppRibbonArea
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppUI.h"
#include "FCAppDockingArea.h"
#include "FCAppRibbonArea.h"
#include "FCAppActions.h"
#include "FCAppCommand.h"
#include "FCAppCore.h"
// #include "FCAppDataManager.h"
#include "AppMainWindow.h"
// #include "FCStatusBar.h"
//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;



//===================================================
// FCAppUI
//===================================================
FCAppUI::FCAppUI(SARibbonMainWindow* m, FCCoreInterface* c) : FCUIInterface(m, c)
{
    //! 这里不进行createUi的调用，因为很多地方的窗口的构建需要FCAppActions，
    //! 而FCAppActions又依赖FCAppUI，在FCAppCore构建FCAppUI时，如果在FCAppUI的构造函数中调用createUi
    //! 那么会导致FCAppUI构造过程中调用createDockingArea，而createDockingArea是创建窗口的主要函数，
    //! 很多窗口的创建又依赖FCAppActions，虽然FCAppActions已经创建，但如果把createUi放到FCAppUI构造函数中，
    //! 此时FCAppUI还未构造完成，FCAppUI未构造完成就导致FCAppCore还无法持有FCAppUI指针，
    //! 那么createDockingArea构造各种窗口时就无法通过FC_APP_UI_ACTIONS宏（FC::FCAppCore::getInstance().getUi()->getActions()）来获取action
    //!
    //! 因此createUi要等FCAppCore持有FCAppUI指针后再调用
    //!
}

/**
 * @brief 获取主程序
 * @return 
 */
QMainWindow* FCAppUI::getMainWindow() const
{
    return static_cast< QMainWindow* >(m_ribbonArea->app());
}

/**
 * @brief 获取界面的docking区域
 * @return 
 */
FCDockingAreaInterface* FCAppUI::getDockingArea()
{
    return m_dockingArea;
}

/**
 * @brief 获取界面的ribbon区域
 * @return 
 */
FCRibbonAreaInterface* FCAppUI::getRibbonArea()
{
    return m_ribbonArea;
}

/**
 * @brief 创建ui
 */
void FCAppUI::createUi()
{
    createCmd();      // cmd必须先创建，因为Actions会用到cmd的
    createActions();  // Actions第二个创建
    createDockingArea();
    createRibbonArea();
    m_ribbonArea->setDockingArea(m_dockingArea);
    createStatusBar();
}

/**
 * @brief 获取app core
 * @return
 */
FCAppCore* FCAppUI::getAppCore()
{
    return qobject_cast< FCAppCore* >(core());
}

/**
 * @brief 获取app actions, 减少一次dynamic_cast
 * @return 
 */
FCAppActions* FCAppUI::getAppActions()
{
    return m_actions;
}

/**
 * @brief 获取app cmd, 减少一次dynamic_cast
 * @return 
 */
FCAppCommand* FCAppUI::getAppCmd()
{
    return m_cmd;
}

/**
 * @brief //获取dock
 * @return 
 */
FCAppDockingArea* FCAppUI::getAppDockingArea()
{
    return m_dockingArea;
}

/**
 * @brief 获取ribbon
 * @return 
 */
FCAppRibbonArea* FCAppUI::getAppRibbonArea()
{
    return m_ribbonArea;
}

/**
 * @brief 创建action
 */
void FCAppUI::createActions()
{
    m_actions = new FCAppActions(this);
    // m_actions->retranslateUi();  // 显示调用文字翻译
    registeAction(m_actions);
}

/**
 * @brief 创建cmd
 */
void FCAppUI::createCmd()
{
    m_cmd = new FCAppCommand(this);
    registeCommand(m_cmd);
}

/**
 * @brief 创建docking 区域
 */
void FCAppUI::createDockingArea()
{
    m_dockingArea = new FCAppDockingArea(this);
    registeExtend(m_dockingArea);
}

/**
 * @brief 创建ribbon 区域
 */
void FCAppUI::createRibbonArea()
{
    m_ribbonArea = new FCAppRibbonArea(this);
    registeExtend(m_ribbonArea);
}

/**
 * @brief 创建statusBar
 */
void FCAppUI::createStatusBar()
{
    // QMainWindow* m = getMainWindow();
    // mStatusBar     = new FCStatusBar(m);
    // m->setStatusBar(mStatusBar);
}
