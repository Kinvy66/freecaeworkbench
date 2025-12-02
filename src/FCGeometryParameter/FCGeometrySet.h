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
    FCGeometrySet(GeometryType type = NONE, bool needID = true);
    ~FCGeometrySet();
    
    /**
     * @brief 设置id
     * @param id
     */ 
    void setID(int id) override;
    
    /**
     * @brief 重置最大id
     * @note 不用轻易调用
     */
    static void resetMaxID();
    
    /**
     * @brief 获取最大id
     * @return 
     */
    static int getMaxID();
    
    /**
     * @brief 根据ID获取子形状
     * @param id 要获取ID的子形状
     * @return GeometrySet* 返回的子形状
     */
    FCGeometrySet *getSetByID(int id);
    
    /**
     * @brief 获取topo数据
     * @param type
     * @param index
     * @return 
     */
    TopoDS_Shape *getShape(int type, int index);
    
    /**
     * @brief 获取形状
     * @param type
     * @param index
     * @return 
     */
    const TopoDS_Shape &getRealShape(int type, int index);
    
    /**
     * @brief 设置可见
     * @param v
     */
    void setVisible(bool v);
    
    /**
     * @brief 是否可见
     * @return 
     */
    bool isVisible();
    
    /**
     * @brief 设置类型
     * @param type
     */
    void setType(GeometryType type);
    
    /**
     * @brief 获取类型
     * @return 
     */
    GeometryType getType();
    
    /**
     * @brief 设置形状的拓扑
     * @param shape
     */
    void setShape(TopoDS_Shape *shape);
    
    /**
     * @brief 获取形状的拓扑
     * @return 
     */
    TopoDS_Shape *getShape();
    
    /**
     * @brief 设置poly data
     * @param poly
     */
    void setPoly(vtkPolyData* poly);
    
    /**
     * @brief 获取poly data
     * @return 
     */
    vtkPolyData* getPoly();
    
    /**
     * @brief 设置操作参数
     * @param p
     */
    void setParameter(FCGeometryModelParaBase *p);
    
    /**
     * @brief 获取操作参数
     * @return 
     */
    FCGeometryModelParaBase *getParameter();
    
    /**
     * @brief 转成流数据
     * @param s
     */
    void dataToStream(QDataStream *s) override;
    
    /**
     * @brief 写出brep文件
     * @param name 要写出的brep文件
     * @return bool 返回写出结果
     */
    bool writeBrep(QString name);
    
    /**
     * @brief 写出vtk文件
     * @param name
     * @return 
     */
    bool writePoly(QString name);
    
    /**
     * @brief 读入brep文件
     * @param name 要读取的brep文件
     * @attention 路径不能出现中文
     * @return bool 返回读取结果
     */
    bool readBrep(QString name);
    
    /**
     * @brief 读入vtk文件
     * @param name
     * @return 
     */
    bool readPoly(QString name);
    
    /**
     * @brief 写出几何到工程文件
     * @param doc
     * @param ele
     * @param isDisp
     * @return 
     */
    virtual QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *ele, bool isDisp = false);
    
    /**
     * @brief 从工程文件几何读入
     * @param e
     * @param isDiso
     */
    virtual void readDataFromProjectFile(QDomElement *e, bool isDiso = false);
    
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
