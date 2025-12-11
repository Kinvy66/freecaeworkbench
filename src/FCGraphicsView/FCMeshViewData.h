/**
 * @file FCMeshViewData.h
 * @brief 网格可视化对象管理
 * @date 2025-12-11
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHVIEWDATA_H
#define FCMESHVIEWDATA_H
#include "FCGraphicsViewGlobal.h"
#include <QHash>
#include <QList>

class vtkPolyData;
class vtkActor;

namespace FC 
{
class FCMeshViewObject
{
public:
    enum ObjectType { Mesh };
    
    FCMeshViewObject(vtkPolyData* data)
        : meshData(data), actor(nullptr), state(0) {}
    
    vtkPolyData* meshData = nullptr;
    vtkActor* actor = nullptr;
    int state = 0; // 0=normal, 1=highlight, 2=selected
};

class FCGRAPHICSVIEW_API FCMeshViewData
{
public:
    using IdType  = uint64_t;  ///< id类型   
public:
    FCMeshViewData() {}
    ~FCMeshViewData();
    
    void addMesh(IdType id, vtkPolyData* mesh);
    void removeMesh(IdType id);
    FCMeshViewObject* getMeshObject(IdType id);
    QList<IdType> getAllMeshIDs() const;
    
    void setHighlight(IdType id, bool on);
    void setSelect(IdType id, bool on);
    
private:
    QHash<IdType, FCMeshViewObject*> mMeshObjs;
};

} // namespace FC


#endif // FCMESHVIEWDATA_H
