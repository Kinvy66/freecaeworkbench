/******************************************************************************
 * File     : FCDockingAreaInterface.h
 * Brief    : dock 区域的接口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-27
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCDOCKINGAREAINTERFACE_H
#define FCDOCKINGAREAINTERFACE_H
#include "FCInterfaceAPI.h"
#include "FCGlobals.h"
#include "FCUIExtendInterface.h"
// #include "FCData.h"
#include <QList>
#include <QPair>
#include "ads_globals.h"

// #include "DAWorkFlowOperateWidget.h"

class SARibbonMainWindow;

namespace ads
{
class CDockManager;
class CDockWidget;
class CDockAreaWidget;

} // namespace ads

namespace FC
{
class FCCoreInterface;
class FCUIInterface;
class FCModelBuilderWidget;
class FCSettingParametersWidget;
class FCGraphicOperateWidget;
class FCMessageLogViewWidget;

// class FCChartManageWidget;
// class FCChartOperateWidget;
// class FCDataManageWidget;
// class FCDataOperateWidget;
class FCMessageLogViewWidget;
// class FCWorkFlowNodeListWidget;
// class FCWorkFlowOperateWidget;

class FCINTERFACE_API FCDockingAreaInterface : public FCUIExtendInterface
{
    Q_OBJECT
    FC_DECLARE_PRIVATE(FCDockingAreaInterface)
public:
    /**
	 * @brief 定义了固定的dock窗口
	 */
    enum DockingArea
    {
        DockingAreaModelOperate,
        DockingAreaSetting,
        DockingAreaGraphic,
        DockingAreaMessageLog
    };
    
public:
    FCDockingAreaInterface(FCUIInterface* u);
    ~FCDockingAreaInterface();
    
    /**
	 * @brief 获取CDockManager
	 * @return
	 */
    ads::CDockManager* dockManager();
    /**
	 * @brief 获取CDockManager
	 * @return
	 */
    const ads::CDockManager* dockManager() const;
        
    
    
    /**
	 * @brief 创建中央dock窗体
	 * @param w
	 * @param widgetName
	 * @return
	 */
    ads::CDockWidget* createCenterDockWidget(QWidget* w,
                                             const QString& widgetName);
    
    /**
	 * @brief 创建一个dock窗体
	 * @param w
	 * @param area
	 * @param widgetName 注意，这里的是作为title同时作为objectname,但多语言应该单独设置title，因此在构造之后必须在设置单独的objname
	 * @param dockAreaWidget
	 * @return
	 */
    ads::CDockWidget* createDockWidget(QWidget* w,
                                       ads::DockWidgetArea area,
                                       const QString& widgetName,
                                       ads::CDockAreaWidget* dockAreaWidget = nullptr);
    /**
	 * @brief 创建一个浮动窗体
	 * @param w 窗口
	 * @param widgetName 窗体名称
	 * @param pos 位置
	 * @return
	 */
    ads::CDockWidget* createFloatingDockWidget(QWidget* w,
                                               const QString& widgetName,
                                               const QPoint& pos);
    
    /**
	 * @brief 创建一个tab dock
	 * @param w 窗口
	 * @param widgetName 窗体名称
	 * @param dockAreaWidget 停靠区域
	 * @return
	 */
    ads::CDockWidget* createDockWidgetAsTab(QWidget* w,
                                            const QString& widgetName,
                                            ads::CDockAreaWidget* dockAreaWidget);
    
    /**
	 * @brief 通过窗口查找对应的CDockWidget
	 * @note 注意此函数是O(n)复杂度
	 * @param w 要查询的窗口
	 * @return 如果没找到，返回nullptr
	 */
    ads::CDockWidget* findDockWidget(QWidget* w) const;
    
    /**
	 * @brief 隐藏某个窗体对应的dockwidget
	 * @param w 传入dock内部维护的widget或dockwidget都可以
	 */
    void hideDockWidget(QWidget* w);
    
    /**
	 * @brief 枚举DockingArea对应的窗口指针
	 * @param area
	 * @return
	 */
    ads::CDockWidget* dockingAreaToDockWidget(DockingArea area) const;
    
    /**
	 * @brief 唤起一个widget对应的dock widget，如果窗口关闭了，也会唤起
	 * @param w
	 * @sa raiseDockingArea
	 */
    void raiseDockByWidget(QWidget* w);
    
    /**
	 * @brief 唤起一个dock widget，如果窗口关闭了，也会唤起
	 * @param area
	 * @sa raiseDockByWidget
	 */
    void raiseDockingArea(DockingArea area);
    
    // 判断是否处于焦点
    bool isDockingAreaFocused(DockingArea area) const;
    
    /**
	 * @brief 获取中心区域
	 * @return
	 */
    ads::CDockAreaWidget* getCenterArea() const;
    
    /**
	 * @brief 获取中心窗口
	 * @return
	 */
    ads::CDockWidget* getCentralWidget() const;
    
    /**
	 * @brief 重置分割尺寸
	 */
    void resetDefaultSplitterSizes();
    
    /**
     * @brief 重置分割尺寸
     * @param area 
     */
    void resetDefaultSplitterSizes(ads::CDockAreaWidget* area);
    
    /**
     * @brief 重置分割子窗口
     * @param area
     * @param sizes
     */
    void resetDefaultSplitterSizes(ads::CDockAreaWidget* area, const QList<int>& sizes);
    
    /**
     * @brief 保存布局
     */
    void saveState();
    
    /**
     * @brief 恢复布局
     */
    void restoreState();
    
    /**
     * @brief 保存预设布局
     */
    void savePerspectives();
    
