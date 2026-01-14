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
       

       
}

AppMainWindow::~AppMainWindow()
{
    
}

void AppMainWindow::showEvent(QShowEvent* event)
{
    // 首次显示时，在窗口完全初始化后设置最大化状态
    // 这样可以避免几何设置冲突，同时减少闪动
    if (mFirstShow) {
        mFirstShow = false;
        // 先调用基类的showEvent，确保窗口完全初始化
        SARibbonMainWindow::showEvent(event);
        
        // 使用QTimer::singleShot(0)确保在当前事件循环完成后立即执行
        // 延迟时间极短，用户几乎感觉不到
        QTimer::singleShot(0, this, [this]() {
            if (!this->isMaximized()) {
                // 使用setWindowState设置最大化状态，比showMaximized()更平滑
                Qt::WindowStates state = this->windowState();
                if (!(state & Qt::WindowMaximized)) {
                    this->setWindowState(state | Qt::WindowMaximized);
                }
            }
        });
    } else {
        SARibbonMainWindow::showEvent(event);
    }
}

void AppMainWindow::changeEvent(QEvent* event)
{
    // 简化changeEvent处理，避免不必要的状态检查导致闪动
    // 基类会正确处理窗口状态变化
    SARibbonMainWindow::changeEvent(event);
}

void AppMainWindow::init()
{
    
}

void AppMainWindow::initPlugins()
{
    
}

} // namespace FC
