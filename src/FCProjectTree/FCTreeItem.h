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
class QAction;
class FCTree;

class FCPROJECTTREE_API FCTreeItem : public QTreeWidgetItem
{
    FC_DECLARE_PRIVATE(FCTreeItem)
    
    friend class FCTree;
public:
    using id_type = quintptr;
    // item 类型
    enum ItemType
    {
        RootItem = QTreeWidgetItem::UserType + 1,  // 根节点
        CategoryItem,       // 类目节点
        EntityGroupItem,    // 实体组节点
        Entity,             // 实体节点
    };
    
    enum PropertyRole
    {
        RoleName = 0,          ///< 名字
        RoleIcon,              ///< 图标
        RoleValue,             ///< 值
        RoleUserDefine = 1000  ///< 用户自定义
    };
    
public:
    FCTreeItem(FCTreeItem* parentItem = nullptr);
    FCTreeItem(const QString& text, FCTreeItem* parentItem = nullptr);
    FCTreeItem(const QIcon& icon, const QString& text, FCTreeItem* parentItem = nullptr);
    
    virtual ~FCTreeItem();
    
public:

    //名字
    void setName(const QString& name);
    QString getName() const;
    
    //图标
    void setIcon(const QIcon& icon);
    QIcon getIcon() const;
    
    // id
    void setID(id_type id);
    id_type getID() const;
    
    void setType(ItemType type);
    ItemType getType() const;
    
    // 添加右键菜单action
    void addContextAction(::QAction* action);
    
    
    //扩展数据操作相关
    // void setProperty(int roleID, const QVariant& var);
    // bool isHaveProperty(int roleID) const;
    // int getPropertyCount() const;
    
    //扩展数据的获取操作
    // const QVariant& property(int id) const;
    // QVariant& property(int id);
    // void property(int index, int& id, QVariant& var) const;
    // QVariant getProperty(int id, const QVariant& defaultvar = QVariant()) const;
    // QMap< int, QVariant > getPropertys() const;
    
    
    //判断是否在树节点上，如果此item是在satree上，此函数返回true，否则为false
    bool isOnTree() const;
    //获取树的指针
    FCTree* getTree() const;
    //判断是否是顶层，parent为nullptr既是说明在顶层
    bool isRootItem() const;
    //设置树
    void setTree(FCTree* tree);
};

} // namespace FC


#endif // FCTREEITEM_H
