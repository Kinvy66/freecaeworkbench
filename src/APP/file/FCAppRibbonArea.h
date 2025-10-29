/******************************************************************************
 * File     : FCAppRibbonArea.h
 * Brief    : App的Ribbon区域接口，负责ribbon层的管理和调度
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPRIBBONAREA_H
#define FCAPPRIBBONAREA_H

#include <FCRibbonAreaInterface.h>
#include <QObject>
#include <QAction>
#include <QUndoStack>
#include <QSpinBox>
#include <QWidgetAction>
// #include "DADataManageWidget.h"
// #include "DAWorkFlowGraphicsScene.h"

#define FCAPPRIBBONAREA_COMMON_SETTING_H(MiddleName)                                                                   \
public:                                                                                                                \
    QPen get##MiddleName##Pen() const;                                                                                 \
    QBrush get##MiddleName##Brush() const;                                                                             \
    QFont get##MiddleName##Font() const;                                                                               \
    QColor get##MiddleName##FontColor() const;                                                                         \
    public slots:                                                                                                          \
    void set##MiddleName##Pen(const QPen& v);                                                                          \
    void set##MiddleName##Brush(const QBrush& v);                                                                      \
    void set##MiddleName##Font(const QFont& v);                                                                        \
    void set##MiddleName##FontColor(const QColor& v);

// Qt
class QComboBox;
class QToolBar;
class QMenuBar;
class QFontComboBox;
class QUndoStack;

// Qt-Advanced-Docking-System 前置申明
namespace ads
{
class CDockWidget;
}

// SA Ribbon
class SARibbonBar;
class SARibbonCategory;
class SARibbonPanel;
class SARibbonContextCategory;
class SARibbonLineWidgetContainer;
class SARibbonButtonGroupWidget;
class SARibbonCtrlContainer;

namespace FC 
{
class AppMainWindow;
class FCAppDockingArea;
class FCAppActions;
class FCAppCommand;
class FCPyDTypeComboBox;
class FCCommandInterface;
class FCAppDataManager;
class FCDataOperateOfDataFrameWidget;
class FCAppProject;
class FCAppRibbonApplicationMenu;
//
class FCDataOperatePageWidget;
// 窗口
class FCFontEditPannelWidget;
class FCShapeEditPannelWidget;
class FCColorPickerButton;
class FCFigureWidget;
class FCChartOperateWidget;
class FCChartWidget;
class FCDataOperateWidget;
class FCWorkFlowEditWidget;
class FCWorkFlowOperateWidget;

/**
 * @brief App的Ribbon区域接口，负责ribbon层的管理和调度
 *
 * @todo 后续抽象出DAAppRibbonAreaInterface，DAAppRibbonArea继承DAAppRibbonAreaInterface，并把可暴露的方法暴露出来，实现插件化
 *
 *```
 * 标签的固定objectname
 * 主页标签:da-ribbon-category-main
 *     通用pannel:da-ribbon-pannel-main.common
 *     数据操作pannel：da-pannel-main.data-opt
 *     绘图操作pannel：da-pannel-main.chart-opt
 *     工作流pannel：da-pannel-main.workflow
 *     设置pannel：da-pannel-main.setting
 * 数据标签:da-ribbon-category-data
 *     数据操作pannel:da-pannel-data.data-opt
 *     数据文件夹操作pannel:da-pannel-data.folder-opt
 * 视图标签:da-ribbon-category-view
 *     视图pannel:da-pannel-view.main
 * 编辑标签:da-ribbon-category-edit
 *     工作流编辑pannel:da-pannel-edit.workflow
 * 绘图标签：da-ribbon-category-figure
 *     绘图编辑：da-pannel-figure.fig_setting
 *     添加绘图：da-pannel-figure.chart-add
 * 工作流编辑上下文标签：da-ribbon-contextcategory-workflow
 *  工作流视图category：da-ribbon-category-workflow.view
 *     视图pannel：da-pannel-context.workflow.view
 *     导出pannel：da-pannel-context.workflow.export
 *  工作流编辑category：da-ribbon-category-workflow.edit
 *     条目pannel：da-pannel-context.workflow.item
 *     文本pannel：da-pannel-context.workflow.text
 *     背景pannel：da-pannel-context.workflow.background
 *     分组pannel：da-pannel-context.workflow.group
 *  工作流运行category：da-ribbon-category-workflow.run
 *     运行pannel：da-pannel-context.workflow.run
 *
 * DataFrame上下文标签:da-ribbon-contextcategory-dataframe
 * Chart上下文标签：da-ribbon-contextcategory-chart
 *  Chart编辑category：da-ribbon-category-chart.edit
 *     绘图窗口设置pannel:da-pannel-context-chartedit.fig_setting
 *     图表设置pannel:da-pannel-context-chartedit.chart_setting
 * ```
 */

