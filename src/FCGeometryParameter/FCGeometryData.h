/**
 * @file FCGeometryData.h
 * @brief 几何数据管理基类（单例）
 * @date 2025-11-23
 * @version V0.0.1
 * @details 管理创建的所有几何模型数据
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYDATA_H
#define FCGEOMETRYDATA_H

#include "FCDataBase.h"
#include "FCGeometryParaAPI.h"

class TopoDS_Shape;
class QDomDocument;
class QDomElement;
class QDomNodeList;
class gp_Ax3;
class vtkPolyData;

namespace FC 
{

class FCGeometrySet;
class FCGeometryDatum;

class FCGEOMETRYPARA_API FCGeometryData : public FCDataBase
{
public:
    /**
     * @brief 获取单例指针
     * @return 返回单例指针
     */
    static FCGeometryData* getInstance();
    
    /**
     * @brief 添加形状
     * @param set
     */
    void appendGeometrySet(FCGeometrySet *set);
    /**
     * @brief 添加基准
     */
    void appendGeometryDatum(FCGeometryDatum *plane);
    
    /**
     * @brief 获取全部基准
     * @return QList<GeometryDatum*> 返回的基准列表
     */
    QList<FCGeometryDatum *> getGeometryDatum();
    
    /**
     * @brief 获取形状的数量
     * @return int 返回形状的数量
     */
    int getGeometrySetCount();
    /**
     * @brief 判断几何数据是否包含形状
     * @return bool
     */
    bool isEmpty();
    /**
     * @brief 获取索引为index的形状
     * @param index 要获取形状的索引
     * @return GeometrySet* 返回获取的形状
     * @attention 索引越界的时候返回nullptr
     */
    FCGeometrySet *getGeometrySetAt(const int index);
    /**
     * @brief 获取获取形状对应的索引
     * @param s 指定的形状
     * @return int 返回指定性转的索引
     * @attention 获取失败时返回-1
     */
    int getIndexByGeoometrySet(FCGeometrySet *s);
    /**
     * @brief 移除索引值为index的形状
     * @param index 要移除形状的索引
     */
    void removeGeometrySet(const int index);
    /**
     * @brief 替换形状
     * @param newset 替换后的形状
     * @param oldset 替换前的形状
     * @attention 如果oldset不是当前对象的形状，则不会执行替换操作
     */
    void replaceSet(FCGeometrySet *newset, FCGeometrySet *oldset);
    /**
     * @brief 移除直接子形状
     * @param set 要移除的直接子形状
     * @note 该函数执行移除操作时不会递归移除
     */
    void removeTopGeometrySet(FCGeometrySet *set);
    /**
     * @brief 判断是否存在直接子形状
     * @param set 要判断的直接子形状
     * @return bool 返回是否存在直接子形状
     */
    bool hasGeometrySet(FCGeometrySet *set);
    //		void removeDatumPlaneByIndex(int index);
    /**
     * @brief 移除直接子基准
     * @param datum 要移除的直接子形状
     */
    void removeGeometryDatum(FCGeometryDatum *plane);
    /**
     * @brief 设置几何形状的可见性
     * @param index 要设置形状的索引
     * @param visable 要设置的可见性
     */
    void setVisable(int index, bool visable);
    /**
     * @brief 清空所有内容
     */
    void clear();
    /**
     * @brief 根据ID获取几何形状
     * @param id 要获取形状的ID
     * @return GeometrySet* 返回获取到的几何形状
     * @attention 如果ID值不合法，则返回nullptr
     */
    FCGeometrySet *getGeometrySetByID(const int id);
    /**
     * @brief 获取索引为index的基准
     * @param index 要获取基准的索引值
     * @return GeometryDatum* 返回获取到的基准
     */
    FCGeometryDatum *getDatumByIndex(const int index);
    /**
     * @brief 获取对象的md5值
     * @return QString 返回计算得到的md5值
     */
    QString getMD5();
    /**
     * @brief 根据ID值进行内部排序
     */
    void sort();
    
    //文件写出至工程文件
    // QDomElement &writeToProjectFile(QDomDocument *doc, QDomElement *element, bool isdiso = false);
    //从工程文件读入数据
    // void readFromProjectFile(QDomNodeList *nodelist, bool isdiso = false);
    /**
     * @brief 设置草绘平面
     * @param loc 草绘平面的坐标原点
     * @param dir 草绘平面的方向向量
     */
    void setSketchPlane(double *loc, double *dir);
    /**
     * @brief 获取草绘平面
     * @return gp_Ax3* 返回草绘平面
     */
    gp_Ax3 *getSketchPlane();
    /**
     * @brief 添加几何组件
     */
    // void appendGeoComponent(GeoComponent *);
    /**
     * @brief 获取所有的几何组件
     * @return QList<GeoComponent *>& 返回所有的几何组件
     */
    // QList<GeoComponent *> &getGeoComponentList();
    /**
     * @brief 根据索引获取组件
     * @return GeoComponent* 返回组件
     */
    // GeoComponent *getGeoComponentByIndex(int);
    /**
     * @brief 根据ID获取组件
     * @return GeoComponent* 返回组件
     */
    // GeoComponent *getGeoComponentByID(int);
    /**
     * @brief 通过索引删除组件
     * @return bool 返回删除操作是否执行成功
     */
    // bool removeGeoComponentByIndex(int);
    /**
     * @brief 删除组件
     * @return bool 返回删除操作是否执行成功
     */
    // bool removeGeoComponent(GeoComponent *);
    //对所有几何组件进行剖分，然后生成网格并写入XML中
    // void generateMeshAndWriteToXML(QDomDocument& doc, QDomElement& parent);
        
private:
    FCGeometryData() = default;
    ~FCGeometryData();
    
private:
    /**
     * @brief 单例指针
     */
    static FCGeometryData *mInstance;
    /**
     * @brief 几何形状列表
     */
    QList<FCGeometrySet *> mGeometryList{};
    /**
     * @brief 基准列表
     */
    QList<FCGeometryDatum *> mGeomtretryDatumList{};
    /**
     * @brief 草绘平面
     */
    gp_Ax3 *mSketchPlan{};
    /**
     * @brief 组件列表
     */
    // QList<GeoComponent *> _geoCpList;
    //		QHash<int, vtkPolyData*> _geoCp
};

} // namespace FC



#endif // FCGEOMETRYDATA_H
