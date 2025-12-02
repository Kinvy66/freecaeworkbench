/**
 * @file FCProjectTree.h
 * @brief 工程树管理
 * @date 2025-11-18
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPROJECTTREE_H
#define FCPROJECTTREE_H
#include "FCProjcetTreeAPI.h"
#include <QObject>
#include <QString>

class QTreeWidgetItem;
class QAction;

namespace FC 
{
class FCTreeWidget;

class FCPROJECTTREE_API FCProjectTree : public QObject
{
    Q_OBJECT
    

public:
    explicit FCProjectTree(QObject *parent = nullptr);
    ~FCProjectTree() override = default;
    
    // 创建默认工程
    void createDefaultProject(const QString& name = tr("Untitled"));
    
    FCTreeWidget* treeWidget() const;
    // 添加几何模型
    void addGeometry(const QString& name);
    
private slots:
    void onTreeActionTriggered(int menuType, const QString &actionText, QTreeWidgetItem *item);
    
private:
    // 创建全局定义的子树
    void createGlobalDefine();
    // 创建组件子树
    void createComponent();
    // 创建研究子树
    void createStudy();
    // 创建结果子树
    void createResult();
    
    // 构建右键菜单
    void buildProjectRootActions();
    void buildGlobalDefineuActions();
    void buildCompnentActions();
    void buildStudyActions();
    void buildResultActions();
    
    
    // 添加参数item
    void addNewParameter(QTreeWidgetItem* parent);
    // 添加变量item
    void addNewVariable(QTreeWidgetItem* parent);
    // 添加函数item
    void addNewFunction(QTreeWidgetItem* parent);
    // 查找同类型的编号
    int findInsertIndexByType(QTreeWidgetItem* parent, int typeValue);
    // 获取下一个编号
    QString  nextChildName(QTreeWidgetItem* parent, const QString& prefix);
    
// signals:
//     void addGeometry();
    
    
private:
    FCTreeWidget* mTreeWidget;
    // 几何根节点
    QTreeWidgetItem* mGeoRoot;
    
    
};
} // namespace FC



#endif // FCPROJECTTREE_H
