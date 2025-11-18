/******************************************************************************
 * File     : FCProjectTree.cpp
 * Brief    : 工程树管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-18
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCProjectTree.h"
#include "FCTreeWidget.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include "FCAppActions.h"

namespace FC 
{

FCProjectTree::FCProjectTree(QObject *parent)
    : QObject(parent)
{
    mTreeWidget = new FCTreeWidget();
    createDefaultProject();
}

/**
 * @brief 创建空白默认工程
 * @param name
 */
void FCProjectTree::createDefaultProject(const QString &name)
{
    QTreeWidgetItem* projectRoot = new QTreeWidgetItem();
    projectRoot->setData(0, Qt::UserRole, FCTreeWidget::MenuProjectRoot);
    projectRoot->setText(0, name);
    projectRoot->setIcon(0,QIcon(":/icon/icon/project.png"));
    mTreeWidget->addTopLevelItem(projectRoot);
    QList<QAction*> actions;
    QAction* addComponent = new QAction(mTreeWidget);
    addComponent->setText(tr("添加组件"));
    QAction* setting = new QAction(mTreeWidget);
    setting->setText(tr("设置"));
    QAction* help = new QAction(mTreeWidget);
    help->setText(tr("帮助"));
    help->setIcon(QIcon(":/icon/icon/help.png"));
    actions.append(addComponent);
    actions.append(setting);
    actions.append(nullptr);
    actions.append(help);

    mTreeWidget->setActionsForMenuType(FCTreeWidget::MenuProjectRoot,
                                       actions);
        
    createGlobalDefine();
    createComponent();
    createStudy();
    createResult();
}

/**
 * @brief 获取树形结构widget
 * @return 
 */
FCTreeWidget *FCProjectTree::treeWidget() const
{
     return mTreeWidget; 
}

/**
 * @brief 创建全局定义的子树
 */
void FCProjectTree::createGlobalDefine()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* globalDefin = new QTreeWidgetItem(root);
    globalDefin->setText(0, tr("全局定义"));
    globalDefin->setIcon(0,QIcon(":/icon/icon/global_define.png"));
    QTreeWidgetItem* parameter = new QTreeWidgetItem(globalDefin);
    parameter->setText(0, tr("参数"));
    parameter->setIcon(0,QIcon(":/icon/icon/parameter.png"));
    QTreeWidgetItem* variable = new QTreeWidgetItem(globalDefin);
    variable->setText(0, tr("变量"));
    variable->setIcon(0,QIcon(":/icon/icon/variable.png"));
    QTreeWidgetItem* function = new QTreeWidgetItem(globalDefin);
    function->setText(0, tr("函数"));
    function->setIcon(0,QIcon(":/icon/icon/funtion.png"));
    // QTreeWidgetItem* material = new QTreeWidgetItem(globalDefin);
    // material->setText(0, tr("材料"));
    // material->setIcon(0,QIcon(":/icon/icon/material.png"));
       
}

/**
 * @brief 创建组件子树
 */
void FCProjectTree::createComponent()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* component = new QTreeWidgetItem(root);
    component->setText(0, tr("组件"));
    component->setIcon(0,QIcon(":/icon/icon/component.png"));
    QTreeWidgetItem* define = new QTreeWidgetItem(component);
    define->setText(0, tr("定义"));
    define->setIcon(0,QIcon(":/icon/icon/define.png"));
    QTreeWidgetItem* gemometry = new QTreeWidgetItem(component);
    gemometry->setText(0, tr("几何"));
    gemometry->setIcon(0,QIcon(":/icon/icon/geometry.png"));
    QTreeWidgetItem* material = new QTreeWidgetItem(component);
    material->setText(0, tr("材料"));
    material->setIcon(0,QIcon(":/icon/icon/material.png"));
    QTreeWidgetItem* mesh = new QTreeWidgetItem(component);
    mesh->setText(0, tr("网格"));
    mesh->setIcon(0,QIcon(":/icon/icon/mesh.png"));
    
}

/**
 * @brief 创建研究子树
 */
void FCProjectTree::createStudy()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* study = new QTreeWidgetItem(root);
    study->setText(0, tr("研究"));
    study->setIcon(0,QIcon(":/icon/icon/study1.png"));
    QTreeWidgetItem* step1 = new QTreeWidgetItem(study);
    step1->setText(0, tr("步骤1"));
    step1->setIcon(0,QIcon(":/icon/icon/study1.png"));
    QTreeWidgetItem* step2 = new QTreeWidgetItem(study);
    step2->setText(0, tr("步骤2"));
    step2->setIcon(0,QIcon(":/icon/icon/study1.png"));
}

/**
 * @brief 创建结果子树
 */
void FCProjectTree::createResult()
{
    QTreeWidgetItem* root =  mTreeWidget->topLevelItem(0);
    if(!root) {
        qDebug() << "Project Tree Root is None!";
        return;
    }
    QTreeWidgetItem* result = new QTreeWidgetItem(root);
    result->setText(0, tr("结果"));
    result->setIcon(0,QIcon(":/icon/icon/result.png"));    
    QTreeWidgetItem* plot3d = new QTreeWidgetItem(result);
    plot3d->setText(0, tr("3维绘图组"));
    plot3d->setIcon(0,QIcon(":/icon/icon/3d_plot.png"));  
    QTreeWidgetItem* plot2d = new QTreeWidgetItem(result);
    plot2d->setText(0, tr("2维绘图组"));
    plot2d->setIcon(0,QIcon(":/icon/icon/2d_plot.png"));  
    QTreeWidgetItem* plot1d = new QTreeWidgetItem(result);
    plot1d->setText(0, tr("1维绘图组"));
    plot1d->setIcon(0,QIcon(":/icon/icon/1d_plot.png"));  
}

} // namespace FC
