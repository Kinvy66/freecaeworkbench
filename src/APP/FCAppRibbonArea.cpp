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
#include "FCAppRibbonArea.h"
#include "AppMainWindow.h"
#include <QActionGroup>
// SARibbon
#include "SARibbonMainWindow.h"
#include "SARibbonBar.h"
#include "SARibbonButtonGroupWidget.h"
#include "SARibbonCategory.h"
#include "SARibbonPanel.h"
#include "SARibbonContextCategory.h"
#include "SARibbonQuickAccessBar.h"
#include "SARibbonButtonGroupWidget.h"
#include "SARibbonMenu.h"
#include "SARibbonCtrlContainer.h"
#include "SARibbonApplicationButton.h"
#include "SARibbonLineWidgetContainer.h"
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
// ui
#include "FCAppRibbonApplicationMenu.h"
// api
#include "FCAppUI.h"
#include "FCAppCommand.h"
#include "FCAppCore.h"
// #include "FCAppDockingArea.h"
#include "FCAppActions.h"
// #include "FCRecentFilesManager.h"
// Qt-Advanced-Docking-System
#include "DockManager.h"
#include "DockAreaWidget.h"

// 快速链接信号槽
#define FCAPPRIBBONAREA_ACTION_BIND(actionname, functionname)                                                          \
connect(actionname, &QAction::triggered, this, &FCAppRibbonArea::functionname)

#define FCAPPRIBBONAREA_COMMON_SETTING_CPP(MiddleName, ShapeEditPannelWidget, FontEditWidget)                          \
    QPen FCAppRibbonArea::get##MiddleName##Pen() const                                                                 \
{                                                                                                                  \
        return ShapeEditPannelWidget->getBorderPen();                                                                  \
}                                                                                                                  \
    QBrush FCAppRibbonArea::get##MiddleName##Brush() const                                                             \
{                                                                                                                  \
        return ShapeEditPannelWidget->getBackgroundBrush();                                                            \
}                                                                                                                  \
    QFont FCAppRibbonArea::get##MiddleName##Font() const                                                               \
{                                                                                                                  \
        return FontEditWidget->getCurrentFont();                                                                       \
}                                                                                                                  \
    QColor FCAppRibbonArea::get##MiddleName##FontColor() const                                                         \
{                                                                                                                  \
        return FontEditWidget->getCurrentFontColor();                                                                  \
}                                                                                                                  \
    void FCAppRibbonArea::set##MiddleName##Pen(const QPen& v)                                                          \
{                                                                                                                  \
        QSignalBlocker b(ShapeEditPannelWidget);                                                                       \
        ShapeEditPannelWidget->setBorderPen(v);                                                                        \
}                                                                                                                  \
    void FCAppRibbonArea::set##MiddleName##Brush(const QBrush& v)                                                      \
{                                                                                                                  \
        QSignalBlocker b(ShapeEditPannelWidget);                                                                       \
        ShapeEditPannelWidget->setBackgroundBrush(v);                                                                  \
}                                                                                                                  \
    void FCAppRibbonArea::set##MiddleName##Font(const QFont& v)                                                        \
{                                                                                                                  \
        QSignalBlocker b(FontEditWidget);                                                                              \
        FontEditWidget->setCurrentFont(v);                                                                             \
}                                                                                                                  \
    void FCAppRibbonArea::set##MiddleName##FontColor(const QColor& v)                                                  \
{                                                                                                                  \
        QSignalBlocker b(FontEditWidget);                                                                              \
        FontEditWidget->setCurrentFontColor(v);                                                                        \
}

//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================

using namespace FC;

//===================================================
// DAAppRibbonArea
//===================================================

FCAppRibbonArea::FCAppRibbonArea(FCUIInterface* u)
    : FCRibbonAreaInterface(u)
{
    FCAppUI* appui = qobject_cast< FCAppUI* >(u);
    m_app          = qobject_cast< AppMainWindow* >(appui->mainWindow());
    m_actions      = qobject_cast< FCAppActions* >(u->getActionInterface());
    m_appCmd       = qobject_cast< FCAppCommand* >(u->getCommandInterface());
    // ribbon的构建在setDockingArea进行，为了保证ribbon在dock之后构建
}

FCAppRibbonArea::~FCAppRibbonArea()
{
}


/**
 * @brief 构建所有的action
 */
void FCAppRibbonArea::buildMenu()
{

    m_menuTheme = new SARibbonMenu(m_app);
    // m_menuTheme->setObjectName(QStringLiteral("menuTheme"));
    // m_menuTheme->setIcon(QIcon(QStringLiteral(":/app/bright/Icon/theme.svg")));
    // m_menuTheme->addAction(m_actions->actionRibbonThemeOffice2013);
    // m_menuTheme->addAction(m_actions->actionRibbonThemeOffice2016Blue);
    // m_menuTheme->addAction(m_actions->actionRibbonThemeOffice2021Blue);
    // m_menuTheme->addAction(m_actions->actionRibbonThemeDark);

}

