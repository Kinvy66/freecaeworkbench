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
class FCModelBuilderWidget;
// 图形窗口
class FCGraphicOperateWidget;
// 设置窗口
class FCSettingParametersWidget;
// 日志窗口
class FCMessageLogViewWidget;


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
    // 获取模型窗口
    virtual FCModelBuilderWidget* getModelBuilderWidge() const override;
    
    // 获取设置窗口
    virtual FCSettingParametersWidget* getSettingParametersWidget() const override;
    
    // 获取图形可视化窗口
    virtual FCGraphicOperateWidget* getGraphicOperateWidget() const override;
    
    // 获取日志显示窗口
    virtual FCMessageLogViewWidget* getMessageLogViewWidget() const override;
    
    /**
	 * @brief 模型构建dock
	 * @return
	 */
    virtual ads::CDockWidget* getModelBuilderDock() const override;
    
    /**
	 * @brief 参数设置窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getSettingParametersDock() const override;
    
    /**
	 * @brief 图形操作窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getGraphicOperateDock() const override;
    
    
    /**
	 * @brief 信息窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getMessageLogDock() const override;
    
    
private:
    // 构建界面
    void buildDockingArea();
    // 创建各个相关的窗口
    void buildModelBuilderWidget();
    void buildSettingParameterWidget();
    void buildGraphicOperateWidget();
    void buildMessageLogViewWidget();
    
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
    
    // 模型构建窗口
    FCModelBuilderWidget* mModelBuilderWidget;                  ///< 模型构建窗口
    ads::CDockWidget* mModelBuilderDock;                        ///< mModelBuilderWidget对应的docking
    
    // 参数设置构建窗口
    FCSettingParametersWidget* mSettingParametersWidget;        ///< 参数设置窗口
    ads::CDockWidget* mSettingParametersDock;                   ///< mSettingParametersWidget对应的docking
    
    // 图形操作窗口
    FCGraphicOperateWidget* mGraphicOperateWidget;              ///< 图形操作窗口
    ads::CDockWidget* mGraphicOperateDock;                      ///< mGraphicOperateWidget对应的docking
    
    // 日志窗口
    FCMessageLogViewWidget* mMessageLogViewWidget;              ///< 日志窗口
    ads::CDockWidget* mMessageLogDock;                          ///< mMessageLogViewWidget对应的docking

};
} // namespace FC


#endif // FCAPPDOCKINGAREA_H
