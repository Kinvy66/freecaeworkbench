/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 * 
 * @file FCGraph3DWindowVTK.h
 * @brief 三维渲染窗口接口声明 
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-14
 * 
 */
#ifndef _FCGraph3D_H_VTK_
#define _FCGraph3D_H_VTK_

#include "FCRenderWindowVTKAPI.h"
#include "FCGraph3DWindowInterface.h"
#include "FCAbstractGraphWidget.h"

#include <QWidget>
#include <QMutex>
#include <QVariant>
#include <QTimer>

class vtkRenderWindow;
class vtkCamera;
class vtkRenderWindowInteractor;
class vtkOrientationMarkerWidget;
class vtkActor;
class vtkRenderer;
class QGridLayout;
class QToolBar;

class FCLegendScaleActor;


namespace Ui 
{
    class FCGraph3DWindowVTK;
}

namespace FC
{
    class FCGraphRender;
    class FCGraphObjectVTK;
    class FCGraphInteractionStyle;
    class FCBoundaryActor;
    class Graph3DWindowInitializer;
    /**
     * @brief 三维渲染窗口toolbar位置枚举
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-06-05
     */
    enum class FCGraphWinToolBarPos
    {
        FCLeftTop = 1,       ///1：左侧顶部
        FCLeftCenter,        ///2：左侧中部          
        FCLeftBottom,        ///3：左侧底部
        FCBottomCenter,      ///4：底部中间
        FCRightBottom,       ///5：右侧底部  
        FCRightCenter,       ///6：右侧中部
        FCRightTop,          ///7：右侧顶部 
        FCTopCenter,         ///8：顶部中间
    };
    /**
     * @brief  三维渲染窗口图片类型
     * @author BaGuijun (baguijun@163.com)
     * @date   2024-10-24
     */
    enum class FCGraphWinImageType
    {
        FC_PNG = 0,
        FC_JPEG,
        FC_TIFF,
        FC_BMP,
        FC_SVG,
    };
    /**
     * @brief 三维渲染窗口接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-14
     */
    class FCRENDERWINDOWVTK_API FCGraph3DWindowVTK 
        : public Core::FCAbstractGraph3DWidget
    {
        Q_OBJECT;
    public:
        /**
         * @brief Construct a new FCGraph3DWindow object
         * @param[i]  info           渲染窗口信息
         * @param[i]  gInterface     渲染窗口对应接口类
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCGraph3DWindowVTK(Graph3DWindowInitializer * initializer);
        /**
         * @brief Destroy the FCGraph3DWindow object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual ~FCGraph3DWindowVTK();

        /**
         * @brief       设置隐藏不可见线框模式。
         * @param[in]   flag：是否开启
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-07-22
         */
        void setHiddenLineRemoval(bool flag);

        /**
         * @brief       获取隐藏不可见线框模式开启状态。
         * @return      是否开启
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-07-22
         */
        bool getHiddenLineRemoval();

        /**
         * @brief 强制刷新
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void reRender();
        /**
         * @brief 设置坐标系状态
         * @param[i]  state          ture显示，false隐藏
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void setAxesEnable(bool state);

        /**
         * @brief       以动画模式切换视角。
         * @param[in]   focalPoint：相机焦点
         * @param[in]   viewUp：相机向上方向
         * @param[in]   position：相机位置
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        void setViewAnime(double* focalPoint, double* viewUp, double* position);

        /**
         * @brief 设置相机视角
         * @param[i]  focalPoint     相机焦点三坐标
         * @param[i]  viewUp         相机向上方向三坐标
         * @param[i]  position       相机位置三坐标
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void setView(double* focalPoint, double* viewUp, double* position) override;
        
        /**
         * @brief 设置默认的初始化相机视角
         * @param[i]  focalPoint     相机焦点三坐标
         * @param[i]  viewUp         相机向上方向三坐标
         * @param[i]  position       相机位置三坐标
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-11-21
         */
        void setDefaultView(double* focalPoint, double* viewUp, double* position);
        
        /**
         * @brief 设置ISO相机视角
         * @param[i]  focalPoint     相机焦点三坐标
         * @param[i]  viewUp         相机向上方向三坐标
         * @param[i]  position       相机位置三坐标
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-11-21
         */
        void setISOView(double* focalPoint, double* viewUp, double* position);
        /**
         * @brief 获取当前相机视角
         * @param[o]  pos            相机位置三坐标
         * @param[o]  focual         相机焦点三坐标
         * @param[o]  viewup         相机向上方向三坐标
         * @return true 获取成功
         * @return false 获取失败
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-04-08
         */
        bool getView(double* pos, double* focual, double* viewup) override;

        /**
         * @brief       设置相机视野包围盒。[重写]
         * @param[in]   bds：包围盒
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-11
         */
        void setViewBounds(double* bds) override;

        /**
         * @brief       快速添加可视化对象。（无视相机视角与对象包围盒计算）
         * 
         *              P.S. 
         *              仅在大批量对象添加时使用。
         * 
         * @param[in]   index：渲染层索引
         * @param[in]   object：可视化对象
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-11-15
         */
        void fastAddObject(int index, FCGraphObjectVTK* object);

        /**
         * @brief 添加渲染对象
         * @param[i]  index          渲染图层索引值
         * @param[i]  object         渲染对象
         * @param[i]  fitview        是否自适应(仅在窗口为空时生效)
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void addObject(int index, FCGraphObjectVTK* object, bool fitview = true);
        /**
         * @brief    获取所有的渲染数据
         * @return   QList<FCGraphObjectVTK*>          全部渲染数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        QList<FCGraphObjectVTK*> getAllGraphObj();
        /**
         * @brief 清空所有显示对象（不删除对象）
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-28
         */
        void clear() override;
        /**
         * @brief 设置渲染图层背景颜色
         * @param[i]  topValue       顶部颜色
         * @param[i]  bottomValue    底部颜色
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void setBackground(double topValue[3],double bottomValue[3]);
        /**
         * @brief 自适应对象大小
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void fitView() override;
        /**
         * @brief 强制刷新窗口
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        virtual void flush() override;

        /**
         * @brief 设置背景颜色
         * @param[i]  rgb1              顶部颜色
         * @param[i]  rgb2              底部颜色
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        virtual void setBackgroundColor(float* rgb1, float* rgb2 =nullptr) override;
        /**
         * @brief 获取背景颜色
         * @param[o]  rgb1              顶部颜色
         * @param[o]  rgb2              底部颜色
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual void getBackgroundColor(float* rgb1, float* rgb2 = nullptr) override;
        /**
         * @brief 根据索引获取渲染图层
         * @param[i]  index          渲染图层索引值
         * @return FCGraphRender* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FCGraphRender* getRenderer(int index);

        /**
         * @brief 获取渲染图层数目
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        int getRenderCount();

        /**
         * @brief 获取vtk渲染窗口
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        vtkRenderWindow* getVTKRenderWindow();

        /**
         * @brief       获取三维窗口相机。
         * @return      相机
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-17
         */
        vtkCamera* getVTKCamera();

        /**
         * @brief       获取三维渲染器。
         * @return      渲染器索引（-1代表最后一个）[默认值]
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-17
         */
        vtkRenderer* getVTKRenderer(int index = -1);
        
        /**
         * @brief 设置是否平行投影
         * @param[i]  enable         是否激活
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-04-08
         */
        virtual void setParallelProjection(bool on = true) override;

        /**
         * @brief 获取是否平行投影
         * @return  是否激活
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-04-08
         */
        virtual bool getParallelProjection();

        /**
         * @brief 从渲染窗口移除渲染对象
         * @param[i]  FCAbstractGraphObject    移除的渲染对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-11
         */
        void removeGraphObj(Core::FCAbstractGraphObject* gobj) override;

        /**
         * @brief 获取渲染对象数量
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-26
         */
        int getGraphObjCount();
        /**
         * @brief 获取渲染对象中心
         * @param[o] center[3] 渲染对象中心 
         * @return bool
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-26
         */
        bool getGraphObjCenter(double* center);

        /**
         * @brief       设置用户自定义信息。[模板]
         * @param[in]   info：窗口信息（可以传入结构体或指针）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-11
         */
        template<class T>
        void setUserInformation(T info)
        {
            m_userInfo = QVariant::fromValue(info);
        }

        /**
         * @brief       获取用户自定义信息。[模板]
         * @return      窗口信息（支持结构体或指针）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-11
         */
        template<class T>
        T getUserInformationAs()
        {
            return m_userInfo.value<T>();
        }

        /**
         * @brief       设置用户自定义信息。
         * @param[in]   info：窗口信息（可以传入结构体或指针）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-11
         */
        void setUserInformation(QVariant info);

        /**
         * @brief       获取用户自定义信息。
         * @return      窗口信息（支持结构体或指针）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-11
         */
        QVariant getUserInformation();
       /**
        * @brief 保存当前渲染窗口为图片
        * @param[i]  image          图片路径
        * @param[i]  w              图片宽度
        * @param[i]  h              图片高度
        * @author BaGuijun (baguijun@163.com)
        * @date 2024-05-28
        */
        virtual void saveImage(const QString& image, int w = -1, int h = -1)override;

        /**
         * @brief       显示/隐藏比例尺图例。
         * @param[in]   visibility：可见性
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-29
         */
        void showScaleLegend(bool visibility);
        /**
        * @brief 渲染窗口工具栏中添加action
        * @param[i]  actions         action列表
        * @param[i]  beforeActions   插入action的位置
        * @author BaGuijun (baguijun@163.com)
        * @date 2024-06-04
        */
        void addActionsToolBar(QList<QAction*> actions, QAction* beforeAction = nullptr);
        /**
        * @brief 设置工具栏位置
        * @param[i]  pos          工具栏位置
        * 1：左顶 2：左中 3：左底 4：底部 5：右底  6：右中 7：右上 8：顶部
        * @author BaGuijun (baguijun@163.com)
        * @date 2024-06-04
        */
        void setToolBarPos(FCGraphWinToolBarPos pos);
        /**
        * @brief 设置渲染窗口的图标(可多次调用切换图标与图标位置)
        * 图标的位置只在左侧顶部、左侧底部、右侧底部、右侧顶部有效
        * @param[i]  iconPath        图片路径
        * @author BaGuijun (baguijun@163.com)
        * @date 2024-06-05
        */
        void initRenderIcon(const QPixmap& image, FCGraphWinToolBarPos pos = FCGraphWinToolBarPos::FCRightTop);
        /**
         * @brief 获取渲染窗口中默认的actions
         * @return QList<QAction*> actio列表
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        QList<QAction*> getActions();
        /**
         * @brief 设置渲染窗口中的action是否显示
         * @param[i]  isShow         是否显示
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        void setIsShowActions(bool isShow);
        /**
         * @brief    设置是否显示裁切按钮（该功能仅在setIsShowActions为true时有效）
         * @param[i] isShow              是否显示
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        void setIsShowClipAction(bool isShow);
        /**
         * @brief       刷新边界演员包围盒。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-07-11
         */
        void updateBoundary();

        /**
         * @brief       获取当前三维窗口渲染包围盒尺寸。
         * @param[in]   bds：包围盒尺寸
         * @return      包围盒是否有效
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-07-14
         */
        bool getBoundray(double* bds);

        /**
         * @brief    设置是否开启VTK警告（默认开启）
         * @param[i] isOpen                   是否开启
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-01-22
         */
        void SetGlobalWarningDisplay(bool isOpen);
        /**
         * @brief    设置是否开启深度剥离
         * @param[i] isOpen                     是否开启
         * @param[i] peelMaxNum                 剥离最大数
         * @param[i] renderIndex                所要剥离的渲染层索引（-1：为全部渲染层）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-05-29
         */
        void SetUseDepthPeeling(bool isOpen, int peelMaxNum, int renderIndex = -1);
        /**
         * @brief    获取渲染交互器
         * @return   FCGraphInteractionStyle*        渲染交互器
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-02
         */
        FCGraphInteractionStyle* getGraphInteractionStyle();
    public slots:
       
        /**
         * @brief 前视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewFrontEvent();
        /**
         * @brief 后视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewBackEvent();
        /**
         * @brief 顶部视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewTopEvent();
        /**
         * @brief 底部视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewBottomEvent();
        /**
         * @brief 左视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewLeftEvent();
        /**
         * @brief 右视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewRightEvent();
        /**
         * @brief 正视角按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewIsoEvent();
        /**
         * @brief 自适应按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewPanEvent();
        /**
         * @brief 保存图片按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionSaveImageEvent();
        /**
         * @brief 平行投影按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewParallelEvent();
        /**
         * @brief 正交投影按钮事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-13
         */
        virtual void slotActionViewPerspectiveEvent();
        /**
         * @brief    裁切按钮事件
         * @param[i] isCreateNewModel               是否产生新模型[缺省]
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-18
         */
        virtual void slotActionClipEvent(bool isCreateNewModel = true);
    protected:
        /**
         * @brief 渲染窗口初始化
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual void init();
        /**
         * @brief 渲染窗口action初始化
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual void initActions();
        /**
         * @brief 设置交互器
         * @param[i]  style          交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void setInteractionStyle(FCGraphInteractionStyle* style);

        /**
         * @brief       初始化显示属性。
         * @param[in]   event：窗口显示事件
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-28
         */
        virtual void showEvent(QShowEvent* event) override;

    private:
        /**
         * @brief       开启视角切换动画。
         * @param[in]   foc：相机焦点
         * @param[in]   up：相机向上方向
         * @param[in]   pos：相机位置
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        void startChangingView(double* foc, double* up, double* pos);

    private slots:
        /**
         * @brief       槽函数 - 动画视角切换。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        void slot_changingView();

    protected:
        /**
         * @brief 渲染窗口信息对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        Graph3DWindowInitializer* _initializer{};
     
        /**
         * @brief 三维渲染界面对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        Ui::FCGraph3DWindowVTK* m_ui = nullptr;
        /**
         * @brief VTK界面
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        QWidget* m_vtkWidget = nullptr;
        /**
         * @brief       三维比例尺。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-28
         */
        FCLegendScaleActor* m_legendScaleActor{ nullptr };

        /**
         * @brief 三维渲染交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        vtkRenderWindowInteractor* m_interactor = nullptr;
        /**
         * @brief 三维渲染窗口对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
//#if VTK_MAJOR_VERSION >= 8
        vtkRenderWindow* m_renderWindow = nullptr;
//#else
//        vtkGenericOpenGLRenderWindow* m_renderWindow = nullptr;
//#endif
        
        /**
         * @brief 三维渲染相机对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        vtkCamera* m_camera = nullptr;
        /**
         * @brief 三维渲染坐标系对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        vtkOrientationMarkerWidget* m_axesWidget = nullptr;
        /**
         * @brief 三维渲染图层链表
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        QHash<int, FCGraphRender*> m_renders = {};
        /**
         * @brief 交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCGraphInteractionStyle* m_interactionStyle = nullptr;
        /**
         * @brief 渲染窗口边界对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCBoundaryActor* m_actorBound = nullptr;

        /**
         * @brief       用户自定义数据。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-11
         */
        QVariant m_userInfo;

        /**
         * @brief       窗口是否初始化。（适应低版本VTK，在showEvent内对某些演员与视角进行初始化与刷新）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-05-29
         */
        bool m_initFlag = false;
        /**
         * @brief 渲染窗口布局对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        QGridLayout* _renderToolBarLayout = nullptr;
        /**
         * @brief 渲染窗口工具栏对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        QToolBar* _renderToolBar = nullptr;
        /**
         * @brief 渲染窗口图标工具栏对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        QToolBar* _renderIconToolBar = nullptr;
        /**
         * @brief 渲染窗口布局类型
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCGraphWinToolBarPos _renderBarStyle = FCGraphWinToolBarPos::FCLeftTop;
        /**
         * @brief  渲染窗口图片类型
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-10-24
         */
        FCGraphWinImageType _imageType = FCGraphWinImageType::FC_PNG;

        /**
         * @brief  默认初始化视角
         * @author libaojun (libaojunqd@foxmail.com)
         * @date   2024-11-21
         */
        double _defFp[3] = { 0,0,0 }, _defVp[3] = { 0,1,0 }, _defPos[3] = { 1,1,1 };
        /**
         * @brief  ISO视角
         * @author libaojun (libaojunqd@foxmail.com)
         * @date   2024-11-21
         */
        double _ISOFp[3] = { 1,1,1 }, _ISOVp[3] = { 0,0,0 }, _ISOPos[3] = { 0,1,0 };

    private:
        /**
         * @brief 互斥锁对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-06-06
         */
        static QMutex _mutex;

        // 视角切换动画。
        //@{
        /**
         * @brief       视角切换定时器。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        QTimer m_timerView;

        /**
         * @brief       视角切换总时间步。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        int m_viewStep = 50;

        /**
         * @brief       当前时间步。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        int m_currStep = 0;

        /**
         * @brief       时间步长度。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        int m_interval = 10;

        /**
         * @brief       目标位置。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        double m_tarPos3[3]{ 0., 0., 0. };

        /**
         * @brief       目标向上方向。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        double m_tarUp3[3]{ 0., 0., 0. };

        /**
         * @brief       目标焦点。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-12
         */
        double m_tarFoc3[3]{ 0., 0., 0. };
        //@}

    };
}
#endif
