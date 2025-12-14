/**
 * @file FCPostProcessingViewProvider.h
 * @brief 后处理可视化管理器
 * @date 2025-12-15
 * @version V0.0.1
 * @details 
 * @copyright Copyright (c) 2025 Kinvy. All rights reserved.
 */
#ifndef FCPOSTPROCESSINGVIEWPROVIDER_H
#define FCPOSTPROCESSINGVIEWPROVIDER_H
#include "FCGraphicsViewGlobal.h"
#include <QObject>
#include <QHash>

class vtkActor;

namespace FC 
{

class FCGraphViewWindow;
class FCPostProcessingKernal;
class FCPostProcessingData;
class FCPostProcessingViewObject;

class FCGRAPHICSVIEW_API FCPostProcessingViewProvider : public QObject
{
    Q_OBJECT
public:
    using IdType  = uint64_t;  ///< id类型  
public:
    /**
     * @brief Construct a new PostProcessing View Provider object
     * @param  viewWindow       图形窗口
     */
    FCPostProcessingViewProvider(FCGraphViewWindow* viewWindow, QObject *parent = nullptr);
    /**
     * @brief Destroy the PostProcessing View Provider object
     */
    ~FCPostProcessingViewProvider();
    /**
     * @brief 更新显示模式
     * @param  postID   后处理ID
     */
    void updateDisplayModel(IdType postID);
    /**
     * @brief 更新颜色等渲染选项
     * @param  postID   后处理ID
     */
    void updateGraphOption(IdType postID);
    /**
     * @brief   是否显示Kernal
     * @param  postID     后处理ID
     * @param  show  是否显示
     */
    void showPostProcessing(IdType postID, bool show);
    /**
     * @brief 隐藏/显示所有后处理
     * @param visible 是否可见
     */
    void setAllPostProcessingVisible(bool visible);
    /**
     * @brief 高亮交互拾取的对象
     * @param  items    交互拾取的对象
     */
    void highLighSelectItem(QMultiHash<int, int> *items);
    
    void removePostProcessingActor(IdType postID);
    
    /**
     * @brief 获取后处理ViewObject
     * @param postID 后处理ID
     * @return FCPostProcessingViewObject* ViewObject指针，如果不存在返回nullptr
     */
    FCPostProcessingViewObject* getViewObject(IdType postID);
    
public slots:
    /**
     * @brief 新建或者删除后处理，更新显示
     */
    void updatePostProcessingActorSlot();
    
    void showPostProcessingSlot(IdType postID, bool r = true);
    
private slots:
    /**
     * @brief  高亮后处理
     * @param  postID
     */
    void highLighKernel(IdType postID);
    /**
     * @brief 清除高亮
     */
    void clearHighLight();
    
private:
    /**
     * @brief 移除显示对象，窗口将不再显示
     * @param  postID     要移除显示的后处理ID
     */
    void removeDisplay(IdType postID);
    
private:
    /**
     * @brief 图形窗口
     */
    FCGraphViewWindow* mGraphViewWindow;
    
    /**
     * @brief 后处理数据
     */
    FCPostProcessingData *mPostProcessingData{};
    /**
     * @brief 显示对象数据管理hash
     */
    QHash<IdType, FCPostProcessingViewObject *> mPostProcessingViewObjects{};
};

} // namespace FC

#endif // FCPOSTPROCESSINGVIEWPROVIDER_H

