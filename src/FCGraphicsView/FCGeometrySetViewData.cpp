/**
 * @file FCGeometrySetViewData.cpp
 * @brief 几何集合可视化对象
 * @date 2025-11-26
 * @version V0.0.1
 * @details 管理一个几何集合模型的基础图元(点、线、面、体）
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometrySetViewData.h"
#include "FCGeometrySet.h"
#include "FCGeometryViewObject.h"
#include "FCGeometryData.h"
#include <QDebug>
//vtk
#include <vtkPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkTriangle.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
// occ
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>

namespace FC 
{

FCGeometrySetViewData::FCGeometrySetViewData(const IdType id)
{
    mGeoSet = FCGeometryData::getInstance()->getGeometrySetByID(id);
}

/**
 * @brief 析构函数
 * @note 手动释放非qt树上的对象实例
 */
FCGeometrySetViewData::~FCGeometrySetViewData()
{
    
    if (nullptr != mFacePoly)
        mFacePoly->Delete();
    if (nullptr != mEdgePoly)
        mEdgePoly->Delete();
    if (nullptr != mPointPoly)
        mPointPoly->Delete();
    
    QList<FCGeometryViewObject *> vs = mPointViewObjs.values();
    vs.append(mEdgeViewObjs.values());
    vs.append(mFaceViewObjs.values());
    vs.append(mSolidViewObjs.values());
    
    for (auto v : vs)
        delete v;
    mPointViewObjs.clear();
    mEdgeViewObjs.clear();
    mFaceViewObjs.clear();
    mSolidViewObjs.clear();
    mFaceObjHash.clear();
}

/**
 * @brief 获取几何模型set
 * @return 
 */
FCGeometrySet *FCGeometrySetViewData::getGeometrySet()
{
    return mGeoSet;
}

/**
 * @brief FCGeometrySetViewData::setFacePoly
 * @param p
 */
void FCGeometrySetViewData::setFacePoly(vtkPolyData *p)
{
    mFacePoly = p;
    // todo
    QColor color = QColor(255,255,255,255);// = Setting::BusAPI::instance()->getGraphOption()->getGeometrySurfaceColor();
    unsigned char colorc[3] = {color.red(), color.green(), color.blue()};
    vtkSmartPointer<vtkUnsignedCharArray> cellcolor = vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellcolor->SetNumberOfComponents(3);
    const int n = mFacePoly->GetNumberOfCells();
    for (int i = 0; i < n; ++i)
        cellcolor->InsertNextTypedTuple(colorc);
    mFacePoly->GetCellData()->SetScalars(cellcolor);
    QList<FCGeometryViewObject *> objs = mFaceViewObjs.values();
    for (auto obj : objs)
        obj->setConnectionData(mFacePoly, this);
}

vtkPolyData *FCGeometrySetViewData::getFacePoly()
{
    return mFacePoly;
    
}

void FCGeometrySetViewData::setEdgePoly(vtkPolyData *p)
{
    mEdgePoly = p;
    QColor color = QColor(0,128,128,255);// = Setting::BusAPI::instance()->getGraphOption()->getGeometryCurveColor();
    unsigned char colorc[3] = {color.red(), color.green(), color.blue()};
    vtkSmartPointer<vtkUnsignedCharArray> cellcolor = vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellcolor->SetNumberOfComponents(3);
    const int n = mEdgePoly->GetNumberOfCells();
    for (int i = 0; i < n; ++i)
        cellcolor->InsertNextTypedTuple(colorc);
    mEdgePoly->GetCellData()->SetScalars(cellcolor);
    QList<FCGeometryViewObject *> objs = mEdgeViewObjs.values();
    for (auto obj : objs)
        obj->setConnectionData(mEdgePoly, this);
}

vtkPolyData *FCGeometrySetViewData::getEdgePoly()
{
    return mEdgePoly;    
}

