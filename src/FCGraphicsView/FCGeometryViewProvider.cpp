/**
 * @file FCGeometryViewProvider.cpp
 * @brief 几何模型可视化管理器
 * @date 2025-11-26
 * @version V0.0.1
 * @details 功能：FCGeometryViewProvider 是几何模块的「可视化管理器」，
 * 负责把 OCCT 的几何对象（FCGeometrySet）转换为 VTK Actor 并管理其
 * 显示、隐藏、选中、高亮等图形状态。 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryViewProvider.h"
#include "FCGeometryData.h"
#include "FCGeometryDatum.h"
#include "FCGeometrySet.h"
#include "FCGeometryViewObject.h"
#include "FCGeometryViewData.h"
#include "FCGraphViewWindow.h"

#include <QColor>
#include <QList>
#include <QDebug>
#include <QMenu>

// vtk
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkCleanPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkGenericCell.h>
#include <vtkPolyLine.h>
#include <vtkPolyVertex.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkVertex.h>
#include <vtkCellData.h>
#include <vtkFloatArray.h>
#include <vtkPlane.h>
#include <vtkMath.h>
#include <vtkSelectEnclosedPoints.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkIdTypeArray.h>
#include <vtkRemoveDuplicatePolys.h>
#include <vtkTriangle.h>
// occt
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Iterator.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <IVtkOCC_ShapeMesher.hxx>
#include <TopExp.hxx>

namespace FC 
{

FCGeometryViewProvider::FCGeometryViewProvider(FCGraphViewWindow* viewWindow, QObject *parent)
    :mGraphViewWindow(viewWindow) , QObject(viewWindow)
{
    mGeoData = FCGeometryData::getInstance();
    
    mViewData = new FCGeometryViewData;
    this->init();
    
}

FCGeometryViewProvider::~FCGeometryViewProvider()
{
    // 手动管理没有继承qt类的对象
    if (mViewData != nullptr)
        delete mViewData;
}

void FCGeometryViewProvider::updateGeoActors()
{
    
}

void FCGeometryViewProvider::updateGraphOption()
{
}

void FCGeometryViewProvider::updateDiaplayStates(FCGeometrySet *s, bool visibility)
{
    
}

QMultiHash<FCGeometrySet *, int> FCGeometryViewProvider::getGeoSelectItems()
{
    // SelectModel mod = _preWindow->getSelectModel();
    // QList<FCGeometryViewObject *> views = _viewData->getViewObjectByStates((int)mod, (int)GeometryViewObject::HighLigh);
    QMultiHash<FCGeometrySet *, int> setHash{};
    // for (auto vs : views)
    // {
    //     auto set = vs->getGeometySet();
    //     int index = vs->getIndex();
    //     setHash.insert(set, index);
    // }
    return setHash;
}

/**
 * @brief 显示几何模型
 * @param set
 * @param render
 */
void FCGeometryViewProvider::showGeoSet(FCGeometrySet *set, bool render)
{
    // todo 
    removeAllActors();
    QList<vtkPolyData *> viewPolys = mViewData->transferToPoly(set);
    vtkPolyData *facePoly = viewPolys.at(0);
    vtkPolyData *edgePoly = viewPolys.at(1);
    vtkPolyData *pointPoly = viewPolys.at(2);
    GeoViewObj viewObj;
    if (facePoly != nullptr)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(facePoly);
        actor->SetMapper(mapper);
        bool vis = set->isVisible();
        bool show = true;// Setting::BusAPI::instance()->getGraphOption()->isShowGeoSurface();
        actor->SetVisibility(show && vis);
        actor->SetPickable(false);
        actor->GetProperty()->SetRepresentationToSurface();
        mGraphViewWindow->AppendActor(actor, D3, false);
        viewObj.mFaceObj = QPair<vtkActor *, vtkPolyData *>(actor, facePoly);
    }
    if (edgePoly != nullptr)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(edgePoly);
        actor->SetMapper(mapper);
        bool vis = set->isVisible();
        bool show = true;// Setting::BusAPI::instance()->getGraphOption()->isShowGeoEdge();
        actor->SetVisibility(show && vis);
        actor->SetPickable(false);
        actor->GetProperty()->SetRepresentationToWireframe();
        //			actor->GetProperty()->EdgeVisibilityOn();
        float width =  2;//Setting::BusAPI::instance()->getGraphOption()->getGeoCurveWidth();
        actor->GetProperty()->SetLineWidth(width);
        mGraphViewWindow->AppendActor(actor, D3, false);
        viewObj.mEdgeObj = QPair<vtkActor *, vtkPolyData *>(actor, edgePoly);
    }
    if (pointPoly != nullptr)
    {
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        float size = 2.0;// Setting::BusAPI::instance()->getGraphOption()->getGeoPointSize();
        mapper->SetInputData(pointPoly);
        actor->SetMapper(mapper);
        bool vis = set->isVisible();
        bool show = true; //Setting::BusAPI::instance()->getGraphOption()->isShowGeoPoint();
        actor->SetVisibility(show && vis);
        actor->SetPickable(false);
        actor->GetProperty()->SetRepresentationToPoints();
        actor->GetProperty()->SetPointSize(size);
        mGraphViewWindow->AppendActor(actor, D3, false);
        viewObj.mPointObj = QPair<vtkActor *, vtkPolyData *>(actor, pointPoly);
    }
    mGeoViewHash.insert(set, viewObj);
    if (render)
        mGraphViewWindow->resetCamera();
    
    qDebug() << "FCGeometryViewProvider::showGeoSet--OK";
}

