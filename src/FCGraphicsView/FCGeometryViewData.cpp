/**
 * @file FCGeometryViewData.cpp
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryViewData.h"
#include "FCGeometrySetViewObject.h"
#include "FCGeometryViewObject.h"
#include "FCGeometrySet.h"
#include <QDebug>
// vtk
#include <vtkPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkCleanPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkTriangle.h>
#include <vtkSmartPointer.h>
#include <vtkPointData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
#include <vtkLine.h>
#include <vtkPolyLine.h>
#include <vtkKdTree.h>
#include <vtkPolyDataWriter.h>
//occ
#include <TopExp.hxx>
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS.hxx>

namespace FC 
{

FCGeometryViewData::~FCGeometryViewData()
{
    QList<FCGeometrySetViewObject *> setViews = mViewObjs.values();
    for (auto v : setViews)
        delete v;
    mViewObjs.clear();
}

QList<vtkPolyData *> FCGeometryViewData::transferToPoly(FCGeometrySet *gset)
{
    removeViewObjs(gset);
    QList<vtkPolyData *> polys;
    auto p = this->transferFace(gset);
    polys.append(p);
    p = this->transferEdge(gset);
    polys.append(p);
    p = this->transferPoint(gset);
    polys.append(p);
    if (mViewObjs.contains(gset))
        mViewObjs.value(gset)->genSolidViewObj();
    return polys;
}

void FCGeometryViewData::removeViewObjs(FCGeometrySet *gset)
{
    if (!mViewObjs.contains(gset))
        return;
    auto obj = mViewObjs.value(gset);
    mViewObjs.remove(gset);
    delete obj;
}

void FCGeometryViewData::updateGraphOption()
{
    QList<FCGeometrySetViewObject *> setViews = mViewObjs.values();
    for (auto setView : setViews)
        setView->resetColor();
}

void FCGeometryViewData::highLight(FCGeometrySet *set, bool on)
{
    auto setView = mViewObjs.value(set);
    if (setView != nullptr)
        setView->highLight(on);
}

void FCGeometryViewData::highLightFace(FCGeometrySet *set, int index, bool on)
{
    auto setView = mViewObjs.value(set);
    if (setView != nullptr)
        setView->highLightFace(index, on);
}

void FCGeometryViewData::highLightEdge(FCGeometrySet *set, int index, bool on)
{
    auto setView = mViewObjs.value(set);
    if (setView != nullptr)
        setView->highLightEdge(index, on);
}

void FCGeometryViewData::highLightPoint(FCGeometrySet *set, int index, bool on)
{
    auto setView = mViewObjs.value(set);
    if (setView != nullptr)
        setView->highLightPoint(index, on);
}

void FCGeometryViewData::highLightSolid(FCGeometrySet *set, int index, bool on)
{
    auto setView = mViewObjs.value(set);
    if (setView != nullptr)
        setView->highLightSolid(index, on);
}

FCGeometryViewObject *FCGeometryViewData::getSolidViewObj(vtkPolyData *solidPoly, int cellIndex)
{
    
    auto face = this->getFaceViewObj(solidPoly, cellIndex);
    if (face == nullptr)
        return nullptr;
    int faceIndex = face->getIndex();
    FCGeometrySetViewObject *sv = face->getGeoSetViewObject();
    if (sv == nullptr || faceIndex < 0)
        return nullptr;
    return sv->getSolidViewObjByFaceIndex(faceIndex);
}

FCGeometryViewObject *FCGeometryViewData::getFaceViewObj(vtkPolyData *facePoly, int cellIndex)
{
    QList<FCGeometrySetViewObject *> setViews = mViewObjs.values();
    FCGeometrySetViewObject *setView = nullptr;
    for (auto view : setViews)
    {
        vtkPolyData *tpoly = view->getFacePoly();
        if (facePoly == tpoly)
        {
            setView = view;
            break;
        }
    }
    if (setView == nullptr)
        return nullptr;
    return setView->getFaceViewObjByCellIndex(cellIndex);
}

FCGeometryViewObject *FCGeometryViewData::getEdgeViewObj(vtkPolyData *edgePoly, int cellIndex)
{
    QList<FCGeometrySetViewObject *> setViews = mViewObjs.values();
    FCGeometrySetViewObject *setView = nullptr;
    for (auto view : setViews)
    {
        vtkPolyData *tpoly = view->getEdgePoly();
        if (edgePoly == tpoly)
        {
            setView = view;
            break;
        }
    }
    if (setView == nullptr)
        return nullptr;
    return setView->getEdgeViewObjByCellIndex(cellIndex);
}

FCGeometryViewObject *FCGeometryViewData::getPointViewObj(vtkPolyData *pointPoly, int pointIndex)
{
    QList<FCGeometrySetViewObject *> setViews = mViewObjs.values();
    FCGeometrySetViewObject *setView = nullptr;
    for (auto view : setViews)
    {
        vtkPolyData *tpoly = view->getPointPoly();
        if (pointPoly == tpoly)
        {
            setView = view;
            break;
        }
    }
    if (setView == nullptr)
        return nullptr;
    return setView->getPointViewObjByCellIndex(pointIndex);
}

QList<FCGeometryViewObject *> FCGeometryViewData::getViewObjectByStates(int selectStates,
                                                                        int states)
{
    QList<FCGeometryViewObject *> objects;
    QList<FCGeometrySetViewObject *> setList = mViewObjs.values();
    for (auto sv : setList)
    {
        if (sv == nullptr)
            continue;
        QList<FCGeometryViewObject *> v = sv->getViewObjectByStates(selectStates, states);
        objects.append(v);
    }
    return objects;
}

void FCGeometryViewData::preHighLight(FCGeometryViewObject *vob)
{
    if (mPreViewObjct != nullptr && mPreViewObjct->getStates() == FCGeometryViewObject::HighLigh)
        mPreViewObjct = nullptr;
    if (vob != nullptr && vob->getStates() == FCGeometryViewObject::HighLigh)
        return;
    if (vob == mPreViewObjct && vob != nullptr)
        return;
    if (mPreViewObjct != nullptr)
        mPreViewObjct->resetColor();
    mPreViewObjct = vob;
    if (mPreViewObjct != nullptr)
        mPreViewObjct->preHighLight();
}

FCGeometryViewObject *FCGeometryViewData::getPreHighLightObj()
{
    return mPreViewObjct;
    
}

vtkPolyData *FCGeometryViewData::transferFace(FCGeometrySet *gset)
{
    TopoDS_Shape *shape = gset->getShape();
    TopExp_Explorer faceExp(*shape, TopAbs_FACE);
    QList<Handle(TopoDS_TShape)> tshapelist;
    
    vtkSmartPointer<vtkAppendPolyData> appendFilter =
        vtkSmartPointer<vtkAppendPolyData>::New();
    vtkPolyData *polyData = vtkPolyData::New();
    int beg = 0;
    for (int index = 0; faceExp.More(); faceExp.Next(), ++index)
    {
        const TopoDS_Shape &s = faceExp.Current();
        Handle(TopoDS_TShape) ts = s.TShape();
        if (tshapelist.contains(ts))
            continue;
        tshapelist.append(ts);
        
        IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(s);
        vtkSmartPointer<IVtkTools_ShapeDataSource> DS =
            vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
        DS->SetShape(aShapeImpl);
        
        vtkSmartPointer<vtkCleanPolyData> cleanFilter =
            vtkSmartPointer<vtkCleanPolyData>::New();
        cleanFilter->SetInputConnection(DS->GetOutputPort());
        cleanFilter->Update();
        vtkSmartPointer<vtkPolyData> tpolys =
            vtkSmartPointer<vtkPolyData>::New();
        vtkPolyData *tpolydata = cleanFilter->GetOutput();
        const int np = tpolydata->GetNumberOfPoints();
        const int nc = tpolydata->GetNumberOfCells();
        vtkPoints *points = vtkPoints::New();
        for (int i = 0; i < np; i++)
        {
            double *coor = tpolydata->GetPoint(i);
            points->InsertNextPoint(coor);
        }
        tpolys->SetPoints(points);
        vtkCellArray *cells = vtkCellArray::New();
        for (int i = 0; i < nc; ++i)
        {
            vtkCell *cell = tpolydata->GetCell(i);
            vtkIdList *ceid = cell->GetPointIds();
            if (ceid->GetNumberOfIds() == 3)
            {
                vtkTriangle *triangle = vtkTriangle::New();
                triangle->DeepCopy(cell);
                cells->InsertNextCell(triangle);
            }
        }
        tpolys->SetPolys(cells);
        
        vtkSmartPointer<vtkPolyDataNormals> normals =
            vtkSmartPointer<vtkPolyDataNormals>::New();
        normals->SetInputData(tpolys);
        normals->FlipNormalsOn();
        normals->Update();
        vtkPolyData *facePoly = normals->GetOutput();
        
        const int ncell = facePoly->GetNumberOfCells();
        if (ncell < 1)
            continue;
        FCGeometryViewObject *obj = new FCGeometryViewObject(FCGeometryViewObject::Face,
                                                             beg, beg + ncell - 1, ts);
        beg += ncell;
        appendFilter->AddInputData(facePoly);
        auto setViewObj = this->getGeosetObj(gset);
        setViewObj->appendFaceViewObj(index, ts, obj);
    }
    
    appendFilter->Update();
    polyData->DeepCopy(appendFilter->GetOutput());
    auto setViewObj = this->getGeosetObj(gset);
    setViewObj->setFacePoly(polyData);
    const int npc = polyData->GetNumberOfCells();
    if (npc < 1)
        return nullptr;
    return polyData;
}

vtkPolyData *FCGeometryViewData::transferEdge(FCGeometrySet *gset)
{
    TopoDS_Shape *shape = gset->getShape();
    
    TopExp_Explorer edgeExp(*shape, TopAbs_EDGE);
    QHash<int, Handle(TopoDS_TShape)> tshapelist;
    QHash<int, vtkPolyData *> indexPoly;
    vtkSmartPointer<vtkAppendPolyData> appendPoly = vtkSmartPointer<vtkAppendPolyData>::New();
    for (int index = 0; edgeExp.More(); edgeExp.Next(), ++index)
    {
        const TopoDS_Shape &s = edgeExp.Current();
        Handle(TopoDS_TShape) ts = s.TShape();
        if (tshapelist.values().contains(ts))
            continue;
        tshapelist.insert(index, ts);
        IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(s);
        vtkSmartPointer<IVtkTools_ShapeDataSource> DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
        DS->SetShape(aShapeImpl);
        DS->Update();
        vtkPolyData *p = DS->GetOutput();
        const int ncell = p->GetNumberOfCells();
        if (ncell < 2)
            continue;
        appendPoly->AddInputData(p);
        indexPoly.insert(index, p);
    }
    vtkSmartPointer<vtkCleanPolyData> cleaner = vtkSmartPointer<vtkCleanPolyData>::New();
    cleaner->SetInputConnection(appendPoly->GetOutputPort());
    cleaner->Update();
    vtkPolyData *tPoly = cleaner->GetOutput();
    vtkPolyData *newPoly = vtkPolyData::New();
    newPoly->DeepCopy(tPoly);
    
    QList<int> lineCell;
    const int ncell = newPoly->GetNumberOfCells();
    for (int i = 0; i < ncell; ++i)
    {
        vtkCell *cell = newPoly->GetCell(i);
        if (cell->GetNumberOfPoints() > 1)
            lineCell.append(i);
    }
    // qDebug() << lineCell;
    
    QList<vtkPolyData *> edges = indexPoly.values();
    for (auto edge : edges)
    {
        const int eindex = indexPoly.key(edge);
        Handle(TopoDS_TShape) ts = tshapelist.value(eindex);
        //			vtkCell* line = this->getLineCellIn(edge);
        int index = getIndexInPoly(edge, newPoly, lineCell);
        if (index < 0)
            continue;
        lineCell.removeOne(index);
        FCGeometryViewObject *obj = new FCGeometryViewObject(FCGeometryViewObject::Edge, index, index, ts);
        auto setViewObj = this->getGeosetObj(gset);
        setViewObj->appendEdgeViewObj(eindex, obj);
    }
    
    auto setViewObj = this->getGeosetObj(gset);
    setViewObj->setEdgePoly(newPoly);
    return newPoly;
    
}

vtkPolyData *FCGeometryViewData::transferPoint(FCGeometrySet *gset)
{
    TopoDS_Shape *shape = gset->getShape();
    TopExp_Explorer ptExp(*shape, TopAbs_VERTEX);
    QList<Handle(TopoDS_TShape)> tshapelist;
    vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    int beg = 0;
    vtkPolyData *polyData = vtkPolyData::New();
    for (int index = 0; ptExp.More(); ptExp.Next(), ++index)
    {
        const TopoDS_Shape &s = ptExp.Current();
        Handle(TopoDS_TShape) ts = s.TShape();
        if (tshapelist.contains(ts))
            continue;
        tshapelist.append(ts);
        IVtkOCC_Shape::Handle aShapeImpl = new IVtkOCC_Shape(s);
        vtkSmartPointer<IVtkTools_ShapeDataSource> DS = vtkSmartPointer<IVtkTools_ShapeDataSource>::New();
        DS->SetShape(aShapeImpl);
        DS->Update();
        vtkPolyData *tpolyData = DS->GetOutput();
        const int np = tpolyData->GetNumberOfPoints();
        if (np < 1)
            continue;
        FCGeometryViewObject *obj = new FCGeometryViewObject(FCGeometryViewObject::Point, beg, beg + np - 1, ts);
        beg += np;
        appendFilter->AddInputData(tpolyData);
        auto setViewObj = this->getGeosetObj(gset);
        setViewObj->appendPointViewObj(index, obj);
    }
    appendFilter->Update();
    polyData->DeepCopy(appendFilter->GetOutput());
    auto setViewObj = this->getGeosetObj(gset);
    setViewObj->setPointPoly(polyData);
    const int npc = polyData->GetNumberOfCells();
    if (npc < 1)
        return nullptr;
    return polyData;
    
}

FCGeometrySetViewObject *FCGeometryViewData::getGeosetObj(FCGeometrySet *set)
{
    if (mViewObjs.contains(set))
        return mViewObjs.value(set);
    auto viewObj = new FCGeometrySetViewObject(set);
    mViewObjs.insert(set, viewObj);
    return viewObj;
}

vtkCell *FCGeometryViewData::getLineCellIn(vtkPolyData *p)
{
    const int n = p->GetNumberOfCells();
    for (int i = 0; i < n; ++i)
    {
        vtkCell *cel = p->GetCell(i);
        const int np = cel->GetNumberOfPoints();
        if (np > 1)
            return cel;
    }
    return nullptr;
    
}

int FCGeometryViewData::getIndexInPoly(vtkPolyData *part, vtkPolyData *poly, QList<int> lineIndexs)
{
    if (part == nullptr || poly == nullptr)
        return -1;
    vtkCell *cell = getLineCellIn(part);
    if (cell == nullptr)
        return -1;
    const int oriCellType = cell->GetCellType();
    const int oriPointCount = cell->GetNumberOfPoints();
    
    vtkSmartPointer<vtkKdTree> kdTree = vtkSmartPointer<vtkKdTree>::New();
    kdTree->BuildLocatorFromPoints(part->GetPoints());
    
    for (int index : lineIndexs)
    {
        vtkCell *currentCell = poly->GetCell(index);
        if (currentCell->GetCellType() != oriCellType)
            continue;
        if (currentCell->GetNumberOfPoints() != oriPointCount)
            continue;
        if (isSameCell(kdTree, currentCell, poly))
            return index;
    }
    return -1;
}

bool FCGeometryViewData::isSameCell(vtkKdTree *tree, vtkCell *cell, vtkPolyData *allPoly)
{
    const int npt = cell->GetNumberOfPoints();
    for (int i = 0; i < npt; ++i)
    {
        int pindex = cell->GetPointId(i);
        double *loc = allPoly->GetPoint(pindex);
        
        int index = tree->FindPoint(loc);
        if (index < 0)
            return false;
        if (i > 8)
            break;
        ;
    }
    return true;
}

} // namespace FC