/**
 * @brief 发生语言变更时会触发此函数
 */
void FCAppRibbonArea::retranslateUi()
{
    // resetText();
}

/**
 * @brief 重置文字
 */
void FCAppRibbonArea::resetText()
{
    ribbonBar()->applicationButton()->setText(tr("文件"));  // 文件
    
    // m_categoryMain->setCategoryName(tr("主页"));              // cn:主页
    // m_categoryGeometry->setCategoryName(tr("几何"));       // cn:几何
    // m_categoryMesh->setCategoryName(tr("Mesh"));              // cn:网格
    // m_categoryStudy->setCategoryName(tr("Study"));            // cn: 研究
    // m_categoryResult->setCategoryName(tr("Reslut"));          // cn:结果
    // m_categoryTools->setCategoryName(tr("Tools"));            // cn:工具
    
    //todo:其他panel以及action的翻译
}

/**
 * @brief 构建ribbon
 */
void FCAppRibbonArea::buildRibbon()
{
    ribbonBar()->showMinimumModeButton();
    ribbonBar()->applicationButton()->setText(tr("文件"));
    buildRibbonMainCategory();
    buildRibbonGeometryCategory();
    buildRibbonMeshCategory();
    buildRibbonStudyCategory();
    buildRibbonResultCategory();
    buildRibbonToolsCategory();
    buildRibbonQuickAccessBar();
    // todo:上下文标签
    //
    buildApplicationMenu();
    //
    buildRightButtonBar();
}

/**
 * @brief 构建主页标签
 * 主页的category objname = fc-ribbon-category-main
 */
void FCAppRibbonArea::buildRibbonMainCategory()
{
    m_categoryMain = new SARibbonCategory(app());
    m_categoryMain->setObjectName(QStringLiteral("fc-ribbon-category-main"));
    m_categoryMain->setCategoryName(tr("主页"));
    //---------File Pannel -----------------------------------------------
    m_pannelMainFileOpt = m_categoryMain->addPanel(tr("文件"));
    // m_pannelMainFileOpt->setObjectName(QStringLiteral("fc-ribbon-category-main.file"));
    // m_pannelMainFileOpt->addLargeAction(m_actions->actionNew);
    // m_pannelMainFileOpt->addLargeAction(m_actions->actionOpen);
    // m_pannelMainFileOpt->addSmallAction(m_actions->actionSave);
    // m_pannelMainFileOpt->addSmallAction(m_actions->actionSaveAs);
    
    // todo:其他pannel
    
    ribbonBar()->addCategoryPage(m_categoryMain);
}

/**
 * @brief 构建几何标签
 * 主页的category objname = fc-ribbon-category-geometry
 */
void FCAppRibbonArea::buildRibbonGeometryCategory()
{
    m_categoryGeometry = new SARibbonCategory(app());
    m_categoryGeometry->setObjectName(QStringLiteral("fc-ribbon-category-geometry"));
    m_categoryGeometry->setCategoryName(tr("几何"));
    
    //---------File Pannel -----------------------------------------------
    m_pannelGeometryBuildOpt = m_categoryGeometry->addPanel(tr("构建"));
    // m_pannelGeometryBuildOpt->setObjectName(QStringLiteral("fc-ribbon-category-geometry.build"));
    // m_pannelGeometryBuildOpt->addLargeAction(m_actions->actionGeometryBuildAll);
    
    // todo:其他pannel
    
    ribbonBar()->addCategoryPage(m_categoryGeometry);
}

/**
 * @brief 构建网格标签
 * 主页的category objname = fc-ribbon-category-mesh
 */
void FCAppRibbonArea::buildRibbonMeshCategory()
{
    m_categoryMesh = new SARibbonCategory(app());
    m_categoryMesh->setObjectName(QStringLiteral("fc-ribbon-category-mesh"));
    m_categoryMesh->setCategoryName(tr("网格"));
    m_pannelMeshBuildOpt = m_categoryMesh->addPanel(tr("构建"));
    
    ribbonBar()->addCategoryPage(m_categoryMesh);
    
}

/**
 * @brief 构建研究标签
 * 主页的category objname = fc-ribbon-category-study
 */
void FCAppRibbonArea::buildRibbonStudyCategory()
{
    m_categoryStudy = new SARibbonCategory(app());
    m_categoryStudy->setObjectName(QStringLiteral("fc-ribbon-category-study"));
    m_categoryStudy->setCategoryName(tr("研究"));
    
    ribbonBar()->addCategoryPage(m_categoryStudy);
    
}