public:
    /*
	 * 接口:
	 */
    
    // 获取模型窗口
    virtual FCModelBuilderWidget* getModelBuilderWidge() const = 0;
    
    // 获取设置窗口
    virtual FCSettingParametersWidget* getSettingParametersWidget() const = 0;
    
    // 获取图形可视化窗口
    virtual FCGraphicOperateWidget* getGraphicOperateWidget() const = 0;
    
    // 获取日志显示窗口
    virtual FCMessageLogViewWidget* getMessageLogViewWidget() const = 0;
    

    
    /**
	 * @brief 获取当前选中的数据
	 * 	 * 如果用户当前焦点实在表格操作界面
	 * 	 * 如果用户打开一个表格，选中了其中一列，那么将返回那一列pd.Series作为数据，
	 * 如果用户选中了多列，那么每列作为一个DAData，最后组成一个QList<DAData>返回,如果用户打开了表格，但没选择任何列，这个函数返回这个表作为Data（pd.DataFrame）
	 * 	 * 如果用户没有选择列，但选中了单元格，那么相当于选中了单元格对应的列
	 * 	 * 如果什么都没选中，那么返回一个空的list
	 * 	 * 	 * 如果用户实在数据管理界面
	 * 	 * 返回选中的dataframe
	 * @return
	 */
    // virtual QList< DAData > getCurrentSelectDatas() const;
    
    
    /**
	 * @brief 模型构建dock
	 * @return
	 */
    virtual ads::CDockWidget* getModelBuilderDock() const = 0;
    
    /**
	 * @brief 参数设置窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getSettingParametersDock() const = 0;
    
    /**
	 * @brief 图形操作窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getGraphicOperateDock() const = 0;
    
    
    /**
	 * @brief 信息窗口dock
	 * @return
	 */
    virtual ads::CDockWidget* getMessageLogDock() const = 0;
    

    
    /**
	 * @brief 判断DataOperateWidget是否是在焦点
	 * @return
	 */
    // bool isDataOperateWidgetDockOnFource() const;
    
    /**
	 * @brief 判断DataManageWidget是否是在焦点
	 * @return
	 */
    // bool isDataManageWidgetDockOnFource() const;
    
public:
    /**
	 * @brief 获取当前的场景
	 * @return
	 */
    // DAWorkFlowGraphicsScene* getCurrentScene() const;
};
    

} // namespace FC

#endif // FCDOCKINGAREAINTERFACE_H
