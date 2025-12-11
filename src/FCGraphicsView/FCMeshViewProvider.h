/**
 * @file FCMeshViewProvider.h
 * @brief 网格可视化管理器
 * @date 2025-12-09
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCMESHVIEWPROVIDER_H
#define FCMESHVIEWPROVIDER_H
#include "FCGraphicsViewGlobal.h"
#include <QObject>
#include <QHash>
#include <QPair>

class vtkPolyData;
class vtkActor;

namespace FC 
{

class FCGraphViewWindow;
class FCMeshViewData;

class FCGRAPHICSVIEW_API FCMeshViewProvider : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型
public:
    FCMeshViewProvider(FCGraphViewWindow* viewWindow, QObject* parent = nullptr);
    ~FCMeshViewProvider();
    
    // void showMesh(IdType id, vtkPolyData* mesh, bool render = true);
    void removeMesh(IdType id);
    void updateMeshColor(IdType id);
    
    void highlightMesh(IdType id, bool on);
    void selectMesh(IdType id, bool on);
    
    void removeAllMeshes();
    
public slots:
    void showMesh(IdType id, bool render = true);
    void updateMeshDisplayActor(const IdType id);
    
    
private:
    FCMeshViewData* mViewData = nullptr;
    FCGraphViewWindow* mGraphViewWindow = nullptr;
    QHash<IdType, vtkActor*> mActors;
};
} // namespace FC



#endif // FCMESHVIEWPROVIDER_H
