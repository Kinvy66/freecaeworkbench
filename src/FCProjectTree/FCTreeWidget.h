/**
 * @file FCTreeWidget.h
 * @brief 树形目录
 * @date 2025-11-13
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCTREEWIDGET_H
#define FCTREEWIDGET_H
#include "FCProjcetTreeAPI.h"
#include <QTreeWidget>
#include <QAction>
#include <QHash>
#include <QList>
#include <QIcon>
#include <functional>


namespace FC 
{

enum RoleType
{
    ContextActions = Qt::UserRole + 1,  // 右键菜单数据
    EntityItmeID,                       // 实体条目id
    EntityItmeType,                     // 条目类型
    EntityMetaData,                     // 实体元数据
};

class FCPROJECTTREE_API FCTreeWidget : public QTreeWidget
{
    Q_OBJECT
    friend class FCProjectTree;
private:
    struct ActionTemplate {
        QString text;
        QString objectName;
        QIcon icon;
        
        bool separator = false;
        QList<ActionTemplate> subActions;
                
        ActionTemplate() = default;
        
        // text-only
        ActionTemplate(const QString& t, const QString& obj = QString())
            : text(t), objectName(obj) {}
        
        // icon-only
        ActionTemplate(const QIcon& icon, const QString& obj = QString())
            : icon(icon), objectName(obj) {}
        
        // text + icon
        ActionTemplate(const QString& t, const QIcon& icon, const QString& obj = QString())
            : text(t), objectName(obj), icon(icon) {}
        
        // 添加子动作（支持连写）
        ActionTemplate& add(const ActionTemplate& child)
        {
            subActions.append(child);
            return *this;
        }
        
        // 分隔符
        static ActionTemplate sep()
        {
            ActionTemplate t;
            t.separator = true;
            return t;
        }
        
        bool isSeparator() const { return separator; }
        bool hasSubMenu() const { return !subActions.isEmpty(); }
    };
public:
    
    // item 右键菜单类型
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
        // MenuComponentMaterial,     // 材料
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
    ~FCTreeWidget() override = default;
    
    // 为特定菜单类型注册一组 QAction（全局 action）
    void setActionTemplates(MenuType type, const QList<ActionTemplate> &templates);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    
private:
     MenuType getItemMenuType(QTreeWidgetItem* item) const;
    void buildMenuFromTemplate(QMenu* menu,const QList<ActionTemplate>& templates,
                            QTreeWidgetItem* item, MenuType type);
    
 signals:
     void actionTriggered(int menuType, const QString &actionText, QTreeWidgetItem *item);
     
private:
    // QMap<MenuType, QList<QAction*>> mMenuActions;
    QHash<MenuType, QList<ActionTemplate>> mActionTemplates;
    
    // QTreeWidgetItem* mLastContextItem;
    
};
} // namespace FC


#endif // FCTREEWIDGET_H
