/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraphInteractionStyle.h"
#include "FCGraphAreaPicker.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKKeyMouseStates.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include <vtkRenderWindowInteractor.h>

namespace Comp
{
    FCGraphInteractionStyle* FCGraphInteractionStyle::New()
    {
        return new FCGraphInteractionStyle();
    }

    void FCGraphInteractionStyle::setGraph3DWin(FCGraph3DWindowVTK * graphWin)
    {
        m_graph3dWin = graphWin;
    }

    void FCGraphInteractionStyle::setInteractor(vtkRenderWindowInteractor * interactor)
    {
        if (interactor == nullptr)return;

        //将渲染窗口的交互器设置为该类
        interactor->SetInteractorStyle(this);
    }

    void FCGraphInteractionStyle::setAreaPickRenderer(vtkRenderer * renderer)
    {
        if (renderer == nullptr || m_areaPick == nullptr)return;
        m_areaPick->setPickerRender(renderer);
    }

    vtkRenderWindowInteractor * FCGraphInteractionStyle::getInteractor()
    {
        return this->Interactor;
    }

    void FCGraphInteractionStyle::setAredPickerState(bool state)
    {
        m_areaPick->enable(state);
    }

    void FCGraphInteractionStyle::areaPick(int* startPos, int* endPos)
    {

    }

    void FCGraphInteractionStyle::applyDolly(double factor)
    {
        Dolly(factor);
    }

    FCGraphInteractionStyle::FCGraphInteractionStyle()
    {
        m_areaPick = new FCGraphAreaPicker(this);
    }

    FCGraphInteractionStyle::~FCGraphInteractionStyle()
    {
        if (m_areaPick != nullptr) delete m_areaPick; m_areaPick = nullptr;
    }

    void FCGraphInteractionStyle::OnLeftButtonDown()
    {
        //使用VTK自身的鼠标左键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnLeftButtonDown();
        if (m_areaPick != nullptr && m_areaPick->isEnable())
        {
            m_areaPick->setLeftButtonDownPos(m_leftButtonDowmPos);
        }
    }

    void FCGraphInteractionStyle::OnLeftButtonUp()
    {
        //使用VTK自身的鼠标左键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

        if (m_areaPick != nullptr /*&& isMouseMoved()*/)
        {
            m_areaPick->enable(false);
        }
    }

    void FCGraphInteractionStyle::OnMiddleButtonDown()
    {
        //使用VTK自身的鼠标中键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnMiddleButtonDown();
    }

    void FCGraphInteractionStyle::OnMiddleButtonUp()
    {
        //使用VTK自身的鼠标中键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnMiddleButtonUp();
    }

    void FCGraphInteractionStyle::OnMouseMove()
    {
        //使用VTK自身的鼠标移动事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnMouseMove();

        //判断是否移动
        bool isMove = this->isMouseMoved();

        //判断鼠标左键是否按下
        bool isMouseState = FITKAPP->getGlobalData()->getKeyMouseStates()->mousePressed(Qt::LeftButton);

        if (m_areaPick != nullptr && isMove  && isMouseState)
        {
            //重新绘制框选选框
            m_areaPick->drawRectangle();
        }
    }

    void FCGraphInteractionStyle::OnMouseWheelForward()
    {
        //调用VTK自身的鼠标滑轮向前事件
        vtkInteractorStyleRubberBandPick::OnMouseWheelForward();
    }

    void FCGraphInteractionStyle::OnMouseWheelBackward()
    {
        //调用VTK自身的鼠标滑轮向后事件
        vtkInteractorStyleRubberBandPick::OnMouseWheelBackward();
    }

    void FCGraphInteractionStyle::OnRightButtonDown()
    {
        //调用VTK自身的鼠标右键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnRightButtonDown();
    }

    void FCGraphInteractionStyle::OnRightButtonUp()
    {
        //调用VTK自身的鼠标右键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnRightButtonUp();
    }

    void FCGraphInteractionStyle::OnChar()
    {
        vtkRenderWindowInteractor* interactor = this->Interactor;
        if (interactor == nullptr) {
            return;
        }

        //当前按钮
        std::string curKey = interactor->GetKeySym();

        //禁用按钮
        QList<std::string> keys = {};
        keys << "KP_3";
        keys << "3";
        keys << "r";

        //判断是否是禁用按钮
        if (keys.contains(curKey)) {
            //直接返回，不处理
            return; 
        }

        vtkInteractorStyleRubberBandPick::OnChar();
    }

    bool FCGraphInteractionStyle::isMouseMoved()
    {
        int dx = m_leftButtonUpPos[0] - m_leftButtonDowmPos[0];
        int dy = m_leftButtonUpPos[1] - m_leftButtonDowmPos[1];
        return dx * dx + dy * dy > 50;
    }
}