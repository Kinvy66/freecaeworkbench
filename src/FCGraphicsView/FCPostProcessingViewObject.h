/**
 * @file FCPostProcessingViewObject.h
 * @brief 后处理的显示层对象
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGVIEWOBJECT_H
#define FCPOSTPROCESSINGVIEWOBJECT_H
#include "FCGraphicsViewGlobal.h"
#include <QObject>

class vtkDataSet;
class vtkActor;
class vtkLookupTable;

namespace FC 
{

class FCPostProcessingKernal;
class FCPostProcessingData;

class FCGRAPHICSVIEW_API FCPostProcessingViewObject : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型   
public:
    /**
     * @brief Construct a new PostProcessing View Object
     * @param  kid                后处理ID
     */
    FCPostProcessingViewObject(IdType kid);
    /**
     * @brief Destroy the PostProcessing View Object
     */
    ~FCPostProcessingViewObject();
    /**
     * @brief  获取显示对象的DataSet
     * @return vtkDataSet*   显示层源数据dataSet
     */
    vtkDataSet* getDisplayData();
    /**
     * @brief Get the Actor object
     * @return vtkActor* 显示对象指针
     */
    vtkActor* getActor();
    /**
     * @brief 获取颜色查找表
     * @return vtkLookupTable* 颜色查找表
     */
    vtkLookupTable* getLookupTable();
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
     * @brief 更新显示数据（从Kernal获取数据并更新显示）
     */
    void updateDisplayData();
    
    /**
     * @brief 设置显示形式 0:面, 1:线框, 2:点
     */
    void setDisplayForm(int form);
    
    /**
     * @brief 设置透明度 (0.0-1.0)
     */
    void setTransparency(double opacity);
    
    /**
     * @brief 设置点大小
     */
    void setPointSize(int size);
    
    /**
     * @brief 设置线宽
     */
    void setLineWidth(int width);
    
    /**
     * @brief 设置着色方式 0:平面着色, 1:Gouraud着色, 2:Phong着色
     */
    void setShadingMethod(int method);
    
    /**
     * @brief 设置光照属性
     */
    void setLightingProperties(double specularCoeff, double specularIntensity, 
                                double ambientCoeff, double diffuseCoeff);
    
    /**
     * @brief 设置边界颜色
     */
    void setBoundaryColor(double r, double g, double b);
    
    /**
     * @brief 设置边界是否显示
     */
    void setBoundaryVisibility(bool visible);
    
    /**
     * @brief 获取显示形式 0:面, 1:线框, 2:点
     */
    int getDisplayForm() const;
    
    /**
     * @brief 获取透明度 (0.0-1.0)
     */
    double getTransparency() const;
    
    /**
     * @brief 获取点大小
     */
    int getPointSize() const;
    
    /**
     * @brief 获取线宽
     */
    int getLineWidth() const;
    
    /**
     * @brief 获取着色方式 0:平面着色, 1:Gouraud着色, 2:Phong着色
     */
    int getShadingMethod() const;
    
    /**
     * @brief 获取光照属性
     */
    void getLightingProperties(double& specularCoeff, double& specularIntensity, 
                                double& ambientCoeff, double& diffuseCoeff) const;
    
    /**
     * @brief 获取边界颜色
     */
    void getBoundaryColor(double& r, double& g, double& b) const;
    
    /**
     * @brief 获取边界是否显示
     */
    bool getBoundaryVisibility() const;
    
private:
    /**
     * @brief 初始化显示层数据
     */
    void init();
    /**
     * @brief 创建颜色查找表
     */
    void createLookupTable();
    
private:
    /**
     * @brief 后处理数据指针
     */
    FCPostProcessingData* mPostProcessingData;
    /**
     * @brief 后处理id
     */
    IdType mPostProcessingID;
    
    /**
     * @brief 显示层数据表示
     */
    vtkDataSet* mDisplayData{};
    /**
     * @brief 显示对象
     */
    vtkActor*  mActor{};
    /**
     * @brief 颜色查找表
     */
    vtkLookupTable* mLookupTable{};
    /**
     * @brief 高亮状态标记
     */
    bool mIsKernalHighLight{ false };
};

} // namespace FC

#endif // FCPOSTPROCESSINGVIEWOBJECT_H

