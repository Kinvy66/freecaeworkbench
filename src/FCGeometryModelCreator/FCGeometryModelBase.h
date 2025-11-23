/**
 * @file FCGeometryModelBase.h
 * @brief 
 * @date 2025-11-23
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGEOMETRYMODELBASE_H
#define FCGEOMETRYMODELBASE_H


#ifndef PI
#define PI 3.14159265358979323846
#endif

#include <QObject>
#include "FCGeometryModelCreatorAPI.h"

class TopoDS_Shape;

namespace FC 
{
    // 几何模型类型
    enum GeometryModelType
    {
        D3Feature, ///< 三维特征
        Sketch,	   ///< 草绘特征
    };

class FCGeometrySet;

class FCGEOMETRYMODELCREATOR_API FCGeometryModelBase : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     */
    FCGeometryModelBase(QObject* parent = nullptr);
    /**
     * @brief 析构函数
     */
    ~FCGeometryModelBase() = default;
    /**
     * @brief 命令执行调用的函数
     * @return bool 返回执行结果
     */
    virtual bool execute() = 0;
    /**
     * @brief 撤销操作
     */
    virtual void undo();
    /**
     * @brief 重做操作
     */
    virtual void redo();
    virtual void releaseResult();
    /**
     * @brief 获取命令执行后的结果形状
     * @return TopoDS_Shape* 返回结果形状
     */
    TopoDS_Shape *getResultShape();
    /**
     * @brief 获取命令类型
     * @return CommandType 返回命令类型
     */
    GeometryModelType getGeometryModelType() const;
    // void setEditData(Geometry::GeometrySet *set);
    
signals:
    void updateGeoTree();
    void showSet(FCGeometrySet *s, bool r = true);
    // void showDatum(Geometry::GeometryDatum *);
    // void removeDisplayActor(Geometry::GeometrySet *s);
    // void removeDisplayDatumActor(Geometry::GeometryDatum *);
    /**
     * @brief 命令执行后会触发此信号
     */
    void updateActions();
    /**
     * @brief 执行撤销操作后会触发此信号
     * @param data
     */
    // void updatePropertySig(DataProperty::DataBase *data);
    
protected:

    /**
     * @brief 命令类型
     */
    GeometryModelType mType{D3Feature};
    /**
     * @brief 命令执行后的形状
     */
    TopoDS_Shape *mResShape{};
    
    // GeometryData *_geoData{};
    /**
     * @brief 命令列表
     */
    // GeoComandList *_commandList{};
    
    bool mIsEdit{false};
    // Geometry::GeometrySet *_editSet{};
};
} // namespace FC



#endif // FCGEOMETRYMODELBASE_H
