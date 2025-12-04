/**
 * @file FCGeometryViewData.cpp
 * @brief 几何对象可视化管理类
 * @date 2025-11-26
 * @version V0.0.1
 * @details 管理所有的可视化对象
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#include "FCGeometryViewData.h"
#include "FCGeometrySetViewData.h"
#include "FCGeometryViewObject.h"
#include "FCGeometrySet.h"
#include "FCGeometryData.h"
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

/**
 * @brief 析构函数
 * @note 手动释放没有被qt对象树管理的对象实例
 */
FCGeometryViewData::~FCGeometryViewData()
{
    QList<FCGeometrySetViewData *> setViews = mViewObjs.values();
    for (auto v : setViews)
        delete v;
    mViewObjs.clear();
}

/**
 * @brief occt topo_ds转换成vtkPolyData
 * @param gset occt topo_ds以及对应的参数
 * @return 
 */
QList<vtkPolyData *> FCGeometryViewData::transferToPoly(const IdType id)
{
    removeViewObjs(id);  // 删除旧的 View 数据
    QList<vtkPolyData *> polys;
    auto p = this->transferFace(id);
    polys.append(p);
    p = this->transferEdge(id);
    polys.append(p);
    p = this->transferPoint(id);
    polys.append(p);
    if (mViewObjs.contains(id))
        mViewObjs.value(id)->genSolidViewObj();
    return polys;
}

/**
 * @brief 移除可视化对象
 * @param id
 */
void FCGeometryViewData::removeViewObjs(const IdType id)
{
    if (!mViewObjs.contains(id))
        return;
    auto obj = mViewObjs.value(id);
    mViewObjs.remove(id);
    delete obj;
}

/**
 * @brief 更新显示配置
 * @note 主要是更新颜色
 */
void FCGeometryViewData::updateGraphOption()
{
    QList<FCGeometrySetViewData *> setViews = mViewObjs.values();
    for (auto setView : setViews)
        setView->resetColor();
}

/**
 * @brief 高亮显示
 * @param set
 * @param on
 */
void FCGeometryViewData::highLight(const IdType id, bool on)
{
    auto setView = mViewObjs.value(id);
    if (setView != nullptr)
        setView->highLight(on);
}

/**
 * @brief 高亮显示面
 * @param set
 * @param index
 * @param on
 */
void FCGeometryViewData::highLightFace(const IdType id, int index, bool on)
{
    auto setView = mViewObjs.value(id);
    if (setView != nullptr)
        setView->highLightFace(index, on);
}

/**
 * @brief 高亮显示边
 * @param set
 * @param index
 * @param on
 */
void FCGeometryViewData::highLightEdge(const IdType id, int index, bool on)
{
    auto setView = mViewObjs.value(id);
    if (setView != nullptr)
        setView->highLightEdge(index, on);
}

/**
 * @brief 高亮显示点
 * @param set
 * @param index
 * @param on
 */
void FCGeometryViewData::highLightPoint(const IdType id, int index, bool on)
{
    auto setView = mViewObjs.value(id);
    if (setView != nullptr)
        setView->highLightPoint(index, on);
}

/**
 * @brief 高亮显示实体
 * @param set
 * @param index
 * @param on
 */
void FCGeometryViewData::highLightSolid(const IdType id, int index, bool on)
{
    auto setView = mViewObjs.value(id);
    if (setView != nullptr)
        setView->highLightSolid(index, on);
}

/**
 * @brief 获取实体的可视化对象
 * @param solidPoly
 * @param cellIndex
 * @return 
 */
FCGeometryViewObject *FCGeometryViewData::getSolidViewObj(vtkPolyData *solidPoly, int cellIndex)
{
    
    auto face = this->getFaceViewObj(solidPoly, cellIndex);
    if (face == nullptr)
        return nullptr;
    int faceIndex = face->getIndex();
    FCGeometrySetViewData *sv = face->getGeoSetViewObject();
    if (sv == nullptr || faceIndex < 0)
        return nullptr;
    return sv->getSolidViewObjByFaceIndex(faceIndex);
}

/**
 * @brief 获取面的可视化对象
 * @param facePoly
 * @param cellIndex
 * @return 
 */
