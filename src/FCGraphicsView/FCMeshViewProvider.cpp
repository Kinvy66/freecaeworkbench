/**
 * @file FCMeshViewProvider.cpp
 * @brief 网格可视化管理器
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCMeshViewProvider.h"
#include "FCGraphViewWindow.h"
#include "FCMeshData.h"
#include "FCMeshKernal.h"
#include "FCMeshViewObject.h"

#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <QDebug>
#include <assert.h>

#include <QDebug>

namespace FC 
{

FCMeshViewProvider::FCMeshViewProvider(FCGraphViewWindow *viewWindow, QObject *parent)
    :mGraphViewWindow(viewWindow)
    , mMeshData(FCMeshData::getInstance())
    , QObject(viewWindow)
{
}

FCMeshViewProvider::~FCMeshViewProvider()
{
    
}

/**
 * @brief 新建或者删除网格，更新显示
 */
void FCMeshViewProvider::updateMeshActorSlot()
{
    // const int nk = mMeshData->getKernalCount();
    
    QList<IdType> ids =  mMeshData->getAllMeshID();
    for (auto id : ids)
    {
        // auto Kernal = mMeshData->getMeshKernalByID(id);
        if (!mMeshViewObjects.contains(id))
        {
            auto vobj = new FCMeshViewObject(id);
            mMeshViewObjects.insert(id, vobj);
            updateDisplayModel(id);
            updateGraphOption(id);
            vtkActor **ac = vobj->getActor();
            mGraphViewWindow->AppendActor(ac[0]);
            mGraphViewWindow->AppendActor(ac[1]);
            mGraphViewWindow->AppendActor(ac[2]);
            // 如果网格不应该显示，立即隐藏
            if (!mMeshShouldBeVisible) {
                ac[0]->SetVisibility(0);
                ac[1]->SetVisibility(0);
                ac[2]->SetVisibility(0);
            }
        }
    }
    // 删除
    QList<IdType> disPlayed = mMeshViewObjects.keys();
    for (auto ker : disPlayed)
    {
        if (mMeshData->isContainsKernal(ker))
            continue;
        this->removeDisplay(ker);
    }
}

void FCMeshViewProvider::showMesh(IdType meshID, bool r)
{
    removeDisplay(meshID);
    if (!mMeshViewObjects.contains(meshID))
    {
        auto vobj = new FCMeshViewObject(meshID);
        mMeshViewObjects.insert(meshID, vobj);
        updateDisplayModel(meshID);
        updateGraphOption(meshID);
        vtkActor **ac = vobj->getActor();
        mGraphViewWindow->AppendActor(ac[0]);
        mGraphViewWindow->AppendActor(ac[1]);
        mGraphViewWindow->AppendActor(ac[2]);
        // 如果网格不应该显示，立即隐藏
        if (!mMeshShouldBeVisible) {
            ac[0]->SetVisibility(0);
            ac[1]->SetVisibility(0);
            ac[2]->SetVisibility(0);
        }
    }
}

void FCMeshViewProvider::highLighKernel(IdType meshID)
{
    auto vobj = mMeshViewObjects.value(meshID);
    vobj->highLight();
    mGraphViewWindow->reRender();
}

// void FCMeshViewProvider::highLighMeshSet(MeshData::MeshSet *set)
// {
//     if (set == nullptr)
//         return;
//     if (!set->isVisible())
//         return;
//     QList<int> kids = set->getKernals();
//     FCMeshData::SetType type = set->getSetType();
//     QColor c = Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
//     for (int kid : kids)
//     {
//         auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
//         if (k == nullptr)
//             continue;
//         QList<int> mids = set->getKernalMembers(kid);
//         if (mids.isEmpty())
//             continue;
//         auto vobj = _viewObjects.value(k);
//         if (vobj == nullptr)
//             continue;
//         if (type == MeshData::Node)
//             vobj->setPointDisplayColor(mids, c);
//         else if (type == MeshData::Element)
//             vobj->setCellDisplayColor(mids, c);
//     }
//     _highLightSet = set;
//     _preWindow->reRender();
// }

