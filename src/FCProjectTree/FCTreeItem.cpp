/******************************************************************************
 * File     : FCTreeItem.cpp
 * Brief    : 基本树形结构的条目
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCTreeItem.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include "FCTree.h"
#include "fc_order_small_map.hpp"


//===================================================
// using FC namespace -- 禁止在头文件using！！
//===================================================
using namespace FC;

class FCTreeItem::PrivateData
{
    FC_DECLARE_PUBLIC(FCTreeItem)
    
public:
    FCTreeItem* mParent { nullptr };
    int mIndex { -1 };  ///< 用于记录当前所处的层级，如果parent不为nullptr，这个将返回parent下item对应的层级
    FCTreeItem::id_type mID { 0 };
    FCTree* mTree { nullptr };  ///< 绑定的树
    QList<FCTreeItem* > mChilds;
    fc_order_small_map< int, QVariant, QVector< int >, QVector< QVariant > > mPropertys;  ///< 定义属性
    QList<QAction*> mActions;
    QMenu* mMenu;
    
public:
    PrivateData(FCTreeItem *par)
        : q_ptr(par)
        , mID(reinterpret_cast< FCTreeItem::id_type >(par))
    {
        mPropertys[ FCTreeItem::RoleName ]  = QString();
        mPropertys[ FCTreeItem::RoleIcon ]  = QIcon();
        mPropertys[ FCTreeItem::RoleValue ] = QVariant();
    }
    
    
    ~PrivateData()
    {
        clearChild();
    }
    
    void clearChild()
    {
        QList< FCTreeItem* > childs = mChilds;
        
        for (int i = 0; i < childs.size(); ++i) {
            delete childs[ i ];
        }
        mChilds.clear();
    }
    
    void updateFieldCount(int startRow = 0)
    {
        const int cc = mChilds.size();
        
        for (int i = startRow; i < cc; ++i) {
            mChilds[ i ]->d_ptr->mIndex = i;
        }
    }
    
};

// 把from的子对象都复制一份到to
void copy_childs(const FCTreeItem* from, FCTreeItem* to);

// 打印一个item内容
QDebug& print_one_item(QDebug& dbg, const FCTreeItem& item, const QString& prefix, bool isNewline = true);
QDebug& print_item_and_child_items(QDebug& dbg, const FCTreeItem& item, int indent);
//===================================================
//
//===================================================
void copy_childs(const FCTreeItem* from, FCTreeItem* to)
{
    QList< FCTreeItem* > items = from->takeChildren();
    const auto size            = items.size();
    
    for (auto i = 0; i < size; ++i) {
        FCTreeItem* tmp = new FCTreeItem();
        // 如果还有子item，会触发递归
        *tmp = *(items[ i ]);
        to->addChildren(tmp);
    }
}


FCTreeItem::FCTreeItem(FCTreeItem *parentItem)
    : d_ptr(new FCTreeItem::PrivateData(this))

{
    if(parentItem)
    {
        parentItem->addChild(this);    
    }
}

FCTreeItem::FCTreeItem(const QString &text, FCTreeItem *parentItem)
    : d_ptr(new FCTreeItem::PrivateData(this))
{
    setName(text);
    if(parentItem)
    {
        parentItem->addChild(this);    
    }
}

FCTreeItem::FCTreeItem(const QIcon &icon, const QString &text, FCTreeItem *parentItem)
    : d_ptr(new FCTreeItem::PrivateData(this))
{
    setName(text);
    setIcon(icon);
    if (parentItem) {
        parentItem->appendChild(this);
    }
}

/**
 * @brief 拷贝构造函数
 * @param c
 */
FCTreeItem::FCTreeItem(const FCTreeItem &c) : d_ptr(new FCTreeItem::PrivateData(this))
{
    *this = c;
}

FCTreeItem::~FCTreeItem()
{
    clearChild();
    FCTreeItem* par = parent();
    
    if (par) {
        int indexOfPar = par->childIndex(this);
        if (indexOfPar >= 0) {
            par->d_ptr->mChilds.removeAt(indexOfPar);
            par->d_ptr->updateFieldCount(indexOfPar);
        }
    }
    if (d_ptr->mTree) {
        // d_ptr->m_tree->
    }
}

/**
 * @brief 等号操作符
 * @param item 另外等待拷贝的item
 * @return 返回自身引用
 * @note m_parent,m_fieldRow,id 不会发生拷贝
 */
FCTreeItem &FCTreeItem::operator=(const FCTreeItem &item)
{
    clearChild();
    d_ptr->mPropertys = item.d_ptr->mPropertys;
    // 复制子对象
    copy_childs(&item, this);
    return (*this);
}

void FCTreeItem::clearChild()
{
    d_ptr->clearChild();
}
