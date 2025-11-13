/******************************************************************************
 * File     : FCTree.h
 * Brief    : 树形目录
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCTREE_H
#define FCTREE_H
#include "FCProjcetTreeAPI.h"
#include <QTreeWidget>
#include <QList>
#include "FCTreeItem.h"


namespace FC 
{
class FCPROJECTTREE_API FCTree : public QTreeWidget
{
public:
    FCTree(QWidget* parent = nullptr);
    

    void addItem(FCTreeItem* item);
    void addItems(const QList<FCTreeItem*>& items);
    
    
    
};
} // namespace FC


#endif // FCTREE_H