void FCMeshViewProvider::clearHighLight()
{
    QList<FCMeshViewObject *> vobjs = mMeshViewObjects.values();
    for (auto v : vobjs)
        if (v->isKernalHighLight())
            v->clearHighLight();
    
    // if (_highLightSet != nullptr)
    // {
    //     auto gp = Setting::BusAPI::instance()->getGraphOption();
    //     MeshData::SetType type = _highLightSet->getSetType();
    //     QList<int> kids = _highLightSet->getKernals();
    //     for (int kid : kids)
    //     {
    //         auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
    //         auto vobj = mViewObjects.value(k);
    //         if (vobj == nullptr)
    //             continue;
    //         if (type == MeshData::Node)
    //             vobj->setPointColor(gp->getMeshNodeColor(), true);
    //         else if (type == MeshData::Element)
    //             vobj->setCellColor(gp->getMeshFaceColor(), true);
    //     }
    //     _highLightSet = nullptr;
    // }
    
    // QList<int> datasetList = mHighLightSelectItems.uniqueKeys();
    // for (auto dataset : datasetList)
    // {
    //     auto k = mMeshData->getKernalByID(dataset);
    //     auto vObjs = mViewObjects.value(k);
    //     QList<int> members = mHighLightSelectItems.values();
    //     if (vObjs == nullptr)
    //         continue;
    //     if (_selectModel == ModuleBase::BoxMeshNode || _selectModel == ModuleBase::MeshNode)
    //     {
    //         QColor c = Setting::BusAPI::instance()->getGraphOption()->getMeshNodeColor();
    //         vObjs->setPointDisplayColor(members, c);
    //     }
        
    //     else if (_selectModel == ModuleBase::BoxMeshCell || _selectModel == ModuleBase::MeshCell)
    //     {
    //         QColor c = Setting::BusAPI::instance()->getGraphOption()->getMeshFaceColor();
    //         vObjs->setCellDisplayColor(members, c);
    //     }
        
    //     mHighLightSelectItems.clear();
    // }
    
    mGraphViewWindow->reRender();
}

// void FCMeshViewProvider::updateMeshSetVisibily(MeshData::MeshSet *set)
// {
//     if (set == nullptr)
//         return;
//     MeshData::SetType type = set->getSetType();
//     QList<int> kids = set->getKernals();
//     for (int kid : kids)
//     {
//         auto k = MeshData::MeshData::getInstance()->getKernalByID(kid);
//         if (k == nullptr)
//             continue;
//         QList<int> mids = set->getKernalMembers(kid);
//         if (mids.isEmpty())
//             continue;
//         auto vobj = _viewObjects.value(k);
//         if (vobj == nullptr)
//             continue;
//         if (type == MeshData::Element)
//             vobj->showCells(mids, set->isVisible());
//     }
//     _preWindow->reRender();
// }

// void FCMeshViewProvider::updateMeshSetColor(int setid)
// {
//     auto meshData = FCMeshData::getInstance();
//     auto meshSet = meshData->getMeshSetByID(setid);
//     if (meshSet == nullptr)
//         return;
//     QColor c = meshSet->getColor();
    
//     QList<int> ks = meshSet->getKernals();
//     for (int k : ks)
//     {
//         auto kernal = meshData->getKernalByID(k);
//         if (kernal == nullptr)
//             continue;
//         auto viewObj = mViewObjects.value(kernal);
//         if (viewObj == nullptr)
//             continue;
        
//         QList<int> mem = meshSet->getKernalMembers(k);
//         if (meshSet->getSetType() == MeshData::Element)
//         {
//             viewObj->setCellDisplayColor(mem, c);
//         }
//         else if (meshSet->getSetType() == MeshData::Node)
//         {
//             viewObj->setPointDisplayColor(mem, c);
//         }
//     }
// }

void FCMeshViewProvider::removeDisplay(IdType meshID)
{
    auto viewObj = mMeshViewObjects.value(meshID);
    if (viewObj == nullptr)
        return;
    vtkActor **ac = viewObj->getActor();
    mGraphViewWindow->RemoveActor(ac[POINTACTOR]);
    mGraphViewWindow->RemoveActor(ac[EDGEACTOR]);
    mGraphViewWindow->RemoveActor(ac[FACEACTOR]);
    mMeshViewObjects.remove(meshID);
    delete viewObj;
    mGraphViewWindow->reRender();
}

FCMeshViewObject *FCMeshViewProvider::getViewObjByDisplayDataSet(vtkDataSet *data)
{
    QList<FCMeshViewObject *> kobjs = mMeshViewObjects.values();
    for (auto obj : kobjs)
    {
        auto d = obj->getDisplayData();
        if (d == data)
            return obj;
    }
    return nullptr;
}

