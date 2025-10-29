/******************************************************************************
 * File     : FCAppActions.h
 * Brief    : action管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-28
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCAPPACTIONS_H
#define FCAPPACTIONS_H

#include "FCActionsInterface.h"

class QActionGroup;

namespace FC 
{
class FCAppActions : public FCActionsInterface
{
    Q_OBJECT
public:
    FCAppActions(FCUIInterface* u);
    ~FCAppActions();
    // 发生语言变更时会调用此函数
    void retranslateUi() override;
    
    
protected:
    void buildActions();
    // 构建主页actions
    void buildMainAction();
    // 构建几何actions
    void buildGeometryAction();
    // 构建网格actions
    void buildMeshtAction();
    // 构建研究actions
    void buildStudyAction();
    // 构建结果actions
    void buildResultAction();
    // 构建工具actions
    void buildToolsActions();
    // 建立其他的actions
    void buildOtherActions();
    
public:
    //===================================================
    // 主页标签 Main Category
    //===================================================
    QAction* actionNew;             ///< 打开
    QAction* actionOpen;           ///< 打开
    QAction* actionSave;           ///< 保存
    QAction* actionSaveAs;         ///< 另存为
    QAction* actionAppendProject;  ///< 追加工程
    
    // todo: 其他标签页的actions
    
    //===================================================
    // 主题
    //===================================================
    QAction* actionRibbonThemeOffice2013;      ///< office2013主题
    QAction* actionRibbonThemeOffice2016Blue;  ///< office2016主题
    QAction* actionRibbonThemeOffice2021Blue;  ///< office2021主题
    QAction* actionRibbonThemeDark;            ///< dark主题
    QActionGroup* actionGroupRibbonTheme;      ///< actionRibbonTheme* 的actionGroup
    
    
     // FCRecentFilesManager* recentFilesManager { nullptr };
    
};
} // namespace FC

#ifndef FC_APP_ACTIONS
/**
 * @def 获取@sa FCAppCore 实例
 * @note 使用此宏需要以下两个头文件：
 * -# FCAppCore.h
 * -# FCAppUI.h
 */
#define FC_APP_ACTIONS FC::FCAppCore::getInstance().getUi()->getActions()
#endif

#endif  // FCAPPACTIONS_H
