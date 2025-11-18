/******************************************************************************
 * File     : FCModelBuilderWidget.h
 * Brief    : 模型构建窗口
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-10-31
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCModelBuilderWidget.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "FCTreeWidget.h"
#include "FCTreeItem.h"
#include "FCProjectTree.h"

namespace FC 
{

FCModelBuilderWidget::FCModelBuilderWidget(QWidget *parent)
    : QWidget(parent)
{

    mProjectTree = new FCProjectTree(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mProjectTree->treeWidget()); // 需要添加 getter
    layout->setContentsMargins(2, 2, 2, 2);
}

FCModelBuilderWidget::~FCModelBuilderWidget()
{
    
}

/**
 * @brief 构建空白工程树形目录
 */
void FCModelBuilderWidget::buildBlankProject()
{
}

} // namespace FC
