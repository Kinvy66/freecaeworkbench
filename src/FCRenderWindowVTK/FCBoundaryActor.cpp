/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCBoundaryActor.h"
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkSmartPointer.h>
#include <vtkCellType.h>
#include <vtkUnstructuredGrid.h>
#include <vtkProperty.h>

namespace FC
{
    FCBoundaryActor::FCBoundaryActor()
    {
        //渲染窗口范围对象创建
        _boundaryActor = vtkActor::New();
        _boundaryActor->SetMapper(vtkSmartPointer<vtkDataSetMapper>::New());
        //边界对象创建
        vtkSmartPointer<vtkUnstructuredGrid> ugrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        points->InsertNextPoint(0., 0., 0.);
        points->InsertNextPoint(0., 0., 0.);
        //顶点创建
        vtkSmartPointer<vtkIdList> c1 = vtkSmartPointer<vtkIdList>::New();
        c1->InsertNextId(0);
        vtkSmartPointer<vtkIdList> c2 = vtkSmartPointer<vtkIdList>::New();
        c2->InsertNextId(1);
        //添加两个节点单元类型
        ugrid->InsertNextCell(VTKCellType::VTK_VERTEX, c1);
        ugrid->InsertNextCell(VTKCellType::VTK_VERTEX, c2);

        ugrid->SetPoints(points);
        _boundaryActor->GetMapper()->SetInputDataObject(ugrid);
        //设置为透明
        _boundaryActor->GetProperty()->SetOpacity(0);
    }

    FCBoundaryActor::~FCBoundaryActor()
    {
        if (_boundaryActor)
            _boundaryActor->Delete();
    }

    vtkActor* FCBoundaryActor::getActor()
    {
        return _boundaryActor;
    }

    void FCBoundaryActor::updateBoundary(double* bound)
    {
        //获取网格
        vtkUnstructuredGrid* ugrid =
            vtkUnstructuredGrid::SafeDownCast(_boundaryActor->GetMapper()->GetInput());
        if (ugrid == nullptr) return;
        //重置
        vtkPoints* pts = ugrid->GetPoints();
        pts->Reset();
        //重置边界
        pts->InsertNextPoint(bound[0], bound[2], bound[4]);
        pts->InsertNextPoint(bound[1], bound[3], bound[5]);

        ugrid->Modified();
    }
}