class FCAppRibbonArea : public FCRibbonAreaInterface
{
    friend class AppMainWindow;
    Q_OBJECT
public:
public:
    /**
	 * @brief 上下文类型
	 */
    enum ContextCategoryType
    {
        ContextCategoryData,      ///< Data相关的上下文
        ContextCategoryWorkflow,  ///< Workflow相关的上下文
        ContextCategoryChart,     ///< Chart相关的上下文
        AllContextCategory        ///< 这个代表所有的上下文
    };
    Q_ENUM(ContextCategoryType)
    
public:
    FCAppRibbonArea(FCUIInterface* u);
    ~FCAppRibbonArea();
    
    // 发生语言变更时会触发此函数
    virtual void retranslateUi() override;
    // 获取app
    AppMainWindow* app() const;
    // 获取ribbon
    SARibbonBar* ribbonBar() const;
    // 获取主标签
    SARibbonCategory* getRibbonCategoryMain() const;
    // 通过FCCommandInterface构建redo/undo的action
    void buildRedoUndo();
    // 更新ActionLockBackgroundPixmap的check statue
    // void updateActionLockBackgroundPixmapCheckStatue(bool c);
    // 显示上下文(会把其他上下文隐藏)
    void showContextCategory(ContextCategoryType type);
    // 隐藏上下文
    void hideContextCategory(ContextCategoryType type);
    
    
public:
    //===================================================
    // 更新操作
    //===================================================
    // 更新绘图相关的ribbon
    // void updateFigureAboutRibbon(DAFigureWidget* fig);
    // void updateChartAboutRibbon(DAChartWidget* chart);
    // void updateChartGridAboutRibbon(DAChartWidget* chart);
    // void updateChartZoomPanAboutRibbon(DAChartWidget* chart);
    // void updateChartPickerAboutRibbon(DAChartWidget* chart);
    // void updateChartLegendAboutRibbon(DAChartWidget* chart);
    
    // void updateWorkflowAboutRibbon(DAWorkFlowOperateWidget* wfo);
    // 重置文字
    void resetText();
    
private:
    // 构建所有的action
    void buildMenu();
    // 构建界面
    void buildRibbon();
    // 构建主页标签
    void buildRibbonMainCategory();
    // 构建几何标签
    void buildRibbonGeometryCategory();
    // 构建网格标签
    void buildRibbonMeshCategory();
    // 构建研究标签
    void buildRibbonStudyCategory();
    // 构建结果标签
    void buildRibbonResultCategory();
    // 构建工具标签
    void buildRibbonToolsCategory();
    // 构建快速响应栏
    void buildRibbonQuickAccessBar();
    // todo: 上下文标签页

    // 构建ApplicationMenu
    void buildApplicationMenu();
    // 构建右工具栏
    void buildRightButtonBar();
    
    FCAPPRIBBONAREA_COMMON_SETTING_H(Edit)
    FCAPPRIBBONAREA_COMMON_SETTING_H(WorkFlowEdit)
    
    /**
	 * @brief 设置dock区，有些pannel的action是依赖dock界面的，统一在这里设置
	 * @param dock
	 */
    void setDockingArea(FCAppDockingArea* dock);
    
Q_SIGNALS:
    
private Q_SLOTS:
    
    
public:
    ///////////////////////////////////////////
    /// ribbon
    ///////////////////////////////////////////
    // pass
    
