/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraph3DWidgetPlane.h"
#include "FCGraph3DWidgetPlaneCallBack.h"
#include "FCGraph3DWindowVTK.h"

#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkRenderWindow.h>

namespace Comp
{
    FCGraph3DWidgetPlane::FCGraph3DWidgetPlane(FCGraph3DWindowVTK* graph3DWidget)
    {
        if (graph3DWidget == nullptr)return;
        //创建裁切平面
        _widget = vtkImplicitPlaneWidget2::New();
        _widget->CreateDefaultRepresentation();

        //获取代理类
        vtkImplicitPlaneRepresentation* planeRep = _widget->GetImplicitPlaneRepresentation();
        if (planeRep == nullptr)return;
        //关闭边框拖拽
        planeRep->SetOutlineTranslation(false);       

        _widget->SetInteractor(graph3DWidget->getVTKRenderWindow()->GetInteractor());

        _callBack = new FCGraph3DWidgetPlaneCallBack();
        connect(_callBack, SIGNAL(sigValueChange(double*, double*)), this, SIGNAL(sigValueChange(double*, double*)));
        _widget->AddObserver(vtkCommand::InteractionEvent, _callBack);
    }

    FCGraph3DWidgetPlane::~FCGraph3DWidgetPlane()
    {
        if (_widget) {
            _widget->Off();
            _widget->Delete();
            _widget = nullptr;
        }

        if (_callBack) {
            delete _callBack;
            _callBack = nullptr;
        }
    }

    void FCGraph3DWidgetPlane::setBounds(double * bounds)
    {
        vtkImplicitPlaneRepresentation* planeRep = _widget->GetImplicitPlaneRepresentation();
        if (planeRep == nullptr)return;
        planeRep->SetWidgetBounds(bounds);
    }

    void FCGraph3DWidgetPlane::setValue(double * origin, double * normal)
    {
        vtkImplicitPlaneRepresentation* planeRep = _widget->GetImplicitPlaneRepresentation();
        if (planeRep == nullptr)return;
        planeRep->SetNormal(normal);
        planeRep->SetOrigin(origin);
    }

    void FCGraph3DWidgetPlane::setIsShow(bool isShow)
    {
        if (_widget == nullptr)return;
        if (isShow) {
            _widget->On();
        }
        else {
            _widget->Off();
        }
    }
}