void FCGeometrySetViewData::setPointPoly(vtkPolyData *p)
{
    mPointPoly = p;
    vtkSmartPointer<vtkUnsignedCharArray> cellcolor = vtkSmartPointer<vtkUnsignedCharArray>::New();
    cellcolor->SetNumberOfComponents(3);
    const int n = mPointPoly->GetNumberOfPoints();
    QColor color = QColor(128,0,128,255);// = Setting::BusAPI::instance()->getGraphOption()->getGeometryPointColor();
    unsigned char colorc[3] = {color.red(), color.green(), color.blue()};
    for (int i = 0; i < n; ++i)
        cellcolor->InsertNextTypedTuple(colorc);
    mPointPoly->GetPointData()->SetScalars(cellcolor);
    QList<FCGeometryViewObject *> objs = mPointViewObjs.values();
    for (auto obj : objs)
        obj->setConnectionData(mPointPoly, this);
}

vtkPolyData *FCGeometrySetViewData::getPointPoly()
{
    return mPointPoly;
    
}

void FCGeometrySetViewData::genSolidViewObj()
{
    TopoDS_Shape *shape = mGeoSet->getShape();
    TopExp_Explorer solidExp(*shape, TopAbs_SOLID);
    for (int index = 0; solidExp.More(); solidExp.Next(), ++index)
    {
        const TopoDS_Shape &asolid = solidExp.Current();
        FCGeometryViewObject *solidView = new FCGeometryViewObject(FCGeometryViewObject::Solid,
                                                                   0, 0, asolid.TShape());
        TopExp_Explorer faceExp(asolid, TopAbs_FACE);
        for (; faceExp.More(); faceExp.Next())
        {
            Handle(TopoDS_TShape) tshape = faceExp.Current().TShape();
            auto faceObj = mFaceObjHash.key(tshape);
            if (faceObj == nullptr)
                continue;
            int faceindex = mFaceViewObjs.key(faceObj);
            if (faceindex < 0)
                continue;
            solidView->appendSolidFace(faceindex);
        }
        mSolidViewObjs.insert(index, solidView);
        solidView->setIndex(index);
        solidView->setConnectionData(nullptr, this);
    }
}

void FCGeometrySetViewData::appendFaceViewObj(int index,
                                                opencascade::handle<TopoDS_TShape> s,
                                                FCGeometryViewObject *v)
{
    mFaceObjHash.insert(v, s);
    mFaceViewObjs.insert(index, v);
    v->setIndex(index);
}

void FCGeometrySetViewData::appendEdgeViewObj(int index, FCGeometryViewObject *v)
{
    mEdgeViewObjs.insert(index, v);
    v->setIndex(index);
}

void FCGeometrySetViewData::appendPointViewObj(int index, FCGeometryViewObject *v)
{
    mPointViewObjs.insert(index, v);
    v->setIndex(index);
}

void FCGeometrySetViewData::appendSolidViewObj(int index, FCGeometryViewObject *v)
{
    mSolidViewObjs.insert(index, v);
    v->setIndex(index);
}

