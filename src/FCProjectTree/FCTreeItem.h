/******************************************************************************
 * File     : FCTreeItem.h
 * Brief    : 基本树形结构的条目
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


class FCPROJECTTREE_API FCTreeItem : QTreeWidgetItem
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
    FCTreeItem(const FCTreeItem& c);
    
    virtual ~FCTreeItem();
    
public:
    //重载等号操作符
    FCTreeItem& operator=(const FCTreeItem& item);
    //名字
    void setName(const QString& name);
    QString getName() const;
    
    //图标
    void setIcon(const QIcon& icon);
    QIcon getIcon() const;
    
    // id
    void setID(id_type id);
    id_type getID() const;
    
    
    //扩展数据操作相关
    void setProperty(int roleID, const QVariant& var);
    bool isHaveProperty(int roleID) const;
    int getPropertyCount() const;
    
    //扩展数据的获取操作
    const QVariant& property(int id) const;
    QVariant& property(int id);
    void property(int index, int& id, QVariant& var) const;
    QVariant getProperty(int id, const QVariant& defaultvar = QVariant()) const;
    QMap< int, QVariant > getPropertys() const;
    

    // 添加右键菜单action
    void addAction(QAction* action);
    
    //父子条目操作相关
    int childItemCount() const;
    
    //索引子条目
    DATreeItem* childItem(int row) const;
    
    //获取当前下的所有子节点
    QList< DATreeItem* > getChildItems() const;
    //获取所有子节点的名字
    QList< QString > getChildItemNames() const;
    
    //追加子条目 item的所有权交由父级item管理
    void appendChild(FCTreeItem* item);
    
    //插入子条目
    void insertChild(FCTreeItem* item, int row);
    
    //清空所有
    void clearChild();
    
    //判断是否存在子节点
    bool haveChild(FCTreeItem* const item) const;
    
    //提取子节点
    FCTreeItem* takeChild(int row);
    bool takeChild(FCTreeItem* const item);
    
    //返回child的索引 O(n)
    int childIndex(FCTreeItem* const item) const;
    
    //删除子对象
    void removeChild(FCTreeItem* item);
    
    //获取父级指针
    FCTreeItem* parent() const;
    
    //用于记录当前所处的层级，如果parent不为nullptr，这个将返回parent下次item对应的层级,如果没有parent，返回-1
    int index() const;
 
    
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
