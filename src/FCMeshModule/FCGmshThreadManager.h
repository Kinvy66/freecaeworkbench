/**
 * @file FCGmshThreadManager.h
 * @brief 网格划分线程管理类
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGMSHTHREADMANAGER_H
#define FCGMSHTHREADMANAGER_H
#include "FCMeshModuleAPI.h"
#include <QObject>
#include <QHash>
#include <QMutex>

class vtkDataSet;

namespace FC 
{

class FCGmshThread;
class FCGmshSettingData;

class FCMESHMODULE_API FCGmshThreadManager : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    static FCGmshThreadManager* getInstance();
    ~FCGmshThreadManager() override;
    
    // 添加任务；返回 true 表示任务已成功加入队列
    bool addTask(IdType meshID, FCGmshSettingData* setting);
    
    // 停止所有进行中的网格生成（会请求线程退出并等待）
    void stopAll();
    
    // 查询是否正在生成
    bool isGenerating(int meshID) const;
    
signals:
    // 当某个线程完成并经过 manager 处理后，向外广播 meshReady
    void meshReady(IdType meshID, vtkDataSet* dataset);
    void meshProgress(IdType meshID, int percent);
    void meshError(IdType meshID, const QString& err);
    
private slots:
    void onThreadFinished(IdType meshID, vtkDataSet* dataset);
    void onThreadProgress(IdType meshID, int percent);
    void onThreadError(IdType meshID, const QString& err);
    
private:
    explicit FCGmshThreadManager(QObject* parent = nullptr);
    static FCGmshThreadManager* s_instance;
    
    mutable QMutex mMutex;
    QHash<IdType, FCGmshThread*> mThreads;
};

} // namespace FC


#endif // FCGMSHTHREADMANAGER_H