FCGeometryViewObject *FCGeometrySetViewData::getFaceViewObjByIndex(int index)
{
    if (mFaceViewObjs.contains(index))
        return mFaceViewObjs.value(index);
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewData::getFaceViewObjByCellIndex(int cellIndex)
{
    QList<FCGeometryViewObject *> viewObjs = mFaceViewObjs.values();
    for (auto view : viewObjs)
    {
        int beg = -1, end = -1;
        view->getRange(beg, end);
        if (cellIndex >= beg && cellIndex <= end)
            return view;
    }
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewData::getEdgeViewObjByCellIndex(int cellIndex)
{
    QList<FCGeometryViewObject *> viewObjs = mEdgeViewObjs.values();
    for (auto view : viewObjs)
    {
        int beg = -1, end = -1;
        view->getRange(beg, end);
        if (cellIndex >= beg && cellIndex <= end)
            return view;
    }
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewData::getPointViewObjByCellIndex(int pointIndex)
{
    QList<FCGeometryViewObject *> viewObjs = mPointViewObjs.values();
    for (auto view : viewObjs)
    {
        int beg = -1, end = -1;
        view->getRange(beg, end);
        if (pointIndex >= beg && pointIndex <= end)
            return view;
    }
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewData::getSolidViewObjByFaceIndex(int faceIndex)
{
    QList<FCGeometryViewObject *> viewObjs = mSolidViewObjs.values();
    for (auto view : viewObjs)
    {
        QList<int> faces = view->getSolidFace();
        if (faces.contains(faceIndex))
            return view;
    }
    return nullptr;
    
}

QList<FCGeometryViewObject *> FCGeometrySetViewData::getViewObjectByStates(int selectModel, int sates)
{
    
    SelectModel m = (SelectModel)selectModel;
    // GeometryViewObject::ViewStates  s = (GeometryViewObject::ViewStates)sates;
    QList<FCGeometryViewObject *> objects;
    switch (m)
    {
    case GeometryWinBody:
    case GeometryBody:
        objects = mSolidViewObjs.values();
        break;
    case GeometryWinSurface:
    case GeometrySurface:
        objects = mFaceViewObjs.values();
        break;
    case GeometryWinCurve:
    case GeometryCurve:
        objects = mEdgeViewObjs.values();
        break;
    case GeometryWinPoint:
    case GeometryPoint:
        objects = mPointViewObjs.values();
        break;
    default:
        break;
    }
    QList<FCGeometryViewObject *> viewObjs;
    for (auto v : objects)
        if (v->getStates() == sates)
            viewObjs.append(v);
    
    return viewObjs;
    
}

void FCGeometrySetViewData::resetColor()
{
    QList<FCGeometryViewObject *> viewObjs = mFaceViewObjs.values();
    for (auto v : viewObjs)
        v->resetColor();
    viewObjs = mEdgeViewObjs.values();
    for (auto v : viewObjs)
        v->resetColor();
    viewObjs = mPointViewObjs.values();
    for (auto v : viewObjs)
        v->resetColor();
    viewObjs = mSolidViewObjs.values();
    for (auto v : viewObjs)
        v->setStates(FCGeometryViewObject::Normal);
}

void FCGeometrySetViewData::highLight(bool on)
{
    if (!on)
    {
        this->resetColor();
        return;
    }
    QList<FCGeometryViewObject *> viewObjs = mFaceViewObjs.values();
    for (auto v : viewObjs)
        v->highLight();
    viewObjs = mEdgeViewObjs.values();
    for (auto v : viewObjs)
        v->highLight();
    viewObjs = mPointViewObjs.values();
    for (auto v : viewObjs)
        v->highLight();
    viewObjs = mSolidViewObjs.values();
    for (auto v : viewObjs)
        v->setStates(FCGeometryViewObject::HighLigh);
}

void FCGeometrySetViewData::highLightFace(int index, bool on)
{
    auto v = mFaceViewObjs.value(index);
    if (nullptr == v)
        return;
    if (on)
        v->highLight();
    else
        v->resetColor();
}

void FCGeometrySetViewData::highLightEdge(int index, bool on)
{
    auto v = mEdgeViewObjs.value(index);
    if (nullptr == v)
        return;
    if (on)
        v->highLight();
    else
        v->resetColor();
}

void FCGeometrySetViewData::highLightPoint(int index, bool on)
{
    auto v = mPointViewObjs.value(index);
    if (nullptr == v)
        return;
    if (on)
        v->highLight();
    else
        v->resetColor();
}

void FCGeometrySetViewData::highLightSolid(int index, bool on)
{
    auto v = mSolidViewObjs.value(index);
    if (nullptr == v)
        return;
    if (on)
        v->highLight();
    else
        v->resetColor();
}

} // namespace FC
