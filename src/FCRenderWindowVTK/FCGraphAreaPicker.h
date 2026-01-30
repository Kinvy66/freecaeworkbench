/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

/**
 * 
 * @file FCGraphAreaPicker.h
 * @brief VTK框选功能接口声明
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-19
 * 
 */
#ifndef _FCGraphAreaPicker_H_
#define _FCGraphAreaPicker_H_

#include <vtkSmartPointer.h>
#include "FCRenderWindowVTKAPI.h"
#include <vtkPolyData.h>
#include <vtkActor2D.h>

class vtkRenderer;
// class vtkActor2D;
// class vtkPolyData;

namespace Comp
{
    class FCGraphInteractionStyle;
    /**
     * @brief VTK框选功能接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-19
     */
    class FCRENDERWINDOWVTK_API  FCGraphAreaPicker
    {
    public:
        /**
         * @brief Construct a new FCGraphAreaPicker object
         * @param[i]  style          交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FCGraphAreaPicker(FCGraphInteractionStyle* style);
        /**
         * @brief Destroy the FCGraphAreaPicker object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        ~FCGraphAreaPicker();
        /**
         * @brief 记录左键点击位置
         * @param[i]  pos            位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setLeftButtonDownPos(int* pos);
        /**
         * @brief 设置框选的渲染图层
         * @param[i]  render         渲染图层对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setPickerRender(vtkRenderer* render);
        /**
         * @brief 设置框选是否激活
         * @param[i]  state             状态
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void enable(bool state = true);
        /**
         * @brief 获取是否激活状态
         * @return bool
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        bool isEnable();
        /**
         * @brief 绘制框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void drawRectangle();
        /**
         * @brief 
         * @param[i]  state             状态
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void pick();

        /**
         * @brief       设置形状颜色。
         * @param[in]   rf：红
         * @param[in]   gf：绿
         * @param[in]   bf：蓝
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-07-10
         */
        void setColor(double rf, double gf, double bf);

    private:
        /**  
         * @brief 初始化框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void initRectangle();
        /**
         * @brief 更新框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void updateRectangle();
    private:
        /**
         * @brief 交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FCGraphInteractionStyle* m_style = nullptr;
        /**
         * @brief 框选图层
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkRenderer* m_render = nullptr;
        /**
         * @brief 鼠标起始位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        int m_startPos[2] = { 0,0 };
        /**
         * @brief 鼠标终止位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        int m_endPos[2] = { 0,0 };
        /**
         * @brief 框选选框数据
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkSmartPointer<vtkPolyData> m_pickData = nullptr;
        /**
         * @brief 框选选框对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkSmartPointer<vtkActor2D> m_pickActor = nullptr;

        /**
         * @brief       形状颜色。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-07-10
         */
        double m_color3[3]{ 1., 1., 1. };

    };
}

#endif
