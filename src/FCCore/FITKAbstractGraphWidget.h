/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 *
 * @file FCGraphWidget.h
 * @brief 渲染窗口抽象类
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-04-08
 *
 */
#ifndef FCGraphWidget_H_
#define FCGraphWidget_H_

#include "FCCoreAPI.h"
#include <QWidget>

namespace Core
{
    class FCAbstractGraphObject;

    /**
     * @brief 渲染窗口抽象类
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-04-08
     */
    class FCCORE_API FCAbstractGraphWidget :public QWidget
    {
    public:
        explicit FCAbstractGraphWidget(QWidget* parent = nullptr);
        /**
         * @brief Destroy the FCGraphWidget object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-08
         */
        virtual ~FCAbstractGraphWidget() = 0 ;
       
        /**
         * @brief 清空所有显示对象（不删除对象）
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        virtual void clear();
     
        /**
         * @brief 保存当前渲染窗口为图片
         * @param[i]  image          图片路径
         * @param[i]  w              图片宽度
         * @param[i]  h              图片高度
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-11
         */
        virtual void saveImage(const QString& image, int w = -1, int h = -1);
        /**
         * @brief 适应窗口大小
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        virtual void fitView();
        /**
         * @brief 设置背景颜色 
         * @param[i]  rgb1              顶部颜色
         * @param[i]  rgb2              底部颜色，空指针则只有rgb1颜色生效
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        virtual void setBackgroundColor(float* rgb1, float* rgb2 = nullptr);

        /**
         * @brief 设置背景颜色
         * @param[o]  rgb1              顶部颜色
         * @param[o]  rgb2              底部颜色
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        virtual void getBackgroundColor(float* rgb1, float* rgb2 = nullptr);

        /**
         * @brief 从渲染窗口移除渲染对象
         * @param[i]  FCAbstractGraphObject    移除的渲染对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-11
         */
        virtual void removeGraphObj(FCAbstractGraphObject* gobj);
        /**
         * @brief 获取窗口ID，与widget的id无关
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int getGraphWidgetID() const;

    private:
        /**
         * @brief 窗口ID
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int _graphWidgetID{ -1 };
    };


    enum FCGraph3DStandardView
    {
        F3DVXPos,
        F3DVXNeg,
        F3DVYPos,
        F3DVYNeg,
        F3DVZPos,
        F3DVZNeg,
        F3DVISO,
    };



    /**
  * @brief 三维渲染窗口抽象类
  * @author libaojun (libaojunqd@foxmail.com)
  * @date 2024-04-08
  */
    class FCCORE_API FCAbstractGraph3DWidget : public FCAbstractGraphWidget
    {
    public:
        using FCAbstractGraphWidget::FCAbstractGraphWidget;
        virtual ~FCAbstractGraph3DWidget() = 0 ;

        /**
        * @brief 设置相机视角
        * @param[i]  focalPoint     相机焦点三坐标
        * @param[i]  viewUp         相机向上方向三坐标
        * @param[i]  position       相机位置三坐标
        * @author libaojun (libaojunqd@foxmail.com)
        * @date 2024-03-14
        */
        virtual void setView(double* focalPoint, double* viewUp, double* position);
        /**
        * @brief 设置相机视角
        * @param[i] v     标准视角 
        * @author libaojun (libaojunqd@foxmail.com)
        * @date 2024-06-13
        */
        virtual void setView(FCGraph3DStandardView v);
        /**
         * @brief 获取当前相机视角
         * @param[o]  pos            相机位置三坐标
         * @param[o]  focual         相机焦点三坐标
         * @param[o]  viewup         相机向上方向三坐标
         * @return true 获取成功
         * @return false 获取失败
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-08
         */
        virtual bool getView(double* pos, double* focual, double* viewup);

        /**
       * @brief 设置是否为平行投影
       * @param[i]   on   是否打开
       * @author libaojun (libaojunqd@foxmail.com)
       * @date 2024-03-14
       */
        virtual void setParallelProjection(bool on = true);

        /**
         * @brief       设置相机视野包围盒。[虚函数]
         * @param[in]   bds：包围盒
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-12-11
         */
        virtual void setViewBounds(double* bds) { Q_UNUSED(bds); };
    };

    /**
    * @brief 二维渲染窗口抽象类
    * @author libaojun (libaojunqd@foxmail.com)
    * @date 2024-04-08
    */
    class FCCoreAPI FCAbstractGraph2DWidget : public FCAbstractGraphWidget
    {
    public:
        using FCAbstractGraphWidget::FCAbstractGraphWidget;
        virtual ~FCAbstractGraph2DWidget() = 0 ;
    };
}

#endif

