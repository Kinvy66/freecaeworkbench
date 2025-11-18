/******************************************************************************
 * File     : FCTreeItem.h
 * Brief    : 树形结构的条目，继承自QTreeWidgetItem 添加右键菜单功能
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-12
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
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
