/**
 * @file FCGmshThread.h
 * @brief gmsh网格划分线程
 * @date 2025-12-09
 * @version V0.0.1
 * @details Gmsh 网格划分线程类
 *
 * 工作流：
 * 1. 从 FCMeshKernal 获取绑定的 FCGeometrySet 列表
 * 2. 将每个 TopoDS_Shape 写为临时 BREP 文件（临时目录）
 * 3. 用 gmsh::model::occ::importShapes(临时文件路径, ...)
 * 4. gmsh::model::occ::synchronize(); gmsh::model::mesh::generate(...)
 * 5. 将 Gmsh 网格转成 vtkUnstructuredGrid 并通过 meshFinished() 发送
 *
 * 注意：由于当前 gmsh C++ SDK（4.15）不支持内存直接导入 BREP，
 *       需要写临时文件然后调用 importShapes(file).
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCGMSHTHREAD_H
#define FCGMSHTHREAD_H
#include "FCMeshModuleAPI.h"
#include <QThread>
#include <QPointer>

class vtkDataSet;
class vtkUnstructuredGrid;
class TopoDS_Compound;
class BRep_Builder;



namespace FC 
{
class FCGmshSettingData;
class FCMESHMODULE_API FCGmshThread : public QThread
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCGmshThread(IdType meshID, FCGmshSettingData* setting, QObject* parent = nullptr);
    ~FCGmshThread() override;
    
protected:
    void run() override;
    
private:
    bool initGmsh();
    bool importAllOccShapesToGmsh();
    void applyMeshSettings();
    bool generateMesh();
    vtkUnstructuredGrid* convertGmshToVtk();
    void finalizeGmsh();
    
    bool saveMeshToFile(IdType meshID);
    
signals:
    void meshFinished(IdType meshID, vtkDataSet* dataset);
    void meshError(IdType meshID, const QString& err);
    void progress(IdType meshID, int percent);
private:
    IdType mMeshID;
    FCGmshSettingData* mSetting; // not owned (caller should ensure lifetime)
    bool mAbort{false};
public:
    void requestAbort() { mAbort = true; }
    
};
} // namespace FC



#endif // FCGMSHTHREAD_H
