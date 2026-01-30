/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraphAreaPicker.h"
#include "FCGraphInteractionStyle.h"
#include <vtkRenderer.h>
#include <vtkActor2D.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

namespace Comp
{
    FCGraphAreaPicker::FCGraphAreaPicker(FCGraphInteractionStyle * style)
    {
        m_style = style;
    }

    FCGraphAreaPicker::~FCGraphAreaPicker()
    {

    }
    void FCGraphAreaPicker::setLeftButtonDownPos(int * pos)
    {
        //记录鼠标左键按下位置
        m_startPos[0] = pos[0];
        m_startPos[1] = pos[1];
    }

    void FCGraphAreaPicker::setPickerRender(vtkRenderer* render)
    {
        if (render == nullptr)return;
        m_render = render;

        //初始化
        initRectangle();
        if (m_pickActor != nullptr)
            m_render->AddActor(m_pickActor);
    }

    void FCGraphAreaPicker::enable(bool state)
    {
        m_pickActor->SetVisibility(state);
        //初始化设置
        if (state)
        {
            vtkPoints* points = m_pickData->GetPoints();
            points->SetNumberOfPoints(0);
            points->InsertPoint(0, 0, 0, 0);
            points->InsertPoint(1, 0, 0, 0);
            points->InsertPoint(2, 0, 0, 0);
            points->InsertPoint(3, 0, 0, 0);

            points->Modified();
            m_pickData->Modified();
            m_pickActor->GetMapper()->Update();
        }

        //刷新渲染窗口
        vtkRenderWindow* rw = m_render->GetRenderWindow();
        if (rw != nullptr) rw->Render();
    }

    bool FCGraphAreaPicker::isEnable()
    {
        if (!m_pickActor) return false;
        return m_pickActor->GetVisibility();
    }

    void FCGraphAreaPicker::drawRectangle()
    {
        //框选选框绘制
        if (!isEnable()) return;
        
        if (m_style == nullptr || m_style->getInteractor() == nullptr)return;
        m_style->getInteractor()->GetEventPosition(m_endPos);

        //刷新框选选框
        updateRectangle();
    }

    void FCGraphAreaPicker::pick()
    {
        if (m_style)
            m_style->areaPick(m_startPos, m_endPos);
    }

    void FCGraphAreaPicker::initRectangle()
    {
        //框选选框管线绘制
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        for (int i = 0; i < 4; i++){
            points->InsertNextPoint(i, i, i);
        }

        vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
        for (int i = 0; i < 4; i++)
        {
            //绘制长方体框选选框
            vtkIdType line[2] = { i,(i + 1) % 4 };
            cells->InsertNextCell(2, line);
        }

        m_pickData = vtkSmartPointer<vtkPolyData>::New();
        m_pickData->SetPoints(points);
        m_pickData->SetLines(cells);

        vtkSmartPointer<vtkPolyDataMapper2D> mapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
        mapper->SetInputData(m_pickData);

        m_pickActor = vtkSmartPointer<vtkActor2D>::New();
        m_pickActor->SetMapper(mapper);

        //设置选框颜色
        m_pickActor->GetProperty()->SetColor(1, 1, 1);

        //设置选框宽度
        m_pickActor->GetProperty()->SetLineWidth(2);

        // 初始化颜色。
        m_pickActor->GetProperty()->SetColor(m_color3);
    }

    void FCGraphAreaPicker::updateRectangle()
    {
        if (m_render == nullptr) return;
        vtkPoints* points = m_pickData->GetPoints();
        points->SetNumberOfPoints(0);
        //坐标位置更新
        const int xmax = m_startPos[0] > m_endPos[0] ? m_startPos[0] : m_endPos[0];
        const int xmin = m_startPos[0] + m_endPos[0] - xmax;
        const int ymax = m_startPos[1] > m_endPos[1] ? m_startPos[1] : m_endPos[1];
        const int ymin = m_startPos[1] + m_endPos[1] - ymax;
        if (xmax - xmin < 2 || ymax - ymin < 2) return;

        points->InsertPoint(0, xmax, ymax, 0);
        points->InsertPoint(1, xmin, ymax, 0);
        points->InsertPoint(2, xmin, ymin, 0);
        points->InsertPoint(3, xmax, ymin, 0);

        //更新渲染
        points->Modified();
        m_pickData->Modified();
        m_pickActor->GetMapper()->Update();

        vtkRenderWindow* rw = m_render->GetRenderWindow();
        if (rw != nullptr)
            rw->Render();
    }

    void FCGraphAreaPicker::setColor(double rf, double gf, double bf)
    {
        m_color3[0] = rf;
        m_color3[1] = gf;
        m_color3[2] = bf;

        if (!m_pickActor)
        {
            return;
        }

        vtkProperty2D* prop2d = m_pickActor->GetProperty();
        if (!prop2d)
        {
            return;
        }

        prop2d->SetColor(rf, gf, bf);
    }
}