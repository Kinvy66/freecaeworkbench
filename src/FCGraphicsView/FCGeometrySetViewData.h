/**
 * @file FCGeometrySetViewData.h
 * @brief 几何集合可视化对象
 * @date 2025-11-26
 * @version V0.0.1
 * @details 管理一个几何集合模型的基础图元(点、线、面、体）
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYSETVIEWDATA_H
#define FCGEOMETRYSETVIEWDATA_H

#include "FCGraphicsViewGlobal.h"
#include <QHash>
#include <QList>
#include <Standard_Handle.hxx>

class vtkPolyData;
class TopoDS_TShape;
class QColor;

namespace FC 
{

class FCGeometryViewObject;
class FCGeometrySet;
class FCGeometryData;

class FCGRAPHICSVIEW_API FCGeometrySetViewData
{
public:
    using IdType  = uint64_t;  ///< id类型 
public:
    FCGeometrySetViewData(const IdType id);
    ~FCGeometrySetViewData();
    FCGeometrySet* getGeometrySet();
    
    void setFacePoly(vtkPolyData* p);
    vtkPolyData* getFacePoly();
    void setEdgePoly(vtkPolyData* p);
    vtkPolyData* getEdgePoly();
    void setPointPoly(vtkPolyData* p);
    vtkPolyData* getPointPoly();
    void genSolidViewObj();
    
    void appendFaceViewObj(int index, Handle(TopoDS_TShape) s, FCGeometryViewObject* v);
    void appendEdgeViewObj(int index, FCGeometryViewObject* v);
    void appendPointViewObj(int index, FCGeometryViewObject* v);
    void appendSolidViewObj(int index, FCGeometryViewObject* v);
    
    FCGeometryViewObject* getFaceViewObjByIndex(int index);
    
    FCGeometryViewObject* getFaceViewObjByCellIndex(int cellIndex);
    FCGeometryViewObject* getEdgeViewObjByCellIndex(int cellIndex);
    FCGeometryViewObject* getPointViewObjByCellIndex(int pointIndex);
    FCGeometryViewObject* getSolidViewObjByFaceIndex(int faceIndex);
    
    QList<FCGeometryViewObject*> getViewObjectByStates(int selectModel, int sates);
    
    void resetColor();
    void highLight(bool on);
    void highLightFace(int index, bool on);
    void highLightEdge(int index, bool on);
    void highLightPoint(int index, bool on);
    void highLightSolid(int index, bool on);
    
private:
    FCGeometrySet* mGeoSet{};
    vtkPolyData* mFacePoly{};
    vtkPolyData* mEdgePoly{};
    vtkPolyData* mPointPoly{};
    
    QHash<FCGeometryViewObject*, Handle(TopoDS_TShape)> mFaceObjHash{};
    QHash<int, FCGeometryViewObject*> mFaceViewObjs{};
    QHash<int, FCGeometryViewObject*> mEdgeViewObjs{};
    QHash<int, FCGeometryViewObject*> mPointViewObjs{};
    QHash<int, FCGeometryViewObject*> mSolidViewObjs{};
    
};
} // namespace FC



#endif // FCGEOMETRYSETVIEWDATA_H