    FCAppActions* m_actions;       ///< 所有的action管理
    FCAppDockingArea* m_dockArea;  ///< 注意这个变量不能在构造函数中调用
    AppMainWindow* m_app;
    FCAppCommand* m_appCmd;        ///< cmd
    //----------------------------------------------------
    // Main
    //----------------------------------------------------
    SARibbonCategory* m_categoryMain;           ///< 主页标签
    SARibbonPanel* m_pannelMainFileOpt;         ///< 文件操作
    SARibbonPanel* m_pannelModelOpt;            ///< 模型操作
    SARibbonPanel* m_pannelGeometryOpt;         ///< 几何操作
    SARibbonPanel* m_pannelMeshOpt;             ///< 网格操作
    SARibbonPanel* m_pannelStudyOpt;            ///< 研究操作
    SARibbonPanel* m_pannelLayoutOpt;           ///< 布局操作
    
    //----------------------------------------------------
    // Geometry
    //----------------------------------------------------
    SARibbonCategory* m_categoryGeometry;           ///< 几何标签
    SARibbonPanel* m_pannelGeometryBuildOpt;        ///< 构建操作
    SARibbonPanel* m_pannelGeometryImpExpOpt;       ///< 导入/导出操作
    SARibbonPanel* m_pannelGeometryPrimOpt;         ///< 体素操作
    // SARibbonPanel* m_pannelGeometryPrimOpt;         ///< 体素操作
    SARibbonPanel* m_pannelGeometryWrkPlaneOpt;     ///< 工作平面操作
    SARibbonPanel* m_pannelGeometryOperatopsOpt;    ///< 操作
    SARibbonPanel* m_pannelGeometryOtherOpt;        ///< 其他操作
    
    //----------------------------------------------------
    // Mesh
    //----------------------------------------------------
    SARibbonCategory* m_categoryMesh;           ///< 网格标签
    SARibbonPanel* m_pannelMeshBuildOpt;        ///< 构建操作
    SARibbonPanel* m_pannelMeshImpExpOpt;       ///< 导入/导出操作
    SARibbonPanel* m_pannelMeshGenerateOpt;     ///< 生成操作
    SARibbonPanel* m_pannelMeshAttrOpt;         ///< 属性操作
    SARibbonPanel* m_pannelMeshOperationOpt;    ///< 编辑操作
    SARibbonPanel* m_pannelMeshEvaluateOpt;     ///< 计算操作
    SARibbonPanel* m_pannelMeshClearOpt;        ///< 清除操作
    
    //----------------------------------------------------
    // Study
    //----------------------------------------------------
    SARibbonCategory* m_categoryStudy;           ///< 研究标签
    // SARibbonPanel* m_pannelStudyOpt;             ///< 计算操作
    SARibbonPanel* m_pannelStudySolverOpt;       ///< 求解器操作
    SARibbonPanel* m_pannelStudyStepOpt;         ///< 研究步骤
    SARibbonPanel* m_pannelStudyCleanOpt;        ///< 清除操作
    
    //----------------------------------------------------
    // Result
    //----------------------------------------------------
    SARibbonCategory* m_categoryResult;      ///< 结果标签
    SARibbonPanel* m_pannelPlotGroupRes;     ///< 绘图组操作
    SARibbonPanel* m_pannelDataSetRes;       ///< 数据集
    SARibbonPanel* m_pannelNumrcalRes;       ///< 数值结果
    SARibbonPanel* m_pannelExportRes;        ///< 导出结果
    SARibbonPanel* m_pannelClearRes;         ///< 清除操作
    
    //----------------------------------------------------
    // Tools
    //----------------------------------------------------
    SARibbonCategory* m_categoryTools;   ///< 工具标签
    SARibbonPanel* m_pannelDevTools;     ///< 开发工具

   
    // ApplicationMenu
    FCAppRibbonApplicationMenu* mApplicationMenu;        ///< ribbon-app menu
    
    // 菜单相关
    // QMenu* mExportWorkflowSceneToImageMenu { nullptr };  ///< scene导出为图片菜单
    // QMenu* m_menuViewLineMarkers { nullptr };            ///< 视图标记线
    // QMenu* m_menuInsertRow { nullptr };                  ///< 针对insertrow的action menu
    // QMenu* m_menuInsertColumn { nullptr };               ///< 这对insertcol的action menu
    QMenu* m_menuTheme { nullptr };                      ///< 主题菜单    

    
};
} // namespace FC
#endif // FCAPPRIBBONAREA_H
