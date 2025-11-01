/******************************************************************************
 * File     : FCAppActions.cpp
 * Brief    : action管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCAppActions.h"
#include <QActionGroup>


// #include "FCRecentFilesManager.h"

//===================================================
// using DA namespace -- 禁止在头文件using！！
//===================================================
using namespace FC;

//===================================================
// FCAppActions
//===================================================
FCAppActions::FCAppActions(FCUIInterface* u) : FCActionsInterface(u)
{
    buildActions();
    // recentFilesManager = new DARecentFilesManager(this, 10, QStringLiteral("DA"), QStringLiteral("DAWorkBench"));
}

FCAppActions::~FCAppActions()
{
}

void FCAppActions::buildActions()
{
    // 构建主页actions    
    buildMainAction();
    // 构建几何actions
    buildGeometryAction();
    // 构建网格actions
    buildMeshtAction();
    // 构建研究actions
    buildStudyAction();
    // 构建结果actions
    buildResultAction();
    // 构建工具actions
    buildToolsActions();
    // 建立其他的actions
    buildOtherActions();
}

/**
 * @brief 构建主页actions  
 */
void FCAppActions::buildMainAction()
{
    // Main Category
    // 1. file pannel
    actionNew = createAction("actionNew", ":/icon/icon/file_new.svg");
    actionNew->setText(tr("新建"));
    actionOpen = createAction("actionOpen", ":/icon/icon/help.svg");
    actionOpen->setText(tr("打开"));
    actionSave = createAction("actionSave", ":/icon/icon/help.svg");
    actionSave->setText(tr("保存"));
    actionSaveAs = createAction("actionSaveAs", ":/icon/icon/help.svg");
    
    // 2. model pannel
    actionHomeImportGeometry = createAction("actionImportGeometry", ":/icon/icon/file_new.svg");
    actionHomeImportGeometry->setText(tr("导入几何"));
    actionImportMesh = createAction("actionImportMesh", ":/icon/icon/file_new.svg");      
    actionImportMesh->setText(tr("导入网格"));
    // 3. layout pannel
    actionWindowViews = createAction("actionWindowViews", ":/icon/icon/file_new.svg");
    actionWindowViews->setText(tr("窗口"));
    actionResetLayout = createAction("actionResetLayout", ":/icon/icon/file_new.svg");
    actionResetLayout->setText(tr("重置布局"));    
}

/**
 * @brief 构建几何actions  
 */
void FCAppActions::buildGeometryAction()
{
    
}

/**
 * @brief 构建网格actions  
 */
void FCAppActions::buildMeshtAction()
{
    
}

/**
 * @brief 构建研究actions  
 */
void FCAppActions::buildStudyAction()
{
    
}

/**
 * @brief 构建结果actions  
 */
void FCAppActions::buildResultAction()
{
    
}

/**
 * @brief 构建工具actions  
 */
void FCAppActions::buildToolsActions()
{
    
}

/**
 * @brief 构建其他actions  
 */
void FCAppActions::buildOtherActions()
{
    
}

void FCAppActions::retranslateUi()
{
    // Main Category
    actionNew->setText(tr("New"));                     // cn:打开
    actionOpen->setText(tr("Open"));                     // cn:打开
    actionOpen->setToolTip(tr("Open file or project"));  // cn:打开文件或项目
    actionSave->setText(tr("Save"));
    actionSaveAs->setText(tr("Save As"));
    // actionAppendProject->setText(tr("Append To Project"));
}

