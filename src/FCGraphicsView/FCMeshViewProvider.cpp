/**
 * @file FCMeshViewProvider.cpp
 * @brief 网格可视化管理器
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshViewProvider.h"
#include "FCMeshViewData.h"
#include "FCGraphViewWindow.h"
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkDataSetSurfaceFilter.h>
#include "FCMeshData.h"
#include "FCMeshKernal.h"

#include <QDebug>

namespace FC 
{

FCMeshViewProvider::FCMeshViewProvider(FCGraphViewWindow* viewWindow, QObject* parent)
    : mGraphViewWindow(viewWindow), QObject(viewWindow)
{
    mViewData = new FCMeshViewData;
}

FCMeshViewProvider::~FCMeshViewProvider()
{
    removeAllMeshes();
    delete mViewData;
}

void FCMeshViewProvider::showMesh(IdType id, bool render)
{
    if (!mGraphViewWindow) return;
    FCMeshKernal* k = FCMeshData::getInstance()->getMeshKernalByID(id);
    vtkDataSet* mesh = k->getMeshData();
    if (!mesh) return;
    
    // --- 将 vtkDataSet 转成 vtkPolyData ---
    vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter =
        vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    surfaceFilter->SetInputData(mesh);
    surfaceFilter->Update();
    
    vtkPolyData* polyMesh = surfaceFilter->GetOutput();
    
    // 添加到 ViewData
    mViewData->addMesh(id, polyMesh);
    auto obj = mViewData->getMeshObject(id);
    
    vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyMesh);
    
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetRepresentationToSurface();
    actor->GetProperty()->SetColor(0/255, 29/255, 252/255); // 默认灰色
    actor->SetVisibility(true);
    mGraphViewWindow->AppendActor(actor, D3, false);
    
    obj->actor = actor;
    mActors.insert(id, actor);
    
    if (render)
        mGraphViewWindow->resetCamera();
}

/**
 * @brief 更新网格actor
 * @param id
 * @note 只执行删除旧actor的操作，新的actor显示在 @sa showMesh 中
 */
void FCMeshViewProvider::updateMeshDisplayActor(const IdType id)
{
    FCMeshViewObject* obj = mViewData->getMeshObject(id);
    if(obj == nullptr) {
        return;
    }
    mViewData->removeMesh(id);
    
    vtkActor* ac = mActors.value(id);
    mGraphViewWindow->RemoveActor(ac);
    mGraphViewWindow->reRender();
}

void FCMeshViewProvider::removeMesh(IdType id)
{
    if (!mGraphViewWindow) return;
    auto actor = mActors.value(id, nullptr);
    if (actor)
        mGraphViewWindow->RemoveActor(actor);

    mActors.remove(id);
    mViewData->removeMesh(id);

    mGraphViewWindow->reRender();
}

void FCMeshViewProvider::updateMeshColor(IdType id)
{
    auto obj = mViewData->getMeshObject(id);
    if (!obj || !obj->actor) return;
    if (obj->state == 0)
        obj->actor->GetProperty()->SetColor(0.8, 0.8, 0.8);
    else if (obj->state == 1)
        obj->actor->GetProperty()->SetColor(1.0, 0.5, 0.0);
    else if (obj->state == 2)
        obj->actor->GetProperty()->SetColor(0.0, 1.0, 0.0);
}

void FCMeshViewProvider::highlightMesh(IdType id, bool on)
{
    mViewData->setHighlight(id, on);
    updateMeshColor(id);
    mGraphViewWindow->reRender();
}

void FCMeshViewProvider::selectMesh(IdType id, bool on)
{
    mViewData->setSelect(id, on);
    updateMeshColor(id);
    mGraphViewWindow->reRender();
}

void FCMeshViewProvider::removeAllMeshes()
{
    for (auto actor : mActors)
    {
        mGraphViewWindow->RemoveActor(actor);
    }
    mActors.clear();
    mViewData->~FCMeshViewData();
    mGraphViewWindow->reRender();
}

} // namespace FC
