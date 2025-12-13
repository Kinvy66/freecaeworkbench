/**
 * @file FCPostProcessingKernal.h
 * @brief 单个后处理结果，包含数据和属性
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGKERNAL_H
#define FCPOSTPROCESSINGKERNAL_H
#include "FCPostProcessingAPI.h"
#include "FCDataBase.h"
#include <vtkSmartPointer.h>
#include <QString>
#include <QColor>
#include <QPair>

class vtkDataSet;
class vtkCell;
class QDataStream;

namespace FC 
{
class FCPOSTPROCESSING_API  FCPostProcessingKernal : public FCDataBase
{
public:
    FCPostProcessingKernal();
    ~FCPostProcessingKernal() = default;
    
    //重置节点和单元的偏移量
    static void resetOffset();
    
    void setID(IdType id) override;
    static void resetMaxID();
    static int getMaxID();
    
    //设置后处理数据，包括节点和标量场数据
    void setPostProcessingData(vtkDataSet* dataset);
    //获取后处理数据，vtk表示
    vtkDataSet* getPostProcessingData();
    //获取节点位置，double[3],index从0开始
    double* getPointAt(const int index);
    //获取单元，index从0开始
    vtkCell* getCellAt(const int index);
    //是否可见
    bool isVisible();
    //设置可见状态
    void setVisible(bool v);
    //获取节点数目
    int getPointCount();
    //获取单元数量
    int getCellCount();
    
    void dataToStream(QDataStream* s) override;
    //写xml
    QDomElement& writeToProjectFile(QDomDocument* doc, QDomElement* ele) override;
    //读xml
    void readDataFromProjectFile(QDomElement* e) override;
    //写出二进制文件
    void writeBinaryFile(QDataStream* dataStream);
    //读入二进制文件
    void readBinaryFile(QDataStream* dataStream);
    
    //设置标量场名称
    void setScalarFieldName(const QString& name);
    QString getScalarFieldName() const;
    
    //设置颜色映射
    void setColorMap(bool enable, const QColor& minColor, const QColor& maxColor);
    QPair<bool, QPair<QColor, QColor>> getColorMap() const;
    
    //绑定网格ID
    void bindMesh(IdType meshID);
    IdType getBindedMesh() const;
    
private:
    bool mVisible{ true };
    vtkSmartPointer<vtkDataSet> mPostData{};
    QString mScalarFieldName{"ScalarField"};
    QPair<bool, QPair<QColor, QColor>> mColorMap{false, {QColor(0, 0, 255), QColor(255, 0, 0)}};
    IdType mBindedMeshID{0};
    
private:
    static int s_idOffset;
    
};

} // namespace FC

#endif // FCPOSTPROCESSINGKERNAL_H

