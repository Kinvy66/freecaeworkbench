/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCGraph3DWidgetPlaneCallBack.h"

#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>

namespace Comp
{
    void FCGraph3DWidgetPlaneCallBack::Execute(vtkObject * caller, unsigned long eventId, void * callData)
    {
        Q_UNUSED(eventId);
        Q_UNUSED(callData);

        vtkImplicitPlaneWidget2* widget = vtkImplicitPlaneWidget2::SafeDownCast(caller);
        if (widget == nullptr)return;
        vtkImplicitPlaneRepresentation* representation = widget->GetImplicitPlaneRepresentation();
        if (representation == nullptr)return;
        double origin[3] = { 0,0,0 };
        double normal[3] = { 0,0,0 };
        representation->GetOrigin(origin);
        representation->GetNormal(normal);
        emit sigValueChange(origin, normal);
    }
}

