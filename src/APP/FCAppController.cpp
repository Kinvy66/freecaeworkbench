/**
 * @file FCAppController.cpp
 * @brief 控制层负责逻辑的对接
 * @date 2025-10-29
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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
#include <QDebug>
// API
#include "AppMainWindow.h"
#include "FCAppCore.h"
#include "FCAppRibbonArea.h"
#include "FCAppDockingArea.h"
#include "FCAppCommand.h"
#include "FCAppActions.h"
#include "FCAppDataManager.h"
#include "FCProjectInterface.h"
// Qt-Advanced-Docking-System
#include "DockManager.h"
#include "DockAreaWidget.h"
// Widget
#include "FCSettingParametersWidget.h"
#include "FCGraphicOperateWidget.h"
#include "FCModelBuilderWidget.h"
// sub module
#include "FCGeometryData.h"

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
 * @brief 设置app数据管理
 * @param d
 * @return 
 */
FCAppController &FCAppController::setAppDataManager(FCAppDataManager *d)
{
    mDatas = d;
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
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionGlobalDelete, deleteProjectItem);
    
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionResetLayout, resetLayout);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionCreateCube, createCube);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionCreateCylinder, createCylinder);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionCreateCone, createCone);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionCreateSphere, createSphere);
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionCreateTorus, createTorus);
    
    FCAPPCONTROLLER_ACTION_BIND(mActions->actionAddMesh, addMesh);
    
    // FCAPPCONTROLLER_ACTION_BIND(mActions->actionAppendProject, onActionAppendProjectTriggered);
    
    FCGraphicOperateWidget* grapicWidget = mDock->getGraphicOperateWidget();
    FCSettingParametersWidget* settingsWidget = mDock->getSettingParametersWidget();
    // 几何模型创建完成通知渲染窗口显示
    connect(settingsWidget, &FCSettingParametersWidget::geometryModelCreated,
            grapicWidget, &FCGraphicOperateWidget::showGeoSet);
    // 几何模型修改通知更新工程树结构
    connect(settingsWidget, &FCSettingParametersWidget::updateGeoTree,
            this, &FCAppController::onUpdateGeoTree);
    // 几何模型修改通知更新渲染窗口   
    connect(settingsWidget, &FCSettingParametersWidget::updateGeometryAcotr,
            grapicWidget,&FCGraphicOperateWidget::updateGeometryAcotr);
    // 网格修改通知更新工程树结构
    connect(settingsWidget, &FCSettingParametersWidget::updateMeshTree,
            this, &FCAppController::onUpdateMeshTree);
    // 网格生成成功，通知渲染窗口显示
    connect(settingsWidget, &FCSettingParametersWidget::meshGenerated,
            grapicWidget,&FCGraphicOperateWidget::showMesh);
    // connect(settingsWidget, &FCSettingParametersWidget::meshGenerated,
    //         this,&FCAppController::onTestSlot);
    
    FCModelBuilderWidget* modelBuilderWidget = mDock->getModelBuilderWidget();
    // 工程树几何节点当前选择改变，通知参数设置窗口改变
    connect(modelBuilderWidget, &FCModelBuilderWidget::currentGeoItemChanged,
            settingsWidget, &FCSettingParametersWidget::updateCurrentGeoSettingWidget);
    // 工程树网格节点当前选择改变，通知参数设置窗口改变
    connect(modelBuilderWidget, &FCModelBuilderWidget::currentMeshItemChanged,
            settingsWidget, &FCSettingParametersWidget::updateCurrentMeshSettingWidget);
    
    
    connect(modelBuilderWidget, &FCModelBuilderWidget::currentItemChanged,
            settingsWidget, &FCSettingParametersWidget::updateCurrentSettingWidget);
    
    connect(modelBuilderWidget, &FCModelBuilderWidget::deleteGeometryEntity,
            this, &FCAppController::deletGeometryEntity);
    
    connect(modelBuilderWidget, &FCModelBuilderWidget::deleteMeshEntity,
            this, &FCAppController::deletMeshEntity);
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

/**
 * @brief 删除几何实体
 * @param id
 * @param name
 */
void FCAppController::deletGeometryEntity(const IdType id, QString name)
{
    // FCGeometrySet* set = FCGeometryData::getInstance()->getGeometrySetByID(id);
    FCGraphicOperateWidget* grapicWidget = mDock->getGraphicOperateWidget();
    grapicWidget->deleteGeometryActor(id);
    // qDebug() << "Remove"
}

void FCAppController::deletMeshEntity(const IdType id, QString name)
{
    FCGraphicOperateWidget* grapicWidget = mDock->getGraphicOperateWidget();
    grapicWidget->deleteMeshActor(id);
}

void FCAppController::save()
{
    // FCAPPCONTROLLER_PASS();
    FCGeometryData* geoData = mDatas->getGeometryData();
    qDebug() << "geometry count : " << geoData->getGeometrySetCount();
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

/**
 * @brief 删除item实体
 */
void FCAppController::deleteProjectItem()
{
    mDock->getModelBuilderWidget()->deleteEntityItem();
}

/**
 * @brief 重置布局
 */
void FCAppController::resetLayout()
{
    qDebug() << "Reset layout";
    mDock->restoreState();
    FCAPPCONTROLLER_PASS();
    
}

/**
 * @brief 创建立方体
 */
void FCAppController::createCube()
{
    mDock->getSettingParametersWidget()->createBox();
    // mDock->getModelBuilderWidge()->addGeometryCube();
}

/**
 * @brief 创建圆柱
 */
void FCAppController::createCylinder()
{
    mDock->getSettingParametersWidget()->createCylinder();
    
}

/**
 * @brief 创建圆锥
 */
void FCAppController::createCone()
{
    mDock->getSettingParametersWidget()->createCone();
    
}

/**
 * @brief 创建球体
 */
void FCAppController::createSphere()
{
    mDock->getSettingParametersWidget()->createSphere();
    
}

/**
 * @brief 创建圆环
 */
void FCAppController::createTorus()
{
    mDock->getSettingParametersWidget()->createTorus();
    
}

/**
 * @brief 添加网格
 */
void FCAppController::addMesh()
{
    mDock->getSettingParametersWidget()->addMesh();
}

void FCAppController::onUpdateGeoTree(const IdType id, const QString &name)
{
    // qDebug() << "onUpdateGeoTree";
    mDock->getModelBuilderWidget()->updateGeometryTree(id, name);
}

void FCAppController::onUpdateMeshTree(const IdType id, const QString &name)
{
    mDock->getModelBuilderWidget()->updateMeshTree(id, name);
}

void FCAppController::onActionAddDataTriggered()
{
    FCAPPCONTROLLER_PASS();
}

void FCAppController::onTestSlot(const IdType id, bool r)
{
    qDebug() << "test mesh id: " << id;
}

void FCAppController::onFocusedDockWidgetChanged(ads::CDockWidget *old, ads::CDockWidget *now)
{
    FCAPPCONTROLLER_PASS();
}


} // namespace FC


