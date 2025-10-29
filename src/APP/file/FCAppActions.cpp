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
    actionNew           = createAction("actionNew", ":/app/bright/Icon/file.svg");
    actionOpen          = createAction("actionOpen", ":/app/bright/Icon/file.svg");
    actionSave          = createAction("actionSave", ":/app/bright/Icon/save.svg");
    actionSaveAs        = createAction("actionSaveAs", ":/app/bright/Icon/save-as.svg");
    actionAppendProject = createAction("actionAppendProject", ":/app/bright/Icon/appendProject.svg");
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
    actionNew->setText(tr("新建"));                     // cn:打开
    actionOpen->setText(tr("Open"));                     // cn:打开
    actionOpen->setToolTip(tr("Open file or project"));  // cn:打开文件或项目
    actionSave->setText(tr("Save"));
    actionSaveAs->setText(tr("Save As"));
    actionAppendProject->setText(tr("Append To Project"));
}

