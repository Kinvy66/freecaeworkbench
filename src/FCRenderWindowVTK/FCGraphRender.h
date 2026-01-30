/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 * 
 * @file FCGraphRender.h
 * @brief 渲染场景接口声明
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-14
 * 
 */
#ifndef _FCGraphRender_H_
#define _FCGraphRender_H_

#include "FCRenderWindowVTKAPI.h"
#include <QObject>
#include <QMutex>

class vtkRenderer;
class vtkRenderWindow;

namespace Core
{
    class FITKGraphObjectManager;
    class FITKGraphObjManager;
}

namespace Comp
{
    class FCGraphObjectVTK;
    class FCGraph3DWindowVTK;
 //   class FITKGraphObjectManager;
    /**
     * @brief 渲染场景接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-14
     */
    class FCRENDERWINDOWVTK_API FCGraphRender :public QObject
    {
        Q_OBJECT;
    public:
        /**
         * @brief Construct a new FITKCompRender object
         * @param[i]  renderWin      三维渲染窗口
         * @param[i]  type           渲染场景类型
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        FCGraphRender(FCGraph3DWindowVTK* graphWin, vtkRenderer* ren = nullptr);
        /**
         * @brief Destroy the FCGraphRender object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        virtual ~FCGraphRender();
        /**
         * @brief 添加渲染对象
         * @param[i]  object         渲染对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void addObject(FCGraphObjectVTK* object);

        /**
         * @brief 移除渲染对象
         * @param[i]  object         渲染对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        void removeObject(FCGraphObjectVTK* object);
        /**
         * @brief 获得渲染场景
         * @return vtkRenderer* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        vtkRenderer* getRenderer();
        /**
         * @brief    获取渲染数据管理器
         * @return   Core::FITKGraphObjManager*      渲染数据管理器
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-09
         */
        Core::FITKGraphObjManager* getGraphObjManager();
        /**
         * @brief 获取actor的边界
         * @param[o]  bound          边界
         * @return double            边界对角线长度，错误值<0
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        double getActorBounds(double* bound);
        /**
         * @brief 获取渲染对象数量
         * @return int
         * @author Libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-26
         */
        int getGraphObjectCount();
        /**
         * @brief 清空所有对象（只清空不删除对象）
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-28
         */
        void clear();
        /**
        * @brief 设置背景颜色
        * @param[i]  rgb1              顶部颜色
        * @param[i]  rgb2              底部颜色
        * @author libaojun (libaojunqd@foxmail.com)
        * @date 2024-05-08
        */
        void setBackgroundColor(float* rgb1, float* rgb2 = nullptr);

    private:

        FCGraph3DWindowVTK* _graphWidget{};

        /**
         * @brief 渲染场景
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-11
         */
        vtkRenderer* m_renderer = nullptr;
        /**
         * @brief 渲染对象管理类接口
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-22
         */
        Core::FITKGraphObjManager* m_objectManager = nullptr;
    };
}

#endif