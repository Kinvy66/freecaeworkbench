/*
 * Copyright (c) 2020-2025, Qingdao Digital Intelligent Ship & Ocean Technology Co., Ltd.
 * All rights reserved.
 *
 * This file is part of FastCAE and is distributed under the terms of the
 * BSD 3-Clause License. See the LICENSE file in the project root for details.
 */

#include "FCLegendScaleActor.h"
#include "vtkActor2D.h"
#include "vtkAxisActor2D.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkCellData.h"
#include "vtkCommand.h"
#include "vtkCoordinate.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkRenderer.h"
#include "vtkTextMapper.h"
#include "vtkTextProperty.h"
#include "vtkUnsignedCharArray.h"
#include "vtkWindow.h"
#include "vtkProperty2D.h"
#include "vtkVersionMacros.h"

vtkStandardNewMacro(FCLegendScaleActor);

//----------------------------------------------------------------------
FCLegendScaleActor::FCLegendScaleActor()
{
    this->BottomAxis = vtkAxisActor2D::New();
    this->BottomAxis->GetPositionCoordinate()->SetCoordinateSystemToViewport();
    this->BottomAxis->GetPosition2Coordinate()->SetCoordinateSystemToViewport();
    this->BottomAxis->GetPositionCoordinate()->SetReferenceCoordinate(nullptr);
    this->BottomAxis->SetFontFactor(0.6);
    this->BottomAxis->SetNumberOfLabels(5);
    this->BottomAxis->AdjustLabelsOff();
    this->BottomAxis->SetVisibility(false);

    this->BottomAxisVisibility = 0;

    this->Legend = vtkPolyData::New();
    this->LegendPoints = vtkPoints::New();
    this->Legend->SetPoints(this->LegendPoints);
    this->LegendMapper = vtkPolyDataMapper2D::New();
    this->LegendMapper->SetInputData(this->Legend);
    this->LegendActor = vtkActor2D::New();
    this->LegendActor->SetMapper(this->LegendMapper);

    this->LegendBorder = vtkPolyData::New();
    this->LegendBorder->SetPoints(this->LegendPoints);
    this->LegendBorderMapper = vtkPolyDataMapper2D::New();
    this->LegendBorderMapper->SetInputData(this->LegendBorder);
    this->LegendBorderActor = vtkActor2D::New();
    this->LegendBorderActor->SetMapper(this->LegendBorderMapper);

    // Create the legend
    vtkIdType pts[4], ptsBd[2];
    this->LegendPoints->SetNumberOfPoints(10);
    vtkCellArray* legendPolys = vtkCellArray::New();
    vtkCellArray* legendLinesBd = vtkCellArray::New();

#if VTK_MAJOR_VERSION < 9
    legendPolys->Allocate(4, 4);
    legendLinesBd->Allocate(4, 2);
#else
    legendPolys->AllocateEstimate(4, 4);
    legendPolys->AllocateEstimate(4, 2);
#endif

    this->Legend->Allocate();
    this->LegendBorder->Allocate();

    // Polys.
    pts[0] = 0;
    pts[1] = 1;
    pts[2] = 6;
    pts[3] = 5;
    legendPolys->InsertNextCell(4, pts);
    pts[0] = 1;
    pts[1] = 2;
    pts[2] = 7;
    pts[3] = 6;
    legendPolys->InsertNextCell(4, pts);
    pts[0] = 2;
    pts[1] = 3;
    pts[2] = 8;
    pts[3] = 7;
    legendPolys->InsertNextCell(4, pts);
    pts[0] = 3;
    pts[1] = 4;
    pts[2] = 9;
    pts[3] = 8;
    legendPolys->InsertNextCell(4, pts);

    // Border.
    ptsBd[0] = 0;
    ptsBd[1] = 4;
    legendLinesBd->InsertNextCell(2, ptsBd);

    ptsBd[0] = 4;
    ptsBd[1] = 9;
    legendLinesBd->InsertNextCell(2, ptsBd);

    ptsBd[0] = 9;
    ptsBd[1] = 5;
    legendLinesBd->InsertNextCell(2, ptsBd);

    ptsBd[0] = 5;
    ptsBd[1] = 0;
    legendLinesBd->InsertNextCell(2, ptsBd);

    this->Legend->SetPolys(legendPolys);
    this->LegendBorder->SetLines(legendLinesBd);
    legendPolys->Delete();
    legendLinesBd->Delete();

    // Create the cell data
    vtkUnsignedCharArray* colors = vtkUnsignedCharArray::New();
    colors->SetNumberOfComponents(3);
    colors->SetNumberOfTuples(4);
    colors->SetTuple3(0, 0, 0, 0);
    colors->SetTuple3(1, 255, 255, 255);
    colors->SetTuple3(2, 0, 0, 0);
    colors->SetTuple3(3, 255, 255, 255);

    vtkUnsignedCharArray* colorsBd = vtkUnsignedCharArray::New();
    colorsBd->SetNumberOfComponents(3);
    colorsBd->SetNumberOfTuples(4);
    colorsBd->SetTuple3(0, 0, 0, 0);
    colorsBd->SetTuple3(1, 0, 0, 0);
    colorsBd->SetTuple3(2, 0, 0, 0);
    colorsBd->SetTuple3(3, 0, 0, 0);

    this->Legend->GetCellData()->SetScalars(colors);
    this->LegendBorder->GetCellData()->SetScalars(colorsBd);
    colors->Delete();
    colorsBd->Delete();

    // Now the text. The first five are for the 0,1/4,1/2,3/4,1 labels.
    this->LegendLabelProperty = vtkTextProperty::New();
    this->LegendLabelProperty->SetJustificationToCentered();
    this->LegendLabelProperty->SetVerticalJustificationToTop();
    this->LegendLabelProperty->SetBold(1);
    this->LegendLabelProperty->SetItalic(0);
    this->LegendLabelProperty->SetShadow(1);
    this->LegendLabelProperty->SetFontFamilyToArial();
    this->LegendLabelProperty->SetFontSize(14);
    for (int i = 0; i < 5; i++)
    {
        this->LabelMappers[i] = vtkTextMapper::New();
        this->LabelMappers[i]->SetTextProperty(this->LegendLabelProperty);
        this->LabelActors[i] = vtkActor2D::New();
        this->LabelActors[i]->SetMapper(this->LabelMappers[i]);
    }
    this->LabelMappers[0]->SetInput("0");
    this->LabelMappers[1]->SetInput("1/4");
    this->LabelMappers[2]->SetInput("1/2");
    this->LabelMappers[3]->SetInput("3/4");
    this->LabelMappers[4]->SetInput("1");

    this->Coordinate = vtkCoordinate::New();
    this->Coordinate->SetCoordinateSystemToDisplay();

    vtkProperty2D* p2d = this->LegendActor->GetProperty();
    if (p2d)
    {
        p2d->SetLineWidth(1.);
        p2d->SetColor(0., 0., 0.);
    }
}

