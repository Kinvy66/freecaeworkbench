/**
 * @file FCModelBuilderWidget.cpp
 * @brief 模型构建窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
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

void FCModelBuilderWidget::addGeometryCube()
{
    
}

void FCModelBuilderWidget::addGeometry(const QString &name)
{
    qDebug() << "FCModelBuilderWidget::addGeometry";
    mProjectTree->addGeometry(name);
}


/**
 * @brief 构建空白工程树形目录
 */
void FCModelBuilderWidget::buildBlankProject()
{
}

} // namespace FC
