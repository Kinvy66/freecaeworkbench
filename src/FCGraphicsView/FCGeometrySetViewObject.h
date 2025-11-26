#ifndef FCGEOMETRYSETVIEWOBJECT_H
#define FCGEOMETRYSETVIEWOBJECT_H

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

class FCGRAPHICSVIEW_API FCGeometrySetViewObject
{
public:
    FCGeometrySetViewObject(FCGeometrySet* set);
    ~FCGeometrySetViewObject();
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



#endif // FCGEOMETRYSETVIEWOBJECT_H