/**
 * @brief 构建结果标签
 * 主页的category objname = fc-ribbon-category-result
 */
void FCAppRibbonArea::buildRibbonResultCategory()
{
    m_categoryResult = new SARibbonCategory(app());
    m_categoryResult->setObjectName(QStringLiteral("fc-ribbon-category-result"));
    m_categoryResult->setCategoryName(tr("结果"));
    
    ribbonBar()->addCategoryPage(m_categoryResult);
    
    
    
}

/**
 * @brief 构建工具标签
 * 主页的category objname = fc-ribbon-category-tools
 */
void FCAppRibbonArea::buildRibbonToolsCategory()
{
    m_categoryTools = new SARibbonCategory(app());
    m_categoryTools->setObjectName(QStringLiteral("fc-ribbon-category-tools"));
    m_categoryTools->setCategoryName(tr("工具"));
    
    ribbonBar()->addCategoryPage(m_categoryTools);
    
}

/**
 * @brief 构建ribbon的QuickAccessBar
 * 主页的category objname = da-ribbon-category-main
 */
void FCAppRibbonArea::buildRibbonQuickAccessBar()
{
    SARibbonQuickAccessBar* quickAccessBar = ribbonBar()->quickAccessBar();
    
    quickAccessBar->addAction(m_actions->actionOpen);
    quickAccessBar->addSeparator();
}

/**
 * @brief 构建ApplicationMenu
 */
void FCAppRibbonArea::buildApplicationMenu()
{
    mApplicationMenu = new FCAppRibbonApplicationMenu(app());
    mApplicationMenu->addAction(m_actions->actionOpen);
    mApplicationMenu->addAction(m_actions->actionSave);
    mApplicationMenu->addAction(m_actions->actionSaveAs);
    // m_actions->recentFilesManager->attachToMenu(mApplicationMenu, tr("Recent Files"));  // cn:最近打开的文件
    SARibbonApplicationButton* appBtn = qobject_cast< SARibbonApplicationButton* >(ribbonBar()->applicationButton());
    if (nullptr == appBtn) {
        return;
    }
    mApplicationMenu->update();
    appBtn->setMenu(mApplicationMenu);
}

/**
 * @brief 构建右工具栏
 */
void FCAppRibbonArea::buildRightButtonBar()
{
    ribbonBar()->activeRightButtonGroup();
    SARibbonButtonGroupWidget* rbar = ribbonBar()->rightButtonGroup();
    rbar->addMenuAction(m_menuTheme);
}

void FCAppRibbonArea::setDockingArea(FCAppDockingArea *dock)
{
    m_dockArea = dock;
    buildMenu();
    buildRibbon();
    buildRedoUndo();
    resetText();
}


AppMainWindow* FCAppRibbonArea::app() const
{
    return (m_app);
}

SARibbonBar* FCAppRibbonArea::ribbonBar() const
{
    return (app()->ribbonBar());
}

/**
 * @brief mian标签
 * @return
 */
SARibbonCategory* FCAppRibbonArea::getRibbonCategoryMain() const
{
    return (m_categoryMain);
}

/**
 * @brief 通过DACommandInterface构建redo/undo的action
 * @param cmd
 */
void FCAppRibbonArea::buildRedoUndo()
{
    QUndoGroup& undoGroup = m_appCmd->undoGroup();
    // 设置redo,undo的action
    
    // m_actions->actionRedo = undoGroup.createRedoAction(this);
    // m_actions->actionRedo->setObjectName("actionRedo");
    // m_actions->actionRedo->setIcon(QIcon(":/app/bright/Icon/redo.svg"));
    // m_actions->actionRedo->setShortcut(QKeySequence::Redo);
    // m_actions->actionUndo = undoGroup.createUndoAction(this);
    // m_actions->actionUndo->setObjectName("actionUndo");
    // m_actions->actionUndo->setIcon(QIcon(":/app/bright/Icon/undo.svg"));
    // m_actions->actionUndo->setShortcut(QKeySequence::Undo);
    // SARibbonQuickAccessBar* bar = ribbonBar()->quickAccessBar();
    // if (!bar) {
    //     return;
    // }
    // bar->addAction(m_actions->actionUndo);
    // bar->addAction(m_actions->actionRedo);
}



/**
 * @brief 显示上下文(会把其他上下文隐藏)
 * @param type
 */
void FCAppRibbonArea::showContextCategory(FCAppRibbonArea::ContextCategoryType type)
{
    SARibbonBar* ribbon = ribbonBar();
    //todo
}

/**
 * @brief 隐藏上下文
 * @param type
 */
void FCAppRibbonArea::hideContextCategory(FCAppRibbonArea::ContextCategoryType type)
{
    SARibbonBar* ribbon = ribbonBar();
   //todo
}




