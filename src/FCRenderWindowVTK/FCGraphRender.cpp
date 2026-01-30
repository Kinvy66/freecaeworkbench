/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraphRender.h"
#include "FCGraphObjectVTK.h"
#include "FCGraph3DWindowVTK.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkInteractorObserver.h>
#include <vtkCubeAxesActor.h>

namespace Comp
{

    FCGraphRender::FCGraphRender(FCGraph3DWindowVTK * gw/*, int type*/, vtkRenderer* ren)
        :_graphWidget(gw)
    {
        if (_graphWidget == nullptr) return;
        //创建渲染对象管理类
        m_objectManager = new Core::FITKGraphObjManager();

        //渲染图层初始化
        if (ren)
        {
            m_renderer = ren;
        }
        else
        {
            m_renderer = vtkRenderer::New();
        }

        m_renderer->SetBackground(1.0, 1.0, 1.0);
        m_renderer->SetBackground2(0.5, 0.8, 0.9);
        m_renderer->SetGradientBackground(true);
        m_renderer->InteractiveOn();

        //三维渲染窗口中添加渲染图层
        auto renderWin = _graphWidget->getVTKRenderWindow();
        if (renderWin != nullptr)
            renderWin->AddRenderer(m_renderer);
    }

    FCGraphRender::~FCGraphRender()
    {
        //渲染图层中的actor移除
        this->clear();
        //释放管理类
        if (m_objectManager) 
            delete m_objectManager; 
        if (m_renderer != nullptr)
            m_renderer->Delete(); 
        
    }

    void FCGraphRender::addObject(FCGraphObjectVTK * object)
    {
        
        //渲染图层添加渲染对象
        if (object == nullptr)return;
        //对象管理
        m_objectManager->appendGraphObj(object);

        object->setGraphWidget(_graphWidget);
        const int nact = object->getActorCount();
        if (m_renderer == nullptr) return;

        vtkCamera* c = m_renderer->GetActiveCamera();

        //显示层
        for (int i = 0; i < nact; i++)
        {
            auto act = object->getActor(i);
            if(act == nullptr) continue;

            //特殊类型处理
            vtkCubeAxesActor* cubeAxes = vtkCubeAxesActor::SafeDownCast(act);
            if (cubeAxes)
            {
                cubeAxes->SetCamera(c);
               // cubeAxes->

            }
               

            m_renderer->AddViewProp(act);
           
        } 
    }

    void FCGraphRender::removeObject(FCGraphObjectVTK* gobj)
    {
        if (gobj == nullptr || !m_objectManager->isContains(gobj)) return;
        if (gobj == nullptr) return;
        //清除记录
        gobj->setGraphWidget(nullptr);
        const int nact = gobj->getActorCount();
        if (m_renderer == nullptr) return;
        //显示层移除
        for (int i = 0; i < nact; i++)
        {
            auto act = gobj->getActor(i);
            m_renderer->RemoveViewProp(gobj->getActor(i));
        }

        // 移除控件。
        //@{
        int nWidget = gobj->getWidgetCount();
        for (int i = 0; i < nWidget; i++)
        {
            vtkInteractorObserver* widget = gobj->getWidget(i);
            if (widget)
            {
                widget->SetDefaultRenderer(nullptr);
                widget->SetInteractor(nullptr);
                widget->SetEnabled(false);
            }
        }
        //@}

        m_objectManager->removeGraphObj(gobj);
    }

    vtkRenderer * FCGraphRender::getRenderer()
    {
        return m_renderer;
    }

    Core::FITKGraphObjManager * FCGraphRender::getGraphObjManager()
    {
        return m_objectManager;
    }

    double FCGraphRender::getActorBounds(double * bound)
    {
        bool isEmpty = true;
        //遍历全部对象
        const int ngobj = m_objectManager->getGraphObjCount();
        for (int i=0; i< ngobj; ++i)
        {
            auto object = m_objectManager->getGraphObjTAt<FCGraphObjectVTK>(i);
            if (object == nullptr)continue;
            
            // 判断是否存在固定尺寸边界。
            double b[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };
            bool hasBds = object->getFixedBounds(b);
            if (!hasBds)
            {
                continue;
            }

            if (b[0] < bound[0]) bound[0] = b[0];
            if (b[1] > bound[1]) bound[1] = b[1];

            if (b[2] < bound[2]) bound[2] = b[2];
            if (b[3] > bound[3]) bound[3] = b[3];

            if (b[4] < bound[4]) bound[4] = b[4];
            if (b[5] > bound[5]) bound[5] = b[5];

            isEmpty = false;
        }

        if (isEmpty) return -1;
        double dx2 = (bound[1] - bound[0]) * (bound[1] - bound[0]);
        double dy2 = (bound[3] - bound[2]) * (bound[3] - bound[2]);
        double dz2 = (bound[5] - bound[4]) * (bound[5] - bound[4]);

        return sqrt(dx2 + dy2 + dz2);
    }

    int FCGraphRender::getGraphObjectCount()
    {
        if (m_objectManager)
            return m_objectManager->getGraphObjCount();
        return 0;
    }

    void FCGraphRender::clear()
    {
        const int nActor = m_objectManager->getGraphObjCount();
        for (int i = 0; i < nActor; ++i)
        {
            auto gobj = m_objectManager->getGraphObjTAt<FCGraphObjectVTK>(i);
            if (gobj == nullptr) continue;
            //清除记录
            gobj->setGraphWidget(nullptr);
            const int nact = gobj->getActorCount();
            if (m_renderer == nullptr) continue;
            //显示层移除
            for (int i = 0; i < nact; i++)
            {
                auto act = gobj->getActor(i);
                m_renderer->RemoveViewProp(gobj->getActor(i));
            }
        }
        m_objectManager->clear();
    }

    void FCGraphRender::setBackgroundColor(float* rgb1, float* rgb2 /*= nullptr*/)
    {
        //错误判断
        if (rgb1 == nullptr || m_renderer == nullptr) return;
        //只有第一个值有效
        if (rgb2 == nullptr) rgb2 = rgb1;
        //设置背景色
        m_renderer->SetGradientBackground(true);
        m_renderer->SetBackground2(rgb1[0], rgb1[1], rgb1[2]);
        m_renderer->SetBackground(rgb2[0],rgb2[1],rgb2[2]);
    }

}