//----------------------------------------------------------------------
FCLegendScaleActor::~FCLegendScaleActor()
{
    this->BottomAxis->Delete();

    this->Legend->Delete();
    this->LegendPoints->Delete();
    this->LegendMapper->Delete();
    this->LegendActor->Delete();
    this->LegendBorder->Delete();
    this->LegendBorderMapper->Delete();
    this->LegendBorderActor->Delete();

    for (int i = 0; i < 5; i++)
    {
        this->LabelMappers[i]->Delete();
        this->LabelActors[i]->Delete();
    }
    this->LegendLabelProperty->Delete();
    this->Coordinate->Delete();
}

//----------------------------------------------------------------------
void FCLegendScaleActor::GetActors2D(vtkPropCollection* pc)
{
    pc->AddItem(this->BottomAxis);
}

//----------------------------------------------------------------------
void FCLegendScaleActor::ReleaseGraphicsResources(vtkWindow* w)
{
    this->BottomAxis->ReleaseGraphicsResources(w);

    this->LegendActor->ReleaseGraphicsResources(w);
    this->LegendBorderActor->ReleaseGraphicsResources(w);

    for (int i = 0; i < 6; i++)
    {
        this->LabelActors[i]->ReleaseGraphicsResources(w);
    }
}

//----------------------------------------------------------------------
int FCLegendScaleActor::RenderOpaqueGeometry(vtkViewport* viewport)
{
    this->BuildRepresentation(viewport);

    int renderedSomething = 0;
    if (this->BottomAxisVisibility)
    {
        renderedSomething += this->BottomAxis->RenderOpaqueGeometry(viewport);
    }
    renderedSomething += this->LegendActor->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LegendBorderActor->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LabelActors[0]->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LabelActors[1]->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LabelActors[2]->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LabelActors[3]->RenderOpaqueGeometry(viewport);
    renderedSomething += this->LabelActors[4]->RenderOpaqueGeometry(viewport);

    return renderedSomething;
}

//----------------------------------------------------------------------
int FCLegendScaleActor::RenderOverlay(vtkViewport* viewport)
{
    int renderedSomething = 0;
    if (this->BottomAxisVisibility)
    {
        renderedSomething += this->BottomAxis->RenderOverlay(viewport);
    }
    renderedSomething += this->LegendActor->RenderOverlay(viewport);
    renderedSomething += this->LegendBorderActor->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[0]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[1]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[2]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[3]->RenderOverlay(viewport);
    renderedSomething += this->LabelActors[4]->RenderOverlay(viewport);

    return renderedSomething;
}

