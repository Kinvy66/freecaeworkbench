/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 *
 * @file FCGraph3DWindowInterface.h
 * @brief 三维渲染窗口组件接口
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-14
 *
 */
#ifndef _FCGraph3DWindowInterface_H_
#define _FCGraph3DWindowInterface_H_

#include "FCRenderWindowVTKAPI.h"
#include "FCComponentInterface.h"
#include "FCVarientParams.h"
#include <functional>
#include <QHash>

//定义字符串
#define  VTKRENDERLAYER  "VTKRENDERLAYER"
#define  BackGroundColorTop "BackGroundColorTop"
#define  BackGroundColorButtom "BackGroundColorButtom"

namespace FC
{
    /**
     * @brief       解决重叠几何方法。
     * @author      ChengHaotian (yeguangbaozi@foxmail.com)
     * @date        2025-08-21
     */
    enum ResolveCoincidentType
    {
        RCT_Off = -1,
        RCT_Default = 0,
        RCT_PolygonOffset,
        RCT_ShiftZBuffer
    };

    class FCGraphInteractionStyle;
    /**
     * @brief 渲染窗口信息
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-18
     */
    class FCRENDERWINDOWVTK_API Graph3DWindowInitializer : public FCVarientParams
    {
    public:
        explicit Graph3DWindowInitializer() = default;
        virtual ~Graph3DWindowInitializer() = default;
        /**
         * @brief 获取交互器
         * @return FCGraphInteractionStyle*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        virtual  FCGraphInteractionStyle* getStyle();
        /**
         * @brief 设置渲染器层数
         * @param[i]  nc         渲染器层数
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        void setLayerCount(const int nc );
        /**
         * @brief 获取渲染层数
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int getLayerCount() const;

    private:
        /**
         * @brief 渲染层数
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int _layerCount{ 3 };


    };


    /**
     * @brief 三维渲染窗口组件接口
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-12
     */
    class FCRENDERWINDOWVTK_API FCGraph3DWindowInterface :public FCComponentInterface
    {
    public:
        /**
         * @brief Construct a new FCGraph3DWindowInterface object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        FCGraph3DWindowInterface() = default;
        /**
         * @brief Destroy the FCGraph3DWindowComp object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        virtual ~FCGraph3DWindowInterface();
        /**
       * @brief 检查系统状态
       * @return QString 返回系统错误信息，如果为空则表示正常
       * @author libaojun
       * @date 2025-03-25
       */
        static QString CheckSystem();

        /**
         * @brief 获取三维渲染界面
         * @param[i]  indexPort      索引值（参数无效）
         * @return QWidget*
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        QWidget* getWidget(const int indexPort)override;
        /**
         * @brief 获取组件名称
         * @return QString
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        QString getComponentName();
        /**
         * @brief 添加渲染窗口相关信息
         * @param[i]  key            索引值
         * @param[i]  info           窗口信息
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void addInitializer(int key, Graph3DWindowInitializer* info);

        /**
         * @brief       设置全局处理重叠拓扑方式。[静态]
         * @param[in]   type：方式
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-08-21
         */
        static void SetResolveCoincidentType(ResolveCoincidentType type);

    private:
        /**
         * @brief 三维渲染窗口信息链表
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        QHash<int, Graph3DWindowInitializer*> _initilizerList{};

    };
}

#endif
