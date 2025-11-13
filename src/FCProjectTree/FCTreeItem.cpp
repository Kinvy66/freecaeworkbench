/******************************************************************************
 * File     : FCTreeItem.cpp
 * Brief    : 树形结构的条目, 
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCTreeItem.h"
#include <QMenu>
#include <QDebug>
#include "FCTree.h"
#include <QAction>

namespace FC {


class FCTreeItem::PrivateData
{
    FC_DECLARE_PUBLIC(FCTreeItem)
    
public:
    int mIndex { -1 };  ///< 用于记录当前所处的层级，如果parent不为nullptr，这个将返回parent下item对应的层级
    FCTreeItem::id_type mID { 0 };
    FCTree* mTree { nullptr };  ///< 绑定的树
    QList<::QAction*> mActions;
    ::QMenu* mMenu {nullptr};
    FCTreeItem::ItemType mType;
    
public:
    PrivateData(FCTreeItem *par)
        : q_ptr(par)
    {
        
    }
    
};

FCTreeItem::FCTreeItem(FCTreeItem *parentItem)
    : QTreeWidgetItem(parentItem)
    , d_ptr(new FCTreeItem::PrivateData(this))

{

}

FCTreeItem::FCTreeItem(const QString &text, FCTreeItem *parentItem)
    : QTreeWidgetItem(parentItem)
    , d_ptr(new FCTreeItem::PrivateData(this))
{
    setName(text);
}

FCTreeItem::FCTreeItem(const QIcon &icon, const QString &text, FCTreeItem *parentItem)
    : QTreeWidgetItem(parentItem)
    , d_ptr(new FCTreeItem::PrivateData(this))
{
    setName(text);
    setIcon(icon);
}


FCTreeItem::~FCTreeItem()
{
    
}

/**
 * @brief 设置名称
 * @param name
 */
void FCTreeItem::setName(const QString &name)
{
    setText(0, name);
}

/**
 * @brief 获取名称
 * @return 
 */
QString FCTreeItem::getName() const
{
    return text(0);
}

/**
 * @brief 设置图标
 * @param icon
 */
void FCTreeItem::setIcon(const QIcon &icon)
{
    QTreeWidgetItem::setIcon(0, icon);
    
}

/**
 * @brief 获取图标
 * @return 
 */
QIcon FCTreeItem::getIcon() const
{
    return icon(0);
}

/**
 * @brief 设置id
 * @param id
 */
void FCTreeItem::setID(id_type id)
{
    d_ptr->mID = id;    
}

/**
 * @brief 获取id
 * @param type
 */
FCTreeItem::id_type FCTreeItem::getID() const
{
    return (d_ptr->mID);
    
}

/**
 * @brief 设置item类型
 * @param type
 */
void FCTreeItem::setType(ItemType type)
{
    d_ptr->mType = type;
}

/**
 * @brief 获取item类型
 * @return 
 */
FCTreeItem::ItemType FCTreeItem::getType() const
{
    return d_ptr->mType;
}

/**
 * @brief 添加右键菜单action
 * @param action
 */
void FCTreeItem::addContextAction(::QAction *action)
{
    if(!d_ptr->mMenu){
        d_ptr->mMenu = new QMenu();
    }
    
    if (!action) return;
    d_ptr->mActions.append(action);
    
    // Ensure menu exists and parent it to treeWidget (if available)
    if (!d_ptr->mMenu) {
        QWidget *parentWidget = nullptr;
        if (QTreeWidgetItem *p = parent()) {
            if (p->treeWidget())
                parentWidget = p->treeWidget();
        } else if (treeWidget()) {
            parentWidget = treeWidget();
        }
        d_ptr->mMenu = new QMenu(parentWidget);
    }
    d_ptr->mMenu->addAction(action);
}

/**
 * @brief 是否在某个树结构中
 * @return 
 */
bool FCTreeItem::isOnTree() const
{
    return ((d_ptr->mTree) != nullptr);
    
}

/**
 * @brief 获取树
 * @return 
 */
FCTree *FCTreeItem::getTree() const
{
    return d_ptr->mTree;
    // return treeWidget();
}

/**
 * @brief 是否为根节点
 * @return 
 * @note 根节点的父对象为 nullptr
 */
bool FCTreeItem::isRootItem() const
{
    // if (d_ptr->mTree) {
    //     return d_ptr->mTree->isRootItem(this);
    // }
    return parent() ? false : true;
}

/**
 * @brief 设置树, todo: 有点多余，应该可以删除
 * @param tree
 */
void FCTreeItem::setTree(FCTree *tree)
{
    if (d_ptr->mTree == tree)
        return;
    
    d_ptr->mTree = tree;
    
    // 同步给所有子节点
    const int cc = childCount();
    for (int i = 0; i < cc; ++i) {
        auto* childItem  = dynamic_cast<FCTreeItem*>(child(i));
        if (childItem )
            childItem ->setTree(tree);
    }
}

}
