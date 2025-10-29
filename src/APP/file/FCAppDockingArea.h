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
#ifndef FCAPPDOCKINGAREA_H
#define FCAPPDOCKINGAREA_H

#include "FCDockingAreaInterface.h"

// #include "DAData.h"
// CDockArea
namespace ads
{
class CDockManager;
class CDockAreaWidget;
}
// SARibbon
class SARibbonMainWindow;

namespace FC 
{
class AppMainWindow;
class FCCoreInterface;
class FCAppDataManager;
class FCAppCommand;

// 模型窗口
// class FCModelWidget;
// 图形窗口
// class FCGraphicWidget;
// 设置窗口
// class FCSettingContainerWidget;
// 日志窗口
// class FCMessageLogViewWidget;


class FCAppDockingArea : public FCDockingAreaInterface
{
    Q_OBJECT
public:
public:
    FCAppDockingArea(FCUIInterface* u);
    ~FCAppDockingArea();
    
    // 翻译
    void retranslateUi() override;
    // 设置文本
    void resetText();
    
public:
    // 获取工作节点管理窗口
    // virtual FCMessageLogViewWidget* getMessageLogViewWidget() const override;
    
    /**
	 * @brief 信息窗口dock
	 * @return
	 */
    // ads::CDockWidget* getMessageLogDock() const override;
    
    
private:
    // 构建界面
    void buildDockingArea();
    // 创建各个相关的窗口
    // void buildWorkflowAboutWidgets();
    // void buildChartAboutWidgets();
    // void buildDataAboutWidgets();
    // void buildOtherWidgets();
    // 初始化信号槽
    void initConnection();
    
private:
    AppMainWindow* mApp;
    FCAppCommand* mAppCmd;  ///< cmd
    // FCAppDataManager* mDataMgr;
    
    
    // 日志窗口
    // FCMessageLogViewWidget* mMessageLogViewWidget;  ///< 日志窗口
    // ads::CDockWidget* mMessageLogDock;
};
} // namespace FC


#endif // FCAPPDOCKINGAREA_H
