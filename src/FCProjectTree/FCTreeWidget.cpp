/******************************************************************************
 * File     : FCTreeWidget.cpp
 * Brief    : 树形目录
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCTreeWidget.h"
#include <QMenu>
#include <QContextMenuEvent>

namespace FC 
{

FCTreeWidget::FCTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{
    setHeaderHidden(true);
    this->setColumnCount(1);
}

/**
 * @brief 设置item的右键菜单
 * @param menuType
 * @param actions
 */

/**
 * @brief 设置item的右键菜单生成模板
 * @param type
 * @param templates
 */
void FCTreeWidget::setActionTemplates(MenuType type, const QList<ActionTemplate> &templates)
{
    mActionTemplates[type] = templates;    
}

/**
 * @brief 右键点击事件
 * @param event
 */
void FCTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem* item = itemAt(event->pos());
    if (!item) return;
    
    MenuType type = getItemMenuType(item);
    auto templates = mActionTemplates.value(type);
    if (templates.isEmpty()) return;
    
    QMenu menu(this);
    
    for (const ActionTemplate &tpl : templates) {
        if (tpl.isSeparator()) {
            menu.addSeparator();
            continue;
        }
        
        QAction* act = tpl.icon.isNull() ? menu.addAction(tpl.text) : menu.addAction(tpl.icon, tpl.text);
        if (!tpl.objectName.isEmpty())
            act->setObjectName(tpl.objectName);
        
        const QString objName = act->objectName();
        connect(act, &QAction::triggered, this, [this, type, objName, item]() {
            emit actionTriggered(static_cast<int>(type), objName, item);
        });
    }
    
    menu.exec(event->globalPos());
}

/**
 * @brief 获取item type
 * @param item
 * @return 
 */
FCTreeWidget::MenuType FCTreeWidget::getItemMenuType(QTreeWidgetItem *item) const
{
    if (!item) return MenuDefault;
    QVariant v = item->data(0, RoleType::ContextActions);
    if (!v.isValid()) return MenuDefault;
    return (MenuType)v.toInt();
}

} // namespace FC