void FCGeometryViewProvider::showDatum(FCGeometrySet *datm)
{
    Q_UNUSED(datm)
    
}

/**
 * @brief 从vtk渲染窗口中移除指定的几何actor
 * @param set
 */
void FCGeometryViewProvider::removeActors(FCGeometrySet *set)
{
    if (!mGeoViewHash.contains(set))
        return;
    GeoViewObj views = mGeoViewHash.value(set);
    mGeoViewHash.remove(set);
    vtkActor *ac = views.mFaceObj.first;
    mGraphViewWindow->RemoveActor(ac);
    ac = views.mEdgeObj.first;
    mGraphViewWindow->RemoveActor(ac);
    ac = views.mPointObj.first;
    mGraphViewWindow->RemoveActor(ac);
    mGraphViewWindow->reRender();
    mViewData->removeViewObjs(set);
}

void FCGeometryViewProvider::setGeometryDisplay(bool v, bool c, bool f)
{
    
}

void FCGeometryViewProvider::setGeoSelectMode(int)
{
    
}

void FCGeometryViewProvider::highLightGeometrySet(FCGeometrySet *s, bool on)
{
    
}

void FCGeometryViewProvider::highLightGeometryFace(FCGeometrySet *s, int id, bool on)
{
    
}

void FCGeometryViewProvider::highLightGeometryEdge(FCGeometrySet *s, int id, bool on)
{
    
}

void FCGeometryViewProvider::highLightGeometryPoint(FCGeometrySet *s, int id, bool on)
{
    
}

void FCGeometryViewProvider::highLightGeometrySolid(FCGeometrySet *s, int id, bool on)
{
    
}

void FCGeometryViewProvider::selectGeometry(bool ctrlpress)
{
    
}

void FCGeometryViewProvider::selectGeometry(bool pre, vtkActor *ac, int index)
{
    
}

void FCGeometryViewProvider::clearAllHighLight()
{
    
}

void FCGeometryViewProvider::init()
{
    const int n = mGeoData->getGeometrySetCount();
    for (int i = 0; i < n; ++i)
    {
        FCGeometrySet *set = mGeoData->getGeometrySetAt(i);
        TopoDS_Shape *shape = set->getShape();
        if (shape == nullptr)
            continue;
        showGeoSet(set, false);
    }
    mGraphViewWindow->resetCamera();
    QList<FCGeometryDatum *> dl = mGeoData->getGeometryDatum();
    for (auto da : dl)
    {
        TopoDS_Shape *shape = da->getShape();
        if (shape == nullptr)
            continue;
        showDatum(da);
    }
}

void FCGeometryViewProvider::removeAllActors()
{
    // 遍历 mGeoViewHash 中的所有 GeoViewObj
    for (auto it = mGeoViewHash.begin(); it != mGeoViewHash.end(); ++it)
    {
        GeoViewObj views = it.value();
        
        // 移除 Face Actor
        if (views.mFaceObj.first != nullptr)
        {
            mGraphViewWindow->RemoveActor(views.mFaceObj.first);
        }
        
        // 移除 Edge Actor
        if (views.mEdgeObj.first != nullptr)
        {
            mGraphViewWindow->RemoveActor(views.mEdgeObj.first);
        }
        
        // 移除 Point Actor
        if (views.mPointObj.first != nullptr)
        {
            mGraphViewWindow->RemoveActor(views.mPointObj.first);
        }
        
        // 删除对应的 ViewData
        mViewData->removeViewObjs(it.key());
    }
    
    // 清空 Hash
    mGeoViewHash.clear();
    
    // 触发重新渲染
    mGraphViewWindow->reRender();
    
    qDebug() << "FCGeometryViewProvider::removeAllActors -- All actors removed";
}

} // namespace FC
