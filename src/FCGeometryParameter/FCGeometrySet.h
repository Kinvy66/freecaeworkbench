/**
 * @file FCGeometrySet.h
 * @brief 几何形状表示类
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYSET_H
#define FCGEOMETRYSET_H

#include "FCDataBase.h"
#include "FCGeometryParaAPI.h"

class TopoDS_Shape;
class vtkDataSet;
class vtkPolyData;


namespace FC 
{

/**
	 * @brief 几何
	 * @since 2.5.0
	 */
enum GeometryType
{
    NONE = 0,
    IGES,
    STEP,
    STL,
    DATUM,
};

class FCGeometryModelParaBase;

class FCGEOMETRYPARA_API FCGeometrySet : public FCDataBase
{
public:
    FCGeometrySet(GeometryType type = NONE);
    ~FCGeometrySet();
    
    void setID(int id) override;
    
    TopoDS_Shape *getShape(int type, int index);
    
    const TopoDS_Shape &getRealShape(int type, int index);
    
    void setVisible(bool v);
    
    bool isVisible();
    
    void setType(GeometryType type);
    
    GeometryType getType();
    
    void setShape(TopoDS_Shape *shape);
    
    TopoDS_Shape *getShape();
    
    void setPoly(vtkPolyData* poly);
    vtkPolyData* getPoly();
    
    void setParameter(FCGeometryModelParaBase *p);
    
    FCGeometryModelParaBase *getParameter();
    
    
    void dataToStream(QDataStream *s) override;
    
    
    bool writeBrep(QString name);
    
    bool writePoly(QString name);
    
    bool readBrep(QString name);
    
    bool readPoly(QString name);
    
protected:
    vtkPolyData* mPolyData{};
    GeometryType mType{NONE};
    bool mVisible{true};
    
    TopoDS_Shape *mShape{};
    
    
    FCGeometryModelParaBase *mParameter{};
    
private:
    static int s_idOffset;
    static TopoDS_Shape * s_tempShape;
    
};
} // namespace FC


#endif // FCGEOMETRYSET_H
