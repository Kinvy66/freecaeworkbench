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
#ifndef FCTREEWIDGET_H
#define FCTREEWIDGET_H
#include "FCProjcetTreeAPI.h"
#include <QTreeWidget>
#include <QMap>
#include <QList>
#include <QAction>
#include "FCTreeItem.h"


namespace FC 
{
class FCPROJECTTREE_API FCTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
       
    enum MenuType {
        MenuProjectRoot,        // 工程根
        MenuDefault,            // 默认的菜单
        MenuGlobalDefine,       // 全局定义
        MenuParameterGroup,     // 参数组
        MenuParameterCase,      // 参数case
        MenuVariable,           // 变量
        MenuFunction,           // 函数
        MenuComponent,          // 组件
        MenuComponentDefin,     // 组件定义
        MenuComponentGeometry,  // 几何
        MenuComponentGeometryEntity,  // 几何体
        MenuComponentPhysic,         // 物理场
        MenuComponentMesh,          // 网格
        MenuComponentMeshEntity,   // 网格实体
        MenuStudyGrop,             // 研究
        MenuStudyStep,              // 研究步骤
        MenuResult,             // 结果
        MenuResult3DPlotGroup,       // 3维绘图组
        MenuResult3DPlot,       // 3维绘图
        MenuResult2DPlotGroup,       // 2维绘图组
        MenuResult2DPlot,       // 2维绘图
        MenuResult1DPlotGroup,       // 1维绘图组
        MenuResult1DPlot,       // 1维绘图
        
    };
    explicit FCTreeWidget(QWidget* parent = nullptr);
    
    // 为特定菜单类型注册一组 QAction（全局 action）
    void setActionsForMenuType(MenuType menuType, const QList<QAction*> &actions);
    
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    
private:
     MenuType getItemMenuType(QTreeWidgetItem* item) const;
    
private:
    QMap<MenuType, QList<QAction*>> mMenuActions;
    
};
} // namespace FC


#endif // FCTREEWIDGET_H
