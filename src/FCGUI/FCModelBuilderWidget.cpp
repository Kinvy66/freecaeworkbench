/**
 * @file FCModelBuilderWidget.cpp
 * @brief 模型构建窗口
 * @date 2025-10-31
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCModelBuilderWidget.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include "FCTreeWidget.h"
#include "FCTreeItem.h"
#include "FCProjectTree.h"

namespace FC 
{

FCModelBuilderWidget::FCModelBuilderWidget(QWidget *parent)
    : QWidget(parent)
{

    mProjectTree = new FCProjectTree(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mProjectTree->treeWidget()); // 需要添加 getter
    layout->setContentsMargins(2, 2, 2, 2);
    connect(mProjectTree, &FCProjectTree::currentItemChanged,
            this, &FCModelBuilderWidget::onCurrentItemChanged);
    connect(mProjectTree, &FCProjectTree::deleteGeometryEntity,
            this,&FCModelBuilderWidget::deleteGeometryEntity);
}

FCModelBuilderWidget::~FCModelBuilderWidget()
{
    
}

void FCModelBuilderWidget::updateGeometryTree(const IdType id, const QString &name)
{
    qDebug() << "FCModelBuilderWidget::addGeometry, id:" << id;
    mProjectTree->updateGeometryTree(id, name);
}

void FCModelBuilderWidget::updateMeshTree(const IdType id, const QString &name)
{
    mProjectTree->updateMeshTree(id, name);
    
}

/**
 * @brief 删除当前选中的几何实体
 */
void FCModelBuilderWidget::deleteEntityItem()
{
    mProjectTree->deleteEntityItem();
}


void FCModelBuilderWidget::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString currentName = "None";
    QString previousName = "None";
    IdType id = 0;
    EntityType type = EntityTypeNone;
    
    if (current) {
        
        QVariant var = current->data(0, RoleType::EntityItmeID);
        if(!var.isValid() || var.isNull()) {
            qDebug() << "Current item is None";
            // return;
        } else {
            id = current->data(0, RoleType::EntityItmeID).value<IdType>();
            type = current->data(0, RoleType::EntityItmeType).value<EntityType>();
            // qDebug() << "Current item id:" << id;
        }
        currentName = current->text(0);
    }
    if (previous) {
        previousName = previous->text(0);
    }
    // qDebug().noquote()<< "Select item changeed, previous:"<< previousName << ", current:" << currentName;
    if (type == GeometryEntity) {
         emit currentGeoItemChanged(id, currentName);
    } else if (type == MeshEmtity){
        emit currentMeshItemChanged(id, currentName);
    }
}


/**
 * @brief 构建空白工程树形目录
 */
void FCModelBuilderWidget::buildBlankProject()
{
}

} // namespace FC
