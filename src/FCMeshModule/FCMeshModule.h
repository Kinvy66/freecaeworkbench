/**
 * @file FCMeshModule.h
 * @brief 网格模块对外接口类
 * @date 2025-12-10
 * @version V0.0.1
 * @details 提供网格管理、网格生成、显示和工程文件读写接口
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHMODULE_H
#define FCMESHMODULE_H

#include "FCMeshModuleAPI.h"
#include <QObject>
#include <QColor>
#include <QList>
#include <QString>
#include <QDomDocument>

class vtkDataSet;

namespace FC
{
class FCMeshKernal;
class FCGmshSettingData;
class FCGmshThreadManager;

class FCMESHMODULE_API FCMeshModule : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    explicit FCMeshModule(QObject* parent = nullptr);
    ~FCMeshModule() override;
    
    /****************************
     * 网格管理接口（CRUD）
     ****************************/
    IdType createMesh(const QString& name, FCGmshSettingData* para);      // 创建网格，返回ID
    bool deleteMeshByID(IdType id);                          // 删除指定ID的网格
    bool deleteMeshAt(int index);                         // 删除指定索引的网格
    int getMeshCount() const;                             // 获取网格数量
    FCMeshKernal* getMeshByID(IdType id) const;             // 获取指定ID网格
    FCMeshKernal* getMeshAt(int index) const;            // 获取指定索引网格
    bool isMeshExist(IdType id) const;                      // 判断网格是否存在
    void clearAllMeshes();                                // 清空所有网格
    
    /****************************
     * 网格生成接口
     ****************************/
    void generateMesh(IdType meshID, FCGmshSettingData* setting);               // 同步生成网格
    void generateMesh(IdType meshID);               // 同步生成网格
    
    void generateMeshesAsync(const QList<IdType>& meshIDs,
                             const QList<FCGmshSettingData*>& settings);     // 异步生成多个网格
    void stopAllMeshGeneration();                                            // 停止所有正在生成的任务
    bool isGenerating(IdType meshID) const;                                     // 查询网格生成状态
    
    /****************************
     * 网格显示接口（VTK）
     ****************************/
    void generateDisplayData(IdType meshID);          // 生成单个网格显示数据
    void generateDisplayAll();                     // 生成全部网格显示数据
    void setMeshVisible(IdType meshID, bool visible); // 设置网格可见性
    bool isMeshVisible(IdType meshID) const;         // 获取网格可见性
    void setMeshColor(IdType meshID, const QColor& color); // 设置网格颜色
    QColor getMeshColor(IdType meshID) const;             // 获取网格颜色
    
    /****************************
     * 工程文件 / 二进制接口
     ****************************/
    void writeToProject(QDomDocument* doc, QDomElement* parent); // 写入工程文件
    void readFromProject(QDomNodeList* nodelist);                // 读取工程文件
    void writeBinary(QDataStream* stream);                       // 写入二进制文件
    void readBinary(QDataStream* stream);                        // 读取二进制文件
    
    /****************************
     * GMSH参数接口
     ****************************/
    void setGmshSetting(IdType meshID, FCGmshSettingData* setting); // 设置网格划分参数
    FCGmshSettingData* getGmshSetting(int meshID) const;         // 获取网格划分参数
    
public slots:
    void onMeshReady(IdType meshID, vtkDataSet* dataset);
signals:
    /****************************
     * 信号接口
     ****************************/
    void meshGenerated(IdType meshID, bool r = true);                 // 网格生成完成
    void meshGenerationProgress(IdType meshID, int percent); // 网格生成进度
    void meshError(IdType meshID, const QString& err);
    void meshDeleted(IdType meshID);                   // 网格删除
    void allMeshesCleared();                        // 所有网格清空完成
    
private:
    FCGmshThreadManager* mThreadManager{nullptr};  // 管理异步生成线程
    // 其余内部操作均通过 FCMeshData 单例管理所有网格
};

} // namespace FC

#endif // FCMESHMODULE_H
