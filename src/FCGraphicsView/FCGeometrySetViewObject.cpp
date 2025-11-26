/**
 * @file FCGeometrySetViewObject.cpp
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometrySetViewObject.h"
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

FCGeometrySetViewObject::FCGeometrySetViewObject(FCGeometrySet *set)
    : mGeoSet(set)
{
    
}

FCGeometrySetViewObject::~FCGeometrySetViewObject()
{
    
}

FCGeometrySet *FCGeometrySetViewObject::getGeometrySet()
{
    return mGeoSet;
    
}

void FCGeometrySetViewObject::setFacePoly(vtkPolyData *p)
{

}

vtkPolyData *FCGeometrySetViewObject::getFacePoly()
{
    return mFacePoly;
    
}

void FCGeometrySetViewObject::setEdgePoly(vtkPolyData *p)
{
    
}

vtkPolyData *FCGeometrySetViewObject::getEdgePoly()
{
    return mEdgePoly;    
}

void FCGeometrySetViewObject::setPointPoly(vtkPolyData *p)
{
    
}

vtkPolyData *FCGeometrySetViewObject::getPointPoly()
{
    return mPointPoly;
    
}

void FCGeometrySetViewObject::genSolidViewObj()
{
    
}

void FCGeometrySetViewObject::appendFaceViewObj(int index,
                                                opencascade::handle<TopoDS_TShape> s,
                                                FCGeometryViewObject *v)
{
    
}

void FCGeometrySetViewObject::appendEdgeViewObj(int index, FCGeometryViewObject *v)
{
    
}

void FCGeometrySetViewObject::appendPointViewObj(int index, FCGeometryViewObject *v)
{
    
}

void FCGeometrySetViewObject::appendSolidViewObj(int index, FCGeometryViewObject *v)
{
    
}

FCGeometryViewObject *FCGeometrySetViewObject::getFaceViewObjByIndex(int index)
{
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewObject::getFaceViewObjByCellIndex(int cellIndex)
{
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewObject::getEdgeViewObjByCellIndex(int cellIndex)
{
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewObject::getPointViewObjByCellIndex(int pointIndex)
{
    return nullptr;
    
}

FCGeometryViewObject *FCGeometrySetViewObject::getSolidViewObjByFaceIndex(int faceIndex)
{
    return nullptr;
    
}

QList<FCGeometryViewObject *> FCGeometrySetViewObject::getViewObjectByStates(int selectModel, int sates)
{
    
    QList<FCGeometryViewObject *> temp;    
    return temp;
    
}

void FCGeometrySetViewObject::resetColor()
{
    
}

void FCGeometrySetViewObject::highLight(bool on)
{
    
}

void FCGeometrySetViewObject::highLightFace(int index, bool on)
{
    
}

void FCGeometrySetViewObject::highLightEdge(int index, bool on)
{
    
}

void FCGeometrySetViewObject::highLightPoint(int index, bool on)
{
    
}

void FCGeometrySetViewObject::highLightSolid(int index, bool on)
{
    
}

} // namespace FC
