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
#include "FCAppController.h"

// Qt
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QStandardPaths>
#include <QFontComboBox>
#include <QComboBox>
#include <QInputDialog>
#include <QMenu>
#include <QApplication>
#include <QActionGroup>
// API
#include "AppMainWindow.h"
#include "FCAppCore.h"
#include "FCAppRibbonArea.h"
#include "FCAppDockingArea.h"
#include "FCAppCommand.h"
#include "FCAppActions.h"
// #include "FCAppDataManager.h"
#include "FCProjectInterface.h"
// Qt-Advanced-Docking-System
#include "DockManager.h"
#include "DockAreaWidget.h"

#ifndef FCAPPRIBBONAREA_WINDOW_NAME
#define FCAPPRIBBONAREA_WINDOW_NAME QCoreApplication::translate("FCAppController", "FC", nullptr)
#endif

#define FCAPPCONTROLLER_PASS()                                                                                         \
QMessageBox::                                                                                                      \
    warning(app(),                                                                                                 \
            QCoreApplication::translate("FCAppRibbonArea", "warning", nullptr),                                    \
            QCoreApplication::translate("FCAppRibbonArea",                                                         \
                                        "The current function is not implemented, only the UI is reserved, "       \
                                        "please pay attention: https://github.com/Kinvy66/freecaeworkbench",         \
                                        nullptr))

// 快速链接信号槽
#define FCAPPCONTROLLER_ACTION_BIND(actionname, functionname)                                                          \
    connect(actionname, &QAction::triggered, this, &FCAppController::functionname)

namespace FC 
{
FCAppController::FCAppController(QObject* par) : QObject(par)
{
}

FCAppController::~FCAppController()
{
}

/**
 * @brief 设置AppMainWindow
 * @param mainWindow
 * @return 返回自身引用,方便链式调用
 */
FCAppController &FCAppController::setAppMainWindow(AppMainWindow *mainWindow)
{
    mMainWindow = mainWindow;
    return (*this);
}

/**
 * @brief 设置core
 * @param core
 * @return
 */
FCAppController &FCAppController::setAppCore(FCAppCore *core)
{
    mCore    = core;
    mProject = mCore->getProjectInterface();
    return (*this);
}

/**
 * @brief 设置ribbon
 * @param ribbon
 * @return 返回自身引用,方便链式调用
 */
FCAppController &FCAppController::setAppRibbonArea(FCAppRibbonArea *ribbon)
{
    mRibbon = ribbon;
    return (*this);
}

/**
 * @brief 设置dock
 * @param dock
 * @return 返回自身引用,方便链式调用
 */
FCAppController &FCAppController::setAppDockingArea(FCAppDockingArea *dock)
{
    mDock = dock;
    
    return (*this);
}

/**
 * @brief 设置AppCommand
 * @param cmd
 * @return 返回自身引用,方便链式调用
 */
FCAppController &FCAppController::setAppCommand(FCAppCommand *cmd)
{
    mCommand = cmd;
    return (*this);
}

/**
 * @brief 设置AppActions
 * @param act
 * @return 返回自身引用,方便链式调用
 */
FCAppController &FCAppController::setAppActions(FCAppActions *act)
{
    mActions = act;
    return (*this);
}

/**
 * @brief 获取app
 * @return
 */
AppMainWindow *FCAppController::app() const
{
     return mMainWindow;
}

/**
 * @brief 控制层初始化
 */
void FCAppController::initialize()
{
    initConnection();
}

/**
 * @brief action和slot connect
 */
void FCAppController::initConnection()
{
    // Main Category
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionOpen, open);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionSave, save);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionSaveAs, saveAs);
    // FCAPPCONTROLLER_ACTION_BIND(mActions->actionAppendProject, onActionAppendProjectTriggered);
}


/**
 * @brief 设置工程为脏
 *
 * @note 如果工程状态已经是脏，此函数不会做任何动作也不会触发任何信号
 * @param on
 */
void FCAppController::setDirty(bool on)
{
    // if (mProject) {
    //     mProject->setModified(on);
    // }
}

/**
 * @brief 工程是否为脏
 * @return
 */
bool FCAppController::isDirty() const
{
    // if (mProject) {
    //     return mProject->isDirty();
    // }
    return false;
}

/**
 * @brief 更新窗口标题
 */
void FCAppController::updateWindowTitle()
{
    // FCAppProject* project = FC_APP_CORE.getAppProject();
    // if (!project || project->isEmpty()) {
    //     app()->setWindowTitle(makeWindowTitle());
    //     return;
    // }
    // app()->setWindowTitle(makeWindowTitle(project));
}

/**
 * @brief 生成窗口标题
 * @return
 */
QString FCAppController::makeWindowTitle()
{
    return QString("%1 [*]").arg(FCAPPRIBBONAREA_WINDOW_NAME);
}

/**
 * @brief 生成当前项目下的窗口标题
 * @return
 */
QString FCAppController::makeWindowTitle(FCProjectInterface *proj)
{
    return QString("%1 [*]").arg(FCAPPRIBBONAREA_WINDOW_NAME);    
}

void FCAppController::save()
{
    FCAPPCONTROLLER_PASS();
}

void FCAppController::saveAs()
{
    FCAPPCONTROLLER_PASS();
}

void FCAppController::open()
{
    FCAPPCONTROLLER_PASS();
}

bool FCAppController::openProjectFile(const QString &projectFilePath)
{
    FCAPPCONTROLLER_PASS();
    return true;
}

void FCAppController::onActionAddDataTriggered()
{
    FCAPPCONTROLLER_PASS();
}

void FCAppController::onFocusedDockWidgetChanged(ads::CDockWidget *old, ads::CDockWidget *now)
{
    FCAPPCONTROLLER_PASS();
}


} // namespace FC


