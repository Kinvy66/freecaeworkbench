/**
 * @file FCGeometryViewData.h
 * @brief 几何对象可视化管理类
 * @date 2025-11-26
 * @version V0.0.1
 * @details 管理所有的可视化对象
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYVIEWDATA_H
#define FCGEOMETRYVIEWDATA_H

#include "FCGraphicsViewGlobal.h"

class vtkPolyData;
class TopoDS_TShape;
class QColor;
class vtkPoints;
class vtkCell;
class vtkCellArray;
class vtkKdTree;

namespace FC 
{

class FCGeometryViewObject;
class FCGeometryData;
class FCGeometrySet;
class FCGeometrySetViewData;

class FCGRAPHICSVIEW_API FCGeometryViewData
{
public:
    using IdType  = uint64_t;  ///< id类型   
public:
    FCGeometryViewData() = default;
    ~FCGeometryViewData();
    
    QList<vtkPolyData *> transferToPoly(const IdType id);
    void removeViewObjs(const IdType id);
    
    void updateGraphOption();
    void highLight(const IdType id, bool on);
    void highLightFace(const IdType id, int index, bool on);
    void highLightEdge(const IdType id, int index, bool on);
    void highLightPoint(const IdType id, int index, bool on);
    void highLightSolid(const IdType id, int index, bool on);
    
    FCGeometryViewObject *getSolidViewObj(vtkPolyData *solidPoly, int cellIndex);
    FCGeometryViewObject *getFaceViewObj(vtkPolyData *facePoly, int cellIndex);
    FCGeometryViewObject *getEdgeViewObj(vtkPolyData *edgePoly, int cellIndex);
    FCGeometryViewObject *getPointViewObj(vtkPolyData *pointPoly, int pointIndex);
    
    QList<FCGeometryViewObject *> getViewObjectByStates(int selectStates, int states);
    
    void preHighLight(FCGeometryViewObject *vob);
    FCGeometryViewObject *getPreHighLightObj();
    
private:
    vtkPolyData *transferFace(const IdType id);
    vtkPolyData *transferEdge(const IdType id);
    vtkPolyData *transferPoint(const IdType id);
    FCGeometrySetViewData *getGeosetObj(const IdType id);
    
    vtkCell *getLineCellIn(vtkPolyData *p);
    int getIndexInPoly(vtkPolyData *part, vtkPolyData *poly, QList<int> lineIndexs);
    bool isSameCell(vtkKdTree *tree, vtkCell *cell, vtkPolyData *allPoly);
    
private:
    FCGeometryViewObject *mViewObject{};
    QHash<IdType, FCGeometrySetViewData *> mViewObjs{};
};
} // namespace FC

#endif // FCGEOMETRYVIEWDATA_H
