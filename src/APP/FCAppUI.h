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
#ifndef FCAPPUI_H
#define FCAPPUI_H

#include <FCUIInterface.h>

namespace FC 
{
class FCAppCore;
class FCAppCommand;
class FCAppActions;
class FCAppDockingArea;
class FCAppRibbonArea;
class FCStatusBar;


class FCAppUI : public FCUIInterface
{
    Q_OBJECT
public:
    FCAppUI(SARibbonMainWindow* m, FCCoreInterface* c);
    
    //获取主程序
    virtual QMainWindow* getMainWindow() const override;
    
    //获取界面的docking区域
    virtual FCDockingAreaInterface* getDockingArea() override;
    
    //获取界面的ribbon区域
    virtual FCRibbonAreaInterface* getRibbonArea() override;
    
    //创建ui
    void createUi();
    
    
public:
    //获取core
    FCAppCore* getAppCore();
    //减少一次dynamic_cast
    FCAppActions* getAppActions();
    //减少一次dynamic_cast
    FCAppCommand* getAppCmd();
    //获取dock
    FCAppDockingArea* getAppDockingArea();
    //获取ribbon
    FCAppRibbonArea* getAppRibbonArea();
    
protected:
    void createActions();
    void createCmd();
    void createDockingArea();
    void createRibbonArea();
    void createStatusBar();
    
public:
    FCAppActions* m_actions;
    FCAppCommand* m_cmd;
    FCAppDockingArea* m_dockingArea;
    FCAppRibbonArea* m_ribbonArea;
    FCStatusBar* mStatusBar;
};

} // namespace FC

#ifndef FC_APP_UI
/**
 * @def 获取@sa FCAppCore 实例
 * @note 使用此宏需要以下头文件：
 * -# FCAppCore.h
 */
#define FC_APP_UI FC::FCAppCore::getInstance().getUi()
#endif


#endif // FCAPPUI_H