FCGeometryViewObject *FCGeometryViewData::getFaceViewObj(vtkPolyData *facePoly, int cellIndex)
{
    QList<FCGeometrySetViewData *> setViews = mViewObjs.values();
    FCGeometrySetViewData *setView = nullptr;
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

/**
 * @brief 获取边的可视化对象
 * @param edgePoly
 * @param cellIndex
 * @return 
 */
FCGeometryViewObject *FCGeometryViewData::getEdgeViewObj(vtkPolyData *edgePoly, int cellIndex)
{
    QList<FCGeometrySetViewData *> setViews = mViewObjs.values();
    FCGeometrySetViewData *setView = nullptr;
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

/**
 * @brief 获取点的可视化对象
 * @param pointPoly
 * @param pointIndex
 * @return 
 */
FCGeometryViewObject *FCGeometryViewData::getPointViewObj(vtkPolyData *pointPoly, int pointIndex)
{
    QList<FCGeometrySetViewData *> setViews = mViewObjs.values();
    FCGeometrySetViewData *setView = nullptr;
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

/**
 * @brief 获取某个(选中状态)的所有可视化对象
 * @param selectStates
 * @param states
 * @return 
 */
QList<FCGeometryViewObject *> FCGeometryViewData::getViewObjectByStates(int selectStates,
                                                                        int states)
{
    QList<FCGeometryViewObject *> objects;
    QList<FCGeometrySetViewData *> setList = mViewObjs.values();
    for (auto sv : setList)
    {
        if (sv == nullptr)
            continue;
        QList<FCGeometryViewObject *> v = sv->getViewObjectByStates(selectStates, states);
        objects.append(v);
    }
    return objects;
}

/**
 * @brief 悬停高亮
 * @param vob
 */
void FCGeometryViewData::preHighLight(FCGeometryViewObject *vob)
{
    if (mViewObject != nullptr && mViewObject->getStates() == FCGeometryViewObject::HighLigh)
        mViewObject = nullptr;
    if (vob != nullptr && vob->getStates() == FCGeometryViewObject::HighLigh)
        return;
    if (vob == mViewObject && vob != nullptr)
        return;
    if (mViewObject != nullptr)
        mViewObject->resetColor();
    mViewObject = vob;
    if (mViewObject != nullptr)
        mViewObject->preHighLight();
}

/**
 * @brief 获取悬停高新的对象
 * @return 
 */
FCGeometryViewObject *FCGeometryViewData::getPreHighLightObj()
{
    return mViewObject;
    
}

/**
 * @brief 转换成面
 * @param gset
 * @return 
 */
vtkPolyData *FCGeometryViewData::transferFace(const IdType id)
{
    FCGeometrySet* gset  = FCGeometryData::getInstance()->getGeometrySetByID(id);
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
        auto setViewObj = this->getGeosetObj(id);
        setViewObj->appendFaceViewObj(index, ts, obj);
    }
    
    appendFilter->Update();
    polyData->DeepCopy(appendFilter->GetOutput());
    auto setViewObj = this->getGeosetObj(id);
    setViewObj->setFacePoly(polyData);
    const int npc = polyData->GetNumberOfCells();
    if (npc < 1)
        return nullptr;
    return polyData;
}

/**
 * @brief 转换成边
 * @param gset
 * @return 
 */
vtkPolyData *FCGeometryViewData::transferEdge(const IdType id)
{
    FCGeometrySet* gset  = FCGeometryData::getInstance()->getGeometrySetByID(id);    
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
        auto setViewObj = this->getGeosetObj(id);
        setViewObj->appendEdgeViewObj(eindex, obj);
    }
    
    auto setViewObj = this->getGeosetObj(id);
    setViewObj->setEdgePoly(newPoly);
    return newPoly;
    
}

/**
 * @brief 转换成点
 * @param gset
 * @return 
 */
vtkPolyData *FCGeometryViewData::transferPoint(const IdType id)
{
    FCGeometrySet* gset  = FCGeometryData::getInstance()->getGeometrySetByID(id);    
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
        auto setViewObj = this->getGeosetObj(id);
        setViewObj->appendPointViewObj(index, obj);
    }
    appendFilter->Update();
    polyData->DeepCopy(appendFilter->GetOutput());
    auto setViewObj = this->getGeosetObj(id);
    setViewObj->setPointPoly(polyData);
    const int npc = polyData->GetNumberOfCells();
    if (npc < 1)
        return nullptr;
    return polyData;
    
}

/**
 * @brief 获取几何模型的可视化对象
 * @param set
 * @return set几何模型对应的可视化对象
 * @note 如果第一次创建的模型会插入mViewObjs中统一管理
 */
FCGeometrySetViewData *FCGeometryViewData::getGeosetObj(const IdType id)
{
    if (mViewObjs.contains(id))
        return mViewObjs.value(id);
    auto viewObj = new FCGeometrySetViewData(id);
    mViewObjs.insert(id, viewObj);
    return viewObj;
}

/**
 * @brief 获取线的vtk cell
 * @param p
 * @return 
 */
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

/**
 * @brief FCGeometryViewData::getIndexInPoly
 * @param part
 * @param poly
 * @param lineIndexs
 * @return 
 */
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

/**
 * @brief 判断是否为同一个cell
 * @param tree
 * @param cell
 * @param allPoly
 * @return 
 */
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
