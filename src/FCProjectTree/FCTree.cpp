/******************************************************************************
 * File     : FCTree.cpp
 * Brief    : 树形目录
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCTree.h"
#include <QTreeWidget>

namespace FC 
{

FCTree::FCTree(QWidget *parent)
    :QTreeWidget(parent)
{
    setHeaderHidden(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

/**
 * @brief 添加item
 * @param item
 */
void FCTree::addItem(FCTreeItem *item)
{
    
}

/**
 * @brief 添加item列表
 * @param items
 */
void FCTree::addItems(const QList<FCTreeItem *> &items)
{
    
}


} // namespace FC

