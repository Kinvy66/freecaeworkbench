/**
 * @file FCTreeItem.h
 * @brief 树形结构的条目
 * @date 2025-11-12
 * @version V0.0.1
 * @details 继承自QTreeWidgetItem 添加右键菜单功能
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCTREEITEM_H
#define FCTREEITEM_H
#include "FCProjcetTreeAPI.h"
#include <QTreeWidgetItem>
#include <QString>
#include <QIcon>
#include <QVariant>



namespace FC 
{
class FCTree;
class FCPROJECTTREE_API FCTreeItem : public QTreeWidgetItem
{

};

} // namespace FC


#endif // FCTREEITEM_H
