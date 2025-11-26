/**
 * @file FCGeometryViewObject.h
 * @brief 
 * @date 2025-11-26
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYVIEWOBJECT_H
#define FCGEOMETRYVIEWOBJECT_H
#include <QList>
#include <QColor>
#include <Standard_Handle.hxx>

class vtkPolyData;
class TopoDS_TShape;
class QColor;

namespace FC 
{
class FCGeometrySet;
class FCGeometrySetViewObject;
class FCGeometryViewObject
{
public:
    
    enum ViewObjType
    {
        Point,
        Edge,
        Face,
        Solid
    };
    
    enum ViewStates
    {
        Normal,
        PreHigh,
        HighLigh
    };
    
    FCGeometryViewObject(ViewObjType type, int beg, int end, Handle(TopoDS_TShape) ts);
    ~FCGeometryViewObject() = default;
    void getRange(int& beg, int &end);
    void appendSolidFace(int f);
    QList<int> getSolidFace();
    void setIndex(int index);
    int getIndex();
    FCGeometrySet* getGeometySet();
    FCGeometrySetViewObject* getGeoSetViewObject();
    ViewStates getStates();
    void setStates(ViewStates s);
    
    void setConnectionData(vtkPolyData* poly, FCGeometrySetViewObject* setViewObj);
    void resetColor();
    void preHighLight();
    void highLight();
    
private:
    void setObjectColor(QColor color);
    void setSolidColor(QColor color);
    
private:
    ViewObjType mType{ Solid };
    ViewStates mStates{ Normal };
    int mIndex{ -1 };
    int mBegin{ 0 };
    int mEnd{ 0 };
    QList<int> mSolidFaces{};
    Handle(TopoDS_TShape) mTshape {};
    
    vtkPolyData* mPolys{};
    FCGeometrySetViewObject* mSetViewObj{};
};

} // namespace FC



#endif // FCGEOMETRYVIEWOBJECT_H
