/******************************************************************************
 * File     : FCAppCore.cpp
 * Brief    : 
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppCore.h"
#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
// API
// #include "FCAppUI.h"
// #include "FCAppRibbonArea.h"
// #include "FCAppDataManager.h"
// #include "DACommandInterface.h"
// #include "FCAppProject.h"
// #include "FCAppCommand.h"
// #if DA_ENABLE_PYTHON
// // DA Python
// #include "DAPyInterpreter.h"
// #include "DAPyScripts.h"
// #else
#include <QProcess>
#include <QList>
#include <QFileInfo>
// #endif
//===================================================
// using DA namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

//===================================================
// FCAppCore
//===================================================
FCAppCore::FCAppCore(QObject* p)
    : FCCoreInterface(p)
    , mAppUI(nullptr)
    , mAppCmd(nullptr)
    , mIsPythonInterpreterInitialized(false)
    , mProject(nullptr)
{
    mDataManager = nullptr;
}

FCAppCore& FCAppCore::getInstance()
{
    static FCAppCore s_core;
    return (s_core);
}


bool FCAppCore::initialized()
{
#if DA_ENABLE_PYTHON
    // 初始化python环境
    qDebug() << "begin app core initialized";
    initializePythonEnv();
    qDebug() << "core have been initialized Python Env";
#endif
    // 初始化数据
    // mDataManager = new FCAppDataManager(this, this);
    // qDebug() << "core have been initialized App Data Manager";
    // mProject = new FCAppProject(this, this);
    // mProject->setDataManagerInterface(mDataManager);
    return true;
}

/**
 * @brief 获取FCAppRibbonAreaInterface
 * @return 
 */
FCUIInterface* FCAppCore::getUiInterface() const
{
    // return mAppUI;
    return nullptr;
}

/**
 * @brief 获取项目管理接口
 * @return 
 */
FCProjectInterface* FCAppCore::getProjectInterface() const
{
    // return mProject;
    return nullptr;
}

/**
 * @brief 创建ui
 * @param mainwindow
 * @details 调用此函数，创建FCAppUIInterface，此函数的调用应该发生在SARibbonMainWindow的构造过程
 */
void FCAppCore::createUi(SARibbonMainWindow* mainwindow)
{
    // mAppUI = new FCAppUI(mainwindow, this);
    // mAppUI->createUi();
    // mAppCmd = mAppUI->getAppCmd();
    // if (mDataManager) {
    //     // 把dataManager的undo stack 注册
    //     if (mAppCmd) {
    //         mAppCmd->setDataManagerStack(mDataManager->getUndoStack());
    //     }
    // }
}

FCDataManagerInterface *FCAppCore::getDataManagerInterface() const
{
    return nullptr;
}


/**
 * @brief 获取FCAppUI，省去qobject_cast
 * @return
 */
FCAppUI* FCAppCore::getAppUi()
{
    // return mAppUI;
    return nullptr;
}
/**
 * @brief 获取工程
 * @return
 */
FCAppProject* FCAppCore::getAppProject()
{
    return mProject;
}
/**
 * @brief 直接获取数据
 * @return
 */
FCAppDataManager* FCAppCore::getAppDatas()
{
    return mDataManager;
}
/**
 * @brief 直接获取FCAppCommand
 *
 * @note 此函数必须在@ref createUi 之后调用才有实际结果
 * @return
 */
FCAppCommand* FCAppCore::getAppCmd()
{
    return mAppCmd;
}

