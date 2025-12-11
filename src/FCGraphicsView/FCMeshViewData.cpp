/**
 * @file FCMeshViewData.cpp
 * @brief 网格可视化对象管理
 * @date 2025-12-11
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshViewData.h"
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkProperty.h>

namespace FC 
{

FCMeshViewData::~FCMeshViewData()
{
    qDeleteAll(mMeshObjs);
    mMeshObjs.clear();
}

void FCMeshViewData::addMesh(IdType id, vtkPolyData* mesh)
{
    if (!mesh) return;
    if (mMeshObjs.contains(id))
        removeMesh(id);
    
    FCMeshViewObject* obj = new FCMeshViewObject(mesh);
    mMeshObjs.insert(id, obj);
}

void FCMeshViewData::removeMesh(IdType id)
{
    if (!mMeshObjs.contains(id)) return;
    delete mMeshObjs.take(id);
}

FCMeshViewObject* FCMeshViewData::getMeshObject(IdType id)
{
    return mMeshObjs.value(id, nullptr);
}

QList<FCMeshViewData::IdType> FCMeshViewData::getAllMeshIDs() const
{
    return mMeshObjs.keys();
}

void FCMeshViewData::setHighlight(IdType id, bool on)
{
    auto obj = getMeshObject(id);
    if (!obj || !obj->actor) return;
    obj->state = on ? 1 : 0;
    if (on)
        obj->actor->GetProperty()->SetColor(1.0, 0.5, 0.0); // 高亮橙色
    else
        obj->actor->GetProperty()->SetColor(0.8, 0.8, 0.8); // 默认灰色
}

void FCMeshViewData::setSelect(IdType id, bool on)
{
    auto obj = getMeshObject(id);
    if (!obj || !obj->actor) return;
    obj->state = on ? 2 : 0;
    if (on)
        obj->actor->GetProperty()->SetColor(0.0, 1.0, 0.0); // 选中绿色
    else
        obj->actor->GetProperty()->SetColor(0.8, 0.8, 0.8); // 默认灰色
}
} // namespace FC
