/******************************************************************************
 * File     : FCProjectTree.h
 * Brief    : 工程树管理
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-18
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#ifndef FCPROJECTTREE_H
#define FCPROJECTTREE_H
#include "FCProjcetTreeAPI.h"
#include <QObject>
#include <QString>


namespace FC 
{
class FCTreeWidget;
class FCPROJECTTREE_API FCProjectTree : public QObject
{
    Q_OBJECT
    
    enum RoleType
    {
        ContextActions = Qt::UserRole + 1,  // 右键菜单数据
        EntityMetaData,           // 元数据
    };
    
public:
    explicit FCProjectTree(QObject *parent = nullptr);
    
    // 创建默认工程
    void createDefaultProject(const QString& name = tr("Untitled"));
    
    FCTreeWidget* treeWidget() const;
    
private:
    // 创建全局定义的子树
    void createGlobalDefine();
    // 创建组件子树
    void createComponent();
    // 创建研究子树
    void createStudy();
    // 创建结果子树
    void createResult();
    
signals:
    
    
    
private:
    FCTreeWidget* mTreeWidget;
    
};
} // namespace FC



#endif // FCPROJECTTREE_H
