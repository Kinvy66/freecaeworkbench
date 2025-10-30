/******************************************************************************
 * File     : FCAppController.h
 * Brief    : 控制层负责逻辑的对接
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-29
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPCONTROLLER_H
#define FCAPPCONTROLLER_H

#include <QObject>
#include <QAction>
#include <QUndoStack>
#include <QScopedPointer>
// #include "DADataManageWidget.h"
// #include "DAWorkFlowGraphicsScene.h"


class QComboBox;
class QToolBar;
class QMenuBar;
class QFontComboBox;
class QUndoStack;
class QGraphicsItem;
// qwt
class QwtPlotItem;
// Qt-Advanced-Docking-System 前置申明
namespace ads
{
class CDockWidget;
}

namespace FC 
{
class AppMainWindow;
class FCAppCore;
class FCProjectInterface;
class FCAppRibbonArea;
class FCAppDockingArea;
class FCAppCommand;
class FCAppActions;
// class FCAppDataManager;
// class FCSettingContainerWidget;
// class FCDataOperateOfDataFrameWidget;
// class FCWorkFlowOperateWidget;
// class FCDataOperateWidget;
// class FCAppChartOperateWidget;
// class FCDataManageWidget;
// class FCFigureWidget;
// class FCChartWidget;
// class FCDataOperatePageWidget;
// class FCAppSettingDialog;
// class FCAppConfig;
// class FCWorkFlowEditWidget;

class FCAppController : public QObject
{
    Q_OBJECT
public:
    
    /**
	 * @brief 针对Operate窗口的最后焦点枚举，用于识别最后用户所在的操作窗口
	 */
    enum LastFocusedOpertateWidget
    {
        LastFocusedNoneOptWidget = 0x00,
        LastFocusedOnWorkflowOpt = 0x01,  ///< 最后焦点在工作流操作窗口
        LastFocusedOnDataOpt     = 0x02,  ///< 最后焦点在数据操作窗口
        LastFocusedOnChartOpt    = 0x04   ///< 最后焦点在绘图操作窗口
    };
    Q_DECLARE_FLAGS(LastFocusedOpertateWidgets, LastFocusedOpertateWidget)
    Q_FLAG(LastFocusedOpertateWidget)
    
public:
    FCAppController(QObject* par = nullptr);
    ~FCAppController();
    
    // 设置AppMainWindow
    FCAppController& setAppMainWindow(AppMainWindow* mainWindow);
    // 设置core
    FCAppController& setAppCore(FCAppCore* core);
    // 设置ribbon
    FCAppController& setAppRibbonArea(FCAppRibbonArea* ribbon);
    // 设置dock
    FCAppController& setAppDockingArea(FCAppDockingArea* dock);
    // 设置AppCommand
    FCAppController& setAppCommand(FCAppCommand* cmd);
    // 设置AppActions
    FCAppController& setAppActions(FCAppActions* act);
    // 设置AppDataManager
    // FCAppController& setAppDataManager(DAAppDataManager* d);
    // 获取app
    AppMainWindow* app() const;
    // 初始化--必须初始化才能生效
    void initialize();
    
    
public:
    // 获取当前dataframeOperateWidget,如果没有返回nullptr,此函数不返回nullptr的前提是
    // FCDataOperateOfDataFrameWidget* getCurrentDataFrameOperateWidget(bool checkDataOperateAreaFocused = true,
                                                                     // bool isShowMessage               = true);
    // 获取工作流操作窗口
    // DAWorkFlowOperateWidget* getWorkFlowOperateWidget() const;
    // 获取数据操作窗口
    // DADataOperateWidget* getDataOperateWidget() const;
    // 获取绘图操作窗口
    // DAAppChartOperateWidget* getChartOperateWidget() const;
    // 获取数据管理窗口
    // DADataManageWidget* getDataManageWidget() const;
    // 获取当前的绘图,如果没有回返回nullptr
    // DAFigureWidget* getCurrentFigure();
    // DAFigureWidget* gcf();
    // 获取绘图操作窗口,如果没有回返回nullptr
    // DAChartWidget* getCurrentChart() const;
    // DAChartWidget* gca() const;
    // 获取设置窗口
    // DASettingContainerWidget* getSettingContainerWidget() const;
    // 判断当前是否是在绘图操作模式，就算绘图操作不在焦点，但绘图操作在前端，此函数也返回true
    // bool isLastFocusedOnChartOptWidget() const;
    // bool isLastFocusedOnWorkflowOptWidget() const;
    // bool isLastFocusedOnDataOptWidget() const;
    // DAAppConfig* getConfig() const;
    // void setConfig(DAAppConfig* config);
    // 设置工程为dirty
    void setDirty(bool on = true);
    bool isDirty() const;
    // 导入数据
    // bool importData(const QString& filePath, const QVariantMap& args, QString* err = nullptr);
    // 更新窗口标题
    void updateWindowTitle();
    // 生成窗口标题
    static QString makeWindowTitle();
    static QString makeWindowTitle(FCProjectInterface* proj);
    
public Q_SLOTS:
    // 保存
    void save();
    // 另存为
    void saveAs();
    //   打开 文件前的检查，  返回true说明可以打开
    // bool openCheck();
    // 打开文件
    void open();
    // 打开工程文件
    bool openProjectFile(const QString& projectFilePath);
private Q_SLOTS:
    // 工程的胀状态改变槽
    // void onProjectDirtyStateChanged(bool isdirty);
    //===================================================
    // 主页标签 Main Category
    //===================================================
    // void onActionAppendProjectTriggered();
    
    void onActionAddDataTriggered();
    
    
   
private slots:
    // DockWidget的焦点变化
    void onFocusedDockWidgetChanged(ads::CDockWidget* old, ads::CDockWidget* now);
private:
    // 初始化信号槽
    void initConnection();
  
    
private:
    AppMainWindow* mMainWindow { nullptr };
    FCAppCore* mCore { nullptr };
    FCProjectInterface* mProject { nullptr };
    
    FCAppRibbonArea* mRibbon { nullptr };
    FCAppDockingArea* mDock { nullptr };
    FCAppCommand* mCommand { nullptr };
    FCAppActions* mActions { nullptr };
    // FCAppDataManager* mDatas { nullptr };
    
    QStringList mFileReadFilters;  ///< 包含支持的文件[Images (*.png *.xpm *.jpg)] [Text files (*.txt)]
    //
    LastFocusedOpertateWidgets mLastFocusedOpertateWidget;  ///< 最后获取焦点的操作窗口
    //
    // DAAppSettingDialog* mSettingDialog { nullptr };         ///< 设置窗口
    // DAAppConfig* mConfig;                                   ///< 设置类
};
} // namespace FC



#endif // FCAPPCONTROLLER_H
