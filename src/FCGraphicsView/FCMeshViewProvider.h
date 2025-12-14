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
#include <QMultiHash>

class vtkActor;
class vtkDataSet;

namespace FC 
{

class FCGraphViewWindow;
class FCMeshKernal;
class FCMeshData;
class FCMeshViewObject;

enum DisplayModel
{
    Node,
    WireFrame,
    Surface,
    SurfaceWithEdge,
};

class FCGRAPHICSVIEW_API FCMeshViewProvider : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型  
public:
    /**
     * @brief Construct a new Mesh View Provider object
     * @param  mainwindow       主窗口
     * @param  preWin           前处理窗口
     */
    FCMeshViewProvider(FCGraphViewWindow* viewWindow, QObject *parent = nullptr);
    /**
     * @brief Destroy the Mesh View Provider object
     */
    ~FCMeshViewProvider();
    /**
     * @brief 更新显示模式
     * @param  k   网格kernal，若为nullptr则全部更新
     */
    void updateDisplayModel(IdType meshID/* FCMeshKernal *k = nullptr*/);
    /**
     * @brief 更新颜色等渲染选项
     * @param  k   网格kernal，若为nullptr则全部更新
     */
    void updateGraphOption(IdType meshID/* FCMeshKernal *k = nullptr*/);
    /**
     * @brief 隐藏/显示所有网格
     * @param visible 是否可见
     */
    void setAllMeshVisible(bool visible);
    /**
     * @brief   是否显示Kernal
     * @param  k     网格Kernal
     * @param  show  是否显示
     */
    void showKernal(IdType meshID /*FCMeshKernal *k*/, bool show);
    /**
     * @brief  设置网格交互拾取模式
     * @param  m   拾取模式
     */
    // void setMeshSelectMode(ModuleBase::SelectModel m);
    /**
     * @brief 高亮交互拾取的对象
     * @param  items    交互拾取的对象
     */
    void highLighSelectItem(QMultiHash<int, int> *items);
    /**
     * @brief  获取交互选取的网格元素
     * @return QMultiHash<int, int>*   kernalID-node/element Index  Hash
     */
    QMultiHash<int, int> *getSelectItem();
    
    void removeMeshActor(IdType meshID);
    
public slots:
    /**
     * @brief 新建或者删除网格，更新显示
     */
    void updateMeshActorSlot();
    
    void showMesh(IdType meshID, bool r = true);
    
private slots:
    /**
     * @brief  高亮网格
     * @param  k
     */
    void highLighKernel(IdType meshID);
    /**
     * @brief  高亮网格组件
     * @param  set   网格组件
     */
    // void highLighMeshSet(MeshData::MeshSet *set);
    /**
     * @brief 清除高亮
     */
    void clearHighLight();
    /**
     * @brief 更新网格组件的显示状态
     * @param  set  需要更新的网格组件
     */
    // void updateMeshSetVisibily(MeshData::MeshSet *set);
    /**
     * @brief 更新网格组件颜色
     * @param  set  需要更新的网格组件id
     */
    // void updateMeshSetColor(int setid);
    
private:
    /**
     * @brief 移除显示对象，窗口将不再显示
     * @param  kernal     要移除显示的Kernal
     */
    void removeDisplay(IdType meshID);
    /**
     * @brief  根据显示层数据获取到View Object
     * @param  data    用于渲染的dataset
     * @return MeshKernalViewObj*  date对应的ViewObject
     */
    FCMeshViewObject *getViewObjByDisplayDataSet(vtkDataSet *data);
    
private:
    /**
     * @brief 前处理窗口
     */
    // PreWindow *_preWindow{};
    /**
     * @brief 主窗口
     */
    // GUI::MainWindow *_mainWindow{};
    FCGraphViewWindow* mGraphViewWindow;
    
    /**
     * @brief 网格数据
     */
    FCMeshData *mMeshData{};
    /**
     * @brief 显示对象数据管理hash
     */
    QHash<FCMeshKernal *, FCMeshViewObject *> mViewObjects{};
    
    /**
     * @brief 显示对象数据管理hash
     */
    QHash<IdType, FCMeshViewObject *> mMeshViewObjects{};
    /**
     * @brief 交互拾取模式
     */
    // ModuleBase::SelectModel _selectModel{ModuleBase::None};
    /**
     * @brief 临时记录网格组件高亮对象
     */
    // MeshData::MeshSet *_highLightSet{nullptr};
    /**
     * @brief 高亮的交互选取的对象
     */
    QMultiHash<int, int> mHighLightSelectItems{};
    /**
     * @brief 是否应该显示网格（用于控制网格的可见性）
     */
    bool mMeshShouldBeVisible{true};
};
} // namespace FC



#endif // FCMESHVIEWPROVIDER_H
