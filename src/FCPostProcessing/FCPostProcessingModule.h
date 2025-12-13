/**
 * @file FCPostProcessingModule.h
 * @brief 后处理模块对外接口类
 * @date 2025-12-15
 * @version V0.0.1
 * @details 提供后处理管理、数据生成、显示和工程文件读写接口
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGMODULE_H
#define FCPOSTPROCESSINGMODULE_H

#include "FCPostProcessingAPI.h"
#include <QObject>
#include <QColor>
#include <QList>
#include <QString>
#include <QDomDocument>

class vtkDataSet;

namespace FC
{
class FCPostProcessingKernal;
class FCMeshModule;

class FCPOSTPROCESSING_API FCPostProcessingModule : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    explicit FCPostProcessingModule(QObject* parent = nullptr);
    ~FCPostProcessingModule() override;
    
    /****************************
     * 后处理管理接口（CRUD）
     ****************************/
    IdType createPostProcessing(const QString& name, IdType meshID);      // 创建后处理，返回ID
    bool deletePostProcessingByID(IdType id);                          // 删除指定ID的后处理
    bool deletePostProcessingAt(int index);                         // 删除指定索引的后处理
    int getPostProcessingCount() const;                             // 获取后处理数量
    FCPostProcessingKernal* getPostProcessingByID(IdType id) const;             // 获取指定ID后处理
    FCPostProcessingKernal* getPostProcessingAt(int index) const;            // 获取指定索引后处理
    bool isPostProcessingExist(IdType id) const;                      // 判断后处理是否存在
    void clearAllPostProcessing();                                // 清空所有后处理
    
    /****************************
     * 后处理数据生成接口
     ****************************/
    void generatePostProcessingData(IdType postID, IdType meshID, FCMeshModule* meshModule = nullptr);               // 在网格上生成随机数据
    
    /****************************
     * 后处理显示接口（VTK）
     ****************************/
    void generateDisplayData(IdType postID);          // 生成单个后处理显示数据
    void generateDisplayAll();                     // 生成全部后处理显示数据
    void setPostProcessingVisible(IdType postID, bool visible); // 设置后处理可见性
    bool isPostProcessingVisible(IdType postID) const;         // 获取后处理可见性
    void setPostProcessingColor(IdType postID, const QColor& color); // 设置后处理颜色
    QColor getPostProcessingColor(IdType postID) const;             // 获取后处理颜色
    
    /****************************
     * 工程文件 / 二进制接口
     ****************************/
    void writeToProject(QDomDocument* doc, QDomElement* parent); // 写入工程文件
    void readFromProject(QDomNodeList* nodelist);                // 读取工程文件
    void writeBinary(QDataStream* stream);                       // 写入二进制文件
    void readBinary(QDataStream* stream);                        // 读取二进制文件
    
public slots:
    void onPostProcessingReady(IdType postID, vtkDataSet* dataset);
signals:
    /****************************
     * 信号接口
     ****************************/
    void postProcessingGenerated(IdType postID, bool r = true);                 // 后处理生成完成
    void postProcessingProgress(IdType postID, int percent); // 后处理生成进度
    void postProcessingError(IdType postID, const QString& err);
    void postProcessingDeleted(IdType postID);                   // 后处理删除
    void allPostProcessingCleared();                        // 所有后处理清空完成
    
private:
    // 在网格上生成随机标量场数据
    vtkDataSet* generateRandomScalarField(vtkDataSet* meshData);
};

} // namespace FC

#endif // FCPOSTPROCESSINGMODULE_H

