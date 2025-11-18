/******************************************************************************
 * File     : FCTree.cpp
 * Brief    : 树形目录
 * Author   : Kinvy
 * Email    : kinvy66@163.com
 * Date     : 2025-11-13
 * Version  : V0.0.1
 * Detail   :
 * Copyright: Copyright By Kinvy, All Rights Reserved
******************************************************************************/
#include "FCTreeWidget.h"
#include <QTreeWidget>
#include <QMenu>
#include <QContextMenuEvent>

namespace FC 
{

FCTreeWidget::FCTreeWidget(QWidget *parent)
    :QTreeWidget(parent)
{
    setHeaderHidden(true);
    this->setColumnCount(1);
    // setContextMenuPolicy(Qt::CustomContextMenu);
}

/**
 * @brief 设置item的右键菜单
 * @param menuType
 * @param actions
 */
void FCTreeWidget::setActionsForMenuType(MenuType menuType, const QList<QAction *> &actions)
{
    mMenuActions[menuType] = actions;
}

/**
 * @brief 右键点击事件
 * @param event
 */
void FCTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QTreeWidgetItem* item = itemAt(event->pos());
    if (!item) {
        return;
    }
    
    MenuType type = getItemMenuType(item);
    
    auto actions = mMenuActions.value(type);
    if (actions.isEmpty()) return;
    
    QMenu menu(this);
    for (QAction* act : actions) {
        if(act == nullptr) {
            menu.addSeparator();
            continue;
        }
        menu.addAction(act);
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
    
    QVariant v = item->data(0, Qt::UserRole);
    if (!v.isValid()) return MenuDefault;
    
    return (MenuType)v.toInt();
}

} // namespace FC