//----------------------------------------------------------------------
void FCLegendScaleActor::BuildRepresentation(vtkViewport* viewport)
{
    if (1) // it's probably best just to rerender every time
    //   if ( this->GetMTime() > this->BuildTime ||
    //        (this->Renderer && this->Renderer->GetVTKWindow() &&
    //         this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime) )
    {
        // Specify the locations of the axes.
        const int* size = viewport->GetSize();

        // Now specify the axis values
        // distance between points
        double* xL = this->BottomAxis->GetPositionCoordinate()->GetComputedWorldValue(viewport);
        double* xR = this->BottomAxis->GetPosition2Coordinate()->GetComputedWorldValue(viewport);
        double d = sqrt(vtkMath::Distance2BetweenPoints(xL, xR));

        char buf0[256];
        snprintf(buf0, sizeof(buf0), "%.3g", -d / 2.0);
        this->LabelMappers[0]->SetInput(buf0);

        char buf1[256];
        snprintf(buf1, sizeof(buf1), "%.3g", -d / 4.0);
        this->LabelMappers[1]->SetInput(buf1);

        char buf2[256];
        snprintf(buf2, sizeof(buf2), "%.3g", 0.);
        this->LabelMappers[2]->SetInput(buf2);

        char buf3[256];
        snprintf(buf3, sizeof(buf3), "%.3g", d / 4.0);
        this->LabelMappers[3]->SetInput(buf3);

        char buf4[256];
        snprintf(buf4, sizeof(buf4), "%.3g", d / 2.0);
        this->LabelMappers[4]->SetInput(buf4);

        this->BottomAxis->SetRange(-d / 2.0, d / 2.0);

        // Update the position
        double posXScale = 0.25;
        double x1 = posXScale * size[0];
        double delX = size[0] * (1 - posXScale * 2) / 4.;

        this->BottomAxis->GetPositionCoordinate()->SetValue(
            x1, 0, 0.0);

        this->LegendPoints->SetPoint(0, x1, 30, 0);
        this->LegendPoints->SetPoint(1, x1 + delX, 30, 0);
        this->LegendPoints->SetPoint(2, x1 + 2 * delX, 30, 0);
        this->LegendPoints->SetPoint(3, x1 + 3 * delX, 30, 0);
        this->LegendPoints->SetPoint(4, x1 + 4 * delX, 30, 0);
        this->LegendPoints->SetPoint(5, x1, 40, 0);
        this->LegendPoints->SetPoint(6, x1 + delX, 40, 0);
        this->LegendPoints->SetPoint(7, x1 + 2 * delX, 40, 0);
        this->LegendPoints->SetPoint(8, x1 + 3 * delX, 40, 0);
        this->LegendPoints->SetPoint(9, x1 + 4 * delX, 40, 0);
        this->LegendPoints->Modified();

        this->BottomAxis->GetPosition2Coordinate()->SetValue(
            size[0] - x1, 0,
            0.0);

        // Specify the position of the legend title
        this->Coordinate->SetValue(0.33333 * size[0], 15, 0.0);
        double* x = this->Coordinate->GetComputedWorldValue(viewport);
        xL[0] = x[0];
        xL[1] = x[1];
        xL[2] = x[2];
        this->Coordinate->SetValue(0.66667 * size[0], 15, 0.0);
        x = this->Coordinate->GetComputedWorldValue(viewport);
        xR[0] = x[0];
        xR[1] = x[1];
        xR[2] = x[2];

        // Now specify the position of the legend labels
        x = this->LegendPoints->GetPoint(0);
        this->LabelActors[0]->SetPosition(x[0], x[1] - 1);
        x = this->LegendPoints->GetPoint(1);
        this->LabelActors[1]->SetPosition(x[0], x[1] - 1);
        x = this->LegendPoints->GetPoint(2);
        this->LabelActors[2]->SetPosition(x[0], x[1] - 1);
        x = this->LegendPoints->GetPoint(3);
        this->LabelActors[3]->SetPosition(x[0], x[1] - 1);
        x = this->LegendPoints->GetPoint(4);
        this->LabelActors[4]->SetPosition(x[0], x[1] - 1);

        this->BuildTime.Modified();
    }
}

//----------------------------------------------------------------------
void FCLegendScaleActor::PrintSelf(ostream& os, vtkIndent indent)
{
    // Superclass typedef defined in vtkTypeMacro() found in vtkSetGet.h
    this->Superclass::PrintSelf(os, indent);

    os << indent << "Bottom Axis Visibility: " << (this->BottomAxisVisibility ? "On\n" : "Off\n");

    os << indent << "Legend Label Property: ";
    if (this->LegendLabelProperty)
    {
        os << this->LegendLabelProperty << "\n";
    }
    else
    {
        os << "(none)\n";
    }

    os << indent << "Bottom Axis: ";
    if (this->BottomAxis)
    {
        os << this->BottomAxis << "\n";
    }
    else
    {
        os << "(none)\n";
    }
}
