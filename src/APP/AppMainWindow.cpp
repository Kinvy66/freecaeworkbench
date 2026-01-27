/**
 * @file AppMainWindow.cpp
 * @brief 主窗口
 * @date 2025-10-27
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */

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
#include <QTimer>
#include <QEvent>
#include <QWindowStateChangeEvent>
#include <QShowEvent>
#include <QRect>

//
#include "SARibbonBar.h"
// 插件相关
// #include "DAAppPluginManager.h"
// #include "DAAbstractPlugin.h"
// #include "DAAbstractNodePlugin.h"
// 界面相关
#include "FCAppController.h"
#include "FCAppCore.h"
#include "FCAppUI.h"
#include "FCAppDockingArea.h"
#include "FCAppRibbonArea.h"
// 对话框

// 节点相关
// #include "DANodeMetaData.h"

//
// #include "DAGraphicsItemFactory.h"
// #include "DAWorkFlowNodeListWidget.h"
// #include "DAWorkFlowOperateWidget.h"
// #include "DAWorkFlowOperateWidget.h"
// #include "DAWorkFlowOperateWidget.h"
//
// #include "DAAppSettingDialog.h"
// #include "SettingPages/DAAppConfig.h"
// Qt-Advanced-Docking-System
#include "DockManager.h"

namespace FC {

AppMainWindow::AppMainWindow(QWidget *parent)
    : SARibbonMainWindow(parent)
{
    // 标签可高亮
    ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting, true);
    // 让dock可以最小化到一个标签
    ads::CDockManager::setAutoHideConfigFlags({ ads::CDockManager::DefaultAutoHideConfig });
    // 建立ribbonArea，此函数的构造函数会生成界面
    QIcon icon(QStringLiteral(":/icon/icon/icon.svg"));
    setWindowIcon(icon);
    this->resize(1300, 800);
    FCAppCore& core = FCAppCore::getInstance();
    // 创建界面
    core.createUi(this);
    mCore     = &core;
    mUI       = qobject_cast< FCAppUI* >(core.getUiInterface());
    mDockArea = mUI->getAppDockingArea();
    // 创建controller
    mController = new FCAppController(this);
    (*mController)
        .setAppMainWindow(this)                       // app
        .setAppCore(&core)                            // core
        .setAppActions(mUI->getAppActions())          // action
        .setAppCommand(mUI->getAppCmd())              // cmd
        .setAppDataManager(core.getAppDatas())        // data
        .setAppDockingArea(mUI->getAppDockingArea())  // dock
        .setAppRibbonArea(mUI->getAppRibbonArea())    // ribbon
        ;
    mController->initialize();
    ribbonBar()->setContentsMargins(3, 0, 3, 0);
    // 界面状态的加载要在init之前，因为inti的插件会改变界面，如果在之后就永远改变不了界面了
    // bool hasUIStateFile = isHaveStateSettingFile();
    // if (hasUIStateFile) {
    //     restoreUIState();
    //     qInfo().noquote() << tr("Restore UI State");  // cn:加载界面状态信息
    // }
    // 首次调用此函数会加载插件，可放置在main函数中调用
    init();
    // retranslateUi();  // 非必要可以验证调用是否正常
    // if (!hasUIStateFile) {
        ribbonBar()->setRibbonStyle(SARibbonBar::RibbonStyleLooseThreeRow);
        // 不在构造函数中直接最大化，而是在showEvent中处理，避免闪动
        // 设置一个标志，表示首次显示时需要最大化
    // }
    showMaximized();
}

AppMainWindow::~AppMainWindow()
{
    
}

void AppMainWindow::init()
{
    
}

void AppMainWindow::initPlugins()
{
    
}

} // namespace FC