void FCMeshViewProvider::updateDisplayModel(IdType meshID /* FCMeshKernal *k = nullptr*/)
{
    QList<FCMeshViewObject *> vobjs;
    FCMeshKernal* k = mMeshData->getMeshKernalByID(meshID);
    if (nullptr == k)
        vobjs = mMeshViewObjects.values();
    else
        vobjs.append(mMeshViewObjects.value(meshID));
    
    // auto gp = Setting::BusAPI::instance()->getGraphOption();
    // 根据 mMeshShouldBeVisible 标志决定是否显示网格
    bool showNode = mMeshShouldBeVisible;// gp->isShowMeshNode();
    bool showEdge = mMeshShouldBeVisible;//gp->isShowMeshEdge();
    bool showFace = mMeshShouldBeVisible;//gp->isShowMeshFace();
    for (auto kobj : vobjs)
    {
        if (nullptr == kobj)
            continue;
        vtkActor **acs = kobj->getActor();
        acs[POINTACTOR]->SetVisibility(showNode ? 1 : 0);
        acs[EDGEACTOR]->SetVisibility(showEdge ? 1 : 0);
        acs[FACEACTOR]->SetVisibility(showFace ? 1 : 0);
        if (showEdge && showFace)
        {
            acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
            QColor edgeColor = QColor(34,88,26);// gp->getMeshEdgeColor();
            acs[EDGEACTOR]->GetProperty()->SetColor(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
        }
        else
            acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
    }
    
    if (k != nullptr)
        showKernal(meshID, k->isVisible() && mMeshShouldBeVisible);
    else
    {
        auto ks = mMeshViewObjects.keys();
        for (auto ck : ks)
            showKernal(ck, k->isVisible() && mMeshShouldBeVisible);
    }
}

void FCMeshViewProvider::setAllMeshVisible(bool visible)
{
    // 记录网格是否应该显示
    mMeshShouldBeVisible = visible;
    
    // 遍历所有网格，设置可见性
    // 当visible为false时，隐藏所有网格（点、线、面）
    // 当visible为true时，显示网格线框（EDGEACTOR），隐藏面和点
    for (auto it = mMeshViewObjects.begin(); it != mMeshViewObjects.end(); ++it) {
        FCMeshViewObject* vobj = it.value();
        if (vobj) {
            vtkActor** actors = vobj->getActor();
            if (actors) {
                if (visible) {
                    // 显示网格时，只显示线框，隐藏面和点
                    actors[0]->SetVisibility(0); // POINTACTOR - 隐藏点
                    actors[1]->SetVisibility(1); // EDGEACTOR - 显示线框
                    actors[2]->SetVisibility(0); // FACEACTOR - 隐藏面
                } else {
                    // 隐藏所有网格 - 强制设置为不可见
                    actors[0]->SetVisibility(0); // POINTACTOR
                    actors[1]->SetVisibility(0); // EDGEACTOR
                    actors[2]->SetVisibility(0); // FACEACTOR
                }
            }
        }
    }
    
    // 如果隐藏网格，确保之后调用updateDisplayModel也不会显示
    // 通过强制重新应用可见性设置来确保
    if (!visible) {
        // 遍历所有网格ID，强制更新显示模型以确保隐藏
        QList<IdType> allIds = mMeshViewObjects.keys();
        for (auto id : allIds) {
            updateDisplayModel(id);
        }
    }
}

void FCMeshViewProvider::updateGraphOption(IdType meshID)
{
    QList<FCMeshViewObject *> vobjs;
    FCMeshKernal* k = mMeshData->getMeshKernalByID(meshID);    
    if (nullptr == k)
        vobjs = mMeshViewObjects.values();
    else
        vobjs.append(mMeshViewObjects.value(meshID));
    
    // auto gp = Setting::BusAPI::instance()->getGraphOption();
    const bool showNode = true;// gp->isShowMeshNode();
    const bool showEdge = true;//gp->isShowMeshEdge();
    const bool showFace = false;//gp->isShowMeshFace();
    const float pointSize = 1.0;//gp->getMeshNodeSize();
    const float lineWidth =  1.5;//gp->getMeshEdgeWidth();
    const QColor pointColor = QColor(38, 38, 38); //gp->getMeshNodeColor();
    const QColor edgeColor = QColor(38, 38, 38); //gp->getMeshEdgeColor();
    const QColor faceColor = QColor(38, 38, 38); //gp->getMeshFaceColor();
    for (auto kobj : vobjs)
    {
        if (nullptr == kobj)
            continue;
        kobj->setPointColor(pointColor);
        kobj->setCellColor(faceColor);
        vtkActor **acs = kobj->getActor();
        acs[POINTACTOR]->GetProperty()->SetPointSize(pointSize);
        acs[EDGEACTOR]->GetProperty()->SetLineWidth(lineWidth);
        if (showEdge && showFace)
        {
            acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(false);
            acs[EDGEACTOR]->GetProperty()->SetColor(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
        }
        else
            acs[EDGEACTOR]->GetMapper()->SetScalarVisibility(true);
    }
    
    // 如果网格不应该显示，确保隐藏所有actor（防止updateGraphOption后网格被显示）
    if (!mMeshShouldBeVisible) {
        for (auto kobj : vobjs) {
            if (nullptr == kobj)
                continue;
            vtkActor **acs = kobj->getActor();
            acs[POINTACTOR]->SetVisibility(0);
            acs[EDGEACTOR]->SetVisibility(0);
            acs[FACEACTOR]->SetVisibility(0);
        }
    }
}

void FCMeshViewProvider::showKernal(IdType meshID, bool show)
{
    FCMeshKernal* k = mMeshData->getMeshKernalByID(meshID);    
    
    if (k == nullptr)
        return;
    auto vobj = mMeshViewObjects.value(meshID, nullptr);
    if (vobj == nullptr)
        return;
    vtkActor **acs = vobj->getActor();
    // 检查网格是否应该显示（考虑 mMeshShouldBeVisible 标志）
    bool shouldShow = show && mMeshShouldBeVisible;
    if (shouldShow)
    {
        // auto gp = Setting::BusAPI::instance()->getGraphOption();
        const bool showNode = true;//gp->isShowMeshNode();
        const bool showEdge = true;//gp->isShowMeshEdge();
        const bool showFace = false;//gp->isShowMeshFace();
        
        acs[POINTACTOR]->SetVisibility(showNode ? 1 : 0);
        acs[EDGEACTOR]->SetVisibility(showEdge ? 1 : 0);
        acs[FACEACTOR]->SetVisibility(showFace ? 1 : 0);
    }
    else
    {
        acs[POINTACTOR]->SetVisibility(0);
        acs[EDGEACTOR]->SetVisibility(0);
        acs[FACEACTOR]->SetVisibility(0);
    }
    mGraphViewWindow->reRender();
}

// void FCMeshViewProvider::setMeshSelectMode(ModuleBase::SelectModel m)
// {
//     clearHighLight();
//     _selectModel = m;
    
//     QList<MeshKernalViewObj *> objs = _viewObjects.values();
//     for (auto vobj : objs)
//     {
//         vtkActor **acs = vobj->getActor();
//         acs[POINTACTOR]->SetPickable(false);
//         acs[EDGEACTOR]->SetPickable(false);
//         acs[FACEACTOR]->SetPickable(false);
        
//         if (m == ModuleBase::MeshNode || m == ModuleBase::BoxMeshNode)
//             acs[POINTACTOR]->SetPickable(true);
//         else if (m == ModuleBase::MeshCell || m == ModuleBase::BoxMeshCell)
//             acs[FACEACTOR]->SetPickable(true);
//     }
// }

// void FCMeshViewProvider::highLighSelectItem(QMultiHash<int, int> *items)
// {
//     if (items->isEmpty())
//         return;
//     mHighLightSelectItems = *items;
//     QColor c = QColor(0, 30, 254);//Setting::BusAPI::instance()->getGraphOption()->getHighLightColor();
//     QList<int> datasetList = items->uniqueKeys();
//     for (auto dataset : datasetList)
//     {
//         auto k = mMeshData->getKernalByID(dataset);
//         auto vObjs = mViewObjects.value(k);
//         QList<int> members = items->values();
//         if (vObjs == nullptr)
//             continue;
//         if (_selectModel == ModuleBase::BoxMeshNode || _selectModel == ModuleBase::MeshNode)
//             vObjs->setPointDisplayColor(members, c);
//         else if (_selectModel == ModuleBase::BoxMeshCell || _selectModel == ModuleBase::MeshCell)
//             vObjs->setCellDisplayColor(members, c);
//     }
//     mGraphViewWindow->reRender();
// }

QMultiHash<int, int> *FCMeshViewProvider::getSelectItem()
{
    return &mHighLightSelectItems;
}

void FCMeshViewProvider::removeMeshActor(IdType meshID)
{
    auto viewObj = mMeshViewObjects.value(meshID);
    if (viewObj == nullptr)
        return;
    vtkActor **ac = viewObj->getActor();
    mGraphViewWindow->RemoveActor(ac[POINTACTOR]);
    mGraphViewWindow->RemoveActor(ac[EDGEACTOR]);
    mGraphViewWindow->RemoveActor(ac[FACEACTOR]);
    mMeshViewObjects.remove(meshID);
    delete viewObj;
    mGraphViewWindow->reRender();
}


} // namespace FC
