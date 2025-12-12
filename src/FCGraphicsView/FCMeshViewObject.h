/**
 * @file FCMeshViewObject.h
 * @brief 网格的显示层对象
 * @date 2025-12-11
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHVIEWOBJECT_H
#define FCMESHVIEWOBJECT_H
#include "FCGraphicsViewGlobal.h"
#include <QObject>


#define POINTACTOR 0
#define EDGEACTOR 1
#define FACEACTOR 2

class vtkDataSet;
class vtkActor;

namespace FC 
{

class FCMeshKernal;
class FCMeshData;
class FCGRAPHICSVIEW_API FCMeshViewObject : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型   
public:
    /**
     * @brief Construct a new Mesh Kernal View Obj object
     * @param  k                网格表示
     */
    FCMeshViewObject(IdType kid);
    /**
     * @brief Destroy the Mesh Kernal View Obj object
     */
    ~FCMeshViewObject();
    /**
     * @brief  获取显示对象的DataSet
     * @return vtkDataSet*   显示层源数据dataSet
     */
    vtkDataSet* getDisplayData();
    /**
     * @brief Get the Actor object
     * @return vtkActor* 显示对象指针数组,3个元素， [点actor，线actor，面actor]
     */
    vtkActor** getActor();
    /**
     * @brief 设置点的颜色
     * @param  c   颜色，只有RGB三个值有效
     * @param  displayOnly 是否只设置显示对象颜色
     */
    void setPointColor(const QColor& c, bool displayOnly = false);
    /**
     * @brief 设置单元颜色
     * @param  c   颜色，只有RGB三个值有效
     * @param  displayOnly 是否只设置显示对象颜色
     */
    void setCellColor(const QColor& c, bool displayOnly = false);
    /**
     * @brief 高亮
     */
    void highLight();
    /**
     * @brief 清除高亮显示
     */
    void clearHighLight();
    /**
     * @brief  当前Kernal是否为高亮状态
     * @return true   是高亮状态
     * @return false  不是高亮状态
     */
    bool isKernalHighLight();
    /**
     * @brief 设置点的颜色
     * @param  indexs           点的在Kernal的索引
     * @param  color            要着色的颜色
     */
    void setPointDisplayColor(QList<int>& indexs, const QColor& color);
    /**
     * @brief 设置单元颜色
     * @param  indexs           单元在Kernal的索引
     * @param  color            要着色的颜色
     */
    void setCellDisplayColor(QList<int>& indexs, const QColor& color);
    /**
     * @brief  根据显示对象设置点的颜色
     * @param  indexs           点在显示对象中的索引
     * @param  color            要着色的颜色
     */
    void setPointDisplayColorByDisplayIndex(QList<int>& indexs, const QColor& color);
    /**
     * @brief  根据显示对象设置单元的颜色
     * @param  indexs           单元在显示对象中的索引
     * @param  color            要着色的颜色
     */
    void setCellDisplayColorByDisplayIndex(QList<int>& indexs, const QColor& color);
    /**
     * @brief  显示/隐藏单元
     * @param  index            需要操作的单元索引
     * @param  show             是否显示
     */		
    void showCells(const QList<int>& index, bool show);
    
private:
    /**
     * @brief 为DataSet生成ID属性
     */
    void generateIDProp();
    /**
     * @brief 初始化显示层数据
     */
    void init();
    /**
     * @brief 根据单元/节点的显示状态更新display actor
     */
    void updateDisplayMember();
    
private:
    /**
     * @brief 全部网格数据指针
     */
    FCMeshData* mMeshData{};
    /**
     * @brief 网格Kernal指针
     */
    // FCMeshKernal* mMeshKernal;
    
    /**
     * @brief 网格id
     */
    IdType mMeshID;
    
    /**
     * @brief 显示层数据表示
     */
    vtkDataSet* mDisplayData{};
    /**
     * @brief 显示对象
     */
    vtkActor*  mActor[3];
    /**
     * @brief 高亮状态标记
     */
    bool mIsKernalHighLight{ false };
};
} // namespace FC



#endif // FCMESHVIEWOBJECT_H
