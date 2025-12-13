/**
 * @file FCPostProcessingViewProvider.cpp
 * @brief 后处理可视化管理器
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCPostProcessingViewProvider.h"
#include "FCGraphViewWindow.h"
#include "FCPostProcessingData.h"
#include "FCPostProcessingKernal.h"
#include "FCPostProcessingViewObject.h"

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkLookupTable.h>
#include <vtkScalarsToColors.h>
#include <QDebug>
#include <assert.h>

namespace FC 
{

FCPostProcessingViewProvider::FCPostProcessingViewProvider(FCGraphViewWindow *viewWindow, QObject *parent)
    :mGraphViewWindow(viewWindow)
    , mPostProcessingData(FCPostProcessingData::getInstance())
    , QObject(viewWindow)
{
}

FCPostProcessingViewProvider::~FCPostProcessingViewProvider()
{
    
}

/**
 * @brief 新建或者删除后处理，更新显示
 */
void FCPostProcessingViewProvider::updatePostProcessingActorSlot()
{
    QList<IdType> ids =  mPostProcessingData->getAllPostProcessingID();
    for (auto id : ids)
    {
        if (!mPostProcessingViewObjects.contains(id))
        {
            auto vobj = new FCPostProcessingViewObject(id);
            mPostProcessingViewObjects.insert(id, vobj);
            updateDisplayModel(id);
            updateGraphOption(id);
            vtkActor* ac = vobj->getActor();
            mGraphViewWindow->AppendActor(ac);
        }
    }
    // 删除
    QList<IdType> displayed = mPostProcessingViewObjects.keys();
    for (auto id : displayed)
    {
        if (mPostProcessingData->isContainsKernal(id))
            continue;
        this->removeDisplay(id);
    }
}

void FCPostProcessingViewProvider::showPostProcessingSlot(IdType postID, bool r)
{
    qDebug() << "showPostProcessingSlot: postID" << postID << "show:" << r;
    
    if (r) {
        // 如果ViewObject已存在，先移除
        if (mPostProcessingViewObjects.contains(postID)) {
            qDebug() << "showPostProcessingSlot: removing existing view object for postID" << postID;
            removeDisplay(postID);
        }
        
        // 创建或重新创建ViewObject
        qDebug() << "showPostProcessingSlot: creating new view object for postID" << postID;
        auto vobj = new FCPostProcessingViewObject(postID);
        mPostProcessingViewObjects.insert(postID, vobj);
        
        // 更新显示数据（确保数据已生成）
        qDebug() << "showPostProcessingSlot: updating display data";
        vobj->updateDisplayData();
        
        // 更新显示模式和选项
        qDebug() << "showPostProcessingSlot: updating display model and graph option";
        updateDisplayModel(postID);
        updateGraphOption(postID);
        
        vtkActor* ac = vobj->getActor();
        if (ac) {
            qDebug() << "showPostProcessingSlot: appending actor to renderer for postID" << postID;
            
            // 检查Actor的状态
            vtkMapper* mapper = ac->GetMapper();
            if (mapper) {
                qDebug() << "showPostProcessingSlot: actor has mapper";
                vtkDataSet* input = mapper->GetInput();
                if (input) {
                    qDebug() << "showPostProcessingSlot: mapper input has" 
                             << input->GetNumberOfPoints() << "points and"
                             << input->GetNumberOfCells() << "cells";
                } else {
                    qWarning() << "showPostProcessingSlot: mapper input is null";
                }
            } else {
                qWarning() << "showPostProcessingSlot: actor has no mapper";
            }
            
            qDebug() << "showPostProcessingSlot: actor visibility:" << ac->GetVisibility();
            qDebug() << "showPostProcessingSlot: actor pickable:" << ac->GetPickable();
            
            mGraphViewWindow->AppendActor(ac);
            mGraphViewWindow->reRender();
            qDebug() << "showPostProcessingSlot: actor appended and render called";
        } else {
            qWarning() << "showPostProcessingSlot: actor is null for postID" << postID;
        }
    } else {
        // 隐藏
        qDebug() << "showPostProcessingSlot: hiding postID" << postID;
        removeDisplay(postID);
    }
}

void FCPostProcessingViewProvider::highLighKernel(IdType postID)
{
    auto vobj = mPostProcessingViewObjects.value(postID);
    if (vobj) {
        vobj->highLight();
        mGraphViewWindow->reRender();
    }
}

void FCPostProcessingViewProvider::clearHighLight()
{
    QList<FCPostProcessingViewObject *> vobjs = mPostProcessingViewObjects.values();
    for (auto v : vobjs)
        if (v->isKernalHighLight())
            v->clearHighLight();
}

void FCPostProcessingViewProvider::updateDisplayModel(IdType postID)
{
    // 更新显示模式，例如表面、线框等
    auto vobj = mPostProcessingViewObjects.value(postID);
    if (!vobj) return;
    
    vtkActor* actor = vobj->getActor();
    if (actor) {
        // 设置为表面显示
        actor->GetProperty()->SetRepresentationToSurface();
        actor->GetProperty()->SetEdgeVisibility(false);
    }
}

void FCPostProcessingViewProvider::updateGraphOption(IdType postID)
{
    // 更新颜色等渲染选项
    auto vobj = mPostProcessingViewObjects.value(postID);
    if (!vobj) return;
    
    FCPostProcessingKernal* kernal = mPostProcessingData->getPostProcessingKernalByID(postID);
    if (!kernal) return;
    
    vtkActor* actor = vobj->getActor();
    if (actor) {
        // 使用标量场着色
        vtkDataSetMapper* mapper = vtkDataSetMapper::SafeDownCast(actor->GetMapper());
        if (mapper) {
            vtkLookupTable* lut = vobj->getLookupTable();
            if (lut) {
                // vtkLookupTable 继承自 vtkScalarsToColors，需要显式转换
                mapper->SetLookupTable(static_cast<vtkScalarsToColors*>(lut));
                mapper->SetScalarModeToUsePointData();
            }
        }
    }
}

void FCPostProcessingViewProvider::showPostProcessing(IdType postID, bool show)
{
    auto vobj = mPostProcessingViewObjects.value(postID);
    if (!vobj) return;
    
    vtkActor* actor = vobj->getActor();
    if (actor) {
        actor->SetVisibility(show ? 1 : 0);
        mGraphViewWindow->reRender();
    }
}

void FCPostProcessingViewProvider::highLighSelectItem(QMultiHash<int, int> *items)
{
    // 实现高亮选中项
    Q_UNUSED(items);
}

void FCPostProcessingViewProvider::removePostProcessingActor(IdType postID)
{
    removeDisplay(postID);
}

void FCPostProcessingViewProvider::removeDisplay(IdType postID)
{
    auto vobj = mPostProcessingViewObjects.value(postID);
    if (!vobj) return;
    
    vtkActor* actor = vobj->getActor();
    if (actor) {
        mGraphViewWindow->RemoveActor(actor);
    }
    
    mPostProcessingViewObjects.remove(postID);
    delete vobj;
}

} // namespace FC

