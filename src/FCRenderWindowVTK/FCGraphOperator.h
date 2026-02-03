/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 * 
 * @file FCGraphOperator.h
 * @brief 绘图控制器接口声明 
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-14
 * 
 */
#ifndef _FCGraphOperator_H_
#define _FCGraphOperator_H_

#include "FCAbstractOperator.h"
#include "FCRenderWindowVTKAPI.h"

namespace Comp
{
    class FITKGraphObject;
    class FCGraph3DWindowVTK;
    /**
     * @brief 绘图控制器
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-14
     */
    class FCRENDERWINDOWVTK_API FCGraphOperator :public Core::FITKAbstractOperator
    {
    public:
        /**
         * @brief Construct a new FCGraphOperator object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        FCGraphOperator();
        /**
         * @brief Destroy the FCGraphOperator object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual ~FCGraphOperator() = 0;
        /**
         * @brief 设置绘图操作器对应的渲染窗口
         * @param[i]  w              渲染窗口对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void setGraph3DWindow(FCGraph3DWindowVTK* w);
        /**
         * @brief 获取对应的渲染窗口对象
         * @return FCGraph3DWindowVTK* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCGraph3DWindowVTK* getGraph3DWindow();
    protected:
        /**
         * @brief 渲染窗口对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FCGraph3DWindowVTK* m_graph3DWindow = nullptr;
    };
}

#endif
