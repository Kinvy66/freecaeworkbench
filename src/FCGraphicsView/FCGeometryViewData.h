/**
 * @file FCGeometryViewData.h
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
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
class FCGeometrySetViewObject;

class FCGRAPHICSVIEW_API FCGeometryViewData
{
public:
    FCGeometryViewData() = default;
    ~FCGeometryViewData();
    
    QList<vtkPolyData *> transferToPoly(FCGeometrySet *gset);
    void removeViewObjs(FCGeometrySet *gset);
    
    void updateGraphOption();
    void highLight(FCGeometrySet *set, bool on);
    void highLightFace(FCGeometrySet *set, int index, bool on);
    void highLightEdge(FCGeometrySet *set, int index, bool on);
    void highLightPoint(FCGeometrySet *set, int index, bool on);
    void highLightSolid(FCGeometrySet *set, int index, bool on);
    
    FCGeometryViewObject *getSolidViewObj(vtkPolyData *solidPoly, int cellIndex);
    FCGeometryViewObject *getFaceViewObj(vtkPolyData *facePoly, int cellIndex);
    FCGeometryViewObject *getEdgeViewObj(vtkPolyData *edgePoly, int cellIndex);
    FCGeometryViewObject *getPointViewObj(vtkPolyData *pointPoly, int pointIndex);
    
    QList<FCGeometryViewObject *> getViewObjectByStates(int selectStates, int states);
    
    void preHighLight(FCGeometryViewObject *vob);
    FCGeometryViewObject *getPreHighLightObj();
    
private:
    vtkPolyData *transferFace(FCGeometrySet *gset);
    vtkPolyData *transferEdge(FCGeometrySet *gset);
    vtkPolyData *transferPoint(FCGeometrySet *gset);
    FCGeometrySetViewObject *getGeosetObj(FCGeometrySet *set);
    
    vtkCell *getLineCellIn(vtkPolyData *p);
    int getIndexInPoly(vtkPolyData *part, vtkPolyData *poly, QList<int> lineIndexs);
    bool isSameCell(vtkKdTree *tree, vtkCell *cell, vtkPolyData *allPoly);
    
private:
    FCGeometryViewObject *mPreViewObjct{};
    QHash<FCGeometrySet *, FCGeometrySetViewObject *> mViewObjs{};
};
} // namespace FC



#endif // FCGEOMETRYVIEWDATA_